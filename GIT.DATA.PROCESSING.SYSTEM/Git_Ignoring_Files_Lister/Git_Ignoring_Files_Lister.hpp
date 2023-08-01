






#ifndef GIT_IGNORING_FILES_LISTER
#define GIT_IGNORING_FILES_LISTER

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Custom_System_Interface.h"


class Git_Ignoring_Files_Lister
{
public:
 Git_Ignoring_Files_Lister( char opr_sis);
 virtual ~Git_Ignoring_Files_Lister();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Write_Ignoring_File_List();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Mermbers();
 void Execute_System_Call(char * cmd);
 void Execute_Listing_Command();
 void Determine_Git_Ignoring_Files_List_Path();
 void Determine_Git_Ignoring_Files_Lister_Command();
 char * From_Std_String_To_Char(std::string str);
 void Clear_String_Memory(std::string * pointer);
 void Clear_CString_Buffer();
 Descriptor_File_Reader * Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 Custom_System_Interface System_Interface;
 std::string Warehouse;
 std::string git_ignoring_files_list_path;
 std::string command_for_make;
 std::string command_for_ps;
 std::string Repo_Dir;
 char * CString;
 char opr_sis;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_IGNORING_FILES_LISTER */
