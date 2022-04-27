


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

Make_File_Cleaner::Make_File_Cleaner(){

   this->Memory_Delete_Condition = false;

}

Make_File_Cleaner::Make_File_Cleaner(const Make_File_Cleaner & orig){

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


void Make_File_Cleaner::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Des_Reader_Pointer = Des_Reader;
}

void Make_File_Cleaner::Receive_File_Lister(Project_Files_Lister * File_Lister){

     this->File_Lister_Pointer = File_Lister;
}

void Make_File_Cleaner::Clear_Make_Files_Exist_On_Repo(){

     int src_file_num = this->File_Lister_Pointer->Get_Source_File_Number();

     for(int i=0;i<src_file_num;i++){

         char * dir =  this->File_Lister_Pointer->Get_Source_File_Directory(i);

         this->Enumerator.List_Files_On_Directory(dir);

         int file_num = this->Enumerator.Get_File_Number();

         char **  file_list = this->Enumerator.Get_File_List();

         for(int i=0;i<file_num;i++){

             bool is_make_file  = this->Is_This_MakeFile(file_list[i]);

             if(is_make_file){

                char * file_path = nullptr;

                this->Determine_File_Path(&file_path,dir,file_list[i],'w');

                this->FileManager.Delete_File(file_path);
             }
         }
     }
}

void Make_File_Cleaner::Determine_File_Path(char ** path, char * dir, char * name,

     char operating_sis){

     size_t dir_size = strlen(dir);

     size_t name_size = strlen(name);

     size_t path_size = dir_size + name_size;

     *path = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<dir_size;i++){

         (*path)[index] = dir[i];

         index++;
     }

     if(operating_sis == 'w'){

        (*path)[index] = '\\';

        index++;
     }

     if(operating_sis == 'l'){

        (*path)[index] = '/';

        index++;
     }

     for(size_t i=0;i<name_size;i++){

        (*path)[index] = name[i];

        index++;
     }

     (*path)[index] = '\0';
}

bool Make_File_Cleaner::Is_This_MakeFile(char * file_name){

     this->Is_MakeFile = true;

     char make_ext [] = ".make";

     char file_ext [] = {'\0','\0','\0','\0','\0','\0'};

     size_t ext_size = strlen(make_ext);

     size_t name_size = strlen(file_name);

     int index = 5;

     for(size_t i=name_size;i>0;i--){

         file_ext[index] = file_name[i];

         index--;
     }

     for(size_t i=0;i<ext_size;i++){

         if(make_ext[i] != file_ext[i]){

            this->Is_MakeFile = false;

            break;
         }
     }

     return this->Is_MakeFile;
}
