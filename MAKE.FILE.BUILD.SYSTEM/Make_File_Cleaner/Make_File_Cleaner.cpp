


/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Make_File_Cleaner.hpp"

Make_File_Cleaner::Make_File_Cleaner(char * DesPath, char opr_sis) :

  File_Lister(DesPath,opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->opr_sis = opr_sis;

   this->File_Lister.Determine_Git_Repo_Info();
}


Make_File_Cleaner::~Make_File_Cleaner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Make_File_Cleaner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->File_Lister.Clear_Dynamic_Memory();
     }
}



void Make_File_Cleaner::Clear_Make_Files_Exist_On_Repo(){

     int src_file_num = this->File_Lister.Get_Source_File_Number();

     for(int i=0;i<src_file_num;i++){

         std::string dir =  this->File_Lister.Get_Source_File_Directory(i);

         this->Enumerator.List_Files_On_Directory(dir);

         int file_num = this->Enumerator.Get_File_Number();

         std::vector<std::string> *  file_list = this->Enumerator.Get_File_List_As_StdStr();

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
