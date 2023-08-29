


#ifndef EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP
#define EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Script_Data_Processor.hpp"
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"


class Executable_MakeFile_Script_Builder
{
public:
 Executable_MakeFile_Script_Builder(char opr_sis);
 virtual ~Executable_MakeFile_Script_Builder();
 void Receive_File_System_Path(char * file_sys_path);
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader* ptr);
 void Build_Compiler_Script_For_Executable_File(char * src_name);
 void Clear_Dynamic_Memory();
protected:
 void Write_The_Executable_Make_File_Update_Script(std::string src_file_name);
 void Construct_Script_Path();
 void Construct_Path(std::string & pointer,
      std::string string, char opr_sis);
 void Determine_Object_Files_Location(char opr_sis);
 void Determine_Src_File_Sys_Dir(std::string & file_sys_dir);
 void Determine_File_Name(std::string & file_name_without_ext);
 void Clear_String_Memory(std::string & pointer);
 void Determine_Compiler_Output_Path(std::string class_name);
 void Clear_String_Memory(std::string * pointer);
 Descriptor_File_Reader * Des_Reader;
 Script_Data_Processor Src_Data_Processor;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::string Repo_Root_Dir;
 std::string object_files_location;
 std::string compiler_output_location;
 std::string headers_locations;
 std::string script_path;
 std::string warehouse_path;
 int source_file_num;
 std::vector<Script_Data> * Data_Pointer;
 std::string file_sys_path;
 std::string file_sys_dir;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP */
