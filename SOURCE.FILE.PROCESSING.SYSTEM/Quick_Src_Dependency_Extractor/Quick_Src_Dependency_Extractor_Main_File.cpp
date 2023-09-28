




#include <iostream>
#include <cstring>
#include <vector>
#include "Quick_Src_Dependency_Extractor.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Project_Files_Lister.h"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: Executable_File <Descriptor File Path> <Target File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();

    std::cout << "\n Descriptor File Readed";

    Git_Data_Processor Git_Data_Proc('w');

    Git_Data_Proc.Receive_Descriptor_File_Path(argv[1]);

    Git_Data_Proc.Write_Git_Repo_List_File();

    Git_Data_Proc.Determine_Git_Repo_Info();


    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();


    std::cout << "\n The project source codes readed..";

    Quick_Src_Dependency_Extractor Quick_Extractor('w');

    Quick_Extractor.Receive_Descriptor_File_Reader(&Des_Reader);

    Quick_Extractor.Receive_Source_Code_Reader(&Code_Rd);

    Quick_Extractor.Receive_Git_Data_Processor(&Git_Data_Proc);


    Quick_Extractor.Extract_Dependency_Search_Data(argv[2]);



    const std::vector<Search_Data> * vec_Pointer = Quick_Extractor.Get_Dependency_Search_Data();

    size_t data_size = vec_Pointer->size();


    std::cout << "\n data_size:" << data_size;

    for(size_t i=0;i<data_size;i++){

        Search_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Directory and File     :" << temp.dir_file_comb << "#";
        std::cout << "\n Header name            :" << temp.name << "#";
        std::cout << "\n Header system path     :" << temp.path << "#";

        std::cout << "\n\n\n";
    }
    
    std::cout << "\n\n";
    std::cout << "\n THE EXTERNAL HEADER FILES FOR THE ROOT PATH:";
    std::cout << "\n\n";

    const std::vector<std::string> * external_headers = Quick_Extractor.Get_Root_File_External_Headers();

    for(size_t i=0;i<external_headers->size();i++){

        std::cout << "\n External Header[" << i << "]:" << external_headers->at(i);
    }

    Quick_Extractor.Clear_Dynamic_Memory();

    std::cout << "\n\n THE END OF THE PROGRAM \n\n";



    return 0;
}
