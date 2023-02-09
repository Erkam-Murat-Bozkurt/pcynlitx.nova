



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

    Descriptor_File_Reader Des_Reader(argv[1]);

    Des_Reader.Read_Descriptor_File();

    Project_Files_Lister Dir_Lister(argv[1],'w');

    Dir_Lister.Determine_Git_Repo_Info();

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    Dir_Lister.~Project_Files_Lister();

    std::cout << "\n TOTAL SOURCE FILE NUMBER:" << src_file_num;

    std::string path = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    if(src_file_num > 0){

       Dep_Determiner.Determine_Dependencies();

       Dep_Determiner.Print_Compiler_Orders();

       Dep_Determiner.Clear_Dynamic_Memory();

       std::cout << "\n\n ---------------------------------------------------------------";

       Dep_Determiner.Determine_Particular_Source_File_Dependencies(path);

       Dep_Determiner.Print_Dependency_List();
    }

    return 0;
}
