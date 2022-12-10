



#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Collector.hpp"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Project_Script_Writer.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Des_File_Reader.Read_Descriptor_File(argv[1]);

    Script_Data_Collector Scr_Data;

    Scr_Data.Build_Compiler_Script(&Des_File_Reader);

    std::cout << "\n The project compiler script has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
