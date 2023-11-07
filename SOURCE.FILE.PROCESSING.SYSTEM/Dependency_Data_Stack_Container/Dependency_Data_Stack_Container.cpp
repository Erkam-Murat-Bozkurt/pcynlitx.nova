




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

#include "Dependency_Data_Stack_Container.hpp"

Dependency_Data_Stack_Container::Dependency_Data_Stack_Container()
{
   this->Memory_Delete_Condition = false;
}


Dependency_Data_Stack_Container::~Dependency_Data_Stack_Container()
{
    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Object_Memory();
    }    
}




void Dependency_Data_Stack_Container::Receive_New_Search_Data(std::string path, const Search_Data_Records * dt){

     const std::vector<Search_Data> * ptr = &dt->Dependent_Headers;

     if(ptr->size()>0){

       this->Search_Stack.push_back(*dt);

       this->Search_Stack_Map.insert(std::make_pair(path,this->Search_Stack.back()));
     }
}


bool Dependency_Data_Stack_Container::Is_Exist_OnSearchStack(std::string path){
     
     bool is_exist = false;

     if(this->Search_Stack_Map.find(path)!=this->Search_Stack_Map.end()){

        is_exist = true;
     }

     return is_exist;
}


const Search_Data_Records * Dependency_Data_Stack_Container::Find_Search_Data_From_Path(std::string path) const
{
    try {        

         return &this->Search_Stack_Map.at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Dependency_Data_Stack_Container instance,";

         std::cout << "\n Inside Find_Search_Data_From_Path,";

         std::cout << "\n the file located on " << path << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}







// THE MEMORY MANAGEMENT FUNCTIONS

void Dependency_Data_Stack_Container::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}


void Dependency_Data_Stack_Container::Clear_Dynamic_Memory()
{
     if(!this->Search_Stack.empty()){

        size_t stack_size = this->Search_Stack.size();

        for(size_t i=0;i<stack_size;i++){

            this->Clear_Search_Data_Memory(this->Search_Stack.at(i).Dependent_Headers);

            this->Clear_String_Memory(this->Search_Stack.at(i).path);
        }
     }

     if(!this->Search_Stack_Map.empty()){

         this->Search_Stack_Map.clear();
     }
}


void Dependency_Data_Stack_Container::Clear_Search_Data_Memory(std::vector<Search_Data> & data){
    
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



void Dependency_Data_Stack_Container::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         std::vector<std::string>::iterator it;

         auto begin = vec.begin();

         auto end   = vec.end();

         for(auto it=begin;it!=end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}

void Dependency_Data_Stack_Container::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}

void Dependency_Data_Stack_Container::Clear_Map_Memory(std::unordered_map<std::string, 
 
     Search_Data *> & Map){

     if(!Map.empty()){

         Map.clear();
     }
}






// GETTER FUNCTIONS

 const std::vector<Search_Data_Records> * Dependency_Data_Stack_Container::Get_Search_Stack(){

      return &this->Search_Stack;
 }
