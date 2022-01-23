
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"

int main(int argc, char ** argv){

    Make_File_Builder File_Builder;

    if(argc < 3){

       std::cout << "\n The usage: Make_File_Builder.exe <Repo Directory> ";

       std::cout << "<Git Header Path>  <Proj. Warehouse Location>";

       std::cout << "\n\n";

       exit(0);
    }

    File_Builder.Build_MakeFile(argv[1],argv[2],argv[3]);

    return 0;
}
