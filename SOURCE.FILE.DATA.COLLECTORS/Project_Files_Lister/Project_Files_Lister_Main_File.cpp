


#include <iostream>
#include <cstring>
#include "Project_Files_Lister.h"
#include "Descriptor_File_Reader.hpp"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();





    Project_Files_Lister Dir_Lister('w');

    Dir_Lister.Receive_Git_Data_Processor(&Data_Processor);

    Dir_Lister.Determine_Git_Repo_Info();

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    std::cout << "\n src_file_num:" << src_file_num;

    std::cin.get();

    std::cout << "\n";

    for(int i=0;i<src_file_num;i++){

        std::cout << "\n\n";

        std::cout << "\n Source file name (without file ext) -" << i << " ";

        std::cout << "\n " << Dir_Lister.Get_Source_File_Name(i);

        std::cout << "\n";

        std::cout << "\n Class header file name -" << i << " " ;

        if(!Dir_Lister.Get_Class_File_Header_Name(i).empty()){

           std::cout <<  Dir_Lister.Get_Class_File_Header_Name(i);
        }
        else{

             std::cout << "\n Class header file name does not exist";
        }

        std::cout << "\n";

    }



    int ind_head_num = Dir_Lister.Get_Indenpendent_Header_Files_Number();

    std::cout << "\n ind_head_num:" << ind_head_num;

    std::cin.get();

    for(int i=0;i<ind_head_num;i++){

        std::cout << "\n Independen header file - " << i << ":"

        << Dir_Lister.Get_Independent_Header_File(i);
    }

    std::cout << "\n\n";


    std::cout << "\n Press eny key..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}
