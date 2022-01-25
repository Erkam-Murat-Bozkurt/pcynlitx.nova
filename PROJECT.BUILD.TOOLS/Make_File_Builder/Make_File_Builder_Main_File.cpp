
#include <iostream>
#include <cstring>
#include "Make_File_Builder.h"
#include "Project_Files_Lister.h"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: Make_File_Builder.exe <Repo Directory> ";

       std::cout << "<Proj. Warehouse Location>";

       std::cout << "\n\n";

       exit(0);
    }

    Project_Files_Lister File_Lister;

    File_Lister.Determine_Git_Repo_Info(argv[1],argv[2]);

    int dir_number = File_Lister.Get_Git_Repo_Directory_Number();

    Make_File_Builder File_Builder;

    char * source_file_name = nullptr;

    char * header_file_name = nullptr;

    char * git_header_path  = nullptr;

    if(dir_number > 0){

       source_file_name = File_Lister.Get_Source_File_Name(0);

       header_file_name = File_Lister.Get_Header_File_Name_With_Extention(0);

       git_header_path =  File_Lister.Get_Git_Repo_Header_File_Path(0);
    }

    std::cout << "\n source file name:" << source_file_name;

    std::cout << "\n header_file_name:" << header_file_name;

    std::cout << "\n git header path :" << git_header_path;

    std::cin.get();

    File_Builder.Receive_Source_File_Name(source_file_name);

    File_Builder.Receive_Header_File_Name_With_Its_Extention(header_file_name);

    File_Builder.Build_MakeFile(argv[1],argv[2],git_header_path);

    return 0;
}
