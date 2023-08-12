

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

Executable_MakeFile_ComConstructor::Executable_MakeFile_ComConstructor(char opr_sis)

{
       this->opr_sis = opr_sis;

}

Executable_MakeFile_ComConstructor::~Executable_MakeFile_ComConstructor()
{
       this->Clear_Dynamic_Memory();
}


void Executable_MakeFile_ComConstructor::Clear_Dynamic_Memory(){

        this->Clear_Vector_Memory(&this->header_file_list);

        this->Clear_Vector_Memory(&this->header_file_dirs);

        this->Clear_Vector_Memory(&this->header_file_paths);

        this->Clear_Vector_Memory(&this->object_file_list);

        this->Clear_String_Memory(&this->git_src_dir);

        this->Clear_String_Memory(&this->src_file_dir);

        this->Clear_String_Memory(&this->source_file_name);

        this->Clear_String_Memory(&this->make_file_name);

        this->Clear_String_Memory(&this->Compiler_System_Command);
}


void Executable_MakeFile_ComConstructor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}


void Executable_MakeFile_ComConstructor::Receive_Depepndency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Dep_Determiner = ptr;
}



void Executable_MakeFile_ComConstructor::Receive_ExeFileName(std::string name){

     this->Exe_Name = name;
}



void Executable_MakeFile_ComConstructor::Construct_Compiler_Commands(std::string main_file_path){

     // Receiving the compiler data from the member objects

     this->warehouse_head_dir = this->Dep_Determiner->Get_Warehouse_Headers_Dir();

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();


     this->Comp_Data_ptr =  this->Dep_Determiner->Get_Compiler_Data_Address();

     this->Determine_Src_File_Dir(main_file_path,'w');

     this->Determine_Git_Src_Dir();

     this->Determine_Make_File_Name(main_file_path);

     this->Determine_Source_File_Name(main_file_path);

     this->Construct_Header_File_List();

     this->Construct_Object_File_List();

     this->Determine_Compiler_System_Command();
}



void Executable_MakeFile_ComConstructor::Construct_Header_File_List(){

     std::string space = " ";

     std::string include_command = "-include";

     std::string go_to_new_line = "\\\n\t";

     Compiler_Data Data = this->Comp_Data_ptr->at(0);

     size_t list_size = Data.dependent_headers.size();

     for(int i=0;i<list_size;i++){

         std::string header_name = Data.dependent_headers.at(i);

         std::string header_dir = Data.dependent_headers_dir.at(i);

         std::string header_path;

         if(!header_name.empty()){
                  
            this->header_file_list.push_back(header_name);
            
            this->header_file_dirs.push_back(header_dir);

            header_path += header_dir;

            if(this->opr_sis=='w'){

               header_path.push_back('\\');
            }

            if(this->opr_sis=='l'){

               header_path.push_back('/');
            }

            header_path += header_name;

            this->header_file_paths.push_back(header_path);
         }
     }
}

void Executable_MakeFile_ComConstructor::Construct_Object_File_List(){

     std::string space = " ";

     std::string go_to_new_line = "\\\n\t";

     size_t list_size = this->Comp_Data_ptr->at(0).dependent_objs.size();

     size_t counter = 0;

     for(int i=0;i<list_size;i++){

         std::string Object_File_Name = this->Comp_Data_ptr->at(0).dependent_objs.at(i);

         if(!Object_File_Name.empty()){

            this->object_file_list.push_back(Object_File_Name);
         }
     }

     this->object_file_list.shrink_to_fit();
}

void Executable_MakeFile_ComConstructor::Determine_Git_Src_Dir(){

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t src_dir_size = this->src_file_dir.length();

     for(size_t i=warehouse_path_size+1;i<src_dir_size;i++){

        this->git_src_dir.push_back(this->src_file_dir[i]);
     }
}

void Executable_MakeFile_ComConstructor::Determine_Src_File_Dir(std::string file_path, 

     char opr_sis){

     size_t path_size = file_path.length();

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

     for(int i=0;i<dir_size;i++){

         this->src_file_dir.push_back(file_path[i]);
     }
}


void Executable_MakeFile_ComConstructor::Determine_Make_File_Name(std::string file_path)
{
     char file_ext [] = ".make";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = file_path.length();

     size_t dir_size  = this->src_file_dir.length();


     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            this->make_file_name.push_back(file_path[i]);
        }
     }

     for(size_t i=0;i<ext_size;i++){

         this->make_file_name.push_back(file_ext[i]);
     }
}


void Executable_MakeFile_ComConstructor::Determine_Source_File_Name(std::string file_path){

     char file_ext [] = ".cpp";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = file_path.length();

     size_t dir_size  = this->src_file_dir.length();


     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            this->source_file_name.push_back(file_path[i]);
        }
     }

     for(size_t i=0;i<ext_size;i++){

         this->source_file_name.push_back(file_ext[i]);
     }
}

void Executable_MakeFile_ComConstructor::Determine_Compiler_System_Command(){

     char compiler_input_command [] = "g++ -Wall -std=c++17 -o";


     options = this->Des_Reader->Get_Options();


     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] ="$(PROJECT_OBJECTS_LOCATION)";

     char Source_Location []  ="$(SOURCE_LOCATION)";


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     this->Place_Information(&this->Compiler_System_Command,compiler_input_command);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,this->Exe_Name);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);

     if(!options.empty()){

        this->Place_Information(&this->Compiler_System_Command,this->options);

        this->Place_Information(&this->Compiler_System_Command,Space_Character);

        this->Place_Information(&this->Compiler_System_Command,slash);

        this->Place_Information(&this->Compiler_System_Command,new_line);

        this->Place_Information(&this->Compiler_System_Command,tab);
     }



     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     for(size_t i=0;i<this->header_file_dirs.size();i++){

         this->Place_Information(&this->Compiler_System_Command,Include_Character);

         this->Place_Information(&this->Compiler_System_Command,this->header_file_dirs[i]);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         this->Place_Information(&this->Compiler_System_Command,slash);

         this->Place_Information(&this->Compiler_System_Command,new_line);

         this->Place_Information(&this->Compiler_System_Command,tab);
     }


     this->Place_Information(&this->Compiler_System_Command,Include_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();


     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         std::string included_dir = this->Des_Reader->Get_Include_Directory(i);

         std::string dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Compiler_System_Command,Include_Character);

         this->Place_Information(&this->Compiler_System_Command,include_dir_symbol);

         this->Place_Information(&this->Compiler_System_Command,dir_index);

         this->Place_Information(&this->Compiler_System_Command,makro_end);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);

            sizer = 0;
          }
     }


     int  library_dir_num = this->Des_Reader->Get_Library_Directory_Number();

     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Objects_Location);


     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);


     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     sizer = 0;

     for(int i=0;i<library_dir_num;i++){

         std::string library_dir = this->Des_Reader->Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Compiler_System_Command,Link_Character);

         this->Place_Information(&this->Compiler_System_Command,library_dir);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);

            sizer = 0;
          }
     }

     this->Place_Information(&this->Compiler_System_Command,this->source_file_name);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     size_t obj_list_size = this->object_file_list.size();


     // The include commands definition

     std::string go_to_new_line = "\\\n\t";



     for(size_t i=0;i<obj_list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,Objects_Location);

         this->Place_Information(&this->Compiler_System_Command,slash);

         this->Place_Information(&this->Compiler_System_Command,this->object_file_list[i]);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         this->Place_Information(&this->Compiler_System_Command,go_to_new_line);
     }

     size_t hdr_list_size = this->header_file_paths.size();

     for(size_t i=0;i<hdr_list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,include_word);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         this->Place_Information(&this->Compiler_System_Command,this->header_file_paths[i]);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         if(i<(hdr_list_size-1)){
         
            this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            
         }
     }
}

void Executable_MakeFile_ComConstructor::Add_String(std::string * list, std::string string){

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         list->push_back(string[i]);
      }
  }

void Executable_MakeFile_ComConstructor::Place_String(std::string * str_pointer,std::string str){

     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         str_pointer->push_back(str[i]) ;
     }
}


void Executable_MakeFile_ComConstructor::Place_Information(std::string * Pointer,

     char * Information){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         Pointer->push_back(Information[i]);
     }
 }
 

 void Executable_MakeFile_ComConstructor::Place_Information(std::string * Pointer,

      std::string Information){

      int String_Size = Information.length();

      for(int i=0;i<String_Size;i++){

          Pointer->push_back(Information[i]);
     }
 }


void Executable_MakeFile_ComConstructor::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
    }
}

void Executable_MakeFile_ComConstructor::Clear_Vector_Memory(std::vector<std::string> * pointer)
{

     if(!pointer->empty()){

        std::vector<std::string>::iterator it;

        auto begin = pointer->begin();

        auto end   = pointer->end();

        for(auto it=begin;it<end;it++){

            if(!it->empty()){

                it->clear();

                it->shrink_to_fit();
            }
         }

         pointer->clear();

         pointer->shrink_to_fit();
      }
  }

std::vector<std::string> * Executable_MakeFile_ComConstructor::Get_Object_File_List()
{
       return &this->object_file_list;
}

std::vector<std::string> * Executable_MakeFile_ComConstructor::Get_Header_File_List()
{
       return &this->header_file_list;
}


std::string Executable_MakeFile_ComConstructor::Get_Src_File_Dr(){

      return this->src_file_dir;
}

std::string Executable_MakeFile_ComConstructor::Get_Git_Src_Dr(){

      return this->git_src_dir;
}

std::string Executable_MakeFile_ComConstructor::Get_Make_File_Name(){

      return this->make_file_name;
}

std::string Executable_MakeFile_ComConstructor::Get_Compiler_System_Command(){

       return this->Compiler_System_Command;
}
