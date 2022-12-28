


#ifndef SCRIPT_DATA_PROCESSOR_HPP
#define SCRIPT_DATA_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"


class Script_Data_Processor
{
public:
 Script_Data_Processor();
 Script_Data_Processor(const Script_Data_Processor & orig);
 virtual ~Script_Data_Processor();
 void Process_Script_Data(Descriptor_File_Reader * Des_File_Reader);
 Script_Data Get_SrcFile_Script_Data(char * file_git_path);
 Script_Data * Get_Script_Data();
 int Get_Source_File_Number();
 void Clear_Dynamic_Memory();
protected:
 void Determine_Script_Information();
 void Initialize_Data_Structures();
 void Determine_Header_Files_Inclusion_Number();
 void Determine_Script_Order();
 void Determine_Project_Script_Path(char * paths);
 void Determine_Make_File_Names();
 void Construct_Path(char ** pointer, char * string, char * warehouse_path);
 Script_Data_Collector Data_Collector;
 Project_Files_Lister Dir_Lister;
 Cpp_FileOperations FileManager;
 CharOperator CString_Proccessor;
 std::string String_Line;
 int source_file_num;
 Script_Data * Data_Pointer;
 char * warehouse_path;
 char * project_repo_dir;
 char * script_path;
 bool Memory_Delete_Condition;
};

#endif /* SCRIPT_DATA_PROCESSOR_HPP */
