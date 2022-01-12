
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    Make_File_Builder File_Builder;

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Headers Location>";

       std::cout << "\n\n";

       exit(0);
    }

    size_t Headers_Location_String_Size = strlen(argv[1]);

    char * Header_Files_Location  = new char [10*Headers_Location_String_Size];

    Place_String(&Header_Files_Location,argv[1]);

    File_Builder.Build_MakeFile(Header_Files_Location);

    delete [] Header_Files_Location;

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
