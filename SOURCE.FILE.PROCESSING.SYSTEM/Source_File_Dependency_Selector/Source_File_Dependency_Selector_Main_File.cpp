




#include <iostream>
#include <cstring>
#include <vector>
#include <stdlib.h>
#include "Source_File_Dependency_Selector.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Dependency_Selector.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }



    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Git_Data_Proc('w');

    Git_Data_Proc.Receive_Descriptor_File_Path(argv[1]);

    Git_Data_Proc.Write_Git_Repo_List_File();

    Git_Data_Proc.Determine_Git_Repo_Info();

    int index_size = Git_Data_Proc.Get_Git_File_Index_Size();




    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();



    Source_File_Dependency_Selector Dep_Selector('w');

    if(index_size > 0){

      Dep_Selector.Receive_Source_Code_Reader(&Code_Rd);

      Dep_Selector.Receive_Git_Data_Processor(&Git_Data_Proc);

      Dep_Selector.Determine_Source_File_Dependencies();

      Dep_Selector.Print_Dependency_List();

      std::cout << "\n Dependency size:" << Dep_Selector.Get_Dependency_List_Size();
    }


    /*
    char path [] =  "D:\\pcynlitx.build.gui.new\\wxLauncher.cpp";


    std::cout << "\n\n";
    std::cout << "\n\n ----------------------------------------------------";
    std::cout << "\n Dependency determination for a single file ..";
    std::cin.get();
    */


    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
