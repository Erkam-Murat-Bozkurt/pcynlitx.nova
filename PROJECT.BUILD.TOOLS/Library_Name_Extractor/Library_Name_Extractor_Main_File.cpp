



#include <iostream>
#include <cstring>
#include "Library_Name_Extractor.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n usage: .\\Library_Name_Extractor.exe <directory path>";

       std::cout << "\n\n";
    }

    size_t dir_path_size = strlen(argv[1]);

    char * path = new char [2*dir_path_size];

    for(size_t i=0;i<2*dir_path_size;i++){

        path[i] = '\0';
    }

    for(size_t i =0;i<dir_path_size;i++){

        path[i] = argv[1][i];
    }

    Library_Name_Extractor Extractor;

    Extractor.Determine_Library_Names(path);

    int archive_files_number = Extractor.Get_Arcive_Files_Number();

    if(archive_files_number){

       std::cout << "\n\n";

       std::cout << "\n THE ARCHIVE FILES:";

       for(int i=0;i<archive_files_number;i++){

           std::cout << "\n File[" << i << "]:" << Extractor.Get_Archive_File(i);
       }
    }

    int dll_files_number = Extractor.Get_DLL_Files_Number();

    if(dll_files_number){

       std::cout << "\n\n";

       std::cout << "\n THE DLL FILES:";

       for(int i=0;i<dll_files_number;i++){

           std::cout << "\n File[" << i << "]:" << Extractor.Get_Dll_File(i);
        }
    }

    delete [] path;

    std::cout << "\n\n";

    return 0;
}
