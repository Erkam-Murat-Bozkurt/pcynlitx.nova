




#ifndef SOURCE_FILE_COMPILER_DATA_EXTRACTOR_HPP
#define SOURCE_FILE_COMPILER_DATA_EXTRACTOR_HPP

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
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


struct Compiler_Data
{
  std::string  header_repo_path;
  std::string  header_name;
  std::string  object_file_name;
  std::vector<std::string> dependent_headers;
  std::vector<std::string> dependent_headers_paths;
  int  priority; // dependency
};


class Source_File_Compiler_Data_Extractor
{
public:
 Source_File_Compiler_Data_Extractor(char * des_file_path, char opr_sis);
 virtual ~Source_File_Compiler_Data_Extractor();
 void Receive_Dependency_Data(std::vector<std::vector<Header_Dependency>> * ptr, std::string wrd);
 void Extract_Compiler_Data();
 void Extract_Compiler_Data(std::string path);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 Compiler_Data Get_Compiler_Data(int num);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
 size_t Get_Compiler_Data_Size();
protected:
 void Extract_Header_File_Name_From_Decleration(std::string * header_name,
      std::string string);
 void Extract_Obj_File_Name_From_Header_Name(std::string * object_name,
      std::string header_name);
 bool Include_Decleration_Test(std::string string);
 bool is_this_independent_header(std::string name);
 void Extract_Header_File_Name_From_Path(std::string * name,
      std::string path);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Buffer_Memory(Compiler_Data * ptr);
 Source_File_Information_Collector * Info_Collector;
 StringOperator StringManager;
 CharOperator Char_Processor;
 Project_Files_Lister File_Lister;
 Cpp_FileOperations FileManager;
 std::vector<std::vector<Header_Dependency>> * dep_data_ptr;
 std::vector<Headers_Data> * headers_dt;
 std::vector<Compiler_Data> compiler_dt;
 Compiler_Data buffer;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char operating_sis;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* SOURCE_FILE_COMPILER_DATA_EXTRACTOR_HPP */
