







#ifndef DEPENDENCY_DATA_EXTRACTOR_HPP
#define DEPENDENCY_DATA_EXTRACTOR_HPP

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
#include "Source_File_Information_Collector.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


struct Search_Data
{
  std::string path;
  std::string name;
  bool search_complated;
};

class Dependency_Data_Extractor
{
public:
 Dependency_Data_Extractor(char * descriptor_file_path, char opr_sis);
 virtual ~Dependency_Data_Extractor();
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Tree(std::string path);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 std::string Find_Header_Name(std::string string);
 bool Find_New_Dependency(std::string path);
 bool Is_This_File_Aready_Searched(std::string name);
 bool Include_Decleration_Test(std::string string);
 void Extract_File_Name_From_Path(std::string * ptr, std::string str);
 bool CompareString(std::string firstString, std::string secondString);
 bool Is_This_Repo_HeaderFile(std::string head_name);
 void Clear_String_Memory(std::string * Pointer);
 int  Determine_Inclusion_Number(std::string path);
 int  Search_Dependencies(Search_Data & Src_Data, std::vector<Search_Data> & dt);
 std::vector<std::string> * Get_File_Content(std::string path);
 std::string Get_Header_System_Path(std::string header_name);
 Project_Src_Code_Rdr * Code_Rd;
 std::vector<Search_Data> searched_paths;
 std::string warehouse_head_dir;
 std::string descriptor_file_path;
 Header_File_Processor Header_Processor; 
 StringOperator StringManager; 
 int    header_file_number;
 size_t ListLength;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool isStringsEqual;
 bool This_File_Exist;
};


#endif /* DEPENDENCY_DATA_EXTRACTOR_HPP */
