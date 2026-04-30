




#ifndef CMAKE_MAIN_FILE_WRITER_HPP
#define CMAKE_MAIN_FILE_WRITER_HPP

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <map>
#include <unordered_map>
#include <iterator>
#include "MakeFile_Path_Determiner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Source_File_Determiner.h"
#include "Header_File_Determiner.h"
#include "Git_Data_Processor.hpp"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"



class CMAKE_Main_File_Writer
{
public:

 CMAKE_Main_File_Writer(char opr_sis);

 virtual ~CMAKE_Main_File_Writer();


 void Receive_Descriptor_File_Reader(const Descriptor_File_Reader * ptr){

      this->Des_Reader = ptr;
 }

 void Receive_Source_File_Dependency_Determiner(const Source_File_Dependency_Determiner * ptr){

      this->Dep_Determiner = ptr;
 }

 void Build_Main_CMAKE_File();

 void Receive_Project_Titles(std::string project_name, std::string version_num){
     
      this->project_name = project_name;

      this->version_num = version_num;
 };

 void Receive_Operating_System(char opr_sis);

 void Clear_Dynamic_Memory();

 void Clear_Object_Memory();

private:

 void Convert_CMAKE_Format(std::string & str);

 bool Check_String_Existance(std::vector<std::string> & list, std::string str);

 const std::vector<Compiler_Data> * Compiler_Data_Pointer;

 const Descriptor_File_Reader * Des_Reader;

 const Source_File_Dependency_Determiner * Dep_Determiner;

 Cpp_FileOperations FileManager;

 char opr_sis;

 std::string project_name;

 std::string version_num; 

 bool Memory_Delete_Condition;

};

#endif /* CMAKE_MAIN_FILE_WRITER_HPP */
