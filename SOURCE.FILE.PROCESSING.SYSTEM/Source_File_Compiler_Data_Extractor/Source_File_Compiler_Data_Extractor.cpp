


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

Source_File_Compiler_Data_Extractor::Source_File_Compiler_Data_Extractor(char * des_file_path, 

    char opr_sis) :

    File_Lister(des_file_path, opr_sis)
{

   this->operating_sis = opr_sis;

   this->File_Lister.Determine_Git_Repo_Info();         // Project_Files_Lister instance
}


Source_File_Compiler_Data_Extractor::~Source_File_Compiler_Data_Extractor()
{
     this->Clear_Object_Memory();
}

void Source_File_Compiler_Data_Extractor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->File_Lister.Clear_Dynamic_Memory();
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

        for(auto it=Data->begin();it<Data->end();it++){

            this->Clear_Vector_Memory(&it->dependent_headers);

            this->Clear_Vector_Memory(&it->dependent_headers_paths);

            this->Clear_Vector_Memory(&it->dependent_objs);

            this->Clear_String_Memory(&it->source_file_path);

            this->Clear_String_Memory(&it->source_file_name);

            this->Clear_String_Memory(&it->object_file_name);
        }
      }

      Data->clear();

      Data->shrink_to_fit();
}



void Source_File_Compiler_Data_Extractor::Receive_Dependency_Data(std::vector<std::vector<Source_File_Dependency>> * ptr,

     std::string wrd)
{
     this->dep_data_ptr = ptr;

     this->warehouse_head_dir = wrd;
}


void Source_File_Compiler_Data_Extractor::Extract_Compiler_Data(){ 

     // Compiler data extraction for whole project

     std::size_t dt_size = this->dep_data_ptr->size();
     
     this->dep_data_ptr->shrink_to_fit();

     if(dt_size >= 8)
     {   
        int division = dt_size/8;
        
        for(int i=0;i<8;i++){

            int str  = i*division;

            int end  = (i+1)*division;

            if(i==7){
            
               end = dt_size;
            }


            this->threads[i] = std::thread(Source_File_Compiler_Data_Extractor::Process_Compiler_Data,
            
                            this,i,str,end);     
        }
    
        for(int i=0;i<8;i++){
     
            this->threads[i].join();
        }


        for(int i=0;i<8;i++){                     
        
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

         std::vector<Source_File_Dependency> * hdr_ptr = &this->dep_data_ptr->at(i);

         hdr_ptr->shrink_to_fit();

         size_t data_size = hdr_ptr->size();

         Compiler_Data buffer;

         if(data_size>0){

            buffer.source_file_name = hdr_ptr->at(0).source_file_name;

            buffer.source_file_path = hdr_ptr->at(0).source_file_path;

            this->Extract_Obj_File_Name_From_File_Name(&(buffer.object_file_name),
            
            buffer.source_file_name);

            buffer.priority = data_size;


            for(size_t k=0;k<data_size;k++){
            
                std::string hdr_name = hdr_ptr->at(k).Header_Name;

                std::string hdr_path = hdr_ptr->at(k).repo_warehouse_path;

                buffer.dependent_headers.push_back(hdr_name);

                buffer.dependent_headers_paths.push_back(hdr_path);                                                
            }

            buffer.dependent_headers.shrink_to_fit();

            buffer.dependent_headers_paths.shrink_to_fit();

            this->compiler_data.push_back(buffer);
         
            this->Clear_Buffer_Memory(&buffer);
         }
      }

      this->compiler_data.shrink_to_fit();
}


void Source_File_Compiler_Data_Extractor::Extract_Compiler_Data(std::string path)
{ 

     this->Clear_Dynamic_Memory();

     // Compiler data extraction for a particular source file

     std::vector<Source_File_Dependency> * src_ptr = &this->dep_data_ptr->at(0);

     size_t data_size = src_ptr->size();

     Compiler_Data buffer;

     if(data_size>0){

        //Compiler_Data buffer is definition of the member variable;              

        buffer.source_file_name = src_ptr->at(0).source_file_name;

        buffer.source_file_path = src_ptr->at(0).source_file_path;

        this->Extract_Obj_File_Name_From_File_Name(&buffer.object_file_name,
        
                                                    buffer.source_file_name);

        buffer.priority = src_ptr->at(0).base_included_hdr_num;
         

        for(size_t k=0;k<data_size;k++){
            
            std::string hdr_name = src_ptr->at(k).Header_Name;

            std::string hdr_path = src_ptr->at(k).repo_warehouse_path;

            std::string obj_name;

            this->Extract_Obj_File_Name_From_File_Name(&obj_name,hdr_name);

            buffer.dependent_headers.push_back(hdr_name);

            buffer.dependent_headers_paths.push_back(hdr_path);

            buffer.dependent_objs.push_back(obj_name);     
         }

         this->compiler_data.push_back(buffer);

         this->Clear_Buffer_Memory(&buffer);
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

            buffer.priority = src_ptr->at(0).base_included_hdr_num;
  

            this->Extract_Obj_File_Name_From_File_Name(&(buffer.object_file_name),
            
                buffer.source_file_name);



            for(size_t k=0;k<data_size;k++){
            
                std::string hdr_name = src_ptr->at(k).Header_Name;

                std::string hdr_path = src_ptr->at(k).repo_warehouse_path;

                buffer.dependent_headers.push_back(hdr_name);

                buffer.dependent_headers_paths.push_back(hdr_path);                                                
            }


            buffer.dependent_headers.shrink_to_fit();

            buffer.dependent_headers_paths.shrink_to_fit();

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



void Source_File_Compiler_Data_Extractor::is_this_independent_header(std::string header_name, 

bool & is_ind)

{
     is_ind = false;

     int ind_header_num = this->File_Lister.Get_Indenpendent_Header_Files_Number();
          
     for(int i=0;i<ind_header_num;i++){

         std::string ind_header_path = this->File_Lister.Get_Independent_Header_File(i);

         std::string ind_header = "";

         this->Extract_Header_File_Name_From_Path(&ind_header,ind_header_path);

         bool is_equal = this->Char_Processor.CompareString(header_name,ind_header);

         if(is_equal){

            is_ind = true;

            break;
         }
      }
}


void Source_File_Compiler_Data_Extractor::Extract_Header_File_Name_From_Path(std::string * name,

     std::string path)
{
     size_t string_size = path.length();

     size_t header_name_size = 0;

     for(size_t i = string_size;i>0;i--){

         if(this->operating_sis == 'w'){

            if(path[i] == '\\'){

               break;
            }
          }
          else{

             if(path[i] == '/'){

                break;
              }
          }

          header_name_size++;
      }

      size_t start_point = string_size - header_name_size + 1;

      for(size_t i = start_point;i<string_size;i++){

           name->push_back(path[i]);
      }

      name->shrink_to_fit();
}


void Source_File_Compiler_Data_Extractor::Clear_Buffer_Memory(Compiler_Data * ptr){

     this->Clear_Vector_Memory(&ptr->dependent_headers);

     this->Clear_Vector_Memory(&ptr->dependent_headers_paths);

     this->Clear_String_Memory(&ptr->source_file_path);

     this->Clear_String_Memory(&ptr->source_file_name);

     this->Clear_String_Memory(&ptr->object_file_name);
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
