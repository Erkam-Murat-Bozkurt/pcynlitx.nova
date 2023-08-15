


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
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Repo_Warehouse_Initializer.h"
#include "CharOperator.h"
#include "IntToCharTranslater.h"



class Executable_MakeFile_Builder
{
public:
 Executable_MakeFile_Builder(char * des_path, char opr_sis);
 virtual ~Executable_MakeFile_Builder();
 void Build_MakeFile(char * path, char * Exe_Name);
 void Clear_Dynamic_Memory();
protected:
 void Write_MakeFile(char * Exe_Name);
 Git_Data_Processor Git_Data_Proc;
 Executable_MakeFile_ComConstructor ComConstructor;
 Source_File_Dependency_Determiner  Dep_Determiner;
 Descriptor_File_Reader Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::vector<Compiler_Data> * Com_Data_ptr;
 std::string Src_File_Dir;
 std::string git_src_dir;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string make_file_name;
 std::string object_file_list;
 std::string header_file_list;
 std::string Dependency_Code_Line;
 std::string Compiler_System_Command;
 int  header_file_number;
 bool Memory_Delete_Condition;
};

#endif /* EXECUTABLE_MAKEFILE_BUILDER_HPP */
