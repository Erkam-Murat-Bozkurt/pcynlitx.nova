

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



#include "CMAKE_Target_List_Data_Structure_Constructor.hpp"

CMAKE_Target_List_Data_Structure_Constructor::CMAKE_Target_List_Data_Structure_Constructor(char * DesPath, char opr_sis, char build_type) :

     Meta_Data_Collector(DesPath,opr_sis,build_type), 

     Target_List_Determiner(build_type),

     Target_List_Data_Processor(build_type)
{
     this->Memory_Delete_Condition = false;

     
}


CMAKE_Target_List_Data_Structure_Constructor::~CMAKE_Target_List_Data_Structure_Constructor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Target_List_Data_Structure_Constructor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Target_List_Determiner.Clear_Dynamic_Memory();

         this->Target_List_Data_Processor.Clear_Dynamic_Memory();

         this->Meta_Data_Collector.Clear_Dynamic_Memory();
     }
}


void CMAKE_Target_List_Data_Structure_Constructor::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;

     this->Meta_Data_Collector.Receive_System_Interface(sysInt);

     this->Target_List_Determiner.Receive_System_Interface(sysInt);

     this->Target_List_Data_Processor.Receive_System_Interface(sysInt);
}


void CMAKE_Target_List_Data_Structure_Constructor::Construct_Target_List_Data_Structure()
{
     this->Meta_Data_Collector.Collect_Meta_Data();

     this->Compiler_Data_Pointer = this->Meta_Data_Collector.Get_Compiler_Data();

     this->Target_List_Determiner.Receive_Compiler_Dependency_Data(this->Compiler_Data_Pointer);

     this->Target_List_Determiner.Determine_Target_Lists();

     const std::vector<cmake::target_list_dtr> * LIST_DTR_PTR 
     
           = this->Target_List_Determiner.Get_CMAKE_Target_List();


     const Descriptor_File_Reader * Des_Reader = 
     
          this->Meta_Data_Collector.Get_Descriptor_File_Reader();

     this->Target_List_Data_Processor.Receive_Descriptor_File(Des_Reader);

     this->Target_List_Data_Processor.Receive_Target_List_Data(LIST_DTR_PTR);

     this->Target_List_Data_Processor.Receive_Compiler_Dependency_Data(this->Compiler_Data_Pointer);

     this->Target_List_Data_Processor.Process_Target_List_Data();
}









