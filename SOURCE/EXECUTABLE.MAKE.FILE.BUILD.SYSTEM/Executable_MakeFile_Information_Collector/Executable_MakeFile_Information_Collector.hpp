


#ifndef EXECUTABLE_MAKEFILE_INFORMATION_COLLECTOR_HPP
#define EXECUTABLE_MAKEFILE_INFORMATION_COLLECTOR_HPP

#include <cstring>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <iterator>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <fcntl.h>
#include <windows.h>
#include "Source_File_Dependency_Determiner.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "CharOperator.h"
#include "IntToCharTranslater.h"


class Executable_MakeFile_Information_Collector
{
public:
 Executable_MakeFile_Information_Collector(char opr_sis);
 virtual ~Executable_MakeFile_Information_Collector();
 void Receive_Construction_Strategy(char strategy);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Dependency_Determiner(Source_File_Dependency_Determiner * ptr); 
 void Clear_Dynamic_Memory();

 void Determine_Src_File_Dir(std::string file_path, std::string & src_dir);
 void Determine_Make_File_Name(std::string & make_file_name,      
      std::string file_path, std::string src_file_dir);
 void Determine_Source_File_Name(std::string & source_file_name,     
      std::string file_path, std::string src_file_dir);
 void Extract_Repo_Directory_Name(std::string & name, std::string root_dir);
 void Determine_Git_Src_Dir(std::string & git_src_dir,     
      std::string src_file_dir);

 void Determine_Include_Directory_List_For_Simple_Construction(std::string & inc_dir_list_for_com, 
      std::vector<std::string> & header_file_dirs);

 void Determine_Include_Directory_List(std::string & inc_dir_list_for_com, 
      std::vector<std::string> & header_file_dirs, 
      std::vector<std::string> & header_file_upper_dirs);

 void Determine_Include_File_List_For_Simple_Construction(std::string & include_file_list,    
      std::vector<std::string> & header_file_paths);

 void Determine_Library_File_Path_List_For_Compiler_Command(std::string & library_path_list);

 void Determine_Source_File_Directory_List_For_Simple_Construction(std::string & src_dir_list_for_com);

 void Construct_Library_Directory_List_For_Compiler_Command(std::string & lib_dir_list_for_compiler);

 void Determine_External_Include_Directory_List_For_Compiler_Command(std::string & ext_inc_dir_list);

 void Determine_Project_Library_Name(std::string & project_library_name);

 void Determine_Compiler_Options_For_Compiler_Command(std::string & compiler_options);

 void Determine_Linker_Options_For_Compiler_Command(std::string & linker_options);

protected:
 void Clear_String_Memory(std::string * pointer);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Add_String(std::string * list, std::string string);
 void Place_String(std::string * pointer, std::string string);
 void Place_Information(std::string * ptr,std::string in);
 void Place_Information(std::string * ptr, char * in);
 bool Check_Include_Directory_Existance(std::vector<std::string> * hdr_dir, std::string dir);
 Descriptor_File_Reader * Des_Reader;
 Source_File_Dependency_Determiner * Dep_Determiner;
 IntToCharTranslater Translater;
 std::string warehouse_obj_dir;
 std::string warehouse_path;
 char opr_sis;
 char constraction_strategy;
};

#endif /* EXECUTABLE_MAKEFILE_INFORMATION_COLLECTOR_HPP */
