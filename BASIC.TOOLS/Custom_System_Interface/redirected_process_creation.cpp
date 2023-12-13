
#include <iostream>
#include "Custom_System_Interface.h"


int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;

    SysInt.Create_Process_With_Redirected_Stdout(argv[1]);

    SysInt.ReadFromPipe();

    std::cout << "\n The end of the parent class\n\n";

    return 0;
}