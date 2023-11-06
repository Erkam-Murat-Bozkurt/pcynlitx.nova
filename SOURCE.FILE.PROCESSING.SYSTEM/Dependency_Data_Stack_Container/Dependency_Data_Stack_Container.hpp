









#ifndef DEPENDENCY_DATA_STACK_CONTAINER_HPP
#define DEPENDENCY_DATA_STACK_CONTAINER_HPP

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
#include <map>
#include <unordered_map>
#include <iterator>
#include <utility>                     // std::pair, std::make_pair
#include <stdexcept>                   // std::out_of_range
#include "Source_File_Information_Collector.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
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
  std::string include_decleration;
  std::string dir_file_comb;
  bool search_complated;
  int dep_counter;
};


struct Search_Data_Records
{
  std::string path;
  int dep_counter;
  std::vector<Search_Data> Dependent_Headers;
  std::vector<std::string> External_Headers;
};

class Dependency_Data_Stack_Container
{
public:
 Dependency_Data_Stack_Container();
 virtual ~Dependency_Data_Stack_Container();
 void Receive_New_Search_Data(std::string path, const Search_Data_Records * ptr);
 bool Is_Exist_OnSearchStack(std::string path);
 const std::vector<Search_Data_Records> * Get_Search_Stack();
 const Search_Data_Records * Find_Search_Data_From_Path(std::string path) const;
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:

 void Clear_Search_Data_Memory(std::vector<Search_Data> & data);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_Map_Memory(std::unordered_map<std::string, Search_Data *> & Map_Inc_Dec);
 void Clear_String_Memory(std::string & str);

 std::unordered_map<std::string, Search_Data_Records> Search_Stack_Map;
 std::vector<Search_Data_Records> Search_Stack;
 bool Memory_Delete_Condition;

};


#endif /* DEPENDENCY_DATA_STACK_CONTAINER_HPP */
