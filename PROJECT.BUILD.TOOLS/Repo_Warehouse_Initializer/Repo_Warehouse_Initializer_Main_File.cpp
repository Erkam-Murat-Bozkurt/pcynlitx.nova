

#include <iostream>
#include <cstring>
#include "Repo_Warehouse_Initializer.h"


int main(int argc, char ** argv)
{

    if(argc <2){

       std::cout << "\n usage: Repo_Warehouse_Initializer.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    Data_Processor.Set_Git_Ignoring_Files();

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();



    Repo_Warehouse_Initializer Initializer(argv[1],'w');

    Initializer.Receive_Git_Data_Processor(&Data_Processor);

    Initializer.Receive_Descriptor_File_Reader(&Des_Reader);

    Initializer.Build_Project_Warehouse();

    std::cout << "\nProject Warehouse Constructed ..";

    std::cout << "\n\n";

    Initializer.Clear_Dynamic_Memory();

    Data_Processor.Clear_Dynamic_Memory();

    return 0;
}
