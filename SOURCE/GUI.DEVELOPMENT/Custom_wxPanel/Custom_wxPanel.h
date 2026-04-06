
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
#include "Custom_Tree_View_Panel.h"


class Custom_wxPanel : public wxPanel
{
public:
  Custom_wxPanel(wxWindow * parent, wxWindowID id, const wxPoint &pos,

                 const wxSize &size, wxColour background);

  virtual ~Custom_wxPanel();

  void Receive_Book_Manager_Window(wxWindow * wnd){

       this->book_manager = wnd;
  }

  void Receive_Main_Menu_Address(wxMenu * menu){

       this->Menu_Ptr = menu;
  }

  void Set_Pane_Properties(wxSize pane_dpi_size);

  wxAuiManager * Interface_Manager_Ptr;

  wxAuiPaneInfo Central_Pane_Info;

  wxMenu * Menu_Ptr;

  //void Update(){};

  void Initialize_Sizer();

  void Open_PopUp_Menu(wxCommandEvent & event);

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void PaintNow(wxWindow * wnd);

  wxStaticText * start_text;
  
  wxButton * Start_Button;

  wxWindow * book_manager;

  wxWindow * bottom_window;

  wxWindow * text_window;


  wxBoxSizer * panel_sizer;

  wxBoxSizer * bottom_win_sizer;

  bool Memory_Delete_Condition;

  Resource_Loader Rsc_Loader;

};

#endif /* CUSTOM_PANEL */
