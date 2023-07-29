




#ifndef GIT_FILE_LIST_WRITER_H
#define GIT_FILE_LIST_WRITER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Custom_System_Interface.h"


class Git_File_List_Writer
{
public:
 Git_File_List_Writer(char opr_sis);
 virtual ~Git_File_List_Writer();
 void Receive_Descriptor_File_Path(char * DesPath);
 void Receive_Descriptor_File_Path(std::string DesPath);
 void Write_Git_Repo_List_File();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Mermbers();
 void Execute_System_Call(char * cmd);
 void List_Files_in_Repo();
 void Control_Std_Error_Status();
 void Determine_Git_File_List_Path();
 void Determine_Git_Listing_Command();
 void Determine_Error_Check_File_Path();
 char * From_Std_String_To_Char(std::string str);
 void Clear_String_Memory(std::string * pointer);
 void Clear_CString_Buffer();
 Descriptor_File_Reader Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 Custom_System_Interface System_Interface;
 std::string Warehouse;
 std::string git_file_list_path;
 std::string git_listing_command;
 std::string git_check_command;
 std::string Repo_Dir;
 std::string std_error_file_path;
 char opr_sis;
 char * CString;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_FILE_LIST_WRITER_H */
