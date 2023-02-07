



#include <iostream>
#include <cstring>
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_File_List_Receiver Receiver(argv[1],'w');

    Receiver.Determine_Git_Repo_Info();

    int index_size = Receiver.Get_Git_File_Index_Size();

    for(int i=0;i<index_size;i++){

        std::cout << "\n";

        std::cout << "\n Git Record File -"  << i << " :" << Receiver.Get_Git_File_Index(i);

        std::cout << "\n System path     -"  << i << " :" << Receiver.Get_File_System_Path(i);

        std::cout << "\n";
    }

    std::cout << "\n Press eny key..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}
