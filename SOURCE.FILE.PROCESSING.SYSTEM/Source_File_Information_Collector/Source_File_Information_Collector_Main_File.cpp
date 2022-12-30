



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Information_Collector.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    char * project_repo_dir = Des_Reader.Get_Repo_Directory_Location();

    char * warehouse_path   = Des_Reader.Get_Warehouse_Location();


    Project_Files_Lister Dir_Lister;

    Dir_Lister.Determine_Git_Repo_Info(&Des_Reader);

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    std::cout << "\n src_file_num:" << src_file_num;


    Source_File_Information_Collector Information_Collector(argv[1]);

    if(src_file_num > 0){

       Information_Collector.Collect_Make_File_Data();

       Information_Collector.Print_Header_Data();
    }


    int data_size = Information_Collector.Get_Compiler_Data_Size();

    Compiler_Data_CString * Data_Pointer = Information_Collector.Get_Compiler_Data();

    Information_Collector.Clear_Dynamic_Memory();

    return 0;
}
