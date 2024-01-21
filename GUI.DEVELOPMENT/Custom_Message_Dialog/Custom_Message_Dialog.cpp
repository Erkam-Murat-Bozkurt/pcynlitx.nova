
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

#include "Custom_Message_Dialog.hpp"

BEGIN_EVENT_TABLE(Custom_Message_Dialog,wxDialog)
    EVT_BUTTON(ID_CLOSE_MESSAGE_WINDOW,Custom_Message_Dialog::CloseWindow)
END_EVENT_TABLE()

Custom_Message_Dialog::Custom_Message_Dialog(wxWindow * parent, const wxString & message, 

    const wxString & message_title, wxWindowID id, const wxString & title, const wxBitmap & bmp, 

    const wxPoint & pos, const wxSize & size, long style, const wxString & name) : 

    wxDialog(parent, id, title, pos, size, style, name)
{
    this->Memory_Delete_Condition = false;

    this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_Message_Dialog::OnPaint,this,wxID_ANY);

    this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_Message_Dialog::OnSize,this,wxID_ANY);


    std::string face_name = "Segoe UI"; 

    this->Default_Font = new wxFont(12,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                         wxFONTWEIGHT_NORMAL,false,wxString(face_name));

    this->SetFont(*this->Default_Font);


    this->figure_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->text_title_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->text_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->button_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);


    this->figure = new wxStaticBitmap(this->figure_panel,wxID_ANY,bmp);

    this->figure->SetBackgroundColour(wxColour(235,235,235));

    this->text   = new wxStaticText(this->text_panel ,wxID_ANY,message);

    this->text_title = new wxStaticText(this->text_title_panel ,wxID_ANY,message_title);


    this->text_title->SetForegroundColour(wxColour(134,104,112));

     wxFont textFont = this->text_title->GetFont();

    this->text_title->SetFont(textFont.Bold());

    this->CloseButton  = new wxButton(this->button_panel,ID_CLOSE_MESSAGE_WINDOW,
    
                         wxT("CLOSE"),wxDefaultPosition, wxSize(100,60));



    wxBoxSizer * text_sizer = new wxBoxSizer(wxVERTICAL);

    text_sizer->Add(this->text_title_panel,0);

    text_sizer->Add(this->text_panel,1);



    wxBoxSizer * panel_sizer = new wxBoxSizer(wxHORIZONTAL);

    panel_sizer->Add(text_sizer,1,  wxALIGN_LEFT | wxALL, 50);

    panel_sizer->Add(this->figure_panel,0, wxRIGHT | wxTOP | wxBOTTOM,60);


    wxBoxSizer * button_sizer = new wxBoxSizer(wxVERTICAL);

    button_sizer->Add(this->button_panel,0,wxALIGN_CENTER_HORIZONTAL |  wxALL,30);




    wxBoxSizer * topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(panel_sizer,2, wxEXPAND | wxALL,0);

    topsizer->Add(button_sizer,0, wxEXPAND | wxALL,0);


    topsizer->Layout();

    this->SetSizer(topsizer);

    topsizer->SetSizeHints(this);

    this->SetDoubleBuffered(true);

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxCLIP_CHILDREN);

    this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);


    this->SetBackgroundColour(wxColour(235,235,235));

    this->SetSize(size);

    this->SetMinSize(size);

    wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

    this->SetIcon(Frame_Icon);


    this->Centre(wxBOTH);

    this->Show();

    this->PaintNow(this);

    wxBell();

}

Custom_Message_Dialog::~Custom_Message_Dialog()
{
     if(!this->Memory_Delete_Condition)
     {
         this->Memory_Delete_Condition = true;

     }
}



void Custom_Message_Dialog::CloseWindow(wxCommandEvent & event)
{
     this->Destroy();
}


void Custom_Message_Dialog::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(235,235,235));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_Message_Dialog::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}


void Custom_Message_Dialog::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);
}



 void Custom_Message_Dialog::OnPaint(wxPaintEvent & event){

      event.Skip(true);

      wxPaintDC dc(this);

      wxRect rect(this->GetSize());

      this->DrawBackground(dc,this,rect);

      wxRect rect_text(this->GetSize());

      this->DrawBackground(dc,this,rect_text);
}

