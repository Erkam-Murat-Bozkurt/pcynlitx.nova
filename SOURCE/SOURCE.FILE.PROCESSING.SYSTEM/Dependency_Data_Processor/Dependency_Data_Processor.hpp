









#ifndef DEPENDENCY_DATA_PROCESSOR_HPP
#define DEPENDENCY_DATA_PROCESSOR_HPP

#include <cstring>
#include <cstdlib>
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
#include <map>
#include <unordered_map>
#include <iterator>
#include <utility>                     // std::pair, std::make_pair
#include <stdexcept>                   // std::out_of_range
#include <thread>
#include <mutex>
#include <stdlib.h>                    //for using the function sleep
#include <algorithm>
#include "Header_Dependency_Data_Extractor.hpp"
#include "Dependency_Data_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Header_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Header_File_Determiner.h"
#include "StringOperator.h"
#include "CharOperator.h"
#include "Cpp_FileOperations.h"
#include "DirectoryOperations.h"
#include "IntToCharTranslater.h"


class Dependency_Data_Processor
{
public:
 Dependency_Data_Processor(char opr_sis);
 virtual ~Dependency_Data_Processor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Perform_Dependency_Search();
 const Search_Data_Records * Find_Search_Data_From_Path(std::string path) const;
 const std::vector<Search_Data_Records> * Get_Search_Data() const;
 void Clear_Dynamic_Memory();
 void Clear_Object_Memory();
 void Perform_Data_Reordering(size_t data_size);
protected:
 void Clear_Temporary_Memory();
 bool Is_Exist_OnSearchStack(std::string path);
 void ReOrder_Stack_Data(Search_Data_Records * ptr);
 void Re_Order_Dependency_Data(int str, int end);
 void Clear_String_Memory(std::string & str);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_Search_Data_Memory(std::vector<Search_Data> & data);
 void Extract_Dependency_Search_Data(int start, int end);
 void Search_Dependency_Data_For_Path(std::string path);
 void ReOrdering_For_Large_Data_Set(size_t data_size);
 void ReOrdering_For_Middle_Data_Set(size_t data_size);
 void ReOrdering_For_Small_Data_Set(size_t data_size);
 void Search_For_Large_Data_Set(size_t data_size);
 void Search_For_Middle_Data_Set(size_t data_size);
 void Search_For_Small_Data_Set(size_t data_size);
 Header_Dependency_Data_Extractor Hdr_Dep_Extractor;
 Dependency_Data_Stack_Container Stack_Container;
 Source_File_Information_Collector Info_Collector; 
 Project_Src_Code_Rdr * Code_Rdr;
 std::vector<std::thread> threadPool;
 std::vector<Source_File_Data> * Source_File_Data_Ptr;
 std::vector<Search_Data_Records> Dependency_Search_Data;
 std::mutex mtx;
 bool Memory_Delete_Condition;
};


#endif /* DEPENDENCY_DATA_PROCESSOR_HPP */
