
#include "Source_File_Determiner.h"

Source_File_Determiner::Source_File_Determiner(){

    this->File_Content = nullptr;

    this->File_Content_Size = 0;

    this->Is_This_Source_File = false;

    this->Source_File_Name = nullptr;

    this->File_Name_Witout_Ext = nullptr;

    this->Class_Function_Patern = nullptr;

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

          if(this->File_Name_Witout_Ext != nullptr){

             delete [] this->File_Name_Witout_Ext;

             this->File_Name_Witout_Ext = nullptr;
          }

          if(this->Class_Function_Patern != nullptr){

             delete [] this->Class_Function_Patern;

             this->Class_Function_Patern = nullptr;
          }
       }
}

bool Source_File_Determiner::Is_Source_File(char * file_path){

     char inclusion_guard [] = "#ifndef";

     char main_file_key [] = "main(";

     char header_add_h [] = ".h";

     char header_add_hpp [] = ".hpp";

     char source_file_ext [] = ".cpp";

     this->Is_This_Source_File = false;

     bool is_header = this->StringManager.CheckStringInclusion(file_path,header_add_h);

     if(is_header){

        this->Is_This_Source_File = false;

        return this->Is_This_Source_File;
     }
     else{

          is_header = this->StringManager.CheckStringInclusion(file_path,header_add_hpp);

          if(is_header){

            this->Is_This_Source_File = false;

            return this->Is_This_Source_File;
          }
     }


    this->Is_This_Source_File = false;

    this->Determine_File_Name_Without_Ext(file_path,'w');

    char * file_name = this->Get_File_Name_Witout_Ext();

    this->Determine_Class_Function_Pattern(file_name);

    char * decleration_pattern = this->Get_Class_Function_Pattern();

    bool is_this_main_file = false;

    if(this->StringManager.CheckStringInclusion(file_path,source_file_ext)){

       this->Read_File(file_path);

       for(int k=0;k<this->File_Content_Size;k++){

           this->Delete_Spaces_on_String(&this->File_Content[k]);

           this->Is_This_Source_File

            = this->StringManager.CheckStringInclusion(this->File_Content[k],decleration_pattern);

            if(this->Is_This_Source_File){

                return this->Is_This_Source_File;
            }

            is_this_main_file = this->StringManager.CheckStringInclusion(this->File_Content[k],main_file_key);

            if(is_this_main_file){

               this->Is_This_Source_File = false;

               return this->Is_This_Source_File;
            }

      }


      this->Is_This_Source_File

                  = this->StringManager.CheckStringInclusion(file_path,source_file_ext);

      if(this->Is_This_Source_File){

         return this->Is_This_Source_File;
      }
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

        if((path[i] == '/') || (path[i] == '\\')){

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

void Source_File_Determiner::Determine_File_Name_Without_Ext(char * path, char operating_sis){

     if(this->File_Name_Witout_Ext != nullptr){

        delete [] this->File_Name_Witout_Ext;

        this->File_Name_Witout_Ext = nullptr;
     }

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     size_t file_extention_start_point = file_path_size;


    for(size_t i=file_path_size;i>0;i--){

        if((path[i] == '/') || (path[i] == '\\')){

            break;
        }
        else{

              dir_size--;
        }
     }


     for(size_t i=file_path_size;i>0;i--){

         if(path[i] == '.'){

           break;
         }
            else{

                file_extention_start_point--;
          }

          if(file_extention_start_point <= dir_size){

             file_extention_start_point = dir_size;
          }
     }

     size_t file_name_size = 0;



     if(file_extention_start_point <= dir_size){

        file_name_size = file_path_size - dir_size; // It is the case in which the file does not have extenton
     }

     if(file_extention_start_point > dir_size){

        file_name_size = file_extention_start_point - dir_size;
     }

     this->File_Name_Witout_Ext = new char [5*file_name_size];

     int index = 0;

     size_t name_start_point = 0;

     if(dir_size != 0){

        name_start_point = dir_size +1;
     }

     for(size_t i=name_start_point;i<file_extention_start_point;i++){

         this->File_Name_Witout_Ext[index] = path[i];

         index++;
     }

     this->File_Name_Witout_Ext[index] = '\0';
}

void Source_File_Determiner::Determine_Class_Function_Pattern(char * file_name){

     if(this->Class_Function_Patern != nullptr){

        delete [] this->Class_Function_Patern;

        this->Class_Function_Patern = nullptr;
     }

     size_t file_name_size = strlen(file_name);

     this->Class_Function_Patern = new char [5*file_name_size];

     int index = 0;

     for(size_t i=0;i<file_name_size;i++){

         this->Class_Function_Patern[index] = file_name[i];

         index++;
     }

     this->Class_Function_Patern[index] = ':';

     index++;

     this->Class_Function_Patern[index] = ':';

     index++;

     this->Class_Function_Patern[index] = '\0';
}

void Source_File_Determiner::Delete_Spaces_on_String(char ** pointer){

     size_t string_size = strlen(*pointer);

     int remove_index = 0;

     for(size_t i=0;i<string_size;i++){

         if((*pointer)[i] == ' '){

            for(size_t k=i;k<string_size;k++){

               (*pointer)[k] = (*pointer)[k+1];
            }

            remove_index++;
         }
     }

     (*pointer)[string_size - remove_index+1] = '\0';
}

char * Source_File_Determiner::Get_Source_File_Name(){

       return this->Source_File_Name;
}

char * Source_File_Determiner::Get_File_Name_Witout_Ext(){

       return this->File_Name_Witout_Ext;
}

char * Source_File_Determiner::Get_Class_Function_Pattern(){

       return this->Class_Function_Patern;
}
