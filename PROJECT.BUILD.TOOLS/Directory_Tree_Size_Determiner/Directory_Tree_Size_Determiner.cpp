

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



#include "Directory_Tree_Size_Determiner.h"

Directory_Tree_Size_Determiner::Directory_Tree_Size_Determiner(){

    this->Directory_Tree_Size = 0;
}


Directory_Tree_Size_Determiner::~Directory_Tree_Size_Determiner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Directory_Tree_Size_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

     }
}

void Directory_Tree_Size_Determiner::Determine_Directory_Tree_Size(char * dir_path){

     Directory_Enumerator Enumerator;

     Enumerator.Find_Sub_Directories(dir_path);

     int sub_dir_num = Enumerator.Get_Directory_Number_In_Directory();

     this->Directory_Tree_Size = this->Directory_Tree_Size + sub_dir_num;

     for(int i=0;i<sub_dir_num;i++){

         std::string sub_dir = Enumerator.Get_Directory_List_Element(i);

         Directory_Enumerator Loop_Enumerator;

         

         size_t dir_size = sub_dir.size();

         char * sub_dir_cstr = new char [5*dir_size];

         for(size_t i=0;i<5*dir_size;i++){

             sub_dir_cstr[i] = '\0';
         }


         size_t index = 0;

         for(size_t i=0;i<sub_dir.size();i++){

             sub_dir_cstr[index] = sub_dir[i];

             index++;
         }

         sub_dir_cstr[index] = '\0';


         Loop_Enumerator.Find_Sub_Directories(sub_dir_cstr);

         delete [] sub_dir_cstr;

         int loop_sub_dir = Loop_Enumerator.Get_Directory_Number_In_Directory();

         Loop_Enumerator.Clear_Dynamic_Memory();

         if(loop_sub_dir > 0){

           this->Determine_Directory_Tree_Size(sub_dir_cstr);
         }
     }
}

int Directory_Tree_Size_Determiner::Get_Directory_Tree_Size(){

     return this->Directory_Tree_Size;
}
