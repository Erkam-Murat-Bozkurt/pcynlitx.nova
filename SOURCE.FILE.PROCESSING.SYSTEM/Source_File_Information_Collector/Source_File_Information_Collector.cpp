


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

#include "Source_File_Information_Collector.hpp"

Source_File_Information_Collector::Source_File_Information_Collector(char opr_sis)
{
   this->operating_sis = opr_sis;
}


Source_File_Information_Collector::~Source_File_Information_Collector()
{
      this->Clear_Object_Memory();
}



/* THE CLASS INPUT FUNCTIONS ****************************************************************************/


void Source_File_Information_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Warehouse_Header_Dir();

     this->Determine_Warehouse_Object_Dir();
}


void Source_File_Information_Collector::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


void Source_File_Information_Collector::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;
}





/* THE MEMBER FUNCTIONS PERFORMING THE MAIN OPERATIONS ******************************************/


void Source_File_Information_Collector::Determine_Source_File_List()
{
      
     for(int i=0;i<this->Code_Rdr->Get_Project_Files_Number();i++)
     {
         std::string path = this->Code_Rdr->Get_File_Path(i);
      
         const FileData * ptr = this->Code_Rdr->Find_File_Data_From_Path(path);

         bool is_source_file = ptr->is_source_file;

         if(is_source_file){

            std::string source_file_name = ptr->file_name;

            Source_File_Data buffer;

            buffer.system_path = path;
            buffer.source_file_name = source_file_name;

            this->Src_Data_Holder.push_back(buffer);

            this->Clear_Buffer_Memory(buffer);
         }
      }      
}



void Source_File_Information_Collector::Extract_Dependency_Data(){  // Data extraction for whole project

     this->Clear_Dynamic_Memory();

     this->Determine_Source_File_List();
}



void Source_File_Information_Collector::Determine_Warehouse_Header_Dir()
{
     std::string warehouse_word = "WAREHOUSE";

     std::string header_directory = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t head_dir_size = header_directory.length();

     size_t wr_word_size  = warehouse_word.length();

     for(size_t i=0;i<warehouse_path_size;i++){

        this->warehouse_head_dir.push_back(this->warehouse_path[i]);
     }

     size_t index =  this->warehouse_head_dir.size(); // The last character index

     char last_character = this->warehouse_head_dir[index];

     if(this->operating_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_head_dir.push_back('\\');
        }
     }

     if(this->operating_sis == 'l'){

         if(last_character!= '/'){

            this->warehouse_head_dir.push_back('/');
         }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_head_dir.push_back(warehouse_word[i]);
     }


     index =  this->warehouse_head_dir.size(); // The last character index

     last_character = this->warehouse_head_dir[index];


     if(this->operating_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_head_dir.push_back('\\');
        }
     }

     if(this->operating_sis == 'l'){

        if(last_character != '/'){

           this->warehouse_head_dir.push_back('/');
        }
     }

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir.push_back(header_directory[i]);
     }
}



void Source_File_Information_Collector::Determine_Warehouse_Object_Dir(){

     std::string object_directory  = "PROJECT.OBJECT.FILES";

     std::string warehouse_word    = "WAREHOUSE";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_dir_size     = object_directory.length();

     size_t wr_word_size        = warehouse_word.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_obj_dir.push_back(this->warehouse_path[i]);
     }

     size_t index =  this->warehouse_path.size(); // The last character index

     char last_character = this->warehouse_path[index];


     if(this->operating_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_obj_dir.push_back('\\');
        }
     }

     if(this->operating_sis == 'l'){

        if(last_character != '/'){

            this->warehouse_obj_dir.push_back('/');
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir.push_back(warehouse_word[i]);
     }


     index =  this->warehouse_path.size(); // The last character index

     last_character = this->warehouse_path[index];

     if(this->operating_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_obj_dir.push_back('\\');
        }
     }

     if(this->operating_sis == 'l'){

        if(last_character != '/'){

           this->warehouse_obj_dir.push_back('/');
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir.push_back(object_directory[i]);
     }
}


bool  Source_File_Information_Collector::Is_Header_File(std::string path){

      const FileData * ptr = this->Code_Rdr->Find_File_Data_From_Path(path);

      bool is_header_file = ptr->is_header_file;

      return is_header_file;
}




/* MEMORY MANAGEMENT FUNCTIONS ******************************************************/


void Source_File_Information_Collector::Clear_Object_Memory()
{
     this->Clear_Dynamic_Memory();

     this->Clear_String_Memory(this->warehouse_path);

     this->Clear_String_Memory(this->warehouse_head_dir);

     this->Clear_String_Memory(this->warehouse_obj_dir);
}



void Source_File_Information_Collector::Clear_Dynamic_Memory()
{
        // Clearing the header data

      this->Clear_Headers_Data();
}



void Source_File_Information_Collector::Clear_Headers_Data()
{
     std::vector<Source_File_Data>::iterator ith;

     if(!this->Src_Data_Holder.empty()){

         for(auto ith=this->Src_Data_Holder.begin();

             ith<this->Src_Data_Holder.end();ith++)
         {
             this->Clear_String_Memory(ith->source_file_name);

             this->Clear_String_Memory(ith->system_path);

         }

         this->Src_Data_Holder.clear();

         this->Src_Data_Holder.shrink_to_fit();
      }
}



void Source_File_Information_Collector::Clear_Buffer_Memory(Source_File_Data & data)
{
     this->Clear_String_Memory(data.source_file_name);

     this->Clear_String_Memory(data.system_path);
}


void Source_File_Information_Collector::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
      }
}








  /* GETTER FUNCTIONS OF THE CLASS *******************************************************/


Source_File_Data Source_File_Information_Collector::Get_Dependency_Data(int num)
{
   return this->Src_Data_Holder[num];
}



std::vector<Source_File_Data> * Source_File_Information_Collector::Get_Source_File_Data_Address()
{
     return &this->Src_Data_Holder;
}



std::string Source_File_Information_Collector::Get_Warehouse_Headers_Dir(){

     return this->warehouse_head_dir;
}


std::string Source_File_Information_Collector::Get_Warehouse_Objetcs_Dir(){

     return this->warehouse_obj_dir;
}



std::string Source_File_Information_Collector::Get_Warehouse_Path(){

     return this->warehouse_path;
}


size_t Source_File_Information_Collector::Get_Dependency_Data_Size(){

       return this->Src_Data_Holder.size();
}
