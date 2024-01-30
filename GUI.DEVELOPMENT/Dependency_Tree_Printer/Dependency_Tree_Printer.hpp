


#ifndef DEPENDENCY_TREE_PRINTER_HPP
#define DEPENDENCY_TREE_PRINTER_HPP

#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/dcclient.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/font.h>
#include <wx/sizer.h>
#include <wx/msgdlg.h>
#include "Custom_wxTreeCtrl.h"
#include "Project_Folder_Lister.h"
#include "Custom_DockArt.h"
#include "Custom_Window.h"
#include "Custom_Close_Button.h"

enum
{
  ID_CLOSE_DEPENDENCY_WINDOW = 81
};


class Dependency_Tree_Printer : public wxFrame
{
public:
  Dependency_Tree_Printer(wxFrame * parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,700), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);


  virtual ~Dependency_Tree_Printer();

  void Clear_Dynamic_Memory();

  void Set_Font(wxFont Default_Font);

  void Load_Project_Directory(wxString Folder);

  Custom_wxTreeCtrl * GetTreeCtrl();

  int GetTotalItemNum(wxString Folder);

  wxString GetItemPath(wxTreeItemId item_number);

  wxFrame * Parent_Frame_Pointer;

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void OnPaint(wxPaintEvent& event);

  void PaintNow();

  //void Initialize_Sizer();

  void Size_Event(wxSizeEvent & event);
  
  wxColour background;

  wxSize tree_control_size;

protected:

  void CloseWindow(wxCommandEvent & event);

  bool Memory_Delete_Condition;

  Project_Folder_Lister * Folder_Lister;

  wxPanel * tree_panel;

  wxPanel * close_panel;

  wxBoxSizer * frame_box;

  wxBoxSizer * close_button_sizer;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * close_box;

  wxButton * CloseButton;

  Custom_wxTreeCtrl * tree_control;

  wxFont * Directory_List_Font;

  DECLARE_EVENT_TABLE()
};

#endif /* DEPENDENCY_TREE_PRINTER_HPP */
