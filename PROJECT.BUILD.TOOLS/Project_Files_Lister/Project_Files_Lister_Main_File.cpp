


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

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    Project_Files_Lister Dir_Lister;

    Dir_Lister.Determine_Git_Repo_Info(&Des_Reader);

    int src_file_num = Dir_Lister.Get_Source_File_Number();

    for(int i=0;i<src_file_num;i++){

        std::cout << "\n Source file directory (system)      :";

        std::cout << "\n " <<  Dir_Lister.Get_Source_File_Directory(i);

        std::cout << "\n";

        std::cout << "\n Source file directory (git record)  :";

        std::cout << "\n " << Dir_Lister.Get_Source_File_Git_Record_Path(i);

        std::cout << "\n";


        std::cout << "\n Source file path (system)           :";

        std::cout << "\n " << Dir_Lister.Get_Source_File_System_Path(i);

        std::cout << "\n";


        std::cout << "\n Source file name (without file ext) :";

        std::cout << "\n " << Dir_Lister.Get_Source_File_Name(i);

        std::cout << "\n";


        std::cout << "\n Source file  name (with file ext)  :";

        std::cout << "\n " << Dir_Lister.Get_Source_File_Name_With_Ext(i);

        std::cout << "\n";


        int src_head_num = Dir_Lister.Get_Source_File_Include_File_Number(i);

        for(int k=0;k<src_head_num;k++){

            std::cout << "\n Included header file:" <<

            Dir_Lister.Get_Source_File_Header(i,k);

            std::cout << "\n Included header file Directory:" <<

            Dir_Lister.Get_Source_File_Header_Directory(i,k);

            std::cout << "\n Included header file system path:" <<

            Dir_Lister.Get_Source_File_Header_System_Path(i,k);
        }

        std::cout << "\n\n\n\n";

    }


    int ind_head_num = Dir_Lister.Get_Indenpendent_Header_Files_Number();

    for(int i=0;i<ind_head_num;i++){

        std::cout << "\n Independen header file - " << i << ":"

        << Dir_Lister.Get_Independent_Header_File(i);
    }

    std::cout << "\n\n";

    int Header_System_Path_Number = Dir_Lister.Get_Header_System_Paths_Number();

    for(int i=0;i<Header_System_Path_Number;i++){

        std::cout << "\n Header Path - " << i << ": "  << Dir_Lister.Get_Header_File_System_Path(i);
    }

    std::cout << "\n Press eny key..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
