
#include <iostream>
#include "Custom_System_Interface.h"


int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;

    SysInt.CreateNamedPipe_From_Parent();

    std::cout << "\n Pipe created";
    std::cin.get();

    SysInt.Create_Process_For_Named_Pipe(argv[1]);

    SysInt.ReadFromPipe();

    //std::cout << "\n Is child process still alive:" << SysInt.IsChildProcess_Still_Alive();

    std::cout << "\n The end of the parent class\n\n";

    return 0;
}