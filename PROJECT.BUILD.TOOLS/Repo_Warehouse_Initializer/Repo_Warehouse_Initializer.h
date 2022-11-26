
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
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Repo_Warehouse_Initializer
{
public:
 Repo_Warehouse_Initializer();
 Repo_Warehouse_Initializer(const Repo_Warehouse_Initializer & orig);
 virtual ~Repo_Warehouse_Initializer();
 void Build_Project_Warehouse(char * Des_File_Path);
 void Update_Warehaouse_Headers(char * Des_File_Path);
 void Clear_Dynamic_Memory();
protected:
 void Determine_File_Name_With_Ext(char ** file_name, char * path);
 void Determine_Warehouse_Path(char opr_sis);
 void Determine_Header_Files_Directory(char opr_sis);
 void Determine_Object_Files_Directory(char opr_sis);
 void Determine_Library_Files_Directory(char opr_sis);
 void Determine_Current_Directory();
 void Construct_Warehouse_Path();
 void Construct_Header_Files_Directory();
 void Construct_Object_Files_Directory();
 void Construct_Library_Files_Directory();
 void Determine_Header_File_Paths();
 void Copy_Independent_Header_Files_To_Project_Headers_Location();
 void Determine_Header_Paths(char * path, int src_num, int hdr_num);
 void Find_Independent_Header_Path(char * path, int path_num);
 void Determine_Independent_Header_Paths();
 void Copy_Header_Files_To_Project_Headers_Location();
 void Clear_Pointer_Memory(char ** pointer);
 DirectoryOperations DirectoryManager;
 Project_Files_Lister Dir_Lister;
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
 int  source_files_number;
 int  ind_hdr_number;
 char *  warehouse_location;
 char *  warehouse_path;
 char *  current_directory;
 char *** Header_File_Paths;
 char *** Headers_New_Paths;
 char ** Independent_Header_Paths;
 char ** Independent_Header_New_Paths;
 char * Headers_Directory;
 char * Object_Files_Directory;
 char * Library_Files_Directory;
 bool Memory_Delete_Condition;
};

#endif /* REPO_WAREHOUSE_INITIALIZER_H */
