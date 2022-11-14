

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

#include "Executable_MakeFile_DepDeterminer.hpp"

Executable_MakeFile_DepDeterminer::Executable_MakeFile_DepDeterminer(){

   this->Memory_Delete_Condition = false;

}

Executable_MakeFile_DepDeterminer::Executable_MakeFile_DepDeterminer(const

          Executable_MakeFile_DepDeterminer & orig){

}

Executable_MakeFile_DepDeterminer::~Executable_MakeFile_DepDeterminer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Executable_MakeFile_DepDeterminer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }
}

void Executable_MakeFile_DepDeterminer::Receive_Executable_MakeFile_DataCollector(Executable_MakeFile_DataCollector * Pointer){

     this->DataCollector = Pointer;
}

void Executable_MakeFile_DepDeterminer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->DataCollector->Receive_Descriptor_File_Reader(Des_Reader);
}

void Executable_MakeFile_DepDeterminer::Receive_Git_Record_Data(Git_File_List_Receiver * Pointer){

     this->DataCollector->Receive_Git_Record_Data(Pointer);
}

void Executable_MakeFile_DepDeterminer::Receive_Source_File_Info(Project_Files_Lister * Pointer){

     this->DataCollector->Receive_Source_File_Info(Pointer);
}

void Executable_MakeFile_DepDeterminer::Determine_Dependencies(){

     this->DepSelector.Receive_Executable_MakeFile_DataCollector(this->DataCollector);

     this->Receive_DataCollector_Info();

     this->Determine_Compile_Order();
}

void Executable_MakeFile_DepDeterminer::Determine_Compile_Order(){

     //this->Reverse_Order_Priorities();

     for(int i=0;i<this->header_file_number;i++){

        //bool rec_search  = this->Data_Ptr_CString[i].rcr_srch_complated;

        char * repo_path = this->Data_Ptr_CString[i].repo_path;

            this->DepSelector.Determine_Source_File_Dependencies(repo_path);

            int priority = this->DepSelector.Get_Dependency_List_Size();

            this->Data_Ptr_CString[i].priority = priority;

            this->DepSelector.Clear_Dynamic_Memory();
      }

      this->Order_Priorities();
}


void Executable_MakeFile_DepDeterminer::Search_Recursive_Include_Dependency(int index){

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

void Executable_MakeFile_DepDeterminer::Order_Priorities(){

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

void Executable_MakeFile_DepDeterminer::Reverse_Order_Priorities(){

     for(int i=0;i<this->header_file_number;i++){

           for(int j=i;j<this->header_file_number;j++){

               int dep_i = this->Data_Ptr_CString[i].priority;

               int dep_j = this->Data_Ptr_CString[j].priority;

               Compiler_Data_CString temp;

               if( dep_i > dep_j){

                   temp  = this->Data_Ptr_CString[j];

                   this->Data_Ptr_CString[j] = this->Data_Ptr_CString[i];

                   this->Data_Ptr_CString[i] = temp;
               }

               dep_i = this->Data_Ptr_CString[i].priority;

               dep_j = this->Data_Ptr_CString[j].priority;
            }
      }
}

void Executable_MakeFile_DepDeterminer::Receive_DataCollector_Info(){

      this->header_file_number = this->DataCollector->Get_Compiler_Data_Size();

      this->Data_Ptr_CString   = this->DataCollector->Get_Compiler_Data();
}

void Executable_MakeFile_DepDeterminer::Print_Compiler_Orders(){

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

Compiler_Data_CString Executable_MakeFile_DepDeterminer::Get_Compiler_Data(int i){

      return this->Data_Ptr_CString[i];
}

Compiler_Data_CString * Executable_MakeFile_DepDeterminer::Get_Compiler_Data_Pointer(){

      return this->Data_Ptr_CString;
}

int Executable_MakeFile_DepDeterminer::Get_Compiler_Data_Size(){

    return this->header_file_number;
}

char * Executable_MakeFile_DepDeterminer::Get_Warehouse_Headers_Dir(){

       return this->DataCollector->Get_Warehouse_Headers_Dir();
}

char * Executable_MakeFile_DepDeterminer::Get_Warehouse_Objetcs_Dir(){

       return this->DataCollector->Get_Warehouse_Objetcs_Dir();
}

char * Executable_MakeFile_DepDeterminer::Get_Warehouse_Path(){

       return this->DataCollector->Get_Warehouse_Path();
}
