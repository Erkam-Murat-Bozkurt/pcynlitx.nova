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


  this->Launch_Menu = new wxMenu();

  this->Help_Menu   = new wxMenu();

  this->Description_Menu = new wxMenu();

  this->Library_Description_Menu = new wxMenu();

  this->Construction_Menu = new wxMenu();


  this->Help_Menu->Append(ID_OPEN_INTROPAGE,"&Intro Page","",wxITEM_NORMAL);

  this->Help_Menu->Append(ID_SHOW_AUTOR_INFO,"&Developer","",wxITEM_NORMAL);

  this->Help_Menu->Append(wxID_ABOUT,"&Version 1.0","",wxITEM_NORMAL);


  this->Description_Menu->Append(ID_OPEN_EMPTY_PROJECT_FILE,"Construct Empty Project File","",wxITEM_NORMAL);

  this->Description_Menu->Append(ID_SELECT_PROJECT_FILE,"Select Project File","",wxITEM_NORMAL);

  this->Description_Menu->Append(ID_SHOW_PROJECT_FILE,"Show Project File","",wxITEM_NORMAL);



  this->Library_Description_Menu->Append(wxID_NONE,                     "&# MAIN DESCRIPTIONS"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_GIT_REPO_LOCATION,       "&   Enter Git Repo Directory"," ",wxITEM_NORMAL);


  this->Library_Description_Menu->Append(wxID_NONE,                     "&# SOURCE FILE LOCATIONS "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_SOURCE_FILE_LOCATION, "&   Enter Source File Location"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# HEADER FILE LOCATIONS "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_HEADER_FILE_LOCATION, "&   Enter Header File Location"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# LIBRARIY INFORMATION"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_LIBRARY_NAME,         "&   Enter Library File For Linking"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_LIBRARY_LOCATION,"&   Enter Library File Location"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# EXECUTABLE FILE NAME"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_EXE_FILE_NAME,       "&   Enter Executable File Name"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# MAIN FILE NAME"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_MAIN_FILE_NAME,      "&    Enter Main File Name"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,"&                        "," ",wxITEM_SEPARATOR);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# C++ STANDART"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_C_STANDART,           "&   Enter C++ Standart "," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(wxID_NONE,                     "&# OPTIONS"," ",wxITEM_NORMAL);

  this->Library_Description_Menu->Append(ID_INPUT_OPTIONS,           "&   Enter Options "," ",wxITEM_NORMAL);



  this->Construction_Menu->Append(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,      "& Run Build System Initializer"," ",wxITEM_NORMAL);


  this->Menu_Bar = new wxMenuBar();

  this->Menu_Bar->Append(this->Help_Menu,wxT("&Help"));

  this->Menu_Bar->Append(this->Library_Description_Menu,wxT("Project Descriptions"));

  this->Menu_Bar->Append(this->Description_Menu,wxT("Descriptor File Selection"));

  this->Menu_Bar->Append(this->Construction_Menu,wxT("Build System"));

}

Menu_Bar_Options::~Menu_Bar_Options(){

        delete this->Description_Menu;

        delete this->Library_Description_Menu;

        delete this->Construction_Menu;

        delete this->Launch_Menu;

        delete this->Help_Menu;

        delete this->Menu_Bar;
}

wxMenuBar * Menu_Bar_Options::Get_MenuBar(){

    return this->Menu_Bar;
}
