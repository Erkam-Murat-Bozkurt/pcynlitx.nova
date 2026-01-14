
#include <iostream>
#include "Custom_System_Interface.h"


int main(int argc, char *argv[]){

    Custom_System_Interface SysInt;

    bool success_status = SysInt.Create_Process_With_Redirected_Stdout(argv[1]);

    if(success_status){

       SysInt.ReadFromPipe();

       std::string out = SysInt.GetAnonymousPipe_String();

       std::cout << out;
    }

    std::cout << "\n The end of the parent class\n\n";

    return 0;
}