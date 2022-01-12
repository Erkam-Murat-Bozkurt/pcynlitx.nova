


#include "Repo_Warehouse_Initializer.h"

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(){

     this->Memory_Delete_Condition = true;

     this->Headers_Directory = nullptr;

     this->Header_File_Paths = nullptr;

     this->Headers_New_Paths = nullptr;

     this->Object_Files_Directory = nullptr;

     this->warehouse_path = nullptr;

     this->current_directory = nullptr;

     this->project_dir_num = 0;
}

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(const Repo_Warehouse_Initializer & orig){


}

Repo_Warehouse_Initializer::~Repo_Warehouse_Initializer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Repo_Warehouse_Initializer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Header_File_Paths != nullptr){

            for(int i=0;i<this->project_dir_num;i++){

               delete [] this->Header_File_Paths[i];
            }

            delete [] this->Header_File_Paths;

            this->Header_File_Paths = nullptr;
         }

         if(this->Headers_New_Paths != nullptr){

            for(int i=0;i<this->project_dir_num;i++){

                delete [] this->Headers_New_Paths[i];
            }

            delete [] this->Headers_New_Paths;

            this->Headers_New_Paths = nullptr;
         }

         if(this->Headers_Directory != nullptr){

             delete [] this->Headers_Directory;

             this->Headers_Directory = nullptr;
         }

         if(this->Object_Files_Directory != nullptr){

             delete [] this->Object_Files_Directory;

             this->Object_Files_Directory = nullptr;
         }


         if(this->warehouse_path != nullptr){

            delete [] this->warehouse_path;

            this->warehouse_path = nullptr;
         }
     }
}

void Repo_Warehouse_Initializer::Build_Project_Warehouse(char * repo_dir, char * warehouse){

     this->Dir_Lister.Receive_Repo_Directory(repo_dir);

     this->Receive_Warehouse_Location(warehouse);

     this->Determine_Current_Directory();

     int return_condition = this->DirectoryManager.ChangeDirectory(warehouse);

     if(return_condition == 0){

        this->DirectoryManager.MakeDirectory(warehouse);
     }

     this->DirectoryManager.ChangeDirectory(this->current_directory);

     this->Dir_Lister.Determine_Project_File_List();

     this->project_dir_num

            = this->Dir_Lister.Get_SourceFile_Directory_Number();

     this->Construct_Header_Files_Directory();

     this->Determine_Header_File_Paths();

     this->Copy_Header_Files_To_Project_Headers_Location();

     this->Construct_Object_Files_Directory();
}

void Repo_Warehouse_Initializer::Receive_Warehouse_Location(char * warehouse){

     size_t string_size = strlen(warehouse);

     this->warehouse_path = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         this->warehouse_path[i] = warehouse[i];
     }

     this->warehouse_path[string_size];
}

void Repo_Warehouse_Initializer::Determine_Current_Directory(){

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t dir_name_size = strlen(Current_Directory);

     if(this->current_directory != nullptr){

        delete [] this->current_directory;

        this->current_directory = nullptr;
     }

     this->current_directory = new char [5*dir_name_size];

     for(size_t i=0;i<dir_name_size;i++){

         this->current_directory[i] = Current_Directory[i];
     }

     this->current_directory[dir_name_size] = '\0';
}

void Repo_Warehouse_Initializer::Construct_Header_Files_Directory(){

     char * header_directory = nullptr;

     char header_directory_folder_name [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_folder_size= strlen(header_directory_folder_name);

     size_t head_dir_size = head_folder_size

                           + warehouse_path_size;


     this->Headers_Directory = new char [5*head_dir_size];

     int index = 0;

     for(int i=0;i<warehouse_path_size;i++){

         this->Headers_Directory[index] = this->warehouse_path[i];

         index++;
     }

     this->Headers_Directory[index] = '\\';

     index++;

     for(int i=0;i<head_folder_size;i++){

         this->Headers_Directory[index] = header_directory_folder_name[i];

         index++;
     }

     this->Headers_Directory[index] = '\0';

     this->DirectoryManager.MakeDirectory(this->Headers_Directory);
}

void Repo_Warehouse_Initializer::Determine_Header_File_Paths(){

     this->Header_File_Paths = new char * [5*this->project_dir_num];

     this->Headers_New_Paths = new char * [5*this->project_dir_num];

     for(int k=0;k<5*this->project_dir_num;k++){

         this->Header_File_Paths[k] = nullptr;

         this->Headers_New_Paths[k] = nullptr;
     }

     for(int i=0;i<this->project_dir_num;i++){

        char * directory = this->Dir_Lister.Get_Source_File_Directory(i);

        this->DirectoryManager.ChangeDirectory(directory);

        this->Determine_Header_Paths(i);
     }
}

void Repo_Warehouse_Initializer::Determine_Header_Paths(int dir_num){

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     this->Enumerator.List_Files_On_Directory(Current_Directory);

     int file_num = this->Enumerator.Get_File_Number();

     char ** file_list = this->Enumerator.Get_File_List();

     char header_add [] = ".h";

     char * header_file_name = nullptr;

     for(int k=0;k<file_num;k++){

         bool is_header = this->StringManager.CheckStringInclusion(file_list[k],header_add);

         if(is_header){

            size_t header_name_size = strlen(file_list[k]);

            header_file_name = new char [5*header_name_size];

            for(int i=0;i<5*header_name_size;i++){

                header_file_name[i] = '\0';
            }

            for(size_t j=0;j<header_name_size;j++){

                header_file_name[j] = file_list[k][j];
            }

            header_file_name[header_name_size] = '\0';

            break;
          }
     }

     size_t Directory_Name_Size = strlen(Current_Directory);

     this->Header_File_Paths[dir_num] = new char [5*Directory_Name_Size];

     int index_counter = 0;

     for(size_t i=0;i<Directory_Name_Size;i++){

         this->Header_File_Paths[dir_num][index_counter] = Current_Directory[i];

         index_counter++;
     }

     this->Header_File_Paths[dir_num][index_counter] = '\\';

     index_counter++;

     size_t header_name_size = strlen(header_file_name);

     for(size_t i=0;i<header_name_size;i++){

             this->Header_File_Paths[dir_num][index_counter] =

                 header_file_name[i];

             index_counter++;
     }

     this->Header_File_Paths[dir_num][index_counter] = '\0';

     size_t Target_Directory_Name_Size = strlen(this->Headers_Directory);

     this->Headers_New_Paths[dir_num] = new char [5*Target_Directory_Name_Size];

     int index = 0;

     for(size_t k=0;k<Target_Directory_Name_Size;k++){

        this->Headers_New_Paths[dir_num][index] = this->Headers_Directory[k];

        index++;
     }

     this->Headers_New_Paths[dir_num][index] = '\\';

     index++;

     for(size_t k=0;k<header_name_size;k++){

         this->Headers_New_Paths[dir_num][index] = header_file_name[k];

         index++;
     }

     this->Headers_New_Paths[dir_num][index] = '\0';

     delete [] header_file_name;

}

void Repo_Warehouse_Initializer::Copy_Header_Files_To_Project_Headers_Location(){

     for(int i=0;i<this->project_dir_num;i++){

        this->FileManager.CpFile(this->Header_File_Paths[i],

                  this->Headers_New_Paths[i]);
     }
}


void Repo_Warehouse_Initializer::Construct_Object_Files_Directory(){

     char * header_directory = nullptr;

     char object_directory_folder_name [] = "PROJECT.OBJECT.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_folder_size= strlen(object_directory_folder_name);

     size_t object_dir_size = warehouse_path_size + object_folder_size;

     this->Object_Files_Directory = new char [5*object_dir_size];

     int index = 0;

     for(int i=0;i<warehouse_path_size;i++){

         this->Object_Files_Directory[index] = this->warehouse_path[i];

         index++;
     }

     this->Object_Files_Directory[index] = '\\';

     index++;

     for(int i=0;i<object_folder_size;i++){

         this->Object_Files_Directory[index] = object_directory_folder_name[i];

         index++;
     }

     this->Object_Files_Directory[index] = '\0';

     this->DirectoryManager.MakeDirectory(this->Object_Files_Directory);

}
