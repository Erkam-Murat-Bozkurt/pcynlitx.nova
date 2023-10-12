
#include "Library_Updater.h"

void Place_String(char ** Pointer, const char * String);

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n\n";

       std::cout << "\n usage: Library_Updater.exe <desciptor file> <library name>";

       std::cout << "\n\n";

       std::cout << "\n\n";

       exit(0);
    }

    Library_Updater Updater(argv[1],'w');

    Updater.Build_Library(argv[2]);


    return 0;
}
