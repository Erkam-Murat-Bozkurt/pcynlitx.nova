


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

#include "MakeFile_Directory_Constructor.hpp"

MakeFile_Directory_Constructor::MakeFile_Directory_Constructor()
{
}


MakeFile_Directory_Constructor::~MakeFile_Directory_Constructor(){

     this->Clear_Dynamic_Memory();   
}

void MakeFile_Directory_Constructor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void MakeFile_Directory_Constructor::Clear_Dynamic_Memory(){

     this->Clear_Vector_Memory(this->MakeFile_Directories);

     this->Clear_Vector_Memory(this->Ordered_MakeFile_Directories);

     this->Clear_String_Memory(this->warehouse_path);
}


void MakeFile_Directory_Constructor::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;
}


void MakeFile_Directory_Constructor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_MakeFiles_Root_Directory();

}

void MakeFile_Directory_Constructor::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr){

      this->Compiler_Data_Ptr = ptr;
}


void MakeFile_Directory_Constructor::Collect_Directory_Info(){

     size_t data_size = this->Compiler_Data_Ptr->size();

     for(size_t i=0;i<data_size;i++){

         std::string git_record_dir, mk_file_dir;

         this->Determine_Git_Record_Directory(git_record_dir,this->Compiler_Data_Ptr->at(i).source_file_path);

         this->Determine_MakeFile_File_Directory(mk_file_dir,git_record_dir);

         this->MakeFile_Directories.push_back(mk_file_dir);         
     }

     this->MakeFile_Directories.shrink_to_fit();



     size_t mk_dir_list_size = this->MakeFile_Directories.size();

     for(size_t i=0;i<this->MakeFile_Directories.size();i++){

         std::string upper_directory;

         std::string dir = this->MakeFile_Directories.at(i);

         this->Find_Upper_Directory(upper_directory,dir);

         bool is_exist = this->Check_Directory_Existance(&this->MakeFile_Directories,upper_directory);

         if(!is_exist){

            size_t root_dir_size = this->make_files_root_directory.size();

            size_t next_dir_size = upper_directory.size();

            if(next_dir_size > root_dir_size){

                this->MakeFile_Directories.push_back(upper_directory);
            }

            this->MakeFile_Directories.shrink_to_fit();
         }
     }

     this->ReOrder_Directories();
}


void MakeFile_Directory_Constructor::Construct_MakeFile_Directories(){

     for(size_t i=0;i<this->Ordered_MakeFile_Directories.size();i++){

         this->Construct_Directory(this->Ordered_MakeFile_Directories.at(i));
     }

     this->Clear_Vector_Memory(this->Ordered_MakeFile_Directories);
}


void MakeFile_Directory_Constructor::ReOrder_Directories(){

     do{

        size_t position = this->Find_Shortest(this->MakeFile_Directories);

        this->Ordered_MakeFile_Directories.push_back(this->MakeFile_Directories.at(position));

        this->Clear_String_Memory(this->MakeFile_Directories.at(position));

        this->MakeFile_Directories.erase(this->MakeFile_Directories.begin() + position);

        this->MakeFile_Directories.shrink_to_fit();
         

     }while(this->MakeFile_Directories.size()>0);

     this->Clear_Vector_Memory(this->MakeFile_Directories);

     this->Ordered_MakeFile_Directories.shrink_to_fit();

}


size_t MakeFile_Directory_Constructor::Find_Shortest(std::vector<std::string> & vec){

    size_t shortest_index = 0;

     std::string shortest = vec.at(0);

     for(size_t i=0;i<vec.size();i++){

        if(vec.at(i).length() < shortest.length()){

           shortest = vec.at(i);

           shortest_index = i;
        }
     }
     
     return shortest_index;
}

void MakeFile_Directory_Constructor::Determine_MakeFiles_Root_Directory(){

     size_t warehouse_size = this->warehouse_path.length();

     for(size_t i=0;i<warehouse_size;i++){

         this->make_files_root_directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        if(!this->make_files_root_directory.back() != '\\'){

            this->make_files_root_directory.push_back('\\');
        }
     }


     if(this->opr_sis == 'l'){

        if(!this->make_files_root_directory.back() != '/'){

            this->make_files_root_directory.push_back('/');
        }
     }


     std::string warehouse_dir_name = "WAREHOUSE";

     size_t warehouse_dir_name_size = warehouse_dir_name.length();

     for(size_t i=0;i<warehouse_dir_name_size;i++){

         this->make_files_root_directory.push_back(warehouse_dir_name[i]);
     }

     if(this->opr_sis == 'w'){

        if(!this->make_files_root_directory.back() != '\\'){

            this->make_files_root_directory.push_back('\\');
        }
     }


     if(this->opr_sis == 'l'){

        if(!this->make_files_root_directory.back() != '/'){

            this->make_files_root_directory.push_back('/');
        }
     }


     std::string make_files_dir_name = "MAKE.FILES";

     size_t name_size = make_files_dir_name.length();

     for(size_t i=0;i<name_size;i++){

         this->make_files_root_directory.push_back(make_files_dir_name[i]);
     }

     if(this->opr_sis == 'w'){

        if(!this->make_files_root_directory.back() != '\\'){

            this->make_files_root_directory.push_back('\\');
        }
     }


     if(this->opr_sis == 'l'){

        if(!this->make_files_root_directory.back() != '/'){

            this->make_files_root_directory.push_back('/');
        }
     }

     this->make_files_root_directory.shrink_to_fit();
}


void MakeFile_Directory_Constructor::Determine_Git_Record_Directory(std::string & git_dir, 

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



void MakeFile_Directory_Constructor::Determine_MakeFile_File_Directory(std::string & mk_dir,

     std::string git_rcr_dir){

     size_t mk_root_dir_size = this->make_files_root_directory.length();

     for(size_t i=0;i<mk_root_dir_size;i++){

         mk_dir.push_back(this->make_files_root_directory[i]);
     }

     size_t git_src_dir_size = git_rcr_dir.length();

     for(size_t i=0;i<git_src_dir_size;i++){

         mk_dir.push_back(git_rcr_dir[i]);
     }

     mk_dir.shrink_to_fit();
}

void MakeFile_Directory_Constructor::Find_Upper_Directory(std::string & upper_dir, std::string dir){

     size_t dir_size = dir.length();

     size_t end_point = 0;

     for(size_t i=dir_size;i>0;i--){

         if((dir[i]=='\\') || (dir[i]=='/')){

             end_point = i;

             break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         upper_dir.push_back(dir[i]);
     }

     upper_dir.shrink_to_fit();
}


bool MakeFile_Directory_Constructor::Check_Directory_Existance(std::vector<std::string> * dir_list, 

     std::string dir){
     
     size_t dir_list_size = dir_list->size();

     bool is_exist = false;

     for(size_t j=0;j<dir_list_size;j++){

          std::string header_dir = dir_list->at(j);

          if(header_dir == dir){

             is_exist = true;

             break;
          }
     }

     return is_exist;

}


void MakeFile_Directory_Constructor::Construct_Directory(std::string dir){

     int return_condition = this->DirectoryManager.ChangeDirectory(dir.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(dir.c_str());

        if(const_cond == 0){

           std::cout << "\n The object files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << dir;

           exit(0);
        }
     }
}

void MakeFile_Directory_Constructor::Place_Std_String(std::string & target_str, std::string str){

     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         target_str.push_back(str[i]);
     }

     target_str.shrink_to_fit();
}



void MakeFile_Directory_Constructor::Place_CString(std::string * pointer, 

     char * string){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         pointer->push_back(string[i]);
     }
}



void MakeFile_Directory_Constructor::Clear_Vector_Memory(std::vector<std::string> & vec){

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


void MakeFile_Directory_Constructor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}


std::vector<std::string> * MakeFile_Directory_Constructor::Get_MakeFile_Directories(){

      return &this->Ordered_MakeFile_Directories;
}
