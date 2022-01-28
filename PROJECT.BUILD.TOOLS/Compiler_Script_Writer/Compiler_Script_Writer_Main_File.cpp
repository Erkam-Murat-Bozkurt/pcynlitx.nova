


#include <iostream>
#include <cstring>
#include "Compiler_Script_Writer.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Compiler_Script_Writer.exe <repo dir> <warehouse_path>";

       std::cout << "\n";

       exit(0);
    }

    Compiler_Script_Writer Script_Writer;

    Script_Writer.Build_Compiler_Script(argv[1],argv[2]);

    std::cout << "\n The project compiler script has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
