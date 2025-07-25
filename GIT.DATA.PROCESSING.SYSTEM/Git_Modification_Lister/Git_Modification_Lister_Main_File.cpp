





#include <iostream>
#include <cstring>
#include "Git_Modification_Lister.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_Modification_Lister Lister('w');

    Lister.Receive_Descriptor_File_Path(argv[1]);

    Lister.Write_Git_Modification_File();

    std::cout << "\n Modification file list constructed..";

    std::cout << "\n\n";

    return 0;
}
