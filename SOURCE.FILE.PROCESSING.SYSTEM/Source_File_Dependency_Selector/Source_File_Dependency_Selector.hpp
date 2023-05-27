





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
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
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
  std::string root_header; // The header file which its dependencies are researched 
  std::string root_header_path;
  std::string Header_Name;
  std::string header_sys_path;
  int included_file_hdr_num;
  int base_included_hdr_num;
};


class Source_File_Dependency_Selector
{
public:
 Source_File_Dependency_Selector(char * descriptor_file_path, char opr_sis);
 virtual ~Source_File_Dependency_Selector();
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Determine_Source_File_Dependencies(std::string path);
 void Determine_Source_File_Dependencies();
 void Print_Dependency_List();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 std::vector<std::vector<Header_Dependency>> * Get_Dependency_List_Adress();
 std::vector<Header_Dependency> * Get_Dependency_List_Element_Adress(int num);
 size_t  Get_Dependency_List_Size();
protected:
 void Extract_Dependency_Data(std::string path);
 void Extract_Dependency_Data();
 void Set_Included_Header_Number(std::vector<Header_Dependency> * ptr, int dep_num);
 std::string Find_Header_Name(std::string string);
 void Determine_Header_Repo_Warehouse_Path( std::string * wrd_path,
      std::string file_name, char opr_sis);
 bool Is_This_File_Aready_Searched(std::string name);
 void Place_String(std::string * str_pointer, std::string string);
 bool Include_Decleration_Test(std::string string);
 void Extract_File_Name_From_Path(std::string * ptr, std::string str);
 bool CompareString(std::string firstString, std::string secondString);
 bool Is_This_Repo_HeaderFile(std::string head_name);
 void Clear_String_Memory(std::string * Pointer);
 void Clear_Vector_Memory(std::vector<Header_Dependency> * pointer);
 void Clear_Temporary_String_Memory(Header_Dependency * temp);
 int Determine_Inclusion_Number(std::string path);
 void Determine_Header_System_Path(std::string & path, std::string name);
 void Set_Dependency_Data(Header_Dependency & data, std::string path, std::string header_name);
 Source_File_Information_Collector Info_Collector; 
 Project_Src_Code_Rdr * Code_Rd;
 std::vector<Header_Dependency> Dependent_List;
 std::vector<Headers_Data> * Headers_Data_Ptr;
 std::vector<std::vector<Header_Dependency>> Dependency_Data;
 std::string warehouse_head_dir;
 std::string descriptor_file_path;
 Header_File_Processor Header_Processor; 
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
