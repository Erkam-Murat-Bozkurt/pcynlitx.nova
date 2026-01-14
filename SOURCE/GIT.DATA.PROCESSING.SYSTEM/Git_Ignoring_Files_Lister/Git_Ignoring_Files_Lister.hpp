






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
 void Set_Ignoring_File_Types();
 void Initialize_Mermbers();
 void Determine_Git_Ignoring_Files_List_Path();
 void Clear_String_Memory(std::string * pointer);
 Descriptor_File_Reader * Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 std::string Warehouse;
 std::string git_ignoring_files_list_path;
 std::string command_for_make;
 std::string command_for_ps;
 std::string Repo_Dir;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* GIT_IGNORING_FILES_LISTER */
