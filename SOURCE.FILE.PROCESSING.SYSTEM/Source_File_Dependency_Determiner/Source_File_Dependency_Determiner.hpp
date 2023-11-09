



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
#include <map>
#include <unordered_map>
#include <iterator>
#include <utility>        // std::pair, std::make_pair
#include <stdexcept>      // std::out_of_range
#include <thread>
#include <mutex>
#include "Source_File_Compiler_Data_Extractor.hpp"
#include "Source_File_Dependency_Selector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Quick_Src_Dependency_Extractor.hpp"
#include "Source_File_Processor.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


struct Dependency_Table
{
   std::string src_file_name_witout_ext;
   int inclusion_number; // The number of included files
};

class Source_File_Dependency_Determiner
{
public:
 Source_File_Dependency_Determiner(char * des_file_path, char opr_sis);
 virtual ~Source_File_Dependency_Determiner();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Collect_Dependency_Information();
 void Collect_Dependency_Information(std::string path);
 void Simple_Dependency_Determination_For_Single_Source_File(std::string path);
 bool Is_Source_File(std::string spath);
 bool Is_Header_File(std::string hpath);
 int  Get_Compiler_Data_Size();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 void Print_Dependency_List();
 void Print_Compiler_Orders();
 void Clear_Object_Memory();
 void Clear_Dynamic_Memory();
 Compiler_Data Get_Compiler_Data(int i);
 std::vector<Compiler_Data> *  Get_Compiler_Data_Address();
 const Simple_Source_File_Dependency * Get_Simple_File_Dependencies();
protected:
 void Order_Priorities();
 void Re_Arrange_Priorities(); 
 void Construct_Dependency_Map();
 bool Check_Dependecy_Search_Status(std::string name);
 void Extract_File_Name_Without_Extention(std::string & name, std::string name_with_ext);
 void Control_Priorities(size_t start, size_t end);
 int Find_File_Priority(std::string name);
 void Clear_Compiler_Data_Memory(Compiler_Data & Data);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_String_Memory(std::string & str);
 void Clear_Compiler_Data_Vector(std::vector<Compiler_Data> * Data);
 Git_Data_Processor * Git_Data_Proc;
 Descriptor_File_Reader * Des_Reader;
 Project_Src_Code_Rdr Code_Rd;
 Source_File_Dependency_Selector DepSelector;
 Source_File_Dependency_Selector_For_Single_File DepSelector_For_Single_File;
 Source_File_Compiler_Data_Extractor Com_Data_Extractor;
 Source_File_Processor Src_Processor;
 Quick_Src_Dependency_Extractor Simple_Dep_Extractor;
 std::string Warehouse_Objetcs_Dir;
 std::string Warehouse_Path;
 std::vector<Compiler_Data> * Compiler_Data_Ptr;
 std::unordered_map<std::string, int> Dependency_Map;
 std::vector<std::thread> threadPool;
 std::mutex mtx;
 size_t  data_size;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DEPENDENCY_DETERMINER_HPP */
