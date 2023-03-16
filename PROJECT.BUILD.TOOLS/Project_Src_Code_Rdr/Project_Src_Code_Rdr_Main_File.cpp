




#include <iostream>
#include <cstring>
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

void print_file(std::vector<std::string> * ptr);

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


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Receiver);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n THE COMPUTATIONS COMPLATED";

    std::cin.get();

    size_t src_file_num = Code_Rd.Get_Project_Files_Number();

    for(size_t i=0;i<src_file_num;i++){
    
       std::vector<std::string> * src_code = Code_Rd.Get_File_Content(i);

       std::string path = Code_Rd.Get_File_Path(i);

       std::cout << "\n\n ";

       std::cout << "\n THE SOURCE CODE FOR FILE PATH:" ;
       
       std::cout << "\n " << path;

       print_file(src_code);
    }

    std::cout << "\n\n";

    Code_Rd.Clear_Object_Memory();

    return 0;
}


void print_file(std::vector<std::string> * ptr){

     size_t vec_size = ptr->size();

     for(size_t i=0;i<vec_size;i++){
     
         std::string line = ptr->at(i);

         std::cout << line;
     }
}