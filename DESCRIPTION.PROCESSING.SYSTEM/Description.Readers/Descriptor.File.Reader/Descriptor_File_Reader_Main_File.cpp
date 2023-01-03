


#include <iostream>
#include <cstring>
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << "\n usage: Descriptor_File_Reader.exe <path>";

       std::cout << "\n\n";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_File_Reader(argv[1]);    

    Des_File_Reader.Read_Descriptor_File();



    std::cout << "\n ROOT DIRECTORY LOCATION:";

    if(Des_File_Reader.Get_Repo_Directory_Location() != ""){

       std::cout << "\n ";

       std::cout << Des_File_Reader.Get_Repo_Directory_Location();

    }
    else{

            std::cout << "\n There is no root directory decleration";
    }

    std::cout << "\n\n";


    std::cout << "\n WAREHOUSE LOCATION:";

    if(Des_File_Reader.Get_Warehouse_Location() != ""){

       std::cout << "\n ";

       std::cout << Des_File_Reader.Get_Warehouse_Location();

    }
    else{

        std::cout << "\n There is no standard decleration";
    }

    std::cout << "\n\n";


    std::cout << "\n STANDART RECORD:";

    if(Des_File_Reader.Get_Standard() != ""){

       std::cout << "\n Standart record:" << Des_File_Reader.Get_Standard();

    }
    else{

        std::cout << "\n There is no standard decleration";
    }

    std::cout << "\n\n";



    std::cout << "\n INCLUDE DIRECTORY RECORD:";

    int include_dir_num = Des_File_Reader.Get_Include_Directory_Number();

    if(include_dir_num > 0){

       for(int i=0;i<include_dir_num;i++){

          std::cout << "\n ";

          std::cout << Des_File_Reader.Get_Include_Directory(i);
       }
    }
    else{

         std::cout << "\n There is no include directory decleration ";
    }

    std::cout << "\n\n";




    std::cout << "\n SOURCE FILE DIRECTORIES RECORD:";

    int source_dir_num = Des_File_Reader.Get_Source_File_Directory_Number();

    if(source_dir_num > 0){

       for(int i=0;i<source_dir_num;i++){

          std::cout << "\n ";

          std::cout << Des_File_Reader.Get_Source_File_Directory(i);
       }
    }
    else{

        std::cout << "\n There is no source file directory decleration";
    }


    std::cout << "\n\n";



    std::cout << "\n LIBRARY DIRECTORIES RECORD:";

    int lib_dir_num = Des_File_Reader.Get_Library_Directory_Number();


    if(lib_dir_num > 0){

       for(int i=0;i<lib_dir_num;i++){

           std::cout << "\n ";

           std::cout << Des_File_Reader.Get_Library_Directory(i);
       }
    }
    else{

         std::cout << "\n There is no library directory decleration";
    }

    std::cout << "\n\n";

    std::cout << "\n LIBRARY-FILES RECORD:";

    int lib_files_num = Des_File_Reader.Get_Library_Files_Number();


    if(lib_files_num > 0){

       for(int i=0;i<lib_files_num;i++){

           std::cout << "\n ";

           std::cout << Des_File_Reader.Get_Library_File(i);
       }
    }
    else{

         std::cout << "\n There is no library directory decleration";
    }

    std::cout << "\n\n";

    std::cout << "\n OPTIONS RECORD: ";

    if(Des_File_Reader.Get_Options() != ""){

       std::cout << "\n ";

       std::cout << Des_File_Reader.Get_Options();
    }
    else{

        std::cout << "\n There is no debugging opption decleration";
    }

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
