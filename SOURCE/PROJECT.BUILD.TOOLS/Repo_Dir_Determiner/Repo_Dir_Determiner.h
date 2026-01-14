



#ifndef REPO_DIR_DETERMINER_H
#define REPO_DIR_DETERMINER_H

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
#include "DirectoryOperations.h"
#include "StringOperator.h"

class Repo_Dir_Determiner
{
public:
 Repo_Dir_Determiner();
 Repo_Dir_Determiner(const Repo_Dir_Determiner & orig);
 virtual ~Repo_Dir_Determiner();
 void Determine_Repo_Dir();
 void Clear_Dynamic_Memory();
 char * Get_Repo_Dir();
protected:
 char * Extract_Folder_Name(char * dir_name);
 StringOperator StringManager;
 DirectoryOperations DirectoryManager;
 char * Repo_Dir;
 char * Folder_Name;
 bool Memory_Delete_Condition;
};

#endif /* REPO_DIR_DETERMINER_H */
