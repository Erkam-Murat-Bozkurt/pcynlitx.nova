
#ifndef MAKE_FILE_BUILDER_H
#define MAKE_FILE_BUILDER_H

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
#include "Header_File_Determiner.h"
#include "ClassNameReader.h"
#include "ClassSyntaxControl.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "Directory_Enumerator.h"
#include "CharOperator.h"

class Make_File_Builder
{
public:
 Make_File_Builder();
 Make_File_Builder(const Make_File_Builder & orig);
 virtual ~Make_File_Builder();
 void Build_MakeFile(char * repo_dir, char * header_path,char * warehouse_path);
 void Clear_Dynamic_Memory();
private:
 void Receive_Git_Header_File_Path(char * header_path);
 void Determine_Header_File_Exact_Path(char operating_sis);
 void Receive_Warehouse_Path(char * warehouse_path);
 void Receive_Repo_Directory(char * repo_dir);
 void Determine_Header_File_Directory(char operating_sis);
 void Determine_Make_File_Name();
 void Determine_Dependency_Code_Line();
 void Place_Information(char ** Pointer, char * Information, int * index_counter);
 void Find_Class_Name(char * class_directory);
 void Determine_Included_Header_Files_Number();
 void Determine_Object_File_Names();
 void Read_Include_File_Names();
 void Determine_Compiler_System_Command(char * Include_Directory_Location);
 bool Include_Line_Determiner(std::string String_Line);
 void Determine_Warehouse_Header_Dir(char operating_sis);
 void Determine_Warehouse_Object_Dir(char operating_sis);
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 Directory_Enumerator Enumerator;
 StringOperator StringManager;
 ClassNameReader NameReader;
 Header_File_Determiner Header_Determiner;
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
 char * Class_Name;
 char * Class_Source_File_Name;
 char * Class_Header_File_Name;
 char * Class_Object_File_Name;
 char * Compiler_System_Command;
 char * Header_File_Copy_Command;
 char * Object_File_Move_Command;
 char ** Included_Header_Files;
 int  Included_Header_Files_Number;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKE_FILE_BUILDER_H */
