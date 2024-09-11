

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Source_File_Processor.hpp"

Source_File_Processor::Source_File_Processor()
{
    this->Is_This_Source_File = false;
}


Source_File_Processor::~Source_File_Processor()
{
    this->Clear_Dynamic_Memory();
}

void Source_File_Processor::Clear_Dynamic_Memory()
{
     this->Clear_String_Memory(&this->Source_File_Name);

     this->Clear_String_Memory(&this->Class_Function_Patern);

     this->Clear_String_Memory(&this->File_Name_Witout_Ext);

     this->StringManager.Clear_Dynamic_Memory();
}


void Source_File_Processor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


void Source_File_Processor::Extract_File_Extention(std::string & ext, std::string file_path, 

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


void Source_File_Processor::Determine_Source_File_Name(std::string path){

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

void Source_File_Processor::Determine_File_Name_Without_Ext(char * path){

     std::string file_path;

     size_t path_size = strlen(path);

     for(size_t i=0;i<path_size;i++){
     
         file_path.push_back(path[i]);
     }

     file_path.shrink_to_fit();

     this->Determine_File_Name_Without_Ext(file_path);
}


void Source_File_Processor::Determine_File_Name_Without_Ext(std::string path)
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

void Source_File_Processor::Determine_Class_Function_Pattern(std::string file_name)
{
     size_t file_name_size = file_name.length();

     this->Clear_String_Memory(&this->Class_Function_Patern);

     for(size_t i=0;i<file_name_size;i++)
     {
         this->Class_Function_Patern.push_back(file_name[i]);
     }

     std::string name_space_opr = "::";

     size_t opr_size = name_space_opr.length();

     for(size_t i=0;i<opr_size;i++){
     
         this->Class_Function_Patern.push_back(name_space_opr[i]);
     }

     this->Class_Function_Patern.shrink_to_fit();
}

void Source_File_Processor::Delete_Spaces_on_String(std::string * str)
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



const std::vector<std::string> * Source_File_Processor::Get_File_Include_Declerations(char * path) const
{
     std::string std_path;

     size_t path_size = strlen(path);

     for(size_t i=0;i<path_size;i++){
     
         std_path.push_back(path[i]);
     }

     std_path.shrink_to_fit();


     const FileData * Data = this->Code_Rdr->Find_File_Data_From_Path(std_path);

     return  &Data->include_declerations;   
}


const std::vector<std::string> * Source_File_Processor::Get_File_Include_Declerations(std::string path) const
{

     const FileData * Data = this->Code_Rdr->Find_File_Data_From_Path(path);

     return  &Data->include_declerations; 
}

void Source_File_Processor::Clear_Vector_Memory(std::vector<std::string> * pointer){

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

void Source_File_Processor::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();
         pointer->shrink_to_fit();
     }
}


std::string Source_File_Processor::Get_Source_File_Name(){

       return this->Source_File_Name;
}

std::string Source_File_Processor::Get_File_Name_Witout_Ext(){

       return this->File_Name_Witout_Ext;
}

std::string Source_File_Processor::Get_Class_Function_Pattern(){

       return this->Class_Function_Patern;
}
