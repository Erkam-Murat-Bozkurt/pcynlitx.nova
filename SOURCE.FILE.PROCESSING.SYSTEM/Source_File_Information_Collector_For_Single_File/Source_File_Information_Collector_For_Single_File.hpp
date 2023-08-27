






#ifndef SOURCE_FILE_INFORMATION_COLLECTOR_FOR_SINGLE_FILE_HPP
#define SOURCE_FILE_INFORMATION_COLLECTOR_FOR_SINGLE_FILE_HPP

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
#include <vector>
#include <thread>
#include <mutex>
#include "Source_File_Information_Collector.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Processor.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"



class Source_File_Information_Collector_For_Single_File
{
public:
 Source_File_Information_Collector_For_Single_File(char opr_sis);
 virtual ~Source_File_Information_Collector_For_Single_File();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Data(std::string src_file_path); // Dependency data extraction for a single file
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 bool Is_Header_File(std::string hpath);
 Source_File_Data Get_Dependency_Data(int num);
 std::vector<Source_File_Data> * Get_Source_File_Data_Address();
 size_t       Get_Dependency_Data_Size();
 std::string  Get_Warehouse_Headers_Dir();
 std::string  Get_Warehouse_Objetcs_Dir();
 std::string  Get_Warehouse_Path();

protected:
 void Determine_Root_Source_File_Header_Dependencies(std::string src_file_path);
 void Determine_Related_Source_Files_From_Header_Dependencies();
 void Find_File_Name_Without_Extantion(std::string hdr_name, std::string & file_name_with_ext);
 void Determine_Warehouse_Object_Dir();
 void Determine_Warehouse_Header_Dir();
 void Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,
      std::string file_name, char opr_sis);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name,
      std::string string);
 void Determine_Header_System_Path(std::string * sys_path,std::string path);
 bool Include_Decleration_Test(std::string string);
 bool CompareString(std::string sr1, std::string sr2);
 void Clear_Buffer_Memory();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Headers_Data();
 std::vector<Search_Data> Dep_Search_Data;
 std::vector<std::string> Dependent_Source_File_Names;
 std::vector<Source_File_Data> Src_Data_Holder;
 Dependency_Data_Extractor ** Dep_Data_Collectors;
 Project_Src_Code_Rdr * Code_Rdr;
 StringOperator StringManager;
 Descriptor_File_Reader * Des_Reader;
 Git_Data_Processor * Git_Data_Proc;
 Source_File_Processor Src_File_Pr;
 Header_File_Processor Header_Processor;
 Source_File_Data buffer;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::mutex mtx;
 std::thread threads[8];
 char opr_sis;
 bool include_decleration_cond;
 bool Memory_Delete_Condition;
 bool is_independent_header;
 bool isStringsEqual;
};

#endif /* SOURCE_FILE_INFORMATION_COLLECTOR_FOR_SINGLE_FILE_HPP */
