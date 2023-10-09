



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

#include "Source_File_Data_Setter.hpp"

Source_File_Data_Setter::Source_File_Data_Setter(char opr_sis)
{
   this->opr_sis = opr_sis;
}


Source_File_Data_Setter::~Source_File_Data_Setter()
{

}

void Source_File_Data_Setter::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;
}


void Source_File_Data_Setter::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){


     this->Code_Rd = ptr;
}


void Source_File_Data_Setter::Receive_Warehouse_Header_Directory(std::string dir){

     this->warehouse_head_dir = dir;
}



void Source_File_Data_Setter::Extract_Directory_From_Path(std::string path, std::string & dir){

     size_t path_size = path.size();

     size_t end_point = path_size;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(path[i]== '\\'){

                break;
            }
            else{

                 end_point--;
            }
         }

         if(this->opr_sis == 'l'){

            if(path[i]== '/'){

                break;
            }
            else{

                 end_point--;
            }
         }         
    }

    for(size_t i=0;i<end_point;i++)
    {
        dir.push_back(path[i]);
    }

    dir.shrink_to_fit();    
}



void Source_File_Data_Setter::Determine_File_Name_Without_Ext(std::string path, std::string & file_name)
{
     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;

     size_t file_extention_start_point = file_path_size;


    for(size_t i=file_path_size;i>0;i--){

        if((path[i] == '/') || (path[i] == '\\')){

            break;
        }
        else{

              dir_size--;
        }
     }

     for(size_t i=file_path_size;i>0;i--){

         if(path[i] == '.'){

           break;
         }
            else{

                file_extention_start_point--;
          }

          if(file_extention_start_point <= dir_size){

             file_extention_start_point = dir_size;
          }
     }

     size_t file_name_size = 0;

     if(file_extention_start_point <= dir_size){

        file_name_size = file_path_size - dir_size;

        // It is the case in which the file does not have extenton
     }

     if(file_extention_start_point > dir_size){

        file_name_size = file_extention_start_point - dir_size;
     }


     size_t name_start_point = 0;

     if(dir_size != 0){

        name_start_point = dir_size +1;
     }

     for(size_t i=name_start_point;i<file_extention_start_point;i++){

         file_name.push_back(path[i]);
     }
}


void Source_File_Data_Setter::Determine_Git_Record_Source_File_Directory(std::string git_record_system_path, 

     std::string & record_dir)     
    {

     size_t path_size = git_record_system_path.length();

     size_t dir_size = path_size;

     size_t end_point = 0;

     for(int i=path_size;i>0;i--){

         if(this->opr_sis =='w'){

           if(git_record_system_path[i] == '\\'){

             end_point = i;

             break;
           }
         }

         if(this->opr_sis =='l'){

           if(git_record_system_path[i] == '/'){

             end_point = i;

             break;
           }
         }
     }

     std::string dir = this->Git_Data_Proc->Get_Git_Repo_Directory();

     size_t repo_dir_size = dir.length();

     size_t start_point = repo_dir_size;

     char start_point_character = git_record_system_path[start_point];

     if(((start_point_character == '\\' )

         || (start_point_character== '/' ))){

         start_point++;
     }

     for(size_t i=start_point;i<end_point;i++){

         record_dir.push_back(git_record_system_path[i]) ;
     }

     record_dir.shrink_to_fit();
}



void Source_File_Data_Setter::Determine_Header_System_Path(std::string & path, std::string name){

     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(name);

     path = FileDtPtr->sys_path;
}


void Source_File_Data_Setter::Determine_Header_Repo_Warehouse_Path(std::string & wrd_path,

     std::string file_name, char opr_sis)
{

     size_t name_size = file_name.length();

     size_t wrd_path_size = this->warehouse_head_dir.length();

     size_t path_size = name_size + wrd_path_size;

     for(size_t i=0;i<wrd_path_size;i++){

         wrd_path.push_back(this->warehouse_head_dir[i]);
     }

     if(opr_sis == 'w'){

        wrd_path.push_back('\\');
     }

     if(opr_sis == 'l'){

        wrd_path.push_back('/');
     }

     for(size_t i=0;i<name_size;i++){

         wrd_path.push_back(file_name[i]);
     }
}


void Source_File_Data_Setter::Determine_Object_File_Name(std::string & obj_name, 
 
     std::string src_name){

     size_t name_size = src_name.size();

     for(size_t i=0;i<name_size;i++){

         if(src_name[i] == '.'){

            obj_name.push_back(src_name[i]);

            break;
         }
         else{

             obj_name.push_back(src_name[i]);
         }
     }

     obj_name.push_back('o');

     obj_name.shrink_to_fit();
}


void Source_File_Data_Setter::Extract_File_Name_From_Path(std::string & name,

     std::string string ){

     size_t string_size = string.length();

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(((string[i] == '/') || (string[i] == '\\'))){

            start_point = i+1;

            break;
        }
     }

     for(size_t i=start_point;i<string_size;i++)
     {
         name.push_back(string[i]) ;
     }

     name.shrink_to_fit();
}



void Source_File_Data_Setter::Copy_String(std::string & target_str, std::string str)
{
     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         target_str.push_back(str[i]);
     }

     target_str.shrink_to_fit();
}










