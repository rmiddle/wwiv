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
/*                                                                        */
/**************************************************************************/
#include "bbs/bbs.h"
#include "core/file.h"
#include "core/inifile.h"
#include "core/stl.h"
#include "core/strings.h"
#include "fmt/format.h"
#include "sdk/filenames.h"
#include <string>
#include <vector>

using namespace wwiv::core;
using namespace wwiv::stl;
using namespace wwiv::strings;

/**
 * Returns the computer type string for computer type number num.
 *
 * @param num The computer type number for which to return the name
 *
 * @return The text describing computer type num
 */
std::string ctypes(int num) {
  // The default list of computer types
  const std::vector<std::string> default_ctypes{
    "IBM PC (8088)",
    "IBM PS/2",
    "IBM AT (80286)",
    "IBM AT (80386)",
    "IBM AT (80486)",
    "Pentium",
    "Apple 2",
    "Apple Mac",
    "Commodore Amiga",
    "Commodore",
    "Atari",
    "Other",
  };

  const IniFile iniFile(FilePath(a()->bbspath(), WWIV_INI), {"CTYPES"});
  if (iniFile.IsOpen()) {
    return iniFile.value<std::string>(fmt::format("COMP_TYPE[{}]", num + 1));
  }
  if (num < 0 || num > ssize(default_ctypes)) {
    return "";
  }
  return default_ctypes[num];
}
