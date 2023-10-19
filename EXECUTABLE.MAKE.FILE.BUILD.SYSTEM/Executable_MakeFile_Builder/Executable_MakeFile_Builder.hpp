


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
#include <cctype>
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Executable_MakeFile_Script_Builder.hpp"
#include "Project_Script_Writer.h"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "Repo_Warehouse_Initializer.h"
#include "CharOperator.h"
#include "IntToCharTranslater.h"



class Executable_MakeFile_Builder
{
public:
 Executable_MakeFile_Builder(char * des_path, char opr_sis);
 virtual ~Executable_MakeFile_Builder();
 void Build_MakeFile(char * path, char * Exe_Name, char c);
 void Clear_Dynamic_Memory();
protected:
 void Advanced_MakeFile_Construction(char * mn_src_path, char * Exe_Name, char strategy);
 void Simple_MakeFile_Construction(char * mn_src_path, char * Exe_Name, char strategy);
 void Write_MakeFile(char * Exe_Name);
 void Write_MakeFile_For_Simple_Construction(char * Exe_Name);
 void Determine_New_Directory_Path();
 void Receive_Exe_File_Name(char * Exe_Name);
 void Construct_New_Directory_For_Build_Files();
 void Script_Name_Determination(std::string & name, char * src_file_name);
 Git_Data_Processor Git_Data_Proc;
 Executable_MakeFile_ComConstructor ComConstructor;
 Executable_MakeFile_Script_Builder Script_Builder;
 Source_File_Dependency_Determiner  Dep_Determiner;
 Project_Script_Writer Project_Rebuild_Script_Writer;
 Descriptor_File_Reader Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::vector<Compiler_Data> * Com_Data_ptr;
 const Simple_Source_File_Dependency * Simple_Data_Ptr;
 std::string Src_File_Dir;
 std::string git_src_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string make_file_name;
 std::string object_file_list;
 std::string header_file_list;
 std::string Dependency_Code_Line;
 std::string Compiler_System_Command;
 std::string source_file_name;
 std::string Exe_File_Name;
 std::string new_dir_path;
 std::string project_library_name;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_BUILDER_HPP */
