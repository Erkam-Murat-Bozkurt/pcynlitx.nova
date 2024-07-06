




#include <iostream>
#include <cstring>
#include "CMAKE_Build_System_Generator.hpp"
#include "CMAKE_System_Constructor.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc< 4){

       std::cout << "\n\n usage: <exe-file> <Descriptor File Path> <project-name> <version-num>";

       std::cout << "\n\n";

       exit(0);
    }

    CMAKE_Build_System_Generator BLD_System_Generator(argv[1],'w','n');

    size_t name_size = strlen(argv[2]);

    std::string file_name;

    for(size_t i=0;i<name_size;i++){

         file_name.push_back(argv[2][i]);
    }

    file_name.shrink_to_fit();

    std::string version_num;

    size_t ver_num_size = strlen(argv[3]);

    for(size_t i=0;i<ver_num_size;i++){

        version_num.push_back(argv[3][i]);
    }

    version_num.shrink_to_fit();


    BLD_System_Generator.Construct_Build_System(file_name,version_num);

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

