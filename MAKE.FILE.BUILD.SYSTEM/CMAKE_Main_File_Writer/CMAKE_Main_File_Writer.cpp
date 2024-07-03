




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

     std::string warehouse_location = this->Des_Reader->Get_Repo_Directory_Location();

     /*

     std::string warehouse_word = "WAREHOUSE";

     std::string warehouse_path = warehouse_location;

     
     if(this->opr_sis == 'w'){

        warehouse_path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        warehouse_path.push_back('/');
     }

     warehouse_path = warehouse_path + warehouse_word;

     */


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


     std::string project_name = "default_proj";

     std::string version_num = "1.0";

     this->FileManager.WriteToFile("\n set( CMAKE_CXX_COMPILER \"D:/mingw64/bin/g++.exe\" )");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n set( CMAKE_C_COMPILER \"D:/mingw64/bin/gcc.exe\" )");

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


     /*

     CharOperator Cr_Opr;

     char dir_char;

     if(this->opr_sis == 'w'){

        dir_char = '\\';
     }

     if(this->opr_sis == 'l'){

        dir_char = '/';
     }


     int first_order_sub_dir_num = 0;

     if(this->cmake_sub_dirs_list.size()>0){

        for(size_t i=0;i<this->cmake_sub_dirs_list.size();i++){

            Git_Sub_Directory_Data Dir_Data =  this->cmake_sub_dirs_list.at(i);

            int dir_char_rep = Cr_Opr.DetermineCharacterRepitation(Dir_Data.dir_path,dir_char);

            if(dir_char_rep == 0){

                if(Dir_Data.cmake_dir_status){

                    first_order_sub_dir_num++;
                }
            }
        }
     }

     if(first_order_sub_dir_num>0){

        for(size_t i=0;i<this->cmake_sub_dirs_list.size();i++){

            Git_Sub_Directory_Data Dir_Data =  this->cmake_sub_dirs_list.at(i);

            std::string sub_dir_path = Dir_Data.dir_path;


            for(size_t i=0;i<Dir_Data.dir_path.size();i++){

                if(sub_dir_path[i] == '\\'){

                   sub_dir_path[i] = '/';
                }
            }

            int dir_char_rep = Cr_Opr.DetermineCharacterRepitation(Dir_Data.dir_path,dir_char);

            if(dir_char_rep == 0){

                if(Dir_Data.cmake_dir_status){

                   this->FileManager.WriteToFile("\n\n    ");

                   this->FileManager.WriteToFile("\n add_subdirectory(");

                   this->FileManager.WriteToFile(sub_dir_path);

                   this->FileManager.WriteToFile(")");
                }
            }
        }
     }


     */

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

     this->FileManager.WriteToFile("add_library(default_proj_lib ");

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

            this->FileManager.WriteToFile(" ");

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



void CMAKE_Main_File_Writer::CMAKE_SubDirectory_Determination(){

     const std::vector<Git_Sub_Directory_Data> * Git_Sub_Dirs = this->Git_Processor->Get_Directory_Tree_Data();

     std::vector<std::string> * file_paths = this->Git_Processor->Get_File_System_Path_Address();

     Header_File_Determiner HDR_Determiner(this->opr_sis);

     Source_File_Determiner SRC_Determiner;

     StringOperator StrOpr;

     for(size_t i=0;i<Git_Sub_Dirs->size();i++){

         Git_Sub_Directory_Data Dir_Data = Git_Sub_Dirs->at(i);

         for(size_t j=0;j<file_paths->size();j++){
           
             bool inc = StrOpr.CheckStringInclusion(file_paths->at(j),Dir_Data.dir_path);

             if(inc){
            
                bool is_src_file = SRC_Determiner.Is_Source_File(file_paths->at(j));

                bool is_hdr_file = HDR_Determiner.Is_Header(file_paths->at(j));

                if(is_src_file || is_hdr_file){

                   Dir_Data.cmake_dir_status = true;

                   std::string file_dir;

                   this->Find_File_Directory(file_dir,file_paths->at(j));

                   if(Dir_Data.dir_path == file_dir){

                      Dir_Data.source_file_inc_status = true;
                   }
                
                   this->cmake_sub_dirs_list.push_back(Dir_Data);

                   break;
                }
             }
         }
     }

     this->cmake_sub_dirs_list.shrink_to_fit();
}



void CMAKE_Main_File_Writer::Find_File_Directory(std::string & file_dir, std::string file_path){

     std::string repo_dir = this->Des_Reader->Get_Repo_Directory_Location();

     size_t path_size = file_path.size();

     size_t end_point = path_size;

     size_t start_point = repo_dir.size() + 1;

     for(size_t i=path_size;i>0;i--){

         if((file_path[i]=='/') || (file_path[i]=='\\')){

            end_point = i;

            break;
         }
     }

     for(size_t i=start_point;i<end_point;i++){

         file_dir.push_back(file_path[i]);
     }

     file_dir.shrink_to_fit();
}


const std::vector<Git_Sub_Directory_Data> * CMAKE_Main_File_Writer::Get_CMAKE_SubDir_List(){

     return &this->cmake_sub_dirs_list;
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
