




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
#include <mutex>
#include <thread>
#include <chrono>
#include "Source_File_Dependency_Selector.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


struct Compiler_Data
{
  std::string  source_file_path;
  std::string  source_file_name;
  std::string  object_file_name;
  std::vector<std::string> dependent_headers;
  std::vector<std::string> dependent_objs;
  std::vector<std::string> dependent_headers_paths;
  std::vector<std::string> dependent_headers_dir;
  int  priority; // dependency
};


class Source_File_Compiler_Data_Extractor
{
public:
 Source_File_Compiler_Data_Extractor(char opr_sis);
 virtual ~Source_File_Compiler_Data_Extractor();
 void Receive_Dependency_Data(Source_File_Dependency_Selector * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Extract_Compiler_Data();
 void Extract_Compiler_Data(std::string path);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 Compiler_Data Get_Compiler_Data(int num);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
protected:    
 void Extract_Obj_File_Name_From_File_Name(std::string * object_name,
      std::string header_name);
 void is_this_independent_header(std::string name, bool & is_ind);
 void Extract_Header_File_Name_From_Path(std::string * name,
      std::string path);
 void Process_Compiler_Data(int start, int end, int thm);
 void Extract_Compiler_Data_For_Single_Thread();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Buffer_Memory(Compiler_Data * ptr);
 void Clear_Data_Memory(std::vector<Compiler_Data> * ptr);
 Source_File_Dependency_Selector * Dep_Selector_Ptr;
 Source_File_Information_Collector * Info_Collector;
 CharOperator Char_Processor;
 Project_Files_Lister File_Lister;
 std::vector<std::vector<Source_File_Dependency>> * dep_data_ptr;
 std::vector<Compiler_Data> compiler_dt[8];
 std::vector<Compiler_Data> compiler_data;
 std::thread threads[8];
 std::mutex mtx;
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
