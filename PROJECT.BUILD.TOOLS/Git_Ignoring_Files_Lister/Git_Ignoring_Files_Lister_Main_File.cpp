






#include <iostream>
#include <cstring>
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_Ignoring_Files_Lister Lister(argv[1],'w');

    Lister.Write_Ignoring_File_List();

    std::cout << "\n The ignoring files setted..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}
