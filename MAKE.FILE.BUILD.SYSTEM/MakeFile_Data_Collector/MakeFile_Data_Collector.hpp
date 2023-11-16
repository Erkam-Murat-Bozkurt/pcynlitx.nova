

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
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class MakeFile_Data_Collector
{
public:
 MakeFile_Data_Collector();
 virtual ~MakeFile_Data_Collector();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Collect_Make_File_Data(std::string fileName);
 void Receive_Git_Record_Data(std::string file_name);
 void Receive_Compiler_Data_Pointer(Compiler_Data * ptr); 
 void Receive_Operating_System(char opr_sis);
 void Receive_Determined_Upper_Directories(std::vector<std::string> * ptr);
 std::string Get_Source_File_Name();
 std::string Get_Source_File_System_Directory();
 std::string Get_Make_File_Name();
 std::string Get_Compiler_System_Command();
 std::string Get_Dependency_Code_Line();
 std::string Get_Object_File_Name();
 std::string Get_System_Header_File_Dir();
 std::string Get_Source_File_Name_With_Extention();
 std::string Get_Repo_Dir();
 std::string Get_Warehouse_Object_Dir();
 std::string Get_Warehouse_Path();
 void Clear_Dynamic_Memory(); 
 void Clear_Object_Memory();
private:
 void Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path);
 void Determine_Source_File_Directory(std::string & git_path, std::string sys_path);
 void Determine_File_Name_Without_Ext(std::string & file_name, std::string file_name_wit_ext);
 void Clear_String_Memory(std::string & pointer);
 void Clear_Vector_Memory(std::vector<std::string> & pointer); 
 void Determine_Make_File_Name();
 void Determine_Dependency_Code_Line();
 void Place_String(std::string * ptr, std::string Information);
 void Place_CString(std::string * ptr, char * Information);
 void Find_Object_File_Name();
 void Determine_Compiler_System_Command();
 void Determine_Warehouse_Object_Dir();
 bool Check_String_Existance(std::vector<std::string> & list, std::string str);
 void Determine_Include_Directive(std::string * directive, int index);
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 Descriptor_File_Reader * Des_Reader;
 Compiler_Data * Compiler_Data_Ptr;

 std::vector<std::string> * Determined_Upper_Directories;
 std::string repo_dir;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string Make_File_Name;

 std::string Dependency_Code_Line;
 std::string Header_File_Directory;
 std::string Header_File_Name_With_Ext;

 std::string Source_File_Name_With_Ext;
 std::string Source_File_Git_Recort_Path;
 std::string Source_File_Name;
 std::string Source_File_Directory;

 std::string Object_File_Name;
 std::string Compiler_System_Command;
 int  Git_Record_Index;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKEFILE_DATA_COLLECTOR_H */
