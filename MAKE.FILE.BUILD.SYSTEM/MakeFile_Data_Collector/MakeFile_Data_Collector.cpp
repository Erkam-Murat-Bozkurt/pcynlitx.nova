



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



#include "MakeFile_Data_Collector.hpp"

MakeFile_Data_Collector::MakeFile_Data_Collector()
{
}


MakeFile_Data_Collector::~MakeFile_Data_Collector(){

     this->Clear_Dynamic_Memory();   
}

void MakeFile_Data_Collector::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void MakeFile_Data_Collector::Clear_Dynamic_Memory(){

     this->Clear_String_Memory(this->Source_File_Name_With_Ext);

     this->Clear_String_Memory(this->Object_File_Name);

     this->Clear_String_Memory(this->Compiler_System_Command);

     this->Clear_String_Memory(this->Dependency_Code_Line);

     this->Clear_String_Memory(this->Make_File_Name);

     this->Clear_String_Memory(this->warehouse_obj_dir);

     this->Clear_String_Memory(this->Source_File_Name);

     this->Clear_String_Memory(this->Source_File_Directory);     

     this->Clear_String_Memory(this->Construction_Code_Line);
}


void MakeFile_Data_Collector::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;
}


void MakeFile_Data_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->repo_dir  = this->Des_Reader->Get_Repo_Directory_Location();

}

void MakeFile_Data_Collector::Receive_Compiler_Data_Pointer(Compiler_Data * ptr){

      this->Compiler_Data_Ptr = ptr;
}


void MakeFile_Data_Collector::Receive_Determined_Upper_Directories(std::vector<std::string> * ptr){

     this->Determined_Upper_Directories = ptr;
}



void MakeFile_Data_Collector::Collect_Make_File_Data(std::string fileName){

     this->Clear_Dynamic_Memory();

     this->Determine_Warehouse_Object_Dir();

     this->Receive_Git_Record_Data(fileName);

     this->Determine_Compiler_System_Command();

     this->Determine_Construction_Code_Line();

     this->Find_Object_File_Name();

     this->Determine_Dependency_Code_Line();

     this->Determine_Make_File_Name();   
}


void MakeFile_Data_Collector::Determine_Warehouse_Object_Dir(){

     std::string object_directory = "OBJECT.FILES";

     std::string warehouse_word = "WAREHOUSE";

     size_t wrd_path_size = this->warehouse_path.length();

     size_t object_dir_size = object_directory.length();

     size_t wr_word_size  = warehouse_word.length();

     for(size_t i=0;i<wrd_path_size;i++){

         this->warehouse_obj_dir.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis== 'w'){

        if(this->warehouse_obj_dir.back() != '\\'){

           this->warehouse_obj_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_obj_dir.back() != '/'){

           this->warehouse_obj_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir.push_back(warehouse_word[i]);
     }


     if(this->opr_sis == 'w'){

        if(this->warehouse_obj_dir.back() != '\\'){

           this->warehouse_obj_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_obj_dir.back() != '/'){

           this->warehouse_obj_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir.push_back(object_directory[i]);         
     }
}


void MakeFile_Data_Collector::Receive_Git_Record_Data(std::string file_name){

     this->Source_File_Name_With_Ext = this->Compiler_Data_Ptr->source_file_name;

     this->Determine_File_Name_Without_Ext(this->Source_File_Name,this->Source_File_Name_With_Ext);
      
     std::string source_file_sys_path = this->Compiler_Data_Ptr->source_file_path;

     this->Determine_Source_File_Directory(this->Source_File_Directory,source_file_sys_path);
     
     this->Header_File_Directory = this->Source_File_Directory;
}



void MakeFile_Data_Collector::Find_Object_File_Name(){

     size_t Source_File_Name_Size = this->Source_File_Name.length();

     // The source file name witout extantion

     for(int i=0;i<Source_File_Name_Size;i++){

         this->Object_File_Name.push_back( this->Source_File_Name[i]);
     }

     this->Object_File_Name.push_back('.');

     this->Object_File_Name.push_back('o');
}

void MakeFile_Data_Collector::Determine_Make_File_Name(){

     std::string make_file_extention = ".make";

     size_t class_name_size = this->Source_File_Name.length();

     size_t extention_size = make_file_extention.length();

     for(size_t i=0;i<class_name_size;i++){

         this->Make_File_Name.push_back(this->Source_File_Name[i]);         
     }

     for(size_t i=0;i<extention_size;i++){

         this->Make_File_Name.push_back(make_file_extention[i]);         
     }
}

void MakeFile_Data_Collector::Determine_Compiler_System_Command(){

     std::string compiler_input_command = "g++ -Wall -c -std=c++17"; 

     std::string file_name_ = this->Compiler_Data_Ptr->source_file_name_witout_ext + "_depends.d " ;

     compiler_input_command += " -MD -MF ";
     
     compiler_input_command += file_name_;
     

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     //const std::vector<std::string> & linker_options   = this->Des_Reader->Get_Linker_Options();


     std::string Include_Character = "-I";

     std::string include_word = "-include";

     std::string Source_Location  ="$(SOURCE_LOCATION)";

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     std::string Space_Character = " ";

     std::string go_to_new_line = "\\\n\t";

     char slash_w [] = "\\";

     char slash_l [] = "/";

     this->Place_String(&this->Compiler_System_Command,compiler_input_command);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);

     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            this->Place_String(&this->Compiler_System_Command,compiler_options.at(i));

            this->Place_String(&this->Compiler_System_Command,Space_Character);

            this->Place_String(&this->Compiler_System_Command,go_to_new_line);
        }
     }
     
     // THE ADDITION OF INCLUDE DIRECTORIES PATHS


     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();

     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         std::string included_dir = this->Des_Reader->Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->Place_String(&this->Compiler_System_Command,Include_Character);

         this->Place_String(&this->Compiler_System_Command,include_dir_symbol);

         this->Place_CString(&this->Compiler_System_Command,dir_index);

         this->Place_CString(&this->Compiler_System_Command,makro_end);

         this->Place_String(&this->Compiler_System_Command,Space_Character);

         this->Place_String(&this->Compiler_System_Command,go_to_new_line);
     }


     this->Place_String(&this->Compiler_System_Command,Include_Character);

     this->Place_String(&this->Compiler_System_Command,Source_Location);

     this->Place_String(&this->Compiler_System_Command,Space_Character);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);




     std::string source_file_name = this->Compiler_Data_Ptr->source_file_name;

     std::vector<std::string> * header_directories = &this->Compiler_Data_Ptr->dependent_headers_dir;

     size_t hdr_dir_size = header_directories->size();


     std::vector<std::string> dir_buffer;
 
     for(size_t i=0;i<hdr_dir_size;i++){

          std::string dir = header_directories->at(i);
                    
          bool is_dir_exist = this->Check_String_Existance(dir_buffer,dir);

          if(!is_dir_exist){

             this->Place_String(&this->Compiler_System_Command,Include_Character);

             this->Place_String(&this->Compiler_System_Command,dir);

             this->Place_String(&this->Compiler_System_Command,Space_Character);

             this->Place_String(&this->Compiler_System_Command,go_to_new_line);
          }

          dir_buffer.push_back(dir);
     }

     dir_buffer.shrink_to_fit();


     std::vector<std::string> * upper_dirs = &this->Compiler_Data_Ptr->upper_directories;

     for(size_t i=0;i<hdr_dir_size;i++){

          std::string dir = upper_dirs->at(i);
                    
          bool is_dir_exist = this->Check_String_Existance(dir_buffer,dir);

          if(!is_dir_exist){

             this->Place_String(&this->Compiler_System_Command,Include_Character);

             this->Place_String(&this->Compiler_System_Command,dir);

             this->Place_String(&this->Compiler_System_Command,Space_Character);

             this->Place_String(&this->Compiler_System_Command,go_to_new_line);
          }

          dir_buffer.push_back(dir);
     }

 
     size_t up_directories_num = this->Determined_Upper_Directories->size();

     for(size_t i=0;i<up_directories_num;i++){

         std::string dir = this->Determined_Upper_Directories->at(i);

         bool is_dir_exist = this->Check_String_Existance(dir_buffer,dir);

          if(!is_dir_exist){

             this->Place_String(&this->Compiler_System_Command,Include_Character);

             this->Place_String(&this->Compiler_System_Command,dir);

             this->Place_String(&this->Compiler_System_Command,Space_Character);

             this->Place_String(&this->Compiler_System_Command,go_to_new_line);
          }

          dir_buffer.push_back(dir);
     }


     dir_buffer.shrink_to_fit();

     this->Clear_Vector_Memory(dir_buffer);  
     


     this->Place_String(&this->Compiler_System_Command,Source_Location);

     if(this->opr_sis == 'w'){
     
        this->Place_String(&this->Compiler_System_Command,slash_w);
     }
     else{
     
         if(this->opr_sis =='l'){
         
           this->Place_String(&this->Compiler_System_Command,slash_l);
         }
     }


     this->Place_String(&this->Compiler_System_Command,this->Source_File_Name_With_Ext);

     this->Place_String(&this->Compiler_System_Command,Space_Character);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);

     this->Compiler_System_Command.shrink_to_fit();

     /*
     std::vector<std::string> inc_directive_buffer;

     size_t dep_header_size = this->Compiler_Data_Ptr->dependent_headers.size();

     for(size_t i=0;i<dep_header_size;i++){

          std::string include_directive;

          this->Determine_Include_Directive(&include_directive,i);

          bool inc_directive_exist = this->Check_String_Existance(inc_directive_buffer,include_directive);

          if(!inc_directive_exist){

              this->Place_String(&this->Compiler_System_Command,include_directive);

              this->Place_String(&this->Compiler_System_Command,Space_Character);

              this->Place_String(&this->Compiler_System_Command,go_to_new_line);

              inc_directive_buffer.push_back(include_directive);
          }
     }     

     inc_directive_buffer.shrink_to_fit();

     this->Clear_Vector_Memory(inc_directive_buffer);  
     
     */
}



void MakeFile_Data_Collector::Determine_Include_Directive(std::string * directive, 

     int index){

     std::string include_word = "-include";

     std::string Space_Character = " ";

     std::string header_name = this->Compiler_Data_Ptr->dependent_headers.at(index);

     std::string dir     = this->Compiler_Data_Ptr->dependent_headers_dir.at(index);

     this->Place_String(directive,include_word);

     this->Place_String(directive,Space_Character);

     this->Place_String(directive,dir);

     if(this->opr_sis == 'w'){

        if(dir.back()!= '\\'){

           directive->push_back('\\');
        }
     }
          
     if(this->opr_sis == 'l'){

        if(dir.back()!= '/'){

           directive->push_back('/');
        }
     }

     this->Place_String(directive,header_name);
}



void MakeFile_Data_Collector::Determine_Dependency_Code_Line(){

     char double_quotes [] = " : ";

     size_t Object_File_Name_Size = this->Object_File_Name.length();

     size_t Header_File_Name_Size = this->Source_File_Name_With_Ext.length();

     size_t Source_File_Name_Size = this->Source_File_Name_With_Ext.length();


     int  sizer = 0;

     std::string Space_Character = " ";

     std::string go_to_new_line = "\\\n\t";

     std::string target_name = ".PHONY dep_list: ";

     this->Place_String(&this->Dependency_Code_Line,target_name);

     this->Place_String(&this->Dependency_Code_Line,this->Source_File_Name_With_Ext);

     this->Place_String(&this->Dependency_Code_Line,Space_Character);

     this->Place_String(&this->Dependency_Code_Line,go_to_new_line);


     std::string source_file_name = this->Compiler_Data_Ptr->source_file_name;

     std::vector<std::string> * header_files = &this->Compiler_Data_Ptr->dependent_headers;

     size_t hdr_dir_size = header_files->size();

     
     std::vector<std::string> header_files_buffer;

     for(size_t i=0;i<hdr_dir_size;i++){

          std::string header = header_files->at(i);

          bool is_exist = this->Check_String_Existance(header_files_buffer,header);

          if(!is_exist){

              this->Place_String(&this->Dependency_Code_Line,header);

              this->Place_String(&this->Dependency_Code_Line,Space_Character);

              this->Place_String(&this->Dependency_Code_Line,go_to_new_line);

              header_files_buffer.push_back(header);
          }
     }   

     this->Clear_Vector_Memory(header_files_buffer);
}


void MakeFile_Data_Collector::Determine_Construction_Code_Line(){

     std::string object_file_name = this->Compiler_Data_Ptr->object_file_name;

     std::string dependency_file_name = this->Compiler_Data_Ptr->source_file_name_witout_ext + "_depends.d" ;

     std::string make_target_name = object_file_name + ": $(" +  dependency_file_name + ") \n";

     this->Construction_Code_Line = make_target_name + "\n\t";

     
     std::string compiler_input_command = "g++ -Wall -c -std=c++17"; 



     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     std::string Space_Character = " ";

     std::string go_to_new_line = "\\\n\t";

     this->Place_String(&this->Construction_Code_Line,compiler_input_command);

     this->Place_String(&this->Construction_Code_Line,go_to_new_line);

     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            this->Place_String(&this->Construction_Code_Line,compiler_options.at(i));

            this->Place_String(&this->Construction_Code_Line,Space_Character);

            this->Place_String(&this->Construction_Code_Line,go_to_new_line);
        }
     }     

     this->Construction_Code_Line +=  "-o $@";

     this->Construction_Code_Line.shrink_to_fit();
}


void MakeFile_Data_Collector::Determine_Git_Record_Directory(std::string & git_dir, 

     std::string sys_path){

     std::string root_dir = this->Des_Reader->Get_Repo_Directory_Location();

     size_t path_size = sys_path.length();

     size_t end_point = path_size;

     size_t start_point = root_dir.length()+1;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(sys_path[i]== '\\'){

               break;
          
            }
            else{

                  end_point--;
            }
         }


         if(this->opr_sis == 'l'){

            if(sys_path[i]== '/'){

               break;
            }
            else{

                  end_point--;
            }
         }
     }


     for(size_t i=start_point;i<end_point;i++){

         git_dir.push_back(sys_path[i]);
     }

     git_dir.shrink_to_fit();

}



void MakeFile_Data_Collector::Determine_Source_File_Directory(std::string & src_dir,

     std::string sys_path){

     size_t path_size = sys_path.length();

     size_t end_point = path_size;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(sys_path[i]== '\\'){

               break;
          
            }
            else{

                  end_point--;
            }
         }


         if(this->opr_sis == 'l'){

            if(sys_path[i]== '/'){

               break;
            }
            else{

                  end_point--;
            }
         }
     }


     for(size_t i=0;i<end_point;i++){

         src_dir.push_back(sys_path[i]);
     }

     src_dir.shrink_to_fit();

}


bool MakeFile_Data_Collector::Check_String_Existance(std::vector<std::string> & list, 

     std::string str){
     
     size_t list_size = list.size();

     bool is_exist = false;

     for(size_t j=0;j<list_size;j++){

          std::string header_dir = list.at(j);

          if(header_dir == str){

             is_exist = true;

             break;
          }
     }

     return is_exist;

}


void MakeFile_Data_Collector::Determine_File_Name_Without_Ext(std::string & file_name, 

     std::string file_name_with_ext)
{
     size_t name_size = file_name_with_ext.length();     

     size_t end_point = name_size;

     for(size_t i=end_point;i>0;i--){

         if(file_name_with_ext[i] == '.'){

           break;
         }
         else{

              end_point--;
         }
     }

     for(size_t i=0;i<end_point;i++){

         file_name.push_back(file_name_with_ext[i]);
     }

     file_name.shrink_to_fit();
}


void MakeFile_Data_Collector::Place_String(std::string * pointer,

     std::string Information){

     int String_Size = Information.length();

     for(int i=0;i<String_Size;i++){

         pointer->push_back(Information[i]);
     }
}

void MakeFile_Data_Collector::Place_CString(std::string * pointer, 

     char * string){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         pointer->push_back(string[i]);
     }
}

void MakeFile_Data_Collector::Clear_Vector_Memory(std::vector<std::string> & vec){

     size_t vec_size = vec.size();

     for(size_t i=0;i<vec_size;i++){

         this->Clear_String_Memory(vec.at(i));
     }

     if(!vec.empty())
     {
         vec.clear();
         vec.shrink_to_fit();
     }
}

void MakeFile_Data_Collector::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}

std::string MakeFile_Data_Collector::Get_Source_File_Name(){

     return this->Source_File_Name;
}

std::string MakeFile_Data_Collector::Get_Make_File_Name(){

     return this->Make_File_Name;
}

std::string MakeFile_Data_Collector::Get_Compiler_System_Command(){

     return this->Compiler_System_Command;
}

std::string MakeFile_Data_Collector::Get_Dependency_Code_Line(){

     return this->Dependency_Code_Line;
}

std::string MakeFile_Data_Collector::Get_Construction_Code_Line(){

     return this->Construction_Code_Line;
}

std::string MakeFile_Data_Collector::Get_Object_File_Name(){

     return this->Object_File_Name;
}

std::string MakeFile_Data_Collector::Get_Source_File_Name_With_Extention(){

     return this->Source_File_Name_With_Ext;
}

std::string MakeFile_Data_Collector::Get_Repo_Dir(){

     return this->repo_dir;
}


std::string MakeFile_Data_Collector::Get_Warehouse_Object_Dir(){

     return this->warehouse_obj_dir;
}

std::string MakeFile_Data_Collector::Get_Warehouse_Path(){

     return this->warehouse_path;
}

std::string MakeFile_Data_Collector::Get_System_Header_File_Dir(){

     return this->Header_File_Directory;
}

std::string MakeFile_Data_Collector::Get_Source_File_System_Directory(){

     return this->Source_File_Directory;
}

