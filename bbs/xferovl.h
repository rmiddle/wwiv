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
#ifndef INCLUDED_BBS_XFEROVL_H
#define INCLUDED_BBS_XFEROVL_H

#include <string>

namespace wwiv::sdk::files {
class FileRecord;
}

void move_file();
void sortdir(int directory_num, int type);
void sort_all(int type);
void rename_file();
bool maybe_upload(const std::string& file_name, int directory_num, const std::string& description);
void upload_files(const std::string& file_name, int directory_num, int type);
bool uploadall(int directory_num);
void relist();
void edit_database();
void add_to_file_database(const std::string& file_name);
void add_to_file_database(const wwiv::sdk::files::FileRecord& f);
void remove_from_file_database(const std::string& file_name);
bool is_uploadable(const std::string& file_name);
void xfer_defaults();
void finddescription();
void arc_l();

#endif
