

#include <iostream>
#include <cstring>
#include "Auto_MakeFile_Builder.h"

#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"


int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Project_Files_Lister File_Lister(argv[1],'w');

    File_Lister.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Collect_Dependency_Information();


    Auto_MakeFile_Builder Make_Builder(argv[1],'w');

    Make_Builder.Receive_Project_Files_Lister(&File_Lister);

    Make_Builder.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    Make_Builder.Build_Make_Files();

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
