

#ifndef CUSTOM_SYSTEM_INTERFACE_H
#define CUSTOM_SYSTEM_INTERFACE_H

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <shlwapi.h>
#include <cwchar>
#include "Cpp_FileOperations.h"

class Custom_System_Interface
{
public:
  Custom_System_Interface();
  virtual ~Custom_System_Interface();
  void SetCpuRate();
  bool Create_Process(std::string cmd);
  bool Create_Process(char * cmd);
  int  System_Function(char * cmd);
  bool Create_Process_With_Redirected_Stdout(char * cmd);
  void SetChildProcess_For_StdOut_Redirection();
  void WriteChildProcess_StdOutput();
  bool TerminateChildProcess();
  bool IsChildProcess_Still_Alive();
  void WaitForChildProcess();
  TCHAR * GetPipePath();
  std::string GetPipePath_StdStr();
  void ReadFromPipe(void);
  PROCESS_INFORMATION piProcInfo; 
  STARTUPINFO siStartInfo;
  UINT uExitCode;
protected:
  void DeterminePipePath(); 
  TCHAR * Convert_CString_To_TCHAR(char * cmd);  
  void Clear_Dynamic_Memory();
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  bool Is_Child_Process_Ended;
  TCHAR * TCHAR_string;
  TCHAR * StdOutPipe;
  std::string std_str_pipe_path;
  DWORD bufsize;
  CHAR chBuf[4096]; 
  DWORD64 Child_PID; 
  DWORD dwRead;
  DWORD dwWritten; 
  HANDLE hStdin;
  HANDLE hStdout; 
  HANDLE g_hChildStd_OUT_Rd;
  HANDLE g_hChildStd_OUT_Wr;
  HANDLE g_hInputFile;
  pid_t pid;
  int status;
  bool return_status;
  int return_value;
  char * cmd;
};

#endif /* CUSTOM_SYSTEM_INTERFACE_H */
