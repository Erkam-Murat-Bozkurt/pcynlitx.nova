




// Header decleraiton

#ifndef DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP
#define DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP

#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <windows.h>
#include <algorithm>
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Syntax_Controller
{
public:
 Descriptor_File_Syntax_Controller(char opr_sis);
 virtual ~Descriptor_File_Syntax_Controller();
 void Receive_Descriptor_File_Path(char * opr_sis);
 void Receive_Descriptor_File_Path(std::string opr_sis);
 void Set_Gui_Read_Status(bool status);
 void Control_Descriptor_File_Syntax();
 bool Get_Invalid_Descriptor_File_Status() const;
 bool GetSyntaxErrorStatus() const;
 void Clear_Dynamic_Memory();
protected:
 void Control_Keywords();
 void Control_Braces();
 bool Control_String_Inclusion(std::string search_word);
 int  Determine_Repitation(std::string search_word);
 void Delete_Spaces_on_String(std::string * pointer);
 void Receive_Descriptor_File_Index();
 void Clear_Vector_Memory(std::vector<std::string> * ptr);
 void Clear_String_Memory(std::string * ptr);
 std::vector<std::string> File_Index;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 std::string Descriptor_File_Path;
 bool include_condition;
 bool Memory_Delete_Condition;
 bool gui_read_status;
 int  syntax_error_number;
 bool syntax_error_status;
 bool invalid_descriptor_file_status;
 int repitation;
};

#endif /*  DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP */
