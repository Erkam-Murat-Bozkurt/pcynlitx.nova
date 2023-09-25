







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
  bool search_complated;
  int dep_counter;
};

class Dependency_Data_Extractor
{
public:
 Dependency_Data_Extractor(char opr_sis);
 virtual ~Dependency_Data_Extractor();
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Extract_Dependency_Tree(std::string path);
 std::vector<Search_Data> * Get_Search_Data();
 const std::vector<std::string> * Get_External_Header_Files() const;
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Re_Order_Dependencies();
 int  Recursive_Dependency_Determination(std::string path, std::vector<Search_Data> & data);
 bool Check_New_Dependency_Status(std::string path, std::vector<Search_Data> & data);
 bool Check_New_Dependency_Status_From_Path(std::string path, std::vector<Search_Data> & data);
 bool Is_This_File_Aready_Searched(std::string inc_dec);
 bool Is_This_Repo_HeaderFile(std::string head_name);
 void Clear_String_Memory(std::string & str);
 int  Determine_Inclusion_Number(std::string path);
 int  Search_Dependencies(Search_Data & Src_Data, std::vector<Search_Data> & dt);
 void Insert_External_Header_File_For_Dependency(std::string hdr_file);
 bool Is_This_A_Combined_Include_Delaration(std::string name);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 const std::vector<std::string> * Get_File_Include_Delarations(std::string path) const;
 std::string Get_Header_System_Path(std::string header_name) const;
 std::string Get_File_Path_Form_Declaration(std::string declaration);
 Project_Src_Code_Rdr * Code_Rd;
 std::vector<Search_Data> searched_paths;
 std::unordered_map<std::string, Search_Data *> Map_Inc_Dec;
 std::vector<std::string> External_Header_Files;
 Header_File_Processor Header_Processor;  
 StringOperator StringManager; 
 bool Memory_Delete_Condition;
 bool is_this_repo_header;
 bool include_decleration_cond;
 bool isStringsEqual;
 bool This_File_Exist;
};


#endif /* DEPENDENCY_DATA_EXTRACTOR_HPP */
