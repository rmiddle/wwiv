/**************************************************************************/
/*                                                                        */
/*                              WWIV Version 5                            */
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
#include "wwivd/wwivd.h"

#include "core/file.h"
#include "core/log.h"
#include "core/os.h"
#include "core/socket_connection.h"
#include "core/strings.h"
#include "sdk/wwivd_config.h"
#include <atomic>
#include <iostream>
#include <csignal>
#include <string>

using namespace wwiv::core;
using namespace wwiv::sdk;
using namespace wwiv::strings;
using namespace wwiv::os;

namespace wwiv::wwivd {

extern std::atomic<bool> need_to_exit;
} // namespace wwiv

using namespace wwiv::wwivd;

void signal_handler(int mysignal) {
  switch (mysignal) {
  // Graceful exit
  case SIGTERM: {
    std::cerr << "SIGTERM: " << mysignal << std::endl;
    // On Windows since we do this, we re-raise it.
    signal(mysignal, SIG_DFL);
    raise(mysignal);
  } break;
  // Interrupts
  case SIGINT: {
    std::cerr << "SIGINT: " << mysignal << std::endl;
    need_to_exit.store(true);
    // call default handler
  } break;
  default: {
    std::cerr << "Unknown signal: " << mysignal << std::endl;
  }
  }
}

void BeforeStartServer() {
  // Not the best place, but this works.
  InitializeSockets();
  signal(SIGTERM, signal_handler);
  signal(SIGINT, signal_handler);
  std::cerr << "set signal handlers" << std::endl;
}

void SwitchToNonRootUser(const std::string&) {
}

bool ExecCommandAndWait(const wwivd_config_t& wc, const std::string& cmd, const std::string& pid,
                        int node_number, SOCKET sock) {

  LOG(INFO) << pid << "Invoking Command Line (Win32):" << cmd;

  STARTUPINFO si{};
  si.cb = sizeof(STARTUPINFO);

  if (wc.launch_minimized) {
    // dwFlags says to look at wShowWindow, and wShowWindow
    // says to minimize
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_MINIMIZE;
  }

  PROCESS_INFORMATION pi{};
  char cmdstr[4000];
  to_char_array(cmdstr, cmd);

  const DWORD creation_flags = CREATE_NEW_CONSOLE;

  const auto current_dir = File::current_directory().string();
  const auto ok = CreateProcess(
    nullptr, 
    cmdstr,
    nullptr,
    nullptr,
    TRUE,
    creation_flags,
    nullptr,
    current_dir.c_str(),
    &si,
    &pi);

  if (!ok) {
    // CreateProcess failed.
    LOG(ERROR) << "Error invoking CreateProcess.";
    return false;
  }

  if (sock != INVALID_SOCKET) {
    // We're done with this socket and the child has another reference count
    // to it.
    closesocket(sock);
  }

  // Wait until child process exits.
  auto dwExitCode = WaitForSingleObject(pi.hProcess, INFINITE);
  GetExitCodeProcess(pi.hProcess, &dwExitCode);

  // Close process and thread handles. 
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  if (node_number > 0) {
    LOG(INFO) << "Node #" << node_number << " exited with error code: " << dwExitCode;
  } else {
    LOG(INFO) << "Command: '" << cmd << "' exited with error code: " << dwExitCode;
  }
  return true;
}

