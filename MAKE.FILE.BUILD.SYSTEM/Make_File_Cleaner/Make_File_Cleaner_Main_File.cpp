

#include <iostream>
#include <cstring>
#include "Make_File_Cleaner.hpp"
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Cleaner.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Project_Files_Lister File_Lister(argv[1],'w');

    File_Lister.Determine_Git_Repo_Info();

    int dir_number = File_Lister.Get_Source_File_Number();

    Make_File_Cleaner Mk_Cleaner(argv[1],'w');

    if(dir_number > 0){

       Mk_Cleaner.Clear_Make_Files_Exist_On_Repo();

    }

    return 0;
}
