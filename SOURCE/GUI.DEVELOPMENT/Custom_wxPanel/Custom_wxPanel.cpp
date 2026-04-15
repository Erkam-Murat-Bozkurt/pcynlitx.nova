
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



#include "Custom_wxPanel.h"



Custom_wxPanel::Custom_wxPanel(wxWindow * parent, wxWindowID id,

              const wxPoint &pos, const wxSize &size,

              wxColour background_colour)

  : wxPanel(parent,id,pos,size)
{
     //this->background = background_colour;

     this->Memory_Delete_Condition = false;

     this->SetThemeEnabled(false);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetBackgroundColour(wxColour(240,240,240));

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);


     this->panel_sizer = new wxBoxSizer(wxVERTICAL);

     int bottom_window_y_extent = size.GetHeight()/8;


     this->bottom_window = new wxWindow(this, wxID_ANY,wxDefaultPosition,
          
                           this->FromDIP(wxSize(this->GetSize().GetX(),bottom_window_y_extent)));
     
     this->bottom_window->SetBackgroundColour(wxColour(240,240,240));

     this->bottom_window->Show(true);


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

void Custom_wxPanel::Set_Pane_Properties(wxSize pane_dpi_size){

     this->Central_Pane_Info.CloseButton(false);

     this->Central_Pane_Info.Centre();

     this->Central_Pane_Info.Dock();

     this->Central_Pane_Info.Show(true);

     this->Central_Pane_Info.Resizable(true);

     this->Central_Pane_Info.MinSize(this->FromDIP(pane_dpi_size));

     this->Interface_Manager_Ptr->AddPane(this,this->Central_Pane_Info);
}

void Custom_wxPanel::Initialize_Sizer()
{
     this->panel_sizer->Add(this->book_manager, 1, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,13);

     this->panel_sizer->Add(this->bottom_window,0, wxALIGN_LEFT | wxFIXED_MINSIZE | wxEXPAND | wxTOP | wxLEFT,0);

     this->SetSizer(this->panel_sizer);

     this->panel_sizer->SetSizeHints(this);

     this->panel_sizer->ShowItems(true);

     this->Fit();

     this->SetAutoLayout(true);
}

void Custom_wxPanel::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-2, rect.GetY()-2, rect.GetWidth()+2,rect.GetHeight());
}

void Custom_wxPanel::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+1,wnd->GetSize().y);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}

