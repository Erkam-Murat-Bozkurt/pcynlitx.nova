


#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
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

    Git_File_List_Receiver Git_Data_Receiver;

    Git_Data_Receiver.Receive_Descriptor_File_Reader(&Des_Reader);

    Git_Data_Receiver.Determine_Git_Repo_Info();


    Project_Files_Lister Dir_Lister;

    Dir_Lister.Determine_Git_Repo_Info(&Des_Reader);

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    std::cout << "\n src_file_num:" << src_file_num;


    Executable_MakeFile_DepDeterminer Dep_Determiner;

    if(src_file_num > 0){

       Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

       Dep_Determiner.Receive_Git_Record_Data(&Git_Data_Receiver);

       Dep_Determiner.Receive_Source_File_Info(&Dir_Lister);

       Dep_Determiner.Determine_Dependencies();

    }

    Executable_MakeFile_ComConstructor Command_Constructor;

    Command_Constructor.Receive_DepDeterminer(&Dep_Determiner);

    Command_Constructor.Construct_Compiler_Commands();

    std::cout << "\n Header File List:" << Command_Constructor.Get_Header_File_List();

    std::cout << "\n Object File List:" << Command_Constructor.Get_Object_File_List();

    return 0;
}
