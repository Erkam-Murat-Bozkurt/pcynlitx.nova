






#include <iostream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <iterator>
#include "CMAKE_Main_File_Writer.hpp"
#include "MakeFile_Path_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"


void Print_String_Vector(std::vector<std::string> & vec);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: CMAKE_Main_File_Writer.exe <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader('w','n');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();



    CMAKE_Main_File_Writer CMK_MF_Builder;

    CMK_MF_Builder.Receive_Descriptor_File_Reader(&Des_Reader);

    CMK_MF_Builder.Receive_Git_Data_Processor(&Data_Processor);

    CMK_MF_Builder.Receive_Operating_System('w');
    
    CMK_MF_Builder.Build_Main_CMAKE_File();
       
    CMK_MF_Builder.Clear_Object_Memory();

    return 0;
}


void Print_String_Vector(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         std::cout << "\n String[" << i << "]:" << vec.at(i);
     }
}