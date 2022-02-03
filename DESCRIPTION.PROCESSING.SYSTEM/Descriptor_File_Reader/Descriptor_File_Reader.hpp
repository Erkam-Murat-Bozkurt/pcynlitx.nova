


// Header decleraiton

#ifndef DESCRIPTOR_FILE_READER_HPP
#define DESCRIPTOR_FILE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "Cpp_FileOperations.h"

class Descriptor_File_Reader
{
public:
 Descriptor_File_Reader();
 Descriptor_File_Reader(const Descriptor_File_Reader & orig);
 virtual ~Descriptor_File_Reader();
 void Read_Descriptor_File(char * path);
 void Clear_Dynamic_Memory();
 char ** Get_Library_Names();
 char ** Get_Library_Directories();
 char ** Get_Source_File_Directories();
 char ** Get_Include_Directories();
 char  * Get_Standard();
 bool    Get_Debugging_Option();
protected:
 void Read_Standard();
 void Read_Include_Directories();
 void Read_Source_File_Directories();
 void Read_Library_Directories();
 void Read_Library_Names();
 void Read_Debugging_Option();
 void Receive_Descriptor_File_Path(char * path);
 Cpp_FileOperations FileManager;
 char * file_path;
 char * standard;
 bool debugging;
 char ** Include_Directories;
 char ** Source_File_Directories;
 char ** Library_Directories;
 char ** Library_Names;
 bool Memory_Delete_Condition;
};

#endif /* DESCRIPTOR_FILE_READER */
