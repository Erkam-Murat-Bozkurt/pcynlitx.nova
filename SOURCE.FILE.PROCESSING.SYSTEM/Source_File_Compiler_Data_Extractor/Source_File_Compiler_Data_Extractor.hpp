




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
#include "Source_File_Dependency_Selector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Git_Data_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Descriptor_File_Reader.hpp"
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
  std::string  source_file_name_witout_ext;
  std::string  src_git_record_dir;
  std::string  src_sys_dir;
  std::string  cmake_target_name;
  std::vector<std::string> dependent_headers;
  std::vector<std::string> dependent_headers_dir;
  std::vector<std::string> upper_directories;
  int  priority; // dependency
  bool file_name_similarity_status;
};


class Source_File_Compiler_Data_Extractor
{
public:
 Source_File_Compiler_Data_Extractor(char opr_sis);
 virtual ~Source_File_Compiler_Data_Extractor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_Single_File_Dependency_Data(Source_File_Dependency_Selector_For_Single_File * ptr);
 void Receive_Dependency_Data(Source_File_Dependency_Selector * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * Proc);
 void Extract_Directory_Short_Path(std::string sys_dir, std::vector<std::string> & sort_dir_path);
 void Extract_Compiler_Data();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 Compiler_Data Get_Compiler_Data(int num);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
protected:    
 void Extract_Obj_File_Name_From_File_Name(std::string * object_name, std::string hdr);
 void Process_Compiler_Data(int start, int end);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Buffer_Memory(Compiler_Data * ptr);
 void Clear_Data_Memory(std::vector<Compiler_Data> * ptr);
 void Find_Upper_Directory(std::string & upper, std::string dir);
 size_t Split_Range(size_t range_size, size_t partition, size_t & remaining_job);
 void Search_For_Large_Data_Set(size_t data_size);
 void Search_For_Middle_Data_Set(size_t data_size);
 void Search_For_Small_Data_Set(size_t data_size);
 void Construct_Compiler_Data_List();
 bool Is_There_File_Name_Similarity(std::string fileName);
 Source_File_Dependency_Selector_For_Single_File * Dep_Selector_For_Single_File_Ptr;
 Source_File_Dependency_Selector * Dep_Selector_Ptr;
 Source_File_Information_Collector * Info_Collector;
 std::vector<std::vector<Source_File_Dependency>> * dep_data_ptr;
 std::vector<std::vector<Compiler_Data>> Compiler_Data_Vectors;
 std::vector<Compiler_Data> compiler_data;
 std::vector<std::thread> threadPool;
 Git_Data_Processor * Git_Data_Proc;
 Descriptor_File_Reader * Des_Reader;
 Compiler_Data buffer;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 size_t thread_num;
 std::mutex mtx;
 char operating_sis;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* SOURCE_FILE_COMPILER_DATA_EXTRACTOR_HPP */
