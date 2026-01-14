




#ifndef CMAKE_SYSTEM_CONSTRUCTOR_HPP
#define CMAKE_SYSTEM_CONSTRUCTOR_HPP

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
#include "Descriptor_File_Reader.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "CMAKE_Target_Library_Builder.hpp"
#include "Make_File_Cleaner.hpp"
#include "MakeFile_Data_Collector.hpp"
#include "MakeFile_Directory_Constructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"

class CMAKE_System_Constructor
{
public:
 CMAKE_System_Constructor(char * DesPath, char opr_sis, char build_type);
 virtual ~CMAKE_System_Constructor();
 void Build_Make_Files(std::string project_name, std::string version_num); 
 void Receive_System_Interface(Custom_System_Interface * sysInt);
 void Clear_Dynamic_Memory();
protected:
 void Write_MakeFiles(int start, int end);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_String_Memory(std::string & str);
 void Construct_Path(std::string * ptr, std::string str, std::string wrd);
 void Perform_Data_Map_Construction();
 void Perform_MakeFile_Construction();
 size_t Split_Range(size_t range_size, size_t partition, size_t & remaining_job);
 void Construct_For_Large_Data_Set(size_t data_size);
 void Construct_For_Middle_Data_Set(size_t data_size);
 void Construct_For_Small_Data_Set(size_t data_size);
 CMAKE_Main_File_Writer CMK_MF_Builder;
 Descriptor_File_Reader Des_Reader;
 Git_Data_Processor Data_Processor;
 Source_File_Dependency_Determiner Dep_Determiner;
 std::vector<Compiler_Data> * Compiler_Data_Pointer;
 Custom_System_Interface * SysInt;
 char * Des_Path;
 std::vector<std::thread> threadPool;
 std::unordered_map<std::string, Compiler_Data> DataMap;
 std::mutex mtx;
 std::string Warehouse_Path;
 std::string Repo_Dir;
 std::string repo_head_dir;
 std::string repo_obj_dir;
 std::string DesPATH;
 char opr_sis;
 char build_type;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_SYSTEM_CONSTRUCTOR_HPP */
