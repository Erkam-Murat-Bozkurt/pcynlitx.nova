


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

         std::cout << "\n the file located on path " 
         
         << path << " can not find on Make_File_Builder object!.\n";

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

     std::string src_file_path = this->Data_Ptr->source_file_path;

     this->Convert_CMAKE_Format(src_file_path);

     this->FileManager.WriteToFile(src_file_path);          



     
     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ");

         std::string dep_header_dir = this->Data_Ptr->dependent_headers_dir.at(i);
      
         this->Convert_CMAKE_Format(dep_header_dir);

         this->FileManager.WriteToFile(dep_header_dir);      

         this->FileManager.WriteToFile("/");

         std::string dep_header_name = this->Data_Ptr->dependent_headers.at(i);

         this->Convert_CMAKE_Format(dep_header_name);

         this->FileManager.WriteToFile(dep_header_name);      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");
     
     /*

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     
     this->FileManager.WriteToFile("target_include_directories(");
     
     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ");

         std::string dep_header_dir = this->Data_Ptr->dependent_headers_dir.at(i);
      
         this->Convert_CMAKE_Format(dep_header_dir);

         this->FileManager.WriteToFile(dep_header_dir);      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

       
     */

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     
     this->FileManager.WriteToFile("include_directories(");
     
     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ");

         std::string dep_header_dir = this->Data_Ptr->dependent_headers_dir.at(i);
      
         this->Convert_CMAKE_Format(dep_header_dir);

         this->FileManager.WriteToFile(dep_header_dir);      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.FileClose();
}

void CMake_List_Builder::Find_Construction_Directory(std::string & dir, std::string file_path){

     size_t dir_size = file_path.size();

     size_t end_point = dir_size;

     for(size_t i=dir_size;i>0;i--){

         if((file_path[i]=='/') || (file_path[i]=='\\')){

            end_point = i;

            break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         dir.push_back(file_path[i]);
     }

     dir.shrink_to_fit();
}

std::string CMake_List_Builder::Get_Construction_Dir(){

     std::string Make_File_Path = this->Path_Determiner.Get_MakeFile_Path();

     std::string dir;

     this->Find_Construction_Directory(dir,Make_File_Path);

     return dir;
}


void CMake_List_Builder::Convert_CMAKE_Format(std::string & str){

     for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
     }
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
