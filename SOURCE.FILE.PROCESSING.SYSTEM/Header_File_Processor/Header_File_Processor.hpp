

// Header decleraiton

#ifndef HEADER_FILE_PROCESSOR_HPP
#define HEADER_FILE_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Header_File_Processor
{
public:
 Header_File_Processor();
 virtual ~Header_File_Processor();
 void Receive_Operating_System(char opr_sis);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 bool Is_Header(std::string file_path);
 bool Include_Decleration_Test(std::string string);
 bool Is_this_file_included_on_anywhere(std::string file_path);
 void Determine_Header_File_Directory(std::string path);
 void Determine_Header_File_Name(std::string path);
 void Determine_Header_File_Name_With_Extention(std::string path);
 void Extract_Header_File_Name_From_Decleration(std::string * header_name, std::string s);
 bool CompareString(std::string firstString, std::string secondString);
 void Extract_File_Extention(std::string & ext, std::string file_name, bool & is_there_ext);
 std::string Get_Header_Directory();
 std::string Get_Header_File_System_Path();
 std::string Get_Header_File_Name_Without_Ext();
 std::string Get_Header_File_Name_With_Ext();
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Clear_String_Memory(std::string * pointer);
 Project_Src_Code_Rdr * Code_Rdr;
 StringOperator StringManager;
 std::string  Header_File_Directory;
 std::string  Header_File_Name;
 std::string  Header_File_Name_With_Extention;
 std::string  Header_File_System_Path;
 char operating_sis;
 bool is_header_file;
 bool is_this_repo_header;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
 bool include_decleration_cond;
 bool Is_this_file_included_on_somewhere;
};

#endif /* HEADER_FILE_PROCESSOR_HPP */
