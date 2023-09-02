

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

#include "Git_Data_Processor.hpp"



Git_Data_Processor::Git_Data_Processor(char opr_sis) :

    Modf_Receiver(opr_sis), Modf_Lister(opr_sis), List_Writer(opr_sis), 
    List_Receiver(opr_sis), Ing_Lister(opr_sis),  Des_Reader(opr_sis),
    FileManager(opr_sis) 
{
    this->opr_sis = opr_sis;

    this->Memory_Delete_Condition = false;

}


Git_Data_Processor::~Git_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_Data_Processor::Receive_Descriptor_File_Path(char * DesPath){

     this->Des_Reader.Receive_Descriptor_File_Path(DesPath);

     this->Des_Reader.Read_Descriptor_File();

     this->List_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->List_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Ing_Lister.Receive_Descriptor_File_Reader(&this->Des_Reader);
}

void Git_Data_Processor::Receive_Descriptor_File_Path(std::string DesPath){

     this->Des_Reader.Receive_Descriptor_File_Path(DesPath);

     this->Des_Reader.Read_Descriptor_File();

     this->List_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->List_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Ing_Lister.Receive_Descriptor_File_Reader(&this->Des_Reader);
}


void Git_Data_Processor::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->List_Receiver.Clear_Dynamic_Memory();

         this->List_Writer.Clear_Dynamic_Memory();

         this->Modf_Lister.Clear_Dynamic_Memory();

         this->Modf_Receiver.Clear_Dynamic_Memory();

         this->Ing_Lister.Clear_Dynamic_Memory();

         this->Des_Reader.Clear_Dynamic_Memory();
     }
}


void Git_Data_Processor::Write_Git_Repo_List_File()
{     
     this->List_Writer.Write_Git_Repo_List_File();
}


void Git_Data_Processor::Determine_Git_Repo_Info(){

     this->List_Receiver.Determine_Git_Repo_Info();     
}


void Git_Data_Processor::Write_Git_Modification_File(){
     
     this->Modf_Lister.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Modf_Lister.Write_Git_Modification_File();
}


void Git_Data_Processor::Receive_Git_Modifications(){

     this->Modf_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Modf_Receiver.Receive_Git_List_Receiver(&this->List_Receiver);

     this->Modf_Receiver.Receive_Git_Modifications();
}


void Git_Data_Processor::Set_Git_Ignoring_Files(){

     this->Ing_Lister.Write_Ignoring_File_List();
}


std::string Git_Data_Processor::Get_File_System_Path(int num){

     return this->List_Receiver.Get_File_System_Path(num);
}

std::string Git_Data_Processor::Get_Git_File_Index(int num)
{
      return this->List_Receiver.Get_Git_File_Index(num);
}


std::string Git_Data_Processor::Get_Git_Repo_Directory(){

       return this->List_Receiver.Get_Git_Repo_Directory();
}


size_t Git_Data_Processor::Get_Git_File_Index_Size(){

    return this->List_Receiver.Get_Git_File_Index_Size();
}


std::string Git_Data_Processor::Get_Git_Record_Directory(int num){
 
      return this->List_Receiver.Get_Git_Record_Directory(num);
}


std::string Git_Data_Processor::Get_Git_Record_Path(int num){
 
      return this->List_Receiver.Get_Git_Record_Path(num);
}

std::string Git_Data_Processor::Get_File_Name(int num){
 
      return this->List_Receiver.Get_File_Name(num);    
}

std::vector<std::string> * Git_Data_Processor::Get_Git_File_Index_Address(){
 
     return this->List_Receiver.Get_Git_File_Index_Address();
}
  
std::vector<std::string> * Git_Data_Processor::Get_File_System_Path_Address(){
 
     return this->List_Receiver.Get_File_System_Path_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_Git_Record_Directory_Address(){
 
     return this->List_Receiver.Get_Git_Record_Directory_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_Git_Record_Path_Address(){
 
      return this->List_Receiver.Get_Git_Record_Path_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_File_Name_Address(){
 
      return this->List_Receiver.Get_File_Name_Address();    
}


std::vector<std::string> * Git_Data_Processor::Get_Updated_Header_Files()  
{
     return this->Modf_Receiver.Get_Updated_Header_Files();
    
}

std::vector<std::string> * Git_Data_Processor::Get_Updated_Source_Files()  
{
     return  this->Modf_Receiver.Get_Updated_Source_Files();
}