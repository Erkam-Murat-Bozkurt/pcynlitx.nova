




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
  std::string  repo_path;
  std::string  header_name;
  std::string  object_file_name;
  std::vector<std::string> included_headers;
  std::vector<std::string> included_headers_paths;
  int  inclusion_number;
  int  priority; // dependency
  bool rcr_srch_complated;
};


class Source_File_Compiler_Data_Extractor
{
public:
 Source_File_Compiler_Data_Extractor(char * des_file_path, char opr_sis);
 virtual ~Source_File_Compiler_Data_Extractor();
 void Receive_Dependency_Data(std::vector<Headers_Data> * ptr, std::string wrd);
 void Extract_Compiler_Data();
 void Clear_Dynamic_Memory();
 Compiler_Data Get_Compiler_Data(int num);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
 size_t Get_Compiler_Data_Size();
protected:
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
 Source_File_Information_Collector * Info_Collector;
 StringOperator StringManager;
 CharOperator Char_Processor;
 Project_Files_Lister File_Lister;
 Cpp_FileOperations FileManager;
 std::vector<Headers_Data> * headers_dt;
 std::vector<Compiler_Data> compiler_dt;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char operating_sis;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* SOURCE_FILE_COMPILER_DATA_EXTRACTOR_HPP */
