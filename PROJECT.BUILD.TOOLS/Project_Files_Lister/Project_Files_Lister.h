

#ifndef PROJECT_FILES_LISTER_H
#define PROJECT_FILES_LISTER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Header_File_Determiner.h"
#include "Source_File_Determiner.h"
#include "StringOperator.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

struct Source_Data {

  char * git_header_file_path;  // Header path in git record
  char * Source_File_Directory;
  char * Header_File_Path;     // Header file exact path ( System Path )
  char * Source_File_Name;
  char * Header_Name_With_Ext; // The header file name with extention

};

struct Make_Data {

  char * git_header_file_path;  // Header path in git record
  char * Source_File_Directory;
  char * Header_File_Path;     // Header file exact path ( System Path )
  char * Source_File_Name;
  char * Header_Name_With_Ext; // The header file name with extention

};

class Project_Files_Lister
{
public:
 Project_Files_Lister();
 Project_Files_Lister(const Project_Files_Lister & orig);
 virtual ~Project_Files_Lister();
 void Determine_Git_Repo_Info(char * repo_dir, char * Warehouse);
 int     Get_Git_Repo_Directory_Number();
 char *  Get_Git_Repo_Directory(int i);
 char *  Get_Git_Repo_Header_File_Path(int num);
 char *  Get_Header_Exact_Path(int num);
 char *  Get_Source_File_Name(int num);
 char *  Get_Header_File_Name_With_Extention(int num);
 int     Get_Make_Data_Number();
 char *  Get_Make_Directory(int i);
 char *  Get_Make_Header_File_Path(int num);
 char *  Get_Make_Header_Exact_Path(int num);
 char *  Get_Make_Source_File_Name(int num);
 char *  Get_Make_Header_File_Name_With_Extention(int num);
protected:
 void Determine_Source_File_Name();
 void Determine_Header_File_Name();
 void Receive_Warehouse_Directory(char * repo_dir);
 void Receive_Repo_Directory(char * repo_dir);
 void Determine_Source_Directory_Number();
 void Determine_Source_Directory_Data();
 void Clear_Dynamic_Memory();
 void Determine_Repo_List_File_Size();
 void List_Files_in_Repo();
 void Read_Repo_List_File();
 void Construct_Git_Header_Path(char ** pointer, char * string_line);
 void Place_String(char ** pointer, std::string string_line);
 void Place_String(char ** pointer, char * string);
 void Construct_Header_File_Path(char ** pointer, char * string_line, char operating_sis);
 void Construct_Directory_Path(char ** pointer, char * string_line, char operating_sis);
 void Construct_Source_File_Name(char ** pointer, char * string_line);
 void Construct_Header_Name_With_File_Extention(char ** pointer, char * string_line);
 void Determine_Git_File_List_Path();
 void Determine_Git_Listing_Command();
 void Construct_Make_Data();
 Header_File_Determiner Header_Determiner;
 Source_File_Determiner Source_Determiner;
 StringOperator StringManager;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 Source_Data * Data_Pointer;
 Make_Data * Make_Data_Pointer;
 int make_data_number;
 char ** File_List_Content;
 char * Warehouse;
 char * git_file_list_path;
 char * git_listing_command;
 char * Repo_Dir;
 int  Source_File_Directory_Number;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_FILES_LISTER_H */
