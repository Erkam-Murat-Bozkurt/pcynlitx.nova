




/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

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

         this->Path_Determiner.Clear_Dynamic_Memory();
     }
}


void CMAKE_Target_Library_Builder::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;

     this->Path_Determiner.Receive_Operating_System(opr_sis);
}


void CMAKE_Target_Library_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Path_Determiner.Receive_Descriptor_File_Reader(ptr);
}

void CMAKE_Target_Library_Builder::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr)
{
     this->Comp_Data_Ptr = ptr;

     this->Path_Determiner.Receive_Compiler_Data_Pointer(ptr);
}


void CMAKE_Target_Library_Builder::Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr){

     this->DataMap_Pointer = ptr;

     this->Path_Determiner.Receive_DataMap(ptr);
}


void CMAKE_Target_Library_Builder::Receive_Simple_Dependency_Data(const Simple_Source_File_Dependency * data_ptr){

     this->dep_data_ptr = data_ptr;
}


Compiler_Data * CMAKE_Target_Library_Builder::Find_Compiler_Data_From_Source_File_Path(std::string path)
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


void CMAKE_Target_Library_Builder::Build_MakeFile(std::string file_path){

     this->Memory_Delete_Condition = false;


     std::string file_dir = this->dep_data_ptr->dir;


     std::string CMake_File_Path = file_dir;

     if(this->opr_sis == 'w'){

        CMake_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMake_File_Path.push_back('\\');
     }

     std::string file_name = this->dep_data_ptr->cmake_target_name  + ".cmake";


     CMake_File_Path = CMake_File_Path +  file_name;


     this->FileManager.SetFilePath(CMake_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("add_library(");

     this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);          

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("  OBJECT ");

     std::string src_file_path = this->dep_data_ptr->source_file_path;

     this->Convert_CMAKE_Format(src_file_path);

     this->FileManager.WriteToFile(src_file_path);          


     std::vector<std::string> dependent_header_paths;


     for(size_t i=0;i<this->dep_data_ptr->Dependent_Header_Paths.size();i++){
      
         std::string dep_header_path = this->dep_data_ptr->Dependent_Header_Paths.at(i);

         this->Convert_CMAKE_Format(dep_header_path);

         if(!this->Check_String_Existance(dependent_header_paths,dep_header_path)){

            dependent_header_paths.push_back(dep_header_path);
         }
     }

     dependent_header_paths.shrink_to_fit();



     for(size_t i=0;i<dependent_header_paths.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("  ");

         this->FileManager.WriteToFile(dependent_header_paths.at(i));      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->Clear_String_Vector(dependent_header_paths);



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



     
     this->FileManager.WriteToFile("target_include_directories(");

     this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);     

     this->FileManager.WriteToFile(" PUBLIC ");
     
     this->FileManager.WriteToFile("\n");


     std::vector<std::string> dependent_header_dirs;

     for(size_t i=0;i<this->dep_data_ptr->Dependent_Header_Directories.size();i++){

         std::string dep_header_dir = this->dep_data_ptr->Dependent_Header_Directories.at(i);
      
         if(!this->Check_String_Existance(dependent_header_dirs,dep_header_dir)){

            dependent_header_dirs.push_back(dep_header_dir);
         }
     }

     for(size_t i=0;i<dependent_header_dirs.size();i++){

         std::string dep_header_dir = dependent_header_dirs.at(i);
      
         std::string upper_dir = this->Search_For_New_Upper_Directory(dependent_header_dirs,dep_header_dir);

         if(!this->Check_String_Existance(dependent_header_dirs,dep_header_dir)){

            dependent_header_dirs.push_back(upper_dir);
         }
     }

     
    dependent_header_dirs.shrink_to_fit();

     for(size_t i=0;i<dependent_header_dirs.size();i++){

         this->Convert_CMAKE_Format(dependent_header_dirs.at(i));
     }


     dependent_header_dirs.shrink_to_fit();


     for(size_t i=0;i<dependent_header_dirs.size();i++){

         this->FileManager.WriteToFile("\n\t");
      
         this->FileManager.WriteToFile(dependent_header_dirs.at(i));      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->Clear_String_Vector(dependent_header_dirs);




     const std::vector<std::string> & Lib_Dirs =  this->Des_Reader->Get_Library_Directories();

     if(Lib_Dirs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("target_link_directories(");

        this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);          

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

        this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);          

        this->FileManager.WriteToFile(" PUBLIC ");

        this->FileManager.WriteToFile("\n\n    ");

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

     this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);          

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

     this->FileManager.WriteToFile(this->dep_data_ptr->cmake_target_name);          

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

void CMAKE_Target_Library_Builder::Find_Construction_Directory(std::string & dir, std::string file_path){

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


void CMAKE_Target_Library_Builder::CMAKE_SubDir_Determination(std::string & sub_dir_path){

     std::string git_dir = this->dep_data_ptr->dir;

     if(this->opr_sis == 'w'){

          for(size_t i=0;i<git_dir.size();i++){

               if(git_dir[i]=='\\'){

                    git_dir[i] = '/';
               }
          }
     }     
     
     sub_dir_path = git_dir;
}


 void CMAKE_Target_Library_Builder::Add_Target_Path_To_Directory_List(){ // Mutual exclusion is required
       
      std::string directory_list_file_path, cmake_sub_dir;

      this->CMAKE_SubDir_Determination(cmake_sub_dir);

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

void CMAKE_Target_Library_Builder::Construct_SubDirectory_List_File(){

     std::string file_name = this->dep_data_ptr->cmake_target_name  + ".cmake";

     std::string file_dir = this->dep_data_ptr->dir;

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

std::string CMAKE_Target_Library_Builder::Get_Construction_Dir(){

     std::string Make_File_Path = this->Path_Determiner.Get_MakeFile_Path();

     std::string dir;

     this->Find_Construction_Directory(dir,Make_File_Path);

     return dir;
}




std::string CMAKE_Target_Library_Builder::Search_For_New_Upper_Directory(std::vector<std::string> & dir_list,

     std::string dir){
     
     std::string upper_directory;

     this->Find_Upper_Directory(upper_directory,dir);
        
     bool is_exist = this->Check_String_Existance(dir_list,upper_directory);

     std::string repo_dir = this->Des_Reader->Get_Repo_Directory_Location();

     if(!is_exist){

         size_t root_dir_size = repo_dir.size();

         size_t next_dir_size = upper_directory.size();

         if(next_dir_size > root_dir_size){

            dir_list.push_back(upper_directory);
         }

         dir_list.shrink_to_fit();
      }

      return upper_directory;
}



void CMAKE_Target_Library_Builder::Find_Upper_Directory(std::string & upper_dir, std::string dir){

     size_t dir_size = dir.length();

     size_t end_point = 0;

     for(size_t i=dir_size;i>0;i--){

         if((dir[i]=='\\') || (dir[i]=='/')){

             end_point = i;

             break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         upper_dir.push_back(dir[i]);
     }

     upper_dir.shrink_to_fit();
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
