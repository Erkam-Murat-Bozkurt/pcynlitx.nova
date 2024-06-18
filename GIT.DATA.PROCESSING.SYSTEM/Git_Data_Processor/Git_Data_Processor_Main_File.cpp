






#include <iostream>
#include <cstring>
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_Modification_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();

    for(size_t i=0;i<index_size;i++){

        std::cout << "\n";

        std::cout << "\n Git Record File -"  << i << " :" << Data_Processor.Get_Git_File_Index(i);

        std::cout << "\n System path     -"  << i << " :" << Data_Processor.Get_File_System_Path(i);

        std::cout << "\n Git Record dir  -"  << i << " :" << Data_Processor.Get_Git_Record_Directory(i);

        std::cout << "\n File Name  -"       << i << " :" << Data_Processor.Get_File_Name(i);

        std::cout << "\n";
    }

    std::cout << "\n\n";


    std::vector<std::string> *  dir_list =  Data_Processor.Get_Git_Record_Directory_Address();

    std::cout << "\n Directory List Determined";

    std::cin.get();

    for(size_t i=0;i<dir_list->size();i++){

        std::cout << "\n dir_list[" << i << "]:" << dir_list->at(i);
    }

    //Data_Processor.Set_Git_Ignoring_Files();

    //Data_Processor.Write_Git_Modification_File();

    //Data_Processor.Receive_Git_Modifications();



    return 0;
}
