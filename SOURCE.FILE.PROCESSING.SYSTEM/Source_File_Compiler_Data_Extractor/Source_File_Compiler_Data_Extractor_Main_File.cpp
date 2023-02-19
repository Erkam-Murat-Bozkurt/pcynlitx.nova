




#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Compiler_Data_Extractor.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"



void print_compiler_data(std::vector<Compiler_Data> * data_ptr);



int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Compiler_Data_Extractor.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Source_File_Dependency_Selector Dep_Selector(argv[1],'w');

    Dep_Selector.Determine_Source_File_Dependencies();

    

    std::vector<std::vector<Header_Dependency>> * ptr = Dep_Selector.Get_Dependency_List_Adress();

    std::string wr_hdr =  Dep_Selector.Get_Warehouse_Headers_Dir();



    Source_File_Compiler_Data_Extractor Compiler_Data_Extractor(argv[1],'w');

    Compiler_Data_Extractor.Receive_Dependency_Data(ptr,wr_hdr);

    Compiler_Data_Extractor.Extract_Compiler_Data();


    std::vector<Compiler_Data> * data_ptr = Compiler_Data_Extractor.Get_Compiler_Data_Address();

    print_compiler_data(data_ptr);

    Compiler_Data_Extractor.Clear_Dynamic_Memory();

    Dep_Selector.Clear_Dynamic_Memory();





    std::string path = "D:\\PCYNLITX.BUILD.TEST\\WAREHOUSE\\PROJECT.HEADER.FILES\\Thread_Manager_Builder.h";

    Dep_Selector.Determine_Source_File_Dependencies(path);

    
    std::vector<std::vector<Header_Dependency>> * s_ptr  = Dep_Selector.Get_Dependency_List_Adress();


    Compiler_Data_Extractor.Receive_Dependency_Data(s_ptr,wr_hdr);

    Compiler_Data_Extractor.Extract_Compiler_Data(path);



    data_ptr = Compiler_Data_Extractor.Get_Compiler_Data_Address();

    std::cout << "\n\n DATA FOR PATH:" << path;

    print_compiler_data(data_ptr);


    Compiler_Data_Extractor.Clear_Object_Memory();

    Dep_Selector.Clear_Object_Memory();

    return 0;
}


void print_compiler_data(std::vector<Compiler_Data> * data_ptr){

     size_t data_size = data_ptr->size();

     for(size_t i=0;i<data_size;i++){

         Compiler_Data temp = data_ptr->at(i);

         std::cout << "\n repo_path            :" << temp.header_repo_path;
         std::cout << "\n header_name          :" << temp.header_name;
         std::cout << "\n object_file_name     :" << temp.object_file_name;

         std::cout << "\n";

         size_t head_size = temp.dependent_headers.size();

         for(int k=0;k<head_size;k++){

             std::cout << "\n included header:" << temp.dependent_headers[k];
         }

         size_t path_size = temp.dependent_headers.size();

         std::cout << "\n";


         for(int k=0;k<path_size;k++){

             std::cout << "\n included header path:" << temp.dependent_headers_paths[k];
         } 

         std::cout << "\n";

         std::cout << "\n priority:" << temp.priority;

         std::cout << "\n\n\n\n\n";
    }
}