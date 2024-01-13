

#include <iostream>
#include "Custom_System_Interface.h"

int main(int argc, char *argv[]){
    
    std::cout << "\n This is a message from child process";

    Custom_System_Interface SysInt;

    SysInt.WriteChildProcess_StdOutput();

    SysInt.WriteChildProcess_StdError();

    return 0;
}