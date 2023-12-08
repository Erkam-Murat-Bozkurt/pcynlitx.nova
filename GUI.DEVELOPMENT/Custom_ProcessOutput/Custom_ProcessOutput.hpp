


#ifndef CUSTOM_PROCESSOUTPUT_HPP

#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/dc.h>
#include <wx/event.h>
#include <wx/dcclient.h>
#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/sizer.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include "Process_Manager.hpp"
#include "Custom_DockArt.h"

class Custom_ProcessOutput : public wxFrame
{
public:

Custom_ProcessOutput(wxFrame *parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,650), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);

  virtual ~Custom_ProcessOutput();

  wxTextCtrl * GetTextControl() const;

  wxGauge * GetDialogAddress();

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void PaintNow(wxWindow * wnd);

  void Construct_Output(int bar_size);

  void OnSize(wxSizeEvent & event);

  void Receive_Process_Manager(Process_Manager * Pr_Man);

  void PrintProcessOutput();

private:

  wxGauge * dialog;

  wxPanel * text_ctrl_panel;

  wxPanel * dialog_panel;

  wxTextCtrl * textctrl;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * dialog_box;

  wxBoxSizer * frame_box;

  wxFont   * Default_Font;

  Process_Manager * Process_Manager_Ptr;

  bool Memory_Delete_Condition;
};

#endif /* CUSTOM_PROCESSOUTPUT_HPP */
