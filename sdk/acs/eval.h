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
#ifndef INCLUDED_SDK_ACS_EVAL_H
#define INCLUDED_SDK_ACS_EVAL_H

#include "core/parser/ast.h"
#include "sdk/value/value.h"
#include "sdk/value/valueprovider.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace wwiv::sdk::acs {

enum class debug_message_t { trace, parse };

/** Shorthand to create an optional Value */
template <typename T> static std::optional<value::Value> val(T&& v) {
  return std::make_optional<value::Value>(std::forward<T>(v));
}

class DefaultValueProvider : public value::ValueProvider {
public:
  DefaultValueProvider() : ValueProvider("") {}
  [[nodiscard]] std::optional<value::Value> value(const std::string& name) const override {
    if (name == "true") {
      return val(true);
    }
    if (name == "false") {
      return val(false);
    }
    return std::nullopt;
  }  
};

/** 
 * Evaluation engine for evaluating expressions provides.
 */
class Eval final : public core::parser::AstVisitor {
public:
  explicit Eval(std::string expression);
  ~Eval() override = default;

  bool eval_throws();
  bool eval();
  bool add(std::unique_ptr<value::ValueProvider>&& p);
  bool add(const value::ValueProvider* p);
  std::optional<value::Value> to_value(core::parser::Factor* n);

  /** 
   * Gets the error text that occurred when failing to evaluate the expression, 
   * or empty string if none exists.
   */
  [[nodiscard]] std::string error_text() const noexcept { return error_text_; }
  [[nodiscard]] bool error() const noexcept { return !error_text_.empty(); }
  
  ///////////////////////////////////////////////////////////////////////////
  // Debug support:  This writes out debug_info lines as the statement is 
  // evaluated. Used to explain how the statement was evaluated.
  [[nodiscard]] const std::vector<std::string>& debug_info() const { return debug_info_; }

  ///////////////////////////////////////////////////////////////////////////
  // Visitor implementation
  //

  void visit(core::parser::AstNode*) override {}
  void visit(core::parser::Expression* n) override;
  void visit(core::parser::Factor* n) override;

private:
  std::string expression_;
  std::unordered_map<std::string, const value::ValueProvider*> providers_;
  std::unordered_map<int, value::Value> values_;
  std::string error_text_;
  std::vector<std::string> debug_info_;
  std::unordered_map<std::string, std::unique_ptr<value::ValueProvider>> providers_storage_;
  DefaultValueProvider default_provider_;
};  // class

} 

#endif
