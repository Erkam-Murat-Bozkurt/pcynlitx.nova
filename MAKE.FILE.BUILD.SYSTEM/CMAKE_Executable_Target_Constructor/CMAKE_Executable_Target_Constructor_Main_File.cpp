






#include <iostream>
#include <cstring>
#include <map>
#include <unordered_map>
#include <iterator>
#include "CMAKE_Executable_Target_Constructor.hpp"
#include "MakeFile_Path_Determiner.hpp"
#include "Git_Data_Processor.hpp"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc <4){

       std::cout << "\n The usage: CMAKE_Executable_Target_Constructor.exe <Descriptor File Path>";

       std::cout << " <Target File Path> <Exe-Name>";

       std::cout << "\n\n";

       exit(0);
    }

    // COMMAND LINE ARGUMENTS TYPE CONVERSION

    size_t _argm2_size = strlen(argv[2]);

    std::string _argm2;

    for(size_t i=0;i<_argm2_size;i++){

          _argm2.push_back(argv[2][i]);
       }

    _argm2.shrink_to_fit();

    
    std::string _argm3;

    size_t _argm3_size = strlen(argv[3]);

    for(size_t i=0;i<_argm3_size;i++){

        _argm3.push_back(argv[3][i]);
    }

    _argm3.shrink_to_fit();

    std::cout << "\n _argm2:" << _argm2;

    std::cout << "\n _argm3:" << _argm3;

    std::cin.get();


    Descriptor_File_Reader Des_File_Reader('w','n');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_File_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information(_argm2);


    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";


    CMAKE_Executable_Target_Constructor CMK_TARGET_EXE_Builder;
    
    CMK_TARGET_EXE_Builder.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    CMK_TARGET_EXE_Builder.Receive_Descriptor_File_Reader(&Des_File_Reader);

    CMK_TARGET_EXE_Builder.Receive_Operating_System('w');


    CMK_TARGET_EXE_Builder.Build_MakeFile(_argm2,_argm3);
       
    CMK_TARGET_EXE_Builder.Clear_Object_Memory();

    std::cout << "\nCMAKE Target constructed..";

    return 0;
}