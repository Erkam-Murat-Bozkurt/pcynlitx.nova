
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



#include "CMAKE_Target_Library_Builder.hpp"

CMAKE_Target_Library_Builder::CMAKE_Target_Library_Builder()
{
   this->Memory_Delete_Condition = false;
}


CMAKE_Target_Library_Builder::~CMAKE_Target_Library_Builder(){

    this->Clear_Object_Memory();
}


void CMAKE_Target_Library_Builder::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void CMAKE_Target_Library_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->StrOpr.Clear_Dynamic_Memory();

         this->target_dependency_data_ptr = nullptr;
     }
}


void CMAKE_Target_Library_Builder::Build_MakeFile(int index){

     this->Memory_Delete_Condition = false;

     const cmake::target_data target_data = this->target_dependency_data_ptr->at(index);


     std::string file_dir = target_data.target_sys_dir;


     std::string CMake_File_Path = file_dir;

     if(this->opr_sis == 'w'){

        CMake_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMake_File_Path.push_back('/');
     }

     std::string file_name =  target_data.target_name  + ".cmake";

     CMake_File_Path = CMake_File_Path +  file_name;


     this->FileManager.SetFilePath(CMake_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("add_library(");

     this->FileManager.WriteToFile(target_data.target_name);          

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(" ");

     std::string target_git_dir = target_data.target_git_record_dir;

     std::string target_name = target_data.target_name_with_file_extention;

     std::string src_file_path = "${CMAKE_SOURCE_DIR}/" + target_git_dir + "/" + target_name;


     this->Convert_CMAKE_Format(src_file_path);


     this->FileManager.WriteToFile(src_file_path);          
    
     if(!target_data.dep_dt.empty()){

        for(size_t k=0;k<target_data.dep_dt.size();k++){

            std::string dependent_file_name   = target_data.dep_dt.at(k).dep_file_name_with_file_extention;

            std::string dependent_file_git_dr = target_data.dep_dt.at(k).dep_file_git_record_dir;

            std::string dependent_file_git_src_path = "${CMAKE_SOURCE_DIR}/" + dependent_file_git_dr + 
         
                        "/" + dependent_file_name;
         
            this->Convert_CMAKE_Format(dependent_file_git_src_path);

            this->FileManager.WriteToFile("\n ");

            this->FileManager.WriteToFile(dependent_file_git_src_path);
        }
    }
    
    this->FileManager.WriteToFile("\n");

    this->FileManager.WriteToFile(")");

    this->FileManager.WriteToFile("\n");

    this->FileManager.WriteToFile("\n");

     
    this->FileManager.WriteToFile("target_include_directories(");

    this->FileManager.WriteToFile(target_data.target_name);          

    this->FileManager.WriteToFile(" PUBLIC ");

    this->FileManager.WriteToFile("\n");

    for(size_t i=0;i<target_data.dependent_header_dirs.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ${CMAKE_SOURCE_DIR}/");

         this->FileManager.WriteToFile(target_data.dependent_header_dirs.at(i));      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");


     const std::vector<std::string> & Lib_Dirs =  this->Des_Reader->Get_Library_Directories();

     if(Lib_Dirs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("target_link_directories(");

        this->FileManager.WriteToFile(target_data.target_name);          

        this->FileManager.WriteToFile(" PUBLIC ");

        this->FileManager.WriteToFile("\n");

        std::vector<std::string> library_directories;

        for(size_t i=0;i<Lib_Dirs.size();i++){

            std::string lib_dir = Lib_Dirs.at(i);

            this->Convert_CMAKE_Format(lib_dir);

            if(!this->Check_String_Existance(library_directories,lib_dir)){

               library_directories.push_back(lib_dir);
            }
        }

        library_directories.shrink_to_fit();


        for(size_t i=0;i<Lib_Dirs.size();i++){

            this->FileManager.WriteToFile("\n\t");

            this->FileManager.WriteToFile(library_directories.at(i));
        }

        this->FileManager.WriteToFile("\n\n )");

        this->Clear_String_Vector(library_directories);
     }



     const std::vector<std::string> & Libs =  this->Des_Reader->Get_Library_Files();

     if(Libs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("target_link_libraries(");

        this->FileManager.WriteToFile(target_data.target_name);          

        this->FileManager.WriteToFile(" PUBLIC ");

        this->FileManager.WriteToFile("\n\n\t");

        int lib_counter = 0;

        for(size_t i=0;i<Libs.size();i++){

            std::string libs = Libs.at(i);

            this->Convert_CMAKE_Format(libs);

            this->FileManager.WriteToFile(libs);

            this->FileManager.WriteToFile("\n\t");
        }

        this->FileManager.WriteToFile("\n )");
     }  

     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_compile_options(");

     this->FileManager.WriteToFile(target_data.target_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     for(size_t i=0;i<compiler_options.size();i++){

         this->FileManager.WriteToFile("\n\n    ");

         this->FileManager.WriteToFile(compiler_options.at(i));         
     }

     this->FileManager.WriteToFile("\n\n    ");

     this->FileManager.WriteToFile(")");

     this->FileManager.WriteToFile("\n\n ");


     this->FileManager.WriteToFile("target_link_options(");

     this->FileManager.WriteToFile(target_data.target_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     const std::vector<std::string> & link_ops = this->Des_Reader->Get_Linker_Options();

     for(size_t i=0;i<link_ops.size();i++){

         this->FileManager.WriteToFile("\n\n    ");

         this->FileManager.WriteToFile(link_ops.at(i));         
     }

     this->FileManager.WriteToFile("\n\n    ");

     this->FileManager.WriteToFile(")");

     this->FileManager.FileClose();
}

void CMAKE_Target_Library_Builder::CMAKE_Sub_Directory_File_Path_Determination(std::string & path){

     std::string warehouse_location = this->Des_Reader->Get_Repo_Directory_Location();

     std::string directory_list_file_name = "directories.cmake";

     path = warehouse_location;
     
     if(this->opr_sis == 'w'){

        path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        path.push_back('/');
     }
     
     path = path + directory_list_file_name;
}


void CMAKE_Target_Library_Builder::Add_Target_Path_To_Directory_List(int target_index){ // Mutual exclusion is required
       
     const cmake::target_data target_data = this->target_dependency_data_ptr->at(target_index);

     std::string directory_list_file_path, cmake_sub_dir;

     cmake_sub_dir =  "${CMAKE_SOURCE_DIR}/" + target_data.target_git_record_dir;

     this->Convert_CMAKE_Format(cmake_sub_dir);

     this->CMAKE_Sub_Directory_File_Path_Determination(directory_list_file_path);

     std::string sub_directory_command = "add_subdirectory(" + cmake_sub_dir + ")";


     if(!this->FileManager.Is_Path_Exist(directory_list_file_path)){
        
         this->FileManager.SetFilePath(directory_list_file_path);

         this->FileManager.FileOpen(Af);  
 
         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile(sub_directory_command);

         this->FileManager.FileClose();
     }
     else{


          this->StrOpr.SetFilePath(directory_list_file_path);

          bool _exist_status = this->StrOpr.Is_String_Exist_On_File(sub_directory_command);

          this->StrOpr.Clear_Dynamic_Memory();

          if(!_exist_status){

             this->FileManager.SetFilePath(directory_list_file_path);

             this->FileManager.FileOpen(Af);  
 
             this->FileManager.WriteToFile("\n\n");

             this->FileManager.WriteToFile(sub_directory_command);

             this->FileManager.FileClose();
          }
     }
}

 
void CMAKE_Target_Library_Builder::Construct_SubDirectory_List_File(int index){

     const cmake::target_data target_data = this->target_dependency_data_ptr->at(index);

     std::string file_name = target_data.target_name  + ".cmake";

     std::string file_dir = target_data.target_sys_dir;

     std::string include_command = "include(" + file_name + ")";

     std::string CMAKE_List_File_Path = file_dir;
     
     if(this->opr_sis == 'w'){

          CMAKE_List_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMAKE_List_File_Path.push_back('/');
     }
     
     CMAKE_List_File_Path = CMAKE_List_File_Path + "CMakeLists.txt";

     if(this->FileManager.Is_Path_Exist(CMAKE_List_File_Path)){
          
        this->StrOpr.SetFilePath(CMAKE_List_File_Path);

        bool inc_word_exist_status = this->StrOpr.Is_String_Exist_On_File(include_command);;

        this->StrOpr.Clear_Dynamic_Memory();

        if(!inc_word_exist_status){

           this->FileManager.SetFilePath(CMAKE_List_File_Path);

           this->FileManager.FileOpen(Af);     

           this->FileManager.WriteToFile("\n");

           this->FileManager.WriteToFile(include_command);

           this->FileManager.WriteToFile("\n");

           this->FileManager.FileClose();      
        }    
     }
     else{

           this->FileManager.SetFilePath(CMAKE_List_File_Path);

           this->FileManager.FileOpen(Af);     

           this->FileManager.WriteToFile("\n");

           this->FileManager.WriteToFile(include_command);

           this->FileManager.WriteToFile("\n");

           this->FileManager.FileClose();
     }
}


void CMAKE_Target_Library_Builder::Convert_CMAKE_Format(std::string & str){

     for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
     }
}

void CMAKE_Target_Library_Builder::Clear_String_Vector(std::vector<std::string> & str){

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



bool CMAKE_Target_Library_Builder::Check_String_Existance(std::vector<std::string> & list, std::string str){

     size_t list_size = list.size();

     bool is_exist = false;

     for(size_t j=0;j<list_size;j++){

         if(list.at(j) == str){

            is_exist = true;

            return is_exist;
          }
     }

     return is_exist;
}



void CMAKE_Target_Library_Builder::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}
