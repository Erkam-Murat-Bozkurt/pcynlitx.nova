


#include <iostream>
#include <cstring>
#include "Project_Script_Writer.h"
#include "Descriptor_File_Reader.hpp"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Project_Script_Writer.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_File_Reader;

    Des_File_Reader.Read_Descriptor_File(argv[1]);

    Project_Script_Writer Script_Writer;

    Script_Writer.Build_Compiler_Script(&Des_File_Reader);

    std::cout << "\n The project compiler script has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
