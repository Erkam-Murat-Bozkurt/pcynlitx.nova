

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

#include "Custom_wxPanel.h"



Custom_wxPanel::Custom_wxPanel(wxWindow * parent, wxWindowID id,

              const wxPoint &pos, const wxSize &size,

              wxColour background_colour, wxAuiPaneInfo * Pane)

  : wxPanel(parent,id,pos,size)
{
     this->background = background_colour;

     this->Pane_Pointer = Pane;

     this->Memory_Delete_Condition = false;

     this->SetThemeEnabled(false);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetBackgroundColour(wxColour(240,240,240));

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);


     this->panel_sizer = new wxBoxSizer(wxVERTICAL);


     this->bottom_window = new wxWindow(this, wxID_ANY,wxDefaultPosition,wxSize(this->GetSize().GetX(),60));

     this->Start_Button  = new wxButton(this->bottom_window,ID_OPEN_POPUP_MENU,wxT("START"),wxDefaultPosition, wxSize(120,50));
     
     this->bottom_window->SetBackgroundColour(wxColour(240,240,240));

     this->Start_Button->SetForegroundColour(wxColour(70,70, 85));


     wxFont button_font = this->Start_Button->GetFont();

     button_font.SetFaceName(wxT("Segoe UI Semibold"));

     this->Start_Button->SetFont(button_font);

     wxPoint position = this->Start_Button->GetPosition() ;

     int text_x = position.x + 137;

     int text_y = position.y + 14;

     this->start_text   = new wxStaticText(this->bottom_window ,
     
                    wxID_ANY,wxT("NWINIX START MENU"),wxPoint(text_x,text_y),wxSize(200,50));

     this->start_text->Show(true);

     this->start_text->SetForegroundColour(wxColour(80,80,95));

     this->start_text->SetFont(button_font);

     //this->Start_Button->SetForegroundColour(wxColour(50,50,50));


     this->bottom_window->Show(true);

     this->Start_Button->Show(true);




     this->Main_Menu = new wxMenu();

     this->File_Menu = new wxMenu();

     this->Project_Management = new wxMenu();

     this->Edit_Menu  = new wxMenu();

     this->Help_Menu  = new wxMenu();

     this->CMAKE_Menu = new wxMenu();

     this->Info_Menu = new wxMenu();


     this->Linux_Debian_Package_Generator = new wxMenu();

     this->Linux_RPM_Package_Generator = new wxMenu();

     this->Windows_Package_Generator = new wxMenu();



     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);


     wxIcon * Info_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\build_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * info_item = new wxMenuItem(this->Info_Menu,ID_SELECT_PROJECT_FILE,"&NWINIX PLATFORM"," ",wxITEM_NORMAL);

     info_item->SetBitmap(*Info_icon);

     this->Main_Menu->Append(info_item);


     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->Append(wxID_NONE,"&                           "," ",wxITEM_SEPARATOR);

     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->AppendSubMenu(this->File_Menu ,"&File Menu                   ","");

     this->Main_Menu->AppendSubMenu(this->Project_Management,"&Project Management          ","");

     this->Main_Menu->AppendSubMenu(this->Edit_Menu,"&Editor Menu (Editor Options)"," ");

     this->Main_Menu->AppendSubMenu(this->Help_Menu,"&Help Menu                   ","");

     this->Main_Menu->AppendSubMenu(this->CMAKE_Menu ,"&CMAKE list file generator         ","");

     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->Append(wxID_NONE,"&PACKAGE GENERATORS","",wxITEM_NORMAL);

     //this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->AppendSubMenu(this->Linux_Debian_Package_Generator ,"&Linux Debian Package Generator     ","");

     this->Main_Menu->AppendSubMenu(this->Linux_RPM_Package_Generator ,   "&Linux RPM Package Generator        ","");

     this->Main_Menu->AppendSubMenu(this->Windows_Package_Generator ,     "&Windows Package Generator          ","");

     this->Main_Menu->Append(wxID_NONE,"&                           ","");




     wxIcon * save_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\save_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * save_item = new wxMenuItem(this->File_Menu,ID_FILE_SAVE,"&Save"," ",wxITEM_NORMAL);

     save_item->SetBitmap(*save_icon);

     this->File_Menu->Append(save_item);

     wxIcon * save_as_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\save_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * save_as_item = new wxMenuItem(this->File_Menu,ID_SAVE_AS,"&Save as"," ",wxITEM_NORMAL);

     save_as_item->SetBitmap(*save_as_icon);

     this->File_Menu->Append(save_as_item);

     this->File_Menu->Append(ID_OPEN_FILE,"&Open file","",wxITEM_NORMAL);

     this->File_Menu->Append(ID_NEW_FILE,"&Create new file as","",wxITEM_NORMAL);

     this->File_Menu->Append(ID_OPEN_TREE_WIEW,"&Open Folder","",wxITEM_NORMAL);

     wxIcon * exit_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\exit_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * exit_item = new wxMenuItem(this->File_Menu,ID_EXIT,"&EXIT"," ",wxITEM_NORMAL);

     exit_item->SetBitmap(*exit_icon);

     this->File_Menu->Append(exit_item);

     this->File_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);





     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"&PROJECT FILE OPERATIONS "," ",wxITEM_NORMAL);

     this->Project_Management->Append(ID_OPEN_EMPTY_PROJECT_FILE,"Construct empty project file","",wxITEM_NORMAL);

     this->Project_Management->Append(ID_SHOW_PROJECT_FILE,"Show Project File","",wxITEM_NORMAL);

     wxIcon * project_file_selection_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\file_selection_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * project_file_seletion_item = new wxMenuItem(this->Project_Management,ID_SELECT_PROJECT_FILE,"&Select project file"," ",wxITEM_NORMAL);

     project_file_seletion_item->SetBitmap(*project_file_selection_icon);

     this->Project_Management->Append(project_file_seletion_item);



     this->Project_Management->Append(ID_PRINT_DESCRIPTIONS, "&Print project descriptions"," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"&              "," ",wxITEM_SEPARATOR);


     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,                "&BUILD SYSTEM OPERATIONS "," ",wxITEM_NORMAL);

     wxIcon * frame_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\build_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * build_item = new wxMenuItem(this->Project_Management,ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,"&Build system initializer"," ",wxITEM_NORMAL);

     build_item->SetBitmap(*frame_icon);

     this->Project_Management->Append(build_item);



     wxIcon * run_build_script_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\open_terminal_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * run_build_script_item = new wxMenuItem(this->Project_Management,ID_RUN_PROJECT_SCRIPT,"&Run project build script"," ",wxITEM_NORMAL);

     run_build_script_item->SetBitmap(*run_build_script_icon);

     this->Project_Management->Append(run_build_script_item);


     wxIcon * dependency_icon = new wxIcon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\dependecy_icon_small.png"),wxBITMAP_TYPE_PNG,-1,-1);

     wxMenuItem * dependency_item = new wxMenuItem(this->Project_Management,ID_DETERMINE_SOURCE_FILE_DEPENDENCIES,"&Determine dependencies"," ",wxITEM_NORMAL);

     dependency_item->SetBitmap(*dependency_icon);

     this->Project_Management->Append(dependency_item);


     this->Project_Management->Append(ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR, "&Make file constructor"," ",wxITEM_NORMAL);

     this->Project_Management->Append(ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR, "&Advance make file constructor"," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);





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





     this->Help_Menu->Append(ID_OPEN_INTROPAGE,"&Intro Page","",wxITEM_NORMAL);

     this->Help_Menu->Append(ID_SHOW_HELP_MENU,"&Developer","",wxITEM_NORMAL);

     this->Help_Menu->Append(ID_SHOW_DOCUMENTS,"&Documents","",wxITEM_NORMAL);

     this->Help_Menu->Append(wxID_ABOUT,"&Version 1.0","",wxITEM_NORMAL);

     this->Help_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);



     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();

     this->SetAutoLayout(true);

     this->ClearBackground();

     this->PaintNow(this);

     this->Show(true);
}

Custom_wxPanel::~Custom_wxPanel()
{
    if(!this->Memory_Delete_Condition)
    {
        this->Memory_Delete_Condition = true;

        this->panel_sizer->Detach(this->book_manager);
    }
}

void Custom_wxPanel::Initialize_Sizer()
{
     this->panel_sizer->Add(this->book_manager, 1, wxEXPAND | wxRIGHT,10);

     this->panel_sizer->Add(this->bottom_window,0, wxALIGN_LEFT | wxFIXED_MINSIZE | wxEXPAND | wxTOP | wxLEFT,5);

     this->SetSizer(this->panel_sizer);

     this->panel_sizer->SetSizeHints(this);

     this->panel_sizer->ShowItems(true);

     this->Fit();

     this->SetAutoLayout(true);
}

void Custom_wxPanel::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-2, rect.GetY()-2, rect.GetWidth()+2,rect.GetHeight()+2);
}

void Custom_wxPanel::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+1,wnd->GetSize().y+1);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}

