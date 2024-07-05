




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

    CMAKE_Build_System_Generator BLD_System_Gnerator(argv[1],'w','n');

    BLD_System_Gnerator.Construct_Build_System();

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

