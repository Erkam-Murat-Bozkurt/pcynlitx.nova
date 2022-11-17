



#ifndef EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP
#define EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP

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
#include "Executable_MakeFile_DepDeterminer.hpp"
#include "Executable_MakeFile_DataCollector.hpp"
#include "Executable_MakeFile_Dependency_Selector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "CharOperator.h"
#include "IntToCharTranslater.h"


class Executable_MakeFile_ComConstructor
{
public:
 Executable_MakeFile_ComConstructor();
 Executable_MakeFile_ComConstructor(const Executable_MakeFile_ComConstructor & orig);
 virtual ~Executable_MakeFile_ComConstructor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 void Receive_DepDeterminer(Executable_MakeFile_DepDeterminer * pointer);
 void Receice_DataCollector(Executable_MakeFile_DataCollector * pointer);
 void Construct_Compiler_Commands(char * main_file_path);
 void Clear_Dynamic_Memory();
 char * Get_Compiler_System_Command();
 char * Get_Object_File_List();
 char * Get_Header_File_List();
 char * Get_Src_File_Dr();
 char * Get_Git_Src_Dr();
 char * Get_Make_File_Name();
protected:
 void Determine_Compiler_System_Command();
 void Construct_Object_File_List();
 void Determine_List_Sizes();
 void Construct_Header_File_List();
 void Set_Header_File_Priorities();
 void Re_Order_Header_Files();
 void Determine_Git_Src_Dir();
 void Determine_Src_File_Dir(char * file_path, char opr_sis);
 void Determine_Object_File_Name(char ** obj_name, char * header);
 void Determine_Make_File_Name(char * file_path);
 void Determine_Source_File_Name(char * file_path);
 void Divide_Options(char * options);
 void Add_String(char ** list, char * string, int * index);
 void Place_String(std::string * pointer, char * string);
 void Place_CString(char ** str_pointer, std::string string);
 void Place_CString(char ** str_pointer, char * string);
 void Place_Information(char ** Pointer,
      char * Information, int * index_counter);
 Descriptor_File_Reader * Des_Reader_Pointer;
 Compiler_Data_CString * Data_Ptr_CString;
 Header_Dependency * Header_Dependency_List;
 CharOperator CharOpr;
 Executable_MakeFile_DepDeterminer * Dep_Determiner;
 Executable_MakeFile_Dependency_Selector Dependency_Selector;
 Executable_MakeFile_DataCollector * Data_Collector;
 IntToCharTranslater Translater;
 char * repo_dir;
 char * options;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * make_file_name;
 char * object_file_list;
 char * header_file_list;
 char * src_file_dir;
 char * git_src_dir;
 char * source_file_name;
 char * Compiler_System_Command;
 int  header_file_number;
 int  Data_Size;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP */
