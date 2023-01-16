





#include <iostream>
#include <cstring>
#include "Source_File_Determiner.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <test_file_path>";

       std::cout << "\n\n";

       exit(0);
    }

    Source_File_Determiner Source_Determiner;

    bool Is_Source_File = Source_Determiner.Is_Source_File(argv[1]);

    if(Is_Source_File){

       std::cout << "\n this is a source file..";
    }
    else{

        std::cout << "\n this is not a source file";
    }

    if(Is_Source_File){

        Source_Determiner.Determine_Source_File_Name(argv[1]);

        std::cout << "\n Source File Name:" << Source_Determiner.Get_Source_File_Name();

        std::cout << "\n Source File Name witout extenton:" << Source_Determiner.Get_File_Name_Witout_Ext();
    }

    std::cout << "\n\n";

    std::string file_path = "D:\\PCYNLITX.BUILD.TEST\\PCYNLITX.PROJECT.WINDOWS\\CLASS.DECLERATION.READER\\ClassReader\\DataBaseBuilder\\DataBaseBuilder.cpp";

    Is_Source_File = Source_Determiner.Is_Source_File(file_path);

    if(Is_Source_File){

       std::cout << "\n this is a source file..";
    }
    else{

        std::cout << "\n this is not a source file";
    }

    if(Is_Source_File){

        Source_Determiner.Determine_Source_File_Name(file_path);

        std::cout << "\n Source File Name:" << Source_Determiner.Get_Source_File_Name();

        std::cout << "\n Source File Name witout extenton:" << Source_Determiner.Get_File_Name_Witout_Ext();
    }

    std::cout << "\n\n";



    return 0;
}

// The Function that places the location Informations listed in below
