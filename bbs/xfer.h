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
#ifndef INCLUDED_BBS_XFER_H
#define INCLUDED_BBS_XFER_H

#include "core/file.h"
#include <string>

struct uploadsrec;

namespace wwiv::sdk::files {
struct directory_t;
}

/** return true if file_name is in the queue */
bool check_ul_event(int directory_num, uploadsrec* upload_record);
bool okfn(const std::string& filename);
void print_devices();
int list_arc_out(const std::string& file_name, const std::string& dir);
bool ratio_ok();
bool dcs();
void dliscan1(int directory_num);
void dliscan1(const wwiv::sdk::files::directory_t& dir);
void dliscan();
std::string aligns(const std::string& file_name);
void printinfo(uploadsrec* u, bool* abort);
void printtitle(bool* abort);
std::string file_mask(const std::string& prompt);
std::string file_mask();
void listfiles();
void nscandir(uint16_t nDirNum, bool& need_title, bool* abort);
void nscanall();
void searchall();
int recno(const std::string& file_mask);
int nrecno(const std::string& file_mask, int start_recno);
int printfileinfo(const uploadsrec* u, const wwiv::sdk::files::directory_t& dir);
void remlist(const std::string& file_name);

#endif 
