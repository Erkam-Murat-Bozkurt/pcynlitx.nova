
#ifndef REPO_WAREHOUSE_INITIALIZER_H
#define REPO_WAREHOUSE_INITIALIZER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <windows.h>
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Repo_Warehouse_Initializer
{
public:
 Repo_Warehouse_Initializer(char * DesPath, char opr_sis);
 virtual ~Repo_Warehouse_Initializer();
 void Build_Project_Warehouse();
 void Update_Warehaouse_Headers();
 void Clear_Dynamic_Memory();
protected:
 void Determine_Warehouse_Path();
 void Determine_Header_Files_Directory();
 void Determine_Object_Files_Directory();
 void Determine_Library_Files_Directory();
 void Determine_Compiler_Output_Directory();
 void Determine_Current_Directory();
 void Construct_Warehouse_Path();
 void Construct_Header_Files_Directory();
 void Construct_Object_Files_Directory();
 void Construct_Library_Files_Directory();
 void Construct_Compiler_Outputs_Directory();
 void Determine_Header_File_Paths();
 void Copy_Independent_Header_Files_To_Project_Headers_Location();
 void Determine_Independent_Header_Paths();
 void Copy_Header_Files_To_Project_Headers_Location();
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 Git_File_List_Writer   Git_List_Writer;
 Header_File_Determiner Header_Determiner;
 Git_File_List_Receiver Git_Receiver;
 Git_Ignoring_Files_Lister Ignoring_Files_Lister;
 DirectoryOperations DirectoryManager;
 Project_Files_Lister Dir_Lister;
 Descriptor_File_Reader Des_Reader;
 Cpp_FileOperations FileManager;
 StringOperator StringManager;
 int  source_files_number;
 int  ind_hdr_number;
 std::string  warehouse_location;
 std::string  warehouse_path;
 std::string  current_directory;
 std::vector<std::string> Header_File_Paths;
 std::vector<std::string> Headers_New_Paths;
 std::vector<std::string> Independent_Header_Paths;
 std::vector<std::string> Independent_Header_New_Paths;
 std::string Headers_Directory;
 std::string Object_Files_Directory;
 std::string Library_Files_Directory;
 std::string Compiler_Outputs_Directory; 
 char opr_sis;
};

#endif /* REPO_WAREHOUSE_INITIALIZER_H */
