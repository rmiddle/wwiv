/**************************************************************************/
/*                                                                        */
/*                            WWIV Version 5                              */
/*           Copyright (C)2020-2021, WWIV Software Services               */
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
/**************************************************************************/
#ifndef INCLUDED_SDK_VALUE_BBSVALUEPROVIDER_H
#define INCLUDED_SDK_VALUE_BBSVALUEPROVIDER_H

#include "sdk/config.h"
#include "sdk/user.h"
#include "sdk/value/value.h"
#include "sdk/value/valueprovider.h"
#include <optional>
#include <string>

namespace wwiv {
namespace common {
class SessionContext;
}
}

namespace wwiv::sdk::value {

/**
 * ValueProvider for "bbs" or system attributes.
 */
class BbsValueProvider final : public ValueProvider {
public:
  /** 
   * Constructs a new ValueProvider.  'user' must remain valid for 
   * the duration of this instance lifetime.
   */
  BbsValueProvider(const Config& config, const common::SessionContext& sess);
  [[nodiscard]] std::optional<Value> value(const std::string& name) const override;

private:
  const Config& config_;
  const common::SessionContext& sess_;
};

}

#endif
