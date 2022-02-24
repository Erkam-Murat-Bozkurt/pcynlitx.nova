

#ifndef MAKEFILE_DATA_COLLECTOR_H
#define MAKEFILE_DATA_COLLECTOR_H

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
#include <windows.h>
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class MakeFile_Data_Collector
{
public:
 MakeFile_Data_Collector();
 MakeFile_Data_Collector(const MakeFile_Data_Collector & orig);
 virtual ~MakeFile_Data_Collector();
 void Collect_Make_File_Data();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * pointer);
 void Receive_Git_Record_Data(Project_Files_Lister * pointer, int git_index);
 char * Get_Source_File_Name();
 char * Get_Make_File_Name();
 char * Get_Compiler_System_Command();
 char * Get_Dependency_Code_Line();
 char * Get_Object_File_Name();
 char * Get_Git_Header_File_Dir();
 char * Get_System_Header_File_Dir();
 char * Get_Source_File_Name_With_Extention();
 char * Get_Repo_Dir();
 char * Get_Warehouse_Header_Dir();
 char * Get_Warehouse_Object_Dir();
 char * Get_Warehouse_Path();
 char * Get_Git_Repo_Header_File_Path();
 char ** Get_Included_Header_Files();
 int  Get_Included_Header_Files_Number();
 void Clear_Dynamic_Memory();
private:
 void Clear_Pointer_Memory(char ** pointer);
 void Receive_Source_File_Name(char * source_file_name);
 void Receive_Header_File_Name_With_Its_Extention(char * header_file_name);
 void Receive_Git_Header_File_Path(char * header_path);
 void Determine_Header_File_Exact_Path(char operating_sis);
 void Receive_Warehouse_Path(char * warehouse_path);
 void Receive_Repo_Directory(char * repo_dir);
 void Determine_Header_File_Directory(char operating_sis);
 void Determine_Make_File_Name();
 void Determine_Dependency_Code_Line();
 void Place_Information(char ** Pointer, char * Information, int * index_counter);
 void Find_File_Names_With_Extention();
 void Determine_Included_Header_Files_Number();
 void Determine_Object_File_Names();
 void Read_Include_File_Names();
 void Determine_Compiler_System_Command(char * Include_Directory_Location);
 bool Include_Line_Determiner(std::string String_Line);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Determine_Warehouse_Object_Dir(char operating_sis);
 void Determine_Git_Header_File_Directory(char operating_sis);
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 Header_File_Determiner Header_Determiner;
 IntToCharTranslater Translater;
 Descriptor_File_Reader * Des_Reader_Pointer;
 Project_Files_Lister * File_Lister_Pointer;
 std::string String_Line;
 char * git_header_dir;
 char * repo_dir;
 char * warehouse_head_dir;
 char * warehouse_obj_dir;
 char * warehouse_path;
 char * Make_File_Name;
 char * Dependency_Code_Line;
 char * Git_Header_File_Path;
 char * Header_File_Exact_Path;
 char * Header_File_Directory;
 char * Source_File_Name;
 char * Header_File_Name_With_Ext;
 char * Source_File_Name_With_Ext;
 char * Object_File_Name;
 char * Compiler_System_Command;
 char ** Included_Header_Files;
 int  Included_Header_Files_Number;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKEFILE_DATA_COLLECTOR_H */
