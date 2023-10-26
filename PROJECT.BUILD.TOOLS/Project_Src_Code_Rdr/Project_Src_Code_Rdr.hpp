




#ifndef PROJECT_SRC_CODE_RDR_HPP
#define PROJECT_SRC_CODE_RDR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <map>
#include <unordered_map>
#include <iterator>
#include <utility>                     // std::pair, std::make_pair
#include <stdexcept>                   // std::out_of_range
#include "Git_Data_Processor.hpp"
#include "Source_File_Determiner.h"
#include "Header_File_Determiner.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


struct FileData
{
   std::string sys_path;
   std::string file_name;
   std::string cmbn_name;        
   std::vector<std::string> include_declerations;
   int  inclusion_number;
   bool is_source_file;
   bool is_main_file;   
   bool is_header_file;
};

/*
   Combined file name is an include decleration including 
   
   both directory and header file. For example: "sample/sample.h"
   
   The variable "cmbn_name" is hold strings including combined file name  
   
   and it is used for header declerations including 
   
   both directory and header file.
*/


class Project_Src_Code_Rdr
{
public:
 Project_Src_Code_Rdr(char opr_sis);
 virtual ~Project_Src_Code_Rdr();
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Read_Project_Source_Code_Files();
 const std::vector<std::string> * Get_Include_Declerations(int i) const;
 const std::vector<std::string> * Get_Included_Headers_From_Path(std::string path) const;
 const FileData * Find_File_Data_From_Path(std::string path) const;
 const FileData * Find_File_Data_From_Name(std::string name) const;
 const FileData * Find_File_Data_From_Directory_File_Name_Combination(std::string name) const;
 std::string Get_File_Path(int i) const;
 std::string Get_File_Name(int i) const;
 std::string Get_Combined_File_Name(int i) const; 
 bool Is_This_Repo_File(std::string path);
 bool Check_Repo_File_Status(std::string name);
 bool Check_Repo_File_Status_From_Directory_File_Name_Combination(std::string name);
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 size_t Get_Project_Files_Number() const;
protected:
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_String_Memory(std::string & str);
 void Clear_Thread_Objects_Memory();
 void Read_Source_Code(int th_num, int st, int end);
 void Delete_Spaces_on_String(std::string * str);
 void Read_Source_Code_Single_Thread();
 void Receive_File_Paths();
 void Determine_File_Name(std::string path, std::string & name);
 void Determine_File_Combined_Name(std::string path, std::string & file_name);
 bool Include_Decleration_Test(std::string string, int thr_num);
 void Determine_Class_Function_Pattern(std::string file_path,std::string & pattern);
 void Clear_Buffer_Memory(FileData & buffer);
 std::string Extract_Include_Decleration(std::string string);
 Git_Data_Processor * Git_Data_Proc;
 Source_File_Determiner ** Src_Determiner;
 Header_File_Determiner ** Hdr_Determiner;
 Cpp_FileOperations FileManager[16];
 StringOperator StringManager[16];
 std::thread threads[16];
 std::mutex  mtx;
 std::vector<FileData> Code_Dt;
 std::vector<std::string> FilePaths;
 std::unordered_map<std::string, FileData *> Map_Path;
 std::unordered_map<std::string, FileData *> Map_Name;
 std::unordered_map<std::string, FileData *> Map_Cmbn;
 std::string root_directory;
 char opr_sis;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
};

#endif /* PROJECT_SRC_CODE_RDR_HPP */
