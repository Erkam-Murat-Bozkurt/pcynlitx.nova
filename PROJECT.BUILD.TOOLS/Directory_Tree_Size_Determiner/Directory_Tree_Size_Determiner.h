



#ifndef DIRECTORY_TREE_SIZE_DETERMINER_H
#define DIRECTORY_TREE_SIZE_DETERMINER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Directory_Enumerator.h"

class Directory_Tree_Size_Determiner
{
public:
 Directory_Tree_Size_Determiner();
 Directory_Tree_Size_Determiner(const Directory_Tree_Size_Determiner & orig);
 virtual ~Directory_Tree_Size_Determiner();
 void Determine_Directory_Tree_Size(char * dir_path);
 int  Get_Directory_Tree_Size();
protected:
 void Determine_Source_File_Directory_Number();
 void Extract_Source_File_Directories();
 void Determine_Directory_Tree_Size();
 void Clear_Dynamic_Memory();
 Directory_Enumerator Enumerator;
 int  Directory_Number;
 int  Directory_Tree_Size;
 bool Memory_Delete_Condition;
};

#endif /* DIRECTORY_TREE_SIZE_DETERMINER_H */
