


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

#include "Source_File_Dependency_Determiner.hpp"

Source_File_Dependency_Determiner::Source_File_Dependency_Determiner(char * des_file_path, char opr_sis) :

   DepSelector(des_file_path,opr_sis)
{

}

Source_File_Dependency_Determiner::~Source_File_Dependency_Determiner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Source_File_Dependency_Determiner::Clear_Dynamic_Memory(){

     this->DepSelector.Clear_Dynamic_Memory();
}

void Source_File_Dependency_Determiner::Determine_Particular_Source_File_Dependencies(std::string file_path){

     this->DepSelector.Clear_Dynamic_Memory();

     this->DepSelector.Determine_Source_File_Dependencies(file_path);
}

void Source_File_Dependency_Determiner::Determine_Dependencies(){

     this->Receive_Collector_Info();

     this->Determine_Compile_Order();
}

void Source_File_Dependency_Determiner::Receive_Collector_Info(){

      this->header_file_number = this->DepSelector.Get_Compiler_Data_Size();

      this->Compiler_Data_Ptr  = this->DepSelector.Get_Compiler_Data_Address();

      std::cout << "\n this->header_file_number:" << this->header_file_number;

      std::cout << "\n Data pointer assigned";

      std::cin.get();
}

void Source_File_Dependency_Determiner::Determine_Compile_Order(){

     for(int i=0;i<this->header_file_number;i++){

         std::string repo_path = this->Compiler_Data_Ptr->at(i).repo_path;

         std::cout << "\n repo_path:" << repo_path;

         std::cin.get();

         this->DepSelector.Determine_Source_File_Dependencies(repo_path);

         int priority = this->DepSelector.Get_Dependency_List_Size();

         std::cout << "\n priority:" << priority;

         std::cin.get();

         this->Compiler_Data_Ptr->at(i).priority = priority;

         this->DepSelector.Clear_Dynamic_Memory();
      }

      this->Order_Priorities();
}


void Source_File_Dependency_Determiner::Search_Recursive_Include_Dependency(int index){

     int inc_num = this->Compiler_Data_Ptr->at(index).inclusion_number;

     if(inc_num>0){

        for(int k=0;k<inc_num;k++){

            std::string inc_header_name = this->Compiler_Data_Ptr->at(index).included_headers[k];

            for(int j=0;j<this->header_file_number;j++){

                std::string repo_header = this->Compiler_Data_Ptr->at(j).header_name;

                bool is_equal = this->Char_Processor.CompareString(inc_header_name,repo_header);

                if(is_equal){

                   int priority = this->Compiler_Data_Ptr->at(j).priority;

                   if(priority == 0){

                      priority = 1;
                   }

                   this->Compiler_Data_Ptr->at(index).priority =

                   this->Compiler_Data_Ptr->at(index).priority + priority;
                }
            }
        }
      }
      else{

           this->Compiler_Data_Ptr->at(index).rcr_srch_complated = true;
      }
}

void Source_File_Dependency_Determiner::Order_Priorities(){

     for(int i=0;i<this->header_file_number;i++){

         for(int j=i;j<this->header_file_number;j++){

             int dep_i = this->Compiler_Data_Ptr->at(i).priority;

             int dep_j = this->Compiler_Data_Ptr->at(j).priority;

             Compiler_Data temp;

             if( dep_i < dep_j){

                 temp  = this->Compiler_Data_Ptr->at(j);

                 this->Compiler_Data_Ptr->at(j) = this->Compiler_Data_Ptr->at(i);

                 this->Compiler_Data_Ptr->at(i) = temp;
              }
          }
      }
}




void Source_File_Dependency_Determiner::Print_Compiler_Orders(){

     for(int i=0;i<this->header_file_number;i++){

         std::cout << "\n\n";

         std::cout << "\n --------------------------------------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Compiler_Data_Ptr->at(i).header_name;

         std::cout << "\n PRIORITY:"

         <<  this->Compiler_Data_Ptr->at(i).priority;

         std::cout << "\n INCLUSION NUMBER:"

         <<  this->Compiler_Data_Ptr->at(i).inclusion_number;

         std::cout << "\n\n";
      }
}

void Source_File_Dependency_Determiner::Print_Dependency_List(){

     this->DepSelector.Print_Dependency_List();
}

Compiler_Data Source_File_Dependency_Determiner::Get_Compiler_Data(int i){

      return this->Compiler_Data_Ptr->at(i);
}

std::vector<Compiler_Data> * Source_File_Dependency_Determiner::Get_Compiler_Data_Address()
{
      return this->Compiler_Data_Ptr;
}

int Source_File_Dependency_Determiner::Get_Compiler_Data_Size(){

    return this->header_file_number;
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Headers_Dir(){

       return this->DepSelector.Get_Warehouse_Headers_Dir();
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Objetcs_Dir(){

       return this->DepSelector.Get_Warehouse_Objetcs_Dir();
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Path(){

       return this->DepSelector.Get_Warehouse_Path();
}


Header_Dependency Source_File_Dependency_Determiner::Get_Header_Dependency_List(int num){

      return this->DepSelector.Get_Header_Dependency_List(num);
}


std::string Source_File_Dependency_Determiner::Get_Dependent_Header(int i){

       return this->DepSelector.Get_Dependent_Header(i);
}

std::string Source_File_Dependency_Determiner::Get_Dependent_Header_Path(int i){

       return this->DepSelector.Get_Dependent_Header_Path(i);
}

int Source_File_Dependency_Determiner::Get_Dependency_List_Size(){

      return this->DepSelector.Get_Dependency_List_Size();
}
