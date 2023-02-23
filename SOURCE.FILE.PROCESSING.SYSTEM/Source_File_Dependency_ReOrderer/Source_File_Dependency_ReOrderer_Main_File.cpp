




#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Dependency_ReOrderer.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_ReOrderer.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Project_Files_Lister Dir_Lister(argv[1],'w');

    Dir_Lister.Determine_Git_Repo_Info();

    int src_file_num = Dir_Lister.Get_Source_File_Number();


    Source_File_Dependency_Selector Dep_Selector(argv[1],'w');


    char path [] = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";


    /*

    if(src_file_num > 0){

      Dep_Selector.Determine_Source_File_Dependencies(path);

      Dep_Selector.Print_Dependency_List();
    }

     */
    
    if(src_file_num > 0){

      Dep_Selector.Determine_Source_File_Dependencies(path);
    }


    Source_File_Dependency_ReOrderer ReOrderer;

    ReOrderer.Receive_Dependency_Data(Dep_Selector.Get_Dependency_List_Adress());

    ReOrderer.Reorder_Dependency_Data();

    ReOrderer.Print_Dependency_Data();

    std::cin.get();

    if(src_file_num > 0){

      Dep_Selector.Determine_Source_File_Dependencies();
    }


    ReOrderer.Receive_Dependency_Data(Dep_Selector.Get_Dependency_List_Adress());

    ReOrderer.Reorder_Dependency_Data();

    ReOrderer.Print_Dependency_Data();

    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
