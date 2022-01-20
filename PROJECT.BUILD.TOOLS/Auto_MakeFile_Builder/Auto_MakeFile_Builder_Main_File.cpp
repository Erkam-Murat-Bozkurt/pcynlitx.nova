

#include <iostream>
#include <cstring>
#include "Project_Files_Lister.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc< 2){

       std::cout << "\n\n usage: <exe-file> <repo dir> <repo warehouse location>";

       std::cout << "\n\n";

       exit(0);
    }


    Auto_MakeFile_Builder Make_Builder;

    Make_Builder.Receive_Repo_Dir_Path(argv[1]);

    Make_Builder.Receive_Warehouse_Path(argv[2]);

    Make_Builder.Build_Make_Files();

    std::cout << "\n The end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
