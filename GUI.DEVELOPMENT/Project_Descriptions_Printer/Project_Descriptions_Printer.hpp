




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
#include <wx/stattext.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Process_Manager.hpp"
#include "Custom_DockArt.h"
#include "Custom_System_Interface.h"
#include "Custom_Tree_View_Panel.h"
#include "Descriptor_File_Reader.hpp"

enum
{
  ID_CLOSE_DESCRIPTION_WINDOW = 80
};

class Project_Descriptions_Printer : public wxFrame
{
public:

Project_Descriptions_Printer(wxFrame *parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,770), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);

  virtual ~Project_Descriptions_Printer();

  wxTextCtrl * GetTextControl() const;

  void Receive_Descriptor_File_Path(wxString DesPATH);

  void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);

  void Print_Descriptions();

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void PaintNow(wxWindow * wnd);

  void Construct_Text_Panel();

  void OnSize(wxSizeEvent & event);

  int GetLogNumber();

  bool GetWindowsOpenStatus();

private:

  void CloseWindow(wxCommandEvent & event);

  Descriptor_File_Reader * Des_Reader;

  wxString Descriptor_File_Path;

  wxPanel * text_ctrl_panel;

  wxPanel * close_panel;

  wxTextCtrl * textctrl;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * close_box;


  wxBoxSizer * close_panel_sizer;

  wxBoxSizer * close_button_sizer;

  wxBoxSizer * frame_box;

  wxButton * CloseButton;

  wxFont   * Default_Font;

  bool Memory_Delete_Condition;

  bool window_open_status;

  int log_num;

  DECLARE_EVENT_TABLE()
};

#endif /* CUSTOM_PROCESSOUTPUT_HPP */
