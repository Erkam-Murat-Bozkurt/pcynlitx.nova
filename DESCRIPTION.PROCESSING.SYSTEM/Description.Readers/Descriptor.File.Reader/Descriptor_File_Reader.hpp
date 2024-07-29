


// Header decleraiton

#ifndef DESCRIPTOR_FILE_READER_HPP
#define DESCRIPTOR_FILE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Descriptor_File_Data_Collector.hpp"
#include "Descriptor_File_Syntax_Controller.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader(char opr_sis, char build_type);
 virtual ~Descriptor_File_Reader();
 void Read_Descriptor_File();
 void Clear_Dynamic_Memory();
 void Receive_Descriptor_File_Path(char * DesPATH);
 void Receive_Descriptor_File_Path(std::string DesPATH);
 void Receive_Data_Record_Condition(bool cond);
 void Set_Gui_Read_Status(bool status);
 std::string Get_Library_Directory(int i);
 std::string Get_Library_File(int i);
 std::string Get_Source_File_Directory(int i);
 std::string Get_Include_Directory(int i);
 const std::vector<std::string> & Get_Include_Directories();
 const std::vector<std::string> & Get_Library_Directories();
 const std::vector<std::string> & Get_Source_File_Directories();
 const std::vector<std::string> & Get_Library_Files();
 const std::vector<std::string> & Get_Exe_File_Names();  
 std::string Get_Standard();
 std::string Get_Build_System_Type();
 std::string Get_Compiler_Options();
 std::string Get_Linker_Options();
 std::string Get_Warehouse_Location();
 std::string Get_Repo_Directory_Location();
 std::string Get_Descriptor_File_Path();
 std::string Get_Error_Message();
 int Get_Library_Directory_Number();
 int Get_Library_Files_Number();
 int Get_Source_File_Directory_Number();
 int Get_Include_Directory_Number();
 bool Get_Gui_Read_Success_Status();
 bool Get_Gui_Read_Status();
 bool Get_Syntax_Error_Status();
 bool Get_Invalid_Descriptor_File_Status();
protected:
 void Initialize_Members();
 void Read_Root_Directory_Location();
 void Read_Warehouse_Location();
 void Read_Standard();
 void Read_Include_Directories();
 void Read_Source_File_Directories();
 void Read_Library_Directories();
 void Read_Library_Files();
 void Read_Compiler_Options();
 void Read_Linker_Options();
 void Read_Build_System_Type();
 bool Is_Include_Character(std::string str);
 void Delete_Spaces_on_String(std::string * str);
 void Divide_Options(std::string & options);
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
 std::string build_system;
 std::string compiler_options;
 std::string linker_options;
 std::string root_dir;
 std::string warehouse_location;
 std::string error_message;
 std::vector<std::string> Include_Directories;
 std::vector<std::string> Source_File_Directories;
 std::vector<std::string> Library_Directories;
 std::vector<std::string> Library_Files;
 bool gui_read_status;
 bool gui_read_success;
 bool gui_syntax_error;
 bool is_project_file_invalid;
 bool Memory_Delete_Condition;
 bool Data_Record_Cond;
};

#endif /* DESCRIPTOR_FILE_READER */
