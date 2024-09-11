
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

#include "Custom_wxTreeCtrl.h"


Custom_wxTreeCtrl::Custom_wxTreeCtrl(wxWindow *parent, wxWindowID id,

  const wxPoint & pos,

  const wxSize & size, long style) : wxTreeCtrl(parent,id,pos,size,style)
  {
     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Parent_Window_Pointer = parent;

     this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_wxTreeCtrl::OnPaint,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_wxTreeCtrl::Size_Event,this,wxID_ANY);

     wxFont tree_font(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,

                          wxFONTWEIGHT_NORMAL,false,wxT("Segoue UI"));

     this->SetFont(tree_font);

     this->SetBackgroundColour(wxColour(250,250,250));

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->ClearBackground();

     this->SetMinSize(this->Parent_Window_Pointer->GetClientSize());

     this->SetSize(this->Parent_Window_Pointer->GetClientSize());

     this->Fit();

     this->SetAutoLayout(true);

     this->CentreOnParent(wxBOTH);

     this->Refresh();
 }

 Custom_wxTreeCtrl::~Custom_wxTreeCtrl()
 {

 }

 void Custom_wxTreeCtrl::PaintNow(){

       wxClientDC dc(this);

       wxRect rect(this->GetSize());

       this->DrawBackground(dc,this,rect);
 }

 void Custom_wxTreeCtrl::OnPaint(wxPaintEvent & event){

      event.Skip(true);

      wxPaintDC dc(this);

      wxRect rect(this->GetSize());

      this->DrawBackground(dc,this,rect);
}


void Custom_wxTreeCtrl::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(255,255,255));

     dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth(),rect.GetHeight());
}

void Custom_wxTreeCtrl::Receive_Position(wxPoint control_position){

     this->Position = control_position;
}

void Custom_wxTreeCtrl::Size_Event(wxSizeEvent & event)
{
      event.Skip(true);

      wxWindow * parent = this->GetParent();

      this->SetSize(parent->GetClientSize());

      this->PaintNow();
}
