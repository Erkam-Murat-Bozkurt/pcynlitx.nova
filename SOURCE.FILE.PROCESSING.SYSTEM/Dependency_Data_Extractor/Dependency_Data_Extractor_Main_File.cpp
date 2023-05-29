






#include <iostream>
#include <cstring>
#include <vector>
#include "Dependency_Data_Extractor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Selector.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Project_Files_Lister Dir_Lister(argv[1],'w');

    Dir_Lister.Determine_Git_Repo_Info();

    int src_file_num = Dir_Lister.Get_Source_File_Number();


    Git_File_List_Receiver Git_Data_Receiver(argv[1],'w');

    Git_Data_Receiver.Determine_Git_Repo_Info();


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Git_Data_Receiver);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n Code reading complated..";

    std::string path =  "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\SERVER.CLASS.BUILDER\\Thread_Manager_Builder\\Thread_Manager_Builder.h";

    Dependency_Data_Extractor Dep_Determiner(argv[1],'w');

    if(src_file_num > 0){

      Dep_Determiner.Receive_Source_Code_Reader(&Code_Rd);

      Dep_Determiner.Extract_Dependency_Tree(path);
    }

    std::vector<Search_Data> * Data_Ptr = Dep_Determiner.Get_Search_Data();

    for(size_t i=0;i<Data_Ptr->size();i++){

        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->at(i).name;
    }


    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
