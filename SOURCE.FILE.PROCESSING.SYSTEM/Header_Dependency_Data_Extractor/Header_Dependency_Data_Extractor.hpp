











#ifndef HEADER_DEPENDENCY_DATA_EXTRACTOR_HPP
#define HEADER_DEPENDENCY_DATA_EXTRACTOR_HPP

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
#include <stdlib.h>     //for using the function sleep
#include "Dependency_Data_Extractor.hpp"
#include "Dependency_Data_Stack_Container.hpp"
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


struct Header_File_Data
{
     std::string Header_File;
     size_t include_number;
};

class Header_Dependency_Data_Extractor
{
public:
 Header_Dependency_Data_Extractor(char opr_sis);
 virtual ~Header_Dependency_Data_Extractor();
 void Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr);
 void Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr);
 void Receive_Dependency_Data_Stack_Container(Dependency_Data_Stack_Container * ptr);
 void Perform_Dependency_Search();
 void Clear_Dynamic_Memory();
 const std::vector<Search_Data_Records> * Get_Search_Data() const;
protected:
 void Find_Header_Files();
 void Search_For_Large_Data_Set(size_t data_size);
 void Search_For_Middle_Data_Set(size_t data_size);
 void Search_For_Small_Data_Set(size_t data_size);
 void Clear_String_Memory(std::string & str);
 void Clear_Vector_Memory(std::vector<std::string> & vec);
 void Clear_Search_Data_Memory(std::vector<Search_Data> & data);
 void Extract_Dependency_Search_Data(int start, int end);
 void Search_Dependency_Data_For_Path(std::string path);
 int  Split_Range(int range_size, int partition, int & ramaining_job);
 Dependency_Data_Stack_Container * Stack_Container;
 Source_File_Information_Collector Info_Collector; 
 Header_File_Processor Hdr_Processor;
 Project_Src_Code_Rdr * Code_Rdr;
 std::vector<Header_File_Data> Header_Files;
 std::mutex mtx;
 std::vector<std::thread> threadPool;
 bool Memory_Delete_Condition;
 char opr_sis;
};


#endif /* HEADER_DEPENDENCY_DATA_EXTRACTOR_HPP */
