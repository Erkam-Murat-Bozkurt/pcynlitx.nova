


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
#include "Custom_wxDataViewTreeCtrl.hpp"
#include "Project_Folder_Lister.h"
#include "Custom_DockArt.h"
#include "Custom_Window.h"
#include "Custom_Close_Button.h"
#include "Resource_Loader.hpp"

enum
{
  ID_CLOSE_DEPENDENCY_WINDOW = 81,
  ID_CLOSE_DEPENDECY_TEXT_WINDOW = 82
};


class Dependency_Tree_Printer : public wxFrame
{
public:
  Dependency_Tree_Printer(wxFrame * parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,700), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);


  virtual ~Dependency_Tree_Printer();

  void Clear_Dynamic_Memory();

  void AppendText_To_TextCtrl(wxString text);

  void Construct_Text_Panel(wxString title, int dialog_size);

  void Construct_Tree_Panel(wxString title);

  void Set_Font(wxFont Default_Font);

  void Load_Project_Directory(wxString Folder);

  wxDataViewTreeCtrl * GetTreeCtrl();

  int GetTotalItemNum(wxString Folder);

  wxString GetItemPath(wxDataViewItem item_number);

  wxFrame * Parent_Frame_Pointer;

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void OnPaint(wxPaintEvent& event);

  void PaintNow();

  void PrintDependencyTree();

  void Size_Event(wxSizeEvent & event);
  
  wxGauge * GetDialogAddress();
  
  wxTextCtrl * GetTextControl();

  wxColour background;

  wxSize tree_control_size;

protected:

  void Close_Tree_Window(wxCommandEvent & event);

  void Close_Process_Window(wxCommandEvent & event);

  bool Memory_Delete_Condition;

  Resource_Loader Rsc_Loader;

  Project_Folder_Lister * Folder_Lister;

  wxPanel * tree_panel;

  wxPanel * close_panel;

  wxBoxSizer * frame_box;

  wxBoxSizer * close_button_sizer;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * close_box;

  wxButton * CloseButton;

  wxDataViewTreeCtrl * tree_control;

  wxFont * Directory_List_Font;






  
  wxPanel * text_ctrl_panel;

  wxPanel * text_ctrl_close_panel;

  wxPanel * text_ctrl_dialog_panel;

  wxGauge * dialog;

  wxTextCtrl * textctrl;

  wxBoxSizer * text_ctrl_sizer;

  wxBoxSizer * text_ctrl_close_box;

  wxBoxSizer * dialog_box;


  wxBoxSizer * text_ctrl_close_panel_sizer;

  wxBoxSizer * text_ctrl_close_button_sizer;

  wxBoxSizer * text_ctrl_frame_box;

  wxButton * text_ctrl_close_button;


  DECLARE_EVENT_TABLE()
};

#endif /* DEPENDENCY_TREE_PRINTER_HPP */
