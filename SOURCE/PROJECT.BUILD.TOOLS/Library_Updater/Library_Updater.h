
#ifndef LIBRARY_UPDATER_H
#define LIBRARY_UPDATER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <windows.h>
#include <shlwapi.h>
#include "Descriptor_File_Reader.hpp"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "Custom_System_Interface.h"

class Library_Updater
{
public:
 Library_Updater(char opr_sis);
 virtual ~Library_Updater();
 void Receive_Descriptor_File_Path(char * DesPATH);
 void Receive_Descriptor_File_Path(std::string DesPATH);
 void Build_Library();
 void Send_Library_To_Libraries_Location();
 void Clear_Dynamic_Memory();
private:
 void Determine_Warehouse_Object_Dir();
 void Determine_Current_Library_Path();
 void Determine_Target_Library_Path();
 void Determine_Library_File_Name();
 void Determine_Project_Library_Name();
 void Extract_Repo_Directory_Name(std::string & name, std::string root_dir);
 void Place_Information(std::string & str, std::string s);
 void Clear_String_Memory(std::string & str);
 void Add_Directory_Character(std::string & str);
 void Place_CString(char ** str, std::string s);
 void Clear_CString(char ** str);
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 Custom_System_Interface System_Interface;
 std::string project_library_name;
 std::string Archive_Build_Command;
 std::string Object_File_List;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 std::string library_name;
 std::string Library_File_Name;
 std::string Target_Library_Path;
 std::string Current_Library_Path;
 bool Memory_Delete_Condition;
 char opr_sis;
};

#endif /* LIBRARY_UPDATER_H */
