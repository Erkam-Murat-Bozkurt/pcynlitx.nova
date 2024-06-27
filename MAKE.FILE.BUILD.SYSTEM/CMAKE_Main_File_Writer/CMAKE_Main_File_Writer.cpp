




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


void CMAKE_Main_File_Writer::Receive_CMAKE_Lists_Construction_Directories(const std::vector<std::string> * dirs){

    this->Const_Dirs = dirs;
}


void CMAKE_Main_File_Writer::Build_Main_CMAKE_File(){

     this->CMAKE_SubDirectory_Determination();

     this->Memory_Delete_Condition = false;

     std::string warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     std::string warehouse_word = "WAREHOUSE";

     std::string warehouse_path = warehouse_location;

     
     if(this->opr_sis == 'w'){

        warehouse_path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        warehouse_path.push_back('/');
     }

     warehouse_path = warehouse_path + warehouse_word;


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


     std::string project_name = "default_proj";

     std::string version_num = "1.0";

     this->FileManager.WriteToFile("\n set( CMAKE_CXX_COMPILER \"D:/mingw64/bin/g++.exe\" )");

     this->FileManager.WriteToFile("\n set( CMAKE_C_COMPILER \"D:/mingw64/bin/gcc.exe\" )");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD 11)");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD_REQUIRED True)");

     this->FileManager.WriteToFile("\n cmake_minimum_required(VERSION 3.10)");



     this->FileManager.WriteToFile("\n project(");

     this->FileManager.WriteToFile(project_name);

     this->FileManager.WriteToFile(" VERSION ");

     this->FileManager.WriteToFile(version_num);

     this->FileManager.WriteToFile(")");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");




     if(this->Const_Dirs->size()>0){

        for(size_t i=0;i<this->Const_Dirs->size();i++){

               //std::string sub_dir_path = warehouse_path;

               //sub_dir_path.push_back('/');

               std::string sub_dir_path =  this->Const_Dirs->at(i);

               //std::cout << "\n this->sub_dirs.at(" << i << "):" << this->sub_dirs.at(i);

               //std::cin.get();


               //std::cout << "\n sub_dir_path:" << sub_dir_path;


               for(size_t i=0;i<sub_dir_path.size();i++){

                   if(sub_dir_path[i] == '\\'){

                      sub_dir_path[i] = '/';
                   }
               }

               this->FileManager.WriteToFile("\n\n    ");

               this->FileManager.WriteToFile("\n add_subdirectory(");

               //((this->FileManager.WriteToFile("\n\n    ");

               //std::cout << "\n this->sub_dirs.at(" << i <<")"  << this->sub_dirs.at(i);

               //std::cin.get();

               this->FileManager.WriteToFile(sub_dir_path);

                //this->FileManager.WriteToFile("\n\n");

               this->FileManager.WriteToFile(" )");
        }
     }


     const std::vector<std::string> & Inc_Dirs =  this->Des_Reader->Get_Include_Directories();

     if(Inc_Dirs.size()>0){

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n include_directories(");

        for(size_t i=0;i<Inc_Dirs.size();i++){

            this->FileManager.WriteToFile("\n\n   ");

            this->FileManager.WriteToFile(Inc_Dirs.at(i));         
        }

        this->FileManager.WriteToFile("\n\n");

        this->FileManager.WriteToFile(" )");
     }

     const std::vector<std::string> & Lib_Dirs =  this->Des_Reader->Get_Library_Directories();

     const std::vector<std::string> & Src_Dirs =  this->Des_Reader->Get_Source_File_Directories();


     if((Lib_Dirs.size()>0) || (Src_Dirs.size()>0) ){
          
         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n link_directories(");
         

         for(size_t i=0;i<Lib_Dirs.size();i++){

             this->FileManager.WriteToFile("\n ");

             this->FileManager.WriteToFile(Lib_Dirs.at(i));         
         }

         for(size_t i=0;i<Src_Dirs.size();i++){

             this->FileManager.WriteToFile("\n ");

             this->FileManager.WriteToFile(Src_Dirs.at(i));         
         }

         this->FileManager.WriteToFile("\n )");
     }



     const std::vector<std::string> &  libs =  this->Des_Reader->Get_Library_Files();

     if(libs.size()>0){

        this->FileManager.WriteToFile("\n link_libraries(");

        for(size_t i=0;i<libs.size();i++){

            this->FileManager.WriteToFile("\n ");

            this->FileManager.WriteToFile(libs.at(i));         
        }

        this->FileManager.WriteToFile("\n )");
     }



     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();


}



void CMAKE_Main_File_Writer::CMAKE_SubDirectory_Determination(){

     std::vector<std::string> * Git_Sub_Dirs = this->Git_Processor->Get_Directory_Tree();

     std::vector<std::string> * file_paths = this->Git_Processor->Get_File_System_Path_Address();

     Header_File_Determiner HDR_Determiner(this->opr_sis);

     Source_File_Determiner SRC_Determiner;

     StringOperator StrOpr;

     for(size_t i=0;i<Git_Sub_Dirs->size();i++){

         std::string dir_path = Git_Sub_Dirs->at(i);

         for(size_t j=0;j<file_paths->size();j++){

             bool inc = StrOpr.CheckStringInclusion(file_paths->at(j),dir_path);

             if(inc){
            
                bool is_src_file = SRC_Determiner.Is_Source_File(file_paths->at(j));

                bool is_hdr_file = HDR_Determiner.Is_Header(file_paths->at(j));

                if(is_src_file || is_hdr_file){

                   this->sub_dirs.push_back(dir_path);

                   break;
                }
             }
         }
     }
}



std::vector<Git_Sub_Directory_Data> * CMAKE_Main_File_Writer::Get_CMAKE_Root_Dirs()
{
     return this->Git_Processor->Get_Git_Root_Dirs();
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
