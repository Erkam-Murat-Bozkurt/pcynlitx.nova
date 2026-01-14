



#include <iostream>
#include <cstring>
#include "Directory_Tree_Size_Determiner.h"

int main(int argc, char ** argv){

    Directory_Tree_Size_Determiner Size_Determiner;

    Size_Determiner.Determine_Directory_Tree_Size(argv[1]);

    int dir_num = Size_Determiner.Get_Directory_Tree_Size();

    std::cout << "\n dir_num:" << dir_num;

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
