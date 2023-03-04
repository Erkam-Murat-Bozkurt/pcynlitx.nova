
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }



    Project_Files_Lister File_Lister(argv[1],'w');

    File_Lister.Determine_Git_Repo_Info();

    int dir_number = File_Lister.Get_Source_File_Number();

    Make_File_Builder File_Builder(argv[1],'w');

    if(dir_number > 0){

       File_Builder.Build_MakeFile(0);
    }

    return 0;
}
