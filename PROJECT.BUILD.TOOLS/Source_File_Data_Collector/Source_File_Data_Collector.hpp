

// Header decleraiton

#ifndef SOURCE_FILE_DATA_COLLECTOR_H
#define SOURCE_FILE_DATA_COLLECTOR_H

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


struct Include_File_Data {

    char * Include_File_Name;
    char * Include_File_Directory;
    int Include_File_Number;
};

class Source_File_Data_Collector
{
public:
 Source_File_Data_Collector();
 Source_File_Data_Collector(const Source_File_Data_Collector & orig);
 virtual ~Source_File_Data_Collector();
 void Receive_Source_File_Data(Git_File_List_Receiver * Git_Receiver, char * file_path);
 void Determine_Header_Files_System_Paths(char ** pointer, char * directory,
      char * file_name, char operating_sis);
 void Determine_Header_File_Directory(char ** directory,char * file_path,
           char operating_sis);
 bool Character_Inclusion_Check(char * string, char chr);
           void Determine_Git_Record_Header_File_Path(char ** header_path,char * header_name);
 void Clear_Dynamic_Memory();
 int Get_Included_File_Number();
 char * Get_Include_File_Name(int num);
 char * Get_Include_File_Directory(int num);
protected:
 void Receive_Include_File_Names();
 void Receive_Include_File_Name(char ** pointer, char * string);
 void Receive_Include_File_Directory(char ** pointer, char * string);
 bool Control_Include_Syntax(char * string);
 void Initialize_Data_Structures();
 void Read_File(char * path);
 void Determine_Include_Line_Number();
 void Read_Include_Files();
 void Delete_Spaces_on_String(char ** pointer);
 Git_File_List_Receiver * Git_Receiver_Pointer;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 Include_File_Data * Include_Data_Pointer;
 bool syntax_error;
 bool Character_Inclusion_Status;
 char *  Git_Repo_Dir;
 char ** File_Content;
 char ** Include_File_List;
 char ** Include_File_Directories;
 int File_Content_Size;
 int git_record_size;
 int included_header_file_number;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DATA_COLLECTOR_H */
