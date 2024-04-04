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

#include "ToolBar_Initializer.h"

ToolBar_Initializer::ToolBar_Initializer(){

}

ToolBar_Initializer::~ToolBar_Initializer(){

      delete this->construct_build_system;

      delete this->open_terminal;

      delete this->file_save;

      delete this->WinDc;

      this->toolBar->Clear();

      this->toolBar->ClearTools();

      this->toolBar->Destroy();
}

void ToolBar_Initializer::Initialize_ToolBar(wxFrame * Frame_Pointer, wxAuiDockArt * Dock_Art_Pointer, wxAuiManager * Interface_Manager){

     this->construct_build_system = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\build_system_generator.png"),wxBITMAP_TYPE_PNG);

     //this->open_terminal = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\open_terminal.png"),wxBITMAP_TYPE_PNG);

     this->open_tree_view = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\open_folder_icon.png"),wxBITMAP_TYPE_PNG);

     this->build_executable = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\build_executable.png"),wxBITMAP_TYPE_PNG);

     this->Select_Project_File = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\file_selection_icon.png"),wxBITMAP_TYPE_PNG);

     this->print_descriptions = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\zoom.png"),wxBITMAP_TYPE_PNG);

     this->open_settings = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\description_enter.png"),wxBITMAP_TYPE_PNG);

     this->open_settings = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\description_enter.png"),wxBITMAP_TYPE_PNG);

     this->open_help_menu = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\help.png"),wxBITMAP_TYPE_PNG);


     this->toolBar = new wxAuiToolBar(Frame_Pointer,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxAUI_TB_PLAIN_BACKGROUND);

     this->Art_Pointer = new MyAuiTBArt();

     this->toolBar->SetBackgroundColour(wxColour(115,115,130,0xff));

     this->toolBar->SetArtProvider(this->Art_Pointer);

     wxAuiPaneInfo ToolBar_Widget_Shape;

     ToolBar_Widget_Shape.CloseButton(false);

     ToolBar_Widget_Shape.LeftDockable(true);

     ToolBar_Widget_Shape.RightDockable(false);

     ToolBar_Widget_Shape.BottomDockable(false);

     ToolBar_Widget_Shape.TopDockable(false);

     ToolBar_Widget_Shape.Movable(false);

     ToolBar_Widget_Shape.Floatable(false);

     ToolBar_Widget_Shape.Left();

     ToolBar_Widget_Shape.Dock();

     ToolBar_Widget_Shape.PaneBorder(true);

     ToolBar_Widget_Shape.DockFixed(true);

     ToolBar_Widget_Shape.Show(true);

     this->WinDc = new wxWindowDC(this->toolBar);

     this->Art_Pointer->DrawPlainBackground(*this->WinDc,this->toolBar,this->toolBar->GetRect());

     this->toolBar->AddTool(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,wxT(""),*this->construct_build_system,wxT(""));

     //this->toolBar->AddTool(ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR,wxT(""),*this->build_executable,wxT(""));

     this->toolBar->AddTool(ID_OPEN_SETTINGS,wxT(""),*this->open_settings,wxT(""));

     this->toolBar->AddTool(ID_OPEN_TREE_WIEW,wxT(""),*this->open_tree_view,wxT(""));

     //this->toolBar->AddTool(ID_OPEN_TERMINAL,wxT(""),*this->open_terminal,wxT(""));

     this->toolBar->AddTool(ID_SELECT_PROJECT_FILE,wxT(""),*this->Select_Project_File,wxT(""));

     this->toolBar->AddTool(ID_PRINT_DESCRIPTIONS,wxT(""),*this->print_descriptions,wxT(""));

     this->toolBar->AddTool(ID_SHOW_HELP_MENU,wxT(""),*this->open_help_menu,wxT(""));

     this->toolBar->SetMargins(3,3,4,4);

     this->toolBar->SetOverflowVisible(false);

     this->toolBar->SetBackgroundStyle(wxBG_STYLE_CUSTOM);

     this->toolBar->SetThemeEnabled(false);

     this->toolBar->RefreshRect(this->toolBar->GetRect(),true);

     this->toolBar->Realize();

     this->toolBar->Show(true);

     Interface_Manager->AddPane(this->toolBar,ToolBar_Widget_Shape);
}

wxAuiToolBar * ToolBar_Initializer::Get_ToolBar_Pointer(){

     return this->toolBar;
}
