


// Header decleraiton

#ifndef DESCRIPTOR_FILE_READER_HPP
#define DESCRIPTOR_FILE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "Descriptor_File_Data_Collector.hpp"
#include "Descriptor_File_Syntax_Controller.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader(char opr_sis);
 virtual ~Descriptor_File_Reader();
 void Read_Descriptor_File();
 void Clear_Dynamic_Memory();
 void Receive_Descriptor_File_Path(char * DesPATH);
 void Receive_Descriptor_File_Path(std::string DesPATH);
 std::string Get_Library_Directory(int i);
 std::string Get_Library_File(int i);
 std::string Get_Source_File_Directory(int i);
 std::string Get_Include_Directory(int i);
 std::string Get_Standard();
 std::string Get_Options();
 std::string Get_Warehouse_Location();
 std::string Get_Repo_Directory_Location();
 int Get_Library_Directory_Number();
 int Get_Library_Files_Number();
 int Get_Source_File_Directory_Number();
 int Get_Include_Directory_Number();
protected:
 void Initialize_Members();
 void Read_Root_Directory_Location();
 void Read_Warehouse_Location();
 void Read_Standard();
 void Read_Include_Directories();
 void Read_Source_File_Directories();
 void Read_Library_Directories();
 void Read_Library_Files();
 void Read_Options();
 void Divide_Options();
 void Clear_String_Memory(std::string * ptr);
 void Clear_Vectory_Memory(std::vector<std::string> * ptr);
 Descriptor_File_Data_Collector Data_Collector;
 Descriptor_File_Syntax_Controller Syntax_Controller;
 StringOperator StringManager;
 int include_dir_num;
 int source_file_dir_num;
 int lib_dir_num;
 int lib_file_num;
 int main_file_name_num;
 int exec_file_name_num;
 std::string descriptor_file_path;
 std::string standard;
 std::string options;
 std::string root_dir;
 std::string warehouse_location;
 std::vector<std::string> Include_Directories;
 std::vector<std::string> Source_File_Directories;
 std::vector<std::string> Library_Directories;
 std::vector<std::string> Library_Files;
 bool Memory_Delete_Condition;
};

#endif /* DESCRIPTOR_FILE_READER */
