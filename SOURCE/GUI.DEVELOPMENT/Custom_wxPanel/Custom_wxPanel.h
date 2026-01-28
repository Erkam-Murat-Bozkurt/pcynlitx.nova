
#ifndef CUSTOM_WXPANEL_H
#define CUSTOM_WXPANEL_H

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/dcclient.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include "Event_ID_Numbers.h"
#include "Resource_Loader.hpp"



enum
{
  ID_OPEN_POPUP_MENU = 100,
};

class Custom_wxPanel : public wxPanel
{
public:
  Custom_wxPanel(wxWindow * parent, wxWindowID id, const wxPoint &pos,

                 const wxSize &size, wxColour background,

                 wxAuiPaneInfo * Pane);

  virtual ~Custom_wxPanel();

  void Receive_Book_Manager_Window(wxWindow * wnd){

       this->book_manager = wnd;
  }

  void Receive_Main_Menu_Address(wxMenu * menu){

       this->Menu_Ptr = menu;
  }

  wxMenu * Menu_Ptr;

  //void Update(){};

  void Initialize_Sizer();

  void Open_PopUp_Menu(wxCommandEvent & event);

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void PaintNow(wxWindow * wnd);


  wxStaticText * start_text;

  wxBitmap * project_file_selection_bitmap;

  int ToolBar_ID = 0;

  wxAuiToolBar * toolBar_pointer;

  wxAuiPaneInfo * Pane_Pointer;

  wxBitmap * Info_Icon_Bmp;

  wxBitmap * Save_Icon_Small;

  wxBitmap * exit_icon_bitmap;

  wxBitmap * build_icon_bitmap;

  wxBitmap * run_build_script_icon_bitmap;

  wxBitmap * dependency_icon_bitmap;
  
  wxColour background;

  wxButton * Start_Button;

  wxWindow * book_manager;

  wxWindow * bottom_window;

  wxWindow * button_window;

  wxWindow * text_window;


  wxBoxSizer * panel_sizer;

  wxBoxSizer * bottom_win_sizer;


  wxEvtHandler Event_Handler;

  bool Memory_Delete_Condition;


  wxMenu  * CMAKE_Menu;

  wxMenu  * Help_Menu;

  wxMenu  * File_Menu;

  wxMenu  * Project_Management;

  wxMenu  * Main_Menu;

  wxMenu  * Edit_Menu;

  wxMenu  * Info_Menu;

  wxMenu  * Linux_Debian_Package_Generator;

  wxMenu  * Linux_RPM_Package_Generator;

  wxMenu  * Windows_Package_Generator;

  Resource_Loader Rsc_Loader;

};

#endif /* CUSTOM_PANEL */
