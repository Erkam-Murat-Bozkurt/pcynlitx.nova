

#ifndef PROJECT_DIRECTORY_LISTER_H
#define PROJECT_DIRECTORY_LISTER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "StringOperator.h"
#include "Directory_Enumerator.h"
#include "Directory_Tree_Size_Determiner.h"

class Project_Directory_Lister
{
public:
 Project_Directory_Lister();
 Project_Directory_Lister(const Project_Directory_Lister & orig);
 virtual ~Project_Directory_Lister();
 void Determine_Project_File_List();
 void Receive_Repo_Directory(char * repo_dir);
 char ** Get_Project_SourceFile_List();
 int     Get_SourceFile_Directory_Number();
 char *  Get_Source_File_Directory(int i);
protected:
 void Determine_Source_File_Directory_Number();
 void Extract_Source_File_Directories();
 void Determine_Directory_Tree_Size();
 void Clear_Dynamic_Memory();
 StringOperator StringManager;
 Directory_Enumerator Enumerator;
 Directory_Tree_Size_Determiner Tree_Size_Determiner;
 char ** Directory_List;
 char ** Source_File_Directory_List;
 char * Repo_Dir;
 int  Source_File_Directory_Number;
 int  Directory_Number;
 int  Directory_Tree_Size;
 int  project_directory_number;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_DIRECTORY_LISTER_H */
