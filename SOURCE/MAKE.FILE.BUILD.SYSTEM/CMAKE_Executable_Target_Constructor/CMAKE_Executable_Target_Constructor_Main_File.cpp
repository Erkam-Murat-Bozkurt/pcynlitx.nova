






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


    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";


    CMAKE_Executable_Target_Constructor CMK_TARGET_EXE_Builder(argv[1],'w','n');
    
    CMK_TARGET_EXE_Builder.Build_MakeFile(_argm2,_argm3);
       
    CMK_TARGET_EXE_Builder.Clear_Object_Memory();

    std::cout << "\n\nCMAKE Target constructed..\n\n";

    return 0;
}