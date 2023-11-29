

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

class Process_Manager : public wxProcess
{
public:
  Process_Manager(wxFrame * Frame, int ID);
  virtual ~Process_Manager();
  void Fork_Process(wxString shell_command);
  void Print_Text(wxString std_out, wxString title);
  void Print_Error_Stream();
  void Print_Output_Stream(wxString title);
  void Increase_Process_End_Counter();
  void Set_Zero_To_Process_End_Counter();
  int  Get_Process_Exit_Status();
private:
  wxFrame * Frame_Ptr;
  int Process_Exit_Status;
  bool error_stream_status;
};

#endif /* PROCESS_MANAGER_H */
