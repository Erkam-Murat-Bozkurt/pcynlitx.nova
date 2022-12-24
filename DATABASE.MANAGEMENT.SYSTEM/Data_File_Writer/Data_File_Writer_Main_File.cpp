




#include <iostream>
#include <cstring>
#include "Data_File_Writer.hpp"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Data_File_Writer.exe <path>";

       std::cout << "\n";

       exit(0);
    }

    Script_Data Data;

    Data.

    Data_File_Writer Dt_File_Wrt;

    Dt_File_Wrt.Build_Data_File(argv[1]);

    std::cout << "\n The data file has been constructed";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
