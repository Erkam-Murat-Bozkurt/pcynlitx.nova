

#include <iostream>
#include <string>
#include "Cpp_FileOperations.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Cpp_FileOperations File_Handler;


    File_Handler.Read_File(argv[1]);

    File_Handler.Printf();

    return 0;

}
