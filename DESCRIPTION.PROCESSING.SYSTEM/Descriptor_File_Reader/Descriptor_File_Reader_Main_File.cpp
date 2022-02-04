





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

    Descriptor_File_Reader Des_File_Reader;

    Des_File_Reader.Read_Descriptor_File(argv[1]);


    std::cout << "\n WAREHOUSE LOCATION:";

    if(Des_File_Reader.Get_Warehouse_location() != nullptr){

       std::cout << "\n ";

       std::cout << Des_File_Reader.Get_Warehouse_location();

    }
    else{

        std::cout << "\n There is no standard decleration";
    }

    std::cout << "\n\n";


    std::cout << "\n STANDART RECORD:";

    if(Des_File_Reader.Get_Standard() != nullptr){

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

          std::cout << Des_File_Reader.Get_Include_Directories()[i];
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

          std::cout << Des_File_Reader.Get_Source_File_Directories()[i];
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

           std::cout << Des_File_Reader.Get_Library_Directories()[i];
       }
    }
    else{

         std::cout << "\n There is no library directory decleration";
    }

    std::cout << "\n\n";


    std::cout << "\n LIBRARY NAMES RECORD:";

    int lib_names_num = Des_File_Reader.Get_Library_Name_Number();

    if(lib_names_num > 0){

      for(int i=0;i<lib_names_num;i++){

          std::cout << "\n ";

          std::cout << Des_File_Reader.Get_Library_Names()[i];
      }
    }
    else{

        std::cout << "\n There is no library names decleration..";
    }

    std::cout << "\n\n";


    std::cout << "\n DEBUGGING OPTION RECORD: ";

    if(Des_File_Reader.Get_Debugging_Option() != nullptr){

       std::cout << "\n ";

       std::cout << Des_File_Reader.Get_Debugging_Option();
    }
    else{

        std::cout << "\n There is no debugging opption decleration";
    }

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
