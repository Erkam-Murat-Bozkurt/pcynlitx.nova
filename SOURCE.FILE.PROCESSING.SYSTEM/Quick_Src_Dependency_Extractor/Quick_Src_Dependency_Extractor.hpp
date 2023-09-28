







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



class Quick_Src_Dependency_Extractor
{
public:
 Quick_Src_Dependency_Extractor(char opr_sis);
 virtual ~Quick_Src_Dependency_Extractor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Search_Data(std::string src_file_path); // Dependency data extraction for a single file
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 bool Is_Header_File(std::string hpath);
 const std::vector<Search_Data> * Get_Dependency_Search_Data() const;
 const std::vector<std::string> * Get_Root_File_External_Headers() const;
 std::string  Get_Warehouse_Headers_Dir();
 std::string  Get_Warehouse_Objetcs_Dir();
 std::string  Get_Warehouse_Path();

protected:
 void Determine_Warehouse_Object_Dir();
 void Determine_Warehouse_Header_Dir();
 void Receive_String_Vector(std::vector<std::string> & target_vec, 
      const std::vector<std::string> * vec);
 void Clear_String_Memory(std::string & str);
 void Clear_Search_Data();
 void Clear_External_Headers_Memory();
 std::vector<Search_Data> Dep_Search_Data;
 std::vector<std::string> Root_File_External_Headers;
 Project_Src_Code_Rdr   * Code_Rdr;
 Descriptor_File_Reader * Des_Reader;
 Git_Data_Processor     * Git_Data_Proc;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* QUICK_SRC_DEPENDENCY_EXTRACTOR_HPP */
