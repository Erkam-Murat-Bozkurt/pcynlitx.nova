







#ifndef CMAKE_TARGET_LIST_DATA_STRUCTURE_CONSTRUCTOR_HPP
#define CMAKE_TARGET_LIST_DATA_STRUCTURE_CONSTRUCTOR_HPP

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
#include "CMAKE_Target_List_Data_Processor.hpp"
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


class CMAKE_Target_List_Data_Structure_Constructor
{
public:

 CMAKE_Target_List_Data_Structure_Constructor(char * DesPath, char opr_sis, char build_type);
 
 virtual ~CMAKE_Target_List_Data_Structure_Constructor();

 void Receive_System_Interface(Custom_System_Interface * sysInt);

 void Receive_Descriptor_File(const Descriptor_File_Reader * ptr){

      this->Des_Reader = ptr;
 }

 const std::vector<cmake::target_data> * Get_Target_List_Elements_Dependency_Data() const {

      return this->Target_List_Data_Processor.Get_Target_List_Elements_Dependency_Data();
 }

 const Descriptor_File_Reader * Get_Descriptor_File_Reader() const{

      return this->Meta_Data_Collector.Get_Descriptor_File_Reader();
 };

 const Source_File_Dependency_Determiner * Get_Source_File_Dependency_Determiner() const{

       return this->Meta_Data_Collector.Get_Source_File_Dependency_Determiner() ;
 };

Git_Data_Processor * Get_Git_Data_Processor(){

       return this->Meta_Data_Collector.Get_Git_Data_Processor();
 };

 void Construct_Target_List_Data_Structure();
 
 void Clear_Dynamic_Memory();

protected:

 Build_System_Meta_Data_Collector Meta_Data_Collector;

 CMAKE_Target_List_Determiner Target_List_Determiner;

 CMAKE_Target_List_Data_Processor Target_List_Data_Processor;

 const std::vector<Compiler_Data> * Compiler_Data_Pointer;

 Custom_System_Interface * SysInt;

 const Descriptor_File_Reader * Des_Reader;

 bool Memory_Delete_Condition;

};

#endif /* CMAKE_TARGET_LIST_DATA_STRUCTURE_CONSTRUCTOR_HPP */
