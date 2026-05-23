


#ifndef CMAKE_TARGET_LIBRARY_BUILDER_HPP
#define CMAKE_TARGET_LIBRARY_BUILDER_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <map>
#include <unordered_map>
#include <iterator>
#include "CMAKE_Target_List_Data_Processor.hpp"
#include "CMAKE_Target_List_Determiner.hpp"
#include "MakeFile_Path_Determiner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class CMAKE_Target_Library_Builder
{
public:

 CMAKE_Target_Library_Builder();

 virtual ~CMAKE_Target_Library_Builder();

 void Receive_Target_Dependency_Data(const std::vector<cmake::target_data> * dt_ptr) {

     this->target_dependency_data_ptr = dt_ptr;
 }

 
 void Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;
 }

 void Receive_Descriptor_File_Reader(const Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
 }


 void Build_MakeFile(int target_list_index);

 void Add_Target_Path_To_Directory_List(int index);

 void Construct_SubDirectory_List_File(int index);

 void Clear_Dynamic_Memory();

 void Clear_Object_Memory();

private:

 std::string Extract_Git_Record_Path(std::string path);

 void Convert_CMAKE_Format(std::string & str);

 void Clear_String_Vector(std::vector<std::string> & str); 

 void Clear_String_Memory(std::string & pointer);

 void CMAKE_Sub_Directory_File_Path_Determination(std::string & path);

 void CMAKE_SubDir_Determination(std::string & sub_dir_path);

 bool Check_String_Existance(std::vector<std::string> & list, std::string str);

 const std::vector<cmake::target_data> * target_dependency_data_ptr;

 const Descriptor_File_Reader * Des_Reader;

 StringOperator StrOpr;

 Cpp_FileOperations FileManager;

 IntToCharTranslater Translater;

 char opr_sis;

 bool Include_Line_Condition;
 
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_TARGET_LIBRARY_BUILDER_HPP */
