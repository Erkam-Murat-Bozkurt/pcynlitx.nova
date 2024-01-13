

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
#include "Event_ID_Numbers.h"
#include "Custom_System_Interface.h"

class Process_Manager
{
public:
  Process_Manager(wxFrame * Frame_Ptr);
  virtual ~Process_Manager();
  void Exec_Cmd_For_Single_Src_File(std::string path, std::string exe_name, char str);
  void Determine_Build_System_Initialization_Command();
  void Receive_Builder_Path(wxString bldr_path);
  void Receive_Descriptor_File_Path(wxString Path);
  void Fork_Process(wxString shell_command);
  void Print_Text(wxString std_out, wxString title);
  void Print_Error_Stream(wxString title);
  void Print_Output_Stream(wxString title);
  int  Get_Process_Exit_Status();
  void Clear_String_Memory(char * ptr);
  char * Get_Process_Command();
private:
  Custom_System_Interface SysInt;
  wxFrame  * Frame_Ptr;
  wxString Des_Path;
  wxString Builder_Path;
  char * procCmd;
  int  Process_Exit_Status;
  bool error_stream_status;
  bool Memory_Delete_Condition;
};

#endif /* PROCESS_MANAGER_H */
