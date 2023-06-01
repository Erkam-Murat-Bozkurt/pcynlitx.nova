


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

#include "Source_File_Dependency_ReOrderer.hpp"

Source_File_Dependency_ReOrderer::Source_File_Dependency_ReOrderer()
{

}


Source_File_Dependency_ReOrderer::~Source_File_Dependency_ReOrderer()
{
    this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_ReOrderer::Clear_Object_Memory()
{

}

void Source_File_Dependency_ReOrderer::Clear_Dynamic_Memory()
{


}

void Source_File_Dependency_ReOrderer::Receive_Dependency_Data(std::vector<std::vector<Header_Dependency>> * ptr){
 
      this->Vector_List_ptr = ptr;
}



void Source_File_Dependency_ReOrderer::Reorder_Dependency_Data(){

     this->Determine_Headers_Dependencies();

     this->Reorder_Data_Records();
}



void Source_File_Dependency_ReOrderer::Determine_Headers_Dependencies(){

     size_t List_Size = this->Vector_List_ptr->size();
 
     for(size_t i=0;i<List_Size;i++){

         std::vector<Header_Dependency> * ptr = &this->Vector_List_ptr->at(i);

         size_t sub_list_size = ptr->size();

         for(size_t k=0;k<sub_list_size;k++){

             std::string _file = ptr->at(k).Header_Name;

             int dep_num = this->Find_Header_Dependency(_file);

             ptr->at(k).included_file_hdr_num = dep_num;
         }
     }
}


int Source_File_Dependency_ReOrderer::Find_Header_Dependency(std::string hdr_name){

     this->dependency = 0;

     size_t List_Size = this->Vector_List_ptr->size();

     for(size_t i=0;i<List_Size;i++){
     
         std::vector<Header_Dependency> * searc_ptr = &this->Vector_List_ptr->at(i);
        
         size_t vec_size = searc_ptr->size();

         std::string _file = searc_ptr->at(0).root_header;

         if(this->CompareString(hdr_name,_file)){

            this->dependency = searc_ptr->size();

            if(this->dependency==1){
            
               std::string root_header = searc_ptr->at(0).root_header;
               std::string header_name = searc_ptr->at(0).Header_Name;

               if(this->CompareString(root_header,header_name)){
               
                  this->dependency = 0;
               }            
            }

            return this->dependency;
        }
     }

     return this->dependency;
}


void Source_File_Dependency_ReOrderer::Reorder_Data_Records(){

     size_t List_Size = this->Vector_List_ptr->size();

     for(size_t i=0;i<List_Size;i++){
     
         std::vector<Header_Dependency> * searc_ptr = &this->Vector_List_ptr->at(i);

         this->Reorder_Data_Records(searc_ptr);
     }
}

void Source_File_Dependency_ReOrderer::Reorder_Data_Records(std::vector<Header_Dependency> * data_ptr){
 
     size_t data_size = data_ptr->size();

     for(int i=0;i<data_size;i++){

         for(int j=i;j<data_size;j++){

             int dep_i = data_ptr->at(i).included_file_hdr_num;

             int dep_j = data_ptr->at(j).included_file_hdr_num;

             Header_Dependency temp;

             if( dep_i < dep_j){

                 temp  = data_ptr->at(i);

                 data_ptr->at(i) = data_ptr->at(j);

                 data_ptr->at(j) = temp;
              }
          }
     }
}


bool Source_File_Dependency_ReOrderer::CompareString(std::string firstString, 

     std::string secondString){

     this->isStringsEqual = false;

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


void Source_File_Dependency_ReOrderer::Print_Dependency_Data(){
     
     size_t data_size = this->Vector_List_ptr->size();

     for(size_t i=0;i<data_size;i++){

         std::vector<Header_Dependency> * ptr = &this->Vector_List_ptr->at(i);

         std::cout << "\n\n\n";

         std::vector<Header_Dependency>::iterator it;         

         if(ptr->size()>0){
         
            std::cout << "\n *****************************************************";

            std::cout << "\n FILE RESEARCHED:" << ptr->at(0).root_header;

            int counter=0;

            for(auto it=ptr->begin();it<ptr->end();it++){
         
                std::cout << "\n list - " << counter << " " << it->Header_Name;     

                std::cout << "\n Included Header Num:" << it->included_file_hdr_num;

                std::cout << "\n\n";

                counter++;
            }
         }
      }

}