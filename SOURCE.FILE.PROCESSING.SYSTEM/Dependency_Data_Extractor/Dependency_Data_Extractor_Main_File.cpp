






#include <iostream>
#include <cstring>
#include <vector>
#include "Dependency_Data_Extractor.hpp"
#include "Dependency_Data_Stack_Container.hpp"
#include "Project_Src_Code_Rdr.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n The usage: Source_File_Dependency_Selector.exe <Descriptor File Path> <Src File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    Git_Data_Processor Data_Processor('w','n');

    Data_Processor.Receive_Descriptor_File_Path(argv[1]);

    Data_Processor.Write_Git_Repo_List_File();

    Data_Processor.Determine_Git_Repo_Info();



    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Data_Processor);

    Code_Rd.Read_Project_Source_Code_Files();


    std::cout << "\n\n";

    std::cout << "\n Code reading complated..";

    Dependency_Data_Stack_Container Stack_Container;


    Dependency_Data_Extractor Dep_Data_Extractor;

    Dep_Data_Extractor.Receive_Operating_System('w');

    Dep_Data_Extractor.Receive_Source_Code_Reader(&Code_Rd);

    Dep_Data_Extractor.Receive_Stack_Container(&Stack_Container);

    Dep_Data_Extractor.Extract_Dependency_Tree(argv[2]);


    std::cout << "\n File path:" << argv[2];

    const Search_Data_Records * Data_Ptr = Dep_Data_Extractor.Get_Search_Data();

    for(size_t i=0;i<Data_Ptr->Dependent_Headers.size();i++){

        std::cout << "\n";
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->Dependent_Headers.at(i).name;
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->Dependent_Headers.at(i).include_decleration;
        std::cout << "\n Dependency File <" << i << ">:" << Data_Ptr->Dependent_Headers.at(i).path;
    }

    std::cout << "\n\n";
    std::cout << "\n THE EXTERNAL HEADER FILES:";
    std::cout << "\n\n";


    if(Data_Ptr->External_Headers.size() > 0){

        for(size_t i=0;i<Data_Ptr->External_Headers.size();i++){

            std::cout << "\n";
            std::cout << "\n External Header[" << i << "]:" << Data_Ptr->External_Headers.at(i);
        }
    }
    else{

            std::cout << "\n There is no external header";
    }



    std::cout << "\n\n THE END OF THE PROGRAM \n\n";


    return 0;
}
