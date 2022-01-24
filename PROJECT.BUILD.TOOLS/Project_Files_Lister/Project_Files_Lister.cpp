
#include "Project_Files_Lister.h"

Project_Files_Lister::Project_Files_Lister(){

    this->Source_File_Directory_Number = 0;

    this->Repo_Dir = nullptr;

    this->Memory_Delete_Condition = true;

    this->File_Line_Number = 0;

    this->File_List_Content = nullptr;

    this->Warehouse = nullptr;

    this->git_file_list_path = nullptr;

    this->git_listing_command = nullptr;

}

Project_Files_Lister::Project_Files_Lister(const Project_Files_Lister & orig){


}

Project_Files_Lister::~Project_Files_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Project_Files_Lister::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Repo_Dir != nullptr){

            delete [] this->Repo_Dir;

            this->Repo_Dir = nullptr;
         }

         if(this->Warehouse != nullptr){

            delete [] this->Warehouse;

            this->Warehouse = nullptr;
         }

         if(this->git_listing_command != nullptr){

            delete [] this->git_listing_command;

            this->git_listing_command = nullptr;
          }


          if(this->Data_Pointer != nullptr){

             for(int i=0;i<5*this->Source_File_Directory_Number;i++){

                 if(this->Data_Pointer[i].git_header_file_path != nullptr){

                    delete [] this->Data_Pointer[i].git_header_file_path;

                    this->Data_Pointer[i].git_header_file_path = nullptr;
                  }

                  if(this->Data_Pointer[i].Source_File_Directory != nullptr){

                     delete [] this->Data_Pointer[i].Source_File_Directory;

                     this->Data_Pointer[i].Source_File_Directory = nullptr;
                  }

                  if(this->Data_Pointer[i].Header_File_Path != nullptr){

                     delete [] this->Data_Pointer[i].Header_File_Path;

                     this->Data_Pointer[i].Header_File_Path = nullptr;
                  }

                  if(this->Data_Pointer[i].Source_File_Name != nullptr){

                     delete [] this->Data_Pointer[i].Source_File_Name;

                     this->Data_Pointer[i].Source_File_Name = nullptr;
                  }
              }

              delete [] this->Data_Pointer;
          }
       }
}

void Project_Files_Lister::Receive_Repo_Directory(char * repo_dir){

     this->Memory_Delete_Condition = false;

     size_t repo_dir_size = strlen(repo_dir);

     this->Repo_Dir = new char [5*repo_dir_size];

     for(size_t i=0;i<repo_dir_size;i++){

        this->Repo_Dir[i] = repo_dir[i];
     }

     this->Repo_Dir[repo_dir_size] = '\0';
}

void Project_Files_Lister::Receive_Warehouse_Directory(char * warehouse){

     this->Memory_Delete_Condition = false;

     size_t warehouse_dir_size = strlen(warehouse);

     this->Warehouse = new char [5*warehouse_dir_size];

     for(size_t i=0;i<warehouse_dir_size;i++){

        this->Warehouse[i] = warehouse[i];
     }

     this->Warehouse[warehouse_dir_size] = '\0';
}

void Project_Files_Lister::Determine_Git_Repo_Info(char * repo_dir, char * Warehouse){

     this->Receive_Repo_Directory(repo_dir);

     this->Receive_Warehouse_Directory(Warehouse);

     this->Determine_Git_File_List_Path();

     this->Determine_Git_Listing_Command();

     this->List_Files_in_Repo();

     this->Determine_Repo_List_File_Size();

     this->Read_Repo_List_File();

     this->Determine_Source_Directory_Number();

     this->Determine_Source_Directory_Data();
}

void Project_Files_Lister::Determine_Git_File_List_Path(){

     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     size_t warehouse_path_size = strlen(this->Warehouse);

     size_t file_path_size = file_name_size + warehouse_path_size;

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


void Project_Files_Lister::Determine_Git_Listing_Command(){

     char git_command [] = "git ls-files > ";

     size_t git_command_size = strlen(git_command);

     size_t target_file_path_size = strlen(this->git_file_list_path);

     size_t command_size = git_command_size + target_file_path_size;

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

void Project_Files_Lister::List_Files_in_Repo(){

     if(this->FileManager.Is_Path_Exist(this->git_file_list_path)){

        this->FileManager.Delete_File(this->git_file_list_path);
     }

     this->DirectoryManager.ChangeDirectory(this->Repo_Dir);

     int system_return_value = system(this->git_listing_command);
}

void Project_Files_Lister::Determine_Repo_List_File_Size(){

     this->File_Line_Number = 0;

     this->FileManager.SetFilePath(this->git_file_list_path);

     this->FileManager.FileOpen(Rf);

     do {

          std::string string_line = this->FileManager.ReadLine();

          this->File_Line_Number++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();

}

void Project_Files_Lister::Read_Repo_List_File(){

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


void Project_Files_Lister::Determine_Source_Directory_Number(){

     bool is_header_file = false;

     this->Source_File_Directory_Number = 0;

     for(int i=0;i<this->File_Line_Number-1;i++){

         is_header_file = this->Header_Determiner.Is_Header(this->File_List_Content[i]);

         if(is_header_file){

            this->Source_File_Directory_Number++;
         }
    }
}

void Project_Files_Lister::Determine_Source_Directory_Data(){

     this->Data_Pointer = new Source_Data [5*this->Source_File_Directory_Number];

     for(int i=0;i<5*this->Source_File_Directory_Number;i++){

          this->Data_Pointer[i].Source_File_Directory = nullptr;

          this->Data_Pointer[i].Header_File_Path = nullptr;

          this->Data_Pointer[i].git_header_file_path = nullptr;

          this->Data_Pointer[i].Source_File_Name = nullptr;
     }

     int index_counter = 0;

     for(int i=0;i<this->File_Line_Number-1;i++){

          bool is_header_file = this->Header_Determiner.Is_Header(this->File_List_Content[i]);

          bool is_source_file = this->Source_Determiner.Is_Source_File(this->File_List_Content[i]);

          // The header file and source file must be the same directory

          if(is_header_file){

             this->Header_Determiner.Determine_Header_File_Directory(this->File_List_Content[i]);

             char * directory = this->Header_Determiner.Get_Header_Directory();

             this->Construct_Directory_Path(&(this->Data_Pointer[index_counter].Source_File_Directory),directory,'w');

             this->Construct_Header_File_Path(&(this->Data_Pointer[index_counter].Header_File_Path),this->File_List_Content[i],'w');

             this->Construct_Git_Header_Path(&(this->Data_Pointer[index_counter].git_header_file_path),this->File_List_Content[i]);

             index_counter++;
          }
          else{

              if(is_source_file){

                 this->Source_Determiner.Determine_Source_File_Name(this->File_List_Content[i],'w');

                 char * source_file_name = this->Source_Determiner.Get_Source_File_Name();

                 this->Construct_Source_File_Name(&(this->Data_Pointer[index_counter].Source_File_Name),source_file_name);
              }
          }
     }
}

void Project_Files_Lister::Place_String(char ** pointer, std::string string_line){

     size_t string_size = string_line.length();

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string_line[i];
     }

     (*pointer)[string_size] = '\0';
}

void Project_Files_Lister::Construct_Header_File_Path(char ** pointer, char * string_line, char operating_sis){

     size_t repo_dir_size = strlen(this->Repo_Dir);

     size_t string_size = strlen(string_line);

     size_t dir_size = repo_dir_size + string_size;

     int index = 0;

     *pointer = new char [5*dir_size];

     for(size_t i=0;i<repo_dir_size;i++){

         (*pointer)[index] = this->Repo_Dir[i];

         index++;

         if(operating_sis == 'w'){

            if((*pointer)[index] == '/'){

               (*pointer)[index] = '\\';
            }
          }
     }

     if(operating_sis == 'w'){

       if(this->Repo_Dir[repo_dir_size-1] != '\\'){

          (*pointer)[index] = '\\';

          index++;
       }
     }

     if(operating_sis == 'l'){

       if(this->Repo_Dir[repo_dir_size-1] != '/'){

          (*pointer)[index] = '/';
       }
     }

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string_line[i];

        if(string_line[i] == '/'){

           if(operating_sis == 'w'){

              (*pointer)[index] = '\\';
            }
        }

        index++;
     }

     (*pointer)[index] = '\0';
}


void Project_Files_Lister::Construct_Directory_Path(char ** pointer, char * string_line, char operating_sis){

     size_t repo_dir_size = strlen(this->Repo_Dir);

     size_t string_size = strlen(string_line);

     size_t dir_size = repo_dir_size + string_size;

     int index = 0;

     *pointer = new char [5*dir_size];

     for(size_t i=0;i<repo_dir_size;i++){

         (*pointer)[index] = this->Repo_Dir[i];

         index++;

         if(operating_sis == 'w'){

            if((*pointer)[index] == '/'){

               (*pointer)[index] = '\\';
            }
          }
     }

     if(operating_sis == 'w'){

       if(this->Repo_Dir[repo_dir_size-1] != '\\'){

          (*pointer)[index] = '\\';

          index++;
       }
     }

     if(operating_sis == 'l'){

       if(this->Repo_Dir[repo_dir_size-1] != '/'){

          (*pointer)[index] = '/';
       }
     }

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string_line[i];

        if(string_line[i] == '/'){

           if(operating_sis == 'w'){

              (*pointer)[index] = '\\';
            }
        }

        index++;
     }

     (*pointer)[index] = '\0';
}

void Project_Files_Lister::Construct_Source_File_Name(char ** pointer, char * string_line){

     size_t string_size = strlen(string_line);

     int index = 0;

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        if(string_line[i] == '.'){

          break;
        }
        else{

          (*pointer)[index] = string_line[i];

           index++;
        }
     }

     (*pointer)[index] = '\0';
}

void Project_Files_Lister::Construct_Git_Header_Path(char ** pointer, char * string_line){

     size_t string_size = strlen(string_line);

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string_line[i];
     }

     (*pointer)[string_size] = '\0';
}


int Project_Files_Lister::Get_Git_Repo_Directory_Number(){

    return this->Source_File_Directory_Number;
}

char * Project_Files_Lister::Get_Git_Repo_Directory(int num){

       return this->Data_Pointer[num].Source_File_Directory;
}

char * Project_Files_Lister::Get_Git_Repo_Header_File_Path(int num){

      return this->Data_Pointer[num].git_header_file_path;
}

char * Project_Files_Lister::Get_Header_Exact_Path(int num){

       return this->Data_Pointer[num].Header_File_Path;
}

char * Project_Files_Lister::Get_Source_File_Name(int num){

       return this->Data_Pointer[num].Source_File_Name;
}
