

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

#include "Executable_MakeFile_ComConstructor.hpp"

Executable_MakeFile_ComConstructor::Executable_MakeFile_ComConstructor(){

   this->Memory_Delete_Condition = false;

   this->object_file_list = nullptr;

   this->header_file_list = nullptr;

}

Executable_MakeFile_ComConstructor::Executable_MakeFile_ComConstructor(const

     Executable_MakeFile_ComConstructor & orig){

}

Executable_MakeFile_ComConstructor::~Executable_MakeFile_ComConstructor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Executable_MakeFile_ComConstructor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){


     }
}

void Executable_MakeFile_ComConstructor::Receive_DepDeterminer(Executable_MakeFile_DepDeterminer * pointer){

     this->Dep_Determiner = pointer;
}


void Executable_MakeFile_ComConstructor::Construct_Compiler_Commands(){

     // Receiving the compiler data from the member objects

     this->warehouse_head_dir = this->Dep_Determiner->Get_Warehouse_Headers_Dir();

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();

     this->Data_Ptr_CString   = this->Dep_Determiner->Get_Compiler_Data_Pointer();

     this->Data_Size = this->Dep_Determiner->Get_Compiler_Data_Size();

     this->Determine_Object_File_List_Size();
}


void Executable_MakeFile_ComConstructor::Determine_Object_File_List_Size(){

     size_t list_size = 0;

     for(int i=0;i<this->Data_Size;i++){

         char * obj_name = this->Data_Ptr_CString[i].object_file_name;

         std::cout << "\n object name:" << obj_name;

         size_t obj_name_size = strlen(obj_name);

         list_size = list_size + obj_name_size;
     }

     std::cout << "\n list_size:" << list_size;
}

void Executable_MakeFile_ComConstructor::Add_String(char ** list, char * string, int * index){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         (*list)[(*index)] = string[i];

         (*index)++;
      }
  }

void Executable_MakeFile_ComConstructor::Place_String(std::string * str_pointer, char * string){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         (*str_pointer).append(1,string[i]) ;
     }

     (*str_pointer).append(1,'\0') ;
}

void Executable_MakeFile_ComConstructor::Place_CString(char ** str_pointer, std::string string){

     size_t string_size = string.length();

     *str_pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         (*str_pointer)[i] = string[i];
     }

     (*str_pointer)[string_size] = '\0' ;
}

void Executable_MakeFile_ComConstructor::Place_CString(char ** str_pointer, char * string){

     size_t string_size = strlen(string);

     *str_pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         (*str_pointer)[i] = string[i];
     }

     (*str_pointer)[string_size] = '\0' ;
}
