
#include "Source_File_Determiner.h"

Source_File_Determiner::Source_File_Determiner(){

    this->File_Content_Size = 0;

    this->Is_This_Source_File = false;

    this->Source_File_Name = "";

    this->File_Name_Witout_Ext = "";

    this->Class_Function_Patern = "";

    this->Memory_Delete_Condition = true;

}


Source_File_Determiner::~Source_File_Determiner(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
}

void Source_File_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        if(!this->File_Content.empty()){

           this->File_Content.clear();
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

    this->Determine_File_Name_Without_Ext(file_path);

    std::string file_name = this->Get_File_Name_Witout_Ext();

    this->Determine_Class_Function_Pattern(file_name);

    std::string decleration_pattern = this->Get_Class_Function_Pattern();

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

void Source_File_Determiner::Read_File(std::string path){

     if(!this->File_Content.empty()){

        this->File_Content.clear();
     }

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(Rf);

     this->Memory_Delete_Condition = false;

     this->File_Content_Size = 0;

     do {

            std::string file_line = this->FileManager.ReadLine();

            this->File_Content.push_back(file_line);

            this->File_Content_Size++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();
}

void Source_File_Determiner::Determine_Source_File_Name(std::string path){

     this->Source_File_Name = "";

     size_t file_path_size = path.length();

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

     int index = 0;

     for(size_t i=dir_size+1;i<file_path_size;i++){

         this->Source_File_Name.append(1,path[i]);
     }
}

void Source_File_Determiner::Determine_File_Name_Without_Ext(std::string path){

     this->File_Name_Witout_Ext ="";

     size_t file_path_size = path.length();

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

     this->File_Name_Witout_Ext = "";

     size_t name_start_point = 0;

     if(dir_size != 0){

        name_start_point = dir_size +1;
     }

     for(size_t i=name_start_point;i<file_extention_start_point;i++){

         this->File_Name_Witout_Ext.append(1,path[i]);
     }


}

void Source_File_Determiner::Determine_Class_Function_Pattern(std::string file_name)
{
     size_t file_name_size = file_name.length();

     this->Class_Function_Patern = "";

     for(size_t i=0;i<file_name_size;i++){

         this->Class_Function_Patern.append(1,file_name[i]);
     }
}

void Source_File_Determiner::Delete_Spaces_on_String(std::string * pointer){

     size_t string_size = pointer->length();

     int remove_index = 0;

     for(size_t i=0;i<string_size;i++){

         if((*pointer)[i] == ' '){

            for(size_t k=i;k<string_size;k++){

               (*pointer)[k] = (*pointer)[k+1];
            }

            remove_index++;
         }
     }

     for(int i=0;i<remove_index+1;i++){

        pointer->pop_back();
     }
}

std::string Source_File_Determiner::Get_Source_File_Name(){

       return this->Source_File_Name;
}

std::string Source_File_Determiner::Get_File_Name_Witout_Ext(){

       return this->File_Name_Witout_Ext;
}

std::string Source_File_Determiner::Get_Class_Function_Pattern(){

       return this->Class_Function_Patern;
}
