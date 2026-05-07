


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



#include "CMAKE_Target_List_Data_Processor.hpp"

CMAKE_Target_List_Data_Processor::CMAKE_Target_List_Data_Processor(char build_type)
{
     this->Memory_Delete_Condition = false;

     this->build_type = build_type;
}


CMAKE_Target_List_Data_Processor::~CMAKE_Target_List_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Target_List_Data_Processor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

     }
}


void CMAKE_Target_List_Data_Processor::Process_Target_List_Data(){

      

     for(size_t i=0;i<this->Target_List_Data_Ptr->size();i++){

         cmake_build::target_data target_dt = this->Target_List_Data_Ptr->at(i);

         const std::vector<std::string> * dep_headers = &(target_dt.DATA_PTR->dependent_headers);


         std::vector<cmake_build::target_dependency_data> vec_data;
        
         for(size_t k=0;k<dep_headers->size();k++){

             cmake_build::target_dependency_data target_;

             std::string file_name_without_ext;

             this->Find_File_Name_Without_Extension(dep_headers->at(k),file_name_without_ext);

             const Compiler_Data * COM_PTR = Find_Compiler_Data_From_File_Name(file_name_without_ext);

             if(COM_PTR != nullptr){

                 target_.dep_data = COM_PTR;

                 target_.dep_name = file_name_without_ext;
             }

             vec_data.push_back(target_);
         }

         vec_data.shrink_to_fit();

         this->Target_List_Dependeny_Data.push_back(vec_data);
     }

     this->Target_List_Dependeny_Data.shrink_to_fit();
}





void CMAKE_Target_List_Data_Processor::Find_File_Name_Without_Extension(std::string hdr_name, 

     std::string & file_name_with_ext){

     size_t end_point =0;

     for(size_t i=hdr_name.size();i>0;i--){

         if(hdr_name[i] == '.'){

            end_point = i;
         }     
     }

     for(size_t i=0;i<end_point;i++){

         file_name_with_ext.push_back(hdr_name[i]);
     }

     file_name_with_ext.shrink_to_fit();
}

const Compiler_Data * CMAKE_Target_List_Data_Processor::Find_Compiler_Data_From_File_Name(std::string file_name){

      for(size_t i=0;i<this->Compiler_Data_Pointer->size();i++){

          std::string name_without_ext  = this->Compiler_Data_Pointer->at(i).source_file_name_witout_ext;

          if(name_without_ext == file_name){

             return &this->Compiler_Data_Pointer->at(i);
          }
      }

      return nullptr;
}

void CMAKE_Target_List_Data_Processor::Print_Processed_Data(){

     for(size_t i=0;i<this->Target_List_Dependeny_Data.size();i++){
        
         std::vector<cmake_build::target_dependency_data> * Dep_Data_Ptr = 

         &this->Target_List_Dependeny_Data.at(i);

         for(size_t k=0;k<Dep_Data_Ptr->size();k++){

             std::cout << "\n Name:" << Dep_Data_Ptr->at(i).dep_name;

             std::cout << "\n Name:" << Dep_Data_Ptr->at(i).dep_data->source_file_name_witout_ext;
         }
     }
}