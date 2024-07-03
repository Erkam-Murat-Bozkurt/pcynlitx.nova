




#ifndef CMAKE_TARGET_LIBRARY_BUILDER_HPP
#define CMAKE_TARGET_LIBRARY_BUILDER_HPP

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
 CMAKE_Executable_Target_Constructor();
 virtual ~CMAKE_Executable_Target_Constructor();
 void Build_MakeFile(std::string file_path, std::string exe_name);
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Operating_System(char opr_sis);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 void Find_Construction_Directory(std::string & upper, std::string dir);
 void Convert_CMAKE_Format(std::string & str);
 void Clear_String_Vector(std::vector<std::string> & str); 
 void Clear_String_Memory(std::string & pointer);
 void CMAKE_Sub_Directory_File_Path_Determination(std::string & path);
 void CMAKE_SubDir_Determination(std::string & sub_dir_path);
 Source_File_Dependency_Determiner * Dep_Determiner;
 Descriptor_File_Reader * Des_Reader;
 StringOperator StrOpr;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 Compiler_Data * Data_Ptr;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_TARGET_LIBRARY_BUILDER_HPP */
