
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
#include "Source_File_Determiner.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Git_Modification_Receiver
{
public:
 Git_Modification_Receiver(char opr_sis);
 virtual ~Git_Modification_Receiver();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_List_Receiver(Git_File_List_Receiver * ptr);
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
 bool Is_Header(std::string file_path);
 void Determine_Git_Record_File_System_Path(std::string * sys_path,std::string file_path);
 bool Include_Decleration_Test(std::string string);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name, std::string string);
 void Determine_Header_File_Name(std::string path);
 bool CompareString(std::string firstString, std::string secondString);
 void Delete_Spaces_on_String(std::string * str);
 void Extract_File_Extention(std::string & ext, std::string file_path, 
      bool & is_there_ext);
 Git_File_List_Receiver * Git_List_Receiver;
 Source_File_Determiner Src_Determiner;
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
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
 std::string Header_File_Name;
 bool Memory_Delete_Condition;
 bool isStringLine;
 char opr_sis;
};

#endif /* GIT_MODIFICATION_RECEIVER_HPP */
