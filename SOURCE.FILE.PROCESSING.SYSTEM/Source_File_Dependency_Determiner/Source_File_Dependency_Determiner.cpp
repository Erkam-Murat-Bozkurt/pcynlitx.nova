


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

   DepSelector(opr_sis), Com_Data_Extractor(opr_sis), Code_Rd(opr_sis)
{

}

Source_File_Dependency_Determiner::~Source_File_Dependency_Determiner(){

    this->Clear_Dynamic_Memory();
}

void Source_File_Dependency_Determiner::Clear_Object_Memory(){

     this->Com_Data_Extractor.Clear_Dynamic_Memory();

     this->Code_Rd.Clear_Object_Memory();

     this->DepSelector.Clear_Object_Memory();

     this->Clear_Dynamic_Memory();
}

void Source_File_Dependency_Determiner::Clear_Dynamic_Memory(){

     this->DepSelector.Clear_Dynamic_Memory();     
}


void Source_File_Dependency_Determiner::Receive_Descriptor_File_Reader(Descriptor_File_Reader *ptr){
     
     this->Code_Rd.Receive_Descriptor_File_Reader(ptr);
}

void Source_File_Dependency_Determiner::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->Code_Rd.Receive_Git_Data_Processor(this->Git_Data_Proc);

     this->Code_Rd.Read_Project_Source_Code_Files();

     this->DepSelector.Receive_Source_Code_Reader(&this->Code_Rd);

     this->Src_Processor.Receive_Source_Code_Reader(&this->Code_Rd); 

     this->Com_Data_Extractor.Receive_Git_Data_Processor(ptr);

     this->DepSelector.Receive_Git_Data_Processor(ptr);
}


void Source_File_Dependency_Determiner::Collect_Dependency_Information(std::string path){

     this->Clear_Dynamic_Memory();

     this->DepSelector.Determine_Source_File_Dependencies(path);

     this->Warehouse_Headers_Dir = this->DepSelector.Get_Warehouse_Headers_Dir();

     this->Warehouse_Objetcs_Dir = this->DepSelector.Get_Warehouse_Objetcs_Dir();

     this->Warehouse_Path = this->DepSelector.Get_Warehouse_Path();

     std::vector<std::vector<Source_File_Dependency>> * s_ptr  
     
               = this->DepSelector.Get_Dependency_List_Adress();
 
     std::string wrd_hdr_dir = this->DepSelector.Get_Warehouse_Headers_Dir();

     this->Com_Data_Extractor.Receive_Dependency_Data(s_ptr,wrd_hdr_dir);

     this->Com_Data_Extractor.Extract_Compiler_Data(path);

     this->Compiler_Data_Ptr = this->Com_Data_Extractor.Get_Compiler_Data_Address();

     this->data_size = this->Compiler_Data_Ptr->size();

     this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_Determiner::Collect_Dependency_Information(){

      this->Clear_Dynamic_Memory();

      this->DepSelector.Determine_Source_File_Dependencies();

      this->Warehouse_Headers_Dir = this->DepSelector.Get_Warehouse_Headers_Dir();

      this->Warehouse_Objetcs_Dir = this->DepSelector.Get_Warehouse_Objetcs_Dir();

      this->Warehouse_Path = this->DepSelector.Get_Warehouse_Path();

      std::vector<std::vector<Source_File_Dependency>> * s_ptr  
      
      = this->DepSelector.Get_Dependency_List_Adress();

      std::string wrd_hdr_dir = this->DepSelector.Get_Warehouse_Headers_Dir();      

      this->Com_Data_Extractor.Receive_Dependency_Data(s_ptr,wrd_hdr_dir);

      this->Com_Data_Extractor.Extract_Compiler_Data();

      this->Compiler_Data_Ptr = this->Com_Data_Extractor.Get_Compiler_Data_Address();

      this->data_size = this->Compiler_Data_Ptr->size();

      this->Order_Priorities();

      this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_Determiner::Order_Priorities(){

     for(int i=0;i<this->data_size;i++){

         for(int j=i;j<this->data_size;j++){

             int dep_i = this->Compiler_Data_Ptr->at(i).priority;

             int dep_j = this->Compiler_Data_Ptr->at(j).priority;

             Compiler_Data temp;

             if( dep_i < dep_j){

                 temp  = this->Compiler_Data_Ptr->at(i);

                 this->Compiler_Data_Ptr->at(i) = this->Compiler_Data_Ptr->at(j);

                 this->Compiler_Data_Ptr->at(j) = temp;
              }
          }
      }
}

bool Source_File_Dependency_Determiner::Is_Source_File(std::string path){

      return this->Src_Processor.Is_Source_File(path);
}

bool Source_File_Dependency_Determiner::Is_Header_File(std::string hpath){

     return this->DepSelector.Is_Header_File(hpath);
}


void Source_File_Dependency_Determiner::Print_Compiler_Orders(){

     for(int i=0;i<this->data_size;i++){

         std::cout << "\n\n";

         std::cout << "\n ------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Compiler_Data_Ptr->at(i).source_file_name;

         std::cout << "\n HEADER PATH:"

         <<  this->Compiler_Data_Ptr->at(i).source_file_path;

         std::cout << "\n PRIORITY:"

         <<  this->Compiler_Data_Ptr->at(i).priority;

         std::vector<std::string> * Dep_Headers = &this->Compiler_Data_Ptr->at(i).dependent_headers;


         size_t dep_size = Dep_Headers->size();

         for(size_t k=0;k<dep_size;k++){
         
             std::cout << "\n Dependent header:" << Dep_Headers->at(k);         
         }

         std::vector<std::string> * Dep_Headers_Paths = &this->Compiler_Data_Ptr->at(i).dependent_headers_paths;


         for(size_t k=0;k<dep_size;k++){
         
             std::cout << "\n Dependent header path:" << Dep_Headers_Paths->at(k);         
         }

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

    return this->data_size;
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Headers_Dir(){

       return this->Warehouse_Headers_Dir;
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Objetcs_Dir(){

       return this->Warehouse_Objetcs_Dir;
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Path(){

       return this->Warehouse_Path;
}
