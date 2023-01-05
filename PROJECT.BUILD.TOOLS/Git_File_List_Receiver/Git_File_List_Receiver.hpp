


#ifndef GIT_FILE_LIST_RECEIVER_H
#define GIT_FILE_LIST_RECEIVER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"


class Git_File_List_Receiver
{
public:
 Git_File_List_Receiver(char * DesPath);
 Git_File_List_Receiver(std::string DesPath);
 virtual ~Git_File_List_Receiver();
 void Determine_Git_Repo_Info();
 int  Get_Git_File_Index_Size();
 std::string Get_Git_File_Index(int num);
 std::string Get_Git_Repo_Directory();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Mermbers();
 void List_Files_in_Repo();
 void Read_Repo_List_File();
 void Determine_Git_File_List_Path();
 void Determine_Git_Listing_Command();
 char * From_Std_String_To_Char(std::string str);
 Descriptor_File_Reader Des_Reader;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 std::vector<std::string> File_List_Content;
 std::string Warehouse;
 std::string git_file_list_path;
 std::string git_listing_command;
 std::string Repo_Dir;
 char * CString;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_FILE_LIST_RECEIVER_H */
