




#ifndef EXECUTABLE_MAKEFILE_DEPENDENCY_SELECTOR_HPP
#define EXECUTABLE_MAKEFILE_DEPENDENCY_SELECTOR_HPP

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
#include "Executable_MakeFile_DataCollector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

struct Header_Dependency {

  bool   rcr_srch_complated;
  char * Header_Name;
  char * Object_File_Name;
  char * repo_warehouse_path;
  int  priority;
};


class Executable_MakeFile_Dependency_Selector
{
public:
 Executable_MakeFile_Dependency_Selector();
 Executable_MakeFile_Dependency_Selector(const Executable_MakeFile_Dependency_Selector & orig);
 virtual ~Executable_MakeFile_Dependency_Selector();
 void Receive_Executable_MakeFile_DataCollector(Executable_MakeFile_DataCollector * pointer);
 void Determine_Source_File_Dependencies(char * pointer);
 void Print_Dependency_List();
 void Clear_Dynamic_Memory();
 Header_Dependency * Get_Header_Dependency_List();
 char * Get_Dependent_Header(int i);
 char * Get_Dependent_Header_Path(int i);
 int    Get_Dependency_List_Size();
protected:
 void Extract_Dependency_Data(char * path);
 void Extract_Header_File_Name_From_Decleration(char ** header_name,
      char * string);
 size_t CharListLength(char * Characterlist);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Determine_Header_Repo_Warehouse_Path(char ** wrd_path,
      char * file_name, char opr_sis);
 bool Is_This_File_Aready_Searched(char * name);
 void Construct_Temporary_String(char ** tmp_string,
      char * string);
 void Delete_Spaces_on_String(char ** pointer);
 void Place_String(char ** str_pointer, char * string);
 void Search_Recursive_Include_Dependency(int index);
 bool Include_Decleration_Test(char * string);
 void Receive_DataCollector_Info();
 bool CompareString(char * firstString,char * secondString);
 bool Is_This_Repo_HeaderFile(char * head_name);
 void Clear_Pointer_Memory(char ** Pointer);
 Executable_MakeFile_DataCollector * DataCollector;
 Header_Dependency * Dependent_List;
 Cpp_FileOperations FileManager;
 Compiler_Data_CString * Data_Ptr_CString;
 char * warehouse_head_dir;
 StringOperator StringManager;
 Header_File_Determiner Header_Determiner;
 int  header_file_number;
 size_t ListLength;
 int Dep_Counter;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool isStringsEqual;
 bool This_File_Exist;
};

#endif /* EXECUTABLE_MAKEFILE_DEPENDENCY_SELECTOR_HPP */
