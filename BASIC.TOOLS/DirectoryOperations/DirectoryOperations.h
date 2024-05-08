
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

struct Directory_Data
{
    std::string directory_path;
    std::vector<std::string> sub_directory_paths;
    std::vector<std::string> file_paths;
    bool sub_dir_search_complation_status;
};


class DirectoryOperations
{
public:
 DirectoryOperations();
 virtual ~DirectoryOperations();
 void LoadSystemFunctionCommand(char * command,char * DirectoryName);
 void RecordCurrentDirectoryPATH();
 void ReturnRecordedDirectoryPATH();
 void DetermineCurrentDirectory();
 void DetermineSubDirectoryName(char * DirectoryName);
 void DetermineUpperDirectoryName();
 void Determine_File_List_In_Directory(const char * directory_path);
 void Determine_File_List_In_Directory_WINAPI(std::string Directory_Name, std::vector<Directory_Data> & data);
 void Remove_Directory_Recursively_WINAPI(std::string Directory_Name);
 int  Remove_Directory_Recursively(const char * directory_path);
 void Clear_Dynamic_Memory();
 int  MakeDirectory(char * path);
 int  MakeSubDirectory(char * path);
 int  MakeDirectory(std::string path);
 int  ChangeDirectory(char * path);
 int  ChangeDirectory(const char * path);
 int  ChangeDirectory(std::string path);
 int  RemoveDirectory(char * path);
 int  GoToUpperDirectory();
 int  GoToSubDirectory(char * DirectoryName);
 int  RemoveSubDirectory(char * DirectoryName);
 bool Search_File_in_Directory(char * Directory_Name, char * File_Name);
 void Determine_File_List_In_Directory_WINAPI(std::string Directory_Path, 
      std::vector<std::string> & filePaths);
 void Delete_File(std::string path);
 void Delete_Directory(std::string path);
 char * GetRecordedDirectoryPATH();
 char * GetCurrentlyWorkingDirectory();
 char * GetSubDirectoryName();
 char * GetUpperDirectoryName();
 char * GetSystemFunctionCommand();
 std::string * Get_File_List_In_Directory();
 int  Get_File_Number_In_Directory();
 bool Is_There_Subdirectory(std::string directory, std::string & subDirPath);
private:
 void Initialize_Mermbers();
 void Extract_Path(const char * up_dir, char * name, std::string & path);
 void Extract_Path(std::string up_dir,  char * name, std::string & path);
 void Place_String(char ** Pointer, char * String, size_t String_Size);
 void Place_Information(char ** Pointer, const char * Information, int * index_counter);
 void Place_Information(char ** Pointer, char * Information, int * index_counter);
 void Clear_Pointer_Memory(char ** ptr);
 void Clear_String_Memory(std::string ** ptr);
 char * Convert_Std_String_To_CString(std::string st);
 void Clear_String_Vector(std::vector<std::string> & vec);
 void Clear_String_Memory(std::string & vec);
 std::vector<std::string> Path_List;
 bool Memory_Delete_Condition;
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
