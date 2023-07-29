


#include <iostream>
#include <cstring>
#include "Git_Modification_Receiver.hpp"


int main(int argc, char ** argv){

    if(argc <2){

       std::cout << "\n usage: Git_Modification_Receiver.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_Modification_Receiver Receiver('w');

    Receiver.Receive_Descriptor_File_Path(argv[1]);

    // The project warehouse will be builded

    Receiver.Receive_Git_Modifications();

    std::cout << "\n Updated file informations determined  ..";

    std::cout << "\n\n";

    std::vector<std::string> * ptr = Receiver.Get_File_System_Path_Address();

    std::vector<std::string>::iterator it;

    for(auto it=ptr->begin();it!=ptr->end();it++){
    
       std::cout << "\n " << *it;
    }

    std::cout << "\n\n";

    std::vector<std::string> * ptr_hdr = Receiver.Get_Updated_Header_Files();

    std::vector<std::string> * ptr_src = Receiver.Get_Updated_Source_Files();


    std::cout << "\n\n UPDATED HEADER FILES:";
    std::cout << "\n";

    for(auto it=ptr_hdr->begin();it!=ptr_hdr->end();it++){
    
       std::cout << "\n " << *it;
    }

    std::cout << "\n\n";


    std::cout << "\n\n UPDATED SOURCE FILES:";
    std::cout << "\n";

    for(auto it=ptr_src->begin();it!=ptr_src->end();it++){
    
       std::cout << "\n " << *it;
    }

    std::cout << "\n\n";



    return 0;
}
