

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#ifndef EVENT_TABLE_HEADER_H
#define EVENT_TABLE_HEADER_H

#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
  EVT_MENU(ID_EXIT,MainFrame::Exit)
  EVT_MENU(ID_OPEN_TERMINAL,MainFrame::OpenTerminal)
  EVT_MENU(ID_OPEN_EMPTY_PROJECT_FILE,MainFrame::Open_Empty_Project_File)
  EVT_MENU(ID_SELECT_PROJECT_FILE,MainFrame::Select_Project_File)
  EVT_MENU(ID_OPEN_INTROPAGE,MainFrame::Open_Intro_Page)
  EVT_MENU(ID_SHOW_HELP_MENU,MainFrame::Show_Help_Menu)

  EVT_MENU(ID_OPEN_TREE_WIEW,MainFrame::DirectoryOpen)
  EVT_MENU(ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR,MainFrame::Single_File_Script_Construction)
  EVT_AUI_PANE_CLOSE(MainFrame::Close_Directory_Pane)
  EVT_MENU(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,MainFrame::Start_Build_System_Construction)
  EVT_MENU(ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR,MainFrame::Advance_Single_File_Script_Construction)
  EVT_MENU(ID_PRINT_DESCRIPTIONS,MainFrame::PrintDescriptions)
  EVT_MENU(ID_DETERMINE_SOURCE_FILE_DEPENDENCIES,MainFrame::Determine_Source_File_Dependencies)
  EVT_MENU(ID_RUN_PROJECT_SCRIPT,MainFrame::Run_Project_Script_On_Terminal)
  EVT_MENU(ID_OPEN_SETTINGS,MainFrame::OpenSettings)
  EVT_PAINT(MainFrame::OnPaint)

END_EVENT_TABLE()

#endif /* EVENT_TABLE_HEADER_H */
