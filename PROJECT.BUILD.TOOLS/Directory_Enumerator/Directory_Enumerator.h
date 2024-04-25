

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
#include <vector>
#include "Cpp_FileOperations.h"

class Directory_Enumerator
{
public:
 Directory_Enumerator();
 virtual ~Directory_Enumerator();
 void Receive_Directory_Path(char * Directory_Path, char ** dir_path);
 void Determine_Sub_Directories(char * Root_Dir_Path);
 void Find_Sub_Directories(char * Root_Dir_Path);
 void Find_Files_On_Directory(char * dir_path);
 void List_Files_On_Directory(char * dir_path);
 void List_Files_On_Directory(std::string dir_path);
 int  Get_Directory_Number_In_Directory() const;
 void Clear_Dynamic_Memory();
 std::string Get_Directory_List_Element(int num) const;
 std::vector<std::string> * Get_File_List();
 std::vector<std::string> * Get_Sub_Directory_List();
 int  Get_File_Number();
private:
 void Find_Sub_Directory_Path(char * dir_root_path, char * dir_name, char ** sub_dir_path);
 bool getStringEquality();
 void Clear_CString_Memory(char ** ptr);
 void Clear_Pointer_List(char *** ptr, int list_size);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Extract_Path(char * up_dir, char * name, char ** path);
 char * Convert_StdStr_CStr(std::string str);
 std::string Convert_CStr_StdStr(char * string);
 std::vector<std::string> File_List;
 std::vector<std::string> Directory_List;
 bool isStringsEqual;
 bool   Memory_Delete_Condition;
 char * dir_path;
 char * c_str;
 std::string std_str;
 int    Directory_Number;
 int    List_Index;
 int    File_Number;
};

#endif /* DIRECTORY_ENUMERATOR_H */
