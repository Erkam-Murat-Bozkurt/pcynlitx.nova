


#include <iostream>
#include "Document_Builder.h"

int main(int argc, char** argv){

    if(argv[1] == NULL){

       std::cout << "\n";
       std::cout << "\n The file name can not be received ..";
       std::cout << "\n";
       std::cout << "\n Please enter the file name!\n\n";
       std::cout << "\n";

       return 0;
    }
    else{

        std::string Document_PATH = "C:\\Development.Files\\PCYNLITX.BUILD.TEST\\Pcynlitx.SCode.txt";

        std::string File_path;

        size_t path_size = strlen(argv[1]);

        for(size_t i=0;i<path_size;i++){

           File_path.push_back(argv[1][i]);
        }

        File_path.shrink_to_fit();

        Document_Builder Builder;

        Builder.Receive_Document_Path(Document_PATH);

        Builder.Receive_File_Path(argv[1]);

        Builder.Add_File_To_Document();
    }

    return 0;
}
