



#include <iostream>
#include <cstring>
#include "Header_File_Determiner.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <test_file_path>";

       std::cout << "\n\n";

       exit(0);
    }

    Header_File_Determiner Head_Determiner;

    bool is_header = Head_Determiner.Is_Header(argv[1]);

    if(is_header){

       std::cout << "\n this is an header file..";
    }
    else{

        std::cout << "\n this is not an header file";
    }

    if(is_header){

        Head_Determiner.Determine_Header_File_Directory(argv[1]);

        std::cout << "\n Header Directory:" << Head_Determiner.Get_Header_Directory();
    }

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
