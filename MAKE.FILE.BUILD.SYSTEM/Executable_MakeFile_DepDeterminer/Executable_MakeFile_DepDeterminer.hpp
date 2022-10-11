



#ifndef EXECUTABLE_MAKEFILE_DEPDETERMINER_HPP
#define EXECUTABLE_MAKEFILE_DEPDETERMINER_HPP

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


class Executable_MakeFile_DepDeterminer
{
public:
 Executable_MakeFile_DepDeterminer();
 Executable_MakeFile_DepDeterminer(const Executable_MakeFile_DepDeterminer & orig);
 virtual ~Executable_MakeFile_DepDeterminer();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_Git_Record_Data(Git_File_List_Receiver * Lister_Pointer);
 void Receive_Source_File_Info(Project_Files_Lister * Pointer);
 void Determine_Dependencies();
 void Print_Compiler_Orders();
 void Clear_Dynamic_Memory();
protected:
 void Search_Recursive_Include_Dependency(int index);
 void Determine_Compile_Order();
 void Reverse_Order_Priorities();
 void Receive_DataCollector_Info();
 void Order_Priorities();
 Executable_MakeFile_DataCollector DataCollector;
 Compiler_Data_CString * Data_Ptr_CString;
 CharOperator Char_Processor;
 char * git_header_dir;
 char * repo_dir;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * Make_File_Name;
 char * object_file_list;
 char * header_file_list;
 int  header_file_number;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* EXECUTABLE_MAKEFILE_DEPDETERMINER_HPP */
