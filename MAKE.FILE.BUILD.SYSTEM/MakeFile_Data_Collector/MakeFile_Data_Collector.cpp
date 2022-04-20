

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

#include "MakeFile_Data_Collector.hpp"

MakeFile_Data_Collector::MakeFile_Data_Collector(){

   this->Memory_Delete_Condition = false;

   this->Compiler_System_Command = nullptr;

   this->Object_File_Name = nullptr;

   this->Source_File_Name_With_Ext = nullptr;

   this->Included_Header_Files = nullptr;

   this->Dependency_Code_Line = nullptr;

   this->Header_File_Directory = nullptr;

   this->Make_File_Name = nullptr;

   this->warehouse_head_dir = nullptr;

   this->warehouse_obj_dir = nullptr;

   this->Header_File_Exact_Path = nullptr;

   this->Header_File_Name_With_Ext = nullptr;

   this->Included_Header_Files_Number = 0;
}

MakeFile_Data_Collector::MakeFile_Data_Collector(const MakeFile_Data_Collector & orig){

}

MakeFile_Data_Collector::~MakeFile_Data_Collector(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void MakeFile_Data_Collector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Pointer_Memory(&this->Source_File_Name_With_Ext);

         this->Clear_Pointer_Memory(&this->Object_File_Name);

         this->Clear_Pointer_Memory(&this->Compiler_System_Command);

         if(this->Included_Header_Files != nullptr){

            for(int i=0;i<this->Included_Header_Files_Number;i++){

                this->Clear_Pointer_Memory(&(this->Included_Header_Files[i]));
            }

            delete [] this->Included_Header_Files;

            this->Included_Header_Files = nullptr;

            this->Included_Header_Files_Number = 0;
         }

         this->Clear_Pointer_Memory(&this->Dependency_Code_Line);

         //this->Clear_Pointer_Memory(&this->Header_File_Directory);

         this->Clear_Pointer_Memory(&this->Make_File_Name);

         this->Clear_Pointer_Memory(&this->warehouse_head_dir);

         this->Clear_Pointer_Memory(&this->warehouse_obj_dir);

         this->Clear_Pointer_Memory(&this->Header_File_Exact_Path);
     }
}

void MakeFile_Data_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader_Pointer = Pointer;

     this->warehouse_path = this->Des_Reader_Pointer->Get_Warehouse_Location();

     this->repo_dir = this->Des_Reader_Pointer->Get_Repo_Directory_Location();
}


void MakeFile_Data_Collector::Collect_Make_File_Data(Project_Files_Lister * Pointer, int git_index){

     this->Determine_Warehouse_Header_Dir('w');

     this->Determine_Warehouse_Object_Dir('w');

     this->Receive_Git_Record_Data(Pointer,git_index);

     this->Collect_Header_Files_Information();

     this->Determine_Compiler_System_Command();

     this->Find_Object_File_Name();

     this->Determine_Dependency_Code_Line();

     this->Determine_Make_File_Name();
}

void MakeFile_Data_Collector::Receive_Git_Record_Data(Project_Files_Lister * Pointer, int git_index){

     this->File_Lister_Pointer  = Pointer;

     this->Git_Record_Index = git_index;

     this->Source_File_Name

     = this->File_Lister_Pointer->Get_Source_File_Name(git_index);

     this->Source_File_Name_With_Ext

     = this->File_Lister_Pointer->Get_Source_File_Name_With_Ext(git_index);

     this->Source_File_Git_Recort_Path

     = this->File_Lister_Pointer->Get_Source_File_Git_Record_Path(git_index);

     this->Source_File_Directory

     = this->File_Lister_Pointer->Get_Source_File_Directory(git_index);

     this->Header_File_Directory

     = this->File_Lister_Pointer->Get_Source_File_Directory(git_index);
}

void MakeFile_Data_Collector::Determine_Warehouse_Header_Dir(char operating_sis){

     char header_directory [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_dir_size = strlen(header_directory);

     size_t path_size = warehouse_path_size + head_dir_size;

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

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir[index] = header_directory[i];

         index++;
     }

     this->warehouse_head_dir[index] = '\0';
}

void MakeFile_Data_Collector::Determine_Warehouse_Object_Dir(char operating_sis){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_dir_size = strlen(object_directory);

     size_t path_size = warehouse_path_size + object_dir_size;

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

            this->warehouse_head_dir[index] = '/';

            index++;
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir[index] = object_directory[i];

         index++;
     }

     this->warehouse_obj_dir[index] = '\0';
}

void MakeFile_Data_Collector::Collect_Header_Files_Information(){

     this->Receive_Included_Header_Files_Number();

     this->Initialize_Header_Data_Pointers();

     this->Receive_Header_Files_Data();
}

void MakeFile_Data_Collector::Receive_Included_Header_Files_Number(){

    this->Included_Header_Files_Number

    = this->File_Lister_Pointer->Get_Source_File_Include_File_Number(this->Git_Record_Index);
}

void MakeFile_Data_Collector::Initialize_Header_Data_Pointers(){

      this->Included_Header_Directories

      = new char * [5*this->Included_Header_Files_Number];


      this->Included_Header_Files

      = new char * [5*this->Included_Header_Files_Number];


      this->Included_Header_Files_System_Paths

      = new char * [5*this->Included_Header_Files_Number];


      this->Included_Header_Files_Git_Record_Paths

      = new char * [5*this->Included_Header_Files_Number];


      this->Included_Header_Files_Git_Record_Dir

      = new char * [5*this->Included_Header_Files_Number];

      for(int i=0;i<5*this->Included_Header_Files_Number;i++){

          this->Included_Header_Directories[i] = nullptr;

          this->Included_Header_Files[i] = nullptr;

          this->Included_Header_Files_System_Paths[i] = nullptr;

          this->Included_Header_Files_Git_Record_Paths[i] = nullptr;

          this->Included_Header_Files_Git_Record_Dir[i] = nullptr;
      }
}

void MakeFile_Data_Collector::Receive_Header_Files_Data(){

     this->Receive_Source_File_Header_Directory();

     this->Receive_Source_File_Header_System_Path();

     this->Receive_Source_File_Header_Git_Record_Path();

     this->Receive_Header_File_Name();
}

void MakeFile_Data_Collector::Receive_Source_File_Header_Directory(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         char * dir = nullptr;

         dir = this->File_Lister_Pointer->Get_Source_File_Header_Directory(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Directories[i]),dir);
     }
}

void MakeFile_Data_Collector::Receive_Source_File_Header_System_Path(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         char * path = nullptr;

         path = this->File_Lister_Pointer->Get_Source_File_Header_System_Path(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Files_System_Paths[i]),path);
     }
}

void MakeFile_Data_Collector::Receive_Source_File_Header_Git_Record_Path(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         char * path = nullptr;

         path = this->File_Lister_Pointer->Get_Source_File_Header_Git_Record_Path(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Files_Git_Record_Paths[i]),path);
     }
}


void MakeFile_Data_Collector::Receive_Source_File_Header_Git_Record_Dir(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         char * dir = nullptr;

         dir = this->File_Lister_Pointer->Get_Source_File_Header_Git_Record_Dir(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Files_Git_Record_Dir[i]),dir);
     }
}

void MakeFile_Data_Collector::Receive_Header_File_Name(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         char * name = nullptr;

         name = this->File_Lister_Pointer->Get_Source_File_Header(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Files[i]),name);
     }
}

void MakeFile_Data_Collector::Find_Object_File_Name(){

     size_t Source_File_Name_Size = strlen(this->Source_File_Name);

     this->Object_File_Name = new char [5*Source_File_Name_Size];

     int index = 0;

     for(int i=0;i<Source_File_Name_Size;i++){

         this->Object_File_Name[index] = this->Source_File_Name[i];

         index++;
     }

     this->Object_File_Name[index] = '.';

     index++;

     this->Object_File_Name[Source_File_Name_Size+1] = 'o';

     index++;

     this->Object_File_Name[Source_File_Name_Size+2] = '\0';
}

void MakeFile_Data_Collector::Determine_Make_File_Name(){

     char make_file_extention [] = ".make";

     size_t class_name_size = strlen(this->Source_File_Name);

     size_t extention_size = strlen(make_file_extention);

     size_t file_name_size = class_name_size + extention_size;

     this->Make_File_Name = new char [5*file_name_size];

     int index = 0;

     for(size_t i=0;i<class_name_size;i++){

         this->Make_File_Name[index] = this->Source_File_Name[i];

         index++;
     }

     for(size_t i=0;i<extention_size;i++){

         this->Make_File_Name[index] = make_file_extention[i];

         index++;
     }

     this->Make_File_Name[index] = '\0';
}

void MakeFile_Data_Collector::Determine_Compiler_System_Command(){

     char compiler_input_command [] = "g++ -Wall -c -std=c++17";

     char Include_Character [] = "-I";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(PROJECT_HEADERS_LOCATION)";

     char Source_Location [] ="$(SOURCE_LOCATION)";

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t Include_Directory_Name_Size = strlen(this->Header_File_Directory);

     size_t Source_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Header_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Current_Directory_Name_Size = strlen(Current_Directory);

     int Included_Header_Files_Name_Size = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         Included_Header_Files_Name_Size = Included_Header_Files_Name_Size

          + strlen(this->Included_Header_Files[i]);
     }

     size_t compiler_input_command_size = strlen(compiler_input_command);

     size_t compiler_command_size = Include_Directory_Name_Size + Current_Directory_Name_Size +

                                    Header_File_Name_Size + Source_File_Name_Size +

                                    compiler_input_command_size +

                                    + Included_Header_Files_Name_Size;

     this->Compiler_System_Command = new char [10*compiler_command_size];

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     this->Place_Information(&this->Compiler_System_Command,compiler_input_command,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     this->Place_Information(&this->Compiler_System_Command,Include_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Headers_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Include_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     int  included_dir_num = this->Des_Reader_Pointer->Get_Include_Directory_Number();

     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         char * included_dir = this->Des_Reader_Pointer->Get_Include_Directories()[i];

         char * dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Compiler_System_Command,Include_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,include_dir_symbol,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,dir_index,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,makro_end,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


         if(((sizer >= 4) && (i!=(included_dir_num -1)))){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,this->Source_File_Name_With_Ext,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);



     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     // The include commands definition

     sizer = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,this->Included_Header_Files[i],&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }

     this->Compiler_System_Command[index_counter] = '\0';
}


void MakeFile_Data_Collector::Determine_Dependency_Code_Line(){

     char double_quotes [] = " : ";

     char space [] = " ";

     size_t Object_File_Name_Size = strlen(this->Object_File_Name);

     size_t Header_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Source_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Included_Header_Files_Name_Size = 0;


     for(int i=0;i<this->Included_Header_Files_Number;i++){

        Included_Header_Files_Name_Size = Included_Header_Files_Name_Size +

          strlen(this->Included_Header_Files[i]);
     }


     size_t Code_Line_Size = Object_File_Name_Size + Source_File_Name_Size +

                          Header_File_Name_Size + Included_Header_Files_Name_Size;

     this->Dependency_Code_Line =  new char [10*Code_Line_Size];

     int index_counter = 0;

     int  sizer = 0;

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     this->Place_Information(&this->Dependency_Code_Line,this->Object_File_Name,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,double_quotes,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Source_File_Name_With_Ext,&index_counter);


     this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);


     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

         this->Place_Information(&this->Dependency_Code_Line,this->Included_Header_Files[i],&index_counter);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);

            sizer = 0;
         }
     }

     this->Dependency_Code_Line[index_counter] = '\0';
}

void MakeFile_Data_Collector::Place_Information(char ** Pointer,

     char * Information, int * index_counter){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         (*Pointer)[(*index_counter)] = Information[i];

         (*index_counter)++;
     }
 }

 void MakeFile_Data_Collector::Place_String(char ** pointer, char * string){

     size_t string_size = strlen(string);

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         (*pointer)[i] = string[i];
     }

     (*pointer)[string_size] = '\0';
 }

 void MakeFile_Data_Collector::Clear_Pointer_Memory(char ** Pointer){

      if(*Pointer != nullptr){

          delete [] *Pointer;

          *Pointer = nullptr;
      }
 }

 char * MakeFile_Data_Collector::Get_Source_File_Name(){

       return this->Source_File_Name;
 }

 char * MakeFile_Data_Collector::Get_Make_File_Name(){

        return this->Make_File_Name;
 }

 char * MakeFile_Data_Collector::Get_Compiler_System_Command(){

       return this->Compiler_System_Command;
 }

 char * MakeFile_Data_Collector::Get_Dependency_Code_Line(){

       return this->Dependency_Code_Line;
 }

 char * MakeFile_Data_Collector::Get_Object_File_Name(){

       return this->Object_File_Name;
 }

 char * MakeFile_Data_Collector::Get_Source_File_Name_With_Extention(){

       return this->Source_File_Name_With_Ext;
 }

 char ** MakeFile_Data_Collector::Get_Included_Header_Files(){

        return this->Included_Header_Files;
 }

 char * MakeFile_Data_Collector::Get_Repo_Dir(){

        return this->repo_dir;
 }

 char * MakeFile_Data_Collector::Get_Warehouse_Header_Dir(){

        return this->warehouse_head_dir;
 }

 char * MakeFile_Data_Collector::Get_Warehouse_Object_Dir(){

        return this->warehouse_obj_dir;
 }

 char * MakeFile_Data_Collector::Get_Warehouse_Path(){

        return this->warehouse_path;
 }

char * MakeFile_Data_Collector::Get_System_Header_File_Dir(){

       return this->Header_File_Directory;
}

 int MakeFile_Data_Collector::Get_Included_Header_Files_Number(){

     return this->Included_Header_Files_Number;
 }
