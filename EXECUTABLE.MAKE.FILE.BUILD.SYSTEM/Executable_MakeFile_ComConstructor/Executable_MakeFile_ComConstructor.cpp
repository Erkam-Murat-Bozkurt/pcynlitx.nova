

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

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


void Executable_MakeFile_ComConstructor::Receive_Dependency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Dep_Determiner = ptr;
}



void Executable_MakeFile_ComConstructor::Receive_ExeFileName(std::string name){

     this->Exe_Name = name;
}


void Executable_MakeFile_ComConstructor::Receive_Construction_Strategy(char strategy){

     this->constraction_strategy = strategy;
}


void Executable_MakeFile_ComConstructor::Construct_Compiler_Commands(std::string main_file_path){

     // Receiving the compiler data from the member objects

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();


     this->Determine_Src_File_Dir(main_file_path,'w');

     this->Determine_Git_Src_Dir();

     this->Determine_Make_File_Name(main_file_path);

     this->Determine_Source_File_Name(main_file_path);

     this->Construct_Library_Directories_List();

     this->Construct_Library_List();

     this->Determine_Project_Library_Name();


     if(this->constraction_strategy == 'a'){

        this->Comp_Data_ptr =  this->Dep_Determiner->Get_Compiler_Data_Address();

        this->Construct_Header_File_List();

        this->Construct_Object_File_List();

        this->Determine_Compiler_System_Command();
     }
     else{

          this->Simple_Data_Ptr = this->Dep_Determiner->Get_Simple_File_Dependencies();

          this->Construct_Header_File_List_For_Simple_Construction();

          this->Determine_Compiler_System_Command_For_Simple_Construction();
     }
}



void Executable_MakeFile_ComConstructor::Construct_Header_File_List(){

     Compiler_Data Data = this->Comp_Data_ptr->at(0);

     size_t list_size = Data.dependent_headers.size();

     for(int i=0;i<list_size;i++){

         std::string header_name = Data.dependent_headers.at(i);

         std::string header_dir = Data.dependent_headers_dir.at(i);

         std::string upper_dir  = Data.upper_directories.at(i);

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

            this->header_file_upper_dirs.push_back(upper_dir);
         }
     }
}




void Executable_MakeFile_ComConstructor::Construct_Object_File_List(){

     size_t list_size = this->Comp_Data_ptr->size();

     size_t counter = 0;

     for(int i=0;i<list_size;i++){

         std::string Object_File_Name = this->Comp_Data_ptr->at(i).object_file_name;

         if(!Object_File_Name.empty()){

            this->object_file_list.push_back(Object_File_Name);
         }
     }

     this->object_file_list.shrink_to_fit();
}




void Executable_MakeFile_ComConstructor::Construct_Library_Directories_List(){

    int lib_dir_num = this->Des_Reader->Get_Library_Directory_Number();
    
    if(lib_dir_num > 0){

       for(int i=0;i<lib_dir_num;i++){

           this->library_directory_list.push_back(this->Des_Reader->Get_Library_Directory(i));
       }
    }

    this->library_directory_list.shrink_to_fit();
}





void Executable_MakeFile_ComConstructor::Construct_Library_List(){

    int lib_files_num = this->Des_Reader->Get_Library_Files_Number();

    if(lib_files_num > 0){

       for(int i=0;i<lib_files_num;i++){

           this->library_name_list.push_back(this->Des_Reader->Get_Library_File(i));
       }
    }

    this->library_name_list.shrink_to_fit();
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
     char file_ext [] = "_exe_builder.make";

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

     this->Clear_String_Memory(&this->Compiler_System_Command);


     char compiler_input_command [] = "g++ -Wall -std=c++17 -o";

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     const std::vector<std::string> & linker_options   = this->Des_Reader->Get_Linker_Options();




     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] ="$(PROJECT_OBJECTS_LOCATION)";

     char Library_Location [] = "$(PROJECT_LIBRARY_LOCATION)";

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

     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            std::string option = compiler_options.at(i);

            if(option.back()!= '\\'){

                 option.push_back('\\');
            }

            this->Place_Information(&this->Compiler_System_Command,option);

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);
        }
     }


     if(!linker_options.empty()){

        for(size_t i=0;i<linker_options.size();i++){

            std::string option = linker_options.at(i);

            if(option.back()!= '\\'){

                 option.push_back('\\');
            }

            this->Place_Information(&this->Compiler_System_Command,option);

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);
        }
     }


     std::vector<std::string> dir_buffer;

     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     for(size_t i=0;i<this->header_file_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,this->header_file_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&this->Compiler_System_Command,Include_Character);

             this->Place_Information(&this->Compiler_System_Command,this->header_file_dirs[i]);

             this->Place_Information(&this->Compiler_System_Command,Space_Character);

             this->Place_Information(&this->Compiler_System_Command,slash);

             this->Place_Information(&this->Compiler_System_Command,new_line);

             this->Place_Information(&this->Compiler_System_Command,tab);
         }

         dir_buffer.push_back(this->header_file_dirs[i]);
     }


     for(size_t i=0;i<this->header_file_upper_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,this->header_file_upper_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&this->Compiler_System_Command,Include_Character);

             this->Place_Information(&this->Compiler_System_Command,this->header_file_upper_dirs[i]);

             this->Place_Information(&this->Compiler_System_Command,Space_Character);

             this->Place_Information(&this->Compiler_System_Command,slash);

             this->Place_Information(&this->Compiler_System_Command,new_line);

             this->Place_Information(&this->Compiler_System_Command,tab);
         }

         dir_buffer.push_back(this->header_file_upper_dirs[i]);
     }

     this->Clear_Vector_Memory(&dir_buffer); 


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

         this->Place_Information(&this->Compiler_System_Command,slash);

         this->Place_Information(&this->Compiler_System_Command,new_line);

         this->Place_Information(&this->Compiler_System_Command,tab);
     }




     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Library_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);



     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Objects_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     int  library_dir_num = this->Des_Reader->Get_Library_Directory_Number();

     sizer = 0;

     for(int i=0;i<library_dir_num;i++){

         std::string library_dir = this->Des_Reader->Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Compiler_System_Command,Link_Character);

         this->Place_Information(&this->Compiler_System_Command,library_dir);

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         this->Place_Information(&this->Compiler_System_Command,slash);

         this->Place_Information(&this->Compiler_System_Command,new_line);

         this->Place_Information(&this->Compiler_System_Command,tab);
     }




     std::string go_to_new_line = "\\\n\t";


     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,this->source_file_name);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,go_to_new_line);


     size_t obj_list_size = this->object_file_list.size();


     for(size_t i=1;i<obj_list_size;i++){

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

     this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            

     char link_symbol [] = "-l";

     size_t library_name_list_size = this->library_name_list.size();

     
     for(size_t i=0;i<library_name_list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,link_symbol);

         this->Place_Information(&this->Compiler_System_Command,this->library_name_list.at(i));

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         if(i<(library_name_list_size-1)){
         
            this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            
         }
     }

     if(library_name_list_size>0){

        this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            

     }

     this->Place_Information(&this->Compiler_System_Command,link_symbol);

     this->Place_Information(&this->Compiler_System_Command,this->project_library_name);
}




void Executable_MakeFile_ComConstructor::Determine_Compiler_System_Command_For_Simple_Construction(){

     this->Clear_String_Memory(&this->Compiler_System_Command);

     char compiler_input_command [] = "g++ -Wall -std=c++17 -o";

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     const std::vector<std::string> & linker_options   = this->Des_Reader->Get_Linker_Options();



     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] = "$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] = "$(PROJECT_OBJECTS_LOCATION)";

     char Library_Location [] = "$(PROJECT_LIBRARY_LOCATION)";

     char Source_Location  [] = "$(SOURCE_LOCATION)";




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



     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            std::string option = compiler_options.at(i);

            this->Place_Information(&this->Compiler_System_Command,option);

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);
        }
     }


     if(!linker_options.empty()){

        for(size_t i=0;i<linker_options.size();i++){

            std::string option = linker_options.at(i);

            this->Place_Information(&this->Compiler_System_Command,option);

            this->Place_Information(&this->Compiler_System_Command,Space_Character);

            this->Place_Information(&this->Compiler_System_Command,slash);

            this->Place_Information(&this->Compiler_System_Command,new_line);

            this->Place_Information(&this->Compiler_System_Command,tab);
        }
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




     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Library_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);



     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     int  library_dir_num = this->Des_Reader->Get_Library_Directory_Number();

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




     std::string go_to_new_line = "\\\n\t";


     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,this->source_file_name);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,go_to_new_line);


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

     this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            

     char link_symbol [] = "-l";

     size_t library_name_list_size = this->library_name_list.size();

     
     for(size_t i=0;i<library_name_list_size;i++){

         this->Place_Information(&this->Compiler_System_Command,link_symbol);

         this->Place_Information(&this->Compiler_System_Command,this->library_name_list.at(i));

         this->Place_Information(&this->Compiler_System_Command,Space_Character);

         if(i<(library_name_list_size-1)){
         
            this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            
         }
     }


    if(library_name_list_size>0){

        this->Place_Information(&this->Compiler_System_Command,go_to_new_line);            

    }

    this->Place_Information(&this->Compiler_System_Command,link_symbol);

    this->Place_Information(&this->Compiler_System_Command,this->project_library_name);

}

bool Executable_MakeFile_ComConstructor::Check_Include_Directory_Existance(std::vector<std::string> * hdr_dir_list, 

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


void Executable_MakeFile_ComConstructor::Determine_Project_Library_Name(){

    std::string repo_dir_path = this->Des_Reader->Get_Repo_Directory_Location();

    std::string repo_dir_name;

    this->Extract_Repo_Directory_Name(repo_dir_name,repo_dir_path);

    this->project_library_name = repo_dir_name;     
}



void Executable_MakeFile_ComConstructor::Construct_Header_File_List_For_Simple_Construction(){

     size_t list_size = this->Simple_Data_Ptr->Dependent_Header_Names.size();

     for(int i=0;i<list_size;i++){

         std::string header_name = this->Simple_Data_Ptr->Dependent_Header_Names.at(i);

         std::string header_dir  = this->Simple_Data_Ptr->Dependent_Header_Directories.at(i);

         std::string header_path = this->Simple_Data_Ptr->Dependent_Header_Paths.at(i);

         if(!header_name.empty()){
                  
            this->header_file_list.push_back(header_name);
            
            this->header_file_dirs.push_back(header_dir);

            this->header_file_paths.push_back(header_path);
         }
     }
}



void Executable_MakeFile_ComConstructor::Extract_Repo_Directory_Name(std::string & name, 

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


std::string Executable_MakeFile_ComConstructor::Get_Project_Library_Name(){

    return this->project_library_name;
}