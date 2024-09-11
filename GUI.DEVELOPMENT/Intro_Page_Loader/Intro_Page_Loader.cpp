

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

#include "Intro_Page_Loader.h"

Intro_Page_Loader::Intro_Page_Loader(wxWindow * parent,wxSize page_size, int tab_ctrl_hgt):

                   wxWindow(parent,-1,wxDefaultPosition,page_size,wxBORDER_NONE)
{
     this->Connect(this->GetId(),wxEVT_PAINT,wxPaintEventHandler(Intro_Page_Loader::OnPaint));

     this->Intro_Page_Open_Status_Pointer = nullptr;

     this->tab_ctrl_height = tab_ctrl_hgt;

     this->Parent_Window_Pointer = parent;

     this->Memory_Delete_Condition = false;

     this->intro_page_bitmap  
     
          = new wxBitmap(wxT("C:\\Program Files\\Nwinix\\Intro_File.png"), wxBITMAP_TYPE_PNG);

     this->intro_page_image = this->intro_page_bitmap->ConvertToImage();

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxCLIP_CHILDREN);

     this->Layout();

     this->Fit();

     wxSize Parent_Size = this->Parent_Window_Pointer->GetClientSize();

     int new_size_y = Parent_Size.y - this->tab_ctrl_height;

     wxSize new_size = wxSize(Parent_Size.x+1,new_size_y+1);

     this->SetSize(new_size);

     this->SetMinSize(this->intro_page_image.GetSize());

     this->CenterOnParent(wxHORIZONTAL);

     this->Fit();

     this->SetAutoLayout(true);

     this->Show(true);
}

Intro_Page_Loader::~Intro_Page_Loader(){

    if(!this->Memory_Delete_Condition){

        this->DeletePendingEvents();

        this->Clear_Dynamic_Memory();

        *this->Intro_Page_Open_Status_Pointer = false;

        this->Intro_Page_Open_Status_Pointer = nullptr;
    }
}

void Intro_Page_Loader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         delete this->intro_page_bitmap;
     }
}

void Intro_Page_Loader::Receive_Intro_Page_Open_Status(bool * status)
{
     this->Intro_Page_Open_Status_Pointer = status;
}

void Intro_Page_Loader::Close_Intro_Page()
{
     this->~Intro_Page_Loader();
}


void Intro_Page_Loader::OnPaint(wxPaintEvent& event)
{
     event.Skip(false);

     event.StopPropagation();

     wxPaintDC dc(this);

     wxSize Rect_Size = this->GetSize();

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,this,rect);
}

void Intro_Page_Loader::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect & rect)
{
     dc.SetPen(wxPen(wxColour(200,200,200,0xff)));

     dc.SetBrush(wxColour(250,250,250,0xff));

     dc.DrawRectangle(rect.GetX(), rect.GetY(), rect.GetWidth(),rect.GetHeight());


     wxSize Bitmap_Size = this->intro_page_bitmap->GetSize();

     wxSize Panel_Size = rect.GetSize();

     int x_extend = Panel_Size.x - Bitmap_Size.x;

     int y_extend = Panel_Size.y - Bitmap_Size.y;

     dc.DrawBitmap(*this->intro_page_bitmap,wxPoint(rect.GetX()+x_extend/2,rect.GetY()+y_extend/2));
}
