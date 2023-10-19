

#include <iostream>
#include <cstring>
#include "Auto_MakeFile_Builder.h"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }




    Descriptor_File_Reader Des_File_Reader('w');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_File_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information();


    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";

    Auto_MakeFile_Builder Make_Builder(argv[1],'w');

    Make_Builder.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    Make_Builder.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Make_Builder.Build_Make_Files();

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
