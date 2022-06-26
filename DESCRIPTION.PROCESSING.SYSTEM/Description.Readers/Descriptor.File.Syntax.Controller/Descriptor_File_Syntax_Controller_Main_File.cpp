





#include <iostream>
#include <cstring>
#include "Descriptor_File_Syntax_Controller.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << "\n usage: Descriptor_File_Syntax_Controller.exe <path>";

       std::cout << "\n\n";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Syntax_Controller Syntax_Controller;

    Syntax_Controller.Control_Descriptor_File_Syntax(argv[1]);

    std::cout << "\n There is no any syntax error.";

    std::cout << "\n\n";

    std::cout << "\n\n";

    return 0;
}
