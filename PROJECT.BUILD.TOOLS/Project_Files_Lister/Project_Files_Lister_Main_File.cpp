


#include <iostream>
#include <cstring>
#include "Project_Files_Lister.h"
#include "DirectoryOperations.h"

void Place_String(char ** Pointer, char * String);

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <repo directory> <Warehouse path>";

       std::cout << "\n\n";

       exit(0);
    }

    DirectoryOperations DirManager;

    int dir_change_status = DirManager.ChangeDirectory(argv[1]);

    if(dir_change_status == 0){

       std::cout << "\n The directory <" << argv[1] << "> does not exist";

       std::cout << "\n\n";
    }

    Project_Files_Lister Dir_Lister;

    Dir_Lister.Determine_Git_Repo_Info(argv[1],argv[2]);

    //Dir_Lister.Determine_Project_File_List();

    int project_dir_num = Dir_Lister.Get_Make_Data_Number();

    for(int i=0;i<project_dir_num;i++){

       std::cout << "\n\n";

       std::cout << "\n RECORD NUMBER: " << i;

       std::cout << "\n";

       std::cout << " Directory Path:";

       std::cout << Dir_Lister.Get_Make_Directory(i);

       std::cout << "\n";

       std::cout << " Header File Path:";

       std::cout << Dir_Lister.Get_Make_Header_File_Path(i);

       std::cout << "\n";

       std::cout << " Header File Name:";

       std::cout << Dir_Lister.Get_Make_Header_File_Name_With_Extention(i);

       std::cout << "\n";

       std::cout << " Source File name:" << Dir_Lister.Get_Make_Source_File_Name(i);

    }

    std::cout << "\n Press eny key..";

    std::cin.get();

    std::cout << "\n\n";

    return 0;
}

// The Function that places the location Informations listed in below
