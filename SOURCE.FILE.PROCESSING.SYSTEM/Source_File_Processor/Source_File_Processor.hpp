

// Header decleraiton

#ifndef SOURCE_FILE_PROCESSOR_HPP
#define SOURCE_FILE_PROCESSOR_HPP

#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <iostream>
#include <windows.h>
#include "Project_Src_Code_Rdr.hpp"
#include "Header_File_Determiner.h"
#include "Source_File_Determiner.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Source_File_Processor
{
public:
 Source_File_Processor();
 virtual ~Source_File_Processor();
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 bool Is_Source_File(std::string file_path);
 bool Is_Source_File(char * file_path);
 void Determine_Source_File_Name(std::string path);
 void Determine_File_Name_Without_Ext(std::string path);
 void Determine_File_Name_Without_Ext(char * path);
 std::string Get_Source_File_Name();
 std::string Get_File_Name_Witout_Ext();
 std::vector<std::string> * Get_File_Source_Code(char * path);
 std::vector<std::string> * Get_File_Source_Code(std::string path);
protected:
 void Determine_Class_Function_Pattern(std::string path);
 std::string Get_Class_Function_Pattern();
 void Delete_Spaces_on_String(std::string * pointer);
 void Clear_Dynamic_Memory();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * pointer);
 Project_Src_Code_Rdr * Code_Rdr;
 StringOperator StringManager;
 std::string Source_File_Name;
 std::string Class_Function_Patern;
 std::string File_Name_Witout_Ext;
 int  File_Content_Size;
 bool Is_This_Source_File;
 bool Memory_Delete_Condition;
};

#endif /* SOURCE_FILE_PROCESSOR_HPP */
