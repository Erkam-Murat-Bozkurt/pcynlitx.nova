

#ifndef DIRECTORY_ENUMERATOR_H
#define DIRECTORY_ENUMERATOR_H

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
#include <vector>
#include "Cpp_FileOperations.h"

#define BUFSIZE MAX_PATH

class Directory_Enumerator
{
public:
 Directory_Enumerator();
 Directory_Enumerator(const Directory_Enumerator & orig);
 virtual ~Directory_Enumerator();
 void Receive_Directory_Path(char * Directory_Path, char ** dir_path);
 void Determine_Sub_Directories(char * Root_Dir_Path);
 void Determine_Sub_Directory_Number(char * Directory_Path);
 void Find_Sub_Directories(char * Root_Dir_Path);
 void List_Files_On_Directory(char * dir_path);
 void List_Files_On_Directory(std::string dir_path);
 void Determine_Search_Path(char * path, TCHAR ** pointer);
 int Get_Directory_Number_In_Directory() const;
 void Clear_Dynamic_Memory();
 char *  Get_Directory_List_Element(int num) const;
 char ** Get_File_List();
 std::string Get_Directory_List_Element_As_StdStr(int num) const;
 std::vector<std::string> * Get_File_List_As_StdStr();
 int  Get_File_Number();
private:
 void Construct_Directory_List_Element(char ** list_element, char * Dir_Name, char * dir_path);
 void Find_Sub_Directory_Path(char * dir_root_path, char * dir_name, char ** sub_dir_path);
 bool CompareString(char * firstString, char * secondString);
 bool getStringEquality();
 void Clear_CString_Memory(char ** ptr);
 void Clear_Pointer_List(char *** ptr, int list_size);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 char * Convert_StdStr_CStr(std::string str);
 std::string Convert_CStr_StdStr(char * string);
 std::vector<std::string> File_List_StdStr;
 std::vector<std::string> Directory_List_StdStr;
 bool isStringsEqual;
 TCHAR * search_path;
 bool   Memory_Delete_Condition;
 char * dir_path;
 char * c_str;
 std::string std_str;
 char ** Directory_List;
 char ** File_List;
 int    Directory_Number;
 int    List_Index;
 int    File_Number;
};

#endif /* DIRECTORY_ENUMERATOR_H */
