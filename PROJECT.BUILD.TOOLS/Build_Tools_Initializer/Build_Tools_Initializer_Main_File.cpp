


#include <iostream>
#include <cstring>
#include "Build_Tools_Initializer.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Build_Tools_Initializer Initializer(argv[1],'w');

    Initializer.Setup_Build_Tools();

    std::cout << "\n";

    std::cout << "\n\e[1;32mTHE CONSTRUCTION COMPLATED\e[0m\n\n";

    return 0;
}

