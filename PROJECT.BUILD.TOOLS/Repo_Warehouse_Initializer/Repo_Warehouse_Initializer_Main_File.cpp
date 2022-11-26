

#include <iostream>
#include <cstring>
#include "Repo_Warehouse_Initializer.h"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc <3){

       std::cout << "\n usage: Repo_Warehouse_Initializer.exe <descriptor file path> <option>";

       std::cout << "\n\n";

       exit(0);
    }

    Repo_Warehouse_Initializer Initializer;

    if(argv[2][0] == 'b'){

       // The project warehouse will be builded

       Initializer.Build_Project_Warehouse(argv[1]);

       std::cout << "\n Project Warehouse Constructed ..";

       std::cout << "\n\n";

    }
    else{

          // The project warehouse headers will be updated

          if(argv[2][0] == 'u'){

              Initializer.Update_Warehaouse_Headers(argv[1]);
          }

          std::cout << "\n Project Header Files Updated ..";

          std::cout << "\n\n";

    }


    return 0;
}
