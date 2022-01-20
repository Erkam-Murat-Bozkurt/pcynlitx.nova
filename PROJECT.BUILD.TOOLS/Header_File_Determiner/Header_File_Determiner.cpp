
#include "Header_File_Determiner.h"

Header_File_Determiner::Header_File_Determiner(){

    this->File_Content = nullptr;

    this->File_Content_Size = 0;

    this->is_header_file = false;

    this->Header_File_Directory = nullptr;

}

Header_File_Determiner::Header_File_Determiner(const Header_File_Determiner & orig){


}

Header_File_Determiner::~Header_File_Determiner(){


}

void Header_File_Determiner::Clear_Dynamic_Memory(){

       if(!this->Memory_Delete_Condition){

           this->Memory_Delete_Condition = true;

           if(this->File_Content != nullptr){

              for(int i=0;i<this->File_Content_Size;i++){

                  delete [] this->File_Content[i];

                  this->File_Content[i] = nullptr;
              }

              delete [] this->File_Content;

              this->File_Content = nullptr;
           }

           if(this->Header_File_Directory != nullptr){

              delete [] this->Header_File_Directory;

              this->Header_File_Directory = nullptr;
           }
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
          else{

                this->Read_File(file_path);

                for(int k=0;k<this->File_Content_Size;k++){

                    this->is_header_file

                        = this->StringManager.CheckStringInclusion(this->File_Content[k],inclusion_guard);

                    if(this->is_header_file){

                       return this->is_header_file;
                    }
                }
          }

          return this->is_header_file;
    }
}


void Header_File_Determiner::Read_File(char * path){

     if(this->File_Content != nullptr){

        for(int i=0;i<this->File_Content_Size;i++){

            delete [] this->File_Content[i];

            this->File_Content[i] = nullptr;
        }

        delete [] this->File_Content;

        this->File_Content = nullptr;
     }

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(Rf);

     this->File_Content_Size = 0;

     do {

            std::string file_line = this->FileManager.ReadLine();

            this->File_Content_Size++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();


     this->File_Content = new char * [5*this->File_Content_Size];

     for(int i=0;i<this->File_Content_Size;i++){

         this->File_Content[i] = nullptr;
     }

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          char * string_line = this->FileManager.ReadLine_as_Cstring();

          size_t string_size = strlen(string_line);

          this->File_Content[index] = new char [5*string_size];

          for(size_t i=0;i<string_size;i++){

              this->File_Content[index][i] = string_line[i];
          }

          this->File_Content[index][string_size] ='\0';

          index++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();
}

void Header_File_Determiner::Determine_Header_File_Directory(char * path){

     if(this->Header_File_Directory != nullptr){

        delete [] this->Header_File_Directory;

        this->Header_File_Directory = nullptr;
     }

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

        if(path[i] == '/'){

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

char * Header_File_Determiner::Get_Header_Directory(){

       return this->Header_File_Directory;
}
