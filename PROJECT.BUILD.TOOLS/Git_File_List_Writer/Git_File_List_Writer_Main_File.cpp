




#include <iostream>
#include <cstring>
#include "Git_File_List_Writer.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_File_List_Writer Writer(argv[1]);

    Writer.Write_Git_Repo_List_File();

    std::cout << "\n Repo file list constructed..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}
