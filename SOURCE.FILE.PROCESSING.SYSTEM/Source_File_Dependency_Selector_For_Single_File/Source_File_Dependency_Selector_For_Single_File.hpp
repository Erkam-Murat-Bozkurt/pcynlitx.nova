





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
 std::string Get_Warehouse_Headers_Dir();
 std::string Get_Warehouse_Objetcs_Dir();
 std::string Get_Warehouse_Path();
 std::vector<std::vector<Source_File_Dependency>> * Get_Dependency_List_Adress();
 std::vector<Source_File_Dependency> * Get_Dependency_List_Element_Adress(int num);
 size_t  Get_Dependency_List_Size();
protected:
 void Extract_Directory_From_Path(std::string path, std::string & dir);
 void Extract_Dependency_Tree(std::string path, int thr_num);
 void Extract_Dependency_Data(int thr_num, int start, int end);
 void Set_Included_Header_Number(std::vector<Source_File_Dependency> * ptr);
 void Determine_Header_Repo_Warehouse_Path( std::string * wrd_path,
      std::string file_name, char opr_sis);
 void Place_String(std::string * str_pointer, std::string string);
 void Extract_File_Name_From_Path(std::string * ptr, std::string str);
 void Clear_String_Memory(std::string & Pointer);
 void Clear_Vector_Memory(std::vector<Source_File_Dependency> * pointer);
 void Clear_Temporary_String_Memory(Source_File_Dependency * temp);
 void Determine_Header_System_Path(std::string & path, std::string name);
 void Set_Dependency_Data(Source_File_Dependency & data, std::string path, std::string header_name);
 std::string Get_Header_System_Path(std::string header_name);
 void Clear_Dependency_Data_Extractors();
 void Construct_Dependency_Data_Extractors();
 void Determine_Object_File_Name(std::string & obj_name, std::string src_name);
 void Determine_Git_Record_Source_File_Directory( std::string git_record_system_path, 
 std::string & record_dir);
 void Determine_File_Name_Without_Ext(std::string path, std::string & file_name);
 Source_File_Information_Collector_For_Single_File Info_Collector; 
 Source_File_Data_Setter Data_Setter;
 Dependency_Data_Extractor ** Dep_Data_Collectors;
 Project_Src_Code_Rdr * Code_Rd;
 Git_Data_Processor * Git_Data_Proc;
 std::vector<Source_File_Dependency> Dependent_List[16];
 std::vector<Source_File_Dependency> Dependent_List_Buffer;
 std::vector<Source_File_Data> * Source_File_Data_Ptr;
 std::vector<std::vector<Source_File_Dependency>> Dependency_Data;
 std::string warehouse_head_dir;
 std::string descriptor_file_path;
 std::mutex mtx;
 std::thread threads[16];
 char opr_sis;
 int  header_file_number;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool This_File_Exist;
};

#endif /* SOURCE_FILE_DEPENDENCY_SELECTOR_FOR_SINGLE_FILE_HPP */
