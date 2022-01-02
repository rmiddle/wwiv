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
#include "bbs/menus/printcommands.h"

#include "bbs/menus/menucommands.h"
#include "bbs/bbs.h"
#include "sdk/config.h"
#include "sdk/menus/menu.h"
#include "sdk/menus/menus_cereal.h"

namespace wwiv::bbs::menus {

using namespace wwiv::core;
using namespace wwiv::strings;
using namespace wwiv::sdk::menus;

void emit_menu(const std::string& cmd, const std::string& cat, const std::string& desc,
               bool markdown, bool group_by_cat) {
  const auto lines = SplitString(desc, "\n");
  const auto c = group_by_cat || cat.empty() ? "" : StrCat(" [", cat, "]");
  if (markdown) {
    std::cout << "### ";
  }
  std::cout << cmd << c << std::endl;
  for (const auto& d : lines) {
    std::cout << "    " << StringTrim(d) << std::endl;
  }
  std::cout << std::endl << std::endl;
}

void emit_category_name(const std::string& cat, bool output_markdown) {
  if (cat.empty()) {
    return;
  }

  if (output_markdown) {
    std::cout << "## ";
  }
  std::cout << "Category: " << StringTrim(cat) << std::endl;
  std::cout << "***" << std::endl;
  std::cout << std::endl;
}

void PrintMenuCommands(const std::string& arg) {
  const auto category_group = arg.find('c') != std::string::npos;
  const auto output_markdown = arg.find('m') != std::string::npos;
  const auto output_json = arg.find('j') != std::string::npos;

  auto raw_commands = CreateCommandMap();
  auto& commands = raw_commands;
  std::map<std::string, std::vector<MenuItem>> cat_commands;
  for (const auto& c : raw_commands) {
    cat_commands[c.second.category_].emplace_back(c.second);
  }

  if (output_json) {
    std::cout << "Saving JSON help file." << std::endl;
    std::vector<menu_command_help_t> cmds;
    for (const auto& c : raw_commands) {
      menu_command_help_t cmd{};
      cmd.cat = c.second.category_;
      cmd.cmd = c.second.cmd_;
      cmd.help = c.second.description_;
      StringTrim(&cmd.help);
      cmds.emplace_back(cmd);
    }
    std::sort(std::begin(cmds), std::end(cmds),
              [](const menu_command_help_t& l, const menu_command_help_t& r) -> bool {
                return l < r;
              });
    SaveCommandHelpJSON(a()->config()->datadir(), cmds);
    return;
  }

  if (output_markdown) {
    std::cout << R"(
# WWIV Menu Commands
***

Here is the list of all WWIV Menu Commands available in the Menu Editor broken
out by category.

)";
  }

  if (category_group) {
    for (const auto& c : cat_commands) {
      emit_category_name(c.first, output_markdown);
      for (const auto& m : c.second) {
        emit_menu(m.cmd_, "", m.description_, output_markdown, true);
      }
    }
    return;
  }
  for (const auto& c : commands) {
    const auto cmd = c.first;
    const auto cat = c.second.category_;
    const auto desc = c.second.description_;
    emit_menu(cmd, cat, desc, output_markdown, false);
  }
}


}
