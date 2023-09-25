


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

Dependency_Data_Extractor::Dependency_Data_Extractor(char opr_sis)

    : Header_Processor(opr_sis)
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
     this->Clear_Vector_Memory(this->External_Header_Files);

     for(size_t i=0;i<this->searched_paths.size();i++){

         this->Clear_String_Memory(this->searched_paths.at(i).path);
         this->Clear_String_Memory(this->searched_paths.at(i).name);
         this->Clear_String_Memory(this->searched_paths.at(i).include_decleration);         
     }

     this->searched_paths.clear();
     this->searched_paths.shrink_to_fit();

     this->Map_Inc_Dec.clear();     
}


void Dependency_Data_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;
}



void Dependency_Data_Extractor::Extract_Dependency_Tree(std::string path){

     this->Clear_Dynamic_Memory();

     this->Recursive_Dependency_Determination(path,this->searched_paths);

     this->Re_Order_Dependencies();     
}

int Dependency_Data_Extractor::Recursive_Dependency_Determination(std::string path, 

     std::vector<Search_Data> & data){

     Search_Data Head;

     Head.path = path;
     Head.search_complated = false;


     int inc_num = this->Search_Dependencies(Head,data);
    
     for(size_t i=0;i<data.size();i++){

        if(!data.at(i).search_complated){

            inc_num =  inc_num +  this->Search_Dependencies(data.at(i),data);

            data.at(i).search_complated = true;

            i=0;
         }
     }

     this->Map_Inc_Dec.clear();     

     return inc_num;
}



int Dependency_Data_Extractor::Search_Dependencies(Search_Data & Src_Data, std::vector<Search_Data> & data)
{

    int inclusion_number = this->Determine_Inclusion_Number(Src_Data.path);

     /*  The inclusion number determined */

    Src_Data.search_complated = true;
    Src_Data.dep_counter = inclusion_number;


    if(inclusion_number>0){

       const std::vector<std::string> * Include_Delerations = this->Get_File_Include_Delarations(Src_Data.path);

       size_t Decleration_Number = Include_Delerations->size();


       for(size_t k=0;k<Decleration_Number;k++){

           std::string inc_dec = Include_Delerations->at(k);
     
           bool is_new_dep = this->Check_New_Dependency_Status(inc_dec,data);
           
           if(is_new_dep){
              
              const FileData * File_Data_Ptr;
      
              Search_Data buffer;     // Temporary data decleration           

              if(this->Is_This_A_Combined_Include_Delaration(inc_dec)){

                 File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Directory_File_Name_Combination(inc_dec);
              }
              else{

                    File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Name(inc_dec);                                
              }


              buffer.name = File_Data_Ptr->file_name;  // This is the header name extracted from decleration

              buffer.path = File_Data_Ptr->sys_path;

              buffer.include_decleration = inc_dec;

              buffer.search_complated = false;

              data.push_back(buffer);

              this->Map_Inc_Dec.insert(std::make_pair(buffer.include_decleration,&data.back()));

           }    
        }           
    }
    else{
             if(this->Check_New_Dependency_Status_From_Path(Src_Data.path,data)){

               const FileData * File_Data_Ptr =  this->Code_Rd->Find_File_Data_From_Path(Src_Data.path);

               Search_Data buffer;
               buffer.path = File_Data_Ptr->sys_path;;
               buffer.include_decleration = File_Data_Ptr->cmbn_name;;
               buffer.name = File_Data_Ptr->file_name;;
               buffer.search_complated = false;

               data.push_back(buffer);

               this->Map_Inc_Dec.insert(std::make_pair(buffer.include_decleration,&data.back()));
            }
    }

    data.shrink_to_fit();

    return inclusion_number;
}



bool Dependency_Data_Extractor::Check_New_Dependency_Status(std::string string_line, 

     std::vector<Search_Data> & data)
{

     bool is_new_dependency = false;
        
     std::string include_decleration = string_line;
     

     if(this->Is_This_A_Combined_Include_Delaration(include_decleration)){

        bool is_repo_file = this->Code_Rd->Check_Repo_File_Status_From_Directory_File_Name_Combination(include_decleration);

        if(is_repo_file){

           bool is_repo_header_file = this->Is_This_Repo_HeaderFile(include_decleration);

           if(is_repo_header_file){
              
               bool is_already_searched = this->Is_This_File_Aready_Searched(include_decleration);

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

                bool is_already_searched = this->Is_This_File_Aready_Searched(include_decleration);

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



bool Dependency_Data_Extractor::Check_New_Dependency_Status_From_Path(std::string path, 

     std::vector<Search_Data> & data){

     bool is_new_dependency = false;

     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     bool is_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

     if(is_header){

        if(this->Code_Rd->Is_This_Repo_File(FileDtPtr->sys_path)){

            if(!this->Is_This_File_Aready_Searched(FileDtPtr->cmbn_name)){

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

         if(this->Code_Rd->Check_Repo_File_Status(include_declaration)){

            is_this_a_repo_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

            return is_this_a_repo_header;
         }             
     }
     
     return is_this_a_repo_header;
}




std::string Dependency_Data_Extractor::Get_File_Path_Form_Declaration(std::string include_declaration){

     bool is_combined_header_decleration = this->Is_This_A_Combined_Include_Delaration(include_declaration);

     const FileData * FileDtPtr;

     if(is_combined_header_decleration){

         FileDtPtr = this->Code_Rd->Find_File_Data_From_Directory_File_Name_Combination(include_declaration);
     }
     else{

         FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(include_declaration);
     }

     return FileDtPtr->sys_path;     
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


     for(size_t i=0;i<this->searched_paths.size();i++){

         std::string sub_path = this->searched_paths.at(i).path;

         std::vector<Search_Data> temp_vec;

         int inc_num = this->Recursive_Dependency_Determination(sub_path,temp_vec);
         
         if(inc_num != 0){

             this->searched_paths.at(i).dep_counter = temp_vec.size();

             this->searched_paths.at(i).dep_counter;

             this->searched_paths.at(i).path;

         }
         else{

               this->searched_paths.at(i).dep_counter = 0;              
         }

         temp_vec.clear();
         temp_vec.shrink_to_fit();                  
     }


     for(size_t i=0;i<this->searched_paths.size();i++){

         for(size_t j=0;j<this->searched_paths.size();j++){

             int dep_i = this->searched_paths.at(i).dep_counter;

             int dep_j = this->searched_paths.at(j).dep_counter;

             if(dep_j<dep_i){

                Search_Data temp = this->searched_paths.at(i);

                this->searched_paths.at(i) = this->searched_paths.at(j);

                this->searched_paths.at(j) = temp;
             }
         }                
     }
}



void Dependency_Data_Extractor::Insert_External_Header_File_For_Dependency(std::string hdr_file_name){

     this->External_Header_Files.push_back(hdr_file_name);

     this->External_Header_Files.shrink_to_fit();
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


const std::vector<std::string> * Dependency_Data_Extractor::Get_File_Include_Delarations(std::string path) const 
{
     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     return &FileDtPtr->include_declerations;
}

std::string Dependency_Data_Extractor::Get_Header_System_Path(std::string header_name) const
{
     return this->Code_Rd->Find_File_Data_From_Name(header_name)->sys_path;
}


const std::vector<std::string> * Dependency_Data_Extractor::Get_External_Header_Files() const
{

     return &this->External_Header_Files;
}

std::vector<Search_Data> * Dependency_Data_Extractor::Get_Search_Data(){

      return &this->searched_paths;
}