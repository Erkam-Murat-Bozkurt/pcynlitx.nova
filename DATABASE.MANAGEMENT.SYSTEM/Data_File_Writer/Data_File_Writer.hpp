


// Header decleraiton

#ifndef DATA_FILE_WRITER_HPP
#define DATA_FILE_WRITER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "Script_Data_Collector.hpp"
#include "Cpp_FileOperations.h"

class Data_File_Writer
{
public:
 Data_File_Writer();
 Data_File_Writer(const Data_File_Writer & orig);
 virtual ~Data_File_Writer();
 void Receive_Source_File_Data(Script_Data * data);
 void Build_Data_File(char * path);
 void Clear_Dynamic_Memory();
protected:
 void Receive_File_Path(char * path);
 void WriteNewLines(int line_number);
 Cpp_FileOperations FileManager;
 char * file_path;
 Script_Data Data_Ptr;
 bool Memory_Delete_Condition;
};

#endif /* DATA_FILE_WRITER_HPP */
