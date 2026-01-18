
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

      dc.SetPen(wxPen(wxColour(50,50,60,0xff)));

      dc.SetBrush(wxColour(50,50,60,0xff));

      dc.DrawRectangle(rect.GetX()-1, rect.GetY() - 1, rect.GetWidth() + 5, rect.GetHeight() + 5);
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




  wxBitmap * CreateBitmapFromPngResource(const wxString& t_name)
  {
     wxBitmap*   r_bitmapPtr = 0;
  
     char*       a_data      = 0;
     DWORD       a_dataSize  = 0;
  
     if(LoadDataFromResource(a_data, a_dataSize, t_name))
     {
        r_bitmapPtr = GetBitmapFromMemory(a_data, a_dataSize);
     }
  
     return r_bitmapPtr;
  }


  bool LoadDataFromResource(char*& t_data, DWORD& t_dataSize, const wxString& t_name)
  {
     bool     r_result    = false;
     HGLOBAL  a_resHandle = 0;
     HRSRC    a_resource;
  
     a_resource = FindResource(0, t_name.wchar_str(), RT_RCDATA);
  
     if(0 != a_resource)
     {
        a_resHandle = LoadResource(NULL, a_resource);
        if (0 != a_resHandle)
        {
           t_data = (char*)LockResource(a_resHandle);
           t_dataSize = SizeofResource(NULL, a_resource);
           r_result = true;
        }
     }
  
     return r_result;
  }


  wxBitmap* GetBitmapFromMemory(const char* t_data, const DWORD t_size)
  {
     wxMemoryInputStream a_is(t_data, t_size);
     return new wxBitmap(wxImage(a_is, wxBITMAP_TYPE_PNG, -1), -1);
  }


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
