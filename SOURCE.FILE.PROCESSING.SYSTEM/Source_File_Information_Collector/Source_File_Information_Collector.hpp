




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

#include "Source_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Processor.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

struct Source_File_Data
{
  std::string source_file_name;
  std::string system_path;
  std::vector<std::string> included_headers;       // Included header files data
  std::vector<std::string> included_headers_paths;
  int inclusion_number;
  int priority;
  bool rcr_srch_complated;
};



class Source_File_Information_Collector
{

public:
 Source_File_Information_Collector(char * des_file_path, char opr_sis);
 virtual ~Source_File_Information_Collector();
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Data(std::string path);
 void Extract_Dependency_Data();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 bool Is_Header_File(std::string hpath);
 Source_File_Data Get_Dependency_Data(int num);
 std::vector<Source_File_Data> * Get_Headers_Data_Address();
 size_t       Get_Dependency_Data_Size();
 std::string  Get_Warehouse_Headers_Dir();
 std::string  Get_Warehouse_Objetcs_Dir();
 std::string  Get_Warehouse_Path();

protected:
 void Determine_Source_File_List();
 void Determine_Warehouse_Object_Dir();
 void Determine_Warehouse_Header_Dir();
 void Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,
      std::string file_name, char opr_sis);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name,
      std::string string);
 void Determine_Header_System_Path(std::string * sys_path,std::string path);
 bool Include_Decleration_Test(std::string string);
 bool CompareString(std::string sr1, std::string sr2);
 void Clear_Buffer_Memory();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Headers_Data();
 Project_Src_Code_Rdr * Code_Rdr;
 StringOperator StringManager;
 Descriptor_File_Reader Des_Reader;
 Git_File_List_Receiver Git_Data_Receiver;
 Source_File_Processor Src_File_Pr;
 Cpp_FileOperations FileManager;
 Header_File_Processor Header_Processor;
 std::vector<Source_File_Data> Src_Data_Holder;
 Source_File_Data buffer;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char operating_sis;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
 bool isStringsEqual;
};

#endif /* SOURCE_FILE_INFORMATION_COLLECTOR_HPP */
