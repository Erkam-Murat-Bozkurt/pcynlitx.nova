





// Header decleraiton

#ifndef DESCRIPTOR_FILE_LINE_READER_HPP
#define DESCRIPTOR_FILE_LINE_READER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Descriptor_File_Data_Collector.hpp"
#include "Descriptor_File_Syntax_Controller.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Descriptor_File_Line_Reader
{
public:
 Descriptor_File_Line_Reader();
 virtual ~Descriptor_File_Line_Reader();
 void Receive_Descriptor_File_Data_Collector(Descriptor_File_Data_Collector * ptr);
 void Read_Root_Directory_Location(std::string & str);
 void Read_Warehouse_Location(std::string & str);
 void Read_Standard(std::string & str);
 void Read_Include_Directories(std::vector<std::string> & vec);
 void Read_Source_File_Directories(std::vector<std::string> & vec);
 void Read_Library_Directories(std::vector<std::string> & vec);
 void Read_Library_Files(std::vector<std::string> & vec);
 void Read_Compiler_Options(std::vector<std::string> & vec);
 void Read_Linker_Options(std::vector<std::string> & vec);
 void Read_Build_System_Type(std::string & str);
 void Read_Project_Name(std::string & str);
 void Read_Version_Number(std::string & str);
 void Read_Compiler_Paths(std::vector<std::string> & vec);
protected:
 bool Is_Include_Character(std::string str);
 bool Is_There_Multiple_Decleration_on_Same_Line(std::string & str_line);
 void Extract_Declerations_Performing_on_Same_Line(std::string str_line, 
 
      std::vector<std::string> & mt_line);
      
 Descriptor_File_Data_Collector * Data_Collector;
 StringOperator StringManager;
 char opr_sis;
};

#endif /* DESCRIPTOR_FILE_LINE_READER_HPP */
