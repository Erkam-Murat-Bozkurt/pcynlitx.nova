



#ifndef INCLUDE_DEPENDENCY_COUNTER_H
#define INCLUDE_DEPENDENCY_COUNTER_H

#include <cstring>
#include <string>
#include "Git_File_List_Receiver.hpp"
#include "Cpp_FileOperations.h"
#include "StringOperator.h"

class Include_Dependency_Counter
{
public:
 Include_Dependency_Counter();
 Include_Dependency_Counter(const Include_Dependency_Counter & orig);
 virtual ~Include_Dependency_Counter();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer);
 int  Determine_Header_File_Inclusion_Number(char * Src_Data_Pointer);
 void Extract_Header_Name_From_String_Line(char ** header_name, char * string_line, char * file_path);
 void Extract_Include_File_Name_From_Path(char ** pointer, char * string );
 bool Is_This_Repo_Header(char * string_line, char * file_path);
 bool CompareString(char * firstString,char * secondString);
protected:
 Git_File_List_Receiver Git_Data_Receiver;
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
 std::string String_Line;
 int  git_record_size;
 int  Dependent_Header_Files_Number;
 bool is_this_repo_header;
 bool isStringsEqual;
 bool Memory_Delete_Condition;
};

#endif /* INCLUDE_DEPENDENCY_COUNTER_H */
