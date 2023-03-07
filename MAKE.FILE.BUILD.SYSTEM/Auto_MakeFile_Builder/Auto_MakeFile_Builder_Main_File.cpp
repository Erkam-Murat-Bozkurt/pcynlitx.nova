

#include <iostream>
#include <cstring>
#include "Auto_MakeFile_Builder.h"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Auto_MakeFile_Builder Make_Builder(argv[1],'w');

    Make_Builder.Build_Make_Files();

    std::cout << "\n The end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
