

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

        this->Memory_Delete_Condition = true;

        delete [] this->header_file_list;

        delete [] this->object_file_list;

        this->Dependency_Selector.Clear_Dynamic_Memory();
     }
}

void Executable_MakeFile_ComConstructor::Receive_DepDeterminer(Executable_MakeFile_DepDeterminer * pointer){

     this->Dep_Determiner = pointer;
}

void Executable_MakeFile_ComConstructor::Receice_DataCollector(Executable_MakeFile_DataCollector * pointer){

     this->Data_Collector = pointer;
}

void Executable_MakeFile_ComConstructor::Construct_Compiler_Commands(char * main_file_path){

     // Receiving the compiler data from the member objects

     this->warehouse_head_dir = this->Dep_Determiner->Get_Warehouse_Headers_Dir();

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();

     this->Data_Ptr_CString   = this->Dep_Determiner->Get_Compiler_Data_Pointer();

     this->Data_Size = this->Dep_Determiner->Get_Compiler_Data_Size();

     this->Dependency_Selector.Receive_Executable_MakeFile_DataCollector(this->Data_Collector);

     this->Dependency_Selector.Determine_Source_File_Dependencies(main_file_path);

     this->Header_Dependency_List =  this->Dependency_Selector.Get_Header_Dependency_List();

     this->Set_Header_File_Priorities();

     this->Re_Order_Header_Files();

     this->Determine_List_Sizes();

     this->Construct_Header_File_List();

     this->Construct_Object_File_List();
}

void Executable_MakeFile_ComConstructor::Set_Header_File_Priorities(){

     int list_size = this->Dependency_Selector.Get_Dependency_List_Size();

     for(int i=0;i<list_size;i++){

         for(int k=0;k<this->Data_Size;k++){

             char * repo_header =  this->Data_Ptr_CString[k].repo_path;

             char * list_header = this->Dependency_Selector.Get_Dependent_Header_Path(i);

             bool is_equal = this->CharOpr.CompareString(repo_header,list_header);

             if(is_equal){

                this->Header_Dependency_List[i].priority

                = this->Data_Ptr_CString[k].priority;

                break;
             }
         }

         char * path = this->Header_Dependency_List[i].repo_warehouse_path;

         int priority = this->Header_Dependency_List[i].priority;
     }
}

void Executable_MakeFile_ComConstructor::Re_Order_Header_Files(){

     int list_size = this->Dependency_Selector.Get_Dependency_List_Size();

     for(int i=0;i<list_size;i++){

        for(int j=i;j<list_size;j++){

          int dep_i = this->Header_Dependency_List[i].priority;

          int dep_j = this->Header_Dependency_List[j].priority;

          Header_Dependency temp;

          if( dep_i < dep_j){

              temp  = this->Header_Dependency_List[j];

              this->Header_Dependency_List[j] = this->Header_Dependency_List[i];

              this->Header_Dependency_List[i] = temp;
           }
       }
   }
}

void Executable_MakeFile_ComConstructor::Determine_List_Sizes(){

     size_t header_number = this->Dependency_Selector.Get_Dependency_List_Size();

     size_t list_size = 0;

     for(int i=0;i<header_number;i++){

         char * head_name = this->Header_Dependency_List[i].Header_Name;

         size_t head_name_size = strlen(head_name);

         list_size = list_size + head_name_size;
     }

     this->header_file_list = new char [5*list_size];

     this->object_file_list = new char [5*list_size];
}

void Executable_MakeFile_ComConstructor::Construct_Header_File_List(){

     size_t list_size = this->Dependency_Selector.Get_Dependency_List_Size();

     int index = 0;

     char space [] = " ";

     char new_line [] = "\n";

     char tab_char [] = "\t";

     char include_command [] = "-include";

     char slash [] = "\\";

     for(int i=0;i<list_size;i++){

         char * header_name = this->Header_Dependency_List[i].Header_Name;

         this->Add_String(&this->header_file_list,include_command,&index);

         this->Add_String(&this->header_file_list,space,&index);

         this->Add_String(&this->header_file_list,header_name,&index);

         this->Add_String(&this->header_file_list,space,&index);

         this->Add_String(&this->header_file_list,slash,&index);

         this->Add_String(&this->header_file_list,new_line,&index);

         this->Add_String(&this->header_file_list,tab_char,&index);
     }

     this->header_file_list[index-2] = '\0';
}

void Executable_MakeFile_ComConstructor::Construct_Object_File_List(){

     size_t list_size = this->Dependency_Selector.Get_Dependency_List_Size();;

     int index = 0;

     char space [] = " ";

     char new_line [] = "\n";

     char tab_char [] = "\t";

     char slash [] = "\\";

     for(int i=0;i<list_size;i++){

         char * header_name = this->Header_Dependency_List[i].Header_Name;

         char * obj_name = nullptr;

         this->Determine_Object_File_Name(&obj_name,header_name);

         if(obj_name != nullptr){

            this->Add_String(&this->object_file_list,obj_name,&index);

            this->Add_String(&this->object_file_list,space,&index);

            this->Add_String(&this->object_file_list,space,&index);

            this->Add_String(&this->object_file_list,slash,&index);

            this->Add_String(&this->object_file_list,new_line,&index);

            this->Add_String(&this->object_file_list,tab_char,&index);
         }

         delete [] obj_name;
     }
}

void Executable_MakeFile_ComConstructor::Determine_Object_File_Name(char ** obj_name, char * header)
{
     size_t name_size = strlen(header);

     char file_extention [] = ".obj";

     size_t extention_size = strlen(file_extention);

     *obj_name = new char [5*name_size];

     int index = 0;

     for(size_t i=0;i<name_size;i++){

        if(header[i] == '.'){

           break;
        }
        else{

              (*obj_name)[index] = header[i];

              index++;
        }
     }

     for(size_t i=0;i<extention_size;i++){

        (*obj_name)[index] = file_extention[i];

        index++;
     }

     (*obj_name)[index] = '\0';
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


char * Executable_MakeFile_ComConstructor::Get_Object_File_List(){

       return this->object_file_list;
}

char * Executable_MakeFile_ComConstructor::Get_Header_File_List(){

       return this->header_file_list;
}
