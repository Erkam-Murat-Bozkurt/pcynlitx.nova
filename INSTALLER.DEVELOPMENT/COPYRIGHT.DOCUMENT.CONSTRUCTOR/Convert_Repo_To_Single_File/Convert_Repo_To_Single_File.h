

#ifndef CONVERT_REPO_TO_SINGLE_FILE_H
#define CONVERT_REPO_TO_SINGLE_FILE_H

#include <ctype.h>
#include <cstring>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <windows.h>
#include "Document_Builder.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "CharOperator.h"

class Convert_Repo_To_Single_File
{
public:
  Convert_Repo_To_Single_File();
  virtual ~Convert_Repo_To_Single_File();
  void Receive_Document_Path(char * path);
  void Receive_Repo_Directory(char * name);
  void Construct_Source_File();
  void Clear_Dynamic_Memory();
private:
  void Place_String(char ** Pointer, char * String);
  void List_Files_in_Repo();
  void Read_File();
  char * Repo_Directory;
  std::string repo_dir_std_str;
  std::string Document_Path;
  std::vector<std::string> File_List_Content;
  Document_Builder Doc_Builder;
  Cpp_FileOperations FileManager;
  DirectoryOperations DirectoryManager;
  bool Memory_Delete_Condition;
  bool Repo_Directory_Receive_Status;
};

#endif /* CONVERT_REPO_TO_SINGLE_FILE_H */
