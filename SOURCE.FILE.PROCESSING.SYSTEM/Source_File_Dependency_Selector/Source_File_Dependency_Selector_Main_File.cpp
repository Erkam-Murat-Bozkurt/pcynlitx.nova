




#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Dependency_Selector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Selector.exe <Descriptor File Path> ";

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



    Source_File_Information_Collector Info_Collector;

    if(src_file_num > 0){

       Info_Collector.Receive_Descriptor_File_Reader(&Des_Reader);

       Info_Collector.Collect_Make_File_Data();
    }

    char path [] = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";

    Source_File_Dependency_Selector Dep_Selector;

    if(src_file_num > 0){

      Dep_Selector.Receive_Source_File_Information_Collector(&Info_Collector);

      Dep_Selector.Determine_Source_File_Dependencies(path);

      Dep_Selector.Print_Dependency_List();
    }

    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
