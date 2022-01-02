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
#include "wwivutil/command.h"

#include "core/command_line.h"
#include "core/file.h"
#include "core/strings.h"
#include "sdk/config.h"

#include <memory>
#include <string>
#include <vector>

using namespace wwiv::strings;
using namespace wwiv::sdk;

namespace wwiv::wwivutil {

// WWIVutil commands

UtilCommand::UtilCommand(const std::string& name, const std::string& description)
  : CommandLineCommand(name, description) {}
UtilCommand::~UtilCommand() = default;

bool UtilCommand::add(std::shared_ptr<UtilCommand> cmd) {
  subcommands_.push_back(cmd);
  cmd->AddStandardArgs();
  const auto added = CommandLineCommand::add(cmd);
  // We want to add the sub commands after we add this one
  cmd->AddSubCommands();
  return added;
}

Configuration* UtilCommand::config() const {
  return config_.get();
}

bool UtilCommand::set_config(const std::shared_ptr<Configuration>& config) { 
  for (const auto& s : subcommands_) {
    s->set_config(config);
  }
  config_ = config;
  return true; 
}

}  // namespace
