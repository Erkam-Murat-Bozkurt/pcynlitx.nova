
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



#include "Custom_wxDataViewTreeCtrl.hpp"

BEGIN_EVENT_TABLE(Custom_wxDataViewTreeCtrl,wxDataViewTreeCtrl)
   EVT_SCROLL(Custom_wxDataViewTreeCtrl::SetScrollPosition)
END_EVENT_TABLE()

Custom_wxDataViewTreeCtrl::Custom_wxDataViewTreeCtrl(wxWindow *parent, wxWindowID id,

  const wxPoint & pos,

  const wxSize & size, long style) : wxDataViewTreeCtrl(parent,id,pos,size,style)
  {
     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Parent_Window_Pointer = parent;

     this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_wxDataViewTreeCtrl::OnPaint,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_wxDataViewTreeCtrl::Size_Event,this,wxID_ANY);

     //this->GetEventHandler()->Bind()


     this->SetThemeEnabled(false);

     this->SetBackgroundColour(wxColour(250,250,250));

     this->SetEventHandler(this);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->ClearBackground();

     this->SetMinSize(this->Parent_Window_Pointer->GetClientSize());

     this->SetSize(this->Parent_Window_Pointer->GetClientSize());

     this->Fit();

     this->Layout();

     this->CentreOnParent(wxBOTH);

     this->Refresh();
 }

 Custom_wxDataViewTreeCtrl::~Custom_wxDataViewTreeCtrl()
 {

 }

 
void Custom_wxDataViewTreeCtrl::SetScrollPosition(wxScrollEvent& event){

     event.Skip(true);

     wxMessageDialog * dial = new wxMessageDialog(this,wxT("scroll event"),wxT(""),wxOK);

     if(dial->ShowModal () == wxOK);

     //this->ScrollLines(this->GetScrollPos(wxVERTICAL));
}

 void Custom_wxDataViewTreeCtrl::OnPaint(wxPaintEvent & event){

      event.Skip(true);

      wxPaintDC dc(this);

      wxRect rect(this->GetSize());

      this->DrawBackground(dc,this,rect);
}

void Custom_wxDataViewTreeCtrl::PaintNow(){

     wxClientDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}



void Custom_wxDataViewTreeCtrl::Size_Event(wxSizeEvent & event)
{
      event.Skip(true);

      wxWindow * parent = this->GetParent();

      this->SetSize(parent->GetClientSize());

      this->PaintNow();
}


void Custom_wxDataViewTreeCtrl::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect){

     dc.SetBrush(wxColour(230,230,230));

     dc.DrawRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(),rect.GetHeight());
}

void Custom_wxDataViewTreeCtrl::Receive_Position(wxPoint control_position){

     this->Position = control_position;
}