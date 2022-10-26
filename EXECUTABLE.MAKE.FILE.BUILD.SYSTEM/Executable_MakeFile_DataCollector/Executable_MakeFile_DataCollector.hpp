



#ifndef EXECUTABLE_MAKEFILE_DATACOLLECTOR_HPP
#define EXECUTABLE_MAKEFILE_DATACOLLECTOR_HPP

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

struct Compiler_Data_CString
{
  char *  repo_path;
  char *  header_name;
  char *  object_file_name;
  char ** included_headers;
  int inclusion_number;
  int priority;
  bool rcr_srch_complated;
};


class Executable_MakeFile_DataCollector
{
public:
 Executable_MakeFile_DataCollector();
 Executable_MakeFile_DataCollector(const Executable_MakeFile_DataCollector & orig);
 virtual ~Executable_MakeFile_DataCollector();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_Git_Record_Data(Git_File_List_Receiver * Lister_Pointer);
 void Receive_Source_File_Info(Project_Files_Lister * Pointer);
 void Collect_Make_File_Data();
 void Clear_Dynamic_Memory();
 void Print_Header_Data();
 Compiler_Data_CString * Get_Compiler_Data();
 int    Get_Compiler_Data_Size();
 char * Get_Warehouse_Headers_Dir();
 char * Get_Warehouse_Objetcs_Dir();
 char * Get_Warehouse_Path();
protected:
 void Clear_Pointer_Memory(char ** Pointer);
 void Determine_Header_File_List();
 void Determine_Warehouse_Object_Dir(char operating_sis);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Extract_Compiler_Data();
 void Determine_Header_Repo_Warehouse_Path(char ** wrd_path,
      char * file_name, char opr_sis);
 void Extract_Header_File_Name_From_Decleration(char ** header_name, char * string);
 void Extract_Obj_File_Name_From_Header_Name(char ** object_name,
      std::string header_name);
 void Delete_Spaces_on_String(char ** pointer);
 void Construct_Temporary_String(char ** tmp_string, char * string);
 void Add_String(char ** list, char * string, int * index);
 void Place_String(std::string * pointer, char * string);
 void Place_CString(char ** str_pointer, std::string string);
 void Place_CString(char ** str_pointer, char * string);
 void Convert_to_CString(char ** Pointer, std::string path);
 bool Include_Decleration_Test(char * string);
 void Initialize_Header_Data();
 bool is_this_independent_header(std::string name);
 void Extract_Header_File_Name_From_Path(char * path,
      char ** name, char opr_sis);
 Descriptor_File_Reader * Des_Reader_Pointer;
 Project_Files_Lister * File_Lister_Pointer;
 Git_File_List_Receiver * Git_Data_Receiver;
 Cpp_FileOperations FileManager;
 Header_File_Determiner Header_Determiner;
 StringOperator StringManager;
 CharOperator Char_Processor;
 std::vector<Headers_Data> v_head_data;
 std::vector<Headers_Data>::iterator itr;
 std::string String_Line;
 Headers_Data * Header_Data_Pointer;
 Compiler_Data_CString * Data_Ptr_CString;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 int  header_file_number;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* EXECUTABLE_MAKEFILE_DATACOLLECTOR_HPP */
