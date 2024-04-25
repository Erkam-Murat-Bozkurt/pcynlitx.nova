

#ifndef LIBRARY_NAME_EXTRACTOR_H
#define LIBRARY_NAME_EXTRACTOR_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include "Directory_Enumerator.h"
#include "Descriptor_File_Reader.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"

class Library_Name_Extractor
{
public:
 Library_Name_Extractor();
 Library_Name_Extractor(const Library_Name_Extractor & orig);
 virtual ~Library_Name_Extractor();
 void Determine_Library_Names(char * Path);
 char * Get_Archive_File(int index);
 char * Get_Dll_File(int index);
 int  Get_DLL_Files_Number();
 int  Get_Arcive_Files_Number();
 void Clear_Dynamic_Memory();
private:
 void Receive_Directory_Path(char * Path);
 void Determine_Files_On_The_Directory();
 void Extract_Library_Files();
 void Extract_Dll_Files();
 void Extract_Archive_Files();
 void Determine_Dll_Files_Number();
 void Determine_Archive_Files_Number();
 void Place_String(char ** pointer, char * string);
 void Place_String(char ** pointer, std::string string);
 Directory_Enumerator Enum;
 Descriptor_File_Reader * Des_Reader_Pointer;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 StringOperator StringManager;
 std::string String_Line;
 char * director_path;
 char ** dll_files;
 char ** archive_files;
 int dll_files_number;
 int archive_files_number;
 bool Memory_Delete_Condition;
};

#endif /* LIBRARY_NAME_EXTRACTOR_H */
