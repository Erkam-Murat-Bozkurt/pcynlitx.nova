
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }

    
    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Collect_Dependency_Information();

    std::vector<Compiler_Data> * vec_ptr = Dep_Determiner.Get_Compiler_Data_Address();



    std::string src_file_name = "DataBaseBuilder.cpp";

    Make_File_Builder File_Builder(argv[1],'w');
    

    File_Builder.Receive_Compiler_Data_Pointer(vec_ptr);

    File_Builder.Build_MakeFile(src_file_name);
   
    File_Builder.Clear_Object_Memory();

    
    std::cout << "\n The make file constructed";
    std::cout << "\n\n";

    return 0;
}
