

#include <iostream>
#include <cstring>
#include "Repo_Dir_Determiner.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    Repo_Dir_Determiner Dir_Determiner;

    Dir_Determiner.Determine_Repo_Dir();

    std::cout << "\n Repo Directory: " << Dir_Determiner.Get_Repo_Dir() << std::endl;

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
