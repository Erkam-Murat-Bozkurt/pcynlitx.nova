

#ifndef PROJECT_FILES_LISTER_H
#define PROJECT_FILES_LISTER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "Git_File_List_Receiver.hpp"
#include "Header_File_Determiner.h"
#include "Source_File_Determiner.h"
#include "Source_File_Data_Collector.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"



class Project_Files_Lister
{
public:
 Project_Files_Lister(char * DesPATH, char opr_sis);
 virtual ~Project_Files_Lister();
 void Determine_Git_Repo_Info();
 int  Get_Source_File_Number();
 std::string Get_Source_File_Directory(int num);
 std::string Get_Source_File_Git_Record_Path(int num);
 std::string Get_Source_File_System_Path(int num);
 std::string Get_Source_File_Name(int num);
 std::string Get_Source_File_Name_With_Ext(int num);
 std::string Get_Source_File_Header(int src_num, int hdr_num);
 std::string Get_Source_File_Header_Directory(int src_num, int hdr_num);
 std::string Get_Source_File_Header_System_Path(int src_num, int hdr_num);
 std::string Get_Source_File_Header_Git_Record_Path(int src_num, int hdr_num);
 std::string Get_Source_File_Header_Git_Record_Dir(int src_num, int hdr_num);
 std::string Get_Independent_Header_File(int num);
 std::string Get_Class_File_Header_System_Path(int src_num);
 std::string Get_Class_File_Header_Name(int src_num);
 std::string Get_Source_File_Git_Record_Directory(int src_num);
 int  Get_Source_File_Include_File_Number(int num);
 int  Get_Indenpendent_Header_Files_Number();
 void Clear_Dynamic_Memory();
protected:
 void Initialize_Members(char opr_sis);
 void Collect_Source_Files_Data();
 void Collect_Independent_Header_Files_Data();
 bool Is_This_Header_File_Included_Anywhere(std::string name);
 void Determine_File_Name_With_Ext(std::string * ptr, std::string str);
 bool Check_String_Equality(std::string s1, std::string s2);
 bool CheckStringInclusion(std::string str, std::string word);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_Build_Data_Memory(std::vector<Build_System_Data> * pointer);
 void Clear_String_Memory(std::string * pointer);
 void Clear_Build_Data(Build_System_Data * pointer);
 Git_File_List_Receiver Git_Data_Receiver;
 Source_File_Data_Collector Src_Data_Col;
 Header_File_Determiner Header_Determiner;
 Source_File_Determiner Source_Determiner;
 StringOperator StringManager;
 std::string Repo_Dir;
 std::vector<Build_System_Data> Data;
 std::vector<std::string> independent_header_files;
 std::vector<std::string> git_record_paths;
 int  independent_header_files_number;
 int  Source_File_Number;
 int  git_record_size;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
 bool is_this_file_included_anywhere;
 char operating_sis;
};

#endif /* PROJECT_FILES_LISTER_H */
