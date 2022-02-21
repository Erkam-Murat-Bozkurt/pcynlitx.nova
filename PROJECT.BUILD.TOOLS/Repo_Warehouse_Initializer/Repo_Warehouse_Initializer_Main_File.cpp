

#include <iostream>
#include <cstring>
#include "Repo_Warehouse_Initializer.h"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc <2){

       std::cout << "\n usage: Repo_Warehouse_Initializer.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Repo_Warehouse_Initializer Initializer;

    Initializer.Build_Project_Warehouse(argv[1]);

    std::cout << "\n\n Project Header Warehouse Constructed ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
