


#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"
#include "Script_Data_Processor.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n usage: Script_Data_Processor.exe <descriptor file path>";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_File_Reader;

    Des_File_Reader.Read_Descriptor_File(argv[1]);

    Script_Data_Processor Srt_Data_Processor;

    Srt_Data_Processor.Process_Script_Data(&Des_File_Reader);

    char File_Name [] ="Kernel";

    Script_Data Data = Srt_Data_Processor.Get_SrcFile_Script_Data(File_Name);

    int head_num = Data.included_header_num;

    for(int i=0;i<head_num;i++){

        std::cout << "\n Header name:" << Data.header_file_names[i];

        std::cout << "\n Header file git location:" << Data.header_files_git_dir[i];
    }

    std::cout << "\n Dependency:" << Data.dependency;

    std::cout << "\n\n";

    return 0;
}
