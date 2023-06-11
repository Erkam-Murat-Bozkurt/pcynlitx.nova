


#ifndef AUTO_MAKEFILE_BUILDER_H
#define AUTO_MAKEFILE_BUILDER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>     //for using the function sleep
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Make_File_Builder.h"
#include "Make_File_Cleaner.hpp"

class Auto_MakeFile_Builder
{
public:
 Auto_MakeFile_Builder(char * DesPath, char opr_sis);
 virtual ~Auto_MakeFile_Builder();
 void Build_Make_Files();
protected:
 void Determine_Project_Directories();
 void Clear_Dynamic_Memory();
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * ptr);
 void Construct_Path(std::string * ptr, std::string str, std::string wrd);
 Project_Files_Lister File_Lister;
 Make_File_Builder Mk_Builder;
 Make_File_Cleaner Mk_File_Clnr;
 Descriptor_File_Reader Des_Reader;
 std::string Warehouse_Path;
 std::string Repo_Dir;
 std::string repo_head_dir;
 std::string repo_obj_dir;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* AUTO_MAKEFILE_BUILDER_H */
