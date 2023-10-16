


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
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Source_File_Dependency_Selector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "Directory_Enumerator.h"

class Make_File_Cleaner
{
public:
 Make_File_Cleaner(char * DesPath, char opr_sis);
 virtual ~Make_File_Cleaner();
 void Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr);
 void Clear_Make_Files_Exist_On_Repo();
 void Clear_Dynamic_Memory();
private:
 bool Is_This_MakeFile(std::string file_name);
 void Determine_File_Path(std::string * path, std::string dir, std::string name); 
 std::vector<Compiler_Data> * Compiler_Data_Pointer;
 Cpp_FileOperations FileManager;
 Directory_Enumerator Enumerator; 
 bool Is_MakeFile;
 bool Memory_Delete_Condition;
 char opr_sis;
};

#endif /* MAKE_FILE_CLEANER_H */
