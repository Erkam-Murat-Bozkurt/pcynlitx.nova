
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    Make_File_Builder File_Builder;

    if(argc < 3){

       std::cout << "\n The usage: Make_File_Builder.exe <Header File Path> ";

       std::cout << "<Proj. Warehouse Location>";

       std::cout << "\n\n";

       exit(0);
    }

    File_Builder.Build_MakeFile(argv[1],argv[2],argv[3]);

    return 0;
}

// The Function that places the location Informations listed in below

void Place_String(char ** Pointer, char * String){

     size_t String_Size = strlen(String);

     for(size_t i=0;i<String_Size;i++){

          (*Pointer)[i] = String[i];
     }

     (*Pointer)[String_Size] = '\0';
}
