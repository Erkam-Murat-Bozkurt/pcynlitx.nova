






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

namespace cmake {

     struct target_dependency_dt
     {
            std::string dep_file_name;

            std::string dep_file_name_with_file_extention; // The file name with file extention such as ".cpp"

            std::string dep_file_path;

            std::string dep_file_sys_dir;

            std::string dep_file_git_record_dir; 
            
            bool is_source_file;

            bool is_header_file;
     };
};


namespace cmake {

     struct target_data 
     {
            std::string target_name; // The target name without file extention such as ".cpp"

            std::string target_name_with_file_extention; // The target name without file extention such as ".cpp"

            std::string target_sys_dir;

            std::string target_git_record_dir;

            std::string target_file_path;

            std::vector<std::string> dependent_header_dirs;

            std::vector<std::string> dependent_source_dirs;

            std::vector<cmake::target_dependency_dt> dep_dt;
     };
};


class CMAKE_Target_List_Data_Processor
{
public:

 CMAKE_Target_List_Data_Processor(char build_type);
 
 virtual ~CMAKE_Target_List_Data_Processor();

 void Receive_Descriptor_File(const Descriptor_File_Reader * ptr){

      this->Des_Reader = ptr;
 }

 void Receive_Target_List_Data(const std::vector<cmake::target_list_dtr> * ptr){

      this->Target_List_Data_Ptr = ptr;
 } 

 void Receive_Compiler_Dependency_Data(const std::vector<Compiler_Data> * ptr){

      this->Compiler_Data_Pointer = ptr;
 } 

 void Receive_System_Interface(Custom_System_Interface * sysInt){
     
      this->SysInt = sysInt;
 }
 
 const std::vector<cmake::target_data> * Get_Target_List_Elements_Dependency_Data() const {

      return &this->Target_List_Dependeny_Data;
 }

 void Process_Target_List_Data();

 void Print_Processed_Data();
 
 void Clear_Dynamic_Memory();

protected:

 void Determine_Target_Dependent_Directories(cmake::target_data & cmake_target);

 void Convert_CMAKE_Format(std::string & str){

      for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
      }
 }

 void Construct_Compiler_Data_Map();

 void Process_Target_Depenendecies(const Compiler_Data * DATA_PTR, 
    
      std::vector<cmake::target_dependency_dt> & target_dep,
     
      std::unordered_map<std::string,cmake::target_dependency_dt> & REPETITION_CONTROL_MAP);

 void Process_Target(cmake::target_list_dtr & target_dt, 
    
      cmake::target_data & target, 
      
      std::unordered_map<std::string,cmake::target_dependency_dt> & REPETITION_CONTROL_MAP);

 void Process_Target_List_Data(int i);

 std::string Extract_Git_Record_Path(std::string path);

 void Find_File_Name_Without_Extension(std::string hdr_name, 

      std::string & file_name_with_ext);
      
 void Set_Target_Dependency_Data_For_Header(cmake::target_dependency_dt & target_dep,

      std::string header_name, std::string header_dir);

 void Set_Target_Dependency_Data_For_Source(cmake::target_dependency_dt & target_dep,

     const Compiler_Data * COM_PTR);

 const Compiler_Data * Find_Compiler_Data_From_File_Name(std::string hdr_name) const;

 const Descriptor_File_Reader * Des_Reader;

 std::unordered_map<std::string,const Compiler_Data *> Compiler_DataMap;
 
 const std::vector<cmake::target_list_dtr> * Target_List_Data_Ptr;

 const std::vector<Compiler_Data> * Compiler_Data_Pointer;

 std::vector<cmake::target_data> Target_List_Dependeny_Data;

 Custom_System_Interface * SysInt;

 bool Memory_Delete_Condition;

 char build_type;
};

#endif /* CMAKE_TARGET_LIST_DATA_PROCESSOR_HPP */
