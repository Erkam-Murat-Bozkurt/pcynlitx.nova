/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/


#include "Menu_Bar_Options.h"

Menu_Bar_Options::Menu_Bar_Options(){


  this->File_Menu = new wxMenu();

  this->Help_Menu   = new wxMenu();

  this->Project_Management = new wxMenu();

  this->Library_Description_Menu = new wxMenu();

  this->Edit_Menu = new wxMenu();


  this->Help_Menu->Append(ID_OPEN_INTROPAGE,"&Intro Page","",wxITEM_NORMAL);

  this->Help_Menu->Append(ID_SHOW_AUTOR_INFO,"&Developer","",wxITEM_NORMAL);

  this->Help_Menu->Append(ID_SHOW_DOCUMENTS,"&Documents","",wxITEM_NORMAL);

  this->Help_Menu->Append(wxID_ABOUT,"&Version 1.0","",wxITEM_NORMAL);

  this->Help_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);


  this->File_Menu->Append(ID_FILE_SAVE,"&Save","",wxITEM_NORMAL);

  this->File_Menu->Append(ID_SAVE_AS,"Save As","",wxITEM_NORMAL);

  this->File_Menu->Append(ID_OPEN_FILE,"&Open file","",wxITEM_NORMAL);

  this->File_Menu->Append(ID_NEW_FILE,"&Create new file as","",wxITEM_NORMAL);

  this->File_Menu->Append(ID_OPEN_TREE_WIEW,"&Open Folder","",wxITEM_NORMAL);


  this->File_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);


  this->Edit_Menu->Append(ID_INCREASE_FONT_SIZE,"&Increase Font Size","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_DECREASE_FONT_SIZE,"Decrease Font Size",wxT(""),wxITEM_NORMAL);


  this->Edit_Menu->Append(ID_UNDO_CHANGES,"&Undo   Ctrl+Z","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_REDO_CHANGES,"&Redo   Ctrl+Y","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_CLEAR_TEXT,"&Clear Text"," ",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_SET_CURSOR_TYPE_DEFAULT,"&Use Default Cursor","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_CHANGE_CURSOR_TYPE,"&Use System Cursor","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_SET_CARET_LINE_VISIBLE,"&Set Caret Line Visible","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_SET_CARET_LINE_INVISIBLE,"&Set Caret Line Invisible","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_USE_BLOCK_CARET,"&Use Block Caret","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_USE_DEFAULT_CARET,"&Use Default Caret","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_CLEAR_STYLE,"&Clear Styling","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_RELOAD_STYLE,"&Reload Default Style","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_BOLD_STYLE,"&Use Bold Styling","",wxITEM_NORMAL);

  this->Edit_Menu->Append(ID_FONT_CHANGE,"&Change Font","",wxITEM_NORMAL);

  this->Edit_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);





  this->Project_Management->Append(wxID_NONE,                "&PROJECT FILE OPERATIONS "," ",wxITEM_NORMAL);

  this->Project_Management->Append(ID_OPEN_EMPTY_PROJECT_FILE,"Construct empty project file","",wxITEM_NORMAL);


  this->Project_Management->Append(ID_SHOW_PROJECT_FILE,"Show Project File","",wxITEM_NORMAL);


   wxIcon * project_file_selection_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\file_selection_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

   wxMenuItem * project_file_seletion_item = new wxMenuItem(this->Project_Management,ID_SELECT_PROJECT_FILE,"&Select project file"," ",wxITEM_NORMAL);

   project_file_seletion_item->SetBitmap(*project_file_selection_icon);

   this->Project_Management->Append(project_file_seletion_item);



  this->Project_Management->Append(ID_PRINT_DESCRIPTIONS, "&Print project descriptions"," ",wxITEM_NORMAL);

  this->Project_Management->Append(wxID_NONE,"&              "," ",wxITEM_SEPARATOR);




  this->Project_Management->Append(wxID_NONE,                "&BUILD SYSTEM OPERATIONS "," ",wxITEM_NORMAL);

   wxIcon * frame_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\build_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

   wxMenuItem * build_item = new wxMenuItem(this->Project_Management,ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,"&Build system initializer"," ",wxITEM_NORMAL);

   build_item->SetBitmap(*frame_icon);

   this->Project_Management->Append(build_item);



   wxIcon * run_build_script_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\open_terminal_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

   wxMenuItem * run_build_script_item = new wxMenuItem(this->Project_Management,ID_RUN_PROJECT_SCRIPT,"&Run project build script"," ",wxITEM_NORMAL);

   run_build_script_item->SetBitmap(*run_build_script_icon);

   this->Project_Management->Append(run_build_script_item);


  this->Project_Management->Append(ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR, "&Make file constructor"," ",wxITEM_NORMAL);

  this->Project_Management->Append(ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR, "&Advance make file constructor"," ",wxITEM_NORMAL);

  this->Project_Management->Append(ID_DETERMINE_SOURCE_FILE_DEPENDENCIES, "&Determine dependencies"," ",wxITEM_NORMAL);


  this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);


  this->Library_Description_Menu->Append(wxID_NONE,                     "&   MAIN DESCRIPTIONS"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_GIT_REPO_LOCATION,    "&   Enter Git Repo Directory"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_CONSTRUCTION_POINT,   "&   Select Project Warehouse Directory"," ",wxITEM_NORMAL);


  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&   SOURCE FILE LOCATIONS "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_SOURCE_FILE_LOCATION, "&   Enter External Source File Locations"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&   HEADER FILE LOCATIONS "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_HEADER_FILE_LOCATION, "&   Enter External Header File Locations"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&   LIBRARIY INFORMATION"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_LIBRARY_NAME,         "&   Enter Libraries File For Linking"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_LIBRARY_LOCATION,     "&   Enter Library File Location"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&   C++ STANDART"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_C_STANDART,           "&   Enter C++ Standart "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&   OPTIONS"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_OPTIONS,              "&   Enter Options "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&                 "," ",wxITEM_NORMAL);



  this->Menu_Bar = new wxMenuBar();

  this->Menu_Bar->Append(this->File_Menu,wxT("&File"));

  this->Menu_Bar->Append(this->Library_Description_Menu,wxT("Project Descriptions"));

  this->Menu_Bar->Append(this->Project_Management,wxT("Project Management"));

  this->Menu_Bar->Append(this->Edit_Menu,wxT("&Editor Options"));

  this->Menu_Bar->Append(this->Help_Menu,wxT("&About Platform"));

}

Menu_Bar_Options::~Menu_Bar_Options(){

        delete this->Project_Management;

        delete this->Library_Description_Menu;

        delete this->File_Menu;

        delete this->Help_Menu;

        delete this->Menu_Bar;

        delete this->Edit_Menu;
}

wxMenuBar * Menu_Bar_Options::Get_MenuBar(){

    return this->Menu_Bar;
}
