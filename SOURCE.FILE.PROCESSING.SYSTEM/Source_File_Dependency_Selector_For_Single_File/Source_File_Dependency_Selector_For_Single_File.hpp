





#ifndef SOURCE_FILE_DEPENDENCY_SELECTOR_FOR_SINGLE_FILE_HPP
#define SOURCE_FILE_DEPENDENCY_SELECTOR_FOR_SINGLE_FILE_HPP

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
#include <thread>
#include <mutex>
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Data_Setter.hpp"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_Modification_Receiver.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
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


class Source_File_Dependency_Selector_For_Single_File
{
public:
 Source_File_Dependency_Selector_For_Single_File(char opr_sis);
 virtual ~Source_File_Dependency_Selector_For_Single_File();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Determine_Source_File_Dependencies(std::string path);
 bool Is_Header_File(std::string hpath);
 void Print_Dependency_List();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 std::vector<std::vector<Source_File_Dependency>> * Get_Dependency_List_Adress();
 std::vector<Source_File_Dependency> * Get_Dependency_List_Element_Adress(int num);
 size_t  Get_Dependency_List_Size();
protected:
 void Construct_Dependency_Data_Vector(std::string path, std::vector<Source_File_Dependency> & vec);
 void Arrange_Dependency_Data(int thr_num, int start, int end);
 void Set_Included_Header_Number(std::vector<Source_File_Dependency> & ptr);
 void Clear_String_Memory(std::string & Pointer);
 void Clear_Source_File_Dependency_Data(std::vector<Source_File_Dependency> & vec);
 void Set_Dependency_Data(Source_File_Dependency & data, std::string path, std::string header_name);
 std::string Get_Header_System_Path(std::string header_name);
 size_t Split_Range(size_t range_size, size_t partition, size_t & remaining_job);
 void Search_For_Large_Data_Set(size_t data_size);
 void Search_For_Middle_Data_Set(size_t data_size);
 void Search_For_Small_Data_Set(size_t data_size);
 Source_File_Information_Collector_For_Single_File Info_Collector; 
 Dependency_Data_Stack_Container Stack_Container;
 Source_File_Data_Setter Data_Setter;
 Project_Src_Code_Rdr * Code_Rd;
 Git_Data_Processor * Git_Data_Proc;
 std::vector<Source_File_Data> * Source_File_Data_Ptr;
 std::vector<std::vector<Source_File_Dependency>> Dependency_Data;
 std::mutex mtx;
 std::vector<std::thread> threadPool;
 char opr_sis;
 int  header_file_number;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool This_File_Exist;
};

#endif /* SOURCE_FILE_DEPENDENCY_SELECTOR_FOR_SINGLE_FILE_HPP */
