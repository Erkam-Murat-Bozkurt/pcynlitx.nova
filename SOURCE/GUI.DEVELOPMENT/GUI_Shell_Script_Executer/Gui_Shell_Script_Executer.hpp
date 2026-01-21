



#ifndef GUI_SHELL_SCRIPT_EXECUTER_HPP
#define GUI_SHELL_SCRIPT_EXECUTER_HPP


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
#include "Cpp_FileOperations.h"
#include "Process_Manager.hpp"
#include "Custom_ProcessOutput.hpp"
#include "Custom_Message_Dialog.hpp"
#include "StringOperator.h"
#include "Resource_Loader.hpp"


class Gui_Shell_Script_Executer : public wxFrame
{
public:
  Gui_Shell_Script_Executer(wxFrame * parent, wxWindowID id=wxID_ANY, 
  
   const wxString & title=wxT(""), 

   const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxSize(900,700), 
   
   long style=wxDEFAULT_FRAME_STYLE | wxSTAY_ON_TOP);

  virtual ~Gui_Shell_Script_Executer();
  void Execute_Shell_Script(std::string path);
  void Fork_Process_With_Std_Out_Redirection(char * cmd);
  wxString Get_Error_Stream();
  wxString Get_Output_Stream();
  void DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect);
  void PaintNow(wxWindow * wnd);
  int  Get_Process_Exit_Status();
  void ReadStdOut();
  void Clear_String_Memory(char * ptr);
  std::string Get_Std_Out();
  char * Get_Process_Command();
  bool is_pipe_open;
private:
  //void CloseWindow(wxCommandEvent & event);
  void OnSize(wxSizeEvent & event);
  char *  Convert_CString(std::string std_str);
  void script_executer(std::string path);
  Custom_System_Interface SysInt;
  Cpp_FileOperations FileManager;
  Custom_ProcessOutput * Process_Output;
  StringOperator StringManager;
  Resource_Loader Rsc_Loader;
  bool script_end_status;
  std::thread * read_process_output;
  std::thread * execute_shell_script;
  std::string std_out_put;
  wxFont * Default_Font;
  std::string script_path;
  char * procCmd;
  int  Process_Exit_Status;
  bool error_stream_status;
  bool Memory_Delete_Condition;
  wxBitmap * exclamation_mark_bmp;

  int script_size;

  char * c_str;

  //DECLARE_EVENT_TABLE()

};

#endif /* GUI_SHELL_SCRIPT_EXECUTER_HPP */
