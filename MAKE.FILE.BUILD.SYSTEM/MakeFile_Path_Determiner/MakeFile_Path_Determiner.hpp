

#ifndef MAKEFILE_PATH_DETERMINER_H
#define MAKEFILE_PATH_DETERMINER_H

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
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class MakeFile_Path_Determiner
{
public:
 MakeFile_Path_Determiner();
 virtual ~MakeFile_Path_Determiner();
 void Determine_MakeFile_Data(std::string file_name);
 void Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Operating_System(char opr_sis);
 void Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr);
 void Set_CMAKE_Construction_Status(bool is_cmake);
 std::string Get_Warehouse_Object_Dir();
 std::string Get_Repo_Dir();
 std::string Get_Dependency_Code_Line();
 std::string Get_Compiler_System_Command();
 std::string Get_MakeFile_Path();
 std::string Get_Source_File_Git_Record_Dir();
 std::vector<std::string> * Get_Header_Vpaths();
 std::vector<std::string> * Get_Header_Vpath_Alias();
 std::vector<std::string> * Get_Upper_Directory_Vpaths();
 std::vector<std::string> * Get_Upper_Directory_Vpaths_Alias();
 std::vector<std::string> * Get_Determined_Upper_Directories();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
private:
 Compiler_Data * Find_Compiler_Data_From_Source_File_Path(std::string name);
 void Determine_Dependent_Headers_Vpath_Alias();
 void Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path);
 void Determine_Header_Vpaths();
 void Determine_Make_File_Name();
 void Determine_MakeFile_Path(std::string & make_file_path, 
      std::string make_file_name);
 void VPATH_Determiner(std::string & path, std::string hdr_name, std::string dir);
 void VPATH_Alias_Determiner(std::string & path, std::string hdr_name);
 void Upper_Directory_VPATH_Determiner(std::string & upper_dir_vpath, std::string dir, int index);
 void Upper_Directory_VPATH_Alias_Determiner(std::string & upper_dir_vpath_alias, int index);
 bool Check_String_Existance(std::vector<std::string> & list, std::string str);
 void Determine_Upper_VPATH_Directories();
 void Find_Upper_Directory(std::string & upper_dir, std::string dir);
 void Research_For_More_Upper_Directory();
 std::string Search_For_New_Upper_Directory(std::vector<std::string> & dir_list, std::string dir);
 void Clear_String_Vector(std::vector<std::string> & str); 
 void Clear_String_Memory(std::string & pointer);
 MakeFile_Data_Collector Data_Collector;
 Descriptor_File_Reader * Des_Reader;
 std::vector<std::string> headers_vpaths;
 std::vector<std::string> headers_vpath_alias;
 std::vector<std::string> upper_directory_vpaths;
 std::vector<std::string> upper_dir_vpaths_alias;
 std::vector<std::string> new_upper_directories;
 std::unordered_map<std::string, Compiler_Data> * DataMap_Pointer;
 std::vector<Compiler_Data> * Comp_Data_Ptr;
 Compiler_Data * Data_Ptr;
 std::string source_file_git_record_dir;
 std::string make_file_path;
 std::string make_file_name;
 char opr_sis;
 bool is_cmake_construction;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKEFILE_PATH_DETERMINER_H */
