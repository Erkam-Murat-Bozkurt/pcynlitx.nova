
// Header decleraiton

#ifndef SOURCE_FILE_DETERMINER_H
#define SOURCE_FILE_DETERMINER_H

#include <string>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <vector>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Source_File_Determiner
{
public:
 Source_File_Determiner();
 virtual ~Source_File_Determiner();
 bool Is_Source_File(std::string file_path);
 bool Is_Source_File(char * file_path);
 void Determine_Source_File_Name(std::string path);
 void Determine_File_Name_Without_Ext(std::string path);
 std::string Get_Source_File_Name();
 std::string Get_File_Name_Witout_Ext();
protected:
 void Read_File(std::string path);
 void Determine_Class_Function_Pattern(std::string path);
 std::string Get_Class_Function_Pattern();
 void Delete_Spaces_on_String(std::string * pointer);
 void Clear_Dynamic_Memory();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 std::vector<std::string> File_Content;
 std::string Source_File_Name;
 std::string Class_Function_Patern;
 std::string File_Name_Witout_Ext;
 int  File_Content_Size;
 bool Is_This_Source_File;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_DETERMINER_H */
