







#ifndef QUICK_SRC_DEPENDENCY_EXTRACTOR_HPP
#define QUICK_SRC_DEPENDENCY_EXTRACTOR_HPP

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
#include "Source_File_Data_Setter.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Processor.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"



/*
   
   THIS CLASS IS USED IN EXECUTABLE MAKE FILE CONSTRUCTION.

   The data type "Simple_Source_File_Dependency" data structure is used
   for the quick construction of make file data. When the file naming convations
   can not preserve, an object file for each source file is constructed by the 
   automatically written scripts. Then, on the make file's compiler command, 
   a simple link is given with a linker to the project library (the library
   which is constructed for the whole project). 
   
*/

struct Simple_Source_File_Dependency 
{
  std::string source_file_name; // The header file which its dependencies are researched 
  std::string source_file_name_without_ext;
  std::string src_git_record_dir;
  std::string src_sys_dir;
  std::string source_file_path;
  std::string Combined_Header_Name;
  std::string dir;
  std::string object_file_name;
  std::vector<std::string> External_Headers;
  std::vector<std::string> Dependent_Header_Names;
  std::vector<std::string> Dependent_Header_Directories;
  std::vector<std::string> Dependent_Header_Paths;
  std::vector<std::string> Include_Declerations;
  int included_file_hdr_num;
};


class Quick_Src_Dependency_Extractor
{
public:
 Quick_Src_Dependency_Extractor(char opr_sis);
 virtual ~Quick_Src_Dependency_Extractor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Data(std::string src_file_path);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 bool Is_Header_File(std::string hpath);
 const Simple_Source_File_Dependency * Get_Simple_Source_File_Dependency() const; 
 const std::vector<Search_Data> * Get_Dependency_Search_Data() const;
 const std::vector<std::string> * Get_Root_File_External_Headers() const;
 std::string  Get_Warehouse_Objetcs_Dir();
 std::string  Get_Warehouse_Path();

protected:
 void Extract_Dependency_Search_Data(std::string src_file_path); // Dependency data extraction for a single file
 void Determine_Warehouse_Object_Dir();
 void Set_Dependency_Data(std::string src_file_path);
 void Extract_Directory_File_Name_Combination(std::string path, std::string & dir_file_com);
 void Extract_Directory_From_Path(std::string & dir, std::string path);
 void Receive_String_Vector(std::vector<std::string> & target_vec, 
      const std::vector<std::string> * vec);
 void Clear_String_Memory(std::string & str);
 void Clear_Search_Data();
 void Clear_External_Headers_Memory();
 void Clear_Dependency_Data();
 void Clear_Vector_Memory(std::vector<std::string> & str);
 Source_File_Data_Setter Data_Setter;
 Simple_Source_File_Dependency Dep_Data;
 Dependency_Data_Extractor Dep_Extractor;
 std::vector<Search_Data> Dep_Search_Data;
 std::vector<std::string> Root_File_External_Headers;
 Project_Src_Code_Rdr   * Code_Rdr;
 Descriptor_File_Reader * Des_Reader;
 Git_Data_Processor     * Git_Data_Proc;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* QUICK_SRC_DEPENDENCY_EXTRACTOR_HPP */
