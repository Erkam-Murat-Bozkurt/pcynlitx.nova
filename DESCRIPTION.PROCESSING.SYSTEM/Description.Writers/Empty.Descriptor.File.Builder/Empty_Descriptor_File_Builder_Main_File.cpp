



#include <iostream>
#include <cstring>
#include "Empty_Descriptor_File_Builder.hpp"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Empty_Descriptor_File_Builder.exe <path>";

       std::cout << "\n";

       exit(0);
    }

    Empty_Descriptor_File_Builder Emp_Builder;

    Emp_Builder.Build_Empty_File(argv[1]);

    std::cout << "\n The empty descriptor file has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
