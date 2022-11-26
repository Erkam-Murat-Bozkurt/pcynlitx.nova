


#include "Repo_Warehouse_Initializer.h"

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(){

     this->Memory_Delete_Condition = true;

     this->Headers_Directory = nullptr;

     this->Header_File_Paths = nullptr;

     this->Headers_New_Paths = nullptr;

     this->Object_Files_Directory = nullptr;

     this->Library_Files_Directory = nullptr;

     this->warehouse_path = nullptr;

     this->warehouse_location = nullptr;

     this->current_directory = nullptr;

     this->source_files_number = 0;
}

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(const

    Repo_Warehouse_Initializer & orig){


}

Repo_Warehouse_Initializer::~Repo_Warehouse_Initializer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Repo_Warehouse_Initializer::Build_Project_Warehouse(char * Des_File_Path){

     this->Des_Reader.Read_Descriptor_File(Des_File_Path);

     this->warehouse_location = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Current_Directory();

     this->Determine_Warehouse_Path('w');

     this->Determine_Header_Files_Directory('w');

     this->Determine_Object_Files_Directory('w');

     this->Determine_Library_Files_Directory('w');

     this->Construct_Warehouse_Path();

     this->Construct_Header_Files_Directory();

     this->Construct_Object_Files_Directory();

     this->Construct_Library_Files_Directory();

     this->DirectoryManager.ChangeDirectory(this->current_directory);

     this->Dir_Lister.Determine_Git_Repo_Info(&this->Des_Reader);

     this->source_files_number

     = this->Dir_Lister.Get_Source_File_Number();

     this->Determine_Header_File_Paths();

     this->Determine_Independent_Header_Paths();

     this->Copy_Header_Files_To_Project_Headers_Location();

     this->Copy_Independent_Header_Files_To_Project_Headers_Location();
}

void Repo_Warehouse_Initializer::Update_Warehaouse_Headers(char * Des_File_Path){

     this->Des_Reader.Read_Descriptor_File(Des_File_Path);

     this->warehouse_location = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Current_Directory();

     this->Determine_Warehouse_Path('w');

     this->Determine_Header_Files_Directory('w');

     this->DirectoryManager.ChangeDirectory(this->current_directory);

     this->Dir_Lister.Determine_Git_Repo_Info(&this->Des_Reader);

     this->Construct_Header_Files_Directory();

     this->source_files_number

     = this->Dir_Lister.Get_Source_File_Number();

     this->Determine_Header_File_Paths();

     this->Determine_Independent_Header_Paths();

     this->Copy_Header_Files_To_Project_Headers_Location();

     this->Copy_Independent_Header_Files_To_Project_Headers_Location();
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

void Repo_Warehouse_Initializer::Determine_Warehouse_Path(char opr_sis){

     char warehouse_word [] ="WAREHOUSE";

     size_t word_size = strlen(warehouse_word);

     size_t wr_location_size = strlen(this->warehouse_location);

     size_t path_size = word_size + wr_location_size;

     this->warehouse_path = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<wr_location_size;i++){

         this->warehouse_path[index] = this->warehouse_location[i];

         index++;
     }

     if(opr_sis == 'w'){

        this->warehouse_path[index] = '\\';

        index++;
     }

     if(opr_sis == 'l'){

        this->warehouse_path[index] = '/';

        index++;
     }

     for(size_t i=0;i<word_size;i++){

         this->warehouse_path[index] = warehouse_word[i];

         index++;
     }

     this->warehouse_path[index] = '\0';
}

void Repo_Warehouse_Initializer::Determine_Header_Files_Directory(char opr_sis){

     char header_directory_folder_name [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_folder_size= strlen(header_directory_folder_name);

     size_t head_dir_size = head_folder_size

                             + warehouse_path_size;

     this->Headers_Directory = new char [5*head_dir_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Headers_Directory[index] = this->warehouse_path[i];

         index++;
     }

     if(opr_sis == 'w'){

       this->Headers_Directory[index] = '\\';
     }
     else{

         this->Headers_Directory[index] = '/';
     }

     index++;

     for(size_t i=0;i<head_folder_size;i++){

         this->Headers_Directory[index] = header_directory_folder_name[i];

         index++;
     }

     this->Headers_Directory[index] = '\0';

}

void Repo_Warehouse_Initializer::Determine_Object_Files_Directory(char opr_sis){

     char object_directory_folder_name [] = "PROJECT.OBJECT.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_folder_size= strlen(object_directory_folder_name);

     size_t object_dir_size = warehouse_path_size + object_folder_size;

     this->Object_Files_Directory = new char [5*object_dir_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Object_Files_Directory[index] = this->warehouse_path[i];

         index++;
     }

     if(opr_sis == 'w'){

        this->Object_Files_Directory[index] = '\\';
     }
     else{

        this->Object_Files_Directory[index] = '/';
     }

     index++;

     for(size_t i=0;i<object_folder_size;i++){

         this->Object_Files_Directory[index] = object_directory_folder_name[i];

         index++;
      }

      this->Object_Files_Directory[index] = '\0';
}

void Repo_Warehouse_Initializer::Determine_Library_Files_Directory(char opr_sis){

     char directory_folder_name [] = "PROJECT.LIBRARY.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t name_size= strlen(directory_folder_name);

     size_t library_dir_size = warehouse_path_size + name_size;

     this->Library_Files_Directory = new char [5*library_dir_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Library_Files_Directory[index] = this->warehouse_path[i];

         index++;
     }

     this->Library_Files_Directory[index] = '\\';

     index++;

     for(size_t i=0;i<name_size;i++){

         this->Library_Files_Directory[index] = directory_folder_name[i];

         index++;
     }

     this->Library_Files_Directory[index] = '\0';
}

void Repo_Warehouse_Initializer::Construct_Warehouse_Path(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->warehouse_path);

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->warehouse_path);

        if(const_cond == 0){

            std::cout << "\n The project warehouse can not be constructed on:";

            std::cout << "\n";

            std::cout << this->warehouse_location;

            exit(0);
        }
     }
}

void Repo_Warehouse_Initializer::Construct_Header_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Headers_Directory);

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Headers_Directory);

        if(const_cond == 0){

           std::cout << "\n The headers files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Headers_Directory;

           exit(0);
        }
     }
}

void Repo_Warehouse_Initializer::Construct_Object_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Object_Files_Directory);

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Object_Files_Directory);

        if(const_cond == 0){

           std::cout << "\n The object files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Object_Files_Directory;

           exit(0);
        }
     }
}


void Repo_Warehouse_Initializer::Construct_Library_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Library_Files_Directory);

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Library_Files_Directory);

        if(const_cond == 0){

           std::cout << "\n The Library files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Library_Files_Directory;

           exit(0);
        }
     }
}

void Repo_Warehouse_Initializer::Determine_Header_File_Paths(){

     this->Header_File_Paths = new char ** [5*this->source_files_number];

     this->Headers_New_Paths = new char ** [5*this->source_files_number];

     for(int k=0;k<5*this->source_files_number;k++){

         this->Header_File_Paths[k] = nullptr;

         this->Headers_New_Paths[k] = nullptr;
     }

     for(int i=0;i<this->source_files_number;i++){

         int included_header_num = this->Dir_Lister.Get_Source_File_Include_File_Number(i);

         this->Header_File_Paths[i] = new char * [5*included_header_num];

         this->Headers_New_Paths[i] = new char * [5*included_header_num];

         for(int k=0;k<included_header_num;k++){

           char * path = this->Dir_Lister.Get_Source_File_Header_System_Path(i,k);

           if(path!= nullptr){

              this->Determine_Header_Paths(path,i,k);
           }
         }
     }
}

void Repo_Warehouse_Initializer::Determine_Header_Paths(char * path, int src_num, int hdr_num){

     size_t path_size = strlen(path);

     this->Header_File_Paths[src_num][hdr_num] = new char [5*path_size];

     int index_counter = 0;

     for(size_t i=0;i<path_size;i++){

         this->Header_File_Paths[src_num][hdr_num][index_counter] = path[i];

         index_counter++;
     }

     this->Header_File_Paths[src_num][hdr_num][index_counter] = '\0';

     char * Header_File_Name = nullptr;

     this->Determine_File_Name_With_Ext(&Header_File_Name,path);

     size_t header_name_size = strlen(Header_File_Name);

     size_t Target_Directory_Name_Size = strlen(this->Headers_Directory);

     size_t target_path_size = header_name_size + Target_Directory_Name_Size;

     this->Headers_New_Paths[src_num][hdr_num] = new char [5*target_path_size];

     int index = 0;

     for(size_t k=0;k<Target_Directory_Name_Size;k++){

        this->Headers_New_Paths[src_num][hdr_num][index] = this->Headers_Directory[k];

        index++;
     }

     this->Headers_New_Paths[src_num][hdr_num][index] = '\\';

     index++;

     for(size_t k=0;k<header_name_size;k++){

         this->Headers_New_Paths[src_num][hdr_num][index] = Header_File_Name[k];

         index++;
     }

     this->Headers_New_Paths[src_num][hdr_num][index] = '\0';

     delete [] Header_File_Name;

}

void Repo_Warehouse_Initializer::Determine_Independent_Header_Paths(){

     this->ind_hdr_number

     = this->Dir_Lister.Get_Indenpendent_Header_Files_Number();

     this->Independent_Header_Paths     = new char * [5*this->ind_hdr_number];

     this->Independent_Header_New_Paths = new char * [5*this->ind_hdr_number];

     for(int k=0;k<5*this->ind_hdr_number;k++){

         this->Independent_Header_Paths[k] = nullptr;

         this->Independent_Header_New_Paths[k] = nullptr;
     }

     for(int i=0;i<this->ind_hdr_number;i++){

         char * path =  this->Dir_Lister.Get_Independent_Header_File(i);

         if(path!= nullptr){

           this->Find_Independent_Header_Path(path,i);
         }
     }
}

void Repo_Warehouse_Initializer::Find_Independent_Header_Path(char * path, int path_num){

     size_t path_size = strlen(path);

     this->Independent_Header_Paths[path_num] = new char [5*path_size];

     int index_counter = 0;

     for(size_t i=0;i<path_size;i++){

         this->Independent_Header_Paths[path_num][index_counter] = path[i];

         index_counter++;
     }

     this->Independent_Header_Paths[path_num][index_counter] = '\0';


     char * Header_File_Name = nullptr;

     this->Determine_File_Name_With_Ext(&Header_File_Name,path);

     size_t header_name_size = strlen(Header_File_Name);

     size_t Target_Directory_Name_Size = strlen(this->Headers_Directory);

     size_t target_path_size = header_name_size + Target_Directory_Name_Size;

     this->Independent_Header_New_Paths[path_num] = new char [5*target_path_size];

     int index = 0;

     for(size_t k=0;k<Target_Directory_Name_Size;k++){

        this->Independent_Header_New_Paths[path_num][index] = this->Headers_Directory[k];

        index++;
     }

     this->Independent_Header_New_Paths[path_num][index] = '\\';

     index++;

     for(size_t k=0;k<header_name_size;k++){

         this->Independent_Header_New_Paths[path_num][index] = Header_File_Name[k];

         index++;
     }

     this->Independent_Header_New_Paths[path_num][index] = '\0';

     delete [] Header_File_Name;
}

void Repo_Warehouse_Initializer::Copy_Header_Files_To_Project_Headers_Location(){

     for(int i=0;i<this->source_files_number;i++){

         int inc_hdr_num = this->Dir_Lister.Get_Source_File_Include_File_Number(i);

         for(int k=0;k<inc_hdr_num;k++){

           if(this->Header_File_Paths[i][k] != nullptr){

              this->FileManager.CpFile(this->Header_File_Paths[i][k],

                       this->Headers_New_Paths[i][k]);
           }
         }
     }
}

void Repo_Warehouse_Initializer::Copy_Independent_Header_Files_To_Project_Headers_Location(){

     for(int i=0;i<this->ind_hdr_number;i++){

        if(this->Independent_Header_Paths[i] != nullptr){

           this->FileManager.CpFile(this->Independent_Header_Paths[i],

                    this->Independent_Header_New_Paths[i]);
        }
     }
}


void Repo_Warehouse_Initializer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Header_File_Paths != nullptr){

            for(int i=0;i<this->source_files_number;i++){

               int inc_hdr_num = this->Dir_Lister.Get_Source_File_Include_File_Number(i);

               for(int k=0;i<inc_hdr_num;k++){

                   this->Clear_Pointer_Memory(&this->Header_File_Paths[i][k]);
               }
            }

            delete [] this->Header_File_Paths;

            this->Header_File_Paths = nullptr;
         }

         if(this->Headers_New_Paths != nullptr){

            for(int i=0;i<this->source_files_number;i++){

               int inc_hdr_num = this->Dir_Lister.Get_Source_File_Include_File_Number(i);

               for(int k=0;i<inc_hdr_num;k++){

                   this->Clear_Pointer_Memory(&this->Headers_New_Paths[i][k]);
               }
            }

            delete [] this->Headers_New_Paths;

            this->Headers_New_Paths = nullptr;
         }

         if(this->Headers_Directory != nullptr){

           this->Clear_Pointer_Memory(&this->Headers_Directory);

           this->Headers_Directory = nullptr;
         }

         if(this->Object_Files_Directory != nullptr){

            this->Clear_Pointer_Memory(&this->Object_Files_Directory);

            this->Object_Files_Directory = nullptr;
         }

         if(this->Library_Files_Directory != nullptr){

           this->Clear_Pointer_Memory(&this->Library_Files_Directory);

           this->Library_Files_Directory = nullptr;
         }

         if(this->warehouse_path != nullptr){

            this->Clear_Pointer_Memory(&this->warehouse_path);

            this->warehouse_path = nullptr;
         }

         this->Des_Reader.Clear_Dynamic_Memory();
     }
}

void Repo_Warehouse_Initializer::Determine_File_Name_With_Ext(char ** file_name,

     char * path){

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

         if(((path[i] == '/') || (path[i] == '\\'))){

            break;
         }
         else{

              dir_size--;
         }
      }

      size_t Header_File_Name_Size = file_path_size - dir_size;

      *file_name = new char [5*Header_File_Name_Size];

      int index = 0;

      for(size_t i=dir_size+1;i<file_path_size;i++){

          (*file_name)[index] = path[i];

          index++;
      }

      (*file_name)[index] = '\0';
}

void Repo_Warehouse_Initializer::Clear_Pointer_Memory(char ** pointer){

     if(*pointer != nullptr){

        delete [] *pointer;

        *pointer = nullptr;
     }
}
