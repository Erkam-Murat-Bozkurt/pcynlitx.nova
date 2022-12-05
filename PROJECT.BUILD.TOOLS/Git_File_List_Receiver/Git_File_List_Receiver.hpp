


#ifndef GIT_FILE_LIST_RECEIVER_H
#define GIT_FILE_LIST_RECEIVER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"


class Git_File_List_Receiver
{
public:
 Git_File_List_Receiver();
 Git_File_List_Receiver(const Git_File_List_Receiver & orig);
 virtual ~Git_File_List_Receiver();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Reader_Pointer);
 void Determine_Git_Repo_Info();
 int Get_Git_File_Index_Size();
 char * Get_Git_File_Index(int num);
 char * Get_Git_Repo_Directory();
 void Clear_Dynamic_Memory();
protected:
 void Place_String(char ** pointer, std::string string_line);
 void Determine_Repo_List_File_Size();
 void List_Files_in_Repo();
 void Read_Repo_List_File();
 void Construct_Git_Header_Path(char ** pointer, char * string_line);
 void Determine_Git_File_List_Path();
 void Determine_Git_Listing_Command();
 void Construct_Make_Data();
 Descriptor_File_Reader * Des_Reader_Pointer;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 char ** File_List_Content;
 char * Warehouse;
 char * git_file_list_path;
 char * git_listing_command;
 char * Repo_Dir;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_FILE_LIST_RECEIVER_H */
