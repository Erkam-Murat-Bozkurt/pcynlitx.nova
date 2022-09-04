


#ifndef EXECUTABLE_MAKEFILE_BUILDER_HPP
#define EXECUTABLE_MAKEFILE_BUILDER_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <windows.h>
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class Executable_MakeFile_Builder
{
public:
 Executable_MakeFile_Builder();
 Executable_MakeFile_Builder(const Executable_MakeFile_Builder & orig);
 virtual ~Executable_MakeFile_Builder();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_Git_Record_Data(Project_Files_Lister * File_Lister);
 void Build_MakeFile();
 void Clear_Dynamic_Memory();
protected:
 void Collect_Make_File_Data();
 void Determine_Object_File_List();
 void Determine_Header_File_List();
 void Determine_Warehouse_Object_Dir(char operating_sis);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Add_String(char ** list, char * string, int * index);
 Descriptor_File_Reader * Des_Reader_Pointer;
 Project_Files_Lister * File_Lister_Pointer;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 Header_File_Determiner Header_Determiner;
 IntToCharTranslater Translater;
 std::string String_Line;
 char * git_header_dir;
 char * repo_dir;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * Make_File_Name;
 char * object_file_list;
 char * header_file_list;

 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_BUILDER_HPP */
