





#ifndef GIT_MODIFICATION_LISTER_H
#define GIT_MODIFICATION_LISTER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Custom_System_Interface.h"


class Git_Modification_Lister
{
public:
 Git_Modification_Lister(char opr_sis);
 virtual ~Git_Modification_Lister(); 
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Write_Git_Modification_File();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Mermbers();
 void Determine_Warehouse_Path();
 void Execute_System_Call(char * cmd);
 void List_Files_in_Repo();
 void Determine_Git_Modification_File_Path();
 void Determine_Git_Listing_Command();
 char * From_Std_String_To_Char(std::string str);
 void Clear_String_Memory(std::string * pointer);
 void Clear_CString_Buffer();
 Descriptor_File_Reader * Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 std::string Warehouse;
 std::string warehouse_path;
 std::string modification_file_path;
 std::string git_listing_command;
 std::string Repo_Dir;
 char opr_sis;
 char * CString;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_MODIFICATION_LISTER_H */
