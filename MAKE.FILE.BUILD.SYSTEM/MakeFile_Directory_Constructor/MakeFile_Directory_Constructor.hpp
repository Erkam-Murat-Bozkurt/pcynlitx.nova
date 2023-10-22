


#ifndef MAKEFILE_DIRECTORY_CONSTRUCTOR_H
#define MAKEFILE_DIRECTORY_CONSTRUCTOR_H

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
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "DirectoryOperations.h"

class MakeFile_Directory_Constructor
{
public:
 MakeFile_Directory_Constructor();
 virtual ~MakeFile_Directory_Constructor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr); 
 void Receive_Operating_System(char opr_sis);
 void Construct_MakeFile_Directories();
 void Collect_Directory_Info();
 std::vector<std::string> * Get_MakeFile_Directories();
 void Clear_Dynamic_Memory(); 
 void Clear_Object_Memory();
private:
 void Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path);
 void Determine_MakeFile_File_Directory(std::string & mk_dir,std::string git_rcr_dir);
 void Determine_MakeFiles_Root_Directory();
 void Clear_String_Memory(std::string & pointer);
 void Clear_Vector_Memory(std::vector<std::string> & pointer); 
 void Place_Std_String(std::string & target_str, std::string str);
 void Place_CString(std::string * ptr, char * Information);
 bool Check_Directory_Existance(std::vector<std::string> * hdr_dir, std::string dir);
 void Find_Upper_Directory(std::string & upper_dir, std::string dir);
 void ReOrder_Directories();
 void Construct_Directory(std::string dir);
 size_t Find_Shortest(std::vector<std::string> & vec);
 DirectoryOperations DirectoryManager;
 Descriptor_File_Reader * Des_Reader;
 std::vector<Compiler_Data> * Compiler_Data_Ptr;
 std::vector<std::string> MakeFile_Directories;
 std::vector<std::string> Ordered_MakeFile_Directories;
 std::string warehouse_path;
 std::string make_files_root_directory;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* MAKEFILE_DIRECTORY_CONSTRUCTOR_H */
