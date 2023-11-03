










#include <iostream>
#include <cstring>
#include <vector>
#include <chrono>
#include <stdlib.h>     //for using the function sleep
#include "Header_Dependency_Data_Extractor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

void Print_Search_Data(Header_Dependency_Data_Extractor * ptr);

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Header_Dependency_Data_Extractor.exe <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();


    Descriptor_File_Reader Des_Reader('w');

    Des_Reader.Receive_Descriptor_File_Path(argv[1]);

    Des_Reader.Read_Descriptor_File();


    Git_Data_Processor Git_Data_Proc('w');

    Git_Data_Proc.Receive_Descriptor_File_Path(argv[1]);

    Git_Data_Proc.Write_Git_Repo_List_File();

    Git_Data_Proc.Determine_Git_Repo_Info();

    int index_size = Git_Data_Proc.Get_Git_File_Index_Size();




    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();


    std::cout << "\n\n";

    std::cout << "\n Code reading complated..";


    Dependency_Data_Stack_Container Stack_Container;


    Header_Dependency_Data_Extractor Header_Dep_Data_Extractor('w');

    Header_Dep_Data_Extractor.Receive_Descriptor_File_Reader(&Des_Reader);

    Header_Dep_Data_Extractor.Receive_Dependency_Data_Stack_Container(&Stack_Container);

    Header_Dep_Data_Extractor.Receive_Source_Code_Reader(&Code_Rd);

    Header_Dep_Data_Extractor.Perform_Dependency_Search();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " 
    
    << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() 
    
    << "[s]" << std::endl;

    std::cout << "\n File dependencies determined";

    Header_Dep_Data_Extractor.Clear_Dynamic_Memory();

    Print_Search_Data(&Header_Dep_Data_Extractor);

    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}


void Print_Search_Data(Header_Dependency_Data_Extractor * ptr){


    const std::vector<Search_Data_Records> * src_data = ptr->Get_Search_Data();

    for(size_t i=0;i<src_data->size();i++){

        std::cout << "\n";
        std::cout << "\n\n THE SEARCH DATA FOR PATH:";
        std::cout << "\n " << src_data->at(i).path; 

        const std::vector<Search_Data> * data_ptr = &(src_data->at(i).Dependent_Headers);

        if(data_ptr->size()>0){

          std::cout << "\n FILE NAME:" << data_ptr->at(0).name;
          std::cout << "\n FILE PATH:" << data_ptr->at(0).path;
          std::cout << "\n";
          std::cout << "\n FILE DEPENDENCIES:";

          for(size_t j=1;j<data_ptr->size();j++){

             std::cout << "\n File name:" << data_ptr->at(j).name;
             //std::cout << "\n File path:" << data_ptr->at(j).path;
             std::cout << "\n Depdency :" << data_ptr->at(j).dep_counter;

          }
        }
     
        const std::vector<std::string> * ext_hdr_ptr = &(src_data->at(i).External_Headers);
     
        if(ext_hdr_ptr->size()>0){

            std::cout << "\n\n";

            for(size_t j=1;j<ext_hdr_ptr->size();j++){

                std::cout << "\n External Header:" << ext_hdr_ptr->at(j);
             }
        }

        std::cout << "\n\n";

        sleep(0.5);
    }

}