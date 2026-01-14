








#include <iostream>
#include <cstring>
#include <vector>
#include "Dependency_Data_Processor.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 2){

       std::cout << "\n The usage: Dependency_Data_Processor.exe <Descriptor File Path>";

       std::cout << "\n\n";

       exit(0);
    }



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


    Dependency_Data_Processor Dep_Data_Processor('w');

    Dep_Data_Processor.Receive_Descriptor_File_Reader(&Des_Reader);

    Dep_Data_Processor.Receive_Source_Code_Reader(&Code_Rd);

    Dep_Data_Processor.Perform_Dependency_Search();



    const std::vector<Search_Data_Records> * src_data = Dep_Data_Processor.Get_Search_Data();


    for(size_t i=0;i<src_data->size();i++){

        std::cout << "\n\n\n";
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
              //std::cout << "\n Depdency :" << data_ptr->at(j).dep_counter;

           }
        }

        std::cout << "\n\n";

        const std::vector<std::string> * ext_hdr_ptr = &(src_data->at(i).External_Headers);

        for(size_t j=1;j<ext_hdr_ptr->size();j++){

             std::cout << "\n External Header:" << ext_hdr_ptr->at(j);
        }

        std::cout << "\n\n";
    }


    //std::cin.get();


    //Dep_Data_Processor.Set_Dependency_Counters();


    /*

    std::cout << "\n\n AFTER DEPENDENCY COUNTER SETS";

    src_data = Dep_Data_Processor.Get_Search_Data();


    for(size_t i=0;i<src_data->size();i++){


        std::cout << "\n\n\n";
        std::cout << "\n\n THE SEARCH DATA FOR PATH:";
        std::cout << "\n " << src_data->at(i).path; 

        const std::vector<Search_Data> * data_ptr = &(src_data->at(i).Dependent_Headers);

        std::cout << "\n FILE NAME:" << data_ptr->at(0).name;
        std::cout << "\n FILE PATH:" << data_ptr->at(0).path;        
        std::cout << "\n";
        std::cout << "\n FILE DEPENDENCIES:";

        for(size_t j=1;j<data_ptr->size();j++){

             std::cout << "\n File name:" << data_ptr->at(j).name;
             //std::cout << "\n File path:" << data_ptr->at(j).path;
             std::cout << "\n Depdency :" << data_ptr->at(j).dep_counter;

        }

        std::cout << "\n\n";

        const std::vector<std::string> * ext_hdr_ptr = &(src_data->at(i).External_Headers);

        for(size_t j=1;j<ext_hdr_ptr->size();j++){

             std::cout << "\n External Header:" << ext_hdr_ptr->at(j);

        }

        std::cout << "\n\n";
    }

    */



    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
