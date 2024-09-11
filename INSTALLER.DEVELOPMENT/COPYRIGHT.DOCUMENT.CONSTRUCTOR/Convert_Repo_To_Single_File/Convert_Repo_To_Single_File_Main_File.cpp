




#include <iostream>
#include "Convert_Repo_To_Single_File.h"

int main(int argc, char** argv){

    if(argc < 3){

       std::cout << "\n";
       std::cout << "\n The project path and document path must be entered ..";
       std::cout << "\n";
       std::cout << "\n Please enter the project path!\n\n";
       std::cout << "\n";

       return 0;
    }
    else{

         Convert_Repo_To_Single_File Converter;

         Converter.Receive_Repo_Directory(argv[1]);

         Converter.Receive_Document_Path(argv[2]);

         Converter.Construct_Source_File();
    }

    return 0;
}
