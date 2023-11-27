

#ifndef PROJECT_SCRIPT_WRITER_H
#define PROJECT_SCRIPT_WRITER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"
#include "Script_Data_Processor.hpp"
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"


class Project_Script_Writer
{
public:
 Project_Script_Writer(char opr_sis);
 virtual ~Project_Script_Writer();
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader* ptr);
 void Set_Script_Path(std::string dir, std::string file_name);
 void Build_Compiler_Script();
 void Build_Update_Script();
 void Clear_Dynamic_Memory();
protected:
 void Write_Sub_Project_Scripts();
 void Write_Source_File_Scripts(int start, int end);
 void Write_Project_Build_Script();
 void Determine_Project_Script_Path();
 void Construct_Path(std::string & path, std::string str, std::string wp);
 void Construct_Path(std::string & pointer,
      std::string string, char opr_sis);
 void Determine_Object_Files_Location(char opr_sis);
 void Clear_String_Memory(std::string & pointer);
 void Determine_Compiler_Output_File_Name(std::string & name, std::string class_name);
 void Determine_MakeFile_Directory(std::string & mkf_dir, std::string git_record_dir);
 void Determine_MakeFiles_Root_Directory();
 int  Determine_Decimal_Space(int total_src_num, int current_number);
 size_t Split_Range(int range_size, int partition, int & remaining_job);
 void Construct_For_Large_Data_Set(int data_size);
 void Construct_For_Middle_Data_Set(int data_size);
 void Construct_For_Small_Data_Set(int data_size);
 Descriptor_File_Reader * Des_Reader;
 Script_Data_Processor Src_Data_Processor;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 IntToCharTranslater Translater;
 std::string MakeFiles_Root_Directory;
 std::string Repo_Rood_Dir;
 std::string object_files_location;
 std::string compiler_output_location;
 std::string script_path;
 std::string warehouse_path;
 bool is_script_path_setted;
 int source_file_num;
 std::vector<std::thread> threadPool;
 std::vector<Script_Data> * Data_Pointer;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_SCRIPT_WRITER_H */
