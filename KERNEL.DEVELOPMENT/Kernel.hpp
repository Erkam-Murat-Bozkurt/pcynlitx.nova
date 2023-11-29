



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
#include <windows.h>
#include <string>
#include "Build_Tools_Initializer.h"
#include "Executable_MakeFile_Builder.hpp"
#include "Repo_Warehouse_Initializer.h"
#include "Auto_MakeFile_Builder.h"
#include "Project_Script_Writer.h"
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"

class Kernel
{
public:
 Kernel(char * DesPATH, char opr_sis);
 virtual ~Kernel();
 void Setup_Build_Tools();
protected:
 void Clear_Dynamic_Memory();
 Build_Tools_Initializer Bld_Init;
 Executable_MakeFile_Builder Exe_Bld;
 bool Memory_Delete_Condition;
};

#endif /* KERNEL_HPP */
