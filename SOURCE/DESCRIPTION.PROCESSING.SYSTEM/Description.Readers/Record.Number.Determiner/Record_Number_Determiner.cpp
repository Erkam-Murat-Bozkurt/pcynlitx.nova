
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



#include "Record_Number_Determiner.hpp"

Record_Number_Determiner::Record_Number_Determiner()
{
   
   this->opr_sis = opr_sis;

   this->Memory_Delete_Condition = false; 

   this->Root_Directory_Location_Record_Number = 0;

   this->Warehouse_Location_Record_Number = 0;
 
   this->Standard_Record_Number = 0;
 
   this->Include_Directories_Record_Number = 0;
 
   this->Source_File_Directories_Record_Number = 0;
 
   this->Library_Directories_Record_Number = 0;
 
   this->Compiler_Options_Record_Number = 0;
 
   this->Linker_Options_Record_Number = 0;
 
   this->Build_System_Type_Record_Number = 0;
 
   this->Project_Name_Record_Number = 0;
 
   this->Version_Number_Record_Number = 0;
 
   this->Compiler_Paths_Record_Number = 0;
}



Record_Number_Determiner::~Record_Number_Determiner(){

    if(!this->Memory_Delete_Condition){

        this->Reset_Record_Numbers();
    }
}


void Record_Number_Determiner::Reset_Record_Numbers(){

     this->Root_Directory_Location_Record_Number = 0;

     this->Warehouse_Location_Record_Number = 0;
 
     this->Standard_Record_Number = 0;
 
     this->Include_Directories_Record_Number = 0;
 
     this->Source_File_Directories_Record_Number = 0;
 
     this->Library_Directories_Record_Number = 0;
 
     this->Compiler_Options_Record_Number = 0;
 
     this->Linker_Options_Record_Number = 0;
 
     this->Build_System_Type_Record_Number = 0;
 
     this->Project_Name_Record_Number = 0;
 
     this->Version_Number_Record_Number = 0;
  
     this->Compiler_Paths_Record_Number = 0;
}

void Record_Number_Determiner::Receive_Descriptor_File_Data_Collector(Descriptor_File_Data_Collector * ptr){

     this->Data_Collector = ptr;
}


void Record_Number_Determiner::Determine_Record_Numbers(){

     this->Reset_Record_Numbers();

     this->Determine_Root_Directory_Location_Record_Number();

     this->Determine_Warehouse_Location_Record_Number();

     this->Determine_Standard_Record_Number();

     this->Determine_Version_Number_Record_Number();
     
     this->Determine_Include_Directories_Record_Number();

     this->Determine_Source_File_Directories_Record_Number();

     this->Determine_Library_Directories_Record_Number();

     this->Determine_Library_Files_Record_Number();

     this->Determine_Compiler_Options_Record_Number();

     this->Determine_Linker_Options_Record_Number();

     this->Determine_Build_System_Type_Record_Number();

     this->Determine_Project_Name_Record_Number();

     this->Determine_Compiler_Paths_Record_Number();
}



void Record_Number_Determiner::Determine_Root_Directory_Location_Record_Number(){
   
     int start_line = this->Data_Collector->Get_Root_Directory_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Root_Directory_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Root_Directory_Location_Record_Number++;
         }
     }
}



void Record_Number_Determiner::Determine_Warehouse_Location_Record_Number(){

     int start_line = this->Data_Collector->Get_Warehouse_Location_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Warehouse_Location_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Warehouse_Location_Record_Number++;
         }
     }
}


void Record_Number_Determiner::Determine_Standard_Record_Number(){

     int start_line = this->Data_Collector->Get_Standard_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Standard_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);
    
         if(this->StringManager.CheckStringLine(line)){

            this->Standard_Record_Number++;
         }
    }
}

void Record_Number_Determiner::Determine_Include_Directories_Record_Number(){
    
     int start_line = this->Data_Collector->Get_Include_Directories_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Include_Directories_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);         

         if(this->StringManager.CheckStringLine(line)){

            this->Include_Directories_Record_Number++;
         }
    }
}



void Record_Number_Determiner::Determine_Source_File_Directories_Record_Number(){

     int start_line = this->Data_Collector->Get_Source_File_Directories_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Source_File_Directories_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->Source_File_Directories_Record_Number++;
            }
         }
     }
}

void Record_Number_Determiner::Determine_Library_Directories_Record_Number(){

     int start_line = this->Data_Collector->Get_Library_Directories_Record_Area(0);

     int end_line  = this->Data_Collector->Get_Library_Directories_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->Library_Directories_Record_Number++;
            }
         }
     }
}


void Record_Number_Determiner::Determine_Library_Files_Record_Number(){

     int start_line = this->Data_Collector->Get_Library_Files_Record_Area(0);

     int end_line  = this->Data_Collector->Get_Library_Files_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

             if(this->Is_Include_Character(line)){

                this->Library_Files_Record_Number++;
             }
         }
     }
}



void Record_Number_Determiner::Determine_Compiler_Options_Record_Number(){

     int start_line = this->Data_Collector->Get_Compiler_Options_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Compiler_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->Compiler_Options_Record_Number++;
            }
         }
     }
}


void Record_Number_Determiner::Determine_Linker_Options_Record_Number(){
    
     int start_line = this->Data_Collector->Get_Linker_Options_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Linker_Options_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Linker_Options_Record_Number++;
         }
    }
}

void Record_Number_Determiner::Determine_Build_System_Type_Record_Number(){

     int start_line = this->Data_Collector->Get_Build_System_Type_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Build_System_Type_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Build_System_Type_Record_Number++;
         }
     }
}

void Record_Number_Determiner::Determine_Project_Name_Record_Number(){

     int start_line = this->Data_Collector->Get_Project_Name_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Project_Name_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);
         
         if(this->StringManager.CheckStringLine(line)){

            this->Project_Name_Record_Number++;
         }
     }
}

void Record_Number_Determiner::Determine_Version_Number_Record_Number(){

     int start_line = this->Data_Collector->Get_Version_Number_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Version_Number_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Version_Number_Record_Number++;
         }
     }
}

void Record_Number_Determiner::Determine_Compiler_Paths_Record_Number(){

     int start_line = this->Data_Collector->Get_Compiler_Paths_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Compiler_Paths_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->Compiler_Paths_Record_Number++;
            }
         }
     }
}

bool Record_Number_Determiner::Is_Include_Character(std::string str){

     bool is_include = false;

     for(size_t i=0;i<str.length();i++){

         if((str.at(i) != ' ') && (str.at(i) != '\n')){

              is_include = true;

              return is_include;
         }
     }

     return is_include;
}


 int Record_Number_Determiner::Get_Root_Directory_Location_Record_Number(){

     return this->Root_Directory_Location_Record_Number;
 }

 int Record_Number_Determiner::Get_Warehouse_Location_Record_Number(){

     return this->Warehouse_Location_Record_Number;
 }

 int Record_Number_Determiner::Get_Standard_Record_Number(){

     return this->Standard_Record_Number;
 }

 int Record_Number_Determiner::Get_Include_Directories_Record_Number(){

     return this->Include_Directories_Record_Number;
 }

 int Record_Number_Determiner::Get_Source_File_Directories_Record_Number(){

     return this->Source_File_Directories_Record_Number;
 }


 int Record_Number_Determiner::Get_Library_Directories_Record_Number(){

     return this->Library_Directories_Record_Number;
 }

 int Record_Number_Determiner::Get_Library_Files_Record_Number(){

     return this->Library_Directories_Record_Number;
 }

 int Record_Number_Determiner::Get_Compiler_Options_Record_Number(){

     return this->Compiler_Options_Record_Number;
 }

 int Record_Number_Determiner::Get_Linker_Options_Record_Number(){

     return this->Linker_Options_Record_Number;
 }

 int Record_Number_Determiner::Record_Number_Determiner::Get_Build_System_Type_Record_Number(){

     return this->Build_System_Type_Record_Number;
 }

 int Record_Number_Determiner::Record_Number_Determiner::Get_Project_Name_Record_Number(){

     return this->Project_Name_Record_Number;
 }

 int Record_Number_Determiner::Get_Version_Number_Record_Number(){

     return this->Version_Number_Record_Number;
 }

 int Record_Number_Determiner::Get_Compiler_Paths_Record_Number(){

     return this->Compiler_Paths_Record_Number;
 }