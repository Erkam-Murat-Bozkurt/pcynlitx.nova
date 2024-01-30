


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

#include "Dependency_Tree_Printer.hpp"


BEGIN_EVENT_TABLE(Dependency_Tree_Printer,wxFrame)
    EVT_BUTTON(ID_CLOSE_DEPENDENCY_WINDOW,Dependency_Tree_Printer::CloseWindow)
END_EVENT_TABLE()

Dependency_Tree_Printer::Dependency_Tree_Printer(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)

{
     this->background = wxColour(240,240,240);

     this->SetDoubleBuffered(true);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_PAINT,&Dependency_Tree_Printer::OnPaint,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Dependency_Tree_Printer::Size_Event,this,wxID_ANY);

     this->SetSize(parent->GetClientSize());

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();

     this->Refresh();

     this->Show(false);


     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);



     this->Memory_Delete_Condition = false;


     this->tree_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,620));


     this->tree_control = new Custom_wxTreeCtrl(this->tree_panel, wxID_ANY,wxDefaultPosition,

                             wxDefaultSize, wxTR_DEFAULT_STYLE | wxTR_ROW_LINES );

     //this->close_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,70));



     this->CloseButton = new wxButton(this,ID_CLOSE_DEPENDENCY_WINDOW,wxT("CLOSE"),
     
                             wxDefaultPosition, wxSize(100, 50));


     //this->tree_control->AlwaysShowScrollbars (true,true);

     //std::string face_name = "Calibri"; 




     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->tree_panel,1,wxEXPAND | wxALL,5);

     this->ctrl_box->Layout();



     this->close_button_sizer = new wxBoxSizer(wxVERTICAL);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Add(this->CloseButton,0, wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxALL,15);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Layout();



     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1,    wxEXPAND | wxTOP    |  wxALL,5);

     this->frame_box->Add(this->close_button_sizer,0,wxEXPAND | wxBOTTOM  | wxALL,5);

     this->frame_box->Layout();

     

     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);

     this->frame_box->Fit(this);



     this->tree_panel->SetSize(this->tree_panel->GetClientSize());

     //this->close_panel->SetSize(this->close_panel->GetClientSize());



     //this->tree_panel->Show(true);

     this->tree_control->Show(true);


     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->SetTitle(title);

     this->Show(true);

     this->Update();


     //this->Folder_Lister = new Project_Folder_Lister(this->tree_control);
}

Dependency_Tree_Printer::~Dependency_Tree_Printer()
{
    if(!this->Memory_Delete_Condition)
    {
       this->Memory_Delete_Condition = true;

       delete this->Folder_Lister;
    }
}

void Dependency_Tree_Printer::Size_Event(wxSizeEvent & event)
{
     event.Skip(true);

     this->PaintNow();
}


/*
void Dependency_Tree_Printer::Initialize_Sizer()
{
     this->tree_control_sizer = new wxBoxSizer(wxVERTICAL);

     this->tree_control_sizer->Add(this->tree_panel,1, wxALL,10);

     this->tree_panel->SetSizer(this->tree_control_sizer);

     this->tree_control_sizer->SetSizeHints(this->tree_panel);

     this->tree_panel->Fit();

     this->tree_panel->SetAutoLayout(true);
}

*/


void Dependency_Tree_Printer::CloseWindow(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_DEPENDENCY_WINDOW){

        this->Destroy();
     }
}

void Dependency_Tree_Printer::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(),rect.GetHeight());
}

void Dependency_Tree_Printer::PaintNow()
{
     wxClientDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}

void Dependency_Tree_Printer::OnPaint(wxPaintEvent& event)
{
     event.Skip(true);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
};

void Dependency_Tree_Printer::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         delete this->Folder_Lister;

         this->tree_control->Destroy();
     }
}

void Dependency_Tree_Printer::Load_Project_Directory(wxString Folder){

     this->Folder_Lister->RemoveProjectDirectory();

     this->Folder_Lister->Load_Project_Directory(Folder);


     this->tree_control->Show(true);

     this->Show(true);

     this->Refresh();
}



int Dependency_Tree_Printer::GetTotalItemNum(wxString Folder){

    return this->Folder_Lister->GetTotalItemNum(Folder);
}


void Dependency_Tree_Printer::Set_Font(wxFont Font){

      this->tree_control->SetFont(Font);
}

Custom_wxTreeCtrl * Dependency_Tree_Printer::GetTreeCtrl(){

     return this->tree_control;
}

wxString Dependency_Tree_Printer::GetItemPath(wxTreeItemId item_number){

     return this->Folder_Lister->GetItemPath(item_number);
}
