
#ifndef DIRECTORYOPERATIONS_H
#define DIRECTORYOPERATIONS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <dirent.h>
#include <cstdio>
#include <windows.h>
#include <tchar.h>
#include <shellapi.h>
#include <fileapi.h>
#include "CharOperator.h"

#define BUFSIZE MAX_PATH

class DirectoryOperations
{
public:
 DirectoryOperations();
 DirectoryOperations(char * DesPath);
 DirectoryOperations(std::string DesPath);
 virtual ~DirectoryOperations();
 void LoadSystemFunctionCommand(char * command,char * DirectoryName);
 void RecordCurrentDirectoryPATH();
 void ReturnRecordedDirectoryPATH();
 void DetermineCurrentDirectory();
 void DetermineSubDirectoryName(char * DirectoryName);
 void DetermineUpperDirectoryName();
 void Determine_File_List_In_Directory(char * DirectoryName);
 void Remove_Directory_Recursively(char * DirectoryName);
 void Clear_Dynamic_Memory();
 int  MakeDirectory(char * path);
 int  MakeSubDirectory(char * path);
 int  MakeDirectory(std::string path);
 int  ChangeDirectory(char * path);
 int  ChangeDirectory(const char * path);
 int  RemoveDirectory(char * path);
 int  GoToUpperDirectory();
 int  GoToSubDirectory(char * DirectoryName);
 int  RemoveSubDirectory(char * DirectoryName);
 bool Search_File_in_Directory(char * Directory_Name, char * File_Name);
 void Delete_File(char * path);
 char * GetRecordedDirectoryPATH();
 char * GetCurrentlyWorkingDirectory();
 char * GetSubDirectoryName();
 char * GetUpperDirectoryName();
 char * GetSystemFunctionCommand();
 std::string * Get_File_List_In_Directory();
 int  Get_File_Number_In_Directory();
private:
 void Initialize_Mermbers();
 void   Place_String(char ** Pointer, char * String, int String_Size);
 void   Place_Information(char ** Pointer, const char * Information, int * index_counter);
 void   Place_Information(char ** Pointer, char * Information, int * index_counter);
 void Clear_Pointer_Memory(char ** ptr);
 void Clear_String_Memory(std::string ** ptr);
 CharOperator CString_Operator;
 bool   Memory_Delete_Condition;
 std::string * File_List;
 char * SystemCommand;
 char * CurrentDirectory;
 char * Sub_Directory;
 char * Upper_Directory;
 char * RecordDirectoryPATH;
 char * c_str;
 bool   File_Exist_Condition;
 int    ReturnCondition;
 int    File_Number;
};

#endif /* DIRECTORYOPERATIONS_H */
