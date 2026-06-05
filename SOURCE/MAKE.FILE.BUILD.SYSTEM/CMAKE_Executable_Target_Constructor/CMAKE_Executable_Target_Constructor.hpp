




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
#include "CMAKE_Target_List_Data_Structure_Constructor.hpp"
#include "CMAKE_Target_List_Data_Processor.hpp"
#include "CMAKE_Target_List_Determiner.hpp"
#include "Build_System_Meta_Data_Collector.hpp"
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

 void Extract_Directory_Short_Path(std::string sys_dir, 

      std::vector<std::string> & sort_dir_path); 

 void Extract_Repo_Directory_Name(std::string & name, std::string root_dir);

 std::string Extract_Git_Record_Path(std::string path);

 void Find_File_Name_Without_Extension(std::string hdr_name, 

     std::string & file_name_with_ext);

 void Construct_Target_Library_Dependencies_for_Executable();

 std::vector<std::string> target_library_dependencies;

 CMAKE_Target_List_Data_Structure_Constructor Target_List_Data_Structure_Constructor;

 Source_File_Dependency_Determiner Dep_Determiner;

 Custom_System_Interface * SysInt;

 StringOperator StrOpr;

 Cpp_FileOperations FileManager;

 std::vector<Compiler_Data> * Comp_Data_Ptr;

 std::string DesPATH;

 char build_type;

 char opr_sis;

 bool Include_Line_Condition;

 bool Memory_Delete_Condition;
};

#endif /* CMAKE_EXECUTABLE_TARGET_CONSTRUCTOR_HPP */
