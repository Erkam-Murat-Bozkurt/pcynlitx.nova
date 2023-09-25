






#include <iostream>
#include <cstring>
#include <vector>
#include "Dependency_Data_Extractor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: Source_File_Dependency_Selector.exe <Descriptor File Path> <Src File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();



    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Data_Processor);

    Code_Rd.Read_Project_Source_Code_Files();


    std::cout << "\n\n";

    std::cout << "\n Code reading complated..";

    //std::string path =  "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\SERVER.CLASS.BUILDER\\Thread_Manager_Builder\\Thread_Manager_Builder.cpp";

    Dependency_Data_Extractor Dep_Data_Extractor('w');

    Dep_Data_Extractor.Receive_Source_Code_Reader(&Code_Rd);

    Dep_Data_Extractor.Extract_Dependency_Tree(argv[2]);


    std::vector<Search_Data> * Data_Ptr = Dep_Data_Extractor.Get_Search_Data();

    for(size_t i=0;i<Data_Ptr->size();i++){

        std::cout << "\n";
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->at(i).name;
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->at(i).include_decleration;
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->at(i).path;
    }


    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
