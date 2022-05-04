

#ifndef PROJECT_SCRIPT_WRITER_H
#define PROJECT_SCRIPT_WRITER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Directory_Enumerator.h"
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"


class Project_Script_Writer
{
public:
 Project_Script_Writer();
 Project_Script_Writer(const Project_Script_Writer & orig);
 virtual ~Project_Script_Writer();
 void Build_Compiler_Script(Descriptor_File_Reader * pointer);
protected:
 void Determine_Script_Information();
 void Initialize_Data_Structures();
 void Place_String(char ** pointer, char * string);
 void Determine_Source_File_Compilation_Information(int dir_num, char operating_sis);
 void Determine_Header_Files_Inclusion_Number();
 void Determine_Compiler_Order();
 void Write_The_Script(char * warehouse_path);
 void Write_Source_File_Scripts();
 void Write_The_Project_Script(char * warehouse_path);
 void Clear_Dynamic_Memory();
 void Determine_Warehouse_Paths(char * paths);
 void Determine_Make_File_Names();
 void Construct_Path(char ** pointer, char * string, char * warehouse_path);
 Script_Data_Collector Data_Collector;
 Source_File_Script_Writer Src_Script_Writer;
 DirectoryOperations DirectoryManager;
 Project_Files_Lister Dir_Lister;
 Cpp_FileOperations FileManager;
 Directory_Enumerator Enumerator;
 StringOperator StringManager;
 std::string String_Line;
 bool Include_Line_Condition;
 int source_file_num;
 int Included_Header_Files_Number;
 Script_Data * Data_Pointer;
 char * project_repo_dir;
 char * script_path;
 char * headers_locations;
 char * object_files_location;
 char * compiler_output_location;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_SCRIPT_WRITER_H */
