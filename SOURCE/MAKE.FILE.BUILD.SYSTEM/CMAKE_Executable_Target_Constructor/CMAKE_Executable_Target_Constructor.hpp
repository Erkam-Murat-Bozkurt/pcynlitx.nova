




#ifndef CMAKE_EXECUTABLE_TARGET_CONSTRUCTOR_HPP
#define CMAKE_EXECUTABLE_TARGET_CONSTRUCTOR_HPP

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
#include <map>
#include <unordered_map>
#include <iterator>
#include "MakeFile_Path_Determiner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class CMAKE_Executable_Target_Constructor
{
public:
 CMAKE_Executable_Target_Constructor(char * DesPath, char opr_sis, char build_type);
 virtual ~CMAKE_Executable_Target_Constructor();
 void Build_MakeFile(std::string file_path, std::string exe_name);
 void Receive_System_Interface(Custom_System_Interface * sysInt);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 void Find_Construction_Directory(std::string & upper, std::string dir);
 void Convert_CMAKE_Format(std::string & str);
 void Clear_String_Vector(std::vector<std::string> & str); 
 void Clear_String_Memory(std::string & pointer);
 void CMAKE_Sub_Directory_File_Path_Determination(std::string & path);
 void CMAKE_SubDir_Determination(std::string & sub_dir_path);
 void Extract_Directory_Short_Path(std::string sys_dir, 
      std::vector<std::string> & sort_dir_path); 
 void Directory_Path_Encoder(std::string sys_dir, std::string & str_encode);
 void Determine_Project_Library_Name();
 void Extract_Repo_Directory_Name(std::string & name, std::string root_dir);
 Descriptor_File_Reader Des_Reader;
 Git_Data_Processor Data_Processor;
 Source_File_Dependency_Determiner Dep_Determiner;
 Custom_System_Interface * SysInt;
 StringOperator StrOpr;
 Cpp_FileOperations FileManager;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 const Simple_Source_File_Dependency * dep_ptr;
 Compiler_Data * Data_Ptr;
 std::string DesPATH;
 std::string project_library_name;
 char build_type;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_EXECUTABLE_TARGET_CONSTRUCTOR_HPP */
