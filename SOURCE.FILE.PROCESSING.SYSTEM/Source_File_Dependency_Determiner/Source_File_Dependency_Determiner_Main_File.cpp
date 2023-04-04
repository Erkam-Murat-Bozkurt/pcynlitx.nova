



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

    Git_File_List_Receiver Git_Data_Receiver(argv[1],'w');

    Git_Data_Receiver.Determine_Git_Repo_Info();


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Git_Data_Receiver);

    Code_Rd.Read_Project_Source_Code_Files();



    char path [] = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\SERVER.CLASS.BUILDER\\Thread_Manager_Builder\\Thread_Manager_Builder.h";

    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Source_Code_Reader(&Code_Rd);

    Dep_Determiner.Collect_Dependency_Information();

    Dep_Determiner.Print_Compiler_Orders();

    std::cin.get();

    Dep_Determiner.Clear_Dynamic_Memory();

    std::cout << "\n\n ---------------------------------------------------------------";

    Dep_Determiner.Collect_Dependency_Information(path);

    Dep_Determiner.Print_Compiler_Orders();

    std::cout << "\n\n";

    //Dep_Determiner.Print_Dependency_List();

    std::cout << "\n The end of the program";

    std::cin.get();

    return 0;
}
