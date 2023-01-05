



// Header decleraiton

#ifndef DESCRIPTOR_FILE_DATA_COLLECTOR_HPP
#define DESCRIPTOR_FILE_DATA_COLLECTOR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <windows.h>
#include <vector>
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"

class Descriptor_File_Data_Collector
{
public:
 Descriptor_File_Data_Collector(char * FilePATH);
 Descriptor_File_Data_Collector(std::string FilePATH);
 virtual ~Descriptor_File_Data_Collector();
 void Collect_Descriptor_File_Data();
 void Clear_Dynamic_Memory();
 int Get_Record_Directory_Record_Area(int index);
 int Get_Library_Directories_Record_Area(int index);
 int Get_Library_Files_Record_Area(int index);
 int Get_Source_File_Directories_Record_Area(int index);
 int Get_Include_Directories_Record_Area(int index);
 int Get_Standard_Record_Area(int index);
 int Get_Options_Record_Area(int index);
 int Get_Warehouse_Location_Record_Area(int index);
 int Get_Main_File_Name_Record_Area(int index);
 int Get_Executable_File_Name_Record_Area(int index);
 int Get_Root_Directory_Record_Area(int index);
 int Get_Descriptor_File_Line_Number();
 std::string Get_Descriptor_File_Line(int line_number);
 void Print_Descriptor_File_Index();
protected:
 void Initialize_Members();
 int  FindStringPoint(std::string search_word,int startPoint);
 void Receive_Descriptor_File_Index();
 void Receive_Descriptor_File_Path(std::string path);
 void Determine_Standard_Record_Area();
 void Read_File_Content();
 void Determine_Main_File_Des_Record_Area();
 void Determine_Executable_File_Name_Record_Area();
 void Determine_Include_Directories_Record_Area();
 void Determine_Source_File_Directories_Record_Area();
 void Determine_Library_Directories_Record_Area();
 void Determine_Library_Files_Record_Area();
 void Determine_Options_Record_Area();
 void Determine_Warehouse_Location_Record_Area();
 void Determine_Root_Directory_Record_Area();
 void Delete_Spaces_on_String(std::string * pointer);
 StringOperator StringManager;
 Cpp_FileOperations FileManager;
 std::string Descriptor_File_Path;
 std::vector<std::string> File_Index;
 int wordPosition;
 int File_Size;
 int Root_Directory_Record_Area[2];
 int Warehouse_Location_Record_Area[2];
 int Library_Directories_Record_Area[2];
 int Library_Files_Record_Area[2];
 int Source_File_Directories_Record_Area[2];
 int Include_Directories_Record_Area[2];
 int Standard_Record_Area[2];
 int Options_Record_Area[2];
 int Main_File_Name_Record_Area[2];
 int Executable_File_Name_Area[2];
 int Library_Directories_Record_Number;
 int Source_File_Directories_Record_Number;
 int Include_Directories_Record_Number;
 bool Memory_Delete_Condition;
};

#endif /* DESCRIPTOR_FILE_DATA_COLLECTOR_HPP */
