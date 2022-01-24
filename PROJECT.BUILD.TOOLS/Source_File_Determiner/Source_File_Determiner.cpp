
#include "Source_File_Determiner.h"

Source_File_Determiner::Source_File_Determiner(){

    this->File_Content = nullptr;

    this->File_Content_Size = 0;

    this->Is_This_Source_File = false;

    this->Source_File_Name = nullptr;

}

Source_File_Determiner::Source_File_Determiner(const Source_File_Determiner & orig){


}

Source_File_Determiner::~Source_File_Determiner(){


}

void Source_File_Determiner::Clear_Dynamic_Memory(){

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

           if(this->Source_File_Name != nullptr){

              delete [] this->Source_File_Name;

              this->Source_File_Name = nullptr;
           }
       }
}

bool Source_File_Determiner::Is_Source_File(char * file_path){

     char inclusion_guard [] = "#ifndef";

     char header_add_h [] = ".h";

     char header_add_hpp [] = ".hpp";

     char source_file_ext [] = ".cpp";

     this->Is_This_Source_File = false;

     bool is_header = this->StringManager.CheckStringInclusion(file_path,header_add_h);

     if(is_header){

        return this->Is_This_Source_File;
     }
     else{

          is_header = this->StringManager.CheckStringInclusion(file_path,header_add_hpp);

          if(is_header){

              return this->Is_This_Source_File;
          }
          else{

                this->Read_File(file_path);

                for(int k=0;k<this->File_Content_Size;k++){

                    is_header

                        = this->StringManager.CheckStringInclusion(this->File_Content[k],inclusion_guard);

                    if(is_header){

                       return this->Is_This_Source_File;
                    }
                }
          }
    }

    if(this->StringManager.CheckStringInclusion(file_path,source_file_ext)){

       this->Is_This_Source_File = true;

       return this->Is_This_Source_File;
    }

    return this->Is_This_Source_File;

}

void Source_File_Determiner::Read_File(char * path){

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

void Source_File_Determiner::Determine_Source_File_Name(char * path, char operating_sis){

     if(this->Source_File_Name != nullptr){

        delete [] this->Source_File_Name;

        this->Source_File_Name = nullptr;
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

     size_t file_name_size = file_path_size - dir_size;

     this->Source_File_Name = new char [5*file_name_size];

     int index = 0;

     for(size_t i=dir_size+1;i<file_path_size;i++){

         this->Source_File_Name[index] = path[i];

         index++;
     }

     this->Source_File_Name[index] = '\0';
}

char * Source_File_Determiner::Get_Source_File_Name(){

       return this->Source_File_Name;
}
