






#include <iostream>
#include <cstring>
#include "Source_File_Data_Collector.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <test_file_path>";

       std::cout << "\n\n";

       exit(0);
    }

    Source_File_Data_Collector Data_Collector;

    Data_Collector.Receive_Source_File_Data(argv[1]);

    int Header_File_Number = Data_Collector.Get_Included_File_Number();

    if(Header_File_Number > 0){

       for(int i=0;i<Header_File_Number;i++){

           std::cout << "\n The header file:" << Data_Collector.Get_Include_File_Name(i);
       }
    }

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
