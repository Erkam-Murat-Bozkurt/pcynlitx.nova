



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


#include "Custom_Progress_Dialog.hpp"


BEGIN_EVENT_TABLE(Custom_Progress_Dialog,wxDialog)
    EVT_BUTTON(ID_CLOSE_PROGRESS_DIALOG,Custom_Progress_Dialog::Close_Process_Window)
END_EVENT_TABLE()

Custom_Progress_Dialog::Custom_Progress_Dialog(wxWindow * parent, wxWindowID id, const wxString & title, 
    
    const wxPoint & pos, const wxSize & size, long style, const wxString & name) 
    
    : wxDialog(parent, id, title, pos, size, style, name)
{
     this->background = wxColour(240,240,240);

     this->SetDoubleBuffered(true);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_Progress_Dialog::OnPaint,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_Progress_Dialog::Size_Event,this,wxID_ANY);

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






Custom_Progress_Dialog::~Custom_Progress_Dialog()
{
    if(!this->Memory_Delete_Condition)
    {
       this->Memory_Delete_Condition = true;

    }
}

void Custom_Progress_Dialog::Size_Event(wxSizeEvent & event)
{
     event.Skip(true);

     this->PaintNow();
}




void Custom_Progress_Dialog::Construct_Text_Panel(wxString title, int dialog_size){

     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,-1));

     this->text_ctrl_close_panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,70));

     this->text_ctrl_dialog_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,30));



     this->text_ctrl_close_button  = new wxButton(this,ID_CLOSE_PROGRESS_DIALOG,wxT("CLOSE"),
     
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

void Custom_Progress_Dialog::SetBoldFont(){

     wxTextAttr AttrBold(wxColor(100, 100, 120));

     AttrBold.SetFontWeight(wxFONTWEIGHT_BOLD);

     AttrBold.SetFontSize(12);

     AttrBold.SetFontFaceName(wxT("Calibri"));

     this->GetTextControl()->SetDefaultStyle(AttrBold);

}

void Custom_Progress_Dialog::SetLightFont(){

     wxTextAttr AttrLigth(wxColor(50,50,50));

     AttrLigth.SetFontWeight(wxFONTWEIGHT_LIGHT);

     AttrLigth.SetFontSize(12);

     AttrLigth.SetFontFaceName(wxT("Calibri")); 

     this->GetTextControl()->SetDefaultStyle(AttrLigth);
}


void Custom_Progress_Dialog::AppendText_To_TextCtrl(wxString text){

     this->textctrl->AppendText(text);

     this->textctrl->Update();
}



void Custom_Progress_Dialog::Close_Process_Window(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_PROGRESS_DIALOG){

        this->Destroy();

     }
}

void Custom_Progress_Dialog::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_Progress_Dialog::PaintNow()
{
     wxClientDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}

void Custom_Progress_Dialog::OnPaint(wxPaintEvent& event)
{
     event.Skip(true);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
};

void Custom_Progress_Dialog::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

     }
}



void Custom_Progress_Dialog::Set_Font(wxFont Font){

      this->textctrl->SetFont(Font);
}


wxGauge * Custom_Progress_Dialog::GetDialogAddress(){

      return this->dialog;
}

wxTextCtrl * Custom_Progress_Dialog::GetTextControl(){

      return this->textctrl;
}