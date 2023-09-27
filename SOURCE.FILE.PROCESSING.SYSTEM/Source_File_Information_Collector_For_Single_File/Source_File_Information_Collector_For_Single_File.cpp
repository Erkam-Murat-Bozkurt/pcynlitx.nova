



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

#include "Source_File_Information_Collector_For_Single_File.hpp"

Source_File_Information_Collector_For_Single_File::Source_File_Information_Collector_For_Single_File(char opr_sis)
{
   this->opr_sis = opr_sis;
}


Source_File_Information_Collector_For_Single_File::~Source_File_Information_Collector_For_Single_File()
{
      this->Clear_Object_Memory();
}





/* THE CLASS INPUT FUNCTIONS ****************************************************************************/


void Source_File_Information_Collector_For_Single_File::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Warehouse_Header_Dir();

     this->Determine_Warehouse_Object_Dir();
}


void Source_File_Information_Collector_For_Single_File::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


void Source_File_Information_Collector_For_Single_File::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;
}





/* THE MEMBER FUNCTIONS PERFORMING THE MAIN OPERATIONS ******************************************/


void Source_File_Information_Collector_For_Single_File::Extract_Dependency_Data(std::string src_file_path){  // Data extraction for whole project
     
     this->Determine_Root_Source_File_Header_Dependencies(src_file_path);

     this->Determine_Related_Source_Files_From_Header_Dependencies();

     const FileData * root_src_code = this->Code_Rdr->Find_File_Data_From_Path(src_file_path);

     Source_File_Data Base_File_Dt;

     Base_File_Dt.source_file_name = root_src_code->file_name;

     Base_File_Dt.system_path = root_src_code->sys_path;

     this->Src_Data_Holder.push_back(Base_File_Dt);

     for(std::size_t i =0; i<this->Dependent_Source_File_Names.size(); i++){

         const FileData * src_code = this->Code_Rdr->Find_File_Data_From_Name(this->Dependent_Source_File_Names.at(i));

         Source_File_Data Buffer_Dat;

         Buffer_Dat.source_file_name = this->Dependent_Source_File_Names.at(i);

         Buffer_Dat.system_path = src_code->sys_path;
             
         this->Src_Data_Holder.push_back(Buffer_Dat);
      }

      this->Src_Data_Holder.shrink_to_fit();
}



void Source_File_Information_Collector_For_Single_File::Determine_Root_Source_File_Header_Dependencies(std::string src_file_path)
{
     Dependency_Data_Extractor * Dep_Extractor = new Dependency_Data_Extractor(this->opr_sis);

     Dep_Extractor->Receive_Source_Code_Reader(this->Code_Rdr);

     Dep_Extractor->Extract_Dependency_Tree(src_file_path);
    

     std::vector<Search_Data> * Dep_Data_Ptr = Dep_Extractor->Get_Search_Data();

     for(size_t i=0;i<Dep_Data_Ptr->size();i++){

         this->Dep_Search_Data.push_back(Dep_Data_Ptr->at(i));
     }

     this->Dep_Search_Data.shrink_to_fit();

     Dep_Extractor->Clear_Object_Memory();

     delete Dep_Extractor;          
}



void Source_File_Information_Collector_For_Single_File::Determine_Related_Source_Files_From_Header_Dependencies(){

     size_t search_data_size = this->Dep_Search_Data.size();

     for(size_t i=0;i<search_data_size;i++){
       
         std::string hdr_name = this->Dep_Search_Data.at(i).name;

         std::string hdr_name_witout_ext;

         this->Find_File_Name_Without_Extantion(hdr_name,hdr_name_witout_ext);

         std::string source_file_name = hdr_name_witout_ext + ".cpp";
         
         if(this->Code_Rdr->Check_Repo_File_Status(source_file_name)){

             this->Dependent_Source_File_Names.push_back(source_file_name);
         }
     }
}




void Source_File_Information_Collector_For_Single_File::Find_File_Name_Without_Extantion(std::string hdr_name, 

     std::string & file_name_with_ext){

     size_t end_point =0;

     for(size_t i=hdr_name.size();i>0;i--){

         if(hdr_name[i] == '.'){

            end_point = i;
         }     
     }

     for(size_t i=0;i<end_point;i++){

         file_name_with_ext.push_back(hdr_name[i]);
     }

     file_name_with_ext.shrink_to_fit();
}




bool  Source_File_Information_Collector_For_Single_File::Is_Header_File(std::string hpath){

      return this->Header_Processor.Is_Header(hpath);
}


void Source_File_Information_Collector_For_Single_File::Determine_Warehouse_Header_Dir()
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

     if(this->opr_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_head_dir.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

         if(last_character!= '/'){

            this->warehouse_head_dir.push_back('/');
         }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_head_dir.push_back(warehouse_word[i]);
     }


     index =  this->warehouse_head_dir.size(); // The last character index

     last_character = this->warehouse_head_dir[index];


     if(this->opr_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_head_dir.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(last_character != '/'){

           this->warehouse_head_dir.push_back('/');
        }
     }

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir.push_back(header_directory[i]);
     }
}



void Source_File_Information_Collector_For_Single_File::Determine_Warehouse_Object_Dir(){

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


     if(this->opr_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_obj_dir.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(last_character != '/'){

            this->warehouse_obj_dir.push_back('/');
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir.push_back(warehouse_word[i]);
     }


     index =  this->warehouse_path.size(); // The last character index

     last_character = this->warehouse_path[index];

     if(this->opr_sis == 'w'){

        if(last_character != '\\'){

           this->warehouse_obj_dir.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(last_character != '/'){

           this->warehouse_obj_dir.push_back('/');
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir.push_back(object_directory[i]);
     }
}



/* MEMORY MANAGEMENT FUNCTIONS ******************************************************/


void Source_File_Information_Collector_For_Single_File::Clear_Object_Memory()
{
     this->Clear_Dynamic_Memory();

     this->Clear_String_Memory(this->warehouse_path);

     this->Clear_String_Memory(this->warehouse_head_dir);

     this->Clear_String_Memory(this->warehouse_obj_dir);
}



void Source_File_Information_Collector_For_Single_File::Clear_Dynamic_Memory()
{
        // Clearing the header data

      this->Clear_Headers_Data();

      this->Clear_Buffer_Memory();
}



void Source_File_Information_Collector_For_Single_File::Clear_Headers_Data()
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



void Source_File_Information_Collector_For_Single_File::Clear_Buffer_Memory(Source_File_Data & data)
{
     this->Clear_String_Memory(data.source_file_name);

     this->Clear_String_Memory(data.system_path);
}



void Source_File_Information_Collector_For_Single_File::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
      }
}






/* THE GETTER FUNCTIONS */


Source_File_Data Source_File_Information_Collector_For_Single_File::Get_Dependency_Data(int num)
{
   return this->Src_Data_Holder[num];
}



std::vector<Source_File_Data> * Source_File_Information_Collector_For_Single_File::Get_Source_File_Data_Address()
{
     return &this->Src_Data_Holder;
}



std::string Source_File_Information_Collector_For_Single_File::Get_Warehouse_Headers_Dir(){

     return this->warehouse_head_dir;
}


std::string Source_File_Information_Collector_For_Single_File::Get_Warehouse_Objetcs_Dir(){

     return this->warehouse_obj_dir;
}



std::string Source_File_Information_Collector_For_Single_File::Get_Warehouse_Path(){

     return this->warehouse_path;
}


size_t Source_File_Information_Collector_For_Single_File::Get_Dependency_Data_Size(){

       return this->Src_Data_Holder.size();
}
