




#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Compiler_Data_Extractor.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Source_File_Information_Collector Information_Collector(argv[1],'w');

    Information_Collector.Collect_Dependency_Data();


    std::vector<Headers_Data> * ptr = Information_Collector.Get_Dependency_Data_Address();

    std::string wr_hdr =  Information_Collector.Get_Warehouse_Headers_Dir();



    Source_File_Compiler_Data_Extractor Compiler_Data_Extractor(argv[1],'w');

    Compiler_Data_Extractor.Receive_Dependency_Data(ptr,wr_hdr);

    Compiler_Data_Extractor.Extract_Compiler_Data();


    std::vector<Compiler_Data> * data_ptr = Compiler_Data_Extractor.Get_Compiler_Data_Address();

    size_t data_size = data_ptr->size();

    for(size_t i=0;i<data_size;i++){

        Compiler_Data temp = data_ptr->at(i);

        std::cout << "\n repo_path            :" << temp.repo_path;
        std::cout << "\n header_name          :" << temp.header_name;
        std::cout << "\n object_file_name     :" << temp.object_file_name;

        std::cout << "\n";

        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k];
        }

        std::cout << "\n";

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n\n\n";
    }


    Compiler_Data_Extractor.Clear_Dynamic_Memory();

    Information_Collector.Clear_Dynamic_Memory();



    std::string path = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";

    Information_Collector.Extract_Dependency_Data(path);


    wr_hdr = Information_Collector.Get_Warehouse_Headers_Dir();

    ptr = Information_Collector.Get_Dependency_Data_Address();


    Compiler_Data_Extractor.Receive_Dependency_Data(ptr,wr_hdr);

    Compiler_Data_Extractor.Extract_Compiler_Data(path);


    data_ptr = Compiler_Data_Extractor.Get_Compiler_Data_Address();

    data_size = data_ptr->size();

    std::cout << "\n\n DATA FOR PATH:" << path;



    for(size_t i=0;i<data_size;i++){

        Compiler_Data temp = data_ptr->at(i);

        std::cout << "\n repo_path            :" << temp.repo_path;
        std::cout << "\n header_name          :" << temp.header_name;
        std::cout << "\n object_file_name     :" << temp.object_file_name;
        std::cout << "\n";


        int inc_num = temp.inclusion_number;

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header:" << temp.included_headers[k];
        }

        for(int k=0;k<inc_num;k++){

            std::cout << "\n includeded header path:" << temp.included_headers_paths[k];
        }
        std::cout << "\n";

        std::cout << "\n priority:" << temp.priority;
        std::cout << "\n rcr_srch_complated:" << temp.rcr_srch_complated;

        std::cout << "\n\n\n\n\n";
    }

    Compiler_Data_Extractor.Clear_Object_Memory();

    return 0;
}
