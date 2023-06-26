

#ifndef SCRIPT_DATA_COLLECTOR_H
#define SCRIPT_DATA_COLLECTOR_H

#include <cstring>
#include <string>
#include "Source_File_Dependency_Determiner.hpp"
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Directory_Enumerator.h"


struct Script_Data
{
  std::string object_file_name;
  std::string object_file_path;
  std::string source_file_name;
  std::string src_name_without_ext;
  std::string source_file_dir;
  std::string source_file_git_record_dir;
  std::string make_file_name;
  std::string warehouse_path;
  int included_header_num;
  int compile_oder;
  int dependency;
};

class Script_Data_Collector
{
public:
 Script_Data_Collector(char * DesPATH, char opr_sis);
 virtual ~Script_Data_Collector();
 void Receive_Compiler_Data(Compiler_Data * dt);
 void Determine_Source_File_Compilation_Information(Script_Data * ptr, std::string str);
 void Determine_Header_Files_Inclusion_Number(Script_Data * ptr, int num);
 void Determine_Make_File_Name(Script_Data * ptr);
 void Find_Git_Record_Dir(std::string header_name, std::string & dir); 
 void Clear_Data_Memory(Script_Data * Src_Data_Pointer, int src_num); 
protected:
 void Find_Data_Record_Index(std::string header_name, int & index);
 void Find_File_Name(std::string name_ext, std::string & name);
 void Place_String(std::string * pointer, std::string string);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 bool CompareString(std::string str1, std::string Str2);
 Descriptor_File_Reader Des_File_Reader;
 Project_Files_Lister Dir_Lister;
 std::vector<Build_System_Data> * Build_Dt;
 Script_Data * Src_Data_Pointer;
 Compiler_Data * Cmp_Data_Ptr;
 std::string warehouse_path;
 bool Include_Line_Condition;
 int  Included_Header_Files_Number;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
 char opr_sis;
};

#endif /* SCRIPT_DATA_COLLECTOR_H */
