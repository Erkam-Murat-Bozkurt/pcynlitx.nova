





#ifndef SOURCE_FILE_DEPENDENCY_SELECTOR_HPP
#define SOURCE_FILE_DEPENDENCY_SELECTOR_HPP

#include <cstring>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <windows.h>
#include "Source_File_Information_Collector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


struct Header_Dependency
{
  bool rcr_srch_complated;
  std::string Header_Name;
  std::string repo_warehouse_path;
};


class Source_File_Dependency_Selector
{
public:
 Source_File_Dependency_Selector(char * descriptor_file_path, char opr_sis);
 virtual ~Source_File_Dependency_Selector();
 void Determine_Source_File_Dependencies(std::string path);
 void Print_Dependency_List();
 void Clear_Dynamic_Memory();
 std::string Get_Dependent_Header(int i);
 std::string Get_Dependent_Header_Path(int i);
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 Header_Dependency Get_Header_Dependency_List(int num);
 size_t  Get_Dependency_List_Size();
protected:
 void Extract_Dependency_Data(std::string path);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name,
      std::string string);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Determine_Header_Repo_Warehouse_Path( std::string * wrd_path,
      std::string file_name, char opr_sis);
 bool Is_This_File_Aready_Searched(std::string name);
 void Delete_Spaces_on_String(std::string * pointer);
 void Place_String(std::string * str_pointer, std::string string);
 void Search_Recursive_Include_Dependency(int index);
 bool Include_Decleration_Test(std::string string);
 void Receive_Collector_Info();
 bool CompareString(std::string firstString, std::string secondString);
 bool Is_This_Repo_HeaderFile(std::string head_name);
 void Clear_String_Memory(std::string * Pointer);
 void Clear_Vector_Memory(std::vector<Header_Dependency> * pointer);
 Source_File_Information_Collector Info_Collector;
 std::vector<Header_Dependency> Dependent_List;
 std::string warehouse_head_dir;
 std::string descriptor_file_path;
 Header_File_Determiner Header_Determiner; 
 StringOperator StringManager; 
 int    header_file_number;
 size_t ListLength;
 int  Dep_Counter;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool isStringsEqual;
 bool This_File_Exist;
};

#endif /* SOURCE_FILE_DEPENDENCY_SELECTOR_HPP */
