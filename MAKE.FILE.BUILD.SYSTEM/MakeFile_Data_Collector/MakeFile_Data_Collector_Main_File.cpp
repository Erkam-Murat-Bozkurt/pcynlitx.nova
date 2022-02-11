


#include <iostream>
#include <cstring>
#include "MakeFile_Data_Collector.hpp"
#include "Project_Files_Lister.h"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_Reader;

    Des_Reader.Read_Descriptor_File(argv[1]);

    char * warehouse_path  = Des_Reader.Get_Warehouse_Location();

    char * project_repo_dir = Des_Reader.Get_Repo_Directory_Location();

    Project_Files_Lister File_Lister;

    File_Lister.Determine_Git_Repo_Info(project_repo_dir,warehouse_path);

    int dir_number = File_Lister.Get_Git_Repo_Directory_Number();

    MakeFile_Data_Collector Data_Collector;

    if(dir_number > 0){

       Data_Collector.Receive_Descriptor_File_Reader(&Des_Reader);

       Data_Collector.Receive_Git_Record_Data(&File_Lister,0);

       Data_Collector.Collect_Make_File_Data();
    }
    else{

        std::cout << "\n There is no source file in that git repo";

        std::cout << "\n\n";

        exit(0);
    }

    int inhd_flnr = Data_Collector.Get_Included_Header_Files_Number();

    std::cout << "\n INCLUDED HEADER FILES NUMBER:";

    for(int i=0;i<inhd_flnr;i++){

        std::cout << "\n Header [" << i << "]:" << Data_Collector.Get_Included_Header_Files()[i];
    }

    std::cout << "\n\n";
    std::cout << "\n Data_Collector.Get_Compiler_System_Command() :" << Data_Collector.Get_Compiler_System_Command();

    std::cout << "\n\n";
    std::cout << "\n Data_Collector.Get_Dependency_Code_Line()    :" << Data_Collector.Get_Dependency_Code_Line();

    std::cout << "\n\n";

    std::cout << "\n Data_Collector.Get_Source_File_Name()                :" << Data_Collector.Get_Source_File_Name();
    std::cout << "\n Data_Collector.Get_Make_File_Name()                  :" << Data_Collector.Get_Make_File_Name();
    std::cout << "\n Data_Collector.Get_Object_File_Name()                :" << Data_Collector.Get_Object_File_Name();
    std::cout << "\n Data_Collector.Get_Git_Header_File_Dir()             :" << Data_Collector.Get_Git_Header_File_Dir();
    std::cout << "\n Data_Collector.Get_Source_File_Name_With_Extention() :" << Data_Collector.Get_Source_File_Name_With_Extention();
    std::cout << "\n Data_Collector.Get_Repo_Dir()                        :" << Data_Collector.Get_Repo_Dir();
    std::cout << "\n Data_Collector.Get_Warehouse_Header_Dir()            :" << Data_Collector.Get_Warehouse_Header_Dir();
    std::cout << "\n Data_Collector.Get_Warehouse_Object_Dir()            :" << Data_Collector.Get_Warehouse_Object_Dir();
    std::cout << "\n Data_Collector.Get_Warehouse_Path()                  :" << Data_Collector.Get_Warehouse_Path();
    std::cout << "\n Data_Collector.Get_Git_Repo_Header_File_Path()       :" << Data_Collector.Get_Git_Repo_Header_File_Path();

    std::cout << "\n\n";
    std::cout << "\n The end of the program ..\n\n";

    return 0;
}
