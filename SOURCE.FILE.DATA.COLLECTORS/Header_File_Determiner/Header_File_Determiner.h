
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
 Header_File_Determiner(char * DesPath, char opr_sis);
 virtual ~Header_File_Determiner();
 bool Is_Header(char * file_path);
 bool Include_Decleration_Test(char * string);
 bool Is_this_an_include_decleration(char * string_line);
 bool Is_this_file_included_on_anywhere(char * file_path);
 void Determine_Header_File_Directory(char * path);
 void Determine_Header_File_Name(char * path);
 void Determine_Header_File_Name_With_Extention(char * path);
 void Determine_Header_File_System_Path(char * repo_dir,
      char * git_record_path, char operating_sis);
 void Extract_Header_File_Name_From_Decleration(char ** header_name, char * string);
 void Determine_Git_Record_File_System_Path(char * file_path, char ** sys_path,
      char operating_sis);
 bool CompareString(char * firstString,char * secondString);
 void Construct_Temporary_String(char ** tmp_string, char * string);
 void Delete_Spaces_on_String(char ** pointer);
 std::string Get_Header_Directory();
 std::string Get_Header_File_System_Path();
 std::string Get_Header_File_Name_Without_Ext();
 std::string Get_Header_File_Name_With_Ext();
 void Clear_Dynamic_Memory();
protected:
 void Read_File(char * path);
 void Clear_Pointer_Memory(char ** pointer);
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 Git_File_List_Receiver Git_Receiver;
 std::string  Header_File_Directory;
 std::string  Header_File_Name;
 std::string  Header_File_Name_With_Extention;
 std::string  Header_File_System_Path;
 std::string  Repo_Dir;
 bool is_header_file;
 int  git_record_size;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
 bool include_decleration_cond;
 bool Is_this_file_included_on_somewhere;
};

#endif /* HEADER_FILE_DETERMINER_H */
