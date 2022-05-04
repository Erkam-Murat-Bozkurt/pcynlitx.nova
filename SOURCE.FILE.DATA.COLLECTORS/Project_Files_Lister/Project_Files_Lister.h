

#ifndef PROJECT_FILES_LISTER_H
#define PROJECT_FILES_LISTER_H

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Descriptor_File_Reader.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Header_File_Determiner.h"
#include "Source_File_Determiner.h"
#include "Source_File_Data_Collector.hpp"
#include "Project_Files_Data_Collector.hpp"
#include "StringOperator.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"


struct Build_System_Data {

  bool   is_this_a_source_file;
  bool   is_this_a_header_file;
  char * git_record_path;  // Header path in git record
  char * git_record_dir;
  char * File_Directory;
  char * File_Path;     // Header file exact path ( System Path )
  char * File_Name;
  char * File_Name_With_Ext; // The header file name with extention
  char * class_header_file_name;
  char * class_header_file_path;
  char ** Included_Header_Files;
  char ** Included_Header_Files_Directories;
  char ** Included_Header_Files_System_Path;
  char ** Included_Header_Files_Git_Record_Path;
  char ** Included_Header_Files_Git_Record_Dir;
  int  Included_Header_Files_Number;

};

class Project_Files_Lister
{
public:
 Project_Files_Lister();
 Project_Files_Lister(const Project_Files_Lister & orig);
 virtual ~Project_Files_Lister();
 void Determine_Git_Repo_Info(Descriptor_File_Reader * Pointer);
 int Get_Source_File_Number();
 char * Get_Source_File_Directory(int num);
 char * Get_Source_File_Git_Record_Path(int num);
 char * Get_Source_File_System_Path(int num);
 char * Get_Source_File_Name(int num);
 char * Get_Source_File_Name_With_Ext(int num);
 char * Get_Source_File_Header(int src_num, int hdr_num);
 char * Get_Source_File_Header_Directory(int src_num, int hdr_num);
 char * Get_Source_File_Header_System_Path(int src_num, int hdr_num);
 char * Get_Source_File_Header_Git_Record_Path(int src_num, int hdr_num);
 char * Get_Source_File_Header_Git_Record_Dir(int src_num, int hdr_num);
 char * Get_Independent_Header_File(int num);
 char * Get_Class_File_Header_System_Path(int src_num);
 char * Get_Class_File_Header_Name(int src_num);
 char * Get_Source_File_Git_Record_Directory(int src_num);
 int  Get_Source_File_Include_File_Number(int num);
 int  Get_Indenpendent_Header_Files_Number();
protected:
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 void Determine_Git_Record_Directories(char operating_sis);
 void Determine_Git_Record_Dir(int data_num, char operating_sis);
 void Determine_Class_Header_Files();
 void Determine_Class_Header_File_Name(int data_num);
 void Determine_Source_File_Number();
 void Determine_Header_File_Number();
 void Collect_Source_Files_Data(char operating_sis);
 void Initialize_Data_Structures();
 void Collect_Independent_Header_Files_Data(char operating_sis);
 void Clear_Dynamic_Memory();
 void Clear_Pointer_Memory(char ** pointer);
 bool Check_String_Equality(char * firstString,char * secondString);
 void Allocate_Memory_For_Headers_Data(int index,int inc_hdr_num);
 void Place_Source_File_Headers_Data(int index, char operating_sis);
 void Place_Headers_Data(int index,int inc_hdr_num, char operating_sis);
 void Place_Source_File_Data(int index, char * file_path, char operating_sis);
 void Place_String(char ** pointer, std::string string_line);
 void Place_String(char ** pointer, char * string);
 Source_File_Data_Collector Src_Data_Col;
 Descriptor_File_Reader * Des_Reader_Pointer;
 Git_File_List_Receiver Git_Data_Receiver;
 Header_File_Determiner Header_Determiner;
 Source_File_Determiner Source_Determiner;
 Project_Files_Data_Collector Data_Cltr;
 StringOperator StringManager;
 DirectoryOperations DirectoryManager;
 Cpp_FileOperations FileManager;
 CharOperator Character_Operator;
 Build_System_Data * Data;
 char *  Repo_Dir;
 char ** independent_header_files;
 int  independent_header_files_number;
 int  Source_File_Number;
 int  Header_File_Number;
 int  git_record_size;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
};

#endif /* PROJECT_FILES_LISTER_H */
