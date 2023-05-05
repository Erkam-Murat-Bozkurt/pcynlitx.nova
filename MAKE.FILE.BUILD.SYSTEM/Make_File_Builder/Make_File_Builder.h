
#ifndef MAKE_FILE_BUILDER_H
#define MAKE_FILE_BUILDER_H

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
#include "MakeFile_Data_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class Make_File_Builder
{
public:
 Make_File_Builder(char * DesPath, char opr_sis);
 virtual ~Make_File_Builder();
 void Build_MakeFile(int git_index);
 void Clear_Dynamic_Memory();
private:
 MakeFile_Data_Collector Data_Collector;
 Header_File_Determiner Header_Determiner;
 Project_Files_Lister File_Lister;
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 IntToCharTranslater Translater;
 char opr_sis;
 bool Include_Line_Condition;
 bool Memory_Delete_Condition;
};

#endif /* MAKE_FILE_BUILDER_H */
