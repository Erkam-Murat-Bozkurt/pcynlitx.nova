

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

   this->make_file_name = nullptr;

   this->src_file_dir = nullptr;

   this->git_src_dir = nullptr;

   this->source_file_name = nullptr;

   this->options = nullptr;
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

        delete [] this->git_src_dir;

        delete [] this->src_file_dir;

        delete [] this->source_file_name;

        delete [] this->make_file_name;

        delete [] this->Compiler_System_Command;

        this->Dependency_Selector.Clear_Dynamic_Memory();
     }
}

void Executable_MakeFile_ComConstructor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * pointer){

     this->Des_Reader_Pointer = pointer;
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

     this->Determine_Src_File_Dir(main_file_path,'w');

     this->Determine_Git_Src_Dir();

     this->Determine_Make_File_Name(main_file_path);

     this->Determine_Source_File_Name(main_file_path);

     this->Set_Header_File_Priorities();

     this->Re_Order_Header_Files();

     this->Determine_List_Sizes();

     this->Construct_Header_File_List();

     this->Construct_Object_File_List();

     this->Determine_Compiler_System_Command();
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

         this->Determine_Object_File_Name(&this->Header_Dependency_List[i].Object_File_Name,header_name);

         char * obj_name = this->Header_Dependency_List[i].Object_File_Name;

         if(obj_name != nullptr){

            this->Add_String(&this->object_file_list,obj_name,&index);

            this->Add_String(&this->object_file_list,space,&index);

            this->Add_String(&this->object_file_list,space,&index);

            this->Add_String(&this->object_file_list,slash,&index);

            this->Add_String(&this->object_file_list,new_line,&index);

            this->Add_String(&this->object_file_list,tab_char,&index);
         }
     }
}

void Executable_MakeFile_ComConstructor::Determine_Object_File_Name(char ** obj_name, char * header)
{
     size_t name_size = strlen(header);

     char file_extention [] = ".o";

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

void Executable_MakeFile_ComConstructor::Determine_Git_Src_Dir(){

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t src_dir_size = strlen(this->src_file_dir);

     size_t git_dr_size = src_dir_size - warehouse_path_size;

     this->git_src_dir = new char [5*git_dr_size];

     int index = 0;

     for(size_t i=warehouse_path_size+1;i<src_dir_size;i++){

        this->git_src_dir[index] = this->src_file_dir[i];

        index++;
     }

     this->git_src_dir[index] = '\0';
}

void Executable_MakeFile_ComConstructor::Determine_Src_File_Dir(char * file_path, char opr_sis){

     size_t path_size = strlen(file_path);

     size_t dir_size = path_size;

     for(int i=path_size;i>0;i--){

         if(opr_sis == 'w'){

              if(file_path[i] == '\\'){

                 break;
              }
              else{

                 dir_size--;
              }
         }

         if(opr_sis == 'l'){

              if(file_path[i] == '/'){

                 break;
              }
              else{

                 dir_size--;
              }
         }
     }

     this->src_file_dir = new char [5*dir_size];

     int index = 0;

     for(int i=0;i<dir_size;i++){

         this->src_file_dir[index] = file_path[i];

         index++;
     }

     this->src_file_dir[index] = '\0';
}


void Executable_MakeFile_ComConstructor::Determine_Make_File_Name(char * file_path){

     char file_ext [] = ".make";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = strlen(file_path);

     size_t dir_size  = strlen(this->src_file_dir);

     size_t name_size = path_size - dir_size + ext_size;

     this->make_file_name = new char [5*name_size];

     int index = 0;

     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            this->make_file_name[index] = file_path[i];

            index++;
        }
     }

     for(size_t i=0;i<ext_size;i++){

         this->make_file_name[index] = file_ext[i];

         index++;
     }

     this->make_file_name[index] ='\0';
}


void Executable_MakeFile_ComConstructor::Determine_Source_File_Name(char * file_path){

     char file_ext [] = ".cpp";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = strlen(file_path);

     size_t dir_size  = strlen(this->src_file_dir);

     size_t name_size = path_size - dir_size + ext_size;

     this->source_file_name = new char [5*name_size];

     int index = 0;

     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            this->source_file_name[index] = file_path[i];

            index++;
        }
     }

     for(size_t i=0;i<ext_size;i++){

         this->source_file_name[index] = file_ext[i];

         index++;
     }

     this->source_file_name[index] ='\0';
}

void Executable_MakeFile_ComConstructor::Determine_Compiler_System_Command(){

     char compiler_input_command [] = "g++ -Wall -c -std=c++17";


     char * options = this->Des_Reader_Pointer->Get_Options();

     this->Divide_Options(options);

     char Include_Character [] = "-I";

     char Link_Character [] = "-L";


     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(PROJECT_HEADERS_LOCATION)";

     char Source_Location [] ="$(SOURCE_LOCATION)";

     size_t object_file_list_size = strlen(this->object_file_list);

     size_t header_file_list_size = strlen(this->header_file_list);

     size_t compiler_command_size = object_file_list_size + header_file_list_size;


     this->Compiler_System_Command = new char [10*compiler_command_size];

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     this->Place_Information(&this->Compiler_System_Command,compiler_input_command,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     if(options != nullptr){

        this->Place_Information(&this->Compiler_System_Command,this->options,&index_counter);

        this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);
     }

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

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

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }


     int  library_dir_num = this->Des_Reader_Pointer->Get_Library_Directory_Number();

     this->Place_Information(&this->Compiler_System_Command,Link_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     sizer = 0;

     for(int i=0;i<library_dir_num;i++){

         char * library_dir = this->Des_Reader_Pointer->Get_Library_Directories()[i];

         char * dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Compiler_System_Command,Link_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,library_dir,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,this->source_file_name,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     int list_size = this->Dependency_Selector.Get_Dependency_List_Size();

     // The include commands definition


     for(int i=0;i<list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,this->Header_Dependency_List[i].Object_File_Name,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(((sizer >= 1) && (i!=(list_size -1)))){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     sizer = 0;

     for(int i=0;i<list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,this->Header_Dependency_List[i].Header_Name,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(((sizer >= 1) && (i!=(list_size -1)))){

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

void Executable_MakeFile_ComConstructor::Divide_Options(char * options){

     if(options != nullptr){

        size_t options_size = strlen(options);

        this->options = new char [5*options_size];

        char space = ' ';

        int space_counter = 0;

        for(int i=0;i<options_size;i++){

           if(options[i] == ' '){

              space_counter++;
            }
        }

        int index = 0;

        if(space_counter>2){

           space_counter = 0;

           for(size_t i=0;i<options_size;i++){

               this->options[index] = options[i];

               index++;

               if(options[i] == ' '){

                  space_counter++;
                }

                if(space_counter>2){

                   this->options[index] = '\\';

                   index++;

                   this->options[index] = '\n';

                   index++;

                   this->options[index] = '\t';

                   index++;


                   this->options[index] = ' ';

                   index++;

                   space_counter = 0;
                }

            }

            this->options[index] = '\0';
          }
       }
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

void Executable_MakeFile_ComConstructor::Place_Information(char ** Pointer,

     char * Information, int * index_counter){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         (*Pointer)[(*index_counter)] = Information[i];

         (*index_counter)++;
     }
 }

char * Executable_MakeFile_ComConstructor::Get_Object_File_List(){

       return this->object_file_list;
}

char * Executable_MakeFile_ComConstructor::Get_Header_File_List(){

       return this->header_file_list;
}

char * Executable_MakeFile_ComConstructor::Get_Src_File_Dr(){

      return this->src_file_dir;
}

char * Executable_MakeFile_ComConstructor::Get_Git_Src_Dr(){

      return this->git_src_dir;
}

char * Executable_MakeFile_ComConstructor::Get_Make_File_Name(){

      return this->make_file_name;
}

char * Executable_MakeFile_ComConstructor::Get_Compiler_System_Command(){

       return this->Compiler_System_Command;
}
