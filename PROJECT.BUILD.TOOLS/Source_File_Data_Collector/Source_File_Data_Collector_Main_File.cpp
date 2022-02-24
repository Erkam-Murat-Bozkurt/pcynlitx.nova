






#include <iostream>
#include <cstring>
#include "Git_File_List_Receiver.hpp"
#include "Source_File_Data_Collector.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path> <Source File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    Git_File_List_Receiver Git_Receiver;

    Git_Receiver.Receive_Descriptor_File_Reader(&Des_Reader);

    Git_Receiver.Determine_Git_Repo_Info();

    Source_File_Data_Collector Data_Collector;

    Data_Collector.Receive_Source_File_Data(&Git_Receiver,argv[2]);

    int Header_File_Number = Data_Collector.Get_Included_File_Number();

    if(Header_File_Number > 0){

       for(int i=0;i<Header_File_Number;i++){

           std::cout << "\n The header file - " << i << ": "

           << Data_Collector.Get_Include_File_Name(i);

          std::cout << "\n The header file - " << i << ": "

          << Data_Collector.Get_Include_File_Directory(i);
       }
    }

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
