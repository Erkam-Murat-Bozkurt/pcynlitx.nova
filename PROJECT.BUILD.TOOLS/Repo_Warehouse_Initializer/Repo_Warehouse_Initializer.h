
#ifndef REPO_WAREHOUSE_INITIALIZER_H
#define REPO_WAREHOUSE_INITIALIZER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Project_Directory_Lister.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Repo_Warehouse_Initializer
{
public:
 Repo_Warehouse_Initializer();
 Repo_Warehouse_Initializer(const Repo_Warehouse_Initializer & orig);
 virtual ~Repo_Warehouse_Initializer();
 void Build_Project_Warehouse(char * repo_dir, char * warehouse);
protected:
 void Receive_Warehouse_Location(char * warehouse_path);
 void Determine_Project_Directories();
 void Determine_Current_Directory();
 void Determine_Header_File_Names();
 void Construct_Header_Files_Directory();
 void Construct_Object_Files_Directory();
 void Determine_Header_File_Paths();
 void Determine_Header_Paths(int dir_num);
 void Determine_New_Header_Paths();
 void Copy_Header_Files_To_Project_Headers_Location();
 void Clear_Dynamic_Memory();
 DirectoryOperations DirectoryManager;
 Project_Directory_Lister Dir_Lister;
 Cpp_FileOperations FileManager;
 Directory_Enumerator Enumerator;
 StringOperator StringManager;
 int  project_dir_num;
 char *  warehouse_path;
 char * current_directory;
 char ** Header_File_Paths;
 char ** Headers_New_Paths;
 char * Headers_Directory;
 char * Object_Files_Directory;
 bool Memory_Delete_Condition;
};

#endif /* REPO_WAREHOUSE_INITIALIZER_H */
