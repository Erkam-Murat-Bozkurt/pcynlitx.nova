



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

    Information_Collector.Collect_Make_File_Data();


    size_t data_size = Information_Collector.Get_Compiler_Data_Size();

    /*

    for(size_t i=0;i<data_size;i++){

        Compiler_Data Data_Pointer = Information_Collector.Get_Compiler_Data(i);

        std::cout << "\n Data_Pointer.repo_path       :" << Data_Pointer.repo_path;
        std::cout << "\n Data_Pointer.header_name     :" << Data_Pointer.header_name;
        std::cout << "\n Data_Pointer.object_file_name:" << Data_Pointer.object_file_name;

        int inc_num = Data_Pointer.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << Data_Pointer.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << Data_Pointer.included_headers_path[k];
        }

        std::cout << "\n priority:" << Data_Pointer.priority;
        std::cout << "\n rcr_srch_complated:" << Data_Pointer.rcr_srch_complated;

        std::cout << "\n\n\n";
    }

    */

    std::vector<Compiler_Data> * vec_Pointer = Information_Collector.Get_Compiler_Data_Address();


    for(size_t i=0;i<data_size;i++){

        Compiler_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Data_Pointer.repo_path       :" << temp.repo_path;
        std::cout << "\n Data_Pointer.header_name     :" << temp.header_name;
        std::cout << "\n Data_Pointer.object_file_name:" << temp.object_file_name;

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers_path[k];
        }

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n";
    }

    Information_Collector.Clear_Dynamic_Memory();

    return 0;
}
