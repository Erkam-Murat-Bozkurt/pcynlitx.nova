
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

     this->construct_build_system = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\build_system_generator.png"),wxBITMAP_TYPE_PNG);

     this->open_tree_view = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\open_folder_icon.png"),wxBITMAP_TYPE_PNG);

     this->build_executable = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\build_executable.png"),wxBITMAP_TYPE_PNG);

     this->Select_Project_File = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\file_selection_icon.png"),wxBITMAP_TYPE_PNG);

     this->print_descriptions = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\zoom.png"),wxBITMAP_TYPE_PNG);

     this->open_settings = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\description_enter.png"),wxBITMAP_TYPE_PNG);

     this->open_help_menu = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\help.png"),wxBITMAP_TYPE_PNG);

     this->close = new wxBitmap(wxT("C:\\Program Files\\Pcynlitx\\icons\\close.png"),wxBITMAP_TYPE_PNG);


     this->toolBar = new wxAuiToolBar(Frame_Pointer,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxAUI_TB_PLAIN_BACKGROUND);

     this->Art_Pointer = new MyAuiTBArt();

     this->toolBar->SetBackgroundColour(wxColour(50,50,60,0xff));

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

     this->toolBar->AddTool(ID_EXIT,wxT(""),*this->close,wxT(""));

     this->toolBar->AddTool(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,wxT(""),*this->construct_build_system,wxT(""));

     this->toolBar->AddTool(ID_OPEN_SETTINGS,wxT(""),*this->open_settings,wxT(""));

     this->toolBar->AddTool(ID_OPEN_TREE_WIEW,wxT(""),*this->open_tree_view,wxT(""));

     this->toolBar->AddTool(ID_SELECT_PROJECT_FILE,wxT(""),*this->Select_Project_File,wxT(""));


     //this->toolBar->AddSpacer(10);

     //this->toolBar->AddTool(ID_PRINT_DESCRIPTIONS,wxT(""),*this->print_descriptions,wxT(""));


     this->toolBar->SetMargins(6,6,0,0);

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
