

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
}

Custom_System_Interface::Custom_System_Interface(const Custom_System_Interface & arg){

}


Custom_System_Interface::~Custom_System_Interface(){


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




     STARTUPINFO si;
     PROCESS_INFORMATION pi;

     ZeroMemory( &si, sizeof(si) );
     si.cb = sizeof(si);
     ZeroMemory( &pi, sizeof(pi) );

     this->return_status = true;

     this->return_status = CreateProcess( NULL,   // No module name (use command line)
          cmd,        // Command line
          NULL,           // Process handle not inheritable
          NULL,           // Thread handle not inheritable
          FALSE,          // Set handle inheritance to FALSE
          CREATE_NO_WINDOW | CREATE_PRESERVE_CODE_AUTHZ_LEVEL | HIGH_PRIORITY_CLASS | CREATE_NEW_PROCESS_GROUP,              // No creation flags
          NULL,           // Use parent's environment block
          NULL,           // Use parent's starting directory
          &si,            // Pointer to STARTUPINFO structure
          &pi );          // Pointer to PROCESS_INFORMATION structure

     // Start the child process.
    if(!this->return_status)
    {
          printf( "\\n CreateProcess failed \\n");
          return this->return_status;
    }


    // Wait until child process exits.
    WaitForSingleObject( pi.hProcess, INFINITE );

    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    return this->return_status;
}
