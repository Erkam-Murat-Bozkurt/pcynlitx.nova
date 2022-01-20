

#ifndef COMPILER_SCRIPT_WRITER_H
#define COMPILER_SCRIPT_WRITER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <string>
#include "Project_Files_Lister.h"
#include "ClassNameReader.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Directory_Enumerator.h"

struct Compiler_Data
{
  char * header_file_path;
  char * header_file_name;
  char * object_file_name;
  char * object_file_path;
  char * class_name;
  char * class_directory;
  int compile_oder;
  int dependency;
};

class Compiler_Script_Writer
{
public:
 Compiler_Script_Writer();
 Compiler_Script_Writer(const Compiler_Script_Writer & orig);
 virtual ~Compiler_Script_Writer();
 void Build_Compiler_Script(char * repo_dir, char * warehouse_path);
protected:
 void Determine_Header_File_Paths();
 void Determine_Header_Paths(int dir_num);
 void Determine_Header_Files_Inclusion_Number();
 void Determine_Compiler_Order();
 void Write_The_Script(char * warehouse_path);
 void Clear_Dynamic_Memory();
 bool Include_Line_Determiner(std::string String_Line);
 void Determine_Warehouse_Paths(char * paths);
 void Construct_Path(char ** pointer, char * string, char * warehouse_path);
 ClassNameReader Cls_Name_Reader;
 DirectoryOperations DirectoryManager;
 Project_Files_Lister Dir_Lister;
 Cpp_FileOperations FileManager;
 Directory_Enumerator Enumerator;
 StringOperator StringManager;
 std::string String_Line;
 bool Include_Line_Condition;
 int  project_dir_num;
 int Included_Header_Files_Number;
 Compiler_Data * Compiler_Data_Pointer;
 char * script_path;
 char * headers_locations;
 char * object_files_location;
 char * compiler_output_location;
 bool Memory_Delete_Condition;
};

#endif /* COMPILER_SCRIPT_WRITER_H */
