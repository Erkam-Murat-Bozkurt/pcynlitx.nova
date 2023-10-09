





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

#include "Quick_Src_Dependency_Extractor.hpp"

Quick_Src_Dependency_Extractor::Quick_Src_Dependency_Extractor(char opr_sis) : Data_Setter(opr_sis)
{
   this->opr_sis = opr_sis;
}


Quick_Src_Dependency_Extractor::~Quick_Src_Dependency_Extractor()
{
      this->Clear_Object_Memory();
}





/* THE CLASS INPUT FUNCTIONS ****************************************************************************/


void Quick_Src_Dependency_Extractor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Warehouse_Header_Dir();

     this->Determine_Warehouse_Object_Dir();
}


void Quick_Src_Dependency_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


void Quick_Src_Dependency_Extractor::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->Data_Setter.Receive_Git_Data_Processor(ptr);
}





/* THE MEMBER FUNCTIONS PERFORMING THE MAIN OPERATIONS ******************************************/


void Quick_Src_Dependency_Extractor::Extract_Dependency_Data(std::string src_file_path){

     this->Extract_Dependency_Search_Data(src_file_path);

     std::string cmb_name;

     this->Extract_Directory_File_Name_Combination(src_file_path,cmb_name);

     this->Dep_Data.Combined_Header_Name = cmb_name;

     this->Set_Dependency_Data(src_file_path);
}



void Quick_Src_Dependency_Extractor::Extract_Dependency_Search_Data(std::string src_file_path){  // Data extraction for whole project
     
     Dependency_Data_Extractor * Dep_Extractor = new Dependency_Data_Extractor(this->opr_sis);

     Dep_Extractor->Receive_Source_Code_Reader(this->Code_Rdr);

     Dep_Extractor->Extract_Dependency_Tree(src_file_path);
    
     std::vector<Search_Data> * Dep_Data_Ptr = Dep_Extractor->Get_Search_Data();

     for(size_t i=0;i<Dep_Data_Ptr->size();i++){

         this->Dep_Search_Data.push_back(Dep_Data_Ptr->at(i));
     }

     this->Dep_Search_Data.shrink_to_fit();

     this->Receive_String_Vector(this->Root_File_External_Headers,Dep_Extractor->Get_External_Header_Files());

     Dep_Extractor->Clear_Object_Memory();

     delete Dep_Extractor;  
}



void Quick_Src_Dependency_Extractor::Set_Dependency_Data(std::string src_file_path){
     
     std::string src_file_name, file_dir, object_file_name,
     
     src_git_record_dir, file_name_without_ext, src_sys_dir;


     this->Data_Setter.Extract_Directory_From_Path(src_file_path,file_dir);

     this->Data_Setter.Extract_File_Name_From_Path(src_file_name,src_file_path);

     this->Data_Setter.Determine_Git_Record_Source_File_Directory(src_file_path,src_git_record_dir);

     this->Data_Setter.Determine_File_Name_Without_Ext(src_file_path,file_name_without_ext);

     this->Data_Setter.Determine_Object_File_Name(object_file_name,src_file_name);

     this->Data_Setter.Extract_Directory_From_Path(src_file_path,src_sys_dir);


     this->Data_Setter.Copy_String(this->Dep_Data.source_file_name,src_file_name);

     this->Data_Setter.Copy_String(this->Dep_Data.source_file_path,src_file_path);

     this->Data_Setter.Copy_String(this->Dep_Data.dir,file_dir);

     this->Data_Setter.Copy_String(this->Dep_Data.source_file_name_without_ext,file_name_without_ext);

     this->Data_Setter.Copy_String(this->Dep_Data.src_git_record_dir,src_git_record_dir);

     this->Data_Setter.Copy_String(this->Dep_Data.src_sys_dir,src_sys_dir);

     this->Data_Setter.Copy_String(this->Dep_Data.object_file_name,object_file_name);




     this->Clear_String_Memory(src_file_name);

     this->Clear_String_Memory(file_dir);

     this->Clear_String_Memory(object_file_name);

     this->Clear_String_Memory(src_git_record_dir);

     this->Clear_String_Memory(file_name_without_ext);
     
     this->Clear_String_Memory(src_sys_dir);



     size_t data_size = this->Dep_Search_Data.size();

     if(data_size>0){   // The header file have dependencies

        for(size_t i=0;i<data_size;i++){

            this->Dep_Data.Dependent_Header_Names.push_back(this->Dep_Search_Data.at(i).name);

            this->Dep_Data.Dependent_Header_Paths.push_back(this->Dep_Search_Data.at(i).path);

            this->Dep_Data.Include_Declerations.push_back(this->Dep_Search_Data.at(i).include_decleration);
        }
     }
}



void Quick_Src_Dependency_Extractor::Extract_Directory_File_Name_Combination(std::string path, 

     std::string & dir_file_com)
{
     size_t dec_size = path.length();

     size_t dir_char_num = 0, start_point = dec_size;

     for(size_t i=dec_size;i>0;i--){

         if((path[i] == '/') || (path[i] == '\\')){

            dir_char_num++;

            if(dir_char_num>1){

               start_point = i+1;        

               break;
            }
         }
         
         start_point--;        
     }
    
     size_t end_point = start_point;
     


     for(size_t i=dec_size;i>start_point;i--){

         if((path[i] == '/') || (path[i] == '\\')){

             end_point = i+1;        

             break;            
         }
         
         end_point--;        
     }


     for(size_t i=start_point;i<end_point;i++){

         dir_file_com.push_back(path[i]);
     }


     std::string hdr_name = this->Dep_Search_Data.at(0).name;

     size_t hdr_name_size = hdr_name.length();

     for(size_t i=0;i<hdr_name_size;i++){

         dir_file_com.push_back(hdr_name[i]);
     }

     dir_file_com.shrink_to_fit();
}


 const Simple_Source_File_Dependency * Quick_Src_Dependency_Extractor::Get_Simple_Source_File_Dependency() const
 {
       return &this->Dep_Data;
 } 



bool Quick_Src_Dependency_Extractor::Is_Header_File(std::string path){

     const FileData * ptr = this->Code_Rdr->Find_File_Data_From_Path(path);

     bool is_header_file = ptr->is_header_file;

     return is_header_file;
}


void Quick_Src_Dependency_Extractor::Determine_Warehouse_Header_Dir()
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



void Quick_Src_Dependency_Extractor::Determine_Warehouse_Object_Dir(){

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


void Quick_Src_Dependency_Extractor::Clear_Object_Memory()
{
     this->Clear_Dynamic_Memory();

     this->Clear_String_Memory(this->warehouse_path);

     this->Clear_String_Memory(this->warehouse_head_dir);

     this->Clear_String_Memory(this->warehouse_obj_dir);
}



void Quick_Src_Dependency_Extractor::Receive_String_Vector(std::vector<std::string> & target_vec,

     const std::vector<std::string> * vec){
   
     for(size_t i=0;i<vec->size();i++){

         target_vec.push_back(vec->at(i));
     }

     target_vec.shrink_to_fit();
}


void Quick_Src_Dependency_Extractor::Clear_Dynamic_Memory()
{
        // Clearing the header data

      this->Clear_Search_Data();

      this->Clear_External_Headers_Memory();
}

void Quick_Src_Dependency_Extractor::Clear_External_Headers_Memory(){

     if(!this->Root_File_External_Headers.empty()){

        for(size_t i=0;i<this->Root_File_External_Headers.size();i++){

            this->Clear_String_Memory(this->Root_File_External_Headers.at(i));
        }

        this->Root_File_External_Headers.clear();

        this->Root_File_External_Headers.shrink_to_fit();
     }
}



void Quick_Src_Dependency_Extractor::Clear_Search_Data()
{
     std::vector<Search_Data>::iterator ith;

     if(!this->Dep_Search_Data.empty()){

         for(auto ith=this->Dep_Search_Data.begin();

             ith<this->Dep_Search_Data.end();ith++)
         {

             this->Clear_String_Memory(ith->dir_file_comb);

             this->Clear_String_Memory(ith->include_decleration);

             this->Clear_String_Memory(ith->name);

             this->Clear_String_Memory(ith->path);

          }

          this->Dep_Search_Data.clear();

          this->Dep_Search_Data.shrink_to_fit();
      }
}


void Quick_Src_Dependency_Extractor::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
      }
}






/* THE GETTER FUNCTIONS */


const std::vector<Search_Data> * Quick_Src_Dependency_Extractor::Get_Dependency_Search_Data() const 
{
      return &this->Dep_Search_Data;
}


std::string Quick_Src_Dependency_Extractor::Get_Warehouse_Headers_Dir(){

     return this->warehouse_head_dir;
}


std::string Quick_Src_Dependency_Extractor::Get_Warehouse_Objetcs_Dir(){

     return this->warehouse_obj_dir;
}


std::string Quick_Src_Dependency_Extractor::Get_Warehouse_Path(){

     return this->warehouse_path;
}


const std::vector<std::string> * Quick_Src_Dependency_Extractor::Get_Root_File_External_Headers() const 
{
    return &this->Root_File_External_Headers;
}
