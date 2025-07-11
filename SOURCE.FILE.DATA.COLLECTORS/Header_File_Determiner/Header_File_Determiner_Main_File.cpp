



#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Git_Data_Processor.hpp"
#include "Header_File_Determiner.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Git_File_List_Receiver Receiver('w');
    
    Receiver.Receive_Descriptor_File_Path(argv[1]);

    Receiver.Determine_Git_Repo_Info();
    

    std::string Repo_Dir = Receiver.Get_Git_Repo_Directory();

    int index_size = Receiver.Get_Git_File_Index_Size();



    Header_File_Determiner Header_Determiner('w');

    Header_Determiner.Receive_Descriptor_File_Path(argv[1]);


    for(int i=0;i<index_size-1;i++){

       std::string git_record_path =  Receiver.Get_Git_File_Index(i);

       std::string header_system_path = "";

       bool is_header = Header_Determiner.Is_Header(git_record_path);

       bool is_repo_header = Header_Determiner.Is_This_Repo_Header(git_record_path);

       if(is_header){

         Header_Determiner.Determine_Header_File_Name_With_Extention(git_record_path);

         std::cout << "\n Header file name:" << Header_Determiner.Get_Header_File_Name_With_Ext();
       }
    }

    std::cout << "\n\n The end of the program ";

    return 0;
}

// The Function that places the location Informations listed in below
