




#ifndef CUSTOM_PROGRESS_DIALOG_HPP
#define CUSTOM_PROGRESS_DIALOG_HPP

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
#include <wx/gauge.h>
#include "Custom_wxTreeCtrl.h"
#include "Project_Folder_Lister.h"
#include "Custom_DockArt.h"
#include "Custom_Window.h"
#include "Custom_Close_Button.h"
#include "Resource_Loader.hpp"

enum
{
  ID_CLOSE_PROGRESS_DIALOG = 91
};


class Custom_Progress_Dialog : public wxDialog
{
public:
  Custom_Progress_Dialog(wxWindow * parent, wxWindowID id=wxID_ANY, 
    
    const wxString & title=wxT("PROCESS REPORT"), 
    
    const wxPoint &pos=wxDefaultPosition,
    
    const wxSize &size=wxSize(800,600),
    
    long style=wxDEFAULT_DIALOG_STYLE, const wxString &name=wxDialogNameStr);


  virtual ~Custom_Progress_Dialog();

  void Clear_Dynamic_Memory();

  void AppendText_To_TextCtrl(wxString text);

  void Construct_Text_Panel(wxString title, int dialog_size);

  void SetBoldFont();

  void SetLightFont();

  void Set_Font(wxFont Default_Font);

  wxFrame * Parent_Frame_Pointer;

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void OnPaint(wxPaintEvent& event);

  void PaintNow();

  void Size_Event(wxSizeEvent & event);
  
  wxGauge * GetDialogAddress();
  
  wxTextCtrl * GetTextControl();

  wxColour background;

  wxSize tree_control_size;

protected:


  void Close_Process_Window(wxCommandEvent & event);

  bool Memory_Delete_Condition;

  Resource_Loader Rsc_Loader;
    
  wxBitmap * Frame_Bitmap;

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

#endif /* CUSTOM_PROGRESS_DIALOG_HPP */
