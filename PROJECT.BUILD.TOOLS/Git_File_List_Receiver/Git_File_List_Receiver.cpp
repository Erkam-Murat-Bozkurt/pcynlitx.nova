

#include "Git_File_List_Receiver.hpp"

Git_File_List_Receiver::Git_File_List_Receiver(){

    this->Memory_Delete_Condition = true;

    this->File_Line_Number = 0;

    this->File_List_Content = nullptr;

    this->Warehouse = nullptr;

    this->git_file_list_path = nullptr;

    this->git_listing_command = nullptr;

    this->Repo_Dir = nullptr;
}

Git_File_List_Receiver::Git_File_List_Receiver(const Git_File_List_Receiver & orig){


}

Git_File_List_Receiver::~Git_File_List_Receiver(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Git_File_List_Receiver::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;


         if(this->git_listing_command != nullptr){

            delete [] this->git_listing_command;

            this->git_listing_command = nullptr;
          }

          if(this->File_List_Content != nullptr){

            for(int i=0;i<this->File_Line_Number;i++){

               delete [] this->File_List_Content[i];
            }

            delete [] this->File_List_Content;

            this->File_List_Content = nullptr;
          }

          if(this->git_file_list_path != nullptr){

             delete [] this->git_file_list_path;
          }
     }
}

void Git_File_List_Receiver::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader_Pointer = Pointer;

     this->Warehouse = this->Des_Reader_Pointer->Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader_Pointer->Get_Repo_Directory_Location();
}

void Git_File_List_Receiver::Determine_Git_Repo_Info(){

     this->Determine_Git_File_List_Path();

     this->Determine_Git_Listing_Command();

     this->List_Files_in_Repo();

     this->Determine_Repo_List_File_Size();

     this->Read_Repo_List_File();
}

void Git_File_List_Receiver::Determine_Git_File_List_Path(){

     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     size_t warehouse_path_size = strlen(this->Warehouse);

     size_t file_path_size = file_name_size + warehouse_path_size;

     this->Memory_Delete_Condition = false;

     this->git_file_list_path = new char [5*file_path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->git_file_list_path[index] = this->Warehouse[i];

         index++;
     }

     if(this->Warehouse[warehouse_path_size-1] != '\\'){

        this->git_file_list_path[index] = '\\';

        index++;
      }

     for(size_t i=0;i<file_name_size;i++){

         this->git_file_list_path[index] = repo_list_file_name[i];

         index++;
     }

     this->git_file_list_path[index] = '\0';
}


void Git_File_List_Receiver::Determine_Git_Listing_Command(){

     char git_command [] = "git ls-files > ";

     size_t git_command_size = strlen(git_command);

     size_t target_file_path_size = strlen(this->git_file_list_path);

     size_t command_size = git_command_size + target_file_path_size;

     this->Memory_Delete_Condition = false;

     this->git_listing_command = new char [5*command_size];

     int index = 0;

     for(size_t i=0;i<git_command_size;i++){

         this->git_listing_command[index] = git_command[i];

         index++;
     }

     for(size_t i=0;i<target_file_path_size;i++){

         this->git_listing_command[index] = git_file_list_path[i];

         index++;
     }

     this->git_listing_command[index] = '\0';
}

void Git_File_List_Receiver::List_Files_in_Repo(){

     if(this->FileManager.Is_Path_Exist(this->git_file_list_path)){

        this->FileManager.Delete_File(this->git_file_list_path);
     }

     this->DirectoryManager.ChangeDirectory(this->Repo_Dir);

     int system_return_value = system(this->git_listing_command);
}

void Git_File_List_Receiver::Determine_Repo_List_File_Size(){

     std::cout << "\n Inside Determine_Repo_List_File_Size";

     std::cin.get();

     this->File_Line_Number = 0;

     this->FileManager.SetFilePath(this->git_file_list_path);

     this->FileManager.FileOpen(Rf);

     do {

          std::string string_line = this->FileManager.ReadLine();

          std::cout << "\n string_line:" << string_line;

          std::cin.get();

          this->File_Line_Number++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();

     std::cout << "\n Inside Git_File_List_Receiver::Determine_Repo_List_File_Size()";

     std::cout << "\n this->File_Line_Number:" << this->File_Line_Number;

     std::cin.get();

}

void Git_File_List_Receiver::Read_Repo_List_File(){

     this->Memory_Delete_Condition = false;

     this->File_List_Content = new char * [10*this->File_Line_Number];

     this->FileManager.SetFilePath(this->git_file_list_path);

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          std::string file_line = this->FileManager.ReadLine();

          this->Place_String(&(this->File_List_Content[index]),file_line);

          index++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();
}


void Git_File_List_Receiver::Place_String(char ** pointer, std::string string_line){

     size_t string_size = string_line.length();

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string_line[i];
     }

     (*pointer)[string_size] = '\0';
}

char * Git_File_List_Receiver::Get_Git_File_Index(int num){

      return this->File_List_Content[num];
}

char * Git_File_List_Receiver::Get_Git_Repo_Directory(){

       return this->Repo_Dir;
}

int Git_File_List_Receiver::Get_Git_File_Index_Size(){

    return this->File_Line_Number;
}
