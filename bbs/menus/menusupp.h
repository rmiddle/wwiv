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
#ifndef INCLUDED_BBS_MENUS_MENUSUPP_H
#define INCLUDED_BBS_MENUS_MENUSUPP_H

#include "bbs/menus/menu_context.h"

namespace wwiv::bbs::menus {

void UnQScan();
void DirList();
void UpSubConf();
void DownSubConf();
void DownSub();
void UpSub();
void ValidateUser();
void Chains();
void TimeBank();
void Defaults(bool& need_menu_reload);
void SendEMail();
void FeedBack();
void Bulletins();
void SystemInfo();
void JumpSubConf();
void KillEMail();
void LastCallers();
void ReadEMail();
void NewMessageScan();
void GoodBye();
void WWIV_PostMessage();
void ScanSub();
void RemovePost();
void TitleScan();
void ListUsers();
void Vote();
void ToggleExpert(const std::string& data);
void WWIVVersion();
void JumpEdit();
void BoardEdit();
void ChainEdit();
void ToggleChat();
void ChangeUser();
void DirEdit();
void LoadTextFile();
void EditText();
void EditBulletins();
void ReadAllMail();
void ResetQscan();
void MemoryStatus();
void InitVotes();
void ReadLog();
void ReadNetLog();
void PrintPending();
void PrintStatus();
void TextEdit();
void VotePrint();
void YesterdaysLog();
void ZLog();
void ViewNetDataLog();
void UploadPost();
void WhoIsOnline();
void NewMsgsAllConfs();
void MultiEmail();
void NewMsgScanFromHere();
void ValidateScan();
void ChatRoom();
void ClearQScan();
void FastGoodBye();
void NewFilesAllConfs();
void ReadIDZ();
void RemoveNotThere();
void UploadAllDirs();
void UploadCurDir();
void RenameFiles();
void MoveFiles();
void SortDirs();
void ReverseSort();
void AllowEdit();
void UploadFilesBBS();
void UpDirConf();
void UpDir();
void DownDirConf();
void DownDir();
void ListUsersDL();
void PrintDSZLog();
void PrintDevices();
void ViewArchive();
void BatchMenu();
void Download();
void FindDescription();
void JumpDirConf();
void ConfigFileList();
void ListFiles();
void NewFileScan();
void RemoveFiles();
void SearchAllFiles();
void XferDefaults();
void Upload();
void YourInfoDL();
void UploadToSysop();
void GuestApply();
void AttachFile();
bool GuestCheck();
void LogOffCmd();
void SetSubNumber(const MenuContext& context);
void SetDirNumber(const MenuContext& context);


}

#endif
