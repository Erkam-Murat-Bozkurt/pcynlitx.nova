

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

#include "Custom_TextCtrl.h"

Custom_TextCtrl::Custom_TextCtrl(wxAuiNotebook * parent, wxWindowID id,

                  const wxPoint &pos, const wxSize &size, wxString path)

  : wxStyledTextCtrl(parent,id,pos,size)
{
    this->SetDoubleBuffered(true);

    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

    this->SetExtraStyle(wxCLIP_CHILDREN);

    this->file_path = path;

    this->SetSize(parent->GetClientSize());

    this->Centre();
}

Custom_TextCtrl::~Custom_TextCtrl(){

}

void Custom_TextCtrl::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(230,230,230));

     dc.DrawRectangle(rect.GetX()-1, rect.GetY()-1, rect.GetWidth()+1, rect.GetHeight()+1);
};
