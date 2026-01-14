
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




#include "Script_Data_Collector.hpp"


Script_Data_Collector::Script_Data_Collector(char opr_sis) 
{
     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;
}



Script_Data_Collector::~Script_Data_Collector()
{
   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

   }
}


void Script_Data_Collector::Receive_Compiler_Data(Compiler_Data * ptr){

     this->Cmp_Data_Ptr = ptr;
}

void Script_Data_Collector::Receive_Simple_Dependency_Search_Data(const Simple_Source_File_Dependency * ptr){

      this->Simple_Data_Ptr = ptr;
}


void Script_Data_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_File_Reader = ptr;

     this->warehouse_path = this->Des_File_Reader->Get_Warehouse_Location();
}


void Script_Data_Collector::Determine_Source_File_Compilation_Information(Script_Data * ptr,

     std::string source_file_name){

     ptr->warehouse_path = this->warehouse_path;


     int record_index = 0;


     std::string git_record_dir = this->Cmp_Data_Ptr->src_git_record_dir;

     this->Place_String(&ptr->source_file_git_record_dir,git_record_dir);



     std::string src_file_name = this->Cmp_Data_Ptr->source_file_name;

     this->Place_String(&ptr->source_file_name,src_file_name);



     std::string src_dir = this->Cmp_Data_Ptr->src_sys_dir;

     this->Place_String(&ptr->source_file_dir,src_dir);


     std::string src_name_without_ext = this->Cmp_Data_Ptr->source_file_name_witout_ext;

     this->Place_String(&ptr->src_name_without_ext,src_name_without_ext);
     


     size_t src_name_size = src_file_name.length();
     
     for(size_t k=0;k<src_name_size;k++){

         ptr->object_file_name.push_back(src_file_name[k]);

         if(src_file_name[k]=='.'){

            break;
         }
     }

     ptr->object_file_name.push_back('o');
     ptr->object_file_name.shrink_to_fit();


     size_t dir_size = src_dir.length();


     for(size_t k=0;k<dir_size;k++){

         ptr->object_file_path.push_back(src_dir[k]);
     }

     if(this->opr_sis == 'w'){

        if( ptr->object_file_path.back() != '\\'){

            ptr->object_file_path.push_back('\\');
        }
     }
     else{
     
         if(this->opr_sis == 'l'){

            if(ptr->object_file_path.back() != '/'){

               ptr->object_file_path.push_back('/');
            }
         }
     }
        

     for(size_t k=0;k<src_name_size;k++){

        ptr->object_file_path.push_back(src_file_name[k]);

        if(src_file_name[k]=='.'){

          break;
        }
     }

     ptr->object_file_path.push_back('o');     

     ptr->object_file_path.shrink_to_fit();   
}




void Script_Data_Collector::Determine_Source_File_Compilation_Information_For_Simple_Search(Script_Data * ptr,

     std::string source_file_name){

     ptr->warehouse_path = this->warehouse_path;

     int record_index = 0;


      

     std::string git_record_dir = this->Simple_Data_Ptr->src_git_record_dir;

     this->Place_String(&ptr->source_file_git_record_dir,git_record_dir);


     std::string src_file_name = this->Simple_Data_Ptr->source_file_name;

     this->Place_String(&ptr->source_file_name,src_file_name);


     std::string src_dir = this->Simple_Data_Ptr->src_sys_dir;

     this->Place_String(&ptr->source_file_dir,src_dir);



     std::string src_name_without_ext = this->Simple_Data_Ptr->source_file_name_without_ext;
     
     this->Place_String(&ptr->src_name_without_ext,src_name_without_ext);
     

     size_t src_name_size = src_file_name.length();
     
     for(size_t k=0;k<src_name_size;k++){

         ptr->object_file_name.push_back(src_file_name[k]);

         if(src_file_name[k]=='.'){

            break;
         }
     }

     ptr->object_file_name.push_back('o');
     ptr->object_file_name.shrink_to_fit();


     size_t dir_size = src_dir.length();


     for(size_t k=0;k<dir_size;k++){

         ptr->object_file_path.push_back(src_dir[k]);
     }

     if(this->opr_sis == 'w'){

        if( ptr->object_file_path.back() != '\\'){

            ptr->object_file_path.push_back('\\');
        }
     }
     else{
     
         if(this->opr_sis == 'l'){

            if(ptr->object_file_path.back() != '/'){

               ptr->object_file_path.push_back('/');
            }
         }
     }
        



     for(size_t k=0;k<src_name_size;k++){

        ptr->object_file_path.push_back(src_file_name[k]);

        if(src_file_name[k]=='.'){

          break;
        }
     }

     ptr->object_file_path.push_back('o');     

     ptr->object_file_path.shrink_to_fit();   
}



void Script_Data_Collector::Determine_Header_Files_Inclusion_Number(Script_Data * ptr)
{
     // THIS MEMBER FUNCTION DETERMINES COMPLIATION PRIORITY OF THE SOURCE FILE

     ptr->dependency = this->Cmp_Data_Ptr->priority;
}


void Script_Data_Collector::Determine_Header_Files_Inclusion_Number_For_Simple_Construction(Script_Data * ptr)
{
     // THIS MEMBER FUNCTION DETERMINES COMPLIATION PRIORITY OF THE SOURCE FILE  

     ptr->dependency =  this->Simple_Data_Ptr->included_file_hdr_num;
}




void Script_Data_Collector::Determine_Make_File_Name(Script_Data * ptr){

   
     std::string src_name = ptr->src_name_without_ext;

     std::string make_ext = ".make";

     size_t file_name_size = src_name.length();

     for(size_t k=0;k<file_name_size;k++){

         ptr->make_file_name.push_back(src_name[k]);
     }

     size_t ext_size = make_ext.length();

     for(size_t k=0;k<ext_size;k++){

         ptr->make_file_name.push_back(make_ext[k]);
     }

     ptr->make_file_name.shrink_to_fit();
}


void Script_Data_Collector::Place_String(std::string * pointer, std::string string){

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

        pointer->push_back(string[i]);
     }

     pointer->shrink_to_fit();
}

