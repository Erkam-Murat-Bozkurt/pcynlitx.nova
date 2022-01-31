
// Header decleraiton

#ifndef SOURCE_FILE_DETERMINER_H
#define SOURCE_FILE_DETERMINER_H

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


class Source_File_Determiner
{
public:
 Source_File_Determiner();
 Source_File_Determiner(const Source_File_Determiner & orig);
 virtual ~Source_File_Determiner();
 bool Is_Source_File(char * file_path);
 void Determine_Source_File_Name(char * path, char operating_sis);
 char * Get_Source_File_Name();
protected:
 void Read_File(char * path);
 void Determine_File_Name_Without_Ext(char * path, char operating_sis);
 void Determine_Class_Function_Pattern(char * path);
 char * Get_Class_Function_Pattern();
 char * Get_File_Name_Witout_Ext();
 void Delete_Spaces_on_String(char ** pointer);
 void Clear_Dynamic_Memory();
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 char ** File_Content;
 char *  Source_File_Name;
 char *  Class_Function_Patern;
 char *  File_Name_Witout_Ext;
 int     File_Content_Size;
 bool    Is_This_Source_File;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DETERMINER_H */
