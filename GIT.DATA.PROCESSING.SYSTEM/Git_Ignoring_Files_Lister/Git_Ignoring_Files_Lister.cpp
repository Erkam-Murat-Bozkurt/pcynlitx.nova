
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




#include "Git_Ignoring_Files_Lister.hpp"


Git_Ignoring_Files_Lister::Git_Ignoring_Files_Lister(char opr_sis)
{
    this->opr_sis = opr_sis;

    this->Initialize_Mermbers();
}


Git_Ignoring_Files_Lister::~Git_Ignoring_Files_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_Ignoring_Files_Lister::Initialize_Mermbers(){

     this->Memory_Delete_Condition = false;
}


 void Git_Ignoring_Files_Lister::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

      this->Des_Reader = ptr;
 }


void Git_Ignoring_Files_Lister::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(&this->Warehouse);

         this->Clear_String_Memory(&this->Repo_Dir);

         this->Clear_String_Memory(&this->git_ignoring_files_list_path);

         this->FileManager.Clear_Dynamic_Memory();

         this->DirectoryManager.Clear_Dynamic_Memory();
     }
}


void Git_Ignoring_Files_Lister::Write_Ignoring_File_List()
{
     this->Memory_Delete_Condition = false;

     this->Warehouse = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir  = this->Des_Reader->Get_Repo_Directory_Location();


     this->Determine_Git_Ignoring_Files_List_Path();

     this->Set_Ignoring_File_Types();

     std::cout << "\nCONFIGURATIONS:";
     std::cout << "\nThe Files having \".make\" and \".ps1\" extention will be ignored by Git";
     std::cout << "\n\n";
}


void Git_Ignoring_Files_Lister::Determine_Git_Ignoring_Files_List_Path()
{
     std::string ignoring_files_list_location;

     if(this->opr_sis == 'w'){

        ignoring_files_list_location = ".git\\info\\exclude";
     }

     if(this->opr_sis == 'l'){

        ignoring_files_list_location = ".git/info/exclude";
     }

     size_t file_name_size = ignoring_files_list_location.length();

     size_t repo_path_size = this->Repo_Dir.length();


     for(size_t i=0;i<repo_path_size;i++){

         this->git_ignoring_files_list_path.push_back(this->Repo_Dir[i]) ;
     }

     if(this->Warehouse[repo_path_size-1] != '\\'){

        this->git_ignoring_files_list_path.push_back('\\') ;
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_ignoring_files_list_path.push_back(ignoring_files_list_location[i]) ;
     }
}


void Git_Ignoring_Files_Lister::Set_Ignoring_File_Types(){

     this->FileManager.SetFilePath(this->git_ignoring_files_list_path);

     this->FileManager.FileOpen(Af);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("*.make");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("*.ps1");

     this->FileManager.FileClose();
}

void Git_Ignoring_Files_Lister::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}