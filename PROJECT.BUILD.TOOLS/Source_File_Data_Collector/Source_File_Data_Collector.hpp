

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
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Source_File_Data_Collector
{
public:
 Source_File_Data_Collector();
 Source_File_Data_Collector(const Source_File_Data_Collector & orig);
 virtual ~Source_File_Data_Collector();
 void Receive_Source_File_Data(char * file_path);
 void Clear_Dynamic_Memory();
 int Get_Included_File_Number();
 char * Get_Include_File_Name(int num);
protected:
 void Receive_Include_File_Names();
 bool Character_Inclusion_Check(char * string, char chr);
 void Receive_Include_File_Name(char ** pointer, char * string);
 bool Control_Include_Syntax(char * string);
 void Read_File(char * path);
 void Determine_Include_Line_Number();
 void Read_Include_Files();
 void Delete_Spaces_on_String(char ** pointer);
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 bool syntax_error;
 bool Character_Inclusion_Status;
 char ** File_Content;
 char ** Include_File_List;
 int File_Content_Size;
 int included_header_file_number;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DATA_COLLECTOR_H */
