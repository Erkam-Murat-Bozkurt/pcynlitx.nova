




#ifndef PROJECT_SRC_CODE_RDR_HPP
#define PROJECT_SRC_CODE_RDR_HPP

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <vector>
#include <thread>
#include <map>
#include <unordered_map>
#include <iterator>
#include <utility>      // std::pair, std::make_pair
#include <stdexcept>      // std::out_of_range
#include "Git_File_List_Receiver.hpp"
#include "Source_File_Determiner.h"
#include "Header_File_Determiner.h"
#include "Descriptor_File_Reader.hpp"
#include "DirectoryOperations.h"
#include "Cpp_FileOperations.h"


struct FileData
{
   std::string sys_path;
   std::string file_name;
   std::vector<std::string> FileContent;
};


class Project_Src_Code_Rdr
{
public:
 Project_Src_Code_Rdr(char opr_sis);
 virtual ~Project_Src_Code_Rdr();
 void Receive_Descriptor_File_Path(char * DesPATH);
 void Receive_Descriptor_File_Path(std::string DesPATH);   
 void Receive_Git_Repo_Information(Git_File_List_Receiver * ptr);
 void Read_Project_Source_Code_Files();
 std::vector<std::string> * Get_File_Content(int i);
 void Get_File_Content_From_Path(std::vector<std::string> & content, std::string path);
 FileData * Find_File_Data_From_Path(std::string path);
 FileData * Find_File_Data_From_Name(std::string name);
 std::string Get_File_Path(int i);
 std::string Get_File_Name(int i);
 bool Is_This_Repo_File(std::string path);
 bool Check_Repo_File_Status(std::string name);
 size_t Get_Project_Files_Number();
 void   Clear_Dynamic_Memory();
 void   Clear_Object_Memory();
protected:
 void Clear_Vector_Memory(std::vector<std::string> * pointer);
 void Clear_String_Memory(std::string * ptr);
 void Clear_Thread_Objects_Memory();
 void Read_Source_Code(int th_num, int st, int end);
 void Delete_Spaces_on_String(std::string * str);
 void Read_Source_Code_Single_Thread();
 void Receive_File_Paths();
 bool CompareString(std::string str1, std::string str2);
 void Determine_File_Name(std::string path, std::string & name);
 Cpp_FileOperations FileManager[8];
 std::vector<FileData> Src_Code_Dt;
 std::vector<std::string> FilePaths;
 Git_File_List_Receiver * Git_Data_Ptr;
 Source_File_Determiner ** Src_Determiner;
 Header_File_Determiner ** Hdr_Determiner;
 char opr_sis;
 std::thread threads[8];
 std::mutex mtx;
 std::string File_Name;
 std::unordered_map<std::string, FileData> CodeBase;
 std::unordered_map<std::string, FileData> CodeBase_Name;
 bool Memory_Delete_Condition;
 bool isStringsEqual;
};

#endif /* PROJECT_SRC_CODE_RDR_HPP */
