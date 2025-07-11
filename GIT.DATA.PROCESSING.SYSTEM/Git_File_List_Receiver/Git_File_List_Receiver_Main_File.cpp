



#include <iostream>
#include <cstring>
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv)
{
    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_File_List_Receiver Receiver('w');

    Receiver.Receive_Descriptor_File_Path(argv[1]);

    Receiver.Determine_Git_Repo_Info();

    size_t index_size = Receiver.Get_Git_File_Index_Size();

    for(size_t i=0;i<index_size;i++){

        std::cout << "\n";

        std::cout << "\n Git Record File -"  << i << " :" << Receiver.Get_Git_File_Index(i);

        std::cout << "\n System path     -"  << i << " :" << Receiver.Get_File_System_Path(i);

        std::cout << "\n Git Record dir  -"  << i << " :" << Receiver.Get_Git_Record_Directory(i);

        std::cout << "\n File Name  -"       << i << " :" << Receiver.Get_File_Name(i);

        std::cout << "\n";
    }

    std::cout << "\n Press eny key..";

    std::cin.get();

    return 0;
}
