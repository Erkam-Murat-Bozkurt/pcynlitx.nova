


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

#include "CMake_List_Builder.hpp"

CMake_List_Builder::CMake_List_Builder()
{
   this->Memory_Delete_Condition = false;
}


CMake_List_Builder::~CMake_List_Builder(){

    this->Clear_Object_Memory();
}


void CMake_List_Builder::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void CMake_List_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }
}


void CMake_List_Builder::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;

     this->Path_Determiner.Receive_Operating_System(opr_sis);
}


void CMake_List_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Path_Determiner.Receive_Descriptor_File_Reader(ptr);
}

void CMake_List_Builder::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr)
{
     this->Comp_Data_Ptr = ptr;

     this->Path_Determiner.Receive_Compiler_Data_Pointer(ptr);
}


void CMake_List_Builder::Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr){

     this->DataMap_Pointer = ptr;

     this->Path_Determiner.Receive_DataMap(ptr);
}


Compiler_Data * CMake_List_Builder::Find_Compiler_Data_From_Source_File_Path(std::string path)
{
    try {        

         return  &this->DataMap_Pointer->at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n the file located on path " << path << " can not find on Make_File_Builder object!.\n";

         exit(EXIT_FAILURE);
    }     
}


void CMake_List_Builder::Build_MakeFile(std::string file_path){

     this->Memory_Delete_Condition = false;

     this->Path_Determiner.Set_CMAKE_Construction_Status(true);

     this->Path_Determiner.Determine_MakeFile_Data(file_path);

     this->Data_Ptr = this->Find_Compiler_Data_From_Source_File_Path(file_path);

     
     std::string Make_File_Path = this->Path_Determiner.Get_MakeFile_Path();


     this->FileManager.SetFilePath(Make_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("add_library(");

     this->FileManager.WriteToFile(this->Data_Ptr->source_file_name_witout_ext);          

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("  ");

     this->FileManager.WriteToFile(this->Data_Ptr->source_file_path);          



     
     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ");


         this->FileManager.WriteToFile(this->Data_Ptr->dependent_headers_dir.at(i));      

         if(this->opr_sis == 'w'){

             this->FileManager.WriteToFile("\\");
         }
         
         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }

         this->FileManager.WriteToFile(this->Data_Ptr->dependent_headers.at(i));      

     }


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.FileClose();
}


void CMake_List_Builder::Clear_String_Vector(std::vector<std::string> & str){

     str.shrink_to_fit();

     for(size_t i=0;i<str.size();i++){

         this->Clear_String_Memory(str.at(i));
     }

     if(!str.empty())
     {
         str.clear();
         str.shrink_to_fit();
     }
 }




void CMake_List_Builder::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}
