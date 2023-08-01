
// Header decleraiton

#ifndef HEADER_FILE_DETERMINER_H
#define HEADER_FILE_DETERMINER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Git_File_List_Receiver.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Header_File_Determiner
{
public:
 Header_File_Determiner(char opr_sis);
 virtual ~Header_File_Determiner();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 bool Is_Header(std::string file_path);
 bool Is_This_Repo_Header(std::string file_path);
 bool Include_Decleration_Test(std::string string);
 bool Is_this_file_included_on_anywhere(std::string file_path);
 void Determine_Header_File_Directory(std::string path);
 void Determine_Header_File_Name(std::string path);
 void Determine_Header_File_Name_With_Extention(std::string path);
 void Determine_Header_File_System_Path(std::string repo_dir, std::string git_rcpath);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name, std::string s);
 void Determine_Git_Record_File_System_Path(std::string * sys_path, std::string file_path);
 bool CompareString(std::string firstString, std::string secondString);
 void Delete_Spaces_on_String(std::string * pointer);
 std::string Get_Header_Directory();
 std::string Get_Header_File_System_Path();
 std::string Get_Header_File_Name_Without_Ext();
 std::string Get_Header_File_Name_With_Ext();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Clear_String_Memory(std::string * pointer);
 Git_File_List_Receiver Git_Receiver;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 std::string  Header_File_Directory;
 std::string  Header_File_Name;
 std::string  Header_File_Name_With_Extention;
 std::string  Header_File_System_Path;
 std::string  Repo_Dir;
 char operating_sis;
 bool is_header_file;
 bool is_this_repo_header;
 int  git_record_size;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
 bool include_decleration_cond;
 bool Is_this_file_included_on_somewhere;
};

#endif /* HEADER_FILE_DETERMINER_H */
