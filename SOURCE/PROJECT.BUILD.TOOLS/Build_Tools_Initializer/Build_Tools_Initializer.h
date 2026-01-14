

#ifndef BUILD_TOOLS_INITIALIZER_H
#define BUILD_TOOLS_INITIALIZER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <string>
#include "Repo_Warehouse_Initializer.h"
#include "Auto_MakeFile_Builder.h"
#include "Project_Script_Writer.h"
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Cpp_FileOperations.h"

class Build_Tools_Initializer
{
public:
 Build_Tools_Initializer(char * DesPATH, char opr_sis, char build_type);
 void Receive_Build_Type(char BuildType);
 void Receive_System_Interface(Custom_System_Interface * sysInt);
 virtual ~Build_Tools_Initializer();
 void Setup_Build_Tools();
 void Clear_Dynamic_Memory();
protected:
 void Determine_Git_File_List_Path();
 void Remove_Git_File_List();
 Git_Data_Processor Git_Data_Proc;
 Descriptor_File_Reader Des_Reader;
 Repo_Warehouse_Initializer Rep_Init;
 Source_File_Dependency_Determiner Dep_Determiner;
 Auto_MakeFile_Builder Mk_Builder;
 Project_Script_Writer Script_Writer;
 Custom_System_Interface * SysInt;
 std::string git_file_list_path;
 bool Memory_Delete_Condition;
 char build_type;
 char opr_sis;
};

#endif /* BUILD_TOOLS_INITIALIZER_H */
