


// Header decleraiton

#ifndef DESCRIPTOR_FILE_READER_HPP
#define DESCRIPTOR_FILE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "Descriptor_File_Data_Collector.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader();
 Descriptor_File_Reader(const Descriptor_File_Reader & orig);
 virtual ~Descriptor_File_Reader();
 void Read_Descriptor_File(char * path);
 void Clear_Dynamic_Memory();
 char ** Get_Library_Directories();
 char ** Get_Source_File_Directories();
 char ** Get_Include_Directories();
 char ** Get_Main_File_Names();
 char ** Get_Exe_File_Names();
 char *  Get_Standard();
 char *  Get_Options();
 char *  Get_Warehouse_location();
 char *  Get_Root_Directory_Location();
 int Get_Library_Directory_Number();
 int Get_Source_File_Directory_Number();
 int Get_Include_Directory_Number();
 int Get_Exe_File_Name_Number();
 int Get_Main_File_Name_Number();
protected:
 void Receive_Descriptor_File_Path(char * path);
 void Read_Root_Directory_Location();
 void Read_Main_File_Names();
 void Read_Executable_File_Names();
 void Read_Warehouse_Location();
 void Read_Standard();
 void Read_Include_Directories();
 void Read_Source_File_Directories();
 void Read_Library_Directories();
 void Read_Options();
 void Place_String(char ** pointer, char * string);
 Descriptor_File_Data_Collector Data_Collector;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 int include_dir_num;
 int source_file_dir_num;
 int lib_dir_num;
 int main_file_name_num;
 int exec_file_name_num;
 char * file_path;
 char * standard;
 char * options;
 char * root_dir;
 char * warehouse_location;
 char ** Include_Directories;
 char ** Source_File_Directories;
 char ** Library_Directories;
 char ** Main_File_Names;
 char ** Executable_File_Names;
 bool Memory_Delete_Condition;
};

#endif /* DESCRIPTOR_FILE_READER */
