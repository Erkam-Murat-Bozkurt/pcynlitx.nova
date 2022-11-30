



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
#include "Source_File_Dependency_Selector.hpp"
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


class Source_File_Dependency_Determiner
{
public:
 Source_File_Dependency_Determiner();
 Source_File_Dependency_Determiner(const Source_File_Dependency_Determiner & orig);
 virtual ~Source_File_Dependency_Determiner();
 void Receive_Source_File_Information_Collector(Source_File_Information_Collector * DataCollector);
 void Determine_Dependencies();
 void Print_Compiler_Orders();
 void Clear_Dynamic_Memory();
 Compiler_Data_CString Get_Compiler_Data(int i);
 Compiler_Data_CString * Get_Compiler_Data_Pointer();
 int    Get_Compiler_Data_Size();
 char * Get_Warehouse_Headers_Dir();
 char * Get_Warehouse_Objetcs_Dir();
 char * Get_Warehouse_Path();
protected:
 void Search_Recursive_Include_Dependency(int index);
 void Determine_Compile_Order();
 void Receive_Collector_Info();
 void Order_Priorities();
 Source_File_Information_Collector * Info_Collector;
 Source_File_Dependency_Selector DepSelector;
 Compiler_Data_CString * Data_Ptr_CString;
 CharOperator Char_Processor;
 int  header_file_number;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DEPENDENCY_DETERMINER_HPP */
