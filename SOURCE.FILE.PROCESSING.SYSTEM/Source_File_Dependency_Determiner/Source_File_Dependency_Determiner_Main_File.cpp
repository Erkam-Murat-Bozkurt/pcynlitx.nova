



#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Dependency_Determiner.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Project_Files_Lister.h"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Git_File_List_Writer.hpp"
#include "Git_Modification_Lister.hpp"
#include "Git_Modification_Receiver.hpp"
#include "Git_Ignoring_Files_Lister.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Determiner.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();

    size_t index_size = Data_Processor.Get_Git_File_Index_Size();


    


    char path [] ="D:\\pcynlitx.build.gui\\wxLauncher.cpp";

    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    //Dep_Determiner.Collect_Dependency_Information(path);


    //Dep_Determiner.Receive_Source_Code_Reader(&Code_Rd);

    /*

    Dep_Determiner.Collect_Dependency_Information();

    Dep_Determiner.Print_Compiler_Orders();

    Dep_Determiner.Clear_Dynamic_Memory();

    std::cout << "\n\n ---------------------------------------------------------------";


    */

    Dep_Determiner.Collect_Dependency_Information(path);

     //Dep_Determiner.Collect_Dependency_Information();



     std::vector<Compiler_Data> * ptr = Dep_Determiner.Get_Compiler_Data_Address();

     for(size_t i=0;i<ptr->size();i++){


        std::cout << " \n\n\n";
        std::cout << "\n source file name:" << ptr->at(i).source_file_name;
        std::cout << "\n object file name:" << ptr->at(i).object_file_name;
        std::cout << "\n source file path:" << ptr->at(i).source_file_path;

        size_t header_number = ptr->at(i).dependent_headers.size();

        std::cout << "\n priority:" << ptr->at(i).priority;

        std::cout << "\n header_number:" << header_number;        

        std::cout << "\n dependent headers:";

        for(size_t j=0;j<header_number;j++){

            std::cout << "\n Header: " << j << "-:" << ptr->at(i).dependent_headers.at(j);
        }
     }


    std::cout << "\n\n";

    //Dep_Determiner.Print_Dependency_List();

    std::cout << "\n The end of the program";

    return 0;
}
