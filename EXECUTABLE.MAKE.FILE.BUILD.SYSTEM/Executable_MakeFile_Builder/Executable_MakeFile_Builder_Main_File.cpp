

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

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    char * project_repo_dir = Des_Reader.Get_Repo_Directory_Location();

    char * warehouse_path   = Des_Reader.Get_Warehouse_Location();

    Git_File_List_Receiver Git_Data_Receiver;

    Git_Data_Receiver.Receive_Descriptor_File_Reader(&Des_Reader);

    Git_Data_Receiver.Determine_Git_Repo_Info();


    Project_Files_Lister Dir_Lister;

    Dir_Lister.Determine_Git_Repo_Info(&Des_Reader);

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    Executable_MakeFile_Builder File_Builder;

    if(src_file_num > 0){

       File_Builder.Receive_Descriptor_File_Path(argv[1]);

       File_Builder.Receive_Git_Record_Data(&Git_Data_Receiver);

       File_Builder.Receive_Source_File_Info(&Dir_Lister);

       File_Builder.Build_MakeFile(argv[2],argv[3]);
    }

    std::cout << "\n The make file for executable file constructed..";

    std::cout << "\n\n";

    return 0;
}
