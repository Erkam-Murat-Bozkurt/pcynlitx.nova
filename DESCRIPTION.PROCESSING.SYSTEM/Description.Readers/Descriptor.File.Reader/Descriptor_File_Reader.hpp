


// Header decleraiton

#ifndef DESCRIPTOR_FILE_READER_HPP
#define DESCRIPTOR_FILE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Record_Number_Determiner.hpp"
#include "Descriptor_File_Line_Reader.hpp"
#include "Descriptor_File_Data_Collector.hpp"
#include "Descriptor_File_Syntax_Controller.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

struct Library_Data
{
    std::string library_dir;
    std::string library_name_with_ext;
    std::string library_name_without_ext;
};

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader(char opr_sis);
 virtual ~Descriptor_File_Reader();
 void Read_Descriptor_File();
 void Clear_Dynamic_Memory();
 void Receive_Descriptor_File_Path(char * DesPATH);
 void Receive_Descriptor_File_Path(std::string DesPATH);
 void Receive_Data_Record_Condition(bool cond);
 std::string Get_Library_Directory(int i);
 std::string Get_Library_File(int i);
 std::string Get_Source_File_Directory(int i);
 std::string Get_Include_Directory(int i);
 void Extract_Library_Names_From_Path();
 const std::vector<std::string> & Get_Include_Directories();
 const std::vector<std::string> & Get_Library_Directories();
 const std::vector<std::string> & Get_Source_File_Directories();
 const std::vector<std::string> & Get_Library_Files();
 const std::vector<std::string> & Get_Exe_File_Names();  
 const std::vector<std::string> & Get_Compiler_Options();
 const std::vector<std::string> & Get_Linker_Options();
 const std::vector<std::string> & Get_Compiler_Paths();
 const std::vector<Library_Data> & Get_Library_File_Data_List();
 std::string Get_Standard();
 std::string Get_Build_System_Type();
 std::string Get_Warehouse_Location();
 std::string Get_Repo_Directory_Location();
 std::string Get_Descriptor_File_Path();
 std::string Get_Error_Message();
 std::string Get_Project_Name();
 std::string Get_Version_Number();
 int Get_Library_Directory_Number();
 int Get_Library_Files_Number();
 int Get_Source_File_Directory_Number();
 int Get_Include_Directory_Number();
 bool Get_Invalid_Descriptor_File_Status();
 bool Get_Syntax_Error_Status();
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
 void Read_Project_Name();
 void Read_Version_Number();
 void Read_Compiler_Paths();
 void Read_Descriptions();
 void Determine_File_Name_Without_Ext(std::string path, std::string & file_name);
 void Determine_File_Name_Without_Ext(char * path, std::string & name);
 void Extract_Directory_From_Path(std::string path, std::string & dir);
 void Extract_File_Name_From_Path(std::string string, std::string & name);

 
 bool Is_This_String_A_File_Path(std::string str);
 bool Is_There_Multiple_Decleration_on_Same_Line(std::string & str_line);
 void Extract_Declerations_Performing_on_Same_Line(std::string str_line, std::vector<std::string> & mt_line);
 void Divide_Options(std::string & options);
 void Clear_String_Memory(std::string * ptr);
 void Clear_Vectory_Memory(std::vector<std::string> * ptr);


 void Exit_With_Error(std::string error);

 Descriptor_File_Line_Reader Line_Reader;
 Descriptor_File_Data_Collector Data_Collector;
 Descriptor_File_Syntax_Controller Syntax_Controller;
 Record_Number_Determiner Number_Determiner;
 int include_dir_num;
 int source_file_dir_num;
 int compiler_path_number;
 int lib_dir_num;
 int lib_file_num;
 int main_file_name_num;
 int exec_file_name_num;
 std::string descriptor_file_path;
 std::string standard;
 std::string build_system;
 std::string root_dir;
 std::string project_name;
 std::string version_number;
 std::string warehouse_location;
 std::string error_message;
 std::vector<std::string> Include_Directories;
 std::vector<std::string> Source_File_Directories;
 std::vector<std::string> Library_Directories;
 std::vector<std::string> Library_Files;
 std::vector<std::string> compiler_options;
 std::vector<std::string> linker_options;
 std::vector<std::string> compiler_paths;
 std::vector<Library_Data> library_data_list;
 bool syntax_error_status;
 bool lack_of_decleration_error;
 bool is_project_file_invalid;
 bool Memory_Delete_Condition;
 bool Data_Record_Cond;
 char opr_sis;
};

#endif /* DESCRIPTOR_FILE_READER */
