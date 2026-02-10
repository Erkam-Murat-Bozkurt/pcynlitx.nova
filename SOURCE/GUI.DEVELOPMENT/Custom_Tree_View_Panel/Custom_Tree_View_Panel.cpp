
/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Custom_Tree_View_Panel.h"


BEGIN_EVENT_TABLE(Custom_Tree_View_Panel,wxPanel)
   EVT_DATAVIEW_ITEM_ACTIVATED(wxID_ANY,Custom_Tree_View_Panel::FileSelect)
   EVT_DATAVIEW_ITEM_START_EDITING(wxID_ANY,Custom_Tree_View_Panel::FileNameEdit)
END_EVENT_TABLE()

Custom_Tree_View_Panel::Custom_Tree_View_Panel(wxFrame * frame,

     wxWindowID id, const wxPoint &pos, const wxSize &size,

     wxAuiManager * Interface_Manager,

     wxFont Default_Font, int tabctrl_hight, wxColor theme_clr)

  : wxPanel(frame,id,pos,size)

{
     this->background = wxColour(240,240,240);

     this->Interface_Manager_Pointer = Interface_Manager;

     this->windows_detach_condition = true;

     this->tab_ctrl_hight = tabctrl_hight;

     //this->close_button_construction_status = false;

     this->Topbar_MinSize = wxSize(400,this->tab_ctrl_hight);

     this->SetDoubleBuffered(true);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_Tree_View_Panel::OnPaint,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_LEFT_UP,&Custom_Tree_View_Panel::mouseReleased,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_Tree_View_Panel::Size_Event,this,wxID_ANY);

     this->SetSize(size);

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();

     this->Refresh();

     this->Show(false);


     this->dir_ctrl = new wxDir;


     this->tab_ctrl_hight = tabctrl_hight +1;

     this->Frame_Pointer = frame;

     this->Memory_Delete_Condition = false;

     this->panel_open_status = false;


     this->File_List_Widget_Shape.TopDockable(false);

     this->File_List_Widget_Shape.LeftDockable(true);

     this->File_List_Widget_Shape.Left();

     this->File_List_Widget_Shape.Resizable(true);

     this->File_List_Widget_Shape.MinSize(size);

     this->File_List_Widget_Shape.Show(true);

     this->File_List_Widget_Shape.CloseButton(false);

     this->File_List_Widget_Shape.Dock();

     this->File_List_Widget_Shape.Row(1);

     this->File_List_Widget_Shape.dock_proportion = 0.3;

     this->SetMinSize(size);


     int tree_size_y = size.y - 2*this->tab_ctrl_hight -60;

     this->Tree_Control_Size = wxSize(size.x,tree_size_y);


     this->tree_control = new wxDataViewTreeCtrl(this, wxID_ANY,wxDefaultPosition,

                             this->Tree_Control_Size,wxDV_NO_HEADER | wxDV_VARIABLE_LINE_HEIGHT  );


     std::string face_name = "Calibri"; 


     this->Directory_List_Font = new wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,wxString(face_name));

     this->tree_control->SetFont(*this->Directory_List_Font);


     wxPoint tree_control_current_position = this->tree_control->GetPosition();

     this->Tree_Control_Position = wxPoint(tree_control_current_position.x,

                                   tree_control_current_position.y + this->tab_ctrl_hight );


     this->tree_control->SetPosition(this->Tree_Control_Position);

     this->tree_control->SetBackgroundColour(wxColour(250,250,250));


     wxSize Tab_Bar_size = wxSize(this->GetSize().x,this->tab_ctrl_hight);

     //this->Top_Bar_Window = new Custom_Window(this,wxPoint(0,0),Tab_Bar_size,wxColour(240,240,240));

     //this->Top_Bar_Window->Receive_Tab_ctrl_Hight(this->tab_ctrl_hight);

     //this->Top_Bar_Window->Show(false);



     // TITLE WINDOW SETTINGS START


     this->Title_Window =  new Custom_Window(this,wxPoint(0,this->tab_ctrl_hight),
     
                           wxSize(Tab_Bar_size.x,Tab_Bar_size.y-5),wxColour(190,190,200,0xff));

     this->Title_Window->Receive_Tab_ctrl_Hight(this->tab_ctrl_hight);

     this->Title_Window->Show(false);



     wxStaticText * text = new wxStaticText(this->Title_Window ,wxID_ANY,wxT("FILE EXPLORER   "));

     wxPoint title_pos =text->GetPosition();

     wxSize text_size = text->GetSize();

     int text_y_pos = title_pos.y + (this->tab_ctrl_hight - text_size.GetY())/2;

     text->SetPosition(wxPoint(title_pos.x+25,text_y_pos));




     wxFont textFont = text->GetFont();

     textFont.SetPointSize(9);

     textFont.SetFaceName(wxT("Segoe UI Semibold"));

     text->SetFont(textFont);

     text->SetForegroundColour(wxColour(60,60,60));

     // TITLE WINDOW SETTINGS END


     this->trew_View_notebook = new Custom_Notebook(

                       nullptr,this,this->Interface_Manager_Pointer,

                       textFont,wxSize(Tab_Bar_size.x,250),theme_clr);

     
     this->trew_View_notebook->SetSize(this->trew_View_notebook->FromDIP(wxSize(Tab_Bar_size.x,250)));

     this->trew_View_notebook->SetMinSize(this->trew_View_notebook->FromDIP(wxSize(Tab_Bar_size.x,250)));

     this->trew_View_notebook->SetAutoLayout(true);

     Custom_TextCtrl * Text_Ctrl = new Custom_TextCtrl(this->trew_View_notebook,wxID_ANY,wxDefaultPosition,

                                                       wxSize(Tab_Bar_size.x,250),wxString(""));
 

     this->trew_View_notebook->AddPage(Text_Ctrl,wxT(" Start  "),true);


     Custom_TextCtrl * Text_Ctrl_Next = new Custom_TextCtrl(this->trew_View_notebook,wxID_ANY,wxDefaultPosition,

                                                       wxSize(Tab_Bar_size.x,250),wxString(""));
 

     this->trew_View_notebook->AddPage(Text_Ctrl_Next,wxT(" Next  "),false);

     //this->trew_View_notebook->OpenIntroPage();


     int bottom_win_y = this->Tree_Control_Position.y + this->tree_control->GetSize().GetY();


     this->Bottom_Window =  new Custom_Window(this,wxPoint(0,bottom_win_y+3),
     
                           wxSize(Tab_Bar_size.x,65),wxColour(240,240,240,0xff));


     //this->bottom_window = new wxWindow(this, wxID_ANY,wxDefaultPosition,wxSize(this->GetSize().GetX(),60));

     this->Start_Button  = new wxButton(this->Bottom_Window,ID_OPEN_POPUP_MENU,wxT("START"),wxDefaultPosition, wxSize(120,50));
     
     //this->bottom_window->SetBackgroundColour(wxColour(240,240,240));



     wxFont button_font = this->Start_Button->GetFont();

     button_font.SetFaceName(wxT("Segoe UI"));

     this->Start_Button->SetFont(button_font);

     wxPoint position = this->Start_Button->GetPosition() ;

     this->Start_Button->SetPosition(wxPoint(position.x+16,position.y));



     int text_x = position.x + 155;

     int text_y = position.y + 14;

     this->start_text   = new wxStaticText(this->Bottom_Window ,
     
                    wxID_ANY,wxT("PCYNLITX START MENU"),wxPoint(text_x,text_y),wxSize(200,50));

     this->start_text->Show(true);

     this->start_text->SetForegroundColour(wxColour(25,25,35));

     this->start_text->SetFont(button_font);



     this->Bottom_Window->Show(true);

     this->Start_Button->Show(true);



     this->Load_Menu_Items();


     // Default wxPanel position is TopLeft corner of the panel

     /*

     wxPoint Panel_Top_Right_Position = this->GetRect().GetTopLeft();

     int close_button_x = Panel_Top_Right_Position.x -35;

     int close_button_y = (this->tab_ctrl_hight - 20) / 2 -3;

     this->close_button_position = wxPoint(close_button_x,close_button_y);



     //this->close_button = new Custom_Close_Button(this->Top_Bar_Window,

                          this->close_button_position,wxSize(25,25));

 

     this->close_button->Show(false);

     */

     //this->close_button_construction_status = true;

     //this->Top_Bar_Window->Receive_Button_ID(this->close_button->GetId());

     this->tree_control->Fit();

     this->tree_control->SetAutoLayout(true);

     this->tree_control->Show(false);

     this->Folder_Lister = new Project_Folder_Lister(this->tree_control);

     this->Initialize_Sizer();

     this->windows_detach_condition = false;

     this->Interface_Manager_Pointer->AddPane(this,this->File_List_Widget_Shape);


     //this->Top_Bar_Window->Show(true);

     this->Title_Window->Show(true);

     //this->close_button->Show(true);

     this->tree_control->Show(true);

     this->Bottom_Window->Show(true);

     this->Show(false);


     this->PostSizeEvent();
}


Custom_Tree_View_Panel::~Custom_Tree_View_Panel()
{
    if(!this->windows_detach_condition)
    {
        this->windows_detach_condition = true;

        this->Detach_Windows_From_Sizer();
    }

    if(!this->Memory_Delete_Condition)
    {
       this->Memory_Delete_Condition = true;

       delete this->Folder_Lister;
    }
}


void Custom_Tree_View_Panel::Load_Menu_Items(){

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


     this->Info_Icon_Bmp = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("LOGO_SMALL"));


     wxIcon Info_icon;

     Info_icon.CopyFromBitmap(*this->Info_Icon_Bmp);

     wxMenuItem * info_item = new wxMenuItem(this->Info_Menu,ID_SHOW_HELP_MENU,"&PCYNLITX VERSION 2.0"," ",wxITEM_NORMAL);

     info_item->SetBitmap(Info_icon);

     this->Main_Menu->Append(info_item);


     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->Append(wxID_NONE,"&                           "," ",wxITEM_SEPARATOR);

     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);

     this->Main_Menu->Append(wxID_NONE,"&EDITOR SETTINGS","",wxITEM_NORMAL);

     this->Main_Menu->AppendSubMenu(this->File_Menu ,"&File Menu                   ","");

     this->Main_Menu->AppendSubMenu(this->Edit_Menu,"&Editor Menu (Editor Options)"," ");

     this->Main_Menu->AppendSubMenu(this->Help_Menu,"&Help Menu                   ","");

     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);


     this->Main_Menu->Append(wxID_NONE,"&BUILD SYSTEM GENERATORS","",wxITEM_NORMAL);

     this->Main_Menu->AppendSubMenu(this->Project_Management,"&Project Management          ","");

     this->Main_Menu->AppendSubMenu(this->CMAKE_Menu ,"&CMAKE list file generator         ","");

     this->Main_Menu->Append(wxID_NONE,"&                           ","",wxITEM_NORMAL);



     this->Main_Menu->Append(wxID_NONE,"&PACKAGE GENERATORS","",wxITEM_NORMAL);

     this->Main_Menu->AppendSubMenu(this->Linux_Debian_Package_Generator ,"&Linux Debian Package Generator     ","");

     this->Main_Menu->AppendSubMenu(this->Linux_RPM_Package_Generator ,   "&Linux RPM Package Generator        ","");

     this->Main_Menu->AppendSubMenu(this->Windows_Package_Generator ,     "&Windows Package Generator          ","");

     this->Main_Menu->Append(wxID_NONE,"&                           ","");



     this->Save_Icon_Small = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("SAVE_ICON_SMALL"));

     wxIcon save_icon;

     save_icon.CopyFromBitmap(*this->Save_Icon_Small);


     wxMenuItem * save_item = new wxMenuItem(this->File_Menu,ID_FILE_SAVE,"&Save"," ",wxITEM_NORMAL);

     save_item->SetBitmap(save_icon);

     this->File_Menu->Append(save_item);

     

     wxMenuItem * save_as_item = new wxMenuItem(this->File_Menu,ID_SAVE_AS,"&Save as"," ",wxITEM_NORMAL);

     save_as_item->SetBitmap(save_icon);

     this->File_Menu->Append(save_as_item);

     this->File_Menu->Append(ID_OPEN_FILE,"&Open file","",wxITEM_NORMAL);

     this->File_Menu->Append(ID_NEW_FILE,"&Create new file as","",wxITEM_NORMAL);

     this->File_Menu->Append(ID_OPEN_TREE_WIEW,"&Open Folder","",wxITEM_NORMAL);

     this->exit_icon_bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("EXIT_ICON_SMALL"));

     wxIcon exit_icon;

     exit_icon.CopyFromBitmap(*this->exit_icon_bitmap);

     wxMenuItem * exit_item = new wxMenuItem(this->File_Menu,ID_EXIT,"&EXIT"," ",wxITEM_NORMAL);

     exit_item->SetBitmap(exit_icon);

     this->File_Menu->Append(exit_item);

     this->File_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);





     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"&PROJECT FILE OPERATIONS "," ",wxITEM_NORMAL);

     this->Project_Management->Append(ID_OPEN_EMPTY_PROJECT_FILE,"Construct empty project file","",wxITEM_NORMAL);

     this->Project_Management->Append(ID_SHOW_PROJECT_FILE,"Show Project File","",wxITEM_NORMAL);

     this->project_file_selection_bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("FILE_SEL_ICON_SMALL"));

     wxIcon project_file_selection_icon;

     project_file_selection_icon.CopyFromBitmap(*this->project_file_selection_bitmap);

     wxMenuItem * project_file_seletion_item = new wxMenuItem(this->Project_Management,ID_SELECT_PROJECT_FILE,"&Select project file"," ",wxITEM_NORMAL);

     project_file_seletion_item->SetBitmap(project_file_selection_icon);

     this->Project_Management->Append(project_file_seletion_item);



     this->Project_Management->Append(ID_PRINT_DESCRIPTIONS, "&Print project descriptions"," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,"&              "," ",wxITEM_SEPARATOR);


     this->Project_Management->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);

     this->Project_Management->Append(wxID_NONE,                "&BUILD SYSTEM OPERATIONS "," ",wxITEM_NORMAL);


     this->build_icon_bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("BUILD_ICON_SMALL"));

     wxIcon build_icon;

     build_icon.CopyFromBitmap(*this->build_icon_bitmap);


     wxMenuItem * build_item = new wxMenuItem(this->Project_Management,ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,"&Build system initializer"," ",wxITEM_NORMAL);

     build_item->SetBitmap(build_icon);

     this->Project_Management->Append(build_item);


     this->run_build_script_icon_bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("OPEN_TERMINAL_SMALL"));

     

     wxIcon run_build_script_icon;

     run_build_script_icon.CopyFromBitmap(*this->run_build_script_icon_bitmap);



     wxMenuItem * run_build_script_item = new wxMenuItem(this->Project_Management,ID_RUN_PROJECT_SCRIPT,"&Run project build script"," ",wxITEM_NORMAL);

     run_build_script_item->SetBitmap(run_build_script_icon);

     this->Project_Management->Append(run_build_script_item);


     
     this->dependency_icon_bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("DEP_ICON_SMALL"));

     wxIcon dependency_icon;

     dependency_icon.CopyFromBitmap(*this->dependency_icon_bitmap);



     wxMenuItem * dependency_item = new wxMenuItem(this->Project_Management,ID_DETERMINE_SOURCE_FILE_DEPENDENCIES,"&Determine dependencies"," ",wxITEM_NORMAL);

     dependency_item->SetBitmap(dependency_icon);

     this->Project_Management->Append(dependency_item);


     this->Project_Management->Append(ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR, "&Make file constructor"," ",wxITEM_NORMAL);

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



     this->CMAKE_Menu->Append(ID_RUN_BUILD_SYSTEM_CONSTRUCTOR,"&Construct CMAKE Build System");

     this->CMAKE_Menu->Append(ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR,"&Construct CMAKE Target");


     this->Help_Menu->Append(ID_OPEN_INTROPAGE,"&Intro Page","",wxITEM_NORMAL);

     this->Help_Menu->Append(ID_SHOW_HELP_MENU,"&Developer","",wxITEM_NORMAL);

     this->Help_Menu->Append(ID_SHOW_DOCUMENTS,"&Documents","",wxITEM_NORMAL);

     this->Help_Menu->Append(wxID_ABOUT,"&Version 1.0","",wxITEM_NORMAL);

     this->Help_Menu->Append(wxID_NONE,"& "," ",wxITEM_NORMAL);


}


void Custom_Tree_View_Panel::Size_Event(wxSizeEvent & event)
{
     event.Skip(true);

     this->PaintNow();
}

void Custom_Tree_View_Panel::mouseReleased(wxMouseEvent & event)
{
     event.Skip(false);

     event.StopPropagation();

     /*

     if(this->close_button->pressedCloseButton){

        this->Close_Directory_Pane();

        this->close_button->pressedCloseButton = false;
     }

     */
}

void Custom_Tree_View_Panel::Initialize_Sizer()
{
     this->panel_sizer = new wxBoxSizer(wxVERTICAL);

     this->panel_sizer->Add(this->trew_View_notebook,0,  wxEXPAND  | wxLEFT | wxRIGHT | wxBOTTOM,16);

     this->panel_sizer->Add(this->Title_Window,0,  wxEXPAND  | wxLEFT | wxRIGHT,16);

     this->panel_sizer->Add(this->tree_control,1,  wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,16);

     this->panel_sizer->Add(this->Bottom_Window,0, wxEXPAND | wxALL,0);


     this->panel_sizer->Layout();

     this->windows_detach_condition = false;

     this->SetSizer(this->panel_sizer);

     this->panel_sizer->SetSizeHints(this);

     this->Fit();

     this->SetAutoLayout(true);

}

void Custom_Tree_View_Panel::Detach_Windows_From_Sizer()
{
     //this->panel_sizer->Detach(this->Top_Bar_Window);

     this->panel_sizer->Detach(this->Title_Window);

     this->panel_sizer->Detach(this->tree_control);

     this->windows_detach_condition = true;
}

void Custom_Tree_View_Panel::Receive_Topbar_MinSize(wxSize size)
{
     this->Topbar_MinSize = size;
}

void Custom_Tree_View_Panel::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth()+10,rect.GetHeight()+10);
}


void Custom_Tree_View_Panel::FileSelect(wxDataViewEvent & event)
{
     event.Skip(true);

     event.StopPropagation();

     wxDataViewItem Item = this->tree_control->GetSelection();

     wxString Path = this->GetItemPath(Item);

     if(this->dir_ctrl->Exists(Path)){

        if(this->GetTreeCtrl()->IsExpanded(Item)){

           this->GetTreeCtrl()->Collapse(Item);
        }
        else{

             this->GetTreeCtrl()->Expand(Item);
        }
     }
     else{

            this->Notebook_Ptr->Open_File(Path);
     }
}



void Custom_Tree_View_Panel::FileNameEdit(wxDataViewEvent & event)
{
     event.Veto();

}




void Custom_Tree_View_Panel::PaintNow()
{
     wxClientDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}

void Custom_Tree_View_Panel::OnPaint(wxPaintEvent & event)
{
     event.Skip(true);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);

     /*

     if(this->close_button_construction_status){

        this->close_button->paintNow();
     }
     */

     //if(this->Get_Panel_Open_Status()){

        //this->Top_Bar_Window->paintNow();

        this->Title_Window->paintNow();

        this->Bottom_Window->paintNow();
     //}
};

void Custom_Tree_View_Panel::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         delete this->Folder_Lister;

         //delete this->Top_Bar_Window;

         this->tree_control->Destroy();
     }
}

void Custom_Tree_View_Panel::Load_Project_Directory(wxString Folder){

     /*
     wxBitmap * save_bmp

      = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("SAVE_SUCCESS_ICON"));


     Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,wxString("Message"),
            
     wxT("STATUS:\n"),wxID_ANY,wxT("status"),*save_bmp);

     dial->ShowModal();

     */

     this->Folder_Lister->RemoveProjectDirectory();

     this->Folder_Lister->Load_Project_Directory(Folder);

     this->Folder_Lister->Expand_Root();


     //this->Top_Bar_Window->Update();

     //this->Title_Window->Update();

     //this->close_button->Update();

     //this->Bottom_Window->Update();



     /*
     for(int i=0;i<5;i++){

         wxYield();

         //this->Top_Bar_Window->Update();

         this->Title_Window->Update();

         //this->close_button->Update();

         this->Bottom_Window->Update();

         this->PostSizeEvent();

     }

     */

     //this->Show(true);

     //this->close_button->pressedCloseButton = false;

     /*
     if(!this->panel_open_status)
     {
        this->panel_open_status = true;
     }
     
     */

     //this->Interface_Manager_Pointer->Update();

}


void Custom_Tree_View_Panel::Expand_Path(wxString path){

     this->Folder_Lister->Expand_Path(path);
}



void Custom_Tree_View_Panel::Close_Directory_Pane()
{
     this->Folder_Lister->RemoveProjectDirectory();

     if(this->panel_open_status)
     {
        this->tree_control->DeleteAllItems();

        this->Show(false);  // Directory_List_Panel

        this->Interface_Manager_Pointer->DetachPane(this);

        this->Interface_Manager_Pointer->Update();

        this->panel_open_status = false;
    }
}


void Custom_Tree_View_Panel::Expand_Selected_Item(){

     this->Folder_Lister->Expand_Selected_Item();
}

int Custom_Tree_View_Panel::GetTotalItemNum(wxString Folder){

    return this->Folder_Lister->GetTotalItemNum(Folder);
}


void Custom_Tree_View_Panel::Set_Font(wxFont Font){

      this->tree_control->SetFont(Font);
}

wxDataViewTreeCtrl * Custom_Tree_View_Panel::GetTreeCtrl(){

     return this->tree_control;
}

wxString Custom_Tree_View_Panel::GetItemPath(wxDataViewItem item_number){

         return this->Folder_Lister->GetItemPath(item_number);
}

void Custom_Tree_View_Panel::RemoveProjectDirectory(){

     this->Folder_Lister->RemoveProjectDirectory();
}

bool Custom_Tree_View_Panel::Get_Panel_Open_Status(){

     return this->panel_open_status;
}
