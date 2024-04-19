
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


enum
{
  ID_OPEN_POPUP_MENU = 300,
  ID_OPEN_FILE_MENU_CONTENT = 301,
  ID_OPEN_PROJECT_MANAGEMENT_MENU_CONTENT = 302,
  ID_OPEN_EDIT_MENU_CONTENT = 303,
  ID_OPEN_HELP_MENU_CONTENT = 304,
  ID_OPEN_CMAKE_MENU_CONTENT = 305,
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

  //void Update(){};

  void Initialize_Sizer();

  void Open_PopUp_Menu(wxCommandEvent & event);

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void Catch_PopUp_Menu(wxCommandEvent & event);

  void PaintNow(wxWindow * wnd);


  void Open_File_Menu(wxCommandEvent & event);
  void Open_Project_Management_Menu(wxCommandEvent & event);
  void Open_Edit_Menu(wxCommandEvent & event);
  void Open_Help_Menu(wxCommandEvent & event);
  void Open_CMAKE_Menu(wxCommandEvent & event);

  int ToolBar_ID = 0;

  wxAuiToolBar * toolBar_pointer;

  wxAuiPaneInfo * Pane_Pointer;


  wxColour background;

  wxButton * Start_Button;

  wxWindow * book_manager;

  wxWindow * bottom_window;

  wxBoxSizer * panel_sizer;

  wxEvtHandler Event_Handler;

  bool Memory_Delete_Condition;


  wxMenu  * CMAKE_Menu;

  wxMenu  * Help_Menu;

  wxMenu  * File_Menu;

  wxMenu  * Project_Management;

  wxMenu  * Main_Menu;

  wxMenu  * Edit_Menu;



  DECLARE_EVENT_TABLE()

};

#endif /* CUSTOM_PANEL */
