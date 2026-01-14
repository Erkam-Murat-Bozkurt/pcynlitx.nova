
#ifndef GIT_DATA_PROCESSOR_HPP
#define GIT_DATA_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include "Git_Modification_Receiver.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "Custom_System_Interface.h"


struct Git_Sub_Directory_Data
{
    std::string dir_path;
    bool source_file_inc_status;
    bool cmake_dir_status;
    std::vector<std::string> sub_dirs;
};


class Git_Data_Processor
{
public:
 Git_Data_Processor(char opr_sis);
 virtual ~Git_Data_Processor();
 void Receive_Descriptor_File_Path(char * DesPath);
 void Receive_Descriptor_File_Path(std::string DesPath);
 void Write_Git_Repo_List_File();
 void Determine_Git_Repo_Info();
 void Write_Git_Modification_File();
 void Receive_Git_Modifications();
 void Extract_Directory_Tree();
 size_t  Get_Git_File_Index_Size();
 std::string Get_Git_File_Index(int num);
 std::string Get_File_System_Path(int num);
 std::string Get_Git_Record_Directory(int num);
 std::string Get_Git_Record_Path(int num);
 std::string Get_File_Name(int num);
 std::vector<std::string> * Get_Git_File_Index_Address();
 std::vector<std::string> * Get_File_System_Path_Address();
 std::vector<std::string> * Get_Git_Record_Directory_Address();
 std::vector<std::string> * Get_Git_Record_Path_Address();
 std::vector<std::string> * Get_File_Name_Address();
 std::string Get_Git_Repo_Directory();
 std::vector<std::string> * Get_Updated_Header_Files();
 std::vector<std::string> * Get_Updated_Source_Files();
 std::vector<std::string> * Get_Directory_Tree();
 std::vector<Git_Sub_Directory_Data> * Get_Directory_Tree_Data();
 std::vector<Git_Sub_Directory_Data> * Get_Git_Root_Dirs();
 void Clear_Dynamic_Memory();
protected:
 void Construct_SubDirectory_Data();
 void Filtering_Root_Directories();
 void Find_Upper_Directory(std::string & upper, std::string dir);
 void Clear_Sub_Directory_Data(Git_Sub_Directory_Data & Data);
 void Clear_Std_String(std::string & str);
 Git_Modification_Receiver Modf_Receiver;
 Git_Modification_Lister   Modf_Lister;
 Git_File_List_Writer      List_Writer;
 Git_File_List_Receiver    List_Receiver;
 Descriptor_File_Reader    Des_Reader;
 std::vector<std::string>  Directory_Tree;
 std::vector<Git_Sub_Directory_Data> Sub_Dir_Data;
 std::vector<Git_Sub_Directory_Data> Root_Dirs;
 bool gui_read_status;
 char opr_sis;
 char * CString;
 int  File_Line_Number;
 bool Memory_Delete_Condition;
};

#endif /* GIT_DATA_PROCESSOR_HPP */
