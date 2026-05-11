






#ifndef CMAKE_TARGET_LIST_DATA_PROCESSOR_HPP
#define CMAKE_TARGET_LIST_DATA_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>     //for using the function sleep
#include <thread>
#include <unordered_map>
#include <vector>
#include "CMAKE_Target_List_Determiner.hpp"
#include "Build_System_Meta_Data_Collector.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "CMAKE_Target_Library_Builder.hpp"
#include "Make_File_Cleaner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "MakeFile_Directory_Constructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

namespace cmake_build {

     struct target_dependency_data
     {
           std::string target_name;
           
           std::string dep_name;

           std::string dep_hdr_dir;

           const Compiler_Data * dep_data; // this is the pointer for Compiler_Data holding 
                                           // related target dependency information
     };
}

class CMAKE_Target_List_Data_Processor
{
public:

 CMAKE_Target_List_Data_Processor(char build_type);
 
 virtual ~CMAKE_Target_List_Data_Processor();

 void Receive_Target_List_Data(const std::vector<cmake_build::target_data> * ptr){

      this->Target_List_Data_Ptr = ptr;
 } 

 void Receive_Compiler_Dependency_Data(const std::vector<Compiler_Data> * ptr){

      this->Compiler_Data_Pointer = ptr;
 } 

 void Receive_System_Interface(Custom_System_Interface * sysInt){
     
      this->SysInt = sysInt;
 }
 
 const std::vector<std::vector<cmake_build::target_dependency_data>> * Get_Target_List_Elements_Dependency_Data(){

      return &this->Target_List_Dependeny_Data;
 }

 void Process_Target_List_Data();

 void Print_Processed_Data();
 
 void Clear_Dynamic_Memory();

protected:

 void Construct_Compiler_Data_Map();

 void Find_File_Name_Without_Extension(std::string hdr_name, 

      std::string & file_name_with_ext);
      
 const Compiler_Data * Find_Compiler_Data_From_File_Name(std::string hdr_name) const;

 std::unordered_map<std::string,const Compiler_Data *> Compiler_DataMap;
 const std::vector<cmake_build::target_data> * Target_List_Data_Ptr;
 const std::vector<Compiler_Data> * Compiler_Data_Pointer;
 std::vector<std::vector<cmake_build::target_dependency_data>> Target_List_Dependeny_Data;
 Custom_System_Interface * SysInt;
 bool Memory_Delete_Condition;
 char build_type;
};

#endif /* CMAKE_TARGET_LIST_DATA_PROCESSOR_HPP */
