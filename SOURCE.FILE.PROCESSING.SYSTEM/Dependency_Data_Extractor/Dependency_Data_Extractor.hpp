







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
  std::vector<Search_Data> Dependent_Headers;
  std::vector<Search_Data> External_Headers;
};


class Dependency_Data_Extractor
{
public:
 Dependency_Data_Extractor();
 virtual ~Dependency_Data_Extractor();
 void Receive_Operating_System(char opr_sis);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Tree(std::string path);
 std::vector<Search_Data> * Get_Search_Data();
 const std::vector<std::string> * Get_External_Header_Files() const;
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Re_Order_Dependencies();
 void Recursive_Dependency_Determination(std::string path);
 bool Check_New_Dependency_Status(std::string path);
 bool Check_New_Dependency_Status_From_Path(std::string path);
 bool Is_This_File_Aready_Searched(std::string inc_dec);
 bool Is_This_Repo_HeaderFile(std::string head_name);
 bool Is_This_RepoFile(std::string head_name);
 void Clear_String_Memory(std::string & str);
 int  Determine_Inclusion_Number(std::string path);
 int  Search_Dependencies(Search_Data & Src_Data);
 void Insert_External_Header_File_For_Dependency(std::string hdr_file);
 bool Is_There_Directory_Character(std::string str);
 void Extract_Header_File_Name(std::string & file_name, std::string path);
 bool Is_This_A_Combined_Include_Delaration(std::string name);
 void Extract_Directory_File_Name_Combination(std::string inc_dec, std::string & dir_file_com);
 bool Check_New_Record_Status(std::vector<std::string> & vec, std::string str);
 void Determine_Dependent_File_Data_From_Decleration(Search_Data & buffer, std::string inc_dec);
 void Determine_Dependent_File_Data_From_Path(Search_Data & buffer, std::string path);
 void Add_Search_Data(Search_Data & buffer);
 void Clear_Search_Data_Memory(std::vector<Search_Data> & data);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_Map_Memory(std::unordered_map<std::string, Search_Data *> & Map_Inc_Dec);
 const std::vector<std::string> * Get_File_Include_Delarations(std::string path) const;
 const std::vector<std::string> * Include_Declerations;
 Header_File_Processor Header_Processor;  
 Project_Src_Code_Rdr * Code_Rd;
 std::vector<Search_Data> Dependent_Headers;
 std::vector<Search_Data> Swap_Memory;
 std::vector<std::string> External_Header_Files;
 std::vector<std::string> records;
 std::unordered_map<std::string, Search_Data *> Map_Inc_Dec;
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
};


#endif /* DEPENDENCY_DATA_EXTRACTOR_HPP */
