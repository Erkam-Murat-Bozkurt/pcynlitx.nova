


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
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Header_File_Determiner
{
public:
 Header_File_Determiner();
 Header_File_Determiner(const Header_File_Determiner & orig);
 virtual ~Header_File_Determiner();
 bool Is_Header(char * file_path);
 void Determine_Header_File_Directory(char * path);
 char * Get_Header_Directory();
protected:
 void Read_File(char * path);
 void Clear_Dynamic_Memory();
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 char ** File_Content;
 char *  Header_File_Directory;
 int     File_Content_Size;
 bool    is_header_file;
 bool Memory_Delete_Condition;
};

#endif /* HEADER_FILE_DETERMINER_H */
