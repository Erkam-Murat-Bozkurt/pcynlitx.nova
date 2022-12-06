


#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Executable_MakeFile_ComConstructor.exe <Descriptor File Path> ";

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


    Source_File_Information_Collector Information_Collector;

    if(src_file_num > 0){

       Information_Collector.Receive_Descriptor_File_Reader(&Des_Reader);

       Information_Collector.Collect_Make_File_Data();
    }

    Source_File_Dependency_Determiner Dep_Determiner;

    if(src_file_num > 0){

       Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

       Dep_Determiner.Determine_Dependencies();
    }


    char path [] = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\KERNEL.DEVELOPMENT\\Kernel\\Kernel_Main_File.cpp";

    char Exe_Name [] = "Kernel.exe";

    Executable_MakeFile_ComConstructor Command_Constructor;

    if(src_file_num > 0){

      Command_Constructor.Receive_Descriptor_File_Reader(&Des_Reader);

      Command_Constructor.Receive_ExeFileName(Exe_Name);

      Command_Constructor.Receive_DepDeterminer(&Dep_Determiner);

      Command_Constructor.Construct_Compiler_Commands(path);
    }


    char * Compiler_System_Command = Command_Constructor.Get_Compiler_System_Command();

    std::cout << "\n Compiler_System_Command:" << Compiler_System_Command;

    std::cout << "\n\n";

    Dep_Determiner.Clear_Dynamic_Memory();

    Information_Collector.Clear_Dynamic_Memory();

    Command_Constructor.Clear_Dynamic_Memory();

    std::cout << "\n\n The end of the program";

    std::cout << "\n\n";

    return 0;
}
