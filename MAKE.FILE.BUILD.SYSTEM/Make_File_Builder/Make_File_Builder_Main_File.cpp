


#include <iostream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <iterator>
#include "Make_File_Builder.h"
#include "MakeFile_Path_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"


void Print_String_Vector(std::vector<std::string> & vec);

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: MakeFile_Path_Determiner.exe <Descriptor File Path> <File Path>";

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
    
    Dep_Determiner.Collect_Dependency_Information();

    std::string src_file_name = "Kernel.cpp";


    std::vector<Compiler_Data> * Compiler_Data_Pointer = Dep_Determiner.Get_Compiler_Data_Address();

    std::unordered_map<std::string, Compiler_Data> DataMap;


    size_t data_size = Compiler_Data_Pointer->size();

    for(size_t i=0;i<data_size;i++){

         std::string source_file_path= Compiler_Data_Pointer->at(i).source_file_path;

         DataMap.insert(std::make_pair(source_file_path,Compiler_Data_Pointer->at(i)));
     }


    Make_File_Builder MK_Builder;

    MK_Builder.Receive_Descriptor_File_Reader(&Des_Reader);

    MK_Builder.Receive_Compiler_Data_Pointer(Compiler_Data_Pointer);

    MK_Builder.Receive_Operating_System('w');
    
    MK_Builder.Receive_DataMap(&DataMap);

    MK_Builder.Build_MakeFile(argv[2]);
       
    MK_Builder.Clear_Object_Memory();

    return 0;
}


void Print_String_Vector(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         std::cout << "\n String[" << i << "]:" << vec.at(i);
     }
}