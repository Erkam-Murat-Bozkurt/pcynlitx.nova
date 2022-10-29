



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
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "CharOperator.h"


class Executable_MakeFile_ComConstructor
{
public:
 Executable_MakeFile_ComConstructor();
 Executable_MakeFile_ComConstructor(const Executable_MakeFile_ComConstructor & orig);
 virtual ~Executable_MakeFile_ComConstructor();
 void Receive_DepDeterminer(Executable_MakeFile_DepDeterminer * pointer);
 void Construct_Compiler_Commands();
 void Clear_Dynamic_Memory();
 char * Get_Object_File_List();
 char * Get_Header_File_List();
protected:
 void Determine_Object_File_List_Size();
 void Construct_Object_File_List();
 void Determine_Header_File_List_Size();
 void Construct_Header_File_List();
 void Add_String(char ** list, char * string, int * index);
 void Place_String(std::string * pointer, char * string);
 void Place_CString(char ** str_pointer, std::string string);
 void Place_CString(char ** str_pointer, char * string);
 Compiler_Data_CString * Data_Ptr_CString;
 Executable_MakeFile_DepDeterminer * Dep_Determiner;
 char * repo_dir;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * Make_File_Name;
 char * object_file_list;
 char * header_file_list;
 int  header_file_number;
 int  Data_Size;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP */
