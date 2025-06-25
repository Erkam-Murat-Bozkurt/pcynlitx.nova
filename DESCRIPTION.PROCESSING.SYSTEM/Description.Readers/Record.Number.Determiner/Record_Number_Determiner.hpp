




// Header decleraiton

#ifndef RECORD_NUMBER_DETERMINER_HPP
#define RECORD_NUMBER_DETERMINER_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "Descriptor_File_Data_Collector.hpp"
#include "Descriptor_File_Syntax_Controller.hpp"
#include "StringOperator.h"
#include "Cpp_FileOperations.h"


class Record_Number_Determiner
{
public:
 Record_Number_Determiner();
 virtual ~Record_Number_Determiner();
 void Receive_Descriptor_File_Data_Collector(Descriptor_File_Data_Collector * ptr);
 void Determine_Record_Numbers();
 int Get_Root_Directory_Location_Record_Number();
 int Get_Warehouse_Location_Record_Number();
 int Get_Standard_Record_Number();
 int Get_Include_Directories_Record_Number();
 int Get_Source_File_Directories_Record_Number();
 int Get_Library_Directories_Record_Number();
 int Get_Library_Files_Record_Number();
 int Get_Compiler_Options_Record_Number();
 int Get_Linker_Options_Record_Number();
 int Get_Build_System_Type_Record_Number();
 int Get_Project_Name_Record_Number();
 int Get_Version_Number_Record_Number();
 int Get_Compiler_Paths_Record_Number();

protected:
 void Determine_Root_Directory_Location_Record_Number();
 void Determine_Warehouse_Location_Record_Number();
 void Determine_Standard_Record_Number();
 void Determine_Include_Directories_Record_Number();
 void Determine_Source_File_Directories_Record_Number();
 void Determine_Library_Directories_Record_Number();
 void Determine_Library_Files_Record_Number();
 void Determine_Compiler_Options_Record_Number();
 void Determine_Linker_Options_Record_Number();
 void Determine_Build_System_Type_Record_Number();
 void Determine_Project_Name_Record_Number();
 void Determine_Version_Number_Record_Number();
 void Determine_Compiler_Paths_Record_Number();
 void Reset_Record_Numbers();
 bool Is_Include_Character(std::string str);
 Descriptor_File_Data_Collector * Data_Collector;
 StringOperator StringManager;
 bool Memory_Delete_Condition;
 int Root_Directory_Location_Record_Number;
 int Warehouse_Location_Record_Number;
 int Standard_Record_Number;
 int Include_Directories_Record_Number;
 int Source_File_Directories_Record_Number;
 int Library_Directories_Record_Number;
 int Library_Files_Record_Number;
 int Compiler_Options_Record_Number;
 int Linker_Options_Record_Number;
 int Build_System_Type_Record_Number;
 int Project_Name_Record_Number;
 int Version_Number_Record_Number;
 int Compiler_Paths_Record_Number;
 char opr_sis;
};

#endif /* RECORD_NUMBER_DETERMINER_HPP */
