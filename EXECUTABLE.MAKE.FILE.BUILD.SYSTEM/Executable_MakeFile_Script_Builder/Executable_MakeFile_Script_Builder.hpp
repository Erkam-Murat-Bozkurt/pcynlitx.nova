


#ifndef EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP
#define EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
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
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader* ptr);
 void Receive_Construction_Directory_Path(std::string path);
 void Receive_Exe_File_Name(char * exe_file_name);
 void Build_Compiler_Script_For_Executable_File(char * src_name);
 void Clear_Dynamic_Memory();
 std::string Get_Src_File_Name_Without_Ext();
 std::string Get_Src_File_Name();
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
 void Determine_Script_Builder_Make_File_Name();
 int  Determine_Decimal_Space(int total_src_num, int current_number);
 void Clear_String_Memory(std::string * pointer);
 void Change_Directory(int index);
 void Determination_of_Up_to_date_Status(int index);
 void Remove_The_Current_Object_File(int index);
 void Compile_The_Source_File(int index);
 void Check_Build_Success_Status(int index);
 void Move_Object_File_To_The_Warehouse(int index);
 void Print_Build_Output_To_Screen(int index);
 Descriptor_File_Reader * Des_Reader;
 Script_Data_Processor Src_Data_Processor;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::string Construction_Directory_Path;
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
 std::string file_name_without_ext;
 std::string src_file_name;
 std::string script_builder_make_file_name;
 std::string exe_file_name;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_SCRIPT_BUILDER_HPP */
