



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Determiner.exe <Descriptor File Path> ";

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

    std::cout << "\n TOTAL SOURCE FILE NUMBER:" << src_file_num;


    Source_File_Information_Collector Info_Collector;

    if(src_file_num > 0){

      Info_Collector.Receive_Descriptor_File_Reader(&Des_Reader);

      Info_Collector.Receive_Git_Record_Data(&Git_Data_Receiver);

      Info_Collector.Receive_Source_File_Info(&Dir_Lister);

      Info_Collector.Collect_Make_File_Data();

    }

    Source_File_Dependency_Determiner Dep_Determiner;

    if(src_file_num > 0){

       Dep_Determiner.Receive_Source_File_Information_Collector(&Info_Collector);

       Dep_Determiner.Determine_Dependencies();

       Dep_Determiner.Print_Compiler_Orders();
    }

    return 0;
}
