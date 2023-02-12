


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

Source_File_Compiler_Data_Extractor::Source_File_Compiler_Data_Extractor(char * des_file_path, char opr_sis) :

    File_Lister(des_file_path, opr_sis)
{

   this->Memory_Delete_Condition = false;

   this->operating_sis = opr_sis;

   this->File_Lister.Determine_Git_Repo_Info();         // Project_Files_Lister instance
}


Source_File_Compiler_Data_Extractor::~Source_File_Compiler_Data_Extractor()
{
    if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
    }
}


void Source_File_Compiler_Data_Extractor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         // Clearing the Compiler Data

         std::vector<Compiler_Data>::iterator it;

         if(!this->compiler_dt.empty()){

           for(auto it=this->compiler_dt.begin();it<this->compiler_dt.end();it++){

              this->Clear_Vector_Memory(&it->included_headers);

              this->Clear_Vector_Memory(&it->included_headers_paths);

              this->Clear_String_Memory(&it->repo_path);

              this->Clear_String_Memory(&it->header_name);

              this->Clear_String_Memory(&it->object_file_name);
           }
         }

        this->File_Lister.Clear_Dynamic_Memory();
     }
}


void Source_File_Compiler_Data_Extractor::Receive_Dependency_Data(std::vector<Headers_Data> * ptr,

     std::string wrd)
{
     this->headers_dt = ptr;

     this->warehouse_head_dir = wrd;
}


void Source_File_Compiler_Data_Extractor::Extract_Compiler_Data(){

     std::size_t dt_size = this->headers_dt->size();

     this->Memory_Delete_Condition = false;

     for(std::size_t i= 0;i<dt_size;i++){

         std::string path = this->headers_dt->at(i).repo_path;

         this->FileManager.Clear_Dynamic_Memory();

         this->FileManager.Read_File(path);


        if(this->headers_dt->at(i).inclusion_number > 1){

           Compiler_Data Temp_Data;

           Temp_Data.repo_path        = this->headers_dt->at(i).repo_path;

           Temp_Data.header_name      = this->headers_dt->at(i).header_name;

           Temp_Data.inclusion_number = this->headers_dt->at(i).inclusion_number;


           bool is_indep = this->is_this_independent_header(Temp_Data.header_name);

             if(!is_indep){

                this->Extract_Obj_File_Name_From_Header_Name(&(Temp_Data.object_file_name),

                Temp_Data.header_name);
             }

             Temp_Data.priority = Temp_Data.inclusion_number;

             Temp_Data.rcr_srch_complated = false;

             int FileSize = this->FileManager.GetFileSize();


             int inclusion_index = 0;

             for(int k=0;k<FileSize;k++){

                 std::string string = this->FileManager.GetFileLine(k);

                 // In order to remove possible spaces on the string

                 // a temporary string is constructed

                 this->Delete_Spaces_on_String(&string);

                 bool is_include_decleration = this->Include_Decleration_Test(string);

                 if(is_include_decleration){

                    std::string header_name;

                    this->Extract_Header_File_Name_From_Decleration(&header_name,string);

                    Temp_Data.included_headers.push_back(header_name);

                    std::string header_path_address;

                    this->Determine_Header_Repo_Warehouse_Path(&header_path_address,header_name,'w');

                    Temp_Data.included_headers_paths.push_back(header_path_address);
                  }
              }

              this->compiler_dt.push_back(Temp_Data);
          }
        }
}


void Source_File_Compiler_Data_Extractor::Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,

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

void Source_File_Compiler_Data_Extractor::Extract_Header_File_Name_From_Decleration(std::string * header_name,

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

     for(int i=start_point;i<end_point;i++)
     {
         header_name->push_back(string[i]);
     }
}


void Source_File_Compiler_Data_Extractor::Delete_Spaces_on_String(std::string * str)
{
     size_t string_size = str->length();
     bool search_cond = true;

     do{

         search_cond = false;

         for(size_t i=0;i<str->length();i++){

            if((*str)[i] == ' '){

               search_cond = true;

               str->erase(i,1);
            }
         }

     }while(search_cond);
}



bool Source_File_Compiler_Data_Extractor::Include_Decleration_Test(std::string string){

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


void Source_File_Compiler_Data_Extractor::Extract_Obj_File_Name_From_Header_Name(std::string * object_name,

     std::string header_name){

     size_t header_name_size = header_name.length();

     for(size_t i=0;i<header_name_size;i++){

         if(header_name[i] == '.'){

            break;
         }
         else{

               object_name->push_back(header_name[i]);
         }
     }

     object_name->push_back('.');

     object_name->push_back('o');

     object_name->shrink_to_fit();
}



bool Source_File_Compiler_Data_Extractor::is_this_independent_header(std::string header_name)
{
     this->is_independent_header = false;

     int ind_header_num = this->File_Lister.Get_Indenpendent_Header_Files_Number();

     for(int i=0;i<ind_header_num;i++){

         std::string ind_header_path = this->File_Lister.Get_Independent_Header_File(i);

         std::string ind_header = "";

         this->Extract_Header_File_Name_From_Path(&ind_header,ind_header_path);

         bool is_equal = this->Char_Processor.CompareString(header_name,ind_header);

         if(is_equal){

            this->is_independent_header = true;

            break;
         }
      }

      return this->is_independent_header;
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

     return this->compiler_dt[num];
}


std::vector<Compiler_Data> * Source_File_Compiler_Data_Extractor::Get_Compiler_Data_Address(){

     return &this->compiler_dt;
}
