


#ifndef CMAKE_BUILD_SYSTEM_GENERATOR_HPP
#define CMAKE_BUILD_SYSTEM_GENERATOR_HPP

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
#include "CMAKE_System_Constructor.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "Descriptor_File_Reader.hpp"
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

class CMAKE_Build_System_Generator
{
public:
 CMAKE_Build_System_Generator(char * DesPath, char opr_sis, char build_type);
 virtual ~CMAKE_Build_System_Generator();
 void Construct_Build_System();
 void Clear_Dynamic_Memory();
protected:
 Git_Data_Processor Data_Processor;
 Descriptor_File_Reader Des_Reader;
 Source_File_Dependency_Determiner Dep_Determiner;
 CMAKE_System_Constructor CMAKE_ListFileBuilder;
 CMAKE_Main_File_Writer CMAKE_MainFileBuilder;
 char opr_sis;
 bool Memory_Delete_Condition;
};

#endif /* CMAKE_BUILD_SYSTEM_GENERATOR_HPP */
