




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
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Syntax_Controller
{
public:
 Descriptor_File_Syntax_Controller();
 virtual ~Descriptor_File_Syntax_Controller();
 void Control_Descriptor_File_Syntax(std::string path);
 void Clear_Dynamic_Memory();
protected:
 void Control_Keywords();
 void Control_Braces();
 bool Control_String_Inclusion(std::string search_word);
 int  Determine_Repitation(std::string search_word);
 void Delete_Spaces_on_String(std::string * pointer);
 void Receive_Descriptor_File_Path(std::string path);
 void Receive_Descriptor_File_Index();
 std::vector<std::string> File_Index;
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 std::string Descriptor_File_Path;
 bool include_condition;
 bool Memory_Delete_Condition;
 int repitation;
};

#endif /*  DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP */
