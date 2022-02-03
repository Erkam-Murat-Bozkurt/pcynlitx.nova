




#include <iostream>
#include <cstring>
#include "Descriptor_File_Data_Collector.hpp"


int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << "\n usage: Descriptor_File_Data_Collector.exe <path>";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Data_Collector Data_Collector;

    Data_Collector.Collect_Descriptor_File_Data(argv[1]);


    std::cout << "\n STANDART RECORD:";

    std::cout << "\n Standart record area start:" << Data_Collector.Get_Standard_Record_Area(0);

    std::cout << "\n Standart record area end:"   << Data_Collector.Get_Standard_Record_Area(1);

    std::cout << "\n\n";



    std::cout << "\n INCLUDE DIRECTORY RECORD:";

    std::cout << "\n Include directories record area start:" << Data_Collector.Get_Include_Directories_Record_Area(0);

    std::cout << "\n Include directories record area end:"   << Data_Collector.Get_Include_Directories_Record_Area(1);

    std::cout << "\n\n";


    std::cout << "\n SOURCE FILE DIRECTORIES RECORD:";

    std::cout << "\n Source File Directories record area start:" << Data_Collector.Get_Source_File_Directories_Record_Area(0);

    std::cout << "\n Source File Directories record area end:"   << Data_Collector.Get_Source_File_Directories_Record_Area(1);

    std::cout << "\n\n";





    std::cout << "\n LIBRARY DIRECTORIES RECORD:";

    std::cout << "\n Library directories record area start:" << Data_Collector.Get_Library_Directories_Record_Area(0);

    std::cout << "\n Library directories record area end:"   << Data_Collector.Get_Library_Directories_Record_Area(1);

    std::cout << "\n\n";



    std::cout << "\n LIBRARY NAMES RECORD:";

    std::cout << "\n Library names record area start:" << Data_Collector.Get_Library_Names_Record_Area(0);

    std::cout << "\n Library names record area end:"   << Data_Collector.Get_Library_Names_Record_Area(1);

    std::cout << "\n\n";


    std::cout << "\n DEBUGGING OPTION RECORD:";

    std::cout << "\n Debugging options record area start:" << Data_Collector.Get_Debugging_Option_Record_Area(0);

    std::cout << "\n Debugging options record area end:"   << Data_Collector.Get_Debugging_Option_Record_Area(1);

    std::cout << "\n\n";


    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
