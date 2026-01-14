



#include <iostream>
#include <cstring>
#include "MakeFile_Directory_Constructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: MakeFile_Directory_Constructor.exe <Descriptor File Path> ";

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


    MakeFile_Directory_Constructor Directory_Constructor;

    Directory_Constructor.Receive_Operating_System('w');

    Directory_Constructor.Receive_Descriptor_File_Reader(&Des_File_Reader);


    std::vector<Compiler_Data> * vec_ptr = Dep_Determiner.Get_Compiler_Data_Address();

    Directory_Constructor.Receive_Compiler_Data_Pointer(vec_ptr);

    Directory_Constructor.Collect_Directory_Info();

    std::vector<std::string> * dirs = Directory_Constructor.Get_MakeFile_Construction_Directories();

    for(size_t i=0;i<dirs->size();i++){

        std::cout << "\n Make File Directory[" << i << "]: " << dirs->at(i);
    }

    Directory_Constructor.Construct_MakeFile_Directories();

    std::cout << "\n The end of the program ..\n\n";

    return 0;
}
