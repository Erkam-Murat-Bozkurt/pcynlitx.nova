


#ifndef EXECUTABLE_MAKEFILE_BUILDER_HPP
#define EXECUTABLE_MAKEFILE_BUILDER_HPP

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
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Executable_MakeFile_DepDeterminer.hpp"
#include "Executable_MakeFile_Dependency_Selector.hpp"
#include "Executable_MakeFile_DataCollector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "CharOperator.h"
#include "IntToCharTranslater.h"



class Executable_MakeFile_Builder
{
public:
 Executable_MakeFile_Builder();
 Executable_MakeFile_Builder(const Executable_MakeFile_Builder & orig);
 virtual ~Executable_MakeFile_Builder();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_Git_Record_Data(Git_File_List_Receiver * Lister_Pointer);
 void Receive_Source_File_Info(Project_Files_Lister * Pointer);
 void Build_MakeFile(char * path);
 void Print_Compiler_Orders();
 void Clear_Dynamic_Memory();
protected:
 void Write_MakeFile();
 void Determine_Src_File_Dir(char * file_path, char opr_sis);
 void Determine_Git_Src_Dir(char * file_path, char opr_sis);
 void Determine_Make_File_Name(char * file_path);
 void Determine_Git_Src_Dir();
 Executable_MakeFile_ComConstructor ComConstructor;
 Executable_MakeFile_DataCollector  Data_Collector;
 Executable_MakeFile_DepDeterminer  Dep_Determiner;
 Descriptor_File_Reader * Des_Reader_Pointer;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 CharOperator Char_Processor;
 IntToCharTranslater Translater;
 char * Src_File_Dir;
 char * git_src_dir;
 char * repo_dir;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * Make_File_Name;
 char * object_file_list;
 char * header_file_list;
 char * Dependency_Code_Line;
 int  header_file_number;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
};

#endif /* EXECUTABLE_MAKEFILE_BUILDER_HPP */
