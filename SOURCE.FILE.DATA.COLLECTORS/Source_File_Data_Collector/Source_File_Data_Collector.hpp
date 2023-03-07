

// Header decleraiton

#ifndef SOURCE_FILE_DATA_COLLECTOR_H
#define SOURCE_FILE_DATA_COLLECTOR_H

#include <cstring>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include <vector>
#include "Git_File_List_Receiver.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

struct Include_File_Data
{
    std::string Include_File_Name;
    std::string Include_File_Directory;
    std::string Include_File_Git_Record_Path;
    std::string Include_File_Git_Record_Dir;
    int Include_File_Number;
};


struct Build_System_Data {

  std::string git_record_path;     // Header path in git record
  std::string git_record_dir;      // The git record directory
  std::string File_Directory;      // The directory of the file which is record constructed
  std::string File_Path;           // The file exact path ( System Path )
  std::string File_Name;           // The file name witout extentation
  std::string File_Name_With_Ext;  // The header file name with extention
  std::string class_header_file_name;
  std::string class_header_file_path;
  std::vector<std::string> Included_Header_Files;    // The list of included header files if the file is a source file
  std::vector<std::string> Included_Header_Files_Directories;
  std::vector<std::string> Included_Header_Files_System_Path;
  std::vector<std::string> Included_Header_Files_Git_Record_Path;
  std::vector<std::string> Included_Header_Files_Git_Record_Dir;
  int  Included_Header_Files_Number;  // The number of the header file included if the file is a source file
  bool is_this_a_source_file;
  bool is_this_a_header_file;
};


class Source_File_Data_Collector
{
public:
 Source_File_Data_Collector(char * DesPath, char operating_sis);
 virtual ~Source_File_Data_Collector();
 void Process_Source_File_Data(Build_System_Data * Ptr, std::string path);
 void Clear_Dynamic_Memory();
 int  Get_Included_File_Number();
 std::string Get_Include_File_Name(int num);
 std::string Get_Include_File_Directory(int num);
 std::string Get_Include_File_Git_Record_Directory(int num);
 std::string Get_Include_File_Git_Record_Path(int num);
 std::string Get_Include_File_Name_Without_Ext(int num);
 Build_System_Data * Get_Data_Pointer();
protected:
 void Initialize_Members();
 void Place_Data_To_Container();
 void Place_Source_File_Data();
 void Place_Source_File_Headers_Data();
 void Place_Headers_Data(int k);
 void Determine_Class_Header_File_Name();
 void Determine_Source_File_System_Path(std::string * pointer, std::string path);
 void Extract_Upper_Directory_Path(std::string * pointer, std::string string_line);
 void Determine_File_Name(std::string * pointer, std::string string_line);
 void Determine_Source_File_Name_With_Ext(std::string * pointer, std::string file_name);
 void Determine_Header_Files_System_Paths(std::string * pointer,
      std::string directory, std::string file_name);
 void Determine_Header_File_Directory(std::string * directory,
       std::string file_path);
 void Determine_Git_Record_Header_File_Path(std::string * header_path,
       std::string header_name);
 void Determine_Git_Record_Header_File_Directory(std::string * header_dir,
       std::string header_path);
  void Determine_Git_Record_Source_File_Path(std::string * source_file_path,
       std::string file_path);
  void Determine_Git_Record_Source_File_Directory(std::string * source_file_dir,
       std::string source_file_path);
 void Extract_Include_File_Name_From_Path(std::string * pointer, std::string string );
 bool CompareString(std::string s1, std::string s2);
 bool Character_Inclusion_Check(std::string string, char chr);
 void Receive_Include_File_Names();
 void Receive_Include_File_Name(std::string * pointer, std::string string);
 bool Control_Include_Syntax(std::string string);
 void Read_File(std::string path);
 void Determine_Include_Line_Number();
 void Delete_Spaces_on_String(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_Include_File_Data(Include_File_Data * pointer);
 void Clear_String_Memory(std::string * pointer);
 Git_File_List_Receiver Git_Receiver;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 char operating_sis;
 bool syntax_error;
 bool isStringsEqual;
 bool Character_Inclusion_Status;
 std::string Git_Repo_Dir;
 std::string FilePATH;
 std::vector<std::string> File_Content;
 std::vector<Include_File_Data> Head_Data;
 Build_System_Data * Data_Pointer;
 int File_Content_Size;
 int git_record_size;
 int included_header_file_number;
};

#endif /* SOURCE_FILE_DATA_COLLECTOR_H */
