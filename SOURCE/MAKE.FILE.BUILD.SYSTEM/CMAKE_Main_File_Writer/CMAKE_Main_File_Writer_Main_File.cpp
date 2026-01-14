






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

    Data_Processor.Extract_Directory_Tree();




    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information();


    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";



    CMAKE_Main_File_Writer CMK_MF_Builder;

    CMK_MF_Builder.Receive_Descriptor_File_Reader(&Des_Reader);

    CMK_MF_Builder.Receive_Git_Data_Processor(&Data_Processor);

    CMK_MF_Builder.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    CMK_MF_Builder.Receive_Operating_System('w');
    
    CMK_MF_Builder.Build_Main_CMAKE_File();
       
    CMK_MF_Builder.CMAKE_SubDirectory_Determination();


    /*

    const std::vector<Git_Sub_Directory_Data> * Root_Dir_Data = CMK_MF_Builder.Get_CMAKE_SubDir_List();


    for(size_t i=0;i<Root_Dir_Data->size();i++){

        std::cout << "\n\n";

        std::cout << "\n Root dir:" << Root_Dir_Data->at(i).dir_path;

        std::cout << "\n Source File Inclution Status:" << Root_Dir_Data->at(i).source_file_inc_status;

        std::cout << "\n CMAKE dir status:" << Root_Dir_Data->at(i).cmake_dir_status;

        size_t sub_dir_size = Root_Dir_Data->at(i).sub_dirs.size();

        for(size_t j=0;j<sub_dir_size;j++){

            std::cout << "\n sub_dir[" << j << "]:" << Root_Dir_Data->at(i).sub_dirs.at(j);
        }
    }

    */

    CMK_MF_Builder.Clear_Object_Memory();

    std::cout << "\n\n The main CMAKE list file constructed";

    std::cout << "\n\n";

    return 0;
}


void Print_String_Vector(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         std::cout << "\n String[" << i << "]:" << vec.at(i);
     }
}