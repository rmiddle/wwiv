/**************************************************************************/
/*                                                                        */
/*                  WWIV Initialization Utility Version 5                 */
/*               Copyright (C)2014-2022, WWIV Software Services           */
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
#ifndef INCLUDED_WWIVCONFIG_SUBSDIRS_H
#define INCLUDED_WWIVCONFIG_SUBSDIRS_H

#include "sdk/config.h"

static constexpr int min_num_subs_and_dirs = 128;
static constexpr int default_num_subs = 256;
static constexpr int default_num_dirs = 128;
static constexpr int max_num_subs_and_dirs = 4096;

void up_subs_dirs(wwiv::sdk::Config& config);

#endif // INCLUDED_WWIVCONFIG_SUBSDIRS_H
