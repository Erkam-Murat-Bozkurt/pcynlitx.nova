




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

#include "CMAKE_Main_File_Writer.hpp"

CMAKE_Main_File_Writer::CMAKE_Main_File_Writer()
{
   this->Memory_Delete_Condition = false;
}


CMAKE_Main_File_Writer::~CMAKE_Main_File_Writer(){

    this->Clear_Object_Memory();
}


void CMAKE_Main_File_Writer::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void CMAKE_Main_File_Writer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }
}


void CMAKE_Main_File_Writer::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;

}


void CMAKE_Main_File_Writer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}

 void CMAKE_Main_File_Writer::Receive_Git_Data_Processor(Git_Data_Processor * Git_Proc){

      this->Git_Processor = Git_Proc;
 }



void CMAKE_Main_File_Writer::Build_Main_CMAKE_File(){

     this->Memory_Delete_Condition = false;

     std::string warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     std::string warehouse_word = "WAREHOUSE";

     std::string cmake_list_file_name = "CMakeLists.txt";

     std::string CMAKE_File_Path = warehouse_location;

     if(this->opr_sis == 'w'){

        CMAKE_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMAKE_File_Path.push_back('/');
     }

     CMAKE_File_Path = CMAKE_File_Path + warehouse_word;
     
     if(this->opr_sis == 'w'){

        CMAKE_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMAKE_File_Path.push_back('/');
     }
     
     CMAKE_File_Path = CMAKE_File_Path + cmake_list_file_name;


     this->FileManager.SetFilePath(CMAKE_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");




     this->FileManager.WriteToFile("\n set( CMAKE_CXX_COMPILER \"D:/mingw64/bin/g++.exe\" )");

     this->FileManager.WriteToFile("\n set( CMAKE_C_COMPILER \"D:/mingw64/bin/gcc.exe\" )");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD 11)");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD_REQUIRED True)");

     this->FileManager.WriteToFile("\n cmake_minimum_required(VERSION 3.10)");




     this->FileManager.WriteToFile("\n");


     this->FileManager.FileClose();
}


void CMAKE_Main_File_Writer::Clear_String_Vector(std::vector<std::string> & str){

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




void CMAKE_Main_File_Writer::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}
