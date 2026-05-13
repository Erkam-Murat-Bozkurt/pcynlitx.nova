





#ifndef CMAKE_TARGET_LIST_DETERMINER_HPP
#define CMAKE_TARGET_LIST_DETERMINER_HPP

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
#include <mutex>
#include "Build_System_Meta_Data_Collector.hpp"
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

     struct target_data
     {
           std::string target_name; // The target file name without file extention 

           //std::string target_name_with_ext; // The target file name with file extention such as ".cpp"

           int data_index; // this is the index for Compiler_Data vector

           const Compiler_Data * DATA_PTR; // this is the pointer for Compiler_Data holding 
                                     // related target dependency information
     };
};


class CMAKE_Target_List_Determiner
{
public:
 CMAKE_Target_List_Determiner(char build_type);
 
 virtual ~CMAKE_Target_List_Determiner();

 void Receive_Compiler_Dependency_Data(const std::vector<Compiler_Data> * ptr){

      this->Compiler_Data_Pointer = ptr;
 } 
 void Receive_System_Interface(Custom_System_Interface * sysInt){
     
      this->SysInt = sysInt;
 }

 void Determine_Target_Lists();

 bool Control_Dependency_For_Any_Previous_Target(int index);

 const std::vector<cmake_build::target_data> * Get_CMAKE_Target_List() const {

       return &this->target_list;
 }

 void Clear_Dynamic_Memory();

protected:

 void Find_File_Name_Without_Extension(std::string hdr_name, 

      std::string & file_name_with_ext);

 const std::vector<Compiler_Data> * Compiler_Data_Pointer;
 std::vector<cmake_build::target_data> target_list;
 Custom_System_Interface * SysInt;
 bool Memory_Delete_Condition;
 char build_type;
};

#endif /* CMAKE_TARGET_LIST_DETERMINER_HPP */
