
#ifndef LIBRARY_UPDATER_H
#define LIBRARY_UPDATER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <windows.h>
#include <shlwapi.h>
#include "Descriptor_File_Reader.hpp"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "Custom_System_Interface.h"

class Library_Updater
{
public:
 Library_Updater();
 Library_Updater(const Library_Updater & orig);
 virtual ~Library_Updater();
 void Receive_Descriptor_File(char * descriptor_file);
 void Build_Library(char * Library_Name);
 void Send_Library_New_Location(char * Object_Files_Directory, char * New_Location, char * Library_Name);
 void Clear_Dynamic_Memory();
private:
 void Determine_Warehouse_Object_Dir(char operating_sis);
 void Place_Information(char ** Pointer, char * Information, int * index_counter);
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 DirectoryOperations DirectoryManager;
 Custom_System_Interface System_Interface;
 char * Archive_Build_Command;
 char * Object_File_List;
 char * warehouse_obj_dir;
 char * warehouse_path;
 bool Memory_Delete_Condition;
};

#endif /* LIBRARY_UPDATER_H */
