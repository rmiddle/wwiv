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
#ifndef INCLUDED_WWIVUTIL_DUMP_NODELIST_H
#define INCLUDED_WWIVUTIL_DUMP_NODELIST_H

#include "core/command_line.h"
#include "wwivutil/command.h"

namespace wwiv::wwivutil::fido {

class DumpNodelistCommand final : public UtilCommand {
public:
  DumpNodelistCommand() : UtilCommand("nodelist", "Dumps contents of a fido nodelist") {}
  [[nodiscard]] std::string GetUsage() const override;
  int Execute() override;
  bool AddSubCommands() override;
};

}

#endif
