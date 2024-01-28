

#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H


#include <wx\wx.h>
#include <wx\frame.h>
#include <wx\panel.h>
#include <wx\process.h>
#include <wx\string.h>
#include <wx\process.h>
#include <wx\utils.h>
#include <wx\stream.h>
#include <wx\txtstrm.h>
#include <wx\textfile.h>
#include <wx\progdlg.h>
#include <wx\msgdlg.h>
#include <wx\richmsgdlg.h>
#include <wx\textctrl.h>
#include <wx/gauge.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "Event_ID_Numbers.h"
#include "Custom_System_Interface.h"

enum
{
  ID_CLOSE_PROCESS_OUTPUT_WINDOW = 71
};

class Process_Manager : public wxFrame
{
public:
  Process_Manager(wxFrame * parent, wxWindowID id=wxID_ANY, const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,700), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);


  virtual ~Process_Manager();
  void Fork_Process_With_Named_Pipe_Connection(char * cmd);
  void AppendText_To_TextCtrl(wxString text);
  void Fork_Process_With_Std_Out_Redirection(char * cmd);
  void Exec_Cmd_For_Single_Src_File(std::string path, std::string exe_name, char str);
  void Find_Source_File_Dependency_Determination_Command(wxString src_path);
  void Determine_Build_System_Initialization_Command();
  void Receive_Builder_Path(wxString bldr_path);
  void Receive_Descriptor_File_Path(wxString Path);
  void Fork_Process(wxString shell_command);
  void Construct_Text_Panel(wxString title, int dialog_size);
  void Print_Error_Stream(wxString title);
  void Print_Output_Stream(wxString title);
  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);
  void PaintNow(wxWindow * wnd);
  int  Get_Process_Exit_Status();
  void ReadStdOut();
  void ReadFromNamedPipe();
  void Clear_String_Memory(char * ptr);
  wxGauge * GetDialogAddress();
  wxTextCtrl * GetTextControl();
  std::string Get_Std_Out();
  std::string GetNamedPipeString();
  char * Get_Process_Command();
  bool is_pipe_open;
private:
  void CloseWindow(wxCommandEvent & event);
  void OnSize(wxSizeEvent & event);

  Custom_System_Interface SysInt;
  std::thread * read_process_output;
  std::thread * read_named_pipe;
  std::string std_out_put;
  std::string named_pipe_str;

  wxFont * Default_Font;

  wxPanel * text_ctrl_panel;

  wxPanel * close_panel;

  wxPanel * dialog_panel;

  wxGauge * dialog;

  wxTextCtrl * textctrl;

  wxBoxSizer * ctrl_box;

  wxBoxSizer * close_box;

  wxBoxSizer * dialog_box;


  wxBoxSizer * close_panel_sizer;

  wxBoxSizer * close_button_sizer;

  wxBoxSizer * frame_box;

  wxButton * CloseButton;



  wxFrame  * Frame_Ptr;
  wxFrame  * Output_Frame;
  wxString Des_Path;
  wxString Builder_Path;
  std::condition_variable cv;
  std::mutex mtx;
  char * procCmd;
  int  Process_Exit_Status;
  bool error_stream_status;
  bool Memory_Delete_Condition;

  DECLARE_EVENT_TABLE()

};

#endif /* PROCESS_MANAGER_H */
