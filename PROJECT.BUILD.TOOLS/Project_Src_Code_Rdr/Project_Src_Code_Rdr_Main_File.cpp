




#include <iostream>
#include <cstring>
#include "Project_Src_Code_Rdr.hpp"
#include "Git_Data_Processor.hpp"
#include "Git_File_List_Receiver.hpp"
#include "Descriptor_File_Reader.hpp"




void print_file(std::vector<std::string> * ptr);

void Clear_Vector_Memory(std::vector<std::string> & pointer);

void Clear_String_Memory(std::string & str);



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


    /*

    int index_size = Git_Data_Proc.Get_Git_File_Index_Size();

    std::cout << "\n index_size:" << index_size;


    for(int i=0;i<index_size;i++){

        std::cout << "\n";

        std::cout << "\n Git Record File -"  << i << " :" << Git_Data_Proc.Get_Git_File_Index(i);

        std::cout << "\n System path     -"  << i << " :" << Git_Data_Proc.Get_File_System_Path(i);

        std::cout << "\n";
    }

    */


    Project_Src_Code_Rdr Code_Rd('w');

    Code_Rd.Receive_Git_Data_Processor(&Git_Data_Proc);

    Code_Rd.Read_Project_Source_Code_Files();

    std::cout << "\n THE COMPUTATIONS COMPLATED";

    size_t src_file_num = Code_Rd.Get_Project_Files_Number();

    std::cout << "\n File number:" << src_file_num;
    std::cin.get();
    
    for(size_t i=0;i<src_file_num;i++){
    
       std::string path = Code_Rd.Get_File_Path(i);

       const FileData * Data = Code_Rd.Find_File_Data_From_Path(path);

       
       std::cout << "\n\n";
       std::cout << "\n i:"<< i;
       std::cout << "\n Path:" << Data->sys_path;

       std::string combined_name = Data->combined_file_name;

       
       /*
       FileData * Data_Name = Code_Rd.Find_File_Data_From_Name(name);

       std::cout << "\n Name:"   << Data_Name->file_name;

       std::string combined_name = Data_Name->combined_file_name;

       std::cout << "\n The obtained combained name:" << combined_name;
       */
       
       const FileData * Data_Combined_Name = Code_Rd.Find_File_Data_From_Combined_Name(combined_name);

       std::cout << "\n File path:"  << Data_Combined_Name->sys_path;

       std::cout << "\n Combined Name:" << Data_Combined_Name->combined_file_name;

       bool is_repo_file = Code_Rd.Check_Repo_File_Status_From_Combined_File_Name(Data_Combined_Name->combined_file_name);

       std::cout << "\n is_repo_file:" << is_repo_file;

       std::cout << "\n\n ";           
    }

    std::cout << "\n\n";

    Code_Rd.Clear_Object_Memory();

    return 0;
}

void Clear_File_Data(FileData & data){

     Clear_String_Memory(data.combined_file_name);
     Clear_String_Memory(data.file_name);
     Clear_String_Memory(data.sys_path);
     Clear_Vector_Memory(data.FileContent);    
}


void Clear_String_Memory(std::string & str){

     if(!str.empty()){

        str.clear();
        str.shrink_to_fit();
     }
}


void Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         std::vector<std::string>::iterator it;

         auto begin = vec.begin();

         auto end   = vec.end();

         for(auto it=begin;it<end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}



void print_file(std::vector<std::string> * ptr){

     size_t vec_size = ptr->size();

     for(size_t i=0;i<vec_size;i++){
     
         std::string line = ptr->at(i);

         std::cout << line;
     }
}