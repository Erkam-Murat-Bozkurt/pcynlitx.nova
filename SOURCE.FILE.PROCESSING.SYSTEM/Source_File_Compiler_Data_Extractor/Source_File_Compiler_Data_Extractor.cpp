


/*

Copyright Â©  2021,  Erkam Murat Bozkurt

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

#include "Source_File_Compiler_Data_Extractor.hpp"

Source_File_Compiler_Data_Extractor::Source_File_Compiler_Data_Extractor(char opr_sis)
{

   this->operating_sis = opr_sis;
}


Source_File_Compiler_Data_Extractor::~Source_File_Compiler_Data_Extractor()
{
     this->Clear_Object_Memory();
}

void Source_File_Compiler_Data_Extractor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void Source_File_Compiler_Data_Extractor::Clear_Dynamic_Memory(){

     // Clearing the Compiler Data

     this->Clear_Buffer_Memory(&this->buffer);

     std::vector<Compiler_Data>::iterator it;

     this->Clear_Data_Memory(&this->compiler_data);
}


void Source_File_Compiler_Data_Extractor::Clear_Data_Memory(std::vector<Compiler_Data> * Data)
{
     // Clearing the Compiler Data

     std::vector<Compiler_Data>::iterator it;

     if(!Data->empty()){

        for(auto it=Data->begin();it!=Data->end();it++){

            this->Clear_Vector_Memory(&it->dependent_headers);

            this->Clear_Vector_Memory(&it->dependent_headers_dir);

            this->Clear_Vector_Memory(&it->upper_directories);

            this->Clear_String_Memory(&it->source_file_path);

            this->Clear_String_Memory(&it->source_file_name);

            this->Clear_String_Memory(&it->object_file_name);

            this->Clear_String_Memory(&it->source_file_name_witout_ext);
        }
      }

      Data->clear();

      Data->shrink_to_fit();
}



// THE CLASS INPUT FUNCTIONS


void Source_File_Compiler_Data_Extractor::Receive_Dependency_Data(Source_File_Dependency_Selector * ptr)
{
     this->Dep_Selector_Ptr = ptr;

     this->dep_data_ptr = this->Dep_Selector_Ptr->Get_Dependency_List_Adress();
}


void Source_File_Compiler_Data_Extractor::Receive_Single_File_Dependency_Data(Source_File_Dependency_Selector_For_Single_File * ptr)
{
     this->Dep_Selector_For_Single_File_Ptr = ptr;

     this->dep_data_ptr = this->Dep_Selector_For_Single_File_Ptr->Get_Dependency_List_Adress();
}


/**** THE CLASS MEMBER FUNTIONS PERFORMING MAIN OPERATIONS  ***************************************/


void Source_File_Compiler_Data_Extractor::Extract_Compiler_Data(){ 

     // Compiler data extraction for whole project

     std::size_t dt_size = this->dep_data_ptr->size();
     
     this->dep_data_ptr->shrink_to_fit();

     if(dt_size >= 16)
     {   
        int division = dt_size/16;
        
        for(int i=0;i<16;i++){

            int str  = i*division;

            int end  = (i+1)*division;

            if(i==15){
            
               end = dt_size;
            }


            this->threads[i] = std::thread(Source_File_Compiler_Data_Extractor::Process_Compiler_Data,
            
                            this,i,str,end);     
        }
    
        for(int i=0;i<16;i++){
     
            this->threads[i].join();
        }


        for(int i=0;i<16;i++){                     
        
            size_t d_size = this->compiler_dt[i].size();

            for(int k=0;k<d_size;k++){
              
                this->compiler_data.push_back(this->compiler_dt[i].at(k));
            }

            this->Clear_Data_Memory(&this->compiler_dt[i]);              
        }

        this->compiler_data.shrink_to_fit();

     }else{
     
           this->Extract_Compiler_Data_For_Single_Thread();
     }
}




void Source_File_Compiler_Data_Extractor::Extract_Compiler_Data_For_Single_Thread(){ 
     
     std::size_t dt_size = this->dep_data_ptr->size();
     
     for(std::size_t i= 0;i<dt_size;i++){

         std::vector<Source_File_Dependency> * src_ptr = &this->dep_data_ptr->at(i);

         src_ptr->shrink_to_fit();

         size_t data_size = src_ptr->size();

         Compiler_Data buffer;

         if(data_size>0){

            buffer.source_file_name = src_ptr->at(0).source_file_name;

            buffer.source_file_path = src_ptr->at(0).source_file_path;


            buffer.priority = data_size;
  

            buffer.src_git_record_dir = src_ptr->at(0).src_git_record_dir;

            buffer.source_file_name_witout_ext = src_ptr->at(0).source_file_name_without_ext; 

            buffer.src_sys_dir = src_ptr->at(0).src_sys_dir;



            this->Extract_Obj_File_Name_From_File_Name(&(buffer.object_file_name),
            
            buffer.source_file_name);

            buffer.priority = data_size;


            for(size_t k=0;k<data_size;k++){
            
                std::string hdr_name = src_ptr->at(k).Header_Name;

                std::string hdr_dir =  src_ptr->at(k).dir;            
                            
                buffer.dependent_headers_dir.push_back(hdr_dir);

                buffer.dependent_headers.push_back(hdr_name);
            }

            buffer.dependent_headers.shrink_to_fit();

            buffer.dependent_headers_dir.shrink_to_fit();

            this->compiler_data.push_back(buffer);
         
            this->Clear_Buffer_Memory(&buffer);
         }
      }

      this->compiler_data.shrink_to_fit();
}




void Source_File_Compiler_Data_Extractor::Process_Compiler_Data(int thm, int start, int end){
    
     for(std::size_t i=start;i<end;i++){

         std::vector<Source_File_Dependency> * src_ptr = &this->dep_data_ptr->at(i);

         src_ptr->shrink_to_fit();

         size_t data_size = src_ptr->size();

         Compiler_Data buffer;

         if(data_size>0){

            buffer.source_file_name = src_ptr->at(0).source_file_name;

            buffer.source_file_path = src_ptr->at(0).source_file_path;          

            buffer.priority = data_size;
  

            buffer.src_git_record_dir = src_ptr->at(0).src_git_record_dir;

            buffer.source_file_name_witout_ext = src_ptr->at(0).source_file_name_without_ext; 

            buffer.src_sys_dir = src_ptr->at(0).src_sys_dir;


            this->Extract_Obj_File_Name_From_File_Name(&(buffer.object_file_name),
            
                buffer.source_file_name);


            for(size_t k=0;k<data_size;k++){
            
                std::string hdr_name = src_ptr->at(k).Header_Name;

                std::string hdr_path = src_ptr->at(k).header_sys_path;

                std::string hdr_dir =  src_ptr->at(k).dir;

                std::string dep_obj =  src_ptr->at(k).object_file_name;           

                buffer.dependent_headers.push_back(hdr_name);

                buffer.dependent_headers_dir.push_back(hdr_dir);     

                std::string upper_dir;

                this->Find_Upper_Directory(upper_dir,hdr_dir);

                buffer.upper_directories.push_back(upper_dir);                                         
            }


            buffer.dependent_headers.shrink_to_fit();

            buffer.dependent_headers_dir.shrink_to_fit();

            buffer.upper_directories.shrink_to_fit();

            this->compiler_dt[thm].push_back(buffer);

            this->Clear_Buffer_Memory(&buffer);
         }
      }


      this->compiler_dt[thm].shrink_to_fit();
}


void Source_File_Compiler_Data_Extractor::Extract_Obj_File_Name_From_File_Name(std::string * object_name,

     std::string file_name){

     size_t name_size = file_name.length();


     for(size_t i=0;i<name_size;i++){

         if(file_name[i] == '.'){

            break;
         }
         else{

               object_name->push_back(file_name[i]);
         }
     }


     object_name->push_back('.');

     object_name->push_back('o');

     object_name->shrink_to_fit();
}



void Source_File_Compiler_Data_Extractor::Find_Upper_Directory(std::string & upper, std::string dir){

     size_t dir_size = dir.size();

     size_t end_point = dir_size;

     for(size_t i=dir_size;i>0;i--){

         if((dir[i]=='/') || (dir[i]=='\\')){

            end_point = i;

            break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         upper.push_back(dir[i]);
     }

     upper.shrink_to_fit();
}



void Source_File_Compiler_Data_Extractor::Clear_Buffer_Memory(Compiler_Data * ptr){

     this->Clear_Vector_Memory(&ptr->dependent_headers);

     this->Clear_Vector_Memory(&ptr->dependent_headers_dir);

     this->Clear_Vector_Memory(&ptr->upper_directories);

     this->Clear_String_Memory(&ptr->source_file_path);

     this->Clear_String_Memory(&ptr->source_file_name);

     this->Clear_String_Memory(&ptr->object_file_name);

     this->Clear_String_Memory(&ptr->source_file_name_witout_ext);

     this->Clear_String_Memory(&ptr->src_git_record_dir);

     this->Clear_String_Memory(&ptr->src_sys_dir);
}




void Source_File_Compiler_Data_Extractor::Clear_Vector_Memory(std::vector<std::string> * pointer)
{
     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();

     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

         if(!it->empty()){

             it->clear();

             it->shrink_to_fit();
         }
      }

      if(!pointer->empty()){

          pointer->clear();

          pointer->shrink_to_fit();
      }
}


void Source_File_Compiler_Data_Extractor::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
    }
}


Compiler_Data Source_File_Compiler_Data_Extractor::Get_Compiler_Data(int num){

     return this->compiler_data[num];
}


std::vector<Compiler_Data> * Source_File_Compiler_Data_Extractor::Get_Compiler_Data_Address(){

     return &this->compiler_data;
}
