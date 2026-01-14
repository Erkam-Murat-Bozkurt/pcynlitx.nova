






#ifndef SOURCE_FILE_DATA_SETTER_HPP
#define SOURCE_FILE_DATA_SETTER_HPP

#include <cstring>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <windows.h>
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_Modification_Receiver.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "IntToCharTranslater.h"



/*
   This is a wrapper class for source file dependency determination 
*/

class Source_File_Data_Setter  
{
public:
 Source_File_Data_Setter(char opr_sis);
 virtual ~Source_File_Data_Setter();
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Directory_From_Path(std::string path, std::string & dir);
 void Determine_Object_File_Name(std::string & obj_name, std::string src_name);
 void Copy_String(std::string & target_str, std::string str);
 void Extract_File_Name_From_Path(std::string & ptr, std::string str);
 void Determine_Header_System_Path(std::string & path, std::string name);
 void Determine_Git_Record_Source_File_Directory( std::string git_record_system_path, 
 std::string & record_dir);
 void Determine_File_Name_Without_Ext(std::string path, std::string & file_name);
 Project_Src_Code_Rdr * Code_Rd;  
 Git_Data_Processor * Git_Data_Proc;
 std::string descriptor_file_path;
 char opr_sis;
};

#endif /* SOURCE_FILE_DATA_SETTER_HPP */
