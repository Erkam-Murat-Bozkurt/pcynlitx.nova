


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

Source_File_Dependency_Determiner::Source_File_Dependency_Determiner(){

   this->Memory_Delete_Condition = false;

}

Source_File_Dependency_Determiner::Source_File_Dependency_Determiner(const

          Source_File_Dependency_Determiner & orig){

}

Source_File_Dependency_Determiner::~Source_File_Dependency_Determiner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Source_File_Dependency_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->DepSelector.Clear_Dynamic_Memory();

         this->Information_Collector.Clear_Dynamic_Memory();
     }
}

void Source_File_Dependency_Determiner::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader = Pointer;

     this->Information_Collector.Receive_Descriptor_File_Reader(this->Des_Reader);

     this->Information_Collector.Collect_Make_File_Data();

     this->DepSelector.Receive_Source_File_Information_Collector(&this->Information_Collector);
}


void Source_File_Dependency_Determiner::Determine_Particular_Source_File_Dependencies(char * file_path){

     this->DepSelector.Clear_Dynamic_Memory();

     this->Memory_Delete_Condition = false;

     this->DepSelector.Determine_Source_File_Dependencies(file_path);
}

void Source_File_Dependency_Determiner::Determine_Dependencies(){

     this->Receive_Collector_Info();

     this->Determine_Compile_Order();
}

void Source_File_Dependency_Determiner::Determine_Compile_Order(){

     for(int i=0;i<this->header_file_number;i++){

         char * repo_path = this->Data_Ptr_CString[i].repo_path;

         this->DepSelector.Determine_Source_File_Dependencies(repo_path);

         int priority = this->DepSelector.Get_Dependency_List_Size();

         this->Data_Ptr_CString[i].priority = priority;

         this->DepSelector.Clear_Dynamic_Memory();
      }

      this->Order_Priorities();
}


void Source_File_Dependency_Determiner::Search_Recursive_Include_Dependency(int index){

     int inc_num = this->Data_Ptr_CString[index].inclusion_number;

     if(inc_num>0){

        for(int k=0;k<inc_num;k++){

            char * inc_header_name = this->Data_Ptr_CString[index].included_headers[k];

            for(int j=0;j<this->header_file_number;j++){

                char * repo_header = this->Data_Ptr_CString[j].header_name;

                bool is_equal = this->Char_Processor.CompareString(inc_header_name,repo_header);

                if(is_equal){

                   int priority = this->Data_Ptr_CString[j].priority;

                   if(priority == 0){

                      priority = 1;
                   }

                   this->Data_Ptr_CString[index].priority =

                   this->Data_Ptr_CString[index].priority + priority;
                }
            }
        }
      }
      else{

           this->Data_Ptr_CString[index].rcr_srch_complated = true;
      }
}

void Source_File_Dependency_Determiner::Order_Priorities(){

     for(int i=0;i<this->header_file_number;i++){

         for(int j=i;j<this->header_file_number;j++){

             int dep_i = this->Data_Ptr_CString[i].priority;

             int dep_j = this->Data_Ptr_CString[j].priority;

             Compiler_Data_CString temp;

             if( dep_i < dep_j){

                 temp  = this->Data_Ptr_CString[j];

                 this->Data_Ptr_CString[j] = this->Data_Ptr_CString[i];

                 this->Data_Ptr_CString[i] = temp;
              }
          }
      }
}


void Source_File_Dependency_Determiner::Receive_Collector_Info(){

      this->header_file_number = this->Information_Collector.Get_Compiler_Data_Size();

      this->Data_Ptr_CString   = this->Information_Collector.Get_Compiler_Data();
}

void Source_File_Dependency_Determiner::Print_Compiler_Orders(){

     for(int i=0;i<this->header_file_number;i++){

         std::cout << "\n\n";

         std::cout << "\n --------------------------------------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Data_Ptr_CString[i].header_name;

         std::cout << "\n PRIORITY:"

         <<  this->Data_Ptr_CString[i].priority;

         std::cout << "\n INCLUSION NUMBER:"

         <<  this->Data_Ptr_CString[i].inclusion_number;

         std::cout << "\n\n";
      }
}

void Source_File_Dependency_Determiner::Print_Dependency_List(){

     this->DepSelector.Print_Dependency_List();
}

Compiler_Data_CString Source_File_Dependency_Determiner::Get_Compiler_Data(int i){

      return this->Data_Ptr_CString[i];
}

Compiler_Data_CString * Source_File_Dependency_Determiner::Get_Compiler_Data_Pointer(){

      return this->Data_Ptr_CString;
}

int Source_File_Dependency_Determiner::Get_Compiler_Data_Size(){

    return this->header_file_number;
}

char * Source_File_Dependency_Determiner::Get_Warehouse_Headers_Dir(){

       return this->Information_Collector.Get_Warehouse_Headers_Dir();
}

char * Source_File_Dependency_Determiner::Get_Warehouse_Objetcs_Dir(){

       return this->Information_Collector.Get_Warehouse_Objetcs_Dir();
}

char * Source_File_Dependency_Determiner::Get_Warehouse_Path(){

       return this->Information_Collector.Get_Warehouse_Path();
}


Header_Dependency * Source_File_Dependency_Determiner::Get_Header_Dependency_List(){

      return this->DepSelector.Get_Header_Dependency_List();
}


char * Source_File_Dependency_Determiner::Get_Dependent_Header(int i){

       return this->DepSelector.Get_Dependent_Header(i);
}

char * Source_File_Dependency_Determiner::Get_Dependent_Header_Path(int i){

       return this->DepSelector.Get_Dependent_Header_Path(i);
}

int Source_File_Dependency_Determiner::Get_Dependency_List_Size(){

      return this->DepSelector.Get_Dependency_List_Size();
}
