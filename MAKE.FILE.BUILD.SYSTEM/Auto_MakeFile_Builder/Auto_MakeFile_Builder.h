


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
#include <windows.h>
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Make_File_Builder.h"
#include "Make_File_Cleaner.hpp"

class Auto_MakeFile_Builder
{
public:
 Auto_MakeFile_Builder();
 Auto_MakeFile_Builder(const Auto_MakeFile_Builder & orig);
 virtual ~Auto_MakeFile_Builder();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Reader_Pointer);
 void Build_Make_Files();
protected:
 void Determine_Project_Directories();
 void Write_Make_Files();
 void Clear_Dynamic_Memory();
 void Construct_Path(char ** pointer, char * string, char * warehouse_path);
 Project_Files_Lister File_Lister;
 Make_File_Builder Mk_Builder;
 Make_File_Cleaner Mk_File_Clnr;
 Descriptor_File_Reader * Des_Reader_Pointer;
 char * Warehouse_Path;
 char * Repo_Dir;
 char * repo_head_dir;
 char * repo_obj_dir;
 bool Memory_Delete_Condition;
};

#endif /* AUTO_MAKEFILE_BUILDER_H */
