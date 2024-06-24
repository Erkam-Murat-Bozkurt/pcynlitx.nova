




#include <iostream>
#include <cstring>
#include "CMAKE_Build_System_Generator.hpp"
#include "CMAKE_System_Constructor.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_File_Reader('w','n');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_File_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    Data_Processor.Extract_Directory_Tree();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information();


    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";

    CMAKE_Build_System_Generator BLD_System_Gnerator(argv[1],'w');

    BLD_System_Gnerator.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

    BLD_System_Gnerator.Receive_Descriptor_File_Reader(&Des_File_Reader);

    BLD_System_Gnerator.Receive_Git_Data_Processor(&Data_Processor);

    BLD_System_Gnerator.Construct_Build_System();

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
