

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
#include "Script_Data_Processor.hpp"
#include "Source_File_Script_Writer.hpp"
#include "Script_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"


class Project_Script_Writer
{
public:
 Project_Script_Writer(char * DesPATH, char opr_sis);
 virtual ~Project_Script_Writer();
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr);
 void Build_Compiler_Script();
 void Clear_Dynamic_Memory();
protected:
 void Write_Source_File_Scripts();
 void Write_The_Project_Script();
 void Determine_Project_Script_Path(std::string paths);
 void Construct_Path(std::string & path, std::string str, std::string wp);
 void Construct_Path(std::string & pointer,
      std::string string, char opr_sis);
 Git_File_List_Receiver Git_Receiver;
 Descriptor_File_Reader Des_Reader;
 Script_Data_Processor Src_Data_Processor;
 Source_File_Script_Writer Src_Script_Writer;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 int source_file_num;
 std::vector<Script_Data> * Data_Pointer;
 std::string script_path;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* PROJECT_SCRIPT_WRITER_H */
