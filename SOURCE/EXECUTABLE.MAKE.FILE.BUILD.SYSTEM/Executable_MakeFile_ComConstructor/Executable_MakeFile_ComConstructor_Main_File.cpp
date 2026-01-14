


#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 5){

       std::cout << "\n The usage: Executable_MakeFile_ComConstructor.exe <Descriptor File Path> ";

       std::cout << "\n <Source File Path> <Exe name> <strategy>";

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


    if(*argv[4] == 'a'){

        Dep_Determiner.Collect_Dependency_Information(argv[2]);

    }
    else{

         if(*argv[4] == 's'){

            Dep_Determiner.Simple_Dependency_Determination_For_Single_Source_File(argv[2]);

         }
         else{

              std::cout << "\n You must enter an option";
         }
    }



    Executable_MakeFile_ComConstructor Command_Constructor('w');

    Command_Constructor.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Command_Constructor.Receive_Dependency_Determiner(&Dep_Determiner);

    Command_Constructor.Receive_ExeFileName(argv[3]);

    Command_Constructor.Receive_Construction_Strategy(*argv[4]);

    Command_Constructor.Construct_Compiler_Commands(argv[2]);
    


    std::string Compiler_System_Command = Command_Constructor.Get_Compiler_System_Command();

    std::cout << "\nCompiler_System_Command:" << std::endl;
    
    std::cout << Compiler_System_Command;

    std::cout << "\n\n";

    Command_Constructor.Clear_Dynamic_Memory();

    std::cout << "\n\n The end of the program";

    std::cout << "\n\n";

    return 0;
}
