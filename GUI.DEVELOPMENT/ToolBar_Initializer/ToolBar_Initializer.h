
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
#include <iostream>
#include "Event_ID_Numbers.h"
#include "Custom_DockArt.h"

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

      dc.SetBrush(wxColour(90,90,100,0xff));

      dc.DrawRectangle(rect.GetX() - 1, rect.GetY() - 1, rect.GetWidth() + 5, rect.GetHeight() + 5);
    }
};

class ToolBar_Initializer
{
public:
  ToolBar_Initializer();
  virtual ~ ToolBar_Initializer();
  void Initialize_ToolBar(wxFrame * Frame_Pointer, 
       wxAuiDockArt * Dock_Art_Pointer, wxAuiManager * Interface_Manager);
  wxAuiToolBar * Get_ToolBar_Pointer();
  wxAuiToolBar * toolBar;
  wxAuiToolBarArt * Art_Pointer;
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
};

#endif /* TOOLBAR_INITIALIZER_H */
