
#include <iostream>
#include "Custom_System_Interface.h"


int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;

    SysInt.Create_Process(argv[1]);

    SysInt.TerminateChildProcess();

    std::cout << "\n Is child process still alive:" << SysInt.IsChildProcess_Still_Alive();

    std::cout << "\n The end of the parent class\n\n";

    return 0;
}