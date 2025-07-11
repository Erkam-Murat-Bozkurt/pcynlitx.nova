







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
#include "Dependency_Data_Stack_Container.hpp"
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



class Dependency_Data_Extractor
{
public:
 Dependency_Data_Extractor();
 virtual ~Dependency_Data_Extractor();
 void Receive_Operating_System(char opr_sis);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Receive_Stack_Container(Dependency_Data_Stack_Container * ptr);
 void Extract_Dependency_Tree(std::string path);
 void Determine_Source_File_Dependencies(std::string path);
 const Search_Data_Records * Get_Search_Data() const;
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
protected:
 void Recursive_Source_File_Dependency_Determination(std::string path);
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
 void Add_Search_Data_Vector(const std::vector<Search_Data> & vec);
 void Clear_Search_Data_Memory(std::vector<Search_Data> & data);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_Map_Memory(std::unordered_map<std::string, Search_Data *> & Map_Inc_Dec);
 void Clear_Temporary_Memory();
 void Construct_Search_Data_Records_Structure(std::string path);
 const std::vector<std::string> * Get_File_Include_Delarations(std::string path) const;
 const std::vector<std::string> * Include_Declerations;
 Header_File_Processor Header_Processor;  
 Project_Src_Code_Rdr * Code_Rd;
 Dependency_Data_Stack_Container * Stack_Ptr;
 Search_Data_Records Search_Record;
 std::vector<Search_Data> Dependent_Headers;
 std::vector<std::string> External_Header_Files;
 std::unordered_map<std::string, Search_Data *> Map_Inc_Dec;
 int search_counter;
 bool Memory_Delete_Condition;
};


#endif /* DEPENDENCY_DATA_EXTRACTOR_HPP */
