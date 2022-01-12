


#include <iostream>
#include <cstring>
#include "Build_Tools_Initializer.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <repo dir> <repo warehouse location>";

       std::cout << "\n\n";

       exit(0);
    }


    Build_Tools_Initializer Initializer;


    Initializer.Setup_Build_Tools(argv[1],argv[2]);

    std::cout << "\n The end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
