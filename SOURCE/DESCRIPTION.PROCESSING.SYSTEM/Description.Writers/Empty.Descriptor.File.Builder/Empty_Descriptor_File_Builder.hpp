

// Header decleraiton

#ifndef EMPTY_DESCRIPTOR_FILE_BUILDER_HPP
#define EMPTY_DESCRIPTOR_FILE_BUILDER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "Cpp_FileOperations.h"

class Empty_Descriptor_File_Builder
{
public:
 Empty_Descriptor_File_Builder(char opr_sis);
 Empty_Descriptor_File_Builder(const Empty_Descriptor_File_Builder & orig);
 virtual ~Empty_Descriptor_File_Builder();
 void Build_Empty_File(char * path);
 void Clear_Dynamic_Memory();
protected:
 void Receive_File_Path(char * path);
 void WriteNewLines(int line_number);
 Cpp_FileOperations FileManager;
 char * file_path;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* EMPTY_DESCRIPTOR_FILE_BUILDER_HPP */
