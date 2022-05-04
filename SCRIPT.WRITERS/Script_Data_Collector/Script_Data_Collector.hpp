

#ifndef SCRIPT_DATA_COLLECTOR_H
#define SCRIPT_DATA_COLLECTOR_H

#include <cstring>
#include <string>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Directory_Enumerator.h"

struct Script_Data
{
  char ** header_files_git_dir;
  char ** header_file_names;
  char * object_file_name;
  char * object_file_path;
  char * source_file_name;
  char * source_file_dir;
  char * source_file_git_record_dir;
  char * make_file_name;
  char * warehouse_path;
  int included_header_num;
  int compile_oder;
  int dependency;
};

class Script_Data_Collector
{
public:
 Script_Data_Collector();
 Script_Data_Collector(const Script_Data_Collector & orig);
 virtual ~Script_Data_Collector();
 void Receive_Script_Data(Script_Data * Pointer);
 void Receive_Project_Files_Lister(Project_Files_Lister * Pointer);
 void Receive_Warehouse_Path(char * path);
 void Initialize_Data_Structure(Script_Data * Src_Data_Pointer, int src_num);
 void Determine_Source_File_Compilation_Information(Script_Data * Src_Data_Pointer,
      int dir_num, char operating_sis);
 void Determine_Header_Files_Inclusion_Number(Script_Data * Src_Data_Pointer,
      int src_num);
 void Determine_Make_File_Name(Script_Data * Src_Data_Pointer,
      int src_num);
 void Delete_Spaces_on_String(char ** pointer);
 void Clear_Data_Memory(Script_Data * Src_Data_Pointer, int src_num);
protected:
 void Place_String(char ** pointer, char * string);
 Script_Data * Src_Data_Pointer;
 Project_Files_Lister * Dir_Lister;
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
 std::string String_Line;
 char * warehouse_path;
 bool Include_Line_Condition;
 int  Included_Header_Files_Number;
 bool Memory_Delete_Condition;
};

#endif /* SCRIPT_DATA_COLLECTOR_H */
