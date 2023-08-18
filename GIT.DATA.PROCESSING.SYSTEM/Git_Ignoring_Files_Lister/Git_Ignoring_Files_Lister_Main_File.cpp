






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


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();



    Git_Ignoring_Files_Lister Lister('w');

    Lister.Receive_Descriptor_File_Reader(&Des_Reader);

    Lister.Write_Ignoring_File_List();

    std::cout << "\n The ignoring files setted..";

    std::cout << "\n\n";

    return 0;
}
