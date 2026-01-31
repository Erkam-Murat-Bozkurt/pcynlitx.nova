
#ifndef TOOLBAR_INITIALIZER_H
#define TOOLBAR_INITIALIZER_H

#include <wx/wx.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/auibar.h>
#include <wx/aui/dockart.h>
#include <wx/bitmap.h>
#include <wx/dc.h>
#include <wx/dcclient.h>
#include <wx/mstream.h>
#include <iostream>
#include <wx/imagpng.h>
#include "Event_ID_Numbers.h"
#include "Custom_DockArt.h"
#include "Resource_Loader.hpp"

class MyAuiTBArt : public wxAuiDefaultToolBarArt
{
public:
    MyAuiTBArt() {}
    virtual ~MyAuiTBArt(){

    }

    // This one is important, without it, it wont work
    wxAuiToolBarArt * Clone() {

        return new MyAuiTBArt(*this);
    }

    virtual void DrawPlainBackground(wxDC& dc, wxWindow * wnd, const wxRect& _rect) {

      wxRect rect = _rect;

      rect.height++;

      dc.SetPen(wxPen(wxColour(60,60,75,0xff)));

      dc.SetBrush(wxColour(60,60,75,0xff));

      dc.DrawRectangle(rect.GetX()-2, rect.GetY() - 3, rect.GetWidth() + 7, rect.GetHeight() + 7);
    }
};

class Custom_wxAuiToolBar : public wxAuiToolBar
{
public:
    Custom_wxAuiToolBar(wxWindow *parent, wxWindowID id=wxID_ANY, 
      
     const wxPoint &position=wxDefaultPosition,
  
     const wxSize &size=wxDefaultSize, long style=wxAUI_TB_DEFAULT_STYLE) 
     
     : wxAuiToolBar(parent,id,position,size,style)

     {
          this->GetEventHandler()->Bind(wxEVT_PAINT,&Custom_wxAuiToolBar::OnPaint,this,wxID_ANY);         
     }

    void OnPaint(wxPaintEvent& event )
    {
        event.Skip(true);

        wxClientDC dc(this);

        this->Art_Pointer->DrawPlainBackground(dc,this,this->GetRect());
   }

   void Receive_Toolbar_Art(MyAuiTBArt * ptr){

        this->Art_Pointer = ptr;
   }

   MyAuiTBArt * Art_Pointer;
};


class ToolBar_Initializer
{
public:
  ToolBar_Initializer();
  virtual ~ ToolBar_Initializer();
  void Initialize_ToolBar(wxFrame * Frame_Pointer, 
       wxAuiDockArt * Dock_Art_Pointer, wxAuiManager * Interface_Manager);
  wxAuiToolBar * Get_ToolBar_Pointer();


  Resource_Loader Rsc_Loader;

  Custom_wxAuiToolBar * toolBar;
  MyAuiTBArt * Art_Pointer;
  wxWindowDC * WinDc;
  wxBitmap * construct_build_system;
  wxBitmap * build_executable_makefile;
  wxBitmap * Select_Project_File;
  wxBitmap * Empty_Project_File;
  wxBitmap * Show_Help_Document;
  wxBitmap * open_terminal;
  wxBitmap * build_executable;
  wxBitmap * open_settings;
  wxBitmap * file_save;
  wxBitmap * open_tree_view;
  wxBitmap * print_descriptions;
  wxBitmap * open_help_menu;
  wxBitmap * close;
};

#endif /* TOOLBAR_INITIALIZER_H */
