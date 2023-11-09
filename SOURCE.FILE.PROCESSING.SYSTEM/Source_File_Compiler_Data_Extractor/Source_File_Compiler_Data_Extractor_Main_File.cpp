




#include <iostream>
#include <cstring>
#include <vector>
#include "Source_File_Compiler_Data_Extractor.hpp"
#include "Source_File_Dependency_Selector_For_Single_File.hpp"
#include "Source_File_Dependency_Selector.hpp"
#include "Source_File_Information_Collector_For_Single_File.hpp"
#include "Source_File_Information_Collector.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"



void print_compiler_data(std::vector<Compiler_Data> * data_ptr);



int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Source_File_Compiler_Data_Extractor.exe <Descriptor File Path> ";

       std::cout << "\n\n";

       exit(0);
    }


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Data_Processor('w');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();


    size_t index_size = Data_Processor.Get_Git_File_Index_Size();



    Project_Src_Code_Rdr Code_Rd('w');


    Code_Rd.Receive_Git_Data_Processor(&Data_Processor);

    Code_Rd.Read_Project_Source_Code_Files();


    /*

    //std::string path =  "D:\\pcynlitx.build.gui\\wxLauncher.cpp";

    std::string path = "D:\\PCYNLITX.BUILD.TEST\\Pcynlitx.Win\\KERNEL.DEVELOPMENT\\Kernel\\Kernel_Main_File.cpp";

    */


    Source_File_Dependency_Selector Dep_Selector('w');

    Dep_Selector.Receive_Source_Code_Reader(&Code_Rd);

    Dep_Selector.Receive_Git_Data_Processor(&Data_Processor);

    Dep_Selector.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Selector.Determine_Source_File_Dependencies();


    std::vector<std::vector<Source_File_Dependency>> * ptr = Dep_Selector.Get_Dependency_List_Adress();

 

    Source_File_Compiler_Data_Extractor Compiler_Data_Extractor('w');

    Compiler_Data_Extractor.Receive_Dependency_Data(&Dep_Selector);

    Compiler_Data_Extractor.Extract_Compiler_Data();


    std::vector<Compiler_Data> * data_ptr = Compiler_Data_Extractor.Get_Compiler_Data_Address();


    std::cout << "\n\n DATA FOR REPOSITORY:";

    print_compiler_data(data_ptr);

    Compiler_Data_Extractor.Clear_Dynamic_Memory();

    Dep_Selector.Clear_Dynamic_Memory();


    Compiler_Data_Extractor.Clear_Object_Memory();

    Dep_Selector.Clear_Object_Memory();

    return 0;
}


void print_compiler_data(std::vector<Compiler_Data> * data_ptr){

     size_t data_size = data_ptr->size();


     for(size_t i=0;i<data_size;i++){

         Compiler_Data temp = data_ptr->at(i);

         std::cout << "\n source file path     :" << temp.source_file_path;
         std::cout << "\n source file name     :" << temp.source_file_name;
         std::cout << "\n object_file_name     :" << temp.object_file_name;
         std::cout << "\n source name wext     :" << temp.source_file_name_witout_ext;


         std::cout << "\n";

         size_t head_size = temp.dependent_headers.size();


         for(int k=0;k<head_size;k++){

             std::cout << "\n included header:" << temp.dependent_headers[k];
         }

         size_t headers_size = temp.dependent_headers.size();

         std::cout << "\n";

         
         for(int k=0;k<headers_size;k++){

             std::cout << "\n included header path:" << temp.dependent_headers[k];
         } 

         std::cout << "\n";


         size_t dir_num = temp.dependent_headers_dir.size();


         for(int k=0;k<dir_num;k++){

             std::cout << "\n included header directory:" << temp.dependent_headers_dir[k];
         } 


         size_t upper_dir__size = temp.upper_directories.size();

         std::cout << "\n";

         
         for(int k=0;k<upper_dir__size;k++){

             std::cout << "\n included header path:" << temp.upper_directories[k];
         } 

         std::cout << "\n";

         std::cout << "\n";

         std::cout << "\n priority:" << temp.priority;

         std::cout << "\n\n\n\n\n";
    }
}