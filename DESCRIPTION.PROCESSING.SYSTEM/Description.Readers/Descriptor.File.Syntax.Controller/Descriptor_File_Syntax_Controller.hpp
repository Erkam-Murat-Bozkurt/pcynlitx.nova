




// Header decleraiton

#ifndef DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP
#define DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include "StringOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Syntax_Controller
{
public:
 Descriptor_File_Syntax_Controller();
 Descriptor_File_Syntax_Controller(const Descriptor_File_Syntax_Controller & orig);
 virtual ~Descriptor_File_Syntax_Controller();
 void Control_Descriptor_File_Syntax(char * path);
 void Clear_Dynamic_Memory();
protected:
 void Control_Keywords();
 void Control_Braces();
 bool Control_String_Inclusion(char * search_word);
 int  Determine_Repitation(char * search_word);
 void Delete_Spaces_on_String(char ** pointer);
 void Receive_Descriptor_File_Path(char * pointer);
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
 char * Descriptor_File_Path;
 bool include_condition;
 bool Memory_Delete_Condition;
 int repitation;
};

#endif /*  DESCRIPTOR_FILE_SYNTAX_CONTROLLER_HPP */
