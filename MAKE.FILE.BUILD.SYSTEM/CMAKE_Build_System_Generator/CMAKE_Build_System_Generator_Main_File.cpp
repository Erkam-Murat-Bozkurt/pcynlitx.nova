




#include <iostream>
#include <cstring>
#include "CMAKE_Build_System_Generator.hpp"
#include "CMAKE_System_Constructor.hpp"
#include "CMAKE_Main_File_Writer.hpp"
#include "Descriptor_File_Reader.hpp"


int main(int argc, char ** argv){

    if(argc< 4){

       std::string error_message = "\n\n USAGE FOR BUILD SYSTEM CONSTRUCTION:";

       error_message += "\n\n <CMAKE_Build.exe> -bs ";

       error_message += "<Descriptor File Path> <project-name> <version-num>";

       error_message += "\n -bs: build type";

       error_message += "\n\n";

       error_message += "\n\n USAGE FOR EXECUTABLE FILE (TARGET) CONSTRUCTION:";

       error_message += "\n\n <CMAKE_Build.exe> -ef ";

       error_message += "<Descriptor File Path> <target-main-file path> <exe file name>";

       error_message += "\n -ef: build type";

       error_message += "\n\n";

       error_message += "\n\n";


       std::cout << error_message;

       exit(0);
    }




    // BUILD TYPE DETERMINATION

    size_t type_size = strlen(argv[1]);

    std::string build_type;

    for(size_t i=0;i<type_size;i++){

        build_type.push_back(argv[1][i]);
    }


    // COMMAND LINE ARGUMENTS TYPE CONVERSION

    size_t _argm3_size = strlen(argv[3]);

    std::string _argm3;

    for(size_t i=0;i<_argm3_size;i++){

          _argm3.push_back(argv[3][i]);
       }

    _argm3.shrink_to_fit();

    
    std::string _argm4;

    size_t _argm4_size = strlen(argv[4]);

    for(size_t i=0;i<_argm4_size;i++){

        _argm4.push_back(argv[4][i]);
    }

    _argm4.shrink_to_fit();




    // BUILD SYSTEM GENERATOR OBJECT CONSTRUCTION

    CMAKE_Build_System_Generator BLD_System_Generator(argv[2],'w','n');

    if(build_type == "-bs"){

       BLD_System_Generator.Construct_Build_System(_argm3,_argm4);
    }


    if(build_type == "-ef"){

        BLD_System_Generator.Construct_Exe_Build_System(_argm3,_argm4);

    }

    std::cout << "\n\nThe end of the program ..";

    std::cout << "\n\n";

    return 0;
}

