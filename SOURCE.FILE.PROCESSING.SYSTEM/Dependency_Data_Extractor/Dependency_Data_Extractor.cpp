


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

#include "Dependency_Data_Extractor.hpp"

Dependency_Data_Extractor::Dependency_Data_Extractor(char * des_file_path, char opr_sis)

    : Header_Processor(des_file_path,opr_sis)
{
   this->Memory_Delete_Condition = false;
}


Dependency_Data_Extractor::~Dependency_Data_Extractor()
{
    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Object_Memory();
    }    
}


void Dependency_Data_Extractor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Header_Processor.Clear_Object_Memory();
}

void Dependency_Data_Extractor::Clear_Dynamic_Memory()
{
     for(size_t i=0;i<this->searched_paths.size();i++){

         this->Clear_String_Memory(this->searched_paths.at(i).path);
         this->Clear_String_Memory(this->searched_paths.at(i).name);
     }

     this->searched_paths.clear();
     this->searched_paths.shrink_to_fit();
}


void Dependency_Data_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;
}


void Dependency_Data_Extractor::Extract_Dependency_Tree(std::string path){

     this->Clear_Dynamic_Memory();

     Search_Data Head;

     Head.path = path;
     Head.search_complated = false;

     int inc_num = this->Search_Dependencies(Head,this->searched_paths);


    for(size_t i=0;i<this->searched_paths.size();i++){

        if(!this->searched_paths.at(i).search_complated){

            inc_num = this->Search_Dependencies(this->searched_paths.at(i),this->searched_paths);

            this->searched_paths.at(i).search_complated = true;

            i=0;
         }
    }
}


int Dependency_Data_Extractor::Search_Dependencies(Search_Data & Src_Data, std::vector<Search_Data> & data)
{

    int inclusion_number = this->Determine_Inclusion_Number(Src_Data.path);

     /*  The inclusion number determined */

    Src_Data.search_complated = true;

    if(inclusion_number>0){

       std::vector<std::string> * FileContent = this->Get_File_Content(Src_Data.path);

       size_t FileSize = FileContent->size();

       for(size_t k=0;k<FileSize;k++){

           std::string string_line = FileContent->at(k);

           bool is_new_dep = this->Find_New_Dependency(string_line);

           std::string header_name = this->Find_Header_Name(string_line);

           if(is_new_dep){

              std::string hdr_sys_path =  this->Get_Header_System_Path(header_name);

              Search_Data temp;

            
              temp.path = hdr_sys_path;
              temp.name = header_name;
              temp.search_complated = false;

              data.push_back(temp);
           }            
        }        
      }
      

      data.shrink_to_fit();

      return inclusion_number;
}


bool Dependency_Data_Extractor::Find_New_Dependency(std::string string_line){

     bool is_new_dependency = false;

     bool is_include_decleration = this->Include_Decleration_Test(string_line);

     if(is_include_decleration){

        std::string header_name  = this->Find_Header_Name(string_line);

        bool is_repo_header_file = this->Is_This_Repo_HeaderFile(header_name);

        if(is_repo_header_file){

           bool is_already_searched = this->Is_This_File_Aready_Searched(header_name);

          if(!is_already_searched){

              is_new_dependency = true;

              return is_new_dependency;
          }
        }
     }

     return is_new_dependency;
}


int Dependency_Data_Extractor::Determine_Inclusion_Number(std::string path){

     int inclusion_number = 0;

     std::vector<std::string> * FileContent = this->Get_File_Content(path);

     size_t FileSize = FileContent->size();


     for(size_t k=0;k<FileSize;k++){

         std::string string_line = FileContent->at(k);

         bool is_include_decleration = this->Include_Decleration_Test(string_line);

         if(is_include_decleration){

            inclusion_number++;
         }

         this->Clear_String_Memory(string_line);
     }

     return inclusion_number;
}



bool Dependency_Data_Extractor::Is_This_Repo_HeaderFile(std::string name)
{
     this->is_this_repo_header = false;

     FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(name);

     bool is_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

     if(is_header){

        if(this->Code_Rd->Check_Repo_File_Status(name)){

            this->is_this_repo_header = true;
        }
     }

     return this->is_this_repo_header;
}


bool Dependency_Data_Extractor::Is_This_File_Aready_Searched(std::string name)
{
     this->This_File_Exist = false;

     size_t list_size = this->searched_paths.size();

     for(int i=0;i<list_size;i++){

         bool is_exist_on_the_list =
    
         this->CompareString(name,this->searched_paths.at(i).name);

         if(is_exist_on_the_list){

            this->This_File_Exist = true;

            return this->This_File_Exist;
         }
      }

      return this->This_File_Exist;
}




std::string Dependency_Data_Extractor::Find_Header_Name(std::string string)
{

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

     size_t end_point = start_point;

     for(size_t k=start_point;k<size;k++){

         if(string[k] == '\"'){

            break;
         }
         else{

              end_point++;
         }
     }

     std::string header_name;

     for(size_t i=start_point;i<end_point;i++){

         header_name.push_back(string[i]);
     }

     return header_name;
}



bool Dependency_Data_Extractor::Include_Decleration_Test(std::string string)
{
     this->include_decleration_cond = false;

     char include_key [] = "#include\"";  // double_quotation_mark

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



void Dependency_Data_Extractor::Extract_File_Name_From_Path(std::string * pointer,

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
         pointer->push_back(string[i]) ;
     }
}


bool Dependency_Data_Extractor::CompareString(std::string firstString, 

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




std::vector<std::string> * Dependency_Data_Extractor::Get_File_Content(std::string path){

     FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     return &FileDtPtr->FileContent;
}

std::string Dependency_Data_Extractor::Get_Header_System_Path(std::string header_name){

     std::string sys_path;

     FileData * Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);

     sys_path = Ptr->sys_path;

     return sys_path;
}

void Dependency_Data_Extractor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}


std::vector<Search_Data> * Dependency_Data_Extractor::Get_Search_Data(){

      return &this->searched_paths;
}