


#ifndef CMAKE_LIST_BUILDER_HPP
#define CMAKE_LIST_BUILDER_HPP

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
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class CMake_List_Builder
{
public:
 CMake_List_Builder();
 virtual ~CMake_List_Builder();
 void Build_MakeFile(std::string file_name);
 void Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Operating_System(char opr_sis);
 void Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 Compiler_Data * Find_Compiler_Data_From_Source_File_Path(std::string name);
 void Convert_CMAKE_Format(std::string & str);
 void Clear_String_Vector(std::vector<std::string> & str); 
 void Clear_String_Memory(std::string & pointer);
 MakeFile_Path_Determiner Path_Determiner;
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::unordered_map<std::string, Compiler_Data> * DataMap_Pointer;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 Compiler_Data * Data_Ptr;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_LIST_BUILDER_HPP */
