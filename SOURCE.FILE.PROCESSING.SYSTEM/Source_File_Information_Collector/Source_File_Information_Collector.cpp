


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

Source_File_Information_Collector::Source_File_Information_Collector(char opr_sis) :

   Header_Processor(opr_sis)
{
   this->operating_sis = opr_sis;
}


Source_File_Information_Collector::~Source_File_Information_Collector()
{
      this->Clear_Object_Memory();
}


void Source_File_Information_Collector::Clear_Object_Memory()
{
     this->Clear_Dynamic_Memory();

     this->Clear_String_Memory(&this->warehouse_path);

     this->Clear_String_Memory(&this->warehouse_head_dir);

     this->Clear_String_Memory(&this->warehouse_obj_dir);
}



void Source_File_Information_Collector::Clear_Dynamic_Memory()
{
        // Clearing the header data

      this->Clear_Headers_Data();

      this->Clear_Buffer_Memory();
}


void Source_File_Information_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Warehouse_Header_Dir();

     this->Determine_Warehouse_Object_Dir();
}


void Source_File_Information_Collector::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Src_File_Pr.Receive_Source_Code_Reader(ptr);
}


void Source_File_Information_Collector::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;
}


void Source_File_Information_Collector::Determine_Source_File_List()
{
     size_t fileNum = this->Code_Rdr->Get_Project_Files_Number();

     for(int i=0;i<fileNum;i++){

         std::string path = this->Code_Rdr->Get_File_Path(i);

         bool is_source_file = this->Src_File_Pr.Is_Source_File(path);

         if(is_source_file){

            this->Src_File_Pr.Determine_Source_File_Name(path);

            std::string source_file_name = this->Src_File_Pr.Get_Source_File_Name();

            this->buffer.system_path = path;
            this->buffer.source_file_name = source_file_name;
            this->buffer.inclusion_number = 0;
            this->buffer.priority = 0;
            this->buffer.rcr_srch_complated = false;


            this->Src_Data_Holder.push_back(this->buffer);

            this->Clear_Buffer_Memory();
         }
      }

      this->Header_Processor.Clear_Dynamic_Memory();
}

void Source_File_Information_Collector::Extract_Dependency_Data(){  // Data extraction for whole project

     this->Clear_Dynamic_Memory();

     this->Determine_Source_File_List();


     std::size_t dt_size = this->Src_Data_Holder.size();
     
     for(std::size_t i = 0;i<dt_size;i++){

         std::string path = this->Src_Data_Holder[i].system_path;

         FileData * src_code = this->Code_Rdr->Find_File_Data_From_Path(path);


         size_t line_num = src_code->FileContent.size();


         for(size_t k=0;k<line_num;k++){

             std::string string = src_code->FileContent.at(k);


             // In order to remove possible spaces on the string

             // a temporary string is constructed

             bool is_include_decleration = this->Include_Decleration_Test(string);

             if(is_include_decleration){

                std::string header_name;

                this->Extract_Header_File_Name_From_Decleration(&header_name,string);

                this->Src_Data_Holder[i].included_headers.push_back(header_name);

                std::string header_path_address;

                this->Determine_Header_Repo_Warehouse_Path(&header_path_address,header_name,'w');

                this->Src_Data_Holder[i].included_headers_paths.push_back(header_path_address);

                this->Src_Data_Holder[i].inclusion_number++;

                this->Src_Data_Holder[i].priority = this->Src_Data_Holder[i].inclusion_number;
              }
          }
      }
}


void Source_File_Information_Collector::Extract_Dependency_Data(std::string path)

{    // Data extraction for particular header file

     this->Clear_Dynamic_Memory();

     bool is_source_file = this->Src_File_Pr.Is_Source_File(path);


     if(is_source_file){

        this->Memory_Delete_Condition = false;

        this->Src_File_Pr.Determine_Source_File_Name(path);

        std::string source_file_name = this->Src_File_Pr.Get_Source_File_Name();


        this->buffer.system_path = path;
        this->buffer.source_file_name = source_file_name;
        this->buffer.inclusion_number = 0;
        this->buffer.priority = 0;
        this->buffer.rcr_srch_complated = false;
    
        FileData * src_code = this->Code_Rdr->Find_File_Data_From_Path(path);


        size_t line_num = src_code->FileContent.size();
   

        for(size_t k=0;k<line_num;k++){

            std::string string_line = src_code->FileContent.at(k);

            // In order to remove possible spaces on the string

            // a temporary string is constructed


            bool is_include_decleration = this->Include_Decleration_Test(string_line);

            if(is_include_decleration){

               std::string header_name;

               this->Extract_Header_File_Name_From_Decleration(&header_name,string_line);

               this->buffer.included_headers.push_back(header_name);

               std::string header_path_address;

               this->Determine_Header_Repo_Warehouse_Path(&header_path_address,header_name,'w');

               this->buffer.included_headers_paths.push_back(header_path_address);

               this->buffer.inclusion_number++;

               this->buffer.priority = this->buffer.inclusion_number;
            }
        }

        this->Src_Data_Holder.push_back(this->buffer);

        this->Clear_Buffer_Memory();
     }
}

void Source_File_Information_Collector::Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,

     std::string file_name, char opr_sis){

     size_t name_size = file_name.length();

     size_t wrd_path_size = this->warehouse_head_dir.length();

     for(size_t i=0;i<wrd_path_size;i++){

          wrd_path->push_back(this->warehouse_head_dir[i]);
     }

     if(opr_sis == 'w'){

         wrd_path->push_back('\\');
     }

     if(opr_sis == 'l'){

        wrd_path->push_back('/');
     }

     for(size_t i=0;i<name_size;i++){

         wrd_path->push_back(file_name[i]);
     }
}


 void Source_File_Information_Collector::Determine_Header_System_Path(std::string * sys_path,std::string path)
 {
      int index_size = this->Git_Data_Proc->Get_Git_File_Index_Size();

      for(int i=0;i<index_size;i++){
      
          std::string file_sys_path = this->Git_Data_Proc->Get_File_System_Path(i);

          bool is_repo_hdr = this->Header_Processor.Is_Header(file_sys_path);

          if(is_repo_hdr){
          
             this->Header_Processor.Determine_Header_File_Name_With_Extention(file_sys_path);       

             std::string head_name = this->Header_Processor.Get_Header_File_Name_With_Ext();

             this->Header_Processor.Determine_Header_File_Name_With_Extention(path);

             std::string ref_hdr_name = this->Header_Processor.Get_Header_File_Name_With_Ext();


             if(this->CompareString(head_name,ref_hdr_name)){
             
                size_t file_size = file_sys_path.size();

                for(size_t k=0;k<file_size;k++){
                
                    sys_path->push_back(file_sys_path[k]);
                }

                sys_path->shrink_to_fit();

                break;               
             }

          }
      }      
 }


void Source_File_Information_Collector::Extract_Header_File_Name_From_Decleration(std::string * header_name,

     std::string string){

     size_t size = string.length();

     int start_point = 0;

     for(size_t k=0;k<size;k++){

         if(string[k] == '\"'){

            break;
         }
         else{

            start_point++;
         }
     }

     start_point = start_point + 1;

     int end_point = start_point;

     for(size_t k=start_point;k<size;k++){

        if(string[k] == '\"'){

           break;
        }
        else{

             end_point++;
        }
     }

     for(int i=start_point;i<end_point;i++){

         header_name->push_back(string[i]);
     }
}


bool  Source_File_Information_Collector::Is_Header_File(std::string hpath){

      return this->Header_Processor.Is_Header(hpath);
}


bool Source_File_Information_Collector::Include_Decleration_Test(std::string string){

     this->include_decleration_cond = false;

     std::string include_key = "#include\"";  // double_quotation_mark


     bool is_this_include_dec

     = this->StringManager.CheckStringInclusion(string,include_key);


     bool char_before_sharp = false; //  sharp symbol = #

     if(string[0]!= '#'){

        char_before_sharp = true;
     }

     // In metaprograms, #include key is used on the inside code

     // Therefore, there may be false include therms which is used in the metaprograms

     // in order to produce header files. If there is a character before the sharp symbol,

     // it is a meta program code. ( simething like write{ #include \"sample.h\" })

     if(!char_before_sharp){

        if(is_this_include_dec){

           this->include_decleration_cond = true;
        }
     }

     return this->include_decleration_cond;
}


void Source_File_Information_Collector::Determine_Warehouse_Header_Dir(){

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


bool Source_File_Information_Collector::CompareString(std::string firstString, 

     std::string secondString){

     size_t firstStringLength  = firstString.length();

     size_t secondStringLength = secondString.length();

     if(firstStringLength==secondStringLength){

        for(size_t i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

            this->isStringsEqual = false;

            return this->isStringsEqual;
     }
}


void Source_File_Information_Collector::Clear_Headers_Data()
{
     std::vector<Source_File_Data>::iterator ith;

     if(!this->Src_Data_Holder.empty()){

         for(auto ith=this->Src_Data_Holder.begin();

             ith<this->Src_Data_Holder.end();ith++)
         {

             this->Clear_Vector_Memory(&ith->included_headers);

             this->Clear_Vector_Memory(&ith->included_headers_paths);

             this->Clear_String_Memory(&ith->source_file_name);
          }

          this->Src_Data_Holder.clear();

          this->Src_Data_Holder.shrink_to_fit();
      }
}



void Source_File_Information_Collector::Clear_Buffer_Memory()
{
     this->Clear_Vector_Memory(&this->buffer.included_headers);

     this->Clear_Vector_Memory(&this->buffer.included_headers_paths);

     this->Clear_String_Memory(&this->buffer.source_file_name);
}



void Source_File_Information_Collector::Clear_Vector_Memory(std::vector<std::string> * pointer)
{
      if(!pointer->empty()){

           std::vector<std::string>::iterator it;

           auto begin = pointer->begin();

           auto end   = pointer->end();

           for(auto it=begin;it<end;it++){

               if(!it->empty()){

                   it->clear();

                   it->shrink_to_fit();
               }
            }

           pointer->clear();

           pointer->shrink_to_fit();
      }
}


  void Source_File_Information_Collector::Clear_String_Memory(std::string * pointer){

       if(!pointer->empty()){

           pointer->clear();

           pointer->shrink_to_fit();
       }
  }


  Source_File_Data Source_File_Information_Collector::Get_Dependency_Data(int num)
  {
         return this->Src_Data_Holder[num];
  }

  std::vector<Source_File_Data> * Source_File_Information_Collector::Get_Headers_Data_Address()
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
