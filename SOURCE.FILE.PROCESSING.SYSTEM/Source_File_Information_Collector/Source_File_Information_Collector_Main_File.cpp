



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Information_Collector.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Information_Collector.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Git_File_List_Receiver Receiver(argv[1],'w');

    Receiver.Determine_Git_Repo_Info();

    int index_size = Receiver.Get_Git_File_Index_Size();


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Receiver);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n The project source codes readed..";

    Source_File_Information_Collector Information_Collector(argv[1],'w');

    Information_Collector.Receive_Source_Code_Reader(&Code_Rd);

    /*

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

    */

    //std::string path = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";


    std::string path = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\SERVER.CLASS.BUILDER\\Thread_Data_Manager_Builder\\Thread_Data_Manager_Builder.cpp";

    Information_Collector.Extract_Dependency_Data(path);

    size_t data_size = Information_Collector.Get_Dependency_Data_Size();

    std::vector<Source_File_Data> * vec_Pointer = Information_Collector.Get_Headers_Data_Address();

    std::cout << "\n data_size:" << data_size;

    for(size_t i=0;i<data_size;i++){

        Source_File_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Source File Name       :" << temp.source_file_name;
        std::cout << "\n Header system path     :" << temp.system_path;

        

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k] << "#";
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k] << "#";
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

        Source_File_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Source File Name       :" << temp.source_file_name;
        std::cout << "\n Header system path     :" << temp.system_path;


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
