
#ifndef EVENT_TABLE_HEADER_H
#define EVENT_TABLE_HEADER_H

#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
  EVT_MENU(ID_INPUT_GIT_REPO_LOCATION,MainFrame::Enter_Git_Repo_Location)
  EVT_MENU(ID_INPUT_MAIN_FILE_NAME,MainFrame::Enter_Main_File_Name)
  EVT_MENU(ID_OPEN_EMPTY_PROJECT_FILE,MainFrame::Open_Empty_Project_File)
  EVT_MENU(ID_SELECT_PROJECT_FILE,MainFrame::Select_Project_File)
  EVT_MENU(ID_SHOW_PROJECT_FILE,MainFrame::Show_Project_File)
  EVT_MENU(ID_OPEN_INTROPAGE,MainFrame::Open_Intro_Page)
  EVT_MENU(ID_SHOW_AUTOR_INFO,MainFrame::Show_Author)
  EVT_MENU(ID_INPUT_HEADER_FILE_LOCATION,MainFrame::Enter_Header_File_Location)
  EVT_MENU(ID_INPUT_SOURCE_FILE_LOCATION,MainFrame::Enter_Source_File_Location)
  EVT_MENU(ID_INPUT_LIBRARY_LOCATION,MainFrame::Enter_Library_Location)
  EVT_MENU(ID_INPUT_LIBRARY_NAME,MainFrame::Enter_Library_Name)
  EVT_MENU(ID_INPUT_CONSTRUCTION_POINT,MainFrame::Enter_Warehouse_Location)
  EVT_MENU(ID_INPUT_EXE_FILE_NAME,MainFrame::Enter_Exe_File_Name)
  EVT_MENU(ID_INPUT_OPTIONS,MainFrame::Enter_Options)
  EVT_MENU(ID_INPUT_C_STANDART,MainFrame::Enter_Standard)
  EVT_AUI_PANE_CLOSE(MainFrame::Close_Directory_Pane)
  EVT_MENU(ID_SHOW_PROJECT_WAREHOUSE,MainFrame::DirectoryOpen)
  EVT_MENU(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,MainFrame::Start_Build_System_Construction)
  EVT_END_PROCESS(wxID_ANY,MainFrame::Process_End)
  EVT_PAINT(MainFrame::OnPaint)
END_EVENT_TABLE()

#endif /* EVENT_TABLE_HEADER_H */
