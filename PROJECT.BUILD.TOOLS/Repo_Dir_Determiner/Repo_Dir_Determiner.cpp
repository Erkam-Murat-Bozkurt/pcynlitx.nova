
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



#include "Repo_Dir_Determiner.h"

Repo_Dir_Determiner::Repo_Dir_Determiner(){

   this->Memory_Delete_Condition = false;

   this->Repo_Dir = nullptr;

   this->Folder_Name = nullptr;
}

Repo_Dir_Determiner::Repo_Dir_Determiner(const Repo_Dir_Determiner & orig){

}

Repo_Dir_Determiner::~Repo_Dir_Determiner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Repo_Dir_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         delete [] this->Repo_Dir;

         this->Repo_Dir = nullptr;

         if(this->Folder_Name != nullptr){

            delete [] this->Folder_Name;
         }
     }
}


void Repo_Dir_Determiner::Determine_Repo_Dir(){

     char repo_name [] = "Pcynlitx.Web";

     char * upper_dir = nullptr;

     bool is_repo_dir = false;

     do{

         this->DirectoryManager.DetermineUpperDirectoryName();

         upper_dir = this->DirectoryManager.GetUpperDirectoryName();

         char * folder_name =  this->Extract_Folder_Name(upper_dir);

         is_repo_dir = this->StringManager.CheckStringInclusion(folder_name,repo_name);

         if(is_repo_dir){

             break;
         }
         else{

              this->DirectoryManager.ChangeDirectory(upper_dir);
         }

     }while(!is_repo_dir);

     size_t path_name_size = strlen(upper_dir);

     this->Repo_Dir = new char [5*path_name_size];

     for(size_t i=0;i<5*path_name_size;i++){  // The initialization of the dynamic array

         this->Repo_Dir[i] = '\0';
     }

     for(size_t i=0;i<path_name_size;i++){

        this->Repo_Dir[i] = upper_dir[i];
     }

     this->Repo_Dir[path_name_size] = '\0';
}


char * Repo_Dir_Determiner::Extract_Folder_Name(char * dir_name){

     if(this->Folder_Name != nullptr){

        delete [] this->Folder_Name;
     }

     size_t dir_name_size = strlen(dir_name);

     this->Folder_Name = new char [5*dir_name_size];

     size_t folder_start = 0;

     for(size_t i=dir_name_size;i>0;i--){

         if(dir_name[i] == '\\'){

            folder_start = i+1;

            break;
         }
     }

     size_t folder_name_size = dir_name_size - folder_start;

     int index = 0;

     for(size_t i=folder_start;i<dir_name_size;i++){

         this->Folder_Name[index] = dir_name[i];

         index++;
     }

     this->Folder_Name[index] = '\0';

     return this->Folder_Name;
}


char * Repo_Dir_Determiner::Get_Repo_Dir(){

      return this->Repo_Dir;
}
