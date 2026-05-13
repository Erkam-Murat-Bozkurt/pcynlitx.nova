

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



#include "CMAKE_Target_List_Determiner.hpp"

CMAKE_Target_List_Determiner::CMAKE_Target_List_Determiner(char build_type)
{
     this->Memory_Delete_Condition = false;

     this->build_type = build_type;
}


CMAKE_Target_List_Determiner::~CMAKE_Target_List_Determiner(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Target_List_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(size_t i=0;i<this->target_list.size();i++){

             this->target_list.at(i).target_name.clear();

             this->target_list.at(i).target_name.shrink_to_fit();   
             
             this->target_list.at(i).DATA_PTR = nullptr;
         }

         this->target_list.clear();

         this->target_list.shrink_to_fit();
     }
}


void CMAKE_Target_List_Determiner::Determine_Target_Lists(){

     int target_index = 0;

     cmake_build::target_data first_target;

     first_target.target_name = this->Compiler_Data_Pointer->at(0).source_file_name_witout_ext;

     //first_target.target_name_with_ext = this->Compiler_Data_Pointer->at(0).source_file_name;

     first_target.data_index = target_index;

     first_target.DATA_PTR = &(this->Compiler_Data_Pointer->at(0));

     this->target_list.push_back(first_target);

     for(size_t i=1;i<this->Compiler_Data_Pointer->size();i++){

         cmake_build::target_data next_target;

         if(!this->Control_Dependency_For_Any_Previous_Target(i)){

            target_index++;

            next_target.target_name = this->Compiler_Data_Pointer->at(i).source_file_name_witout_ext;

            //next_target.target_name_with_ext = this->Compiler_Data_Pointer->at(i).source_file_name;

            next_target.data_index = target_index;

            next_target.DATA_PTR = &this->Compiler_Data_Pointer->at(i);

            this->target_list.push_back(next_target);
          }          
     }

     this->target_list.shrink_to_fit();


     char process_result [] = "\nThe CMAKE Targets determined..\n";

     std::cout << "\n";
     std::cout << process_result;
     std::cout << "\n";

     if(this->build_type == 'g'){

       this->SysInt->WriteTo_NamedPipe_FromChild(process_result);
     }
}


bool CMAKE_Target_List_Determiner::Control_Dependency_For_Any_Previous_Target(int index){

     bool dependency_to_previous_target = false;

     std::string current_target_name = this->Compiler_Data_Pointer->at(index).source_file_name_witout_ext;

     for(size_t i=0;i<this->target_list.size();i++){

         cmake_build::target_data control_target = this->target_list.at(i);

         const std::vector<std::string> * headers =  &(control_target.DATA_PTR->dependent_headers);

         for(size_t k=0;k<headers->size();k++){

             std::string file_name_with_ext;
            
             this->Find_File_Name_Without_Extension(headers->at(k),file_name_with_ext);

             if(current_target_name == file_name_with_ext){

                dependency_to_previous_target = true;

                return dependency_to_previous_target;
             }
         }
     }

     return dependency_to_previous_target;
}




void CMAKE_Target_List_Determiner::Find_File_Name_Without_Extension(std::string hdr_name, 

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

