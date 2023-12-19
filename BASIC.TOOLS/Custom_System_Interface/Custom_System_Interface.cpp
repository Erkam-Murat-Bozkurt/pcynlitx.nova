

/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Custom_System_Interface.h"

Custom_System_Interface::Custom_System_Interface(){

    this->status = 0;

    this->return_status = false; // The return status of the system call..

    this->hStdin = nullptr;
    
    this->hStdout = nullptr; 
  
    this->g_hChildStd_OUT_Rd = nullptr;
  
    this->g_hChildStd_OUT_Wr = nullptr;
  
    this->g_hInputFile = nullptr;

    this->StdOutPipe = nullptr;

    this->TCHAR_string = nullptr;

    this->bufsize = 4096;
}

Custom_System_Interface::~Custom_System_Interface(){

    if(!this->Memory_Delete_Condition){

         this->Clear_Dynamic_Memory();
    }
}

void Custom_System_Interface::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->StdOutPipe != nullptr){

            delete [] this->StdOutPipe;

            this->StdOutPipe = nullptr;
         }

         if(this->TCHAR_string != nullptr){

            delete [] this->TCHAR_string;

            this->TCHAR_string = nullptr;
         }

         if(this->FileManager.Is_Path_Exist(this->GetPipePath_StdStr()))
         {
             this->FileManager.Delete_File(this->GetPipePath_StdStr());
         }
     }
}



int Custom_System_Interface::System_Function(char * cmd){

     this->return_value = 0;

     STARTUPINFO startupInfo;

     PROCESS_INFORMATION processInformation;

     ZeroMemory(&startupInfo,sizeof(startupInfo));

     startupInfo.cb = sizeof(startupInfo);

     ZeroMemory(&processInformation,sizeof(processInformation));

     this->return_value = CreateProcessA(NULL,cmd,NULL,NULL,TRUE,

                          NORMAL_PRIORITY_CLASS,NULL,NULL,&startupInfo,

                          &processInformation);

     WaitForSingleObject( processInformation.hProcess, INFINITE );

     DWORD exit_code = 0;

     GetExitCodeProcess(processInformation.hProcess, &exit_code );

     CloseHandle(processInformation.hProcess);

     if(((exit_code != 0) || (this->return_value == 0))){

        std::cout << "\n The system function executing a command (an exacutable binary)";

        std::cout << "\n in a seperate process can not ended sucessfully.";

        std::cout << "\n the process has been ended with exit code:" << exit_code;

        std::cout << "\n\n";

        this->return_value = exit_code;

        return this->return_value;
     }
     else{

          this->return_value = 0;

          return this->return_value;
     }
}

bool Custom_System_Interface::Create_Process(std::string std_cmd){

     size_t cmd_size = std_cmd.length();

     this->cmd = new char [5*cmd_size];

     int index = 0;

     for(size_t i=0;i<cmd_size;i++){

          this->cmd[index] = std_cmd[i];

          index++;
     }

     this->cmd[index] = '\0';

     bool return_status = this->Create_Process(this->cmd);
     
     delete [] this->cmd;

     return return_status;
}


void Custom_System_Interface::SetCpuRate(){


     HANDLE hJobObject = NULL;

     hJobObject = CreateJobObject(NULL,NULL);
     
     if (hJobObject == NULL) {
    
         std::cout << "\n Job CPU limit can not created"; 

         exit(EXIT_FAILURE);         
     }

     JOBOBJECT_CPU_RATE_CONTROL_INFORMATION cpuRateInfo; 

     cpuRateInfo.ControlFlags = JOB_OBJECT_CPU_RATE_CONTROL_ENABLE | JOB_OBJECT_CPU_RATE_CONTROL_HARD_CAP;

     cpuRateInfo.CpuRate = 5000;

     if (!SetInformationJobObject(hJobObject, JobObjectCpuRateControlInformation, &cpuRateInfo, 
     
          sizeof(JOBOBJECT_CPU_RATE_CONTROL_INFORMATION))) {
    
          std::cout << "\n Job CPU limit can not be assigned"; 

          exit(EXIT_FAILURE);
     }


    if (!AssignProcessToJobObject(hJobObject,GetCurrentProcess())) {
   
       std::cout << "\n Job CPU limit can not be assigned"; 

       exit(EXIT_FAILURE);
    }

    BOOL bInJob = FALSE;

    IsProcessInJob(GetCurrentProcess(),NULL,&bInJob);

    if (!bInJob)
    {
       std::cout << "\n The process is not on the job";
               
       exit(EXIT_FAILURE);
    }

}

bool Custom_System_Interface::Create_Process(char * cmd){

     ZeroMemory(&this->siStartInfo, sizeof(STARTUPINFO) );

     this->siStartInfo.cb = sizeof(STARTUPINFO); 

     
     ZeroMemory(&this->piProcInfo, sizeof(PROCESS_INFORMATION) );

     this->return_status = true;

     TCHAR * Cmd_Line = this->Convert_CString_To_TCHAR(cmd);

     this->return_status = CreateProcess( NULL,   // No module name (use command line)
          Cmd_Line,        // Command line
          NULL,           // Process handle not inheritable
          NULL,           // Thread handle not inheritable
          FALSE,          // Set handle inheritance to FALSE
          CREATE_NO_WINDOW | CREATE_PRESERVE_CODE_AUTHZ_LEVEL | 
          HIGH_PRIORITY_CLASS,   // No creation flags
          NULL,           // Use parent's environment block
          NULL,           // Use parent's starting directory
          &this->siStartInfo,            // Pointer to STARTUPINFO structure
          &this->piProcInfo);          // Pointer to PROCESS_INFORMATION structure

     // Start the child process.
    if(!this->return_status)
    {
          printf( "\\n CreateProcess failed \\n");
          return this->return_status;
    }


    // Wait until child process exits.

    this->Child_PID = this->piProcInfo.dwProcessId;

    CloseHandle(this->piProcInfo.hProcess);
    CloseHandle(this->piProcInfo.hThread);

    return this->return_status;
}


bool Custom_System_Interface::TerminateChildProcess(){

     bool termination_status = false;

     HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, this->Child_PID);

     if(processHandle == NULL){

        std::cout << "\n The child process can not be openned";

        std::cout << "\n in process termination process";

        exit(EXIT_FAILURE);
     }
     else{

          BOOL success_status = TerminateProcess(processHandle,this->uExitCode);

          if(success_status == 0){

             std::cout << "\n Build System construction process can not be terminated";

             exit(EXIT_FAILURE);
          }
          else{

               termination_status = true;
          }
     }

     return termination_status;
}


bool Custom_System_Interface::Create_Process_With_Redirected_Stdout(char * cmd){

     SECURITY_ATTRIBUTES saAttr; 
      
     saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
     saAttr.bInheritHandle = TRUE; 
     saAttr.lpSecurityDescriptor = NULL; 

     // Create a pipe for the child process's STDOUT. 

     if (!CreatePipe(&this->g_hChildStd_OUT_Rd, &this->g_hChildStd_OUT_Wr, &saAttr, 0) ){

         std::cout << "\n stdout pipe can not be created";

         exit(EXIT_FAILURE);
     }

     // Ensure the read handle to the pipe for STDOUT is not inherited.

     if (!SetHandleInformation(this->g_hChildStd_OUT_Rd, HANDLE_FLAG_INHERIT, 0) ){

         std::cout << "\n stdout handle information can not be set";

         exit(EXIT_FAILURE);       
     }


     BOOL bSuccess = FALSE; 
 
     // Set up members of the PROCESS_INFORMATION structure. 
 
     ZeroMemory( &this->piProcInfo, sizeof(PROCESS_INFORMATION) );
 
     // Set up members of the STARTUPINFO structure. 
     // This structure specifies the STDIN and STDOUT handles for redirection.
 
     ZeroMemory( &this->siStartInfo, sizeof(STARTUPINFO) );
     this->siStartInfo.cb = sizeof(STARTUPINFO); 
     this->siStartInfo.hStdError  = this->g_hChildStd_OUT_Wr;
     this->siStartInfo.hStdOutput = this->g_hChildStd_OUT_Wr;
     this->siStartInfo.dwFlags |= STARTF_USESTDHANDLES;
 
     // Create the child process. 
    
     TCHAR * Cmd_Line = this->Convert_CString_To_TCHAR(cmd);

     bSuccess = CreateProcess(NULL, 
      Cmd_Line,     // command line 
      NULL,          // process security attributes 
      NULL,          // primary thread security attributes 
      TRUE,          // handles are inherited 
      CREATE_NO_WINDOW, // creation flags 
      NULL,          // use parent's environment 
      NULL,          // use parent's current directory 
      &this->siStartInfo,  // STARTUPINFO pointer 
      &this->piProcInfo);  // receives PROCESS_INFORMATION 
   
      // If an error occurs, exit the application. 
      if ( ! bSuccess ) {

          std::cout << "\n The child process can not be created";

          exit(EXIT_FAILURE);
      }
      else 
      {
         // Close handles to the child process and its primary thread.
         // Some applications might keep these handles to monitor the status
         // of the child process, for example. 

         CloseHandle(this->piProcInfo.hProcess);
         CloseHandle(this->piProcInfo.hThread);
      
         // Close handles to the stdin and stdout pipes no longer needed by the child process.
         // If they are not explicitly closed, there is no way to recognize that the child process has ended.
      
         CloseHandle(this->g_hChildStd_OUT_Wr);      
      }

     // Get a handle to an input file for the parent. 
     // This example assumes a plain text file and uses string output to verify data flow. 
    
     this->DeterminePipePath();


     if(this->FileManager.Is_Path_Exist(this->GetPipePath_StdStr()))
     {
        this->FileManager.Delete_File(this->GetPipePath_StdStr());
     }

     TCHAR * pipePath = this->GetPipePath();

     this->g_hInputFile = CreateFile(
       pipePath, 
       GENERIC_READ, 
       0, 
       NULL, 
       CREATE_ALWAYS,
       FILE_ATTRIBUTE_READONLY, 
       NULL); 

   if ( this->g_hInputFile == INVALID_HANDLE_VALUE ){

        std::cout << "\n pipe file can not be created";

        exit(EXIT_FAILURE);
   }
 
   CloseHandle(this->g_hInputFile);


   return 0; 
}


void Custom_System_Interface::ReadFromPipe(void) 

     // Read output from the child process's pipe for STDOUT
     // and write to the parent process's pipe for STDOUT.
     // Stop when there is no more data.
{ 
     BOOL bSuccess = FALSE;

     HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

     for (;;) 
     { 
        bSuccess = ReadFile(this->g_hChildStd_OUT_Rd,this->chBuf, this->bufsize, &this->dwRead, NULL);
        if( ! bSuccess || this->dwRead == 0 ) break; 

        bSuccess = WriteFile(hParentStdOut,this->chBuf, 
                           this->dwRead, &this->dwWritten, NULL);

        if (! bSuccess ) break; 
     } 
} 
 

void Custom_System_Interface::DeterminePipePath(){

     if(this->StdOutPipe != nullptr){

          delete [] this->StdOutPipe;

          this->StdOutPipe = nullptr;
     }

     CHAR Buffer[this->bufsize];

     GetCurrentDirectory(this->bufsize,Buffer);

     char PipeName [] = "CBuild_StdOut.txt";

     size_t dir_size = strlen(Buffer);

     
     for(size_t i=0;i<dir_size;i++){

        this->std_str_pipe_path.push_back(Buffer[i]);
     }

     if(this->std_str_pipe_path.back()!= '\\'){

        this->std_str_pipe_path.push_back('\\');
     }

     for(size_t i=0;i<dir_size;i++){

        this->std_str_pipe_path.push_back(PipeName[i]);
     }

     this->std_str_pipe_path.shrink_to_fit();

     size_t path_size = this->std_str_pipe_path.length();


     this->StdOutPipe = new TCHAR [2*path_size];

     size_t index = 0;

     for(size_t i=0;i<path_size;i++){

         this->StdOutPipe[index] = this->std_str_pipe_path[i];

         index++;
     }

     this->StdOutPipe[index] = _T('\0');
}



void Custom_System_Interface::SetChildProcess_For_StdOut_Redirection(){
 
     this->hStdout = GetStdHandle(STD_OUTPUT_HANDLE); 
     this->hStdin  = GetStdHandle(STD_INPUT_HANDLE); 

     if ((this->hStdout == INVALID_HANDLE_VALUE) || (this->hStdin == INVALID_HANDLE_VALUE)){

         exit(EXIT_FAILURE); 
     } 
}

void Custom_System_Interface::WriteChildProcess_StdOutput(){

     BOOL bSuccess; 

     for (;;){
       
       // Write to standard output and stop on error.
        bSuccess = WriteFile(this->hStdout,this->chBuf,this->dwRead, &this->dwWritten, NULL);    
        if (! bSuccess || this->dwRead == 0) 
         break; 

      } 
}


TCHAR * Custom_System_Interface::Convert_CString_To_TCHAR(char * cmd){

     if(this->TCHAR_string != nullptr){

          delete [] this->TCHAR_string;

          this->TCHAR_string = nullptr;
     }

     size_t cmd_size= strlen(cmd);

     this->TCHAR_string = new TCHAR[2*cmd_size];

     for(size_t i=0;i<2*cmd_size;i++){

         this->TCHAR_string[i] = _T('\0');
     }

     size_t index = 0;

     for (size_t i = 0; i < cmd_size; i++) {
     
          this->TCHAR_string[index] =cmd[i];

          index++;
     }

     this->TCHAR_string[index] = _T('\0');

     return this->TCHAR_string;
}


TCHAR * Custom_System_Interface::GetPipePath(){

     return this->StdOutPipe;
}


std::string Custom_System_Interface::GetPipePath_StdStr(){

     return this->std_str_pipe_path;
}
