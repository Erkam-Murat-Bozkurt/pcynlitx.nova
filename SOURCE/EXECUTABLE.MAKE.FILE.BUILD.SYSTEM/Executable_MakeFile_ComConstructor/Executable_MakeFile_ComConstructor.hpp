



#ifndef EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP
#define EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP

#include <cstring>
#include <cstdlib>
#include <cctype>
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
#include "Executable_MakeFile_Information_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "CharOperator.h"
#include "IntToCharTranslater.h"


class Executable_MakeFile_ComConstructor
{
public:
 Executable_MakeFile_ComConstructor(char opr_sis);
 virtual ~Executable_MakeFile_ComConstructor();
 void Receive_Construction_Strategy(char strategy);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Dependency_Determiner(Source_File_Dependency_Determiner * ptr); 
 void Receive_ExeFileName(std::string name);
 void Construct_Compiler_Commands(std::string main_file_path);
 void Clear_Dynamic_Memory();
 std::string Get_Compiler_System_Command();
 std::string Get_Dependency_Determination_Command();
 std::vector<std::string> * Get_Object_File_List();
 std::vector<std::string> * Get_Header_File_List();
 std::string Get_Src_File_Dr();
 std::string Get_Git_Src_Dr();
 std::string Get_Make_File_Name();
 std::string Get_Project_Library_Name();
protected:
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Dependency_Determination_Command_Construction();
 void Determine_Compiler_System_Command();
 void Construct_Object_File_List();
 void Construct_Header_File_List();
 void Construct_Library_Directories_List();
 void Determine_Git_Src_Dir();
 void Determine_Compiler_System_Command_For_Simple_Construction();
 void Determine_Dependency_Determination_Command_For_Simple_Construction();
 void Determine_Include_Directory_List_For_Simple_Construction();
 void Determine_Source_File_Directory_List_For_Simple_Construction();
 void Construct_Header_File_List_For_Simple_Construction();
 void Determine_Src_File_Dir(std::string file_path, char opr_sis);
 void Determine_Make_File_Name(std::string file_path);
 void Determine_Source_File_Name(std::string file_path);
 void Extract_Repo_Directory_Name(std::string & name, std::string root_dir);
 void Add_String(std::string * list, std::string string);
 void Place_String(std::string * pointer, std::string string);
 void Place_Information(std::string * ptr,std::string in);
 void Place_Information(std::string * ptr, char * in);
 bool Check_Include_Directory_Existance(std::vector<std::string> * hdr_dir, std::string dir);
 void Determine_Project_Library_Name();
 Executable_MakeFile_Information_Collector Information_Collector;
 Descriptor_File_Reader * Des_Reader;
 Source_File_Dependency_Determiner * Dep_Determiner;
 IntToCharTranslater Translater;
 std::vector<Compiler_Data> * Comp_Data_ptr;
 const Simple_Source_File_Dependency * Simple_Data_Ptr;
 std::vector<std::string> header_file_list;
 std::vector<std::string> header_file_paths;
 std::vector<std::string> header_file_dirs;
 std::vector<std::string> header_file_upper_dirs;
 std::vector<std::string> object_file_list;
 std::vector<std::string> library_name_list;
 std::string Exe_Name;
 std::string options;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string make_file_name;
 std::string src_file_dir;
 std::string git_src_dir;
 std::string source_file_name;
 std::string source_file_name_without_ext;
 std::string Compiler_System_Command;
 std::string Dependency_Determination_Command;
 std::string project_library_name;
 std::string include_directory_list_for_compiler_command;
 std::string source_file_directory_list_for_compiler_command;
 std::string library_directory_list_for_compiler_command;
 std::string include_file_list_for_compiler_command;
 std::string library_path_list_for_compiler_command;
 std::string external_include_directory_list_for_compiler_command;
 std::string compiler_options_list_for_compiler_command;
 std::string linker_options_list_for_compiler_command;
 int  header_file_number;
 int  Data_Size;
 char opr_sis;
 char constraction_strategy;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_COMCONSTRUCTOR_HPP */
