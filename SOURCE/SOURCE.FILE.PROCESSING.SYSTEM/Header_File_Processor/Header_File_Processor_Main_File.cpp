




#include <iostream>
#include <cstring>
#include "Project_Src_Code_Rdr.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Header_File_Processor.hpp"

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


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Receiver);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n The project source codes readed..";

    std::cin.get();


    Header_File_Processor Processor(argv[1],'w');

    Processor.Receive_Source_Code_Reader(&Code_Rd);

    for(int i=0;i<index_size-1;i++){

       std::string git_record_path =  Receiver.Get_Git_File_Index(i);

       std::string header_system_path = "";

       bool is_header = Processor.Is_Header(git_record_path);

       if(is_header){

          bool is_repo_header = Processor.Is_This_Repo_Header(git_record_path);

          if(is_repo_header){
          
             Processor.Determine_Header_File_Name_With_Extention(git_record_path);

             std::cout << "\n Header file name:" << Processor.Get_Header_File_Name_With_Ext();
          }
       }
    }

    std::cout << "\n\n The end of the program ";

    return 0;
}

// The Function that places the location Informations listed in below
