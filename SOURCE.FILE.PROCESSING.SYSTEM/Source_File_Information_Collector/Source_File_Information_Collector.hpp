




#ifndef SOURCE_FILE_INFORMATION_COLLECTOR_HPP
#define SOURCE_FILE_INFORMATION_COLLECTOR_HPP

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
#include <vector>
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

struct Headers_Data
{
  std::string repo_path;
  std::string name;
  std::vector<std::string> included_headers;
  int inclusion_number;
  int priority;
};

struct Compiler_Data
{
  std::string  repo_path;
  std::string  header_name;
  std::string  object_file_name;
  std::vector<std::string> included_headers;
  std::vector<std::string> included_headers_path;
  int  inclusion_number;
  int  priority; // dependency
  bool rcr_srch_complated;
};


class Source_File_Information_Collector
{
public:
 Source_File_Information_Collector(char * descriptor_file_path, char opr_sis);
 virtual ~Source_File_Information_Collector();
 void Collect_Make_File_Data();
 void Clear_Dynamic_Memory();
 Compiler_Data Get_Compiler_Data(int num);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
 size_t  Get_Compiler_Data_Size();
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
protected:
 void Determine_Header_File_List();
 void Determine_Warehouse_Object_Dir();
 void Determine_Warehouse_Header_Dir();
 void Extract_Compiler_Data();
 void Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,
      std::string file_name, char opr_sis);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name,
      std::string string);
 void Extract_Obj_File_Name_From_Header_Name(std::string * object_name,
      std::string header_name);
 void Delete_Spaces_on_String(std::string * pointer);
 bool Include_Decleration_Test(std::string string);
 bool is_this_independent_header(std::string name);
 void Extract_Header_File_Name_From_Path(std::string * name,
      std::string path);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Headers_Data();
 StringOperator StringManager;
 CharOperator Char_Processor;
 Descriptor_File_Reader Des_Reader;
 Project_Files_Lister File_Lister;
 Git_File_List_Receiver Git_Data_Receiver;
 Cpp_FileOperations FileManager;
 Header_File_Determiner Header_Determiner;
 std::vector<Headers_Data> v_head_data;
 std::vector<Compiler_Data> Data;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char operating_sis;
 int  header_file_number;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* SOURCE_FILE_INFORMATION_COLLECTOR_HPP */
