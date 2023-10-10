



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_Modification_Receiver.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"


void Print_Advance_Data(std::vector<Compiler_Data> * ptr);
void Print_Simple_Data(const Simple_Source_File_Dependency * data_ptr);



int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Determiner.exe <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);


    if(argc < 3){

       Dep_Determiner.Collect_Dependency_Information();

       std::vector<Compiler_Data> * ptr = Dep_Determiner.Get_Compiler_Data_Address();

       Print_Advance_Data(ptr);         
    }

    if(argc > 2){

       if(*argv[3] == 'a'){

          Dep_Determiner.Collect_Dependency_Information(argv[2]);

          std::vector<Compiler_Data> * ptr = Dep_Determiner.Get_Compiler_Data_Address();

          Print_Advance_Data(ptr);

       }
       else{

         if(*argv[3] == 's'){

            Dep_Determiner.Simple_Dependency_Determination_For_Single_Source_File(argv[2]);

            const Simple_Source_File_Dependency * data_ptr = Dep_Determiner.Get_Simple_File_Dependencies();

            Print_Simple_Data(data_ptr);
         }
         else{

              std::cout << "\n You must enter an option";
         }
       }
    }

    std::cout << "\n The end of the program";

    return 0;
}


void Print_Advance_Data(std::vector<Compiler_Data> * ptr){

    for(size_t i=0;i<ptr->size();i++){

        std::cout << " \n\n\n";
        std::cout << "\n source file name:" << ptr->at(i).source_file_name;
        std::cout << "\n object file name:" << ptr->at(i).object_file_name;
        std::cout << "\n source file path:" << ptr->at(i).source_file_path;

        size_t header_number = ptr->at(i).dependent_headers.size();

        std::cout << "\n priority:" << ptr->at(i).priority;

        std::cout << "\n header_number:" << header_number;        

        std::cout << "\n dependent headers:";

        for(size_t j=0;j<header_number;j++){

            std::cout << "\n Header: " << j << "-:" << ptr->at(i).dependent_headers.at(j);
        }
    }

    std::cout << "\n\n";
}



void Print_Simple_Data(const Simple_Source_File_Dependency * data_ptr){
     
     std::cout << "\n source_file_nam                 :" << data_ptr->source_file_name;
     std::cout << "\n Combined_Header_Name            :" << data_ptr->Combined_Header_Name;
     std::cout << "\n dir                             :" << data_ptr->dir;
     std::cout << "\n object_file_name                :" << data_ptr->object_file_name;
     std::cout << "\n source_file_name_without_ext    :" << data_ptr->source_file_name_without_ext;
     std::cout << "\n source_file_path                :" << data_ptr->source_file_path;
     std::cout << "\n src_sys_dir                     :" << data_ptr->src_sys_dir;
     std::cout << "\n src_git_record_dir              :" << data_ptr->src_git_record_dir;

     for(size_t i=0;i<data_ptr->Dependent_Header_Names.size();i++){

         std::cout << "\n Dependent Header Name ["<< i << "]:"  << data_ptr->Dependent_Header_Names.at(i);
     }

     for(size_t i=0;i<data_ptr->Dependent_Header_Paths.size();i++){

         std::cout << "\n Dependent Header Paths ["<< i << "]:" 
        
         << data_ptr->Dependent_Header_Paths.at(i);
     }

     for(size_t i=0;i<data_ptr->Include_Declerations.size();i++){

         std::cout << "\n Include Decleration ["<< i << "]:" 
        
         << data_ptr->Include_Declerations.at(i);
    }

    std::cout << "\n\n";
}