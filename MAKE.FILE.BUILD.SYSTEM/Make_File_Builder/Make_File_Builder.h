
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
#include "MakeFile_Data_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class Make_File_Builder
{
public:
 Make_File_Builder(char * DesPath, char opr_sis);
 virtual ~Make_File_Builder();
 void Build_MakeFile(int git_index);
 void Clear_Dynamic_Memory();
private:
 void Receive_Git_Header_File_Path(std::string header_path);
 void Determine_Header_File_Exact_Path(char operating_sis);
 void Receive_Warehouse_Path(std::string warehouse_path);
 void Receive_Repo_Directory(std::string repo_dir);
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
 MakeFile_Data_Collector Data_Collector;
 Header_File_Determiner Header_Determiner;
 Project_Files_Lister File_Lister;
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 std::string String_Line;
 std::string git_header_dir;
 std::string repo_dir;
 std::string warehouse_head_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string Make_File_Name;
 std::string Dependency_Code_Line;
 std::string Git_Header_File_Path;
 std::string Header_File_Exact_Path;
 std::string Header_File_Directory;
 std::string Source_File_Name;
 std::string Header_File_Name_With_Ext;
 std::string Source_File_Name_With_Ext;
 std::string Object_File_Name;
 std::string Compiler_System_Command;
 std::vector<std::string> Included_Header_Files;
 int  Included_Header_Files_Number;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKE_FILE_BUILDER_H */
