

#ifndef GIT_MODIFICATION_RECEIVER_HPP
#define GIT_MODIFICATION_RECEIVER_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <vector>
#include <string>
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Git_Modification_Receiver
{
public:
 Git_Modification_Receiver(char * DesPath, char opr_sis);
 virtual ~Git_Modification_Receiver();
 void Receive_Git_Modifications();
 std::vector<std::string> * Get_File_System_Path_Address();
 std::vector<std::string> * Get_Updated_Header_Files();
 std::vector<std::string> * Get_Updated_Source_Files();
 void Clear_Dynamic_Memory();
protected:
 void Determine_Warehouse_Path();
 void Determine_Header_Files_Directory();
 void Determine_Object_Files_Directory();
 void Determine_Library_Files_Directory();
 void Determine_Git_Modification_File_Path();
 void Read_Modification_File();
 void Convert_Windows_Paths();
 void Determine_File_System_Paths();
 void Determine_Updated_Header_Files();
 void Determine_Updated_Source_Files();
 void Convert_to_System_path(std::string & sys_path, std::string path);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Delete_Spaces_on_String(std::string & str);
 bool CheckStringLine(std::string str);
 Header_File_Determiner Header_Determiner;
 Source_File_Determiner Src_Determiner;
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 int  File_Line_Number;
 std::string  warehouse_location;
 std::string  warehouse_path;
 std::vector<std::string> File_Content;
 std::vector<std::string> File_System_Paths;
 std::vector<std::string> Updated_Header_Files;
 std::vector<std::string> Updated_Source_Files;
 std::string Headers_Directory;
 std::string Object_Files_Directory;
 std::string Library_Files_Directory; 
 std::string modification_file_path;
 std::string Repo_Dir;
 bool Memory_Delete_Condition;
 bool isStringLine;
 char opr_sis;
};

#endif /* GIT_MODIFICATION_RECEIVER_HPP */
