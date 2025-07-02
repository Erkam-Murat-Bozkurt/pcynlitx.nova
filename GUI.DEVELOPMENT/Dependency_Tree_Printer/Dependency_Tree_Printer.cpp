

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


#include "Dependency_Tree_Printer.hpp"


BEGIN_EVENT_TABLE(Dependency_Tree_Printer,wxFrame)
    EVT_BUTTON(ID_CLOSE_DEPENDENCY_WINDOW,Dependency_Tree_Printer::Close_Tree_Window)
    EVT_BUTTON(ID_CLOSE_DEPENDECY_TEXT_WINDOW,Dependency_Tree_Printer::Close_Process_Window)
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

     this->SetSize(this->GetClientSize());

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();

     this->Refresh();

     this->Show(false);


     wxIcon Frame_Icon(wxT("C:\\Program Files\\Pcynlitx\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->Memory_Delete_Condition = false;
}






Dependency_Tree_Printer::~Dependency_Tree_Printer()
{
    if(!this->Memory_Delete_Condition)
    {
       this->Memory_Delete_Condition = true;

    }
}

void Dependency_Tree_Printer::Size_Event(wxSizeEvent & event)
{
     event.Skip(true);

     this->PaintNow();
}


void Dependency_Tree_Printer::Construct_Tree_Panel(wxString title){

     
     this->tree_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,620));


     this->tree_control = new wxDataViewTreeCtrl(this->tree_panel, wxID_ANY,wxDefaultPosition,

                             wxSize(900,590), wxTR_DEFAULT_STYLE | wxTR_ROW_LINES );

     this->CloseButton = new wxButton(this,ID_CLOSE_DEPENDENCY_WINDOW,wxT("CLOSE"),
     
                             wxDefaultPosition, wxSize(100, 50));


     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->tree_panel,1,wxEXPAND | wxALL,5);

     this->ctrl_box->Layout();



     this->close_button_sizer = new wxBoxSizer(wxHORIZONTAL);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Add(this->CloseButton,0, wxEXPAND  | wxALL,15);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Layout();



     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1,    wxEXPAND | wxTOP    |  wxALL,5);

     this->frame_box->Add(this->close_button_sizer,0,wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxBOTTOM  | wxALL,5);

     this->frame_box->Layout();

     

     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);

     this->frame_box->Fit(this);



     this->tree_panel->SetSize(this->tree_panel->GetClientSize());

     this->tree_control->Show(false);



     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->SetTitle(title);

     this->Show(false);

     this->Update();


     std::string face_name = "Calibri"; 

     
     wxFont * tree_font = new wxFont(11,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,wxString(face_name));

     this->tree_control->SetFont(*tree_font);
}



void Dependency_Tree_Printer::Construct_Text_Panel(wxString title, int dialog_size){

     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,-1));

     this->text_ctrl_close_panel     = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,70));

     this->text_ctrl_dialog_panel    = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,30));



     this->text_ctrl_close_button     = new wxButton(this,ID_CLOSE_DEPENDECY_TEXT_WINDOW,wxT("CLOSE"),
     
                             wxDefaultPosition, wxSize(100, 50));


     this->textctrl = new wxTextCtrl(this->text_ctrl_panel,wxID_ANY, wxT(""), 
     
                      wxDefaultPosition, wxSize(900,550), wxTE_MULTILINE | wxTE_RICH);


     this->textctrl->SetVirtualSize(wxSize(1000,10000));

     this->textctrl->FitInside();


     this->dialog = new wxGauge(this->text_ctrl_dialog_panel,wxID_ANY,dialog_size,
     
                    wxDefaultPosition,wxSize(900,30),wxGA_HORIZONTAL | wxGA_SMOOTH );



     this->dialog_box = new wxBoxSizer(wxHORIZONTAL);

     this->dialog_box->Add(this->text_ctrl_dialog_panel,1,wxEXPAND | wxALL,5);
       
     this->dialog_box->Layout();





     this->text_ctrl_sizer = new wxBoxSizer(wxHORIZONTAL);

     this->text_ctrl_sizer->Add(this->text_ctrl_panel,1,wxEXPAND  | wxALL,5);

     this->text_ctrl_sizer->Layout();



     this->text_ctrl_close_button_sizer = new wxBoxSizer(wxVERTICAL);

     this->text_ctrl_close_button_sizer->AddStretchSpacer();

     this->text_ctrl_close_button_sizer->Add(this->text_ctrl_close_button,0, 
     
               wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxALL,15);

     this->text_ctrl_close_button_sizer->AddStretchSpacer();

     this->text_ctrl_close_button_sizer->Layout();

     

     this->text_ctrl_frame_box = new wxBoxSizer(wxVERTICAL);

     this->text_ctrl_frame_box->Add(this->text_ctrl_sizer,1,    wxEXPAND | wxTOP    |  wxALL,5);

     this->text_ctrl_frame_box->Add(this->dialog_box,0,    wxEXPAND | wxTOP    |  wxALL,5);

     this->text_ctrl_frame_box->Add(this->text_ctrl_close_button_sizer,0,   wxEXPAND | wxBOTTOM  | wxALL,5);

     this->text_ctrl_frame_box->Layout();


     this->SetSizer(this->text_ctrl_frame_box);

     this->text_ctrl_frame_box->SetSizeHints(this);

     this->text_ctrl_frame_box->Fit(this);



     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->SetTitle(title);

     this->Show(true);

     this->Update();

}



void Dependency_Tree_Printer::PrintDependencyTree(){

     this->tree_control->Show(true);

     this->Show(true);

     this->Update();

}


void Dependency_Tree_Printer::AppendText_To_TextCtrl(wxString text){

     this->textctrl->AppendText(text);

     this->textctrl->Update();
}



void Dependency_Tree_Printer::Close_Tree_Window(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_DEPENDENCY_WINDOW){

        this->Destroy();
     }
}

void Dependency_Tree_Printer::Close_Process_Window(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_DEPENDECY_TEXT_WINDOW){

        Dependency_Tree_Printer * printer = new Dependency_Tree_Printer(this);

        printer->Construct_Tree_Panel(wxT("Sample"));

        printer->PrintDependencyTree();

        //this->Destroy();
     }
}

void Dependency_Tree_Printer::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(245,245,245));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
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

wxDataViewTreeCtrl * Dependency_Tree_Printer::GetTreeCtrl(){

     return this->tree_control;
}

wxString Dependency_Tree_Printer::GetItemPath(wxDataViewItem item_number){

     return this->Folder_Lister->GetItemPath(item_number);
}

wxGauge * Dependency_Tree_Printer::GetDialogAddress(){

      return this->dialog;
}

wxTextCtrl * Dependency_Tree_Printer::GetTextControl(){

      return this->textctrl;
}