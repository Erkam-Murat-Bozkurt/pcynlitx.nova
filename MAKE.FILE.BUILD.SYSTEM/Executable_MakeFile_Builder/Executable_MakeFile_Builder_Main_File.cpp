

#include <iostream>
#include <cstring>
#include "Executable_MakeFile_Builder.hpp"
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    char * project_repo_dir = Des_Reader.Get_Repo_Directory_Location();

    char * warehouse_path   = Des_Reader.Get_Warehouse_Location();

    Project_Files_Lister File_Lister;

    File_Lister.Determine_Git_Repo_Info(&Des_Reader);

    int dir_number = File_Lister.Get_Source_File_Number();

    Executable_MakeFile_Builder File_Builder;

    if(dir_number > 0){

       File_Builder.Receive_Descriptor_File_Reader(&Des_Reader);

       File_Builder.Receive_Git_Record_Data(&File_Lister);

       File_Builder.Build_MakeFile();

    }

    return 0;
}
