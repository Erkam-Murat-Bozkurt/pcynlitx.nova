

#ifndef PROJECT_FILES_LISTER_H
#define PROJECT_FILES_LISTER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

struct Project_Files_Data
{
   char * header_file_name;
   char * header_directory;
};

class Project_Files_Lister
{
public:
 Project_Files_Lister();
 Project_Files_Lister(const Project_Files_Lister & orig);
 virtual ~Project_Files_Lister();
 void Determine_Project_File_List(char * repo_dir, char * Warehouse);
 char ** Get_Project_SourceFile_List();
 int     Get_SourceFile_Directory_Number();
 char *  Get_Source_File_Directory(int i);
protected:
 void Receive_Warehouse_Directory(char * repo_dir);
 void Receive_Repo_Directory(char * repo_dir);
 void Determine_Source_Directory_Number();
 void Determine_Source_Directories();
 void Clear_Dynamic_Memory();
 void Determine_Repo_List_File_Size();
 void List_Files_in_Repo();
 void Read_Repo_List_File();
 void Place_String(char ** pointer, std::string string_line);
 void Construct_Directory_path(char ** pointer, char * string_line, char operating_sis);
 void Determine_Git_File_List_Path();
 void Determine_Git_Listing_Command();
 Header_File_Determiner Header_Determiner;
 StringOperator StringManager;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 char ** File_Content;
 int    File_Content_Size;
 char * Warehouse;
 char * git_file_list_path;
 char * git_listing_command;
 char ** Directory_List;
 char ** Source_File_Directory_List;
 char ** File_List_Content;
 char * Repo_Dir;
 int  Source_File_Directory_Number;
 int  Directory_Number;
 int  Directory_Tree_Size;
 int  project_directory_number;
 int  File_Line_Number;
 int  header_files_number;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_FILES_LISTER_H */
