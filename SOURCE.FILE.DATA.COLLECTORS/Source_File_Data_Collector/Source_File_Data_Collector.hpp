

// Header decleraiton

#ifndef SOURCE_FILE_DATA_COLLECTOR_H
#define SOURCE_FILE_DATA_COLLECTOR_H

#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <vector>
#include "Git_File_List_Receiver.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

struct Include_File_Data
{
    std::string Include_File_Name;
    std::string Include_File_Directory;
    std::string Include_File_Git_Record_Path;
    std::string Include_File_Git_Record_Dir;
    int Include_File_Number;
};

class Source_File_Data_Collector
{
public:
 Source_File_Data_Collector(char * DesPath, char operating_sis);

 virtual ~Source_File_Data_Collector();

 void Receive_Source_File_Data(std::string file_path);

 void Determine_Header_Files_System_Paths(std::string * pointer,

      std::string directory, std::string file_name);

 void Determine_Header_File_Directory(std::string * directory,

      std::string file_path);

 void Determine_Git_Record_Header_File_Path(std::string * header_path,

      std::string header_name);

 void Determine_Git_Record_Header_File_Directory(std::string * header_dir,

      std::string header_path);

 void Determine_Git_Record_Source_File_Path(std::string * source_file_path,

      std::string file_path);

 void Determine_Git_Record_Source_File_Directory(std::string * source_file_dir,

      std::string source_file_path);

 void Clear_Dynamic_Memory();

 int  Get_Included_File_Number();

 std::string Get_Include_File_Name(int num);
 std::string Get_Include_File_Directory(int num);
 std::string Get_Include_File_Git_Record_Directory(int num);
 std::string Get_Include_File_Git_Record_Path(int num);
 std::string Get_Include_File_Name_Without_Ext(int num);
protected:
 void Initialize_Members();
 void Extract_Include_File_Name_From_Path(std::string * pointer, std::string string );
 bool CompareString(std::string firstString, std::string secondString);
 bool Character_Inclusion_Check(std::string string, char chr);
 void Receive_Include_File_Names();
 void Receive_Include_File_Name(std::string * pointer, std::string string);
 void Receive_Include_File_Directory(std::string * pointer, std::string string);
 bool Control_Include_Syntax(std::string string);
 void Read_File(std::string path);
 void Determine_Include_Line_Number();
 void Read_Include_Files();
 void Delete_Spaces_on_String(std::string * pointer);
 Git_File_List_Receiver Git_Receiver;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 char operating_sis;
 bool syntax_error;
 bool isStringsEqual;
 bool Character_Inclusion_Status;
 std::string Git_Repo_Dir;
 std::vector<std::string> File_Content;
 std::vector<Include_File_Data> Head_Data;
 int File_Content_Size;
 int git_record_size;
 int included_header_file_number;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DATA_COLLECTOR_H */
