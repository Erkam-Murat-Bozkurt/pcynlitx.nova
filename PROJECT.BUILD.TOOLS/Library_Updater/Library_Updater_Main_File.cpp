
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

    Library_Updater Updater;

    Updater.Receive_Descriptor_File(argv[1]);

    Updater.Build_Library(argv[2]);

    //Updater.Send_Library_New_Location(Object_Files_Location,Library_Directory,Library_Name);

    return 0;
}
