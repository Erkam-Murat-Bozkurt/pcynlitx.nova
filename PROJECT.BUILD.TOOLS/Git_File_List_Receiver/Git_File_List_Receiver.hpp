


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
 Git_File_List_Receiver(char * DesPath, char opr_sis);
 Git_File_List_Receiver(std::string DesPath, char opr_sis);
 virtual ~Git_File_List_Receiver();
 void Determine_Git_Repo_Info();
 size_t  Get_Git_File_Index_Size();
 std::string Get_Git_File_Index(int num);
 std::string Get_File_System_Path(int num);
 std::string Get_Git_Repo_Directory();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Mermbers();
 void Read_Repo_List_File();
 void Determine_Git_File_List_Path();
 void Determine_File_System_Paths();
 void Convert_Windows_Paths();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_CString_Buffer();
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 std::vector<std::string> File_List_Content;
 std::vector<std::string> File_System_Paths;
 std::string Warehouse;
 std::string git_file_list_path;
 std::string Repo_Dir;
 char opr_sis;
 char * CString;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_FILE_LIST_RECEIVER_H */
