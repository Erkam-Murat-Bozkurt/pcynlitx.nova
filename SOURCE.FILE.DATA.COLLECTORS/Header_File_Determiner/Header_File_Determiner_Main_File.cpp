



#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Header_File_Determiner.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    Git_File_List_Receiver Receiver;

    Receiver.Receive_Descriptor_File_Reader(&Des_Reader);

    Receiver.Determine_Git_Repo_Info();

    char * Repo_Dir = Receiver.Get_Git_Repo_Directory();

    int index_size = Receiver.Get_Git_File_Index_Size();

    Header_File_Determiner Header_Determiner;

    Header_Determiner.Receive_Git_Data(&Receiver);

    for(int i=0;i<index_size-1;i++){

       char * git_record_path =  Receiver.Get_Git_File_Index(i);

       char * header_system_path = nullptr;

       Header_Determiner.Clear_Dynamic_Memory();

       bool is_header = Header_Determiner.Is_Header(git_record_path);

       if(is_header){

         Header_Determiner.Determine_Header_File_Name_With_Extention(git_record_path);

         std::cout << "\n Header file name:" << Header_Determiner.Get_Header_File_Name_With_Ext();
       }
    }

    std::cout << "\n\n The end of the program ";

    return 0;
}

// The Function that places the location Informations listed in below
