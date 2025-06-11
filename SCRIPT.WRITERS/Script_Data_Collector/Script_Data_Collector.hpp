

#ifndef SCRIPT_DATA_COLLECTOR_H
#define SCRIPT_DATA_COLLECTOR_H

#include <cstring>
#include <string>
#include "Source_File_Dependency_Determiner.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Git_Data_Processor.hpp"
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
 Script_Data_Collector(char opr_sis);
 virtual ~Script_Data_Collector();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Compiler_Data(Compiler_Data * dt);
 void Receive_Simple_Dependency_Search_Data(const Simple_Source_File_Dependency * ptr);
 void Determine_Source_File_Compilation_Information(Script_Data * ptr, std::string str);
 void Determine_Source_File_Compilation_Information_For_Simple_Search(Script_Data * ptr, std::string str);
 void Determine_Header_Files_Inclusion_Number(Script_Data * ptr);
 void Determine_Header_Files_Inclusion_Number_For_Simple_Construction(Script_Data * ptr);
 void Determine_Make_File_Name(Script_Data * ptr);
protected:
 void Place_String(std::string * pointer, std::string string);
 Descriptor_File_Reader * Des_File_Reader;
 Compiler_Data * Cmp_Data_Ptr;
 const Simple_Source_File_Dependency * Simple_Data_Ptr;
 std::string warehouse_path;
 bool Memory_Delete_Condition;
 char opr_sis;
};

#endif /* SCRIPT_DATA_COLLECTOR_H */
