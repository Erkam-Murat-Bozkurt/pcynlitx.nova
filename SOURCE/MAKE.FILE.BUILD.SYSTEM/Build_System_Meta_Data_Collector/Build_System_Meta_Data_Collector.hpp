





#ifndef BUILD_SYSTEM_META_DATA_COLLECTOR_HPP
#define BUILD_SYSTEM_META_DATA_COLLECTOR_HPP

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
#include <vector>
#include <unordered_map>
#include "Descriptor_File_Reader.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "Custom_System_Interface.h"


class Build_System_Meta_Data_Collector
{
public:
 Build_System_Meta_Data_Collector(char * DesPath, char opr_sis, char build_type);

 virtual ~Build_System_Meta_Data_Collector();

 void Collect_Meta_Data();
 
 void Clear_Dynamic_Memory();
 
 const Descriptor_File_Reader * Get_Descriptor_File_Reader() const{

      return &this->Des_Reader;
 };

 const Source_File_Dependency_Determiner * Get_Source_File_Dependency_Determiner() const{

       return &this->Dep_Determiner;
 };

Git_Data_Processor * Get_Git_Data_Processor(){

       return &this->Data_Processor;
 };

 void Receive_System_Interface(Custom_System_Interface * sysInt){
 
      this->SysInt = sysInt;
 }

 const std::unordered_map<std::string, Compiler_Data> * Get_Data_Map(){

      return &this->DataMap;
 }


 const std::vector<Compiler_Data> * Get_Compiler_Data(){

      return this->Compiler_Data_Pointer;
 }
 
protected:
 void Clear_Vector_Memory(std::vector<std::string> & vec);

 void Clear_String_Memory(std::string & str);
 
 void Perform_Data_Map_Construction();
 
 const std::vector<Compiler_Data> * Compiler_Data_Pointer;
 Descriptor_File_Reader Des_Reader;
 Git_Data_Processor Data_Processor;
 Source_File_Dependency_Determiner Dep_Determiner;
 Custom_System_Interface * SysInt;
 char * Des_Path;
 std::unordered_map<std::string, Compiler_Data> DataMap;
 std::string Warehouse_Path;
 std::string Repo_Dir;
 std::string repo_head_dir;
 std::string repo_obj_dir;
 std::string DesPATH;
 char opr_sis;
 char build_type;
 bool Memory_Delete_Condition;
};

#endif /* BUILD_SYSTEM_META_DATA_COLLECTOR_HPP */
