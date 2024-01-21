
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

Custom_Message_Dialog::Custom_Message_Dialog(wxWindow * parent, const wxString & message, wxWindowID id, const wxString & title,

    const wxPoint & pos, const wxSize & size, long style, const wxString & name) : 

     wxDialog(parent, id, title, pos, size, style, name)
{
    this->Memory_Delete_Condition = false;

    this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_Message_Dialog::OnPaint,this,wxID_ANY);

    this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_Message_Dialog::OnSize,this,wxID_ANY);



    this->figure_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->text_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);

    this->button_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxDefaultSize);


    wxBitmap bmp(wxT("D:\\Pcynlitx_Build_Platform\\icons\\exclamation_icon.png"),wxBITMAP_TYPE_ANY);

    this->figure = new wxStaticBitmap(this->figure_panel,wxID_ANY,bmp);

    this->text   = new wxStaticText(this->text_panel ,wxID_ANY,message);

    this->CloseButton  = new wxButton(this->button_panel,ID_CLOSE_MESSAGE_WINDOW,wxT("CLOSE"),wxDefaultPosition, wxSize(90, 50));


    wxBoxSizer * figure_sizer = new wxBoxSizer(wxVERTICAL);

    figure_sizer->Add(this->figure_panel,0,wxALIGN_CENTER_HORIZONTAL | wxALL,20);


    wxBoxSizer * text_sizer = new wxBoxSizer(wxVERTICAL);

    text_sizer->Add(this->text_panel,1, wxALIGN_CENTER_HORIZONTAL | wxALL, 20);


    wxBoxSizer * button_sizer = new wxBoxSizer(wxVERTICAL);

    button_sizer->Add(this->button_panel,0,wxALIGN_CENTER_HORIZONTAL |  wxALL,20);




    wxBoxSizer * topsizer = new wxBoxSizer(wxVERTICAL);

    topsizer->Add(figure_sizer,0, wxEXPAND | wxALL,0);

    topsizer->Add(text_sizer  ,1, wxEXPAND | wxALL,0);

    topsizer->Add(button_sizer,0, wxEXPAND | wxALL,0);


    topsizer->Layout();

    this->SetSizer(topsizer);

    topsizer->SetSizeHints(this);

    this->SetDoubleBuffered(true);

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxCLIP_CHILDREN);

    this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);


    this->SetBackgroundColour(wxColour(225,225,225));

    this->SetSize(size);

    this->SetMinSize(size);

    wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

    this->SetIcon(Frame_Icon);


    this->Centre(wxBOTH);

    this->Show();

    this->PaintNow(this);

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
     dc.SetBrush(wxColour(225,225,225));

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
}

