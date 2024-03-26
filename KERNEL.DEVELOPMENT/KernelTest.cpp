

#include <iostream>
#include <string>
#include "Custom_System_Interface.h"

int main(int argc, char ** argv){


    if(argc < 2){

       std::cout << "\n\n the usage: <exe file for test> <reputation>";

       std::cout << "\n\n";

       exit(0);
    }

    int test_number = std::stoi(argv[1]);



    Custom_System_Interface SysInt;

    char cmd [] = "D:\\Pcynlitx_Build_Platform\\CBuild.exe D:\\PCYNLITX.BUILD.TEST\\Pcb_Descriptor.txt -ip";


    for(int i=0;i<test_number;i++){

       bool success_status = SysInt.Create_Process_With_Redirected_Stdout(cmd);

       if(success_status){

          std::cout << "\n Test Num:" << i;

          SysInt.ReadFromPipe();

          //std::string out = SysInt.GetAnonymousPipe_String();

          //std::cout << out;
       }
       else{

           exit(EXIT_FAILURE);
       }
    }

    std::cout << "\n\n";

    return 0;
}