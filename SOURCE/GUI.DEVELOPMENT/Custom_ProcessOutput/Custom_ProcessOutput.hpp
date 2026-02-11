


#ifndef CUSTOM_PROCESSOUTPUT_HPP
#define CUSTOM_PROCESSOUTPUT_HPP

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
#include "Custom_Message_Dialog.hpp"
#include "Resource_Loader.hpp"
#include "Workspace_Data_Holder.hpp"


enum
{
  ID_CLOSE_WINDOW = 70
};

class Custom_ProcessOutput : public wxFrame
{
public:

Custom_ProcessOutput(wxFrame *parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(750,600), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);

  virtual ~Custom_ProcessOutput();

  wxTextCtrl * GetTextControl() const;

  wxGauge * GetDialogAddress();

  void Directory_List_Show_Cond(bool cond);

  void Receive_Directory_Open_Location(wxString loc);

  void Receive_Tree_View_Panel(Custom_Tree_View_Panel * ptr);

  void Receive_System_Interface(Custom_System_Interface * Sys);

  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);

  void SetWindowOpenStatus(bool status);

  void SetBoldFont();

  void SetLightFont();

  void PaintNow(wxWindow * wnd);

  void Construct_Output(int size);

  void OnSize(wxSizeEvent & event);

  void PrintProcessOutput(wxString text);

  void ReadProcessOutput(wxString start_text);

  int GetLogNumber();

  bool GetWindowsOpenStatus();

  bool process_complation_status;

  bool process_interrrupt_status;

  int progress_point;

  char * cmd;

  Custom_System_Interface SysInt;

  Workspace_Data_Holder * Wrk_Data_Holder_Ptr;

private:
  
  void OnClose(wxCloseEvent & ent);

  void CloseWindow(wxCommandEvent & event);

  bool IsChildProcessStillAlive();

  bool ProcessTermination();

  bool process_end_status;

  bool dir_list_show_cnd;

  Resource_Loader Rsc_Loader;
    
  wxBitmap * Frame_Bitmap;

  Custom_System_Interface * SysPtr;

  Custom_Tree_View_Panel * dir_list_ptr;

  wxGauge * dialog;

  wxPanel * text_ctrl_panel;

  wxPanel * dialog_panel;

  wxPanel * close_panel;

  wxTextCtrl * textctrl;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * dialog_box;

  wxBoxSizer * close_box;


  wxBoxSizer * close_panel_sizer;

  wxBoxSizer * close_button_sizer;

  wxBoxSizer * frame_box;

  wxButton * CloseButton;

  wxFont   * Default_Font;


  bool * Progress_Bar_Start_status;

  Process_Manager * Process_Manager_Ptr;

  wxString directory_open_location;

  bool Memory_Delete_Condition;

  bool progress_cond;

  bool window_open_status;

  int log_num;

  DECLARE_EVENT_TABLE()
};

#endif /* CUSTOM_PROCESSOUTPUT_HPP */
