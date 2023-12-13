

#include <iostream>
#include "Custom_System_Interface.h"

int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;
    
    SysInt.SetChildProcess_For_StdOut_Redirection();

    std::cout << "\n This is a message from child process";

    SysInt.WriteChildProcess_StdOutput();

    return 0;
}