


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


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Collect_Dependency_Information();


    Project_Script_Writer Script_Writer(argv[1],'w');

    Script_Writer.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    Script_Writer.Build_Compiler_Script();

    Script_Writer.Clear_Dynamic_Memory();

    std::cout << "\n The project compiler script has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
