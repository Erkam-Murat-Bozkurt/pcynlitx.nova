

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
    

    std::string file_path = "";

    size_t path_size = strlen(argv[2]);

    for(size_t i=0;i<path_size;i++){

         file_path.append(1,argv[2][i]);
    }

    Source_File_Data_Collector Data_Collector(argv[1],'w');

    Data_Collector.Receive_Source_File_Data(file_path);

    int Header_File_Number = Data_Collector.Get_Included_File_Number();

    if(Header_File_Number > 0){

       for(int i=0;i<Header_File_Number;i++){

           std::cout << "\n The header file - " << i << ": "

           << Data_Collector.Get_Include_File_Name(i);


          std::cout << "\n The header file directory- " << i << ": "

          << Data_Collector.Get_Include_File_Directory(i);


          std::cout << "\n The header file git record directory - " << i << ": "

          << Data_Collector.Get_Include_File_Git_Record_Directory(i);


          std::cout << "\n The header file git record path - " << i << ": "

          << Data_Collector.Get_Include_File_Git_Record_Path(i);
       }
    }

    std::cout << "\n\n";

    return 0;
}
