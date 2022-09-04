

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

Executable_MakeFile_Builder::Executable_MakeFile_Builder(const Executable_MakeFile_Builder & orig){

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

     this->Des_Reader_Pointer = Des_Reader;

     this->warehouse_path = this->Des_Reader_Pointer->Get_Warehouse_Location();

     this->repo_dir = this->Des_Reader_Pointer->Get_Repo_Directory_Location();
}

void Executable_MakeFile_Builder::Receive_Git_Record_Data(Project_Files_Lister * Lister_Pointer){

     this->File_Lister_Pointer = Lister_Pointer;
}

void Executable_MakeFile_Builder::Build_MakeFile(){

     int src_num = this->File_Lister_Pointer->Get_Source_File_Number();

     for(int i=0;i<src_num;i++){

         char * src_file_name =

             this->File_Lister_Pointer->Get_Source_File_Name(i);

         std::cout << "\n src_file_name:" << src_file_name;

     }

     this->Collect_Make_File_Data();
}



void Executable_MakeFile_Builder::Collect_Make_File_Data(){

     this->Determine_Warehouse_Header_Dir('w');

     this->Determine_Warehouse_Object_Dir('w');

     this->Determine_Object_File_List();

     this->Determine_Header_File_List();
}

void Executable_MakeFile_Builder::Determine_Header_File_List(){

  int src_head_num = this->File_Lister_Pointer->Get_Source_File_Number();

  std::cout << "\n src_head_num:" << src_head_num;

  for(int k=0;k<src_head_num;k++){

      std::cout << "\n Included header file -" << k <<

      this->File_Lister_Pointer->Get_Class_File_Header_Name(k);
  }

  std::cout << "\n src_head_num:" << src_head_num;

  std::cin.get();

  int ind_head_num = this->File_Lister_Pointer->Get_Indenpendent_Header_Files_Number();

  for(int i=0;i<ind_head_num;i++){

      std::cout << "\n Independen header file - " << i << ":"

      << this->File_Lister_Pointer->Get_Independent_Header_File(i);
  }
}

void Executable_MakeFile_Builder::Determine_Object_File_List(){

     int src_num = this->File_Lister_Pointer->Get_Source_File_Number();

     size_t list_size = 0;

     for(int i=0;i<src_num;i++){

         char * src_file_name =

         this->File_Lister_Pointer->Get_Source_File_Name(i);

         size_t src_name_size = strlen(src_file_name);

         list_size = list_size + src_name_size;
     }

     this->object_file_list = new char [5*list_size];

     char object_file_add [] = ".o";

     int index = 0;

     for(int i=0;i<src_num;i++){

         char * src_name =

         this->File_Lister_Pointer->Get_Source_File_Name(i);

         this->Add_String(&this->object_file_list,src_name,&index);

         this->Add_String(&this->object_file_list,object_file_add,&index);

         this->object_file_list[index] = ' ';

         index++;
     }

     this->object_file_list[index] = '\0';
}


void Executable_MakeFile_Builder::Add_String(char ** list, char * string, int * index){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         (*list)[(*index)] = string[i];

         (*index)++;
     }
}

void Executable_MakeFile_Builder::Determine_Warehouse_Header_Dir(char operating_sis){

     char warehouse_word   [] = "WAREHOUSE";

     char header_directory [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_dir_size = strlen(header_directory);

     size_t wr_word_size  = strlen(warehouse_word);

     size_t path_size = warehouse_path_size + head_dir_size + wr_word_size;

     this->warehouse_head_dir = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

        this->warehouse_head_dir[index] = this->warehouse_path[i];

        index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '\\'){

           this->warehouse_head_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

         if(this->warehouse_head_dir[warehouse_path_size-1] != '/'){

            this->warehouse_head_dir[index] = '/';

            index++;
         }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_head_dir[index] = warehouse_word[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '\\'){

           this->warehouse_head_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '/'){

           this->warehouse_head_dir[index] = '/';

           index++;
        }
     }

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir[index] = header_directory[i];

         index++;
     }

     this->warehouse_head_dir[index] = '\0';

     std::cout << "\n this->warehouse_head_dir:" << this->warehouse_head_dir;
}


void Executable_MakeFile_Builder::Determine_Warehouse_Object_Dir(char operating_sis){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     char warehouse_word   [] = "WAREHOUSE";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_dir_size = strlen(object_directory);

     size_t wr_word_size  = strlen(warehouse_word);


     size_t path_size = warehouse_path_size

            + object_dir_size + wr_word_size;


     this->warehouse_obj_dir = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_obj_dir[index] = this->warehouse_path[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

            this->warehouse_obj_dir[index] = '/';

            index++;
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir[index] = warehouse_word[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

           this->warehouse_obj_dir[index] = '/';

           index++;
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir[index] = object_directory[i];

         index++;
     }

     this->warehouse_obj_dir[index] = '\0';

     std::cout << "\n this->warehouse_obj_dir:" << this->warehouse_obj_dir;
}
