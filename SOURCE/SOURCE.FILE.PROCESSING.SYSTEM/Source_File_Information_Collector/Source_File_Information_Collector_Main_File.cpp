



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Information_Collector.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Information_Collector.exe <Descriptor File Path> ";

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

    int index_size = Git_Data_Proc.Get_Git_File_Index_Size();

    std::cout << "\n index_size:" << index_size;


    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();



    std::cout << "\n The project source codes readed..";

    Source_File_Information_Collector Information_Collector('w');

    Information_Collector.Receive_Descriptor_File_Reader(&Des_Reader);

    Information_Collector.Receive_Source_Code_Reader(&Code_Rd);

    Information_Collector.Receive_Git_Data_Processor(&Git_Data_Proc);

    Information_Collector.Extract_Dependency_Data();

    size_t data_size = Information_Collector.Get_Dependency_Data_Size();

    std::vector<Source_File_Data> * vec_Pointer = Information_Collector.Get_Source_File_Data_Address();

    std::cout << "\n data_size:" << data_size;

    for(size_t i=0;i<data_size;i++){

        Source_File_Data temp = (*vec_Pointer).at(i);

        std::cout << "\n Source File Name       :" << temp.source_file_name;
        std::cout << "\n Header system path     :" << temp.system_path;

        std::cout << "\n\n\n";
    }
    
    Information_Collector.Clear_Dynamic_Memory();

    return 0;
}
