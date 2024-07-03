






#include <iostream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <iterator>
#include "CMAKE_Executable_Target_Constructor.hpp"
#include "MakeFile_Path_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"


void Print_String_Vector(std::vector<std::string> & vec);

int main(int argc, char ** argv){

    if(argc <4){

       std::cout << "\n The usage: CMAKE_Executable_Target_Constructor.exe <Descriptor File Path> <Target File Path> <Exe-Name>";

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

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);
    


    CMAKE_Executable_Target_Constructor CMK_TARGET_EXE_Builder;

    CMK_TARGET_EXE_Builder.Receive_Descriptor_File_Reader(&Des_Reader);

    CMK_TARGET_EXE_Builder.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    CMK_TARGET_EXE_Builder.Receive_Operating_System('w');
    
    CMK_TARGET_EXE_Builder.Build_MakeFile(argv[2],argv[3]);
       
    CMK_TARGET_EXE_Builder.Clear_Object_Memory();

    return 0;
}


void Print_String_Vector(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         std::cout << "\n String[" << i << "]:" << vec.at(i);
     }
}