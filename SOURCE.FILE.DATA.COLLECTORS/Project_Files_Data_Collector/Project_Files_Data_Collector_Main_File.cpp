

#include <iostream>
#include <cstring>
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"
#include "Project_Files_Data_Collector.hpp"

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

    int index_size = Receiver.Get_Git_File_Index_Size();

    Project_Files_Data_Collector Data_Collector;

    char repo_dir [] = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS";

    for(int i=0;i<index_size;i++){

        char * file_record = Receiver.Get_Git_File_Index(i);

        std::cout << "\n Git Record File -"  << i << " :" << file_record;

        char * file_system_path = nullptr;

        Data_Collector.Determine_File_Exact_Path(&file_system_path,repo_dir,file_record,'w');

        char * upper_directory_path = nullptr;

        Data_Collector.Extract_Upper_Directory_Path(&upper_directory_path,file_system_path,'w');

        char * file_name = nullptr;

        Data_Collector.Determine_File_Name(&file_name,file_system_path);

        char * File_Name_With_Ext = nullptr;

        Data_Collector.Determine_Source_File_Name_With_Ext(&File_Name_With_Ext,file_name);

        std::cout << "\n file_system_path:" << file_system_path;

        std::cout << "\n upper_directory_path:" << upper_directory_path;

        std::cout << "\n file_name:" << file_name;

        std::cout << "\n File_Name_With_Ext:" << File_Name_With_Ext;

        std::cin.get();

        delete [] file_system_path;

        delete [] upper_directory_path;

        delete [] file_name;
    }

    std::cout << "\n Press eny key..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}
