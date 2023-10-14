
#include "Library_Updater.h"

void Place_String(char ** Pointer, const char * String);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << "\n usage: Library_Updater.exe <desciptor file>";

       std::cout << "\n\n";

       std::cout << "\n\n";

       exit(0);
    }

    Library_Updater Updater('w');

    Updater.Receive_Descriptor_File_Path(argv[1]);

    //Updater.Receive_Library_Name(argv[2]);

    Updater.Build_Library();


    return 0;
}
