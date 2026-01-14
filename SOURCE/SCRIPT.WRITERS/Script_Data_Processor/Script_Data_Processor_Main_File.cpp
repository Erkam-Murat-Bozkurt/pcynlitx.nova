


#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Processor.hpp"
#include "Git_Data_Processor.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Script_Data_Processor.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }



    Descriptor_File_Reader Des_File_Reader('w');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_File_Reader.Read_Descriptor_File();



    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information();



    Script_Data_Processor Srt_Data_Processor('w');

    Srt_Data_Processor.Receive_Git_Data_Processor(&Data_Processor);

    Srt_Data_Processor.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Srt_Data_Processor.Receive_Source_File_Dependency_Determiner(&Dep_Determiner);

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
