



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



    char path [] = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\SERVER.CLASS.BUILDER\\Thread_Manager_Builder\\Thread_Manager_Builder.cpp";

    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    //Dep_Determiner.Receive_Source_Code_Reader(&Code_Rd);

    /*

    Dep_Determiner.Collect_Dependency_Information();

    Dep_Determiner.Print_Compiler_Orders();

    Dep_Determiner.Clear_Dynamic_Memory();

    std::cout << "\n\n ---------------------------------------------------------------";


    */

    Dep_Determiner.Collect_Dependency_Information(path);

    //Dep_Determiner.Print_Compiler_Orders();

    //Dep_Determiner.Clear_Dynamic_Memory();

     std::vector<Compiler_Data> * ptr = Dep_Determiner.Get_Compiler_Data_Address();

     for(size_t i=0;i<ptr->size();i++){

        std::cout << "\n source file name:" << ptr->at(i).source_file_name;
        std::cout << "\n object file name:" << ptr->at(i).object_file_name;
        std::cout << "\n source file path:" << ptr->at(i).source_file_path;

        size_t header_number = ptr->at(i).dependent_headers.size();
        
        std::cout << "\n dependent headers:";

        for(size_t j=0;j<header_number;j++){

            std::cout << "\n Header: " << j << "-:" << ptr->at(i).dependent_headers.at(j);
        }
     }


    std::cout << "\n\n";

    //Dep_Determiner.Print_Dependency_List();

    std::cout << "\n The end of the program";

    return 0;
}
