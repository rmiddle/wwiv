/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)2016-2022, WWIV Software Services             */
/*                                                                        */
/*    Licensed  under the  Apache License, Version  2.0 (the "License");  */
/*    you may not use this  file  except in compliance with the License.  */
/*    You may obtain a copy of the License at                             */
/*                                                                        */
/*                http://www.apache.org/licenses/LICENSE-2.0              */
/*                                                                        */
/*    Unless  required  by  applicable  law  or agreed to  in  writing,   */
/*    software  distributed  under  the  License  is  distributed on an   */
/*    "AS IS"  BASIS, WITHOUT  WARRANTIES  OR  CONDITIONS OF ANY  KIND,   */
/*    either  express  or implied.  See  the  License for  the specific   */
/*    language governing permissions and limitations under the License.   */
/*                                                                        */
/**************************************************************************/
#include "binkp/cram.h"

#include "core/datetime.h"
#include "core/log.h"
#include "core/md5.h"
#include "core/strings.h"
#include "core/version.h"
#include "fmt/format.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <string>

using namespace wwiv::strings;

namespace wwiv::net {

bool Cram::GenerateChallengeData() {
  if (challenge_data_.empty()) {
    const auto raw = fmt::format("WWIV {} {} {}", core::full_version(),
                                 os::random_number(std::numeric_limits<int>::max()),
                                 core::DateTime::now().to_string()); 
    challenge_data_ = md5(raw);
  }
  initialized_ = true;
  return true;
}

bool Cram::ValidatePassword(const std::string& challenge,
                            const std::string& secret, 
                            const std::string& given_hashed_secret) {
  const auto expected = CreateHashedSecret(challenge, secret);
  VLOG(1) << "       CRAM Challenge: " << challenge;
  VLOG(1) << "       expected pw: " << expected << "; given: " << given_hashed_secret;
  return expected == given_hashed_secret;
}
 
static std::string FromHex(const std::string& hex) {
  if ((hex.length() % 2) != 0) {
    throw std::logic_error(
        StrCat("FromHex needs length of size a multiple of 2.  hex: '", hex, "' len:", hex.size()));
  }

  if (hex.length() > 256) {
    throw std::logic_error("FromHex needs length of < 256");
  }

  char result[128];
  auto len = 0;
  auto it = hex.begin();
  while (it != hex.end()) {
    std::string s;
    s.push_back(*it++);
    s.push_back(*it++);

    const auto chl = to_number<unsigned long>(s, 16);
    const char ch = chl & 0xff;
    result[len++] = ch;
  }
  return std::string(result, len);
}

static std::string SecretOrHash(const std::string& secret) {
  if (secret.size() <= 64) {
    return secret;
  }

  VLOG(1) << "secret is >64 bytes";

  MD5_CTX ctx;
  MD5_Init(&ctx);

  unsigned char hash[16];
  MD5_Update(&ctx, &secret[0], secret.size());
  MD5_Final(hash, &ctx);

  return std::string(reinterpret_cast<const char*>(hash), 16);
}

std::string Cram::CreateHashedSecret(
    const std::string& original_challenge_hex, const std::string& secret) {
  if (!initialized_) {
    if (!GenerateChallengeData()) {
      // TODO: Go Boom
    }
  }
  
  auto c = StringTrim(original_challenge_hex);
  while (c.back() == '\0') {
    // Radius adds a trailing null character here.
    c.pop_back();
  }
  const auto original_challenge = FromHex(c);

  auto challenge = SecretOrHash(original_challenge);
  unsigned char ipad[65];
  unsigned char opad[65];
  memset(ipad, 0, sizeof(ipad));
  memset(opad, 0, sizeof(opad));
  memcpy(ipad, secret.data(), secret.size());
  memcpy(opad, secret.data(), secret.size());

  for (auto i = 0; i < 65; i++) {
    ipad[i] ^= 0x36;
    opad[i] ^= 0x5c;
  }

  // Inner
  MD5_CTX ctx;
  unsigned char digest[17];
  MD5_Init(&ctx);
  MD5_Update(&ctx, ipad, 64);
  MD5_Update(&ctx, challenge.data(), challenge.size());
  MD5_Final(digest, &ctx);

  // Outer
  MD5_Init(&ctx);
  MD5_Update(&ctx, opad, 64);
  MD5_Update(&ctx, digest, 16);
  MD5_Final(digest, &ctx);

  std::ostringstream ss;
  for (int i = 0; i < 16; i++) {
    ss << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(digest[i]);
  }
  return ss.str();
}

}
