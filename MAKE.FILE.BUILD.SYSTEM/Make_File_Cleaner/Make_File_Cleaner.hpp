


#ifndef MAKE_FILE_CLEANER_H
#define MAKE_FILE_CLEANER_H

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
#include <windows.h>
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "Directory_Enumerator.h"

class Make_File_Cleaner
{
public:
 Make_File_Cleaner();
 Make_File_Cleaner(const Make_File_Cleaner & orig);
 virtual ~Make_File_Cleaner();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader);
 void Receive_File_Lister(Project_Files_Lister * File_Lister);
 void Clear_Make_Files_Exist_On_Repo();
 void Clear_Dynamic_Memory();
private:
 bool Is_This_MakeFile(char * file_name);
 void Determine_File_Path(char ** path, char * dir, char * name, char operating_sis);
 Descriptor_File_Reader * Des_Reader_Pointer;
 Project_Files_Lister * File_Lister_Pointer;
 Cpp_FileOperations FileManager;
 Directory_Enumerator Enumerator;
 bool Is_MakeFile;
 bool Memory_Delete_Condition;
};

#endif /* MAKE_FILE_CLEANER_H */
