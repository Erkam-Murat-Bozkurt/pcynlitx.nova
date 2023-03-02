

#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_Builder.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 4){

       std::cout << "\n The usage: Executable_MakeFile_Builder.exe <Descriptor File Path>";

       std::cout << " <main file path> <exe file name>";

       std::cout << "\n\n";

       exit(0);
    }


    Executable_MakeFile_Builder File_Builder(argv[1],'w');


    File_Builder.Update_Warehaouse_Headers();

    File_Builder.Build_MakeFile(argv[2],argv[3]);
    

    std::cout << "\n The make file for executable file constructed..";

    std::cout << "\n\n";

    return 0;
}
