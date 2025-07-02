
/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Source_File_Determiner.h"

Source_File_Determiner::Source_File_Determiner()
{
    this->File_Content_Size = 0;

    this->Is_This_Source_File = false;

    this->Is_This_Main_File = false;

    this->FileManager.Receive_Operating_System('w');
}


Source_File_Determiner::~Source_File_Determiner()
{
    this->Clear_Dynamic_Memory();
}

void Source_File_Determiner::Clear_Dynamic_Memory()
{
     this->File_Content_Size = 0;

     this->Clear_Vector_Memory(&this->File_Content);

     this->Clear_String_Memory(&this->Source_File_Name);

     this->Clear_String_Memory(&this->Class_Function_Patern);

     this->Clear_String_Memory(&this->File_Name_Witout_Ext);

     this->StringManager.Clear_Dynamic_Memory();

     this->FileManager.Clear_Dynamic_Memory();
}

bool Source_File_Determiner::Is_Source_File(char * file_path){

     this->Clear_Dynamic_Memory();

     std::string std_srt_path;

     size_t path_size = strlen(file_path);

     for(size_t i=0;i<path_size;i++){

         std_srt_path.push_back(file_path[i]);
     }

     std::string inclusion_guard = "#ifndef";

     std::string main_file_key   = "main(";

     std::string header_add_h    = ".h";

     std::string header_add_hpp  = ".hpp";

     std::string source_file_ext_1  = ".cpp";

     std::string source_file_ext_2  = ".cc";



     std::string file_extention;

     bool is_there_file_ext = false;

     this->Extract_File_Extention(file_extention,file_path,is_there_file_ext);


     if(!is_there_file_ext){

         this->Is_This_Source_File = false;

         return this->Is_This_Source_File;
     }


     this->Is_This_Source_File = false;

     bool is_header = this->StringManager.CompareString(file_extention,header_add_h);

     if(is_header){

        this->Is_This_Source_File = false;

        return this->Is_This_Source_File;
     }
     else{

          is_header = this->StringManager.CompareString(file_extention,header_add_hpp);

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

    bool ext_chek_cond_1 = this->StringManager.CompareString(file_extention,source_file_ext_1);

    bool ext_chek_cond_2 = this->StringManager.CompareString(file_extention,source_file_ext_2);

    if(ext_chek_cond_1 || ext_chek_cond_2){

       this->Read_File(file_path);

       for(int k=0;k<this->File_Content_Size;k++){

           this->Delete_Spaces_on_String(&this->File_Content[k]);

           this->Is_This_Source_File

            = this->StringManager.CheckStringInclusion(this->File_Content[k],decleration_pattern);

            if(this->Is_This_Source_File){

                return this->Is_This_Source_File;
            }

            this->Is_This_Main_File = false;

            is_this_main_file = this->StringManager.CheckStringInclusion(this->File_Content[k],main_file_key);

            if(is_this_main_file){

               this->Is_This_Source_File = true;

               this->Is_This_Main_File = true;

               return this->Is_This_Source_File;
            }
      }


      this->Is_This_Source_File = ext_chek_cond_1 || ext_chek_cond_2;

      if(this->Is_This_Source_File){

         return this->Is_This_Source_File;
      }
    }

    return this->Is_This_Source_File;
}



bool Source_File_Determiner::Is_Source_File(std::string file_path){

     this->Clear_Dynamic_Memory();

     std::string inclusion_guard = "#ifndef";

     std::string main_file_key   = "main(";

     std::string header_add_h    = ".h";

     std::string header_add_hpp  = ".hpp";

     std::string source_file_ext_1  = ".cpp";

     std::string source_file_ext_2  = ".cc";

     std::string source_file_ext_3  = ".cxx";

     std::string source_file_ext_4   = ".c";




     this->Is_This_Source_File = false;

     std::string file_extention;

     bool is_there_file_ext = false;

     this->Extract_File_Extention(file_extention,file_path,is_there_file_ext);


     if(!is_there_file_ext){

         this->Is_This_Source_File = false;

         return this->Is_This_Source_File;
     }



     bool is_header = this->StringManager.CompareString(file_extention,header_add_h);

     if(is_header){

        this->Is_This_Source_File = false;

        return this->Is_This_Source_File;
     }
     else{

          is_header = this->StringManager.CompareString(file_extention,header_add_hpp);

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

    bool ext_chek_cond_1 = this->StringManager.CompareString(file_extention,source_file_ext_1);

    bool ext_chek_cond_2 = this->StringManager.CompareString(file_extention,source_file_ext_2);


    bool ext_chek_cond_3 = this->StringManager.CompareString(file_extention,source_file_ext_3);

    bool ext_chek_cond_4 = this->StringManager.CompareString(file_extention,source_file_ext_4);


    if(ext_chek_cond_1 || ext_chek_cond_2 || ext_chek_cond_3 || ext_chek_cond_4){

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

               this->Is_This_Source_File = true;

               return this->Is_This_Source_File;
            }
      }


      this->Is_This_Source_File = ext_chek_cond_1 || ext_chek_cond_2 || ext_chek_cond_3 || ext_chek_cond_4;

      if(this->Is_This_Source_File)
      {
         return this->Is_This_Source_File;
      }
    }

    return this->Is_This_Source_File;
}


void Source_File_Determiner::Extract_File_Extention(std::string & ext, std::string file_path, 

     bool & is_there_ext){

     size_t name_size   = file_path.length();
     size_t start_point = 0;

     is_there_ext = false;
     
     for(size_t i=name_size;i>0;i--){

         if(file_path[i] == '.'){

            is_there_ext = true;

            start_point=i;

            break;
         }
     }

     for(size_t i=start_point;i<name_size;i++){

         ext.push_back(file_path[i]);
     }

     ext.shrink_to_fit();     
}


bool Source_File_Determiner::Is_Main_File(std::string path){

     this->Is_This_Main_File = false;

     bool is_source_file = this->Is_Source_File(path);
     
     if(is_source_file){

         return this->Is_This_Main_File;
     }
     else{

          this->Is_This_Main_File = false;

          return this->Is_This_Main_File;
     }
}

bool Source_File_Determiner::Is_Main_File(char * path){

     bool is_source_file = this->Is_Source_File(path);
     
     if(is_source_file){

         return this->Is_This_Main_File;
     }
     else{

          this->Is_This_Main_File = false;

          return this->Is_This_Main_File;
     }
}



void Source_File_Determiner::Read_File(std::string path){

     this->Clear_Vector_Memory(&this->File_Content);

     this->FileManager.Clear_Dynamic_Memory();

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(Rf);


     this->File_Content_Size = 0;

     do {
          std::string file_line = this->FileManager.ReadLine();

          this->File_Content.push_back(file_line);

          this->File_Content_Size++;

     }while(!this->FileManager.Control_Stop_Condition());

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();
}

void Source_File_Determiner::Determine_Source_File_Name(std::string path){

     this->Clear_String_Memory(&this->Source_File_Name);

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

         this->Source_File_Name.push_back(path[i]);
     }
}

void Source_File_Determiner::Determine_File_Name_Without_Ext(std::string path)
{
     this->Clear_String_Memory(&this->File_Name_Witout_Ext);

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

        file_name_size = file_path_size - dir_size;

        // It is the case in which the file does not have extenton
     }

     if(file_extention_start_point > dir_size){

        file_name_size = file_extention_start_point - dir_size;
     }


     size_t name_start_point = 0;

     if(dir_size != 0){

        name_start_point = dir_size +1;
     }

     for(size_t i=name_start_point;i<file_extention_start_point;i++){

         this->File_Name_Witout_Ext.push_back(path[i]);
     }
}

void Source_File_Determiner::Determine_Class_Function_Pattern(std::string file_name)
{
     size_t file_name_size = file_name.length();

     this->Clear_String_Memory(&this->Class_Function_Patern);

     for(size_t i=0;i<file_name_size;i++)
     {
         this->Class_Function_Patern.push_back(file_name[i]);
     }
}

void Source_File_Determiner::Delete_Spaces_on_String(std::string * str)
{
     size_t string_size = str->length();

     bool search_cond = true;

     do{

         search_cond = false;

         for(size_t i=0;i<str->length();i++){

            if((*str)[i] == ' '){

              search_cond = true;

              str->erase(i,1);
            }
         }

     }while(search_cond);

     str->shrink_to_fit();
}



void Source_File_Determiner::Clear_Vector_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();
            it->shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void Source_File_Determiner::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();
         pointer->shrink_to_fit();
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
