


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

Dependency_Data_Extractor::Dependency_Data_Extractor()
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


void Dependency_Data_Extractor::Receive_Operating_System(char opr_sis){

     this->Header_Processor.Receive_Operating_System(opr_sis);
}


void Dependency_Data_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;
}



void Dependency_Data_Extractor::Extract_Dependency_Tree(std::string path){

     this->Clear_Dynamic_Memory();

     this->Recursive_Dependency_Determination(path);
     
     this->Re_Order_Dependencies();     
}


void Dependency_Data_Extractor::Recursive_Dependency_Determination(std::string path){

     Search_Data Head;

     Head.path = path;
     Head.search_complated = false;


     this->Search_Dependencies(Head);
    
     for(size_t i=0;i<this->Dependent_Headers.size();i++){

        if(!this->Dependent_Headers.at(i).search_complated){

            this->Search_Dependencies(this->Dependent_Headers.at(i));

            this->Dependent_Headers.at(i).search_complated = true;

            i=0;
         }
     }


     if(!this->Map_Inc_Dec.empty()){

        this->Map_Inc_Dec.clear();
     }
}





int Dependency_Data_Extractor::Search_Dependencies(Search_Data & Src_Data)
{

    int inclusion_number = this->Determine_Inclusion_Number(Src_Data.path);          /*  The inclusion number determined */

    Src_Data.search_complated = true;

    Src_Data.dep_counter = inclusion_number;


    if(inclusion_number>0){

       this->Include_Delerations = this->Get_File_Include_Delarations(Src_Data.path);

       size_t Decleration_Number = this->Include_Delerations->size();


       for(size_t k=0;k<Decleration_Number;k++){

           std::string inc_dec = this->Include_Delerations->at(k);
     
           Search_Data buffer;

           if(this->Check_New_Dependency_Status(inc_dec)){

              this->Determine_Dependent_File_Data_From_Decleration(buffer,inc_dec);

              this->Dependent_Headers.push_back(buffer);

              this->Map_Inc_Dec.insert(std::make_pair(buffer.dir_file_comb,&this->Dependent_Headers.back()));
           }
        }      
    }
    else{

            if(this->Check_New_Dependency_Status_From_Path(Src_Data.path)){

               Search_Data buffer;

               this->Determine_Dependent_File_Data_From_Path(buffer,Src_Data.path);

               this->Dependent_Headers.push_back(buffer);

               this->Map_Inc_Dec.insert(std::make_pair(buffer.dir_file_comb,&this->Dependent_Headers.back()));
            }
    }


    this->Dependent_Headers.shrink_to_fit();

    return inclusion_number;
}





void Dependency_Data_Extractor::Determine_Dependent_File_Data_From_Decleration(Search_Data & buffer, std::string inc_dec){

     std::string dir_file_name_comb; 

     const FileData * File_Data_Ptr;
                
     if(this->Is_This_A_Combined_Include_Delaration(inc_dec)){
                 
        /*
          If it is a combined header decleration, there may be more directory information 
          on the include decleration. For instance the include decleration can be in the 
          form as "somedir/sample/sample.h"
                   
          The function "Extract_Directory_File_Name_Combination()" is used to find last 
          directory and file name
        */

        this->Extract_Directory_File_Name_Combination(inc_dec,dir_file_name_comb);  
                 
        File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Directory_File_Name_Combination(dir_file_name_comb);
     }
     else{

           File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Name(inc_dec);

           dir_file_name_comb = File_Data_Ptr->cmbn_name;                                
     }

     buffer.name = File_Data_Ptr->file_name;  // This is the header name extracted from decleration

     buffer.path = File_Data_Ptr->sys_path;

     buffer.include_decleration = inc_dec;

     buffer.dir_file_comb = dir_file_name_comb;

     buffer.search_complated = false;
}





void Dependency_Data_Extractor::Determine_Dependent_File_Data_From_Path(Search_Data & buffer, std::string path){

     const FileData * File_Data_Ptr =  this->Code_Rd->Find_File_Data_From_Path(path);

     buffer.path = File_Data_Ptr->sys_path;

     buffer.include_decleration = File_Data_Ptr->cmbn_name;

     buffer.dir_file_comb = File_Data_Ptr->cmbn_name;

     buffer.name = File_Data_Ptr->file_name;
               
     buffer.search_complated = false;
}



bool Dependency_Data_Extractor::Check_New_Dependency_Status(std::string string_line)
{

     bool is_new_dependency = false;
        
     std::string include_decleration = string_line;
     

     if(this->Is_This_A_Combined_Include_Delaration(include_decleration)){

        // There may be more directory information on the include decleration
        // For instance the include decleration can be in the form as "somedir/sample/sample.h"
        // The function Extract_Directory_File_Name_Combination is used to find last directory and file name

        std::string dir_file_name_comb;

        this->Extract_Directory_File_Name_Combination(include_decleration,dir_file_name_comb);  


        bool is_repo_file = this->Code_Rd->Check_Repo_File_Status_From_Directory_File_Name_Combination(dir_file_name_comb);

 
        if(is_repo_file){

           bool is_repo_header_file = this->Is_This_Repo_HeaderFile(dir_file_name_comb);

           if(is_repo_header_file){
              
               bool is_already_searched = this->Is_This_File_Aready_Searched(dir_file_name_comb);

               if(!is_already_searched){

                   is_new_dependency = true;

                   return is_new_dependency;
               }
           }
        }
        else{

              this->Insert_External_Header_File_For_Dependency(include_decleration);

              is_new_dependency = false;

              return is_new_dependency;
        }
     }
     else{

          bool is_repo_file = this->Code_Rd->Check_Repo_File_Status(string_line);

          if(is_repo_file){

             bool is_repo_header_file = this->Is_This_Repo_HeaderFile(include_decleration);
            
             if(is_repo_header_file){

                const FileData  * FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(include_decleration);

                std::string file_dir_comb = FileDtPtr->cmbn_name;

                bool is_already_searched = this->Is_This_File_Aready_Searched(file_dir_comb);

                if(!is_already_searched){

                    is_new_dependency = true;

                    return is_new_dependency;
                }
             }
           }
           else{

                  this->Insert_External_Header_File_For_Dependency(include_decleration);

                  is_new_dependency = false;

                  return is_new_dependency;
           }
     }

     return is_new_dependency;
}



bool Dependency_Data_Extractor::Check_New_Dependency_Status_From_Path(std::string path){

     bool is_new_dependency = false;

     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     bool is_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

     if(is_header){

        if(this->Code_Rd->Is_This_Repo_File(FileDtPtr->sys_path)){

            bool is_already_searched = this->Is_This_File_Aready_Searched(FileDtPtr->cmbn_name);

            if(!is_already_searched){

               is_new_dependency = true;

               return is_new_dependency;
            }
        }
        else{

              this->Insert_External_Header_File_For_Dependency(FileDtPtr->file_name);

              is_new_dependency = false;

              return is_new_dependency;
        }
     }

     return is_new_dependency;
}




bool Dependency_Data_Extractor::Is_This_A_Combined_Include_Delaration(std::string name)
{
     bool is_combined = false;

     size_t name_size = name.length();

     for(size_t i=0;i<name_size;i++){

         if(((name[i]=='/') || (name[i]=='\\'))){

            is_combined = true;

            return is_combined;
         }
     }

     return is_combined;
}



int Dependency_Data_Extractor::Determine_Inclusion_Number(std::string path){

     const std::vector<std::string> * Include_Delerations = this->Get_File_Include_Delarations(path);

     size_t inclusion_number = Include_Delerations->size();

     return inclusion_number;
}





bool Dependency_Data_Extractor::Is_This_Repo_HeaderFile(std::string include_declaration)
{
     bool is_this_a_repo_header = false;

     const FileData * FileDtPtr;

     bool is_combined_header_decleration = this->Is_This_A_Combined_Include_Delaration(include_declaration);

     if(is_combined_header_decleration){  // The decleration is in the form "sample/sample.h" (director + name)

        FileDtPtr = this->Code_Rd->Find_File_Data_From_Directory_File_Name_Combination(include_declaration);

        is_this_a_repo_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);;

        return is_this_a_repo_header;
     }
     else{

         FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(include_declaration);

         if(this->Code_Rd->Check_Repo_File_Status(include_declaration)){

            is_this_a_repo_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

            return is_this_a_repo_header;
         }             
     }
     
     return is_this_a_repo_header;
}



void Dependency_Data_Extractor::Extract_Directory_File_Name_Combination(std::string inc_dec, 

     std::string & dir_file_com)
{
     size_t dec_size = inc_dec.length();

     size_t dir_char_num = 0, start_point = dec_size;

     for(size_t i=dec_size;i>0;i--){

         if((inc_dec[i] == '/') || (inc_dec[i] == '\\')){

            dir_char_num++;

            if(dir_char_num>1){

               start_point = i+1;        

               break;
            }
         }
         
         start_point--;        
     }
    
     for(size_t i=start_point;i<dec_size;i++){

         dir_file_com.push_back(inc_dec[i]);
     }

     dir_file_com.shrink_to_fit();
}



bool Dependency_Data_Extractor::Is_This_File_Aready_Searched(std::string inc_dec)
{
     bool is_this_file_searched = false;

     if(this->Map_Inc_Dec.find(inc_dec)!=this->Map_Inc_Dec.end()){

        is_this_file_searched = true;
     }

    return is_this_file_searched;
}


void Dependency_Data_Extractor::Re_Order_Dependencies(){

     this->Swap_Memory = this->Dependent_Headers;

     for(size_t i=0;i<this->Swap_Memory.size();i++){

         this->Clear_Search_Data_Memory(this->Dependent_Headers);

         std::string sub_path = this->Swap_Memory.at(i).path;

         this->Recursive_Dependency_Determination(sub_path);
         
         size_t Dependency_Size = this->Dependent_Headers.size();

         if(Dependency_Size != 0){

             this->Swap_Memory.at(i).dep_counter = this->Dependent_Headers.size();
         }
         else{

               this->Swap_Memory.at(i).dep_counter = 0;              
         }              
     }

     this->Clear_Search_Data_Memory(this->Dependent_Headers);

     this->Dependent_Headers = this->Swap_Memory;

     this->Clear_Search_Data_Memory(this->Swap_Memory);



     for(size_t i=0;i<this->Dependent_Headers.size();i++){

         for(size_t j=0;j<this->Dependent_Headers.size();j++){

             int dep_i = this->Dependent_Headers.at(i).dep_counter;

             int dep_j = this->Dependent_Headers.at(j).dep_counter;

             if(dep_j<dep_i){

                Search_Data temp = this->Dependent_Headers.at(i);

                this->Dependent_Headers.at(i) = this->Dependent_Headers.at(j);

                this->Dependent_Headers.at(j) = temp;
             }
         }                
     }
}



void Dependency_Data_Extractor::Insert_External_Header_File_For_Dependency(std::string hdr_file_name){

     std::string fileName;

     if(this->Is_There_Directory_Character(hdr_file_name)){

        this->Extract_Header_File_Name(fileName,hdr_file_name);
     }
     else{

           fileName = hdr_file_name;
     }

     bool is_exist_on_records = this->Check_New_Record_Status(this->External_Header_Files,fileName);

     if(!is_exist_on_records){

         this->External_Header_Files.push_back(fileName);

         this->External_Header_Files.shrink_to_fit(); 
     }     
}


bool Dependency_Data_Extractor::Is_There_Directory_Character(std::string str){

     bool is_exist = false;

     for(size_t i=0;i<str.size();i++){

         if((str.at(i) == '\\') || (str.at(i) == '/' )){

             is_exist = true;

             return is_exist;
         }
     }

     return is_exist;
}


void Dependency_Data_Extractor::Extract_Header_File_Name(std::string & file_name, std::string str){
    
     this->Clear_String_Memory(file_name);

     size_t string_size = str.length();

     size_t start_point = string_size;

     for(size_t i=string_size;i>0;i--){

        if((str[i] == '/') || (str[i] == '\\')){

          break;
        }
        else{

            start_point--;
        }
     }

     for(size_t i=start_point+1;i<string_size;i++){

         file_name.push_back(str[i]);        
     }

     file_name.shrink_to_fit();
}



bool Dependency_Data_Extractor::Check_New_Record_Status(std::vector<std::string> & vec, std::string str){

     bool record_exist = false;

     for(size_t i=0;i<vec.size();i++){

         if(vec.at(i) == str){

            record_exist = true;

            return record_exist;
         }
     }
     
     return record_exist;
 }




// THE MEMORY MANAGEMENT FUNCTIONS

void Dependency_Data_Extractor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Header_Processor.Clear_Object_Memory();
}


void Dependency_Data_Extractor::Clear_Dynamic_Memory()
{
     this->Clear_Vector_Memory(this->External_Header_Files);

     this->Clear_Search_Data_Memory(this->Dependent_Headers);

     if(!this->External_Header_Files.empty()){

         this->External_Header_Files.clear();

         this->External_Header_Files.shrink_to_fit();
     }

     if(!this->Map_Inc_Dec.empty()){

         this->Map_Inc_Dec.clear();
     }     
}


void Dependency_Data_Extractor::Clear_Search_Data_Memory(std::vector<Search_Data> & data){
    
     if(!data.empty()){

         for(size_t i=0;i<data.size();i++){

             this->Clear_String_Memory(data.at(i).path);
             
             this->Clear_String_Memory(data.at(i).name);
             
             this->Clear_String_Memory(data.at(i).include_decleration);         
         }
    
         data.clear();
     
         data.shrink_to_fit();
     }
}

void Dependency_Data_Extractor::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         std::vector<std::string>::iterator it;

         auto begin = vec.begin();

         auto end   = vec.end();

         for(auto it=begin;it<end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}

void Dependency_Data_Extractor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}







// GETTER FUNCTIONS

const std::vector<std::string> * Dependency_Data_Extractor::Get_File_Include_Delarations(std::string path) const 
{
     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     return &FileDtPtr->include_declerations;
}


const std::vector<std::string> * Dependency_Data_Extractor::Get_External_Header_Files() const
{

     return &this->External_Header_Files;
}

std::vector<Search_Data> * Dependency_Data_Extractor::Get_Search_Data(){

      return &this->Dependent_Headers;
}