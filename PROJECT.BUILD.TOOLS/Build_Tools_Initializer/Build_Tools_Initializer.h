

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
#include "Compiler_Script_Writer.h"


class Build_Tools_Initializer
{
public:
 Build_Tools_Initializer();
 Build_Tools_Initializer(const Build_Tools_Initializer & orig);
 virtual ~Build_Tools_Initializer();
 void Setup_Build_Tools(char * repo_dir_path, char * warehouse_path );
protected:
 void Clear_Dynamic_Memory();
 Repo_Warehouse_Initializer Rep_Init;
 Auto_MakeFile_Builder Mk_Builder;
 Compiler_Script_Writer Script_Writer;
 bool Memory_Delete_Condition;
};

#endif /* BUILD_TOOLS_INITIALIZER_H */
