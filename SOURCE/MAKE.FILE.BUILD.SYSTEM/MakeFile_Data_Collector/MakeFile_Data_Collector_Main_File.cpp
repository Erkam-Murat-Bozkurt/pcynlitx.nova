


#include <iostream>
#include <cstring>
#include "MakeFile_Data_Collector.hpp"
#include "Source_File_Dependency_Determiner.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Make_File_Builder.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }

    Descriptor_File_Reader Des_File_Reader('w');    

    Des_File_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_File_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    Source_File_Dependency_Determiner Dep_Determiner(argv[1],'w');

    Dep_Determiner.Receive_Descriptor_File_Reader(&Des_File_Reader);

    Dep_Determiner.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Determiner.Collect_Dependency_Information();


    MakeFile_Data_Collector Data_Collector('w');

    std::vector<Compiler_Data> * vec_ptr = Dep_Determiner.Get_Compiler_Data_Address();

    Compiler_Data ptr = vec_ptr->at(0);

    Data_Collector.Receive_Compiler_Data_Pointer(&ptr);

    std::cout << "\n The initialization data collected..";

    std::cout << "\n src_file_num:" << src_file_num;

    std::cin.get();


    std::string source_file_name = "Kernel.cpp";

    if(src_file_num > 0){

       Data_Collector.Collect_Make_File_Data(source_file_name);
    }
    else{

        std::cout << "\n There is no source file in that git repo";

        std::cout << "\n\n";

        exit(0);
    }

    int inhd_flnr = Data_Collector.Get_Included_Header_Files_Number();

    std::cout << "\n SOURCE FILE NAME:" << source_file_name;

    std::cout << "\n INCLUDED HEADER FILES NUMBER:";

    std::cout << "\n inhd_flnr:" << inhd_flnr;

    std::cout << "\n";

    for(int i=0;i<inhd_flnr;i++){

        std::cout << "\n Header [" << i << "]:" << Data_Collector.Get_Included_Header_Files().at(i);
    }

    std::cout << "\n\n";
    std::cout << "\n Compiler_System_Command :";

    std::cout << "\n " << Data_Collector.Get_Compiler_System_Command();


    std::cout << "\n\n";
    std::cout << "\n Dependency_Code_Line    :";
    
    std::cout << "\n " << Data_Collector.Get_Dependency_Code_Line();

    std::cout << "\n\n";

    std::cout << "\n Source File Name                :" << Data_Collector.Get_Source_File_Name();
    std::cout << "\n Make File Name                  :" << Data_Collector.Get_Make_File_Name();
    std::cout << "\n Object File Name                :" << Data_Collector.Get_Object_File_Name();
    std::cout << "\n Source File Name With Extention :" << Data_Collector.Get_Source_File_Name_With_Extention();
    std::cout << "\n Repo Dir                        :" << Data_Collector.Get_Repo_Dir();
    std::cout << "\n Warehouse Header Dir            :" << Data_Collector.Get_Warehouse_Header_Dir();
    std::cout << "\n Warehouse Object Dir            :" << Data_Collector.Get_Warehouse_Object_Dir();
    std::cout << "\n Warehouse Path                  :" << Data_Collector.Get_Warehouse_Path();

    std::cout << "\n\n";
    std::cout << "\n The end of the program ..\n\n";

    return 0;
}
