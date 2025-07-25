
/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Script_Data_Processor.hpp"

Script_Data_Processor::Script_Data_Processor(char opr_sis) :

  Data_Collector(opr_sis)

{
     this->Memory_Delete_Condition = false;

     this->source_file_num = 0;
}


Script_Data_Processor::~Script_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Memory_Delete_Condition = true;

       this->Clear_Object_Memory();
   }
}


void Script_Data_Processor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void Script_Data_Processor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}


void Script_Data_Processor::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr)
{
     this->Dep_Determiner = ptr;

     if(!this->Dep_Determiner->Get_Simple_Search_Status()){

         std::vector<Compiler_Data> * data_ptr = this->Dep_Determiner->Get_Compiler_Data_Address();

         this->source_file_num = data_ptr->size();
     }
     else{

           this->source_file_num = 1;
     }
}


void Script_Data_Processor::Process_Script_Data(){

     if(this->Des_Reader->Get_Warehouse_Location().empty()){

        std::cout << "\n There is no any decleration about";
        std::cout << "\n project warehouse location";

        exit(0);
     }

     if(this->source_file_num > 0){

        this->Determine_Script_Information();

        this->Determine_Script_Order();
     }

}

void Script_Data_Processor::Determine_Script_Information(){

     if(!this->Dep_Determiner->Get_Simple_Search_Status()){

        for(int i=0;i<this->source_file_num;i++){

            Compiler_Data Cmp_Dt = this->Dep_Determiner->Get_Compiler_Data(i);

            this->Data_Collector.Receive_Compiler_Data(&Cmp_Dt);
        
            this->Data_Collector.Determine_Source_File_Compilation_Information(&this->Temp_Data,Cmp_Dt.source_file_name);

            this->Data_Collector.Determine_Header_Files_Inclusion_Number(&this->Temp_Data);

            this->Data_Collector.Determine_Make_File_Name(&this->Temp_Data);

            this->Data.push_back(this->Temp_Data);

            this->Clear_Script_Data(&this->Temp_Data);
         }
     }
     else{

                const Simple_Source_File_Dependency * Cmp_Dt = this->Dep_Determiner->Get_Simple_File_Dependencies();

                this->Data_Collector.Receive_Simple_Dependency_Search_Data(Cmp_Dt);
        
                this->Data_Collector.Determine_Source_File_Compilation_Information_For_Simple_Search(&this->Temp_Data,Cmp_Dt->source_file_name);

                this->Data_Collector.Determine_Header_Files_Inclusion_Number_For_Simple_Construction(&this->Temp_Data);

                this->Data_Collector.Determine_Make_File_Name(&this->Temp_Data);

                this->Data.push_back(this->Temp_Data);

                this->Clear_Script_Data(&this->Temp_Data);
     }
}


void Script_Data_Processor::Determine_Script_Information_For_Simple_Search(){

}


void Script_Data_Processor::Determine_Script_Order(){

     for(int i=0;i<this->source_file_num;i++){

           for(int j=i;j<this->source_file_num;j++){

             int dep_i = this->Data.at(i).dependency;

             int dep_j = this->Data.at(j).dependency;

             Script_Data temp;

             if( dep_i > dep_j){

                 temp  = this->Data.at(i);

                 this->Data.at(i) = this->Data.at(j);

                 this->Data.at(j) = temp;
             }
           }
     }
}


void Script_Data_Processor::Clear_Dynamic_Memory(){

     this->Clear_Script_Data(&this->Data);
}

std::vector<Script_Data> *  Script_Data_Processor::Get_Script_Data_Address(){

     return &this->Data;
}


int Script_Data_Processor::Get_Source_File_Number(){

    return this->source_file_num;
}


void Script_Data_Processor::Clear_Script_Data(std::vector<Script_Data> * ptr){

     size_t data_size = ptr->size();

     for(size_t i=0;i<data_size;i++){
     

         this->Clear_String_Memory(&ptr->at(i).object_file_name);
         
         this->Clear_String_Memory(&ptr->at(i).object_file_path);

         this->Clear_String_Memory(&ptr->at(i).source_file_name);

         this->Clear_String_Memory(&ptr->at(i).source_file_dir);

         this->Clear_String_Memory(&ptr->at(i).source_file_git_record_dir);

         this->Clear_String_Memory(&ptr->at(i).make_file_name);

         this->Clear_String_Memory(&ptr->at(i).warehouse_path);

         this->Clear_String_Memory(&ptr->at(i).src_name_without_ext);

     }
 
}

void Script_Data_Processor::Clear_String_Memory(std::string * ptr){

     if(!ptr->empty()){
     
        ptr->clear();

        ptr->shrink_to_fit();     
     }
}

 void Script_Data_Processor::Clear_String_Vector(std::vector<std::string> * ptr){
 
      size_t data_size = ptr->size();

      for(size_t i=0;i<data_size;i++){
      
          this->Clear_String_Memory(&ptr->at(i));
      }

      ptr->clear();

      ptr->shrink_to_fit();
}


void Script_Data_Processor::Clear_Script_Data(Script_Data * ptr)
{  
     this->Clear_String_Memory(&this->Temp_Data.object_file_name);

     this->Clear_String_Memory(&this->Temp_Data.object_file_path);

     this->Clear_String_Memory(&this->Temp_Data.source_file_name);

     this->Clear_String_Memory(&this->Temp_Data.source_file_dir);

     this->Clear_String_Memory(&this->Temp_Data.source_file_git_record_dir);

     this->Clear_String_Memory(&this->Temp_Data.make_file_name);

     this->Clear_String_Memory(&this->Temp_Data.warehouse_path);

     this->Clear_String_Memory(&this->Temp_Data.src_name_without_ext);

}
