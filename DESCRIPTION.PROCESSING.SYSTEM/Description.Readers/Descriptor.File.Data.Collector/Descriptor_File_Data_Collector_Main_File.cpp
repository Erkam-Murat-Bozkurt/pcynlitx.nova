




#include <iostream>
#include <cstring>
#include "Descriptor_File_Data_Collector.hpp"


int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << "\n usage: Descriptor_File_Data_Collector.exe <path>";

       std::cout << "\n\n";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Data_Collector Data_Collector;

    Data_Collector.Collect_Descriptor_File_Data(argv[1]);

    std::cout << "\n ROOT DIRECTORY LOCATION:";

    std::cout << "\n Root directory record area start:" << Data_Collector.Get_Root_Directory_Record_Area(0);

    std::cout << "\n Root directory record area end:"   << Data_Collector.Get_Root_Directory_Record_Area(1);

    std::cout << "\n\n";


    std::cout << "\n PROJECT WAREHOUSE LOCATION:";

    std::cout << "\n Warehouse record area start:" << Data_Collector.Get_Warehouse_Location_Record_Area(0);

    std::cout << "\n Warehouse record area end:"   << Data_Collector.Get_Warehouse_Location_Record_Area(1);

    std::cout << "\n\n";


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

    std::cout << "\n LIBRARY FILES RECORD:";

    std::cout << "\n Library files record area start:" << Data_Collector.Get_Library_Files_Record_Area(0);

    std::cout << "\n Library files record area end:"   << Data_Collector.Get_Library_Files_Record_Area(1);

    std::cout << "\n\n";



    std::cout << "\n OPTIONS RECORD:";

    std::cout << "\n Options record area start:" << Data_Collector.Get_Options_Record_Area(0);

    std::cout << "\n Options record area end:"   << Data_Collector.Get_Options_Record_Area(1);

    std::cout << "\n\n";


    std::cout << "\n MAIN FILE NAME RECORD:";

    std::cout << "\n Main File name record area start:" << Data_Collector.Get_Main_File_Name_Record_Area(0);

    std::cout << "\n Main File name record area end:"   << Data_Collector.Get_Main_File_Name_Record_Area(1);

    std::cout << "\n\n";



    std::cout << "\n EXECUTABLE FILE NAME RECORD:";

    std::cout << "\n Executable File name record area start:" << Data_Collector.Get_Executable_File_Name_Record_Area(0);

    std::cout << "\n Executable File name record area end:"   << Data_Collector.Get_Executable_File_Name_Record_Area(1);

    std::cout << "\n\n";

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
