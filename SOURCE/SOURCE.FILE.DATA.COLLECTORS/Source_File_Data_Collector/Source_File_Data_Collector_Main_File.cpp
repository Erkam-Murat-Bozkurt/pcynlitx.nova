

#include <iostream>
#include <cstring>
#include "Git_File_List_Receiver.hpp"
#include "Source_File_Data_Collector.hpp"
#include "Descriptor_File_Reader.hpp"

int main(int argc, char ** argv){

    if(argc < 3){

       std::cout << "\n\n";

       std::cout << " usage: <exe file> <Descriptor File Path> <Source File Path>";

       std::cout << "\n\n";

       exit(0);
    }


    std::string file_path;

    size_t path_size = strlen(argv[2]);

    for(size_t i=0;i<path_size;i++){

         file_path.push_back(argv[2][i]);
    }


    Git_File_List_Receiver Receiver('w');

    Receiver.Receive_Descriptor_File_Path(argv[1]);

    Receiver.Determine_Git_Repo_Info();



    Build_System_Data Data;

    Source_File_Data_Collector Data_Collector('w');

    Data_Collector.Receive_Git_File_List_Receiver(&Receiver);



    Data_Collector.Receive_Descriptor_File_Path(argv[1]);  

    Data_Collector.Process_Source_File_Data(&Data,file_path);


    file_path.clear();

    file_path.shrink_to_fit();


    int Header_File_Number = Data_Collector.Get_Included_File_Number();

    if(Header_File_Number > 0){

       for(int i=0;i<Header_File_Number;i++){

           std::cout << "\n The header file - " << i << ": "

           << Data_Collector.Get_Include_File_Name(i);


          std::cout << "\n The header file directory- " << i << ": "

          << Data_Collector.Get_Include_File_Directory(i);


          std::cout << "\n The header file git record directory - " << i << ": "

          << Data_Collector.Get_Include_File_Git_Record_Directory(i);


          std::cout << "\n The header file git record path - " << i << ": "

          << Data_Collector.Get_Include_File_Git_Record_Path(i);
       }
    }

    std::cout << "\n\n";

    std::cout << "\n\n BUILD DATA INFORMATIONS: ";

    std::cout << "\n git_record_path   :"  << Data.git_record_path;   // Header path in git record
    std::cout << "\n git_record_dir    :"  << Data.git_record_dir;    // The git record directory
    std::cout << "\n File_Directory    :"  << Data.File_Directory;      // The directory of the file which is record constructed
    std::cout << "\n File_Path         :"  << Data.File_Path;           // Header file exact path ( System Path )
    std::cout << "\n File_Name         :"  << Data.File_Name;           // The file name witout extentation
    std::cout << "\n File_Name (Ext)   :"  << Data.File_Name_With_Ext;  // The header file name with extention
    std::cout << "\n Header Name       :"  << Data.class_header_file_name;
    std::cout << "\n Header Path       :"  << Data.class_header_file_path;
    std::cout << "\n Header Number     :"  << Data.Included_Header_Files_Number;
    std::cout << "\n Is Source         :"  << Data.is_this_a_source_file;
    std::cout << "\n Is Header         :"  << Data.is_this_a_header_file;


    std::vector<std::string>::iterator it;

    for(auto it=Data.Included_Header_Files.begin();it<Data.Included_Header_Files.end();it++){

        std::cout << "\n Header File :" << *it;
    }


    for(auto it=Data.Included_Header_Files_Directories.begin();it<Data.Included_Header_Files_Directories.end();it++){

        std::cout << "\n Header File :" << *it;
    }


    for(auto it=Data.Included_Header_Files_System_Path.begin();it<Data.Included_Header_Files_System_Path.end();it++){

        std::cout << "\n Header File :" << *it;
    }

    for(auto it=Data.Included_Header_Files_Git_Record_Path.begin();it<Data.Included_Header_Files_Git_Record_Path.end();it++){

        std::cout << "\n Header File :" << *it;
    }

    for(auto it=Data.Included_Header_Files_Git_Record_Dir.begin();it<Data.Included_Header_Files_Git_Record_Dir.end();it++){

        std::cout << "\n Header File :" << *it;
    }

    Data_Collector.Clear_Dynamic_Memory();

    file_path.clear();

    file_path.shrink_to_fit();


    return 0;
}
