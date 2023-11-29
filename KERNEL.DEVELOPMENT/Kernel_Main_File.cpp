


#include <iostream>
#include <cstring>
#include "Kernel.hpp"


int main(int argc, char ** argv){

    if(argc< 3){

       std::cout << "\n\n usage: BuildSystem <Descriptor File Path> <operation>";

       std::cout << "\n\n";

       exit(0);
    }


    Kernel Build_System(argv[1],'w');

    if(*argv[2] == 'i'){

        std::cout << "\n\n\e[0;32mC++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED\e[0m\n";

        Build_System.Setup_Build_Tools();

        std::cout << "\n\e[0;32mTHE CONSTRUCTION COMPLATED\e[0m\n\n";
    }


    if(*argv[2] == 'e'){

        if(argc < 6){

           std::cout << "\n You must also specify the name of the executable";
           std::cout << "\n and construction strategy";
           std::cout << "\n";
           std::cout << "\n usage: BuildSystem [Descriptor File Path] [operation] \\";
           std::cout << "\n        [Source File Path] [Executable File Name] [Strategy]";

           std::cout << "\n";
           std::cout << "\n";
        }

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTION STARTED\e[0m\n";

        Build_System.Build_MakeFile(argv[3],argv[4],*argv[5]);

        std::cout << "\n";

        std::cout << "\n\e[0;32mTHE MAKEFILE CONSTRUCTED\e[0m\n\n";

    }

    std::cout << "\n";


    return 0;
}

