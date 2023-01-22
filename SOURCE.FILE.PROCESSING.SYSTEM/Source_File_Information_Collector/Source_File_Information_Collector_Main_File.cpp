



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Information_Collector.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Source_File_Information_Collector Information_Collector(argv[1],'w');

    Information_Collector.Collect_Make_File_Data();

    Information_Collector.Print_Header_Data();



    size_t data_size = Information_Collector.Get_Data_Size();

    Compiler_Data Data_Pointer = Information_Collector.Get_Compiler_Data(0);

    Information_Collector.Clear_Dynamic_Memory();

    return 0;
}
