
#include <iostream>
#include "Custom_System_Interface.h"


int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;

    SysInt.Create_Process_With_Redirected_Stdout(argv[1]);

    SysInt.ReadFromPipe();


    //std::cout << "\n The cild process ID:" << SysInt.dwPid;

    /*

    UINT uExitCode=0;

    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE,SysInt.dwPid);

    if(hProcess == NULL){

        std::cout << "\n The process object can not be oppenned";

        std::cout << "\n Error Code:" << GetLastError();
    }
    else{

        //CloseHandle(SysInt.g_hInputFile);

        BOOL Status = TerminateProcess(hProcess,uExitCode);

        if(Status == 0){

           std::cout << "\n The child process can not be terminated";

           std::cout << "\n Exit Code:" << uExitCode;

           std::cout << "\n Error Code:" << GetLastError();
        }
        else{

           std::cout << "\n The child process terminated";

           std::cout << "\n Exit Code:" << uExitCode;
        }
    }

    */


    /*

    BOOL Status = TerminateProcess(hProcess,uExitCode);

    if(Status == 0){

       std::cout << "\n The child process can not be terminated";

       std::cout << "\n Exit Code:" << uExitCode;

       std::cout << "\n Error Code:" << GetLastError();
    }
    else{

       std::cout << "\n The child process terminated";

       std::cout << "\n Exit Code:" << uExitCode;
    }

    */

    std::cout << "\n The end of the parent class\n\n";

    return 0;
}