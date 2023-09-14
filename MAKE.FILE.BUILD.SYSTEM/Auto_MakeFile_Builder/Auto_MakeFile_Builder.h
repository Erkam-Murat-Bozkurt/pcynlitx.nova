


#ifndef AUTO_MAKEFILE_BUILDER_H
#define AUTO_MAKEFILE_BUILDER_H

#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>     //for using the function sleep
#include <thread>
#include <mutex>
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Make_File_Builder.h"
#include "Make_File_Cleaner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Lister.h"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class Auto_MakeFile_Builder
{
public:
 Auto_MakeFile_Builder(char * DesPath, char opr_sis);
 virtual ~Auto_MakeFile_Builder();
 void Build_Make_Files(); 
 void Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * dep_ptr);
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Clear_Dynamic_Memory();
protected:
 void Determine_Project_Directories();
 void Write_MakeFiles(int thr_num, int start, int end);
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * ptr);
 void Construct_Path(std::string * ptr, std::string str, std::string wrd);
 void Construct_Data_Map(int thr_num, int start, int end);
 void Perform_Data_Map_Construction();
 void Perform_MakeFile_Construction();
 Source_File_Dependency_Determiner * Dep_Determiner;
 Git_Data_Processor * Git_Data_Proc;
 std::vector<Compiler_Data> * Compiler_Data_Pointer;
 Make_File_Builder Mk_Builder[16];
 Make_File_Cleaner Mk_File_Clnr;
 Descriptor_File_Reader * Des_Reader;
 std::thread threads[16];
 std::mutex mtx;
 std::unordered_map<std::string, Compiler_Data> DataMap;
 std::string Warehouse_Path;
 std::string Repo_Dir;
 std::string repo_head_dir;
 std::string repo_obj_dir;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* AUTO_MAKEFILE_BUILDER_H */
