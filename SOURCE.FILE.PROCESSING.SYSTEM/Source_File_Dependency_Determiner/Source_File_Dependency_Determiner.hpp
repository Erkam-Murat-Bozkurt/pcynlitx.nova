



#ifndef SOURCE_FILE_DEPENDENCY_DETERMINER_HPP
#define SOURCE_FILE_DEPENDENCY_DETERMINER_HPP

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
#include "Source_File_Compiler_Data_Extractor.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Source_File_Processor.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


class Source_File_Dependency_Determiner
{
public:
 Source_File_Dependency_Determiner(char * des_file_path, char opr_sis);
 virtual ~Source_File_Dependency_Determiner();
 void Collect_Dependency_Information();
 void Collect_Dependency_Information(std::string path);
 bool Is_Source_File(std::string spath);
 bool Is_Header_File(std::string hpath);
 int  Get_Compiler_Data_Size();
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 void Print_Dependency_List();
 void Print_Compiler_Orders();
 void Clear_Object_Memory();
 void Clear_Dynamic_Memory();
 Compiler_Data Get_Compiler_Data(int i);
 std::vector<Compiler_Data> * Get_Compiler_Data_Address();
protected:
 void Order_Priorities(); 
 Git_File_List_Receiver Git_Data_Receiver;
 Project_Src_Code_Rdr Code_Rd;
 Source_File_Dependency_Selector DepSelector;
 Source_File_Compiler_Data_Extractor Com_Data_Extractor;
 Source_File_Processor Src_Processor;
 std::string Warehouse_Headers_Dir;
 std::string Warehouse_Objetcs_Dir;
 std::string Warehouse_Path;
 std::vector<Compiler_Data> * Compiler_Data_Ptr;
 size_t  data_size;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DEPENDENCY_DETERMINER_HPP */
