


#include <iostream>
#include <cstring>
#include <vector>
#include "Executable_MakeFile_ComConstructor.hpp"
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Executable_MakeFile_ComConstructor.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    char path [] = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\KERNEL.DEVELOPMENT\\Kernel\\Kernel_Main_File.cpp";

    char Exe_Name [] = "Kernel.exe";

    Executable_MakeFile_ComConstructor Command_Constructor(argv[1],'w');



    Command_Constructor.Receive_ExeFileName(Exe_Name);

    Command_Constructor.Construct_Compiler_Commands(path);
    


    std::string Compiler_System_Command = Command_Constructor.Get_Compiler_System_Command();

    std::cout << "\nCompiler_System_Command:" << std::endl;
    
    std::cout << Compiler_System_Command;

    std::cout << "\n\n";

    Command_Constructor.Clear_Dynamic_Memory();

    std::cout << "\n\n The end of the program";

    std::cout << "\n\n";

    return 0;
}
