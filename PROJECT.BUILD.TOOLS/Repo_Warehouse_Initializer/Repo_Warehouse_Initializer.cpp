
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



#include "Repo_Warehouse_Initializer.h"

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(char * DesPath, char opr_sis)
{
     this->opr_sis = opr_sis;

}


Repo_Warehouse_Initializer::~Repo_Warehouse_Initializer(){

     this->Clear_Dynamic_Memory();
}


void Repo_Warehouse_Initializer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}

void Repo_Warehouse_Initializer::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Dt_Proc = ptr;
}

void Repo_Warehouse_Initializer::Build_Project_Warehouse(){


     this->warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Current_Directory();

     this->Determine_Warehouse_Path();

     this->Determine_Object_Files_Directory();

     this->Determine_Library_Files_Directory();

     this->Determine_Make_Files_Directory();


     this->Construct_Warehouse_Path();

     this->Construct_Object_Files_Directory();

     this->Construct_Make_Files_Directory();

     this->Construct_Library_Files_Directory();

     this->DirectoryManager.ChangeDirectory(this->current_directory.c_str());
}


void Repo_Warehouse_Initializer::Determine_Current_Directory(){

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t dir_name_size = strlen(Current_Directory);
     
     this->Clear_String_Memory(&this->current_directory);

     for(size_t i=0;i<dir_name_size;i++){
     
         this->current_directory.push_back(Current_Directory[i]);
     }

     this->current_directory.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Determine_Warehouse_Path(){

     std::string warehouse_word  ="WAREHOUSE";

     size_t word_size = warehouse_word.length();

     size_t wr_location_size = this->warehouse_location.length();


     for(size_t i=0;i<wr_location_size;i++){

         this->warehouse_path.push_back(this->warehouse_location[i]);
     }

     if(this->opr_sis == 'w'){

        this->warehouse_path.push_back('\\');        
     }
     else{

          if(this->opr_sis == 'l'){

             this->warehouse_path.push_back('/');        
          }
     }

     for(size_t i=0;i<word_size;i++){

         this->warehouse_path.push_back(warehouse_word[i]);
     }

     this->warehouse_path.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Determine_Object_Files_Directory(){

     std::string object_directory_folder_name = "OBJECT.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_folder_size= object_directory_folder_name.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Object_Files_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        this->Object_Files_Directory.push_back('\\');
     }
     else{

        this->Object_Files_Directory.push_back('/');
     }


     for(size_t i=0;i<object_folder_size;i++){

         this->Object_Files_Directory.push_back(object_directory_folder_name[i]);
     }

     this->Object_Files_Directory.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Determine_Make_Files_Directory(){

     std::string make_files_directory_folder_name = "MAKE.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_folder_size= make_files_directory_folder_name.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Make_Files_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        this->Make_Files_Directory.push_back('\\');
     }
     else{

        this->Make_Files_Directory.push_back('/');
     }


     for(size_t i=0;i<object_folder_size;i++){

         this->Make_Files_Directory.push_back(make_files_directory_folder_name[i]);
     }

     this->Make_Files_Directory.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Determine_Library_Files_Directory(){

     std::string directory_folder_name = "LIBRARY.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t name_size= directory_folder_name.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->Library_Files_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis=='w'){
     
        this->Library_Files_Directory.push_back('\\');
     } 
     else{
           if(this->opr_sis == 'l'){
           
              this->Library_Files_Directory.push_back('/');              
           }         
     }     

     for(size_t i=0;i<name_size;i++){

         this->Library_Files_Directory.push_back(directory_folder_name[i]);         
     }

     this->Library_Files_Directory.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Construct_Warehouse_Path(){

     int const_cond = this->DirectoryManager.MakeDirectory(this->warehouse_path.c_str());

     if(const_cond == 0){

        std::cout << "\n The project warehouse can not be constructed on:";

        std::cout << "\n";

        std::cout << this->warehouse_location;

        exit(0);
     }
}


void Repo_Warehouse_Initializer::Construct_Object_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Object_Files_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Object_Files_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The object files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Object_Files_Directory;

           exit(0);
        }
     }
}


void Repo_Warehouse_Initializer::Construct_Make_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Make_Files_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Make_Files_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The make files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Make_Files_Directory;

           exit(0);
        }
     }
}



void Repo_Warehouse_Initializer::Construct_Library_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Library_Files_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Library_Files_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The Library files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Library_Files_Directory;

           exit(0);
        }
     }
}



void Repo_Warehouse_Initializer::Clear_Dynamic_Memory(){
  
     this->Clear_String_Memory(&this->Object_Files_Directory);

     this->Clear_String_Memory(&this->Library_Files_Directory);

     this->Clear_String_Memory(&this->warehouse_path);

     this->Clear_String_Memory(&this->warehouse_location);

     this->Clear_String_Memory(&this->current_directory);
}


void Repo_Warehouse_Initializer::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}
