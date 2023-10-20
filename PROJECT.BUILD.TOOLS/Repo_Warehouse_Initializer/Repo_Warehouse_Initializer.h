
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
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"

class Repo_Warehouse_Initializer
{
public:
 Repo_Warehouse_Initializer(char * DesPath, char opr_sis);
 virtual ~Repo_Warehouse_Initializer();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Git_Data_Processor(Git_Data_Processor * ptr);
 void Build_Project_Warehouse();
 void Clear_Dynamic_Memory();
protected:
 void Determine_Warehouse_Path();
 void Determine_Object_Files_Directory();
 void Determine_Library_Files_Directory();
 void Determine_Compiler_Output_Directory();
 void Determine_Make_Files_Directory();
 void Determine_Current_Directory();
 void Construct_Warehouse_Path();
 void Construct_Object_Files_Directory();
 void Construct_Make_Files_Directory();
 void Construct_Library_Files_Directory();
 void Construct_Compiler_Outputs_Directory();
 void Clear_String_Memory(std::string * pointer);
 Git_Data_Processor * Git_Dt_Proc;
 DirectoryOperations DirectoryManager;
 Descriptor_File_Reader * Des_Reader;
 std::string warehouse_location;
 std::string warehouse_path;
 std::string current_directory;
 std::string Make_Files_Directory;
 std::string Object_Files_Directory;
 std::string Library_Files_Directory;
 std::string Compiler_Outputs_Directory; 
 char opr_sis;
};

#endif /* REPO_WAREHOUSE_INITIALIZER_H */
