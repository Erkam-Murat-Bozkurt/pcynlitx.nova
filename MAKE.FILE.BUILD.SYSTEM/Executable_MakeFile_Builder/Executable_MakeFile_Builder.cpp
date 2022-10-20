

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

#include "Executable_MakeFile_Builder.hpp"

Executable_MakeFile_Builder::Executable_MakeFile_Builder(){

   this->Memory_Delete_Condition = false;

   this->object_file_list = nullptr;

   this->header_file_list = nullptr;

}

Executable_MakeFile_Builder::Executable_MakeFile_Builder(const

     Executable_MakeFile_Builder & orig){

}

Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){


     }
}

void Executable_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Dep_Determiner.Receive_Descriptor_File_Reader(Des_Reader);
}

void Executable_MakeFile_Builder::Receive_Git_Record_Data(Git_File_List_Receiver * Pointer){

     this->Dep_Determiner.Receive_Git_Record_Data(Pointer);
}

void Executable_MakeFile_Builder::Receive_Source_File_Info(Project_Files_Lister * Pointer){

     this->Dep_Determiner.Receive_Source_File_Info(Pointer);
}

void Executable_MakeFile_Builder::Build_MakeFile(){

     this->Dep_Determiner.Determine_Dependencies();

     // Receiving the compiler data from the member objects

      this->warehouse_head_dir = this->Dep_Determiner.Get_Warehouse_Headers_Dir();

      this->warehouse_obj_dir  = this->Dep_Determiner.Get_Warehouse_Objetcs_Dir();

      this->warehouse_path     = this->Dep_Determiner.Get_Warehouse_Path();

      this->Data_Ptr_CString   = this->Dep_Determiner.Get_Compiler_Data_Pointer();

      std::cout << "\n WAREHOUSE HEADER DIR:" << this->warehouse_head_dir;

      std::cout << "\n WAREHOUSE OBJECT DIR:" << this->warehouse_obj_dir;

      std::cout << "\n WAREHOUSE PATH      :" << this->warehouse_path;

      this->Print_Compiler_Orders();
}


void Executable_MakeFile_Builder::Print_Compiler_Orders(){

     int head_number = this->Dep_Determiner.Get_Compiler_Data_Size();

     for(int i=0;i<head_number;i++){

         std::cout << "\n\n";

         std::cout << "\n --------------------------------------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Data_Ptr_CString[i].header_name;

         std::cout << "\n PRIORITY:"

         <<  this->Data_Ptr_CString[i].priority;

         std::cout << "\n INCLUSION NUMBER:"

         <<  this->Data_Ptr_CString[i].inclusion_number;

         std::cout << "\n\n";
     }
}


  void Executable_MakeFile_Builder::Add_String(char ** list, char * string, int * index){

       size_t string_size = strlen(string);

       for(size_t i=0;i<string_size;i++){

           (*list)[(*index)] = string[i];

           (*index)++;
       }
  }

  void Executable_MakeFile_Builder::Place_String(std::string * str_pointer, char * string){

       size_t string_size = strlen(string);

       for(size_t i=0;i<string_size;i++){

           (*str_pointer).append(1,string[i]) ;
       }

       (*str_pointer).append(1,'\0') ;
  }

  void Executable_MakeFile_Builder::Place_CString(char ** str_pointer, std::string string){

       size_t string_size = string.length();

       *str_pointer = new char [5*string_size];

       for(size_t i=0;i<string_size;i++){

           (*str_pointer)[i] = string[i];
       }

       (*str_pointer)[string_size] = '\0' ;
  }

  void Executable_MakeFile_Builder::Place_CString(char ** str_pointer, char * string){

       size_t string_size = strlen(string);

       *str_pointer = new char [5*string_size];

       for(size_t i=0;i<string_size;i++){

           (*str_pointer)[i] = string[i];
       }

       (*str_pointer)[string_size] = '\0' ;
  }
