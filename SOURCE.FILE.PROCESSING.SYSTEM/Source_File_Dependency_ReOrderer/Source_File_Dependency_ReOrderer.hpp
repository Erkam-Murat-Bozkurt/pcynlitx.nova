





#ifndef SOURCE_FILE_DEPENDENCY_REORDERER_HPP
#define SOURCE_FILE_DEPENDENCY_REORDERER_HPP

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
#include "Source_File_Dependency_Selector.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


class Source_File_Dependency_ReOrderer
{
public:
 Source_File_Dependency_ReOrderer();
 virtual ~Source_File_Dependency_ReOrderer();
 void Receive_Dependency_Data(std::vector<std::vector<Header_Dependency>> * ptr);
 void Reorder_Dependency_Data();
 void Print_Dependency_Data();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Determine_Headers_Dependencies();
 void Reorder_Data_Records();
 void Reorder_Data_Records(std::vector<Header_Dependency> * searc_ptr);
 std::vector<std::vector<Header_Dependency>> * Vector_List_ptr;
 std::vector<Header_Dependency> * Vector_ptr;
 std::vector<Header_Dependency> * Buffer_ptr;
 int  Find_Header_Dependency(std::string hdr_name);
 bool CompareString(std::string Str_1, std::string Str_2);
 bool isStringsEqual;
 int dependency;
};

#endif /* SOURCE_FILE_DEPENDENCY_REORDERER_HPP */
