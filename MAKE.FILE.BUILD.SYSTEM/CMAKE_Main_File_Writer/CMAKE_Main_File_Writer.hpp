




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
 void Build_Main_CMAKE_File();
 void Receive_Git_Data_Processor(Git_Data_Processor * Git_Proc);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Operating_System(char opr_sis);
 std::vector<Git_Sub_Directory_Data> * Get_CMAKE_Root_Dirs();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 void Clear_String_Vector(std::vector<std::string> & str); 
 void Clear_String_Memory(std::string & pointer);
 void CMAKE_SubDirectory_Determination();
 void Write_CMAKE_Sub_Directory_Declerations();
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::unordered_map<std::string, Compiler_Data> * DataMap_Pointer;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 Git_Data_Processor * Git_Processor;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_MAIN_FILE_WRITER_HPP */
