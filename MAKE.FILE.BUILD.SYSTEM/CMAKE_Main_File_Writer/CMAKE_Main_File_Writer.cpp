




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


void CMAKE_Main_File_Writer::Build_Main_CMAKE_File(std::string project_name, std::string version_num){

     this->Memory_Delete_Condition = false;

     std::string warehouse_location = this->Des_Reader->Get_Repo_Directory_Location();


     std::string cmake_list_file_name = "CMakeLists.txt";

     std::string CMAKE_Main_File_Path = warehouse_location;
     
     if(this->opr_sis == 'w'){

        CMAKE_Main_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMAKE_Main_File_Path.push_back('/');
     }
     
     CMAKE_Main_File_Path = CMAKE_Main_File_Path + cmake_list_file_name;


     this->FileManager.SetFilePath(CMAKE_Main_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     const std::vector<std::string> & compiler_paths =  this->Des_Reader->Get_Compiler_Paths();

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_COMPILER \"");
     
     std::string cpp_compiler = compiler_paths[0];

     this->Convert_CMAKE_Format(cpp_compiler);

     this->FileManager.WriteToFile(cpp_compiler);
     
     this->FileManager.WriteToFile("\")");


     if(compiler_paths.size()>1){

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n set(CMAKE_C_COMPILER \"");
     
        std::string c_compiler = compiler_paths[1];

        this->Convert_CMAKE_Format(c_compiler);

        this->FileManager.WriteToFile(c_compiler);

        this->FileManager.WriteToFile("\")");
     }

  

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD 11)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n set(CMAKE_CXX_STANDARD_REQUIRED True)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n set(CMAKE_OBJECT_PATH_MAX 360)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n cmake_minimum_required(VERSION 3.10)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n project(");

     this->FileManager.WriteToFile(project_name);

     this->FileManager.WriteToFile(" VERSION ");

     this->FileManager.WriteToFile(version_num);

     this->FileManager.WriteToFile(")");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     const std::vector<std::string> & Inc_Dirs =  this->Des_Reader->Get_Include_Directories();

     if(Inc_Dirs.size()>0){

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n include_directories(");

        for(size_t i=0;i<Inc_Dirs.size();i++){

            this->FileManager.WriteToFile("\n\n   ");

            std::string inc_dir = Inc_Dirs.at(i);

            this->Convert_CMAKE_Format(inc_dir);

            this->FileManager.WriteToFile(inc_dir);         
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
         
         this->FileManager.WriteToFile("\n");

         for(size_t i=0;i<Lib_Dirs.size();i++){

             this->FileManager.WriteToFile("\n   ");

             std::string lib_dir = Lib_Dirs.at(i);

             this->Convert_CMAKE_Format(lib_dir);

             this->FileManager.WriteToFile(lib_dir);         
         }

         for(size_t i=0;i<Src_Dirs.size();i++){

             this->FileManager.WriteToFile("\n   ");

             std::string src_dir = Src_Dirs.at(i);

             this->Convert_CMAKE_Format(src_dir);

             this->FileManager.WriteToFile(src_dir);         
         }

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n )");
     }



     const std::vector<std::string> &  libs =  this->Des_Reader->Get_Library_Files();

     if(libs.size()>0){

        this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n link_libraries(");

        for(size_t i=0;i<libs.size();i++){

            this->FileManager.WriteToFile("\n    ");

            std::string link_lib = libs.at(i);

            this->Convert_CMAKE_Format(link_lib);

            this->FileManager.WriteToFile(link_lib);         
        }

         this->FileManager.WriteToFile("\n");

        this->FileManager.WriteToFile("\n )");
     }



     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n include(directories.cmake)");


     this->Compiler_Data_Pointer = this->Dep_Determiner->Get_Compiler_Data_Address();

     int target_counter = 0;

     std::string project_target_list;

     std::string space_string = " ";

     for(size_t i=0;i<this->Compiler_Data_Pointer->size();i++){

         std::string target_name = "$<TARGET_OBJECTS:" +
         
          this->Compiler_Data_Pointer->at(i).source_file_name_witout_ext + ">";

         project_target_list = project_target_list + space_string + target_name;   

         target_counter++;

         if(target_counter>1){

             project_target_list = project_target_list + "\n\t";

             target_counter = 0;
         }      
     }

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile(" add_library(");

     this->FileManager.WriteToFile(project_name);


     this->FileManager.WriteToFile("_lib ");


     this->FileManager.WriteToFile(project_target_list);

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.WriteToFile("\n\n");


     const std::vector<std::string> & Libs =  this->Des_Reader->Get_Library_Files();

     if(Libs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("link_libraries(");

        this->FileManager.WriteToFile("\n\n    ");

        int lib_counter = 0;

        for(size_t i=0;i<Libs.size();i++){

            this->FileManager.WriteToFile(Libs.at(i));

            this->FileManager.WriteToFile("  ");

            lib_counter++;

            if(lib_counter>3){

               this->FileManager.WriteToFile("\n\n    ");

               lib_counter = 0;
            }
        }

        this->FileManager.WriteToFile("\n )");
     }  

     this->FileManager.FileClose();
}



void CMAKE_Main_File_Writer::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->Dep_Determiner = dep_ptr;
}


void CMAKE_Main_File_Writer::Convert_CMAKE_Format(std::string & str){

     for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
     }
}
