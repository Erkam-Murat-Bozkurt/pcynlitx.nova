
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



#include "Executable_MakeFile_Information_Collector.hpp"


Executable_MakeFile_Information_Collector::Executable_MakeFile_Information_Collector(char opr_sis)

{
       this->opr_sis = opr_sis;

}

Executable_MakeFile_Information_Collector::~Executable_MakeFile_Information_Collector()
{
       this->Clear_Dynamic_Memory();
}


void Executable_MakeFile_Information_Collector::Clear_Dynamic_Memory()
{

}




void Executable_MakeFile_Information_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}


void Executable_MakeFile_Information_Collector::Receive_Dependency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Dep_Determiner = ptr;

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();
}


void Executable_MakeFile_Information_Collector::Receive_Construction_Strategy(char strategy){

     this->constraction_strategy = strategy;
}



void Executable_MakeFile_Information_Collector::Determine_Include_File_List_For_Simple_Construction(std::string & include_file_list,
     
     std::vector<std::string> & header_file_paths){

     std::string go_to_new_line = "\\\n\t";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     size_t hdr_list_size = header_file_paths.size();

     for(size_t i=0;i<hdr_list_size;i++){

         this->Place_Information(&include_file_list,include_word);

         this->Place_Information(&include_file_list,Space_Character);

         this->Place_Information(&include_file_list,header_file_paths[i]);

         this->Place_Information(&include_file_list,Space_Character);

         if(i<(hdr_list_size-1)){
         
            this->Place_Information(&include_file_list,go_to_new_line);            
         }
     }    
}


void Executable_MakeFile_Information_Collector::Determine_External_Include_Directory_List_For_Compiler_Command(std::string & ext_inc_dir_list){

     char Include_Character [] = "-I";

     char Space_Character [] = {' ','\0'};

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();

     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         std::string dir_index = this->Translater.Translate(i);

         this->Place_Information(&ext_inc_dir_list,Include_Character);

         this->Place_Information(&ext_inc_dir_list,include_dir_symbol);

         this->Place_Information(&ext_inc_dir_list,dir_index);

         this->Place_Information(&ext_inc_dir_list,makro_end);

         this->Place_Information(&ext_inc_dir_list,Space_Character);

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&ext_inc_dir_list,Space_Character);

            this->Place_Information(&ext_inc_dir_list,slash);

            this->Place_Information(&ext_inc_dir_list,new_line);

            this->Place_Information(&ext_inc_dir_list,tab);

            sizer = 0;
          }
     }
}


void Executable_MakeFile_Information_Collector::Determine_Library_File_Path_List_For_Compiler_Command(std::string & library_path_list){

     const std::vector<std::string> & library_paths = this->Des_Reader->Get_Library_Files();

     std::string go_to_new_line = "\\\n\t";

     for(size_t i=0;i<library_paths.size();i++){

         library_path_list += library_paths.at(i);

         library_path_list += " ";

         library_path_list += go_to_new_line;
     }

     library_path_list.shrink_to_fit();
}



void Executable_MakeFile_Information_Collector::Determine_Include_Directory_List_For_Simple_Construction(std::string & inc_dir_list_for_com, 
     
     std::vector<std::string> & header_file_dirs){
    
     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();



     std::vector<std::string> dir_buffer;

     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     for(size_t i=0;i<header_file_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,header_file_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&inc_dir_list_for_com,Include_Character);

             this->Place_Information(&inc_dir_list_for_com,header_file_dirs[i]);

             this->Place_Information(&inc_dir_list_for_com,Space_Character);

             this->Place_Information(&inc_dir_list_for_com,slash);

             this->Place_Information(&inc_dir_list_for_com,new_line);

             this->Place_Information(&inc_dir_list_for_com,tab);
         }

         dir_buffer.push_back(header_file_dirs[i]);
     }

     this->Clear_Vector_Memory(&dir_buffer); 
}



void Executable_MakeFile_Information_Collector::Determine_Include_Directory_List(std::string & inc_dir_list_for_com, 
     
     std::vector<std::string> & header_file_dirs, 

     std::vector<std::string> & header_file_upper_dirs){
    
     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();



     std::vector<std::string> dir_buffer;

     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     for(size_t i=0;i<header_file_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,header_file_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&inc_dir_list_for_com,Include_Character);

             this->Place_Information(&inc_dir_list_for_com,header_file_dirs[i]);

             this->Place_Information(&inc_dir_list_for_com,Space_Character);

             this->Place_Information(&inc_dir_list_for_com,slash);

             this->Place_Information(&inc_dir_list_for_com,new_line);

             this->Place_Information(&inc_dir_list_for_com,tab);
         }

         dir_buffer.push_back(header_file_dirs[i]);
     }


     for(size_t i=0;i<header_file_upper_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,header_file_upper_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&inc_dir_list_for_com,Include_Character);

             this->Place_Information(&inc_dir_list_for_com,header_file_upper_dirs[i]);

             this->Place_Information(&inc_dir_list_for_com,Space_Character);

             this->Place_Information(&inc_dir_list_for_com,slash);

             this->Place_Information(&inc_dir_list_for_com,new_line);

             this->Place_Information(&inc_dir_list_for_com,tab);
         }

         dir_buffer.push_back(header_file_upper_dirs[i]);
     }

     this->Clear_Vector_Memory(&dir_buffer); 
}


void Executable_MakeFile_Information_Collector::Determine_Source_File_Directory_List_For_Simple_Construction(std::string & src_dir_list_for_com){

     char Link_Character [] = "-L";

     char Space_Character [] = {' ','\0'};

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     const std::vector<std::string> & src_dir = this->Des_Reader->Get_Source_File_Directories();

     int sizer = 0;

     for(size_t i=0;i<src_dir.size();i++){

         std::string source_file_dir = src_dir.at(i);

         char * dir_index = this->Translater.Translate(static_cast<int>(i));

         this->Place_Information(&src_dir_list_for_com,Link_Character);

         this->Place_Information(&src_dir_list_for_com,source_file_dir);

         this->Place_Information(&src_dir_list_for_com,Space_Character);

         sizer++;

         if(sizer >= 1){

            this->Place_Information(&src_dir_list_for_com,Space_Character);

            this->Place_Information(&src_dir_list_for_com,slash);

            this->Place_Information(&src_dir_list_for_com,new_line);

            this->Place_Information(&src_dir_list_for_com,tab);

            sizer = 0;
          }
     }    
}



void Executable_MakeFile_Information_Collector::Determine_Compiler_Options_For_Compiler_Command(std::string & compiler_options_list){

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     char Space_Character [] = {' ','\0'};

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     
     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            std::string option = compiler_options.at(i);

            this->Place_Information(&compiler_options_list,option);

            this->Place_Information(&compiler_options_list,Space_Character);

            this->Place_Information(&compiler_options_list,slash);

            this->Place_Information(&compiler_options_list,new_line);

            this->Place_Information(&compiler_options_list,tab);
        }
     }

}



void Executable_MakeFile_Information_Collector::Determine_Linker_Options_For_Compiler_Command(std::string & linker_options_list){

     const std::vector<std::string> & linker_options   = this->Des_Reader->Get_Linker_Options();

     char Space_Character [] = {' ','\0'};

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";     


     if(!linker_options.empty()){

        for(size_t i=0;i<linker_options.size();i++){

            std::string option = linker_options.at(i);

            this->Place_Information(&linker_options_list,option);

            this->Place_Information(&linker_options_list,Space_Character);

            this->Place_Information(&linker_options_list,slash);

            this->Place_Information(&linker_options_list,new_line);

            this->Place_Information(&linker_options_list,tab);
        }
     }
}







bool Executable_MakeFile_Information_Collector::Check_Include_Directory_Existance(std::vector<std::string> * hdr_dir_list, 

     std::string dir){
     
     size_t dir_list_size = hdr_dir_list->size();

     bool is_exist = false;

     for(size_t j=0;j<dir_list_size;j++){

          std::string header_dir = hdr_dir_list->at(j);

          if(header_dir == dir){

             is_exist = true;

             break;
          }
     }

     return is_exist;
}

void Executable_MakeFile_Information_Collector::Construct_Library_Directory_List_For_Compiler_Command(std::string & lib_dir_list_for_compiler)
{
     lib_dir_list_for_compiler.clear();     

     lib_dir_list_for_compiler.shrink_to_fit();

     char Link_Character [] = "-L";

     int lib_dir_num = this->Des_Reader->Get_Library_Directory_Number();

     std::string go_to_new_line = "\\\n\t";

     if(lib_dir_num > 0){

       for(int i=0;i<lib_dir_num;i++){

           lib_dir_list_for_compiler += Link_Character;

           lib_dir_list_for_compiler += this->Des_Reader->Get_Library_Directory(i);

           lib_dir_list_for_compiler += " ";

           lib_dir_list_for_compiler += go_to_new_line;
       }
     }

     lib_dir_list_for_compiler.shrink_to_fit();
}



void Executable_MakeFile_Information_Collector::Determine_Project_Library_Name(std::string & project_library_name){

    std::string repo_dir_path = this->Des_Reader->Get_Repo_Directory_Location();

    std::string repo_dir_name;

    this->Extract_Repo_Directory_Name(repo_dir_name,repo_dir_path);

    std::string lib_prefix = "lib";

    std::string archive_subfix = ".a";

    project_library_name =  lib_prefix + repo_dir_name + archive_subfix;     
}


void Executable_MakeFile_Information_Collector::Determine_Git_Src_Dir(std::string & git_src_dir, 
    
     std::string src_file_dir){

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t src_dir_size = src_file_dir.length();

     for(size_t i=warehouse_path_size+1;i<src_dir_size;i++){

        git_src_dir.push_back(src_file_dir[i]);
     }

     git_src_dir.shrink_to_fit();
}


void Executable_MakeFile_Information_Collector::Determine_Source_File_Name(std::string & source_file_name, 
    
     std::string file_path, std::string src_file_dir){

     this->Clear_String_Memory(&source_file_name);

     char file_ext [] = ".cpp";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = file_path.length();

     size_t dir_size  = src_file_dir.length();


     std::string source_file_name_without_ext;

     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            source_file_name_without_ext.push_back(file_path[i]);
        }
     }

     source_file_name_without_ext.shrink_to_fit();    

     source_file_name = source_file_name_without_ext;

     for(size_t i=0;i<ext_size;i++){

         source_file_name.push_back(file_ext[i]);
     }

     source_file_name.shrink_to_fit();
}



void Executable_MakeFile_Information_Collector::Determine_Make_File_Name(std::string & make_file_name, 
     
     std::string file_path, std::string src_file_dir)
{
     char file_ext [] = "_exe_builder.make";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = file_path.length();

     size_t dir_size  = src_file_dir.length();

     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            make_file_name.push_back(file_path[i]);
        }
     }

     for(size_t i=0;i<ext_size;i++){

         make_file_name.push_back(file_ext[i]);
     }
}



void Executable_MakeFile_Information_Collector::Extract_Repo_Directory_Name(std::string & name, 

     std::string root_dir){

     size_t root_dir_size = root_dir.size();

     size_t start_point = root_dir_size;

     for(size_t i=root_dir_size;i>0;i--){

         if((root_dir[i] == '\\') || (root_dir[i] == '/') ){

             start_point = i+1;
             break;
         }   
     }    

     for(size_t i=start_point;i<root_dir_size;i++){

         name.push_back(tolower(root_dir[i]));
     }

     name.shrink_to_fit();
}


void Executable_MakeFile_Information_Collector::Add_String(std::string * list, std::string string){

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         list->push_back(string[i]);
      }
}




void Executable_MakeFile_Information_Collector::Place_String(std::string * str_pointer,std::string str){

     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         str_pointer->push_back(str[i]) ;
     }
}



void Executable_MakeFile_Information_Collector::Place_Information(std::string * Pointer,

     char * Information){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         Pointer->push_back(Information[i]);
     }
 }
 



void Executable_MakeFile_Information_Collector::Place_Information(std::string * Pointer,

      std::string Information){

      int String_Size = Information.length();

      for(int i=0;i<String_Size;i++){

          Pointer->push_back(Information[i]);
     }
}



void Executable_MakeFile_Information_Collector::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
    }
}


void Executable_MakeFile_Information_Collector::Clear_Vector_Memory(std::vector<std::string> * pointer)
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



void Executable_MakeFile_Information_Collector::Determine_Src_File_Dir(std::string file_path, 

     std::string & src_dir){

     size_t path_size = file_path.length();

     size_t dir_size = path_size;

     for(int i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

              if(file_path[i] == '\\'){

                 break;
              }
              else{

                 dir_size--;
              }
         }

         if(this->opr_sis == 'l'){

              if(file_path[i] == '/'){

                 break;
              }
              else{

                 dir_size--;
              }
         }
     }

     for(int i=0;i<dir_size;i++){

         src_dir.push_back(file_path[i]);
     }
}

