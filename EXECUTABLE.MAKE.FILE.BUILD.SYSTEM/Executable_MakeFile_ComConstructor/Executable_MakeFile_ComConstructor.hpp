



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
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "CharOperator.h"
#include "IntToCharTranslater.h"


class Executable_MakeFile_ComConstructor
{
public:
 Executable_MakeFile_ComConstructor(char * des_path, char opr_sis);
 virtual ~Executable_MakeFile_ComConstructor();
 void Receive_ExeFileName(std::string name);
 void Construct_Compiler_Commands(std::string main_file_path);
 void Clear_Dynamic_Memory();
 std::string Get_Compiler_System_Command();
 std::vector<std::string> * Get_Object_File_List();
 std::vector<std::string> * Get_Header_File_List();
 std::string Get_Src_File_Dr();
 std::string Get_Git_Src_Dr();
 std::string Get_Make_File_Name();
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
protected:
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Determine_Compiler_System_Command();
 void Construct_Object_File_List();
 void Construct_Header_File_List();
 void Determine_Git_Src_Dir();
 void Determine_Src_File_Dir(std::string file_path, char opr_sis);
 void Determine_Make_File_Name(std::string file_path);
 void Determine_Source_File_Name(std::string file_path);
 void Divide_Options(std::string options);
 void Add_String(std::string * list, std::string string);
 void Place_String(std::string * pointer, std::string string);
 void Place_Information(std::string * ptr,std::string in);
 void Place_Information(std::string * ptr, char * in);
 Descriptor_File_Reader Des_Reader;
 Source_File_Dependency_Determiner Dep_Determiner;
 IntToCharTranslater Translater;
 std::vector<Compiler_Data> * Comp_Data_ptr;
 std::vector<std::string> header_file_list;
 std::vector<std::string> object_file_list;
 std::string Exe_Name;
 std::string options;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string make_file_name;
 std::string src_file_dir;
 std::string git_src_dir;
 std::string source_file_name;
 std::string Compiler_System_Command;
 int  header_file_number;
 int  Data_Size;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP */
