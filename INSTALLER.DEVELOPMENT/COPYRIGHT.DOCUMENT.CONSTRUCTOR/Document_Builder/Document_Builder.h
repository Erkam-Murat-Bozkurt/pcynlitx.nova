
#ifndef DOCUMENT_BUILDER_H
#define DOCUMENT_BUILDER_H

#include <ctype.h>
#include <cstring>
#include <string>
#include <vector>
#include "Cpp_FileOperations.h"

class Document_Builder
{
public:
  Document_Builder();
  Document_Builder(const Document_Builder & orig);
  virtual ~Document_Builder();
  void Receive_Document_Path(std::string name);
  void Receive_File_Path(std::string path);
  void Add_File_To_Document();
  void Clear_Dynamic_Memory();
private:
  void Read_File();
  void Add_To_Document();
  void Clear_Std_String(std::string & str);
  std::string FilePath;
  std::string Document_Name;
  std::vector<std::string> File_Content;
  Cpp_FileOperations FileManager;
  bool Memory_Delete_Condition;
  bool File_Path_Receive_Status;
  bool Document_Name_Receive_Status;
  int File_Line_Number;
};

#endif /* DOCUMENT_BUILDER_H */
