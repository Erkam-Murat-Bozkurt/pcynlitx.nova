




#ifndef CMAKE_MAIN_FILE_WRITER_HPP
#define CMAKE_MAIN_FILE_WRITER_HPP

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
#include "Source_File_Determiner.h"
#include "Header_File_Determiner.h"
#include "Git_Data_Processor.hpp"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class CMAKE_Main_File_Writer
{
public:
 CMAKE_Main_File_Writer();
 virtual ~CMAKE_Main_File_Writer();
 void Build_Main_CMAKE_File(std::string project_name, std::string version_num);
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * dep_ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * Git_Proc);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Operating_System(char opr_sis);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 void Convert_CMAKE_Format(std::string & str);
 Source_File_Dependency_Determiner * Dep_Determiner;
 std::vector<Compiler_Data> * Compiler_Data_Pointer;
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 Git_Data_Processor * Git_Processor;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_MAIN_FILE_WRITER_HPP */
