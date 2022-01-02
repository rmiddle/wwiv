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
#ifndef INCLUDED_BBS_MESSAGE_FILE_H
#define INCLUDED_BBS_MESSAGE_FILE_H

#include <cstdint>
#include <optional>
#include <string>

constexpr uint8_t EMAIL_STORAGE = 2;

struct messagerec;

void remove_link(const messagerec* msg, const std::string& fileName);
void savefile(const std::string& text, messagerec* msg, const std::string& fileName);
std::optional<std::string> readfile(const messagerec* msg, const std::string& fileName);
void lineadd(const messagerec* msg, const std::string& sx, const std::string fileName);

#endif
