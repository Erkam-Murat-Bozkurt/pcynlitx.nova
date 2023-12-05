
#ifndef DATARECORDER_H
#define DATARECORDER_H

#include "Descriptor_File_Reader.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"
#include <cstring>
#include <string>

class DataRecorder
{
public:
  DataRecorder(char * Path, char opr_sis);
  virtual ~DataRecorder();
  void Add_Data_Record(char * Data_Type, char * Data_Record);
  void Clear_Data_Record(char * Data_Type);
  void Replace_Data_Record(char * Data_Type,  char * Data_Record);
  void Replace_Data_Record(char * Data_Type,  std::vector<std::string> & vec);
  void Clear_Object_Memory();
  void Clear_Dynamic_Memory();
private:
  Descriptor_File_Reader Des_Reader;
  void Receive_Decriptor_File();
  void Clear_String_Memory(std::string & str);
  void Clear_String_Vector(std::vector<std::string> & vec);
  void Place_Vector_Data(const std::vector<std::string> & base_vec, std::vector<std::string> & target_vec);
  void Place_String_Data(const std::string & base_str, std::string & target_str);
  void Place_String_Data(char * base_str, std::string & target_str);
  void Update_Descriptor_File();
  void WriteNewLines(int line_number);
  void Write_Vector_Data(std::vector<std::string> & vec);
  void Write_String_Data(std::string dt);
  bool Is_Data_List(std::string data);
  void Extract_Data_List(std::vector<std::string> & vec, std::string data);
  void Clear_Data_Memory();
  StringOperator StringOperations;
  Cpp_FileOperations File_Manager;
  std::string standard;
  std::string options;
  std::string root_dir;
  std::string warehouse_location;
  std::vector<std::string> Include_Directories;
  std::vector<std::string> Source_File_Directories;
  std::vector<std::string> Library_Directories;
  std::vector<std::string> Library_Files;
  std::vector<std::string> Exe_File_Names;
  std::vector<std::string> Main_File_Names;
  bool Memory_Delete_Condition;
};

#endif /* DATARECORDER_H */
