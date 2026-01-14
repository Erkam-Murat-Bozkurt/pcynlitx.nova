


#include <iostream>
#include <cstring>
#include "Directory_Enumerator.h"

void Place_String(char ** Pointer, const char * String);

int main(int argc, char ** argv){

    size_t dir_path_size = strlen(argv[1]);

    char * path = new char [2*dir_path_size];

    for(size_t i=0;i<2*dir_path_size;i++){

        path[i] = '\0';
    }

    for(size_t i =0;i<dir_path_size;i++){

        path[i] = argv[1][i];
    }

    Directory_Enumerator Enumarator;

    Enumarator.List_Files_On_Directory(path);

    int file_num = Enumarator.Get_File_Number();

    std::cout << "\n file_num:" << file_num;

    std::cin.get();

    char **  file_list = Enumarator.Get_File_List();

    for(int i=0;i<file_num;i++){

        std::cout << "\n file_list[" << i << "]: " << file_list[i];
    }

    delete [] path;

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below

void Place_String(char ** Pointer, const char * String){

     int String_Size = strlen(String);

     for(int i=0;i<String_Size;i++){

          (*Pointer)[i] = String[i];
     }

     (*Pointer)[String_Size] = '\0';
}
