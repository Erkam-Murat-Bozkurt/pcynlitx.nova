

#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_Builder.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 5){

       std::cout << "\n The usage: Executable_MakeFile_Builder.exe <Descriptor File Path>";

       std::cout << " <main file path> <exe file name> <build strategy>";

       std::cout << "\n\n";

       exit(0);
    }

    if(*argv[4] != 'a'){

        if(*argv[4] != 's'){

            std::cout << "\nThe build strategy must be one of the following characters:";
            std::cout << "\n";
            std::cout << "\na: Advanced build";
            std::cout << "\ns: Simple build";
            std::cout << "\n\n";

            exit(0);
        }
    }


    Executable_MakeFile_Builder File_Builder(argv[1],'w');

    File_Builder.Build_MakeFile(argv[2],argv[3],*argv[4]);
    

    std::cout << "\nThe make file for executable file constructed..";

    std::cout << "\n\n";

    return 0;
}
