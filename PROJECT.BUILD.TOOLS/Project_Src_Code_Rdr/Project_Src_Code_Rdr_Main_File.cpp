




#include <iostream>
#include <cstring>
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"




void print_include_declerations(const std::vector<std::string> & vec);



int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_Data_Processor Git_Data_Proc('w');

    Git_Data_Proc.Receive_Descriptor_File_Path(argv[1]);

    Git_Data_Proc.Write_Git_Repo_List_File();

    Git_Data_Proc.Determine_Git_Repo_Info();


    int index_size = Git_Data_Proc.Get_Git_File_Index_Size();

    std::cout << "\n index_size:" << index_size;


    for(int i=0;i<index_size;i++){

        std::cout << "\n";

        std::cout << "\n Git Record File -"  << i << " :" << Git_Data_Proc.Get_Git_File_Index(i);

        std::cout << "\n System path     -"  << i << " :" << Git_Data_Proc.Get_File_System_Path(i);

        std::cout << "\n";
    }


    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n THE COMPUTATIONS COMPLATED";

    size_t src_file_num = Code_Rd.Get_Project_Files_Number();

    std::cout << "\n File number:" << src_file_num;

    for(size_t i=0;i<src_file_num;i++){
    
       std::string path = Code_Rd.Get_File_Path(i);

       const FileData * Data = Code_Rd.Find_File_Data_From_Path(path);

       
       std::cout << "\n\n";
       std::cout << "\n #FILE NAME: " << Data->file_name;
       std::cout << "\n Data index:"<< i;
       std::cout << "\n Path:" << Data->sys_path;

       std::string combined_name = Data->cmbn_name;

       
       /*
       FileData * Data_Name = Code_Rd.Find_File_Data_From_Name(name);

       std::cout << "\n Name:"   << Data_Name->file_name;

       std::string combined_name = Data_Name->combined_file_name;

       std::cout << "\n The obtained combained name:" << combined_name;
       */
       
       const FileData * Data_Combined_Name = Code_Rd.Find_File_Data_From_Directory_File_Name_Combination(combined_name);

       std::cout << "\n";
       std::cout << "\n\e[1;32m After retreiving data from combined file name!\e[0m";
       std::cout << "\n";

       std::cout << "\n File path:"      << Data_Combined_Name->sys_path;

       std::cout << "\n Combined Name:"  << Data_Combined_Name->cmbn_name;

       std::cout << "\n Is source file:" << Data_Combined_Name->is_source_file;

       std::cout << "\n Is main   file:" << Data_Combined_Name->is_main_file;
       
       std::cout << "\n Is header file:" << Data_Combined_Name->is_header_file;

       bool is_repo_file = Code_Rd.Check_Repo_File_Status_From_Directory_File_Name_Combination(Data_Combined_Name->cmbn_name);

       std::cout << "\n is_repo_file:" << is_repo_file;

       print_include_declerations(Data_Combined_Name->include_declerations);

       std::cout << "\n\n ";           
    }

    std::cout << "\n\n";

    Code_Rd.Clear_Object_Memory();

    return 0;
}


void print_include_declerations(const std::vector<std::string> & vec){

     std::cout << "\n\n The include declerations:";    
     std::cout << "\n ---------------------------------";


     size_t vec_size = vec.size();

     for(size_t i=0;i<vec_size;i++){
     
         std::string line = vec.at(i);

         std::cout << "\n " << line;
     }
}