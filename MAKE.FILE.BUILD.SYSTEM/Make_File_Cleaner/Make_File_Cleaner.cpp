




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


#include "Make_File_Cleaner.hpp"

Make_File_Cleaner::Make_File_Cleaner(char * DesPath, char opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->opr_sis = opr_sis;

}


Make_File_Cleaner::~Make_File_Cleaner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Make_File_Cleaner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }
}

void Make_File_Cleaner::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr){

     this->Compiler_Data_Pointer = ptr;
}


void Make_File_Cleaner::Clear_Make_Files_Exist_On_Repo(){

     size_t Data_Size = this->Compiler_Data_Pointer->size();
     
     for(int i=0;i<Data_Size;i++){

         std::string dir = this->Compiler_Data_Pointer->at(i).src_sys_dir;

         this->Enumerator.List_Files_On_Directory(dir);

         int file_num = this->Enumerator.Get_File_Number();

         std::vector<std::string> *  file_list = this->Enumerator.Get_File_List();

         for(int k=0;k<file_num;k++){

             bool is_make_file  = this->Is_This_MakeFile(file_list->at(k));

             if(is_make_file){

                std::string file_path;

                this->Determine_File_Path(&file_path,dir,file_list->at(k));

                this->FileManager.Delete_File(file_path);
             }
         }
     }
}

void Make_File_Cleaner::Determine_File_Path(std::string * path, std::string dir, 

     std::string name){

     size_t dir_size  = dir.length();

     size_t name_size = name.length();

     for(size_t i=0;i<dir_size;i++){

         path->push_back(dir[i]);         
     }

     if(this->opr_sis == 'w'){

        if(path->back()!= '\\'){
        
           path->push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(path->back()!= '/'){
        
           path->push_back('\\');
        }
     }

     for(size_t i=0;i<name_size;i++){

         path->push_back(name[i]);
     }     
}

bool Make_File_Cleaner::Is_This_MakeFile(std::string file_name){

     this->Is_MakeFile = true;

     std::string make_ext = ".make";

     std::string file_ext;

     size_t ext_size = make_ext.length();

     size_t name_size = file_name.length();


     for(size_t i=name_size-ext_size;i<name_size;i++){

         file_ext.push_back(file_name[i]);
     }

     for(size_t i=0;i<ext_size;i++){

         if(make_ext[i] != file_ext[i]){

            this->Is_MakeFile = false;

            break;
         }
     }

     return this->Is_MakeFile;
}
