



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


    Source_File_Information_Collector Information_Collector(argv[1],'w');

    Information_Collector.Extract_Dependency_Data();

    size_t data_size = Information_Collector.Get_Dependency_Data_Size();


    std::vector<Headers_Data> * vec_Pointer = Information_Collector.Get_Headers_Data_Address();


    for(size_t i=0;i<data_size;i++){

        Headers_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Repo path       :" << temp.repo_path;
        std::cout << "\n Header name     :" << temp.header_name;

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k];
        }

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n";
    }

    Information_Collector.Clear_Dynamic_Memory();

    std::string path = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";


    Information_Collector.Extract_Dependency_Data(path);

    data_size = Information_Collector.Get_Dependency_Data_Size();

    vec_Pointer = Information_Collector.Get_Headers_Data_Address();


    for(size_t i=0;i<data_size;i++){

        Headers_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n repo_path       :" << temp.repo_path;
        std::cout << "\n header_name     :" << temp.header_name;

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k];
        }

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n";
    }


    Information_Collector.Clear_Dynamic_Memory();

    Information_Collector.Extract_Dependency_Data();


    data_size   = Information_Collector.Get_Dependency_Data_Size();

    vec_Pointer = Information_Collector.Get_Headers_Data_Address();


    for(size_t i=0;i<data_size;i++){

        Headers_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Repo path       :" << temp.repo_path;
        std::cout << "\n Header name     :" << temp.header_name;

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k];
        }

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n";
    }

    return 0;
}
