
#include "Header_File_Determiner.h"

Header_File_Determiner::Header_File_Determiner(){

    this->is_header_file = false;

    this->Header_File_Directory = nullptr;

    this->Header_File_Name = nullptr;

    this->Header_File_System_Path = nullptr;

}

Header_File_Determiner::Header_File_Determiner(const Header_File_Determiner & orig){


}

Header_File_Determiner::~Header_File_Determiner(){


}

void Header_File_Determiner::Clear_Dynamic_Memory(){

       if(!this->Memory_Delete_Condition){

           this->Memory_Delete_Condition = true;

           this->Clear_Pointer_Memory(&this->Header_File_Directory);

           this->Clear_Pointer_Memory(&this->Header_File_Name);

           this->Clear_Pointer_Memory(&this->Header_File_System_Path);
       }
}

bool Header_File_Determiner::Is_Header(char * file_path){

     char inclusion_guard [] = "#ifndef";

     char header_add_h [] = ".h";

     char header_add_hpp [] = ".hpp";

     char source_file_ext [] = ".cpp";

     this->is_header_file = false;

     if(this->StringManager.CheckStringInclusion(file_path,source_file_ext)){

        return this->is_header_file;
     }

     this->is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_h);

     if(this->is_header_file){

        return this->is_header_file;
     }
     else{

          this->is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_hpp);

          if(this->is_header_file){

              return this->is_header_file;
          }
    }

    return this->is_header_file;
}

void Header_File_Determiner::Determine_Header_File_Directory(char * path){

     this->Clear_Pointer_Memory(&this->Header_File_Directory);

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

     this->Header_File_Directory = new char [5*dir_size];

     for(size_t i=0;i<dir_size;i++){

         this->Header_File_Directory[i] = path[i];
     }

     this->Header_File_Directory[dir_size] = '\0';
}

void Header_File_Determiner::Determine_Header_File_Name(char * path){

     this->Clear_Pointer_Memory(&this->Header_File_Name);

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

      this->Header_File_Name = new char [5*Header_File_Name_Size];

      int index = 0;

      for(size_t i=dir_size+1;i<file_path_size;i++){

          if( path[i] == '.'){

              break;
          }

          this->Header_File_Name[index] = path[i];

          index++;
      }

      this->Header_File_Name[index] = '\0';
}


void Header_File_Determiner::Determine_Header_File_System_Path(char * repo_dir,

     char * git_record_path, char operating_sis){

     this->Clear_Pointer_Memory(&this->Header_File_System_Path);

     size_t repo_dir_size   = strlen(repo_dir);

     size_t git_record_size = strlen(git_record_path);

     size_t path_size = repo_dir_size + git_record_size;

     int index = 0;

     this->Header_File_System_Path = new char [5*path_size];

     for(size_t i=0;i<repo_dir_size;i++){

         this->Header_File_System_Path[index] = repo_dir[i];

         if(operating_sis == 'w'){

            if(this->Header_File_System_Path[index] == '/'){

               this->Header_File_System_Path[index] = '\\' ;
            }
         }

         index++;
     }

     if(operating_sis == 'w'){

        if(repo_dir[repo_dir_size-1] != '\\' ){

           this->Header_File_System_Path[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

       if(repo_dir[repo_dir_size-1] != '/' ){

         this->Header_File_System_Path[index] = '/';

         index++;
       }
     }

     for(size_t i=0;i<git_record_size;i++){

         this->Header_File_System_Path[index] = git_record_path[i];

         if(operating_sis == 'w'){

            if(this->Header_File_System_Path[index] == '/'){

               this->Header_File_System_Path[index] = '\\' ;
             }
          }

         index++;
     }

     this->Header_File_System_Path[index] = '\0';
}

void Header_File_Determiner::Clear_Pointer_Memory(char ** pointer){

     if(*pointer != nullptr){

       delete [] *pointer;

       *pointer = nullptr;
     }
}

char * Header_File_Determiner::Get_Header_Directory(){

       return this->Header_File_Directory;
}

char * Header_File_Determiner::Get_Header_File_Name_Without_Ext(){

       return this->Header_File_Name;
}

char * Header_File_Determiner::Get_Header_File_System_Path(){

      return this->Header_File_System_Path;
}
