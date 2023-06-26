


#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Script_Data_Processor.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_File_List_Receiver Receiver(argv[1],'w');

    Receiver.Determine_Git_Repo_Info();


    Script_Data_Processor Srt_Data_Processor(argv[1],'w');

    Srt_Data_Processor.Receive_Git_File_List_Info(&Receiver);

    Srt_Data_Processor.Process_Script_Data();

    char File_Name [] ="Kernel.cpp";

    Script_Data Data = Srt_Data_Processor.Get_SrcFile_Script_Data(File_Name);

    std::cout << "\n object_file_name:" << Data.object_file_name;
    std::cout << "\n object_file_path:" << Data.object_file_path;
    std::cout << "\n source_file_name:" << Data.source_file_name;
    std::cout << "\n source_file_dir:"  << Data.source_file_dir;
    std::cout << "\n source_file_git_record_dir:" << Data.source_file_git_record_dir;
    std::cout << "\n make_file_name:" << Data.make_file_name;
    std::cout << "\n warehouse_path:" << Data.warehouse_path;

    std::cout << "\n Dependency:" << Data.dependency;

    std::cout << "\n\n";

    return 0;
}
