



#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include "Build_Tools_Initializer.h"
#include "CMAKE_Build_System_Generator.hpp"
#include "Executable_MakeFile_Builder.hpp"
#include "Repo_Warehouse_Initializer.h"
#include "Auto_MakeFile_Builder.h"
#include "Project_Script_Writer.h"
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Empty_Descriptor_File_Builder.hpp"
#include "DataRecorder.h"
#include "Library_Updater.h"

class Kernel
{
public:
 Kernel(char * DesPATH, char opr_sis, char build_type);
 virtual ~Kernel();
 void Receive_Build_Type(char BuildType);
 void Receive_System_Interface(Custom_System_Interface * SysInt);
 void Setup_Build_Tools();
 void Build_MakeFile(char * mn_src_path, char * Exe_Name, char strategy);
 void Determine_Source_File_Dependency_List(char * src_path);
 void Update_Library();
 std::vector<Compiler_Data> * Get_Src_Dependency_List();
 void Clear_Dynamic_Memory();
protected:
 Build_Tools_Initializer Bld_Init;
 CMAKE_Build_System_Generator CMAKE_Builder;
 Executable_MakeFile_Builder Exe_Bld;
 Descriptor_File_Reader Des_Reader;
 Git_Data_Processor Git_Prog;
 Source_File_Dependency_Determiner Dep_Determiner;
 Library_Updater Lib_Up;
 Custom_System_Interface * SysInt;
 std::string DesPATH;
 char strategy;
 char build_type;
 bool Memory_Delete_Condition;
};

#endif /* KERNEL_HPP */
