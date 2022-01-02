/**************************************************************************/
/*                                                                        */
/*                            WWIV Version 5                              */
/*           Copyright (C)2020-2022, WWIV Software Services               */
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
#ifndef INCLUDED_SDK_ACS_EVAL_ERROR_H
#define INCLUDED_SDK_ACS_EVAL_ERROR_H

#include <stdexcept>
#include <string>

namespace wwiv::sdk::acs {

/** An error evaluating the expression */
struct eval_error : public std::runtime_error {
  eval_error(const std::string& m) : runtime_error(m) {}
};

}

#endif
