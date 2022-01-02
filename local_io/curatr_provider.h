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
#ifndef INCLUDED_LOCAL_IO_CURATR_PROVIDER_H
#define INCLUDED_LOCAL_IO_CURATR_PROVIDER_H

#include <cstdint>

namespace wwiv::local::io {

class curatr_provider {
public:
  virtual ~curatr_provider() = default;
  [[nodiscard]] virtual uint8_t curatr() const noexcept = 0;
  virtual void curatr(int n) = 0;
};

}

#endif
