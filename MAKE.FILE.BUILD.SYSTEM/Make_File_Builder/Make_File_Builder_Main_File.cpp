
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }



    Project_Files_Lister File_Lister(argv[1],'w');

    File_Lister.Determine_Git_Repo_Info();

    int file_num = File_Lister.Get_Source_File_Number();

    
    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Collect_Dependency_Information();

    std::vector<Compiler_Data> * vec_ptr = Dep_Determiner.Get_Compiler_Data_Address();


    Make_File_Builder File_Builder(argv[1],'w');

    if(file_num > 0){

       File_Builder.Receive_File_Lister_Pointer(&File_Lister);

       File_Builder.Receive_Compiler_Data_Pointer(vec_ptr);

       File_Builder.Build_MakeFile(0);
    }

    std::cout << "\n The make file constructed";
    std::cout << "\n\n";

    return 0;
}
