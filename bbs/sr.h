/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*             Copyright (C)1998-2022, WWIV Software Services             */
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
#ifndef INCLUDED_BBS_SR_H
#define INCLUDED_BBS_SR_H

#include <filesystem>
#include <string>

enum class xfertype {
  xf_up,
  xf_down,
  xf_up_temp,
  xf_down_temp,
  xf_up_batch,
  xf_down_batch,
  xf_none
};

void calc_CRC(unsigned char b);
char gettimeout(long ds, bool *abort);
int extern_prot(int nProtocolNum, const std::filesystem::path& path, bool bSending);
bool ok_prot(int nProtocolNum, xfertype xt);
std::string prot_name(int num);
int  get_protocol(xfertype xt);
void ascii_send(const std::filesystem::path& path, bool* sent, double* percent);
void maybe_internal(const std::filesystem::path& path, bool* xferred, double* percent, bool bSend,
                    int prot);
void send_file(const std::filesystem::path& path, bool* sent, bool* abort,
               const std::string& sfn, int dn, long fs);
void receive_file(const std::filesystem::path& path, int* received, const std::string& sfn, int dn);


#endif
