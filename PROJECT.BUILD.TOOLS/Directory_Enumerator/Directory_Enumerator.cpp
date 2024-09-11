



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

#include "Directory_Enumerator.h"
#include <iostream>

Directory_Enumerator::Directory_Enumerator(){

     this->dir_path = nullptr;

     this->Directory_Number = 0;

     this->List_Index = 0;

     this->Memory_Delete_Condition = false;

     this->c_str = nullptr;
};


Directory_Enumerator::~Directory_Enumerator(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void Directory_Enumerator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_CString_Memory(&this->c_str);

         this->List_Index = 0;     
         
         if(!this->std_str.empty()){
       
            this->std_str.clear();

            this->std_str.shrink_to_fit();
         }

         this->Clear_Vector_Memory(this->File_List);

         this->Clear_Vector_Memory(this->Directory_List);
     }
}

void Directory_Enumerator::Find_Sub_Directories(char * Root_Dir_Path){

     this->Clear_Dynamic_Memory();

     this->Memory_Delete_Condition = false;

     this->Clear_Vector_Memory(this->Directory_List);

     this->Determine_Sub_Directories(Root_Dir_Path);
}


void Directory_Enumerator::Determine_Sub_Directories(char * Directory_Path){

     this->Memory_Delete_Condition = false;


     DIR * d;

     struct dirent * dir;


     d = opendir(Directory_Path);

     if (d!=NULL){

          while ((dir = readdir(d)) != NULL)
          {

              bool is_element = true; 

              if((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)){

                  is_element = false;
              }
              

              if(is_element){

                 DIR *sub_d;

                 char * path = nullptr;

                 this->Extract_Path(Directory_Path,dir->d_name,&path);


                 bool is_directory = false;

                 sub_d = opendir(path);

                 if( sub_d != NULL){

                    is_directory = true;

                    closedir(sub_d);
                 };

                 if(is_directory){

                    std::string str;

                    size_t path_size = strlen(path);

                    for(size_t i=0;i<path_size;i++){

                        str.push_back(path[i]);
                    }

                    str.shrink_to_fit();

                    this->Directory_List.push_back(str);

                    this->Determine_Sub_Directories(path);
                 }

                 delete [] path;
              }
          }

          closedir(d);

          this->Directory_List.shrink_to_fit();
     }
}



void Directory_Enumerator::Extract_Path(char * up_dir, char * name, char ** path){

     size_t up_dir_size = strlen(up_dir);

     size_t name_size = strlen(name);

     size_t path_size = up_dir_size + name_size;

     *path = new char [5*path_size];

     for(size_t i=0;i<5*path_size;i++){

         (*path)[i] = '\0';
     }

     size_t index=0;

     for(size_t i=0;i<up_dir_size;i++){

         (*path)[index] = up_dir[i];

         index++;
     }

     (*path)[index] = '/';

     index++;

     for(size_t i=0;i<name_size;i++){

         (*path)[index] = name[i];

         index++;
     }

     (*path)[index] = '\0';
}


void Directory_Enumerator::Receive_Directory_Path(char * Directory_Path,

     char ** dir_path){

     this->Memory_Delete_Condition = false;

     size_t dir_path_size = strlen(Directory_Path);

     *dir_path = new char [5*dir_path_size];

     for(size_t i=0;i<5*dir_path_size;i++){

         (*dir_path)[i] = '\0';
     }

     int index_counter = 0;

     for(size_t i=0;i<dir_path_size;i++){

         (*dir_path)[index_counter] = Directory_Path[i];

         index_counter++;
     }

     (*dir_path)[index_counter] = '\0';
}



void Directory_Enumerator::Find_Sub_Directory_Path(char * dir_root_path, char * dir_name,

     char ** sub_dir_path){

     size_t dir_root_path_size = strlen(dir_root_path);

     size_t dir_name_size = strlen(dir_name);

     size_t sub_dir_path_size = dir_root_path_size + dir_name_size;

     *sub_dir_path = new char [5*sub_dir_path_size];

     for(size_t i=0;i<5*sub_dir_path_size;i++){

         (*sub_dir_path)[i] = '\0';
     }

     int index_counter = 0;

     for(size_t i=0;i<dir_root_path_size;i++){

         (*sub_dir_path)[index_counter] = dir_root_path[i];

         index_counter++;
     }

     if((*sub_dir_path)[index_counter-1] != '/'){

        (*sub_dir_path)[index_counter] = '/';

        index_counter++;
     }

     for(size_t i=0;i<dir_name_size;i++){

        (*sub_dir_path)[index_counter] = dir_name[i] ;

        index_counter++;
     }

     (*sub_dir_path)[index_counter] = '\0';
}




void Directory_Enumerator::Find_Files_On_Directory(char * dir_path){

     this->Memory_Delete_Condition = false;
     
     this->Clear_Vector_Memory(this->File_List);

     this->List_Files_On_Directory(dir_path);
}



void Directory_Enumerator::List_Files_On_Directory(std::string dir_path){

     char * path = this->Convert_StdStr_CStr(dir_path);

     this->List_Files_On_Directory(path);
}


void Directory_Enumerator::List_Files_On_Directory(char * dir_path){

     DIR * d;

     struct dirent * dir;


     d = opendir(dir_path);

     if (d!=NULL){

          while ((dir = readdir(d)) != NULL)
          {

              bool is_element = true; 

              if((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)){

                  is_element = false;
              }
              

              if(is_element){

                 DIR *sub_d;

                 char * path = nullptr;

                 this->Extract_Path(dir_path,dir->d_name,&path);


                 bool is_directory = false;

                 sub_d = opendir(path);

                 if( sub_d != NULL){

                    is_directory = true;

                    closedir(sub_d);

                    this->List_Files_On_Directory(path);
                 };

                 if(!is_directory){

                    std::string str;

                    size_t path_size = strlen(path);

                    for(size_t i=0;i<path_size;i++){

                        str.push_back(path[i]);
                    }

                    str.shrink_to_fit();

                    this->File_List.push_back(str);

                    this->List_Files_On_Directory(path);
                 }

                 delete [] path;
              }
          }

          closedir(d);

          this->File_List.shrink_to_fit();
     }
}



char * Directory_Enumerator::Convert_StdStr_CStr(std::string string)
{

       this->Clear_CString_Memory(&this->c_str);

       size_t str_size = string.length();

       this->c_str = new char [2*str_size];

       for(size_t i=0;i<str_size;i++){
       
           this->c_str[i] = string[i];
       }

       this->c_str[str_size] = '\0';

       return this->c_str;
}

std::string Directory_Enumerator::Convert_CStr_StdStr(char * string) 
{
       if(!this->std_str.empty()){
       
           this->std_str.clear();

           this->std_str.shrink_to_fit();
       }

       size_t str_size = strlen(string);

       for(size_t i=0;i<str_size;i++){
       
           this->std_str.push_back(string[i]);
       
       }

       return this->std_str;
}

void Directory_Enumerator::Clear_CString_Memory(char ** ptr){

     if(*ptr != nullptr){
     
        delete [] *ptr;

        *ptr = nullptr;
     }
}

void Directory_Enumerator::Clear_Pointer_List(char *** ptr, int list_size)
{     
     if(*ptr != nullptr){

         for(int i=0;i<list_size;i++){

            if((*ptr)[i] != nullptr){
     
              delete [] (*ptr)[i];

              (*ptr)[i] = nullptr;
            }
         }

         delete [] (*ptr);
      }
}

void Directory_Enumerator::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         for(size_t i=0;i<vec.size();i++){

             if(!vec.at(i).empty()){

                 vec.at(i).clear();

                 vec.at(i).shrink_to_fit();
              }
          }

          vec.clear();

          vec.shrink_to_fit();
     }
}



 std::vector<std::string> * Directory_Enumerator::Get_Sub_Directory_List(){

     return &this->Directory_List;
 }


bool Directory_Enumerator::getStringEquality(){

     return this->isStringsEqual;
}


std::string Directory_Enumerator::Get_Directory_List_Element(int num) const {

     return this->Directory_List[num];
}


int Directory_Enumerator::Get_Directory_Number_In_Directory() const
{
   return this->Directory_List.size();
}

std::vector<std::string> * Directory_Enumerator::Get_File_List()
{
     return &this->File_List;
}

int Directory_Enumerator::Get_File_Number(){

     return this->File_List.size();
}
