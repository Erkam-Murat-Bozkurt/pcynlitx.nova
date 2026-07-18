



#include <iostream>
#include <cstring>
#include "CMAKE_System_Constructor.hpp"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc< 4){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path> <project_name> <version_num>";

       std::cout << "\n\n";

       exit(0);
    }

    std::cout << "\n\e[1;32mDependency information have been determined..\e[0m\n";

    CMAKE_System_Constructor Make_Builder(argv[1],'w','n');

    Make_Builder.Build_Make_Files(argv[2],argv[3]);

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
