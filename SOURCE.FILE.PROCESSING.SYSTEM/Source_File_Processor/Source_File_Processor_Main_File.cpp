






#include <iostream>
#include <cstring>
#include "Source_File_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Git_File_List_Receiver.hpp"


int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path> <test_file_path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_File_List_Receiver Receiver(argv[1],'w');

    Receiver.Determine_Git_Repo_Info();

    int index_size = Receiver.Get_Git_File_Index_Size();


    Project_Src_Code_Rdr Code_Rd(argv[1],'w');

    Code_Rd.Receive_Git_Repo_Information(&Receiver);

    Code_Rd.Read_Project_Source_Code_Files();

    Source_File_Processor File_Processor;

    File_Processor.Receive_Source_Code_Reader(&Code_Rd);

    bool Is_Source_File = File_Processor.Is_Source_File(argv[2]);

    if(Is_Source_File){

       std::cout << "\n this is a source file..";
    }
    else{

        std::cout << "\n this is not a source file";
    }

    if(Is_Source_File){

        File_Processor.Determine_Source_File_Name(argv[2]);

        std::cout << "\n Source File Name:" << File_Processor.Get_Source_File_Name();

        std::cout << "\n Source File Name witout extenton:" << File_Processor.Get_File_Name_Witout_Ext();
    }

    std::cout << "\n\n";

    std::string file_path = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\CLASS.DECLERATION.READER\\ClassReader\\DataBaseBuilder\\DataBaseBuilder.cpp";

    Is_Source_File = File_Processor.Is_Source_File(file_path);

    if(Is_Source_File){

       std::cout << "\n this is a source file..";
    }
    else{

        std::cout << "\n this is not a source file";
    }

    if(Is_Source_File){

        File_Processor.Determine_Source_File_Name(file_path);

        std::cout << "\n Source File Name:" << File_Processor.Get_Source_File_Name();

        std::cout << "\n Source File Name witout extenton:" << File_Processor.Get_File_Name_Witout_Ext();
    }

    std::cout << "\n\n";



    return 0;
}

// The Function that places the location Informations listed in below
