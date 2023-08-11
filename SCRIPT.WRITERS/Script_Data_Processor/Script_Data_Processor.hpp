


#ifndef SCRIPT_DATA_PROCESSOR_HPP
#define SCRIPT_DATA_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Git_Data_Processor.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"


class Script_Data_Processor
{
public:
 Script_Data_Processor(char opr_sis);
 virtual ~Script_Data_Processor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr);
 void Process_Script_Data();
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 Script_Data Get_SrcFile_Script_Data(char * file_git_path);
 std::vector<Script_Data> * Get_Script_Data_Address();
 int  Get_Source_File_Number();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Determine_Script_Information();
 void Determine_Script_Order();
 void Clear_Script_Data(std::vector<Script_Data> * ptr);
 void Clear_String_Memory(std::string * ptr);
 void Clear_String_Vector(std::vector<std::string> * ptr);
 void Clear_Script_Data(Script_Data * ptr);
 Script_Data_Collector Data_Collector;
 Source_File_Dependency_Determiner * Dep_Determiner;
 Descriptor_File_Reader * Des_Reader;
 Cpp_FileOperations FileManager;
 CharOperator CString_Proccessor;
 std::vector<Script_Data> Data;
 Script_Data Temp_Data;
 std::string String_Line;
 std::string warehouse_path;
 std::string project_repo_dir;
 std::string script_path;
 int source_file_num;
 bool Memory_Delete_Condition;
};

#endif /* SCRIPT_DATA_PROCESSOR_HPP */
