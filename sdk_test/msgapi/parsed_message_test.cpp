/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5.x                          */
/*           Copyright (C)2014-2022, WWIV Software Services               */
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
#include "gtest/gtest.h"

#include "bbs/msgbase1.h"
#include "core/datetime.h"
#include "core/stl.h"
#include "core/strings.h"
#include "core/textfile.h"
#include "local_io/keycodes.h"
#include "sdk/msgapi/parsed_message.h"

using namespace wwiv::core;
using namespace wwiv::local::io;
using namespace wwiv::strings;
using namespace wwiv::sdk;
using namespace wwiv::stl;
using namespace wwiv::sdk::msgapi;

static std::vector<std::string> split_wwiv_style_message_text(const std::string& s) {
  auto temp(s);
  temp.erase(std::remove(temp.begin(), temp.end(), 10), temp.end());
  // Use SplitString(..., false) so we don't skip blank lines.
  return SplitString(temp, "\r", false);
}

class ParsedMessageTest : public ::testing::Test {
protected:
  ParsedMessageTest()
    : ca("\001"),
      cd("\004"),
      cz(std::string(1, static_cast<char>(CZ))) {}

  void SetUp() override {
    expected_list_.emplace_back("Title");
    expected_list_.push_back(daten_to_wwivnet_time(daten_t_now()));
    expected_list_.push_back(ca + "PID");
    expected_list_.push_back(ca + "MSGID 1234");
    expected_list_.push_back(ca + "TZUTC");
    expected_list_.emplace_back("Line of text");

    expected_list_new_msgid_.emplace_back("Title");
    expected_list_new_msgid_.push_back(daten_to_wwivnet_time(daten_t_now()));
    expected_list_new_msgid_.push_back(ca + "PID");
    expected_list_new_msgid_.push_back(ca + "MSGID 5678");
    expected_list_new_msgid_.push_back(ca + "TZUTC");
    expected_list_new_msgid_.emplace_back("Line of text");


    expected_list_wwiv_.emplace_back("Title");
    expected_list_wwiv_.push_back(daten_to_wwivnet_time(daten_t_now()));
    expected_list_wwiv_.push_back(cd + "0PID");
    expected_list_wwiv_.push_back(cd + "0MSGID 1234");
    expected_list_wwiv_.push_back(cd + "0TZUTC");
    expected_list_wwiv_.emplace_back("Line of text");
  }

  std::string expected_string(size_t pos, const std::string& val) {
    insert_at(expected_list_, pos, val);
    return JoinStrings(expected_list_, "\r\n") + cz;
  }

  std::string expected_string_new_msgid(size_t pos, const std::string& val) {
    insert_at(expected_list_new_msgid_, pos, val);
    return JoinStrings(expected_list_new_msgid_, "\r\n") + cz;
  }

  std::string expected_string_wwiv(size_t pos, const std::string& val) {
    insert_at(expected_list_wwiv_, pos, val);
    return JoinStrings(expected_list_wwiv_, "\r\n") + cz;
  }

  void TearDown() override {
    expected_list_.clear();
    expected_list_wwiv_.clear();
  }

  std::string ca;
  std::string cd;
  std::string cz;

  std::vector<std::string> expected_list_;
  std::vector<std::string> expected_list_new_msgid_;
  std::vector<std::string> expected_list_wwiv_;
};

TEST_F(ParsedMessageTest, AfterMsgID) {
  const auto kReply = ca + "REPLY";
  ParsedMessageText p(ca, JoinStrings(expected_list_, "\r\n"), split_wwiv_style_message_text, "\r\n");
  p.add_control_line_after("MSGID", "REPLY");
  const auto actual_string = p.to_string();

  EXPECT_EQ(expected_string(4, kReply), actual_string);
}

TEST_F(ParsedMessageTest, AddReplyAndReplaceMsgID) {
  const auto kReply = ca + "REPLY";
  ParsedMessageText p(ca, JoinStrings(expected_list_, "\r\n"), split_wwiv_style_message_text,
                      "\r\n");
  const auto kNewMsgId = ca + "MSGID 5678";
  p.add_control_line_after("MSGID", "MSGID 5678");
  // Remove original msgid
  p.remove_control_line("MSGID");
  p.add_control_line_after("MSGID", "REPLY");
  const auto actual_string = p.to_string();

  EXPECT_EQ(expected_string_new_msgid(4, kReply), actual_string);
}

TEST_F(ParsedMessageTest, AfterMsgID_WWIVControlLines) {
  const auto kReply = cd + "0REPLY";
  ParsedMessageText p(cd + "0", JoinStrings(expected_list_wwiv_, "\r\n"),
                      split_wwiv_style_message_text, "\r\n");
  p.add_control_line_after("MSGID", "REPLY");
  const auto actual_string = p.to_string();

  EXPECT_EQ(expected_string_wwiv(4, kReply), actual_string);
}

TEST_F(ParsedMessageTest, AtEndOfControlLines) {
  const auto kControlLineWithControlChar = ca + "DUDE";
  const std::string kControlLine = "DUDE";
  ParsedMessageText p(ca, JoinStrings(expected_list_, "\r\n"), split_wwiv_style_message_text,
                      "\r\n");
  p.add_control_line(kControlLine);
  const auto actual_string = p.to_string();

  EXPECT_EQ(expected_string(5, kControlLineWithControlChar), actual_string);
}

TEST_F(ParsedMessageTest, AtEndOfControlLines_WWIVControlLines) {
  const std::string kControlLine = "DUDE";
  const auto kControlLineWithControlChar = cd + "0DUDE";
  ParsedMessageText p(cd + "0", JoinStrings(expected_list_wwiv_, "\r\n"),
                      split_wwiv_style_message_text, "\r\n");
  p.add_control_line(kControlLine);
  const auto actual_string = p.to_string();

  EXPECT_EQ(expected_string_wwiv(5, kControlLineWithControlChar), actual_string);
}

TEST(WWIVParsedMessageTest, ToString_StaysSingleLine) {
  const std::string cz(1, static_cast<char>(CZ));
  const std::string text = "This is a long line and this is a long line and this is a long line and this too is a long line and this too is a long line";

  const WWIVParsedMessageText p(text);
  EXPECT_EQ(StrCat(text, "\r\n", cz), p.to_string());
}

TEST(WWIVParsedMessageTest, ToString_SplitLineWithContinuations) {
  const std::string cz(1, static_cast<char>(CZ));
  const std::string text = "This is a long line and this is a long line and this is a long line and this\x1\r\n too is a long line and this too is a long line";
  const std::string expected = "This is a long line and this is a long line and this is a long line and this too is a long line and this too is a long line";

  const WWIVParsedMessageText p(text);
  EXPECT_EQ(StrCat(expected, "\r\n", cz), p.to_string());
}

TEST(WWIVParsedMessageTest, ToLines_Smoke) {
  const std::string cz(1, static_cast<char>(CZ));
  const std::string text = 
    "This is a long line and this is a long line and this is a long line and this\x1\r\n too is a long line and this too is a long line";

  const WWIVParsedMessageText p(text);
  parsed_message_lines_style_t style{};
  style.line_length = 40;
  const auto lines = p.to_lines(style);
  EXPECT_EQ(4u, lines.size());
  EXPECT_EQ("This is a long line and this is a long\x1|"
            "line and this is a long line and this\x1|"
            "too is a long line and this too is a\x1|"
            "long line|",
            JoinStrings(lines, "|"));
}

TEST(WWIVParsedMessageTest, ToLines_ReattributeQuote) {
  const std::string cz(1, static_cast<char>(CZ));
  const std::string text =     "RF> This is a long line of text\r\nRF> xxxx of the text";
  const std::string expected = "RF> This is a long\x1|RF> line of text|RF> xxxx of the text|";

  const WWIVParsedMessageText p(text);
  parsed_message_lines_style_t style{};
  style.line_length = 20;
  style.reattribute_quotes = true;
  const auto lines = p.to_lines(style);
  EXPECT_EQ(3u, lines.size());
  EXPECT_EQ(expected,
            JoinStrings(lines, "|"));
}

TEST(WWIVParsedMessageTest, ToLines_Hang) {
  const std::string cz(1, static_cast<char>(CZ));
  //TextFile f(R"(U:\wwiv\gfiles\message-from-jim-killed-quoting.txt)", "rt");
  //auto text = f.ReadFileIntoString();
  std::string raw_text =R"(Re: WWIV Chat Sunday December 12th
Jimmy Mac #1 @707
Mon Dec  7 22:52:26 2020
0R 53 - 12/07/20 23:21:22 wwivnet ->513
0R 38RC6 - 12/07/20 18:06:42 WWIVnet ->1
0R 38RC6 - 12/07/20 18:06:41 WWIVnet ->1
0R 53 - 12/07/20 14:53:59 WWIVnet ->707
RE: Re: WWIV Chat Sunday December 12th
BY: Rushfan #1 @513

0PID: WWIV 5.6.0.3359

1R7> 5Oh, in wwiv.ini back in 5.2 or 5.3, I Changed the defaults for the temp0
1R7> 5and batch directory (it shouldn't impact your use).  You may want to0
1R7> 5change it, it's easier for scripting.  Here's what it is now:0
1R7> 0
1R7> 5;=======================================================================0
1R7> 5=====0
1R7> 5;                        TEMPORARY DIRECTORY SETTING0
1R7> 5;=======================================================================0
1R7> 5=====0
1R7> 5NUM_INSTANCES        = 80
1R7> 5TEMP_DIRECTORY       = e/%n/temp0
1R7> 5BATCH_DIRECTORY      = e/%n/batch0
1R7> 0
1R7> 5The e is for ephemeral, and it makes it handle to just rmdir /s/q e to0
1R7> 5clean everything up.0
1R7> 0

oh!  D'Oh! I'm still using my wwiv.ini from 4.3!  I'll need to review the new 
one to see what else needs updating. So, do the same %x options apply in 
chainedit? Will changing wwiv.ini impact the games requiring changes?

J..

1
226<-->     The Blood Stone BBS - Telnet & HTTP www.bsbbs.com      <-->
326 \/        WWIVnet Node 1@707 - Sonoma County California         \/
4
5


  )";
  auto raw_lines = SplitString(raw_text, "\n");
  auto text = JoinStrings(raw_lines, "\r\n");
  const std::string expected = "X";

  WWIVParsedMessageText p(text);
  parsed_message_lines_style_t style{};
  style.line_length = 72;
  style.ctrl_lines = msgapi::control_lines_t::no_control_lines;
  style.add_wrapping_marker = false;
  // experimental
  style.reattribute_quotes = true;
  const auto lines = p.to_lines(style);
  EXPECT_EQ(34u, lines.size()) << JoinStrings(lines, "\n");
}
