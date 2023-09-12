
#ifndef MAKE_FILE_BUILDER_H
#define MAKE_FILE_BUILDER_H

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
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class Make_File_Builder
{
public:
 Make_File_Builder(char opr_sis);
 virtual ~Make_File_Builder();
 void Build_MakeFile(std::string file_name);
 void Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Construct_Data_Map();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 Compiler_Data * Find_Compiler_Data_From_Source_File_Name(std::string name);
 void Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path);
 void Write_Header_Paths_Shorts_Cuts();
 MakeFile_Data_Collector Data_Collector;
 //Project_Files_Lister * File_Lister;
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 std::unordered_map<std::string, Compiler_Data> DataMap;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 Compiler_Data * Data_Ptr;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKE_FILE_BUILDER_H */
