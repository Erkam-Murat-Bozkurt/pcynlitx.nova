






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


#include "CMAKE_Executable_Target_Constructor.hpp"

CMAKE_Executable_Target_Constructor::CMAKE_Executable_Target_Constructor(char * DesPath, char opr_sis, 

    char build_type) : 
  
    Des_Reader(opr_sis),
    
    Dep_Determiner(DesPath,opr_sis) , Data_Processor(opr_sis)
{
    this->Memory_Delete_Condition = false;

    this->opr_sis = opr_sis;
 
    this->build_type = build_type;

    size_t des_path_size = strlen(DesPath);

    for(size_t i=0;i<des_path_size;i++){

        this->DesPATH.push_back(DesPath[i]);
    }

    this->DesPATH.shrink_to_fit();
     
}


CMAKE_Executable_Target_Constructor::~CMAKE_Executable_Target_Constructor(){

    this->Clear_Object_Memory();
}


void CMAKE_Executable_Target_Constructor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void CMAKE_Executable_Target_Constructor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->StrOpr.Clear_Dynamic_Memory();
     }
}


void CMAKE_Executable_Target_Constructor::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;
}


void CMAKE_Executable_Target_Constructor::Build_MakeFile(std::string file_path, std::string exe_name){

     this->Memory_Delete_Condition = false;

     
     // Determination of the directories recorded on the git repo
          
     this->Des_Reader.Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader.Read_Descriptor_File();


     char read_opr [] = "\n\n The project descriptor file read\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
 

     this->Data_Processor.Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  


     char git_data [] = "\n The data for git version controller has been collected\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Simple_Dependency_Determination_For_Single_Source_File(file_path);




     char dependency_data [] = "\n Source file dependencies has been determined\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     this->dep_ptr = this->Dep_Determiner.Get_Simple_File_Dependencies();




     int target_counter = 0;

     std::string target_dep_list;

     std::string space_string = " ";

     std::string str_encode;

     this->Directory_Path_Encoder(this->dep_ptr->src_git_record_dir,str_encode);

     std::string target_name = "$<TARGET_OBJECTS:" +
         
     this->dep_ptr->source_file_name_without_ext + "_" + str_encode + ">";

     target_dep_list = target_dep_list + target_name + space_string + "\n\t";   


     std::string file_dir = this->dep_ptr->src_sys_dir;

     std::string CMake_File_Path = file_dir;


     if(this->opr_sis == 'w'){

        CMake_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMake_File_Path.push_back('/');
     }


     std::string encode_string;
          
     this->Directory_Path_Encoder(this->dep_ptr->src_git_record_dir,encode_string);


     std::string file_name = exe_name + ".cmake";

     CMake_File_Path = CMake_File_Path +  file_name;



     this->FileManager.SetFilePath(CMake_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("add_executable(");

     this->FileManager.WriteToFile(exe_name);     

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\t");

     std::string src_file_path = file_path;


     this->Convert_CMAKE_Format(src_file_path);

     this->FileManager.WriteToFile(src_file_path);        

     this->FileManager.WriteToFile("\n\t");  



     

     for(size_t i=0;i<this->dep_ptr->Dependent_Header_Paths.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\t");

         std::string dep_header_path = this->dep_ptr->Dependent_Header_Paths.at(i);
               
         this->Convert_CMAKE_Format(dep_header_path);

         this->FileManager.WriteToFile(dep_header_path);         
     }



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");
     
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     
     this->FileManager.WriteToFile("target_include_directories(");

     this->FileManager.WriteToFile(exe_name);     

     this->FileManager.WriteToFile(" PUBLIC ");
     
     this->FileManager.WriteToFile("\n");
     
     for(size_t i=0;i<this->dep_ptr->Dependent_Header_Directories.size();i++){

         this->FileManager.WriteToFile("\n\t");

         std::string dep_header_dir = this->dep_ptr->Dependent_Header_Directories.at(i);
      
         this->Convert_CMAKE_Format(dep_header_dir);


         this->FileManager.WriteToFile(dep_header_dir);      
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");



     const std::vector<std::string> & Lib_Dirs =  this->Des_Reader.Get_Library_Directories();

     if(Lib_Dirs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("target_link_directories(");

        this->FileManager.WriteToFile(exe_name);          

        this->FileManager.WriteToFile(" PUBLIC ");

        for(size_t i=0;i<Lib_Dirs.size();i++){

            this->FileManager.WriteToFile("\n\n\t");

            std::string lib_dir = Lib_Dirs.at(i);

            this->Convert_CMAKE_Format(lib_dir);

            this->FileManager.WriteToFile(lib_dir);
        }

        this->FileManager.WriteToFile("\n\n )");
     }



     const std::vector<std::string> & Libs =  this->Des_Reader.Get_Library_Files();

     if(Libs.size()>0){

        this->FileManager.WriteToFile("\n\n ");

        this->FileManager.WriteToFile("target_link_libraries(");

        this->FileManager.WriteToFile(exe_name);          

        this->FileManager.WriteToFile(" PUBLIC ");

        this->FileManager.WriteToFile("\n\n\t");

        int lib_counter = 0;

        for(size_t i=0;i<Libs.size();i++){

            std::string library = Libs.at(i);

            this->Convert_CMAKE_Format(library);

            this->FileManager.WriteToFile(library);

            this->FileManager.WriteToFile("\n\n\t");
        }

        std::string project_lib_name = this->Des_Reader.Get_Project_Name() + "_lib";

        this->FileManager.WriteToFile(project_lib_name);

        this->FileManager.WriteToFile("\n )");
     }  


     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_compile_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     this->FileManager.WriteToFile("\n\n    ");

     const std::vector<std::string> & com_options = this->Des_Reader.Get_Compiler_Options();

     for(size_t i=0;i<com_options.size();i++){

         this->FileManager.WriteToFile("\n\n ");

         this->FileManager.WriteToFile(com_options.at(i));
     }

     this->FileManager.WriteToFile("\n\n ");


     this->FileManager.WriteToFile(")");


     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_link_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     this->FileManager.WriteToFile("\n\n    ");



     const std::vector<std::string> & link_options = this->Des_Reader.Get_Linker_Options();

     for(size_t i=0;i<link_options.size();i++){

         this->FileManager.WriteToFile("\n\n ");

         this->FileManager.WriteToFile(link_options.at(i));
     }

     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.FileClose();


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


void CMAKE_Executable_Target_Constructor::Directory_Path_Encoder(std::string sys_dir, std::string & str_encode){
    
     std::vector<std::string> dir_sort_path;

     std::string file_git_record_directory = sys_dir;

     this->Extract_Directory_Short_Path(file_git_record_directory,dir_sort_path);
     
     for(auto it=dir_sort_path.rbegin();it<dir_sort_path.rend();it++){

         std::string str = *it;

         int encode = 0;

         for(char c : str){

             encode += static_cast<int>(c);
         }

         std::string str_numbers = std::to_string(encode); 
         
         if(str_numbers.size()>0){
             
            str_numbers.push_back('_');
         }

         str_encode += str_numbers;
     }


     str_encode.shrink_to_fit();

     if(str_encode.back()=='_'){

        str_encode.erase(str_encode.size()-1);
     }
}



void CMAKE_Executable_Target_Constructor::Extract_Directory_Short_Path(std::string sys_dir, 

     std::vector<std::string> & sort_dir_path){

     size_t dir_size = sys_dir.length();
     
     std::string repo_dir = this->Des_Reader.Get_Repo_Directory_Location();

     std::string file_path =  repo_dir + "\\" + sys_dir;

     file_path.shrink_to_fit();

     size_t end_point = file_path.size();

     size_t start_point = end_point;

     do{

        std::string short_path;

        for(size_t i=end_point;i>repo_dir.size();i--){

            if((file_path[i] == '\\') || (file_path[i] == '/')){

                break;
            }
            else{

               start_point--;
            }
        }

        for(size_t i=start_point+1;i<end_point;i++){

            short_path.push_back(file_path[i]);
        }

        short_path.shrink_to_fit();


        for(size_t i=file_path.length();i>start_point-1;i--){

            file_path.erase(i,1);
        }

        file_path.shrink_to_fit();


        if(!short_path.empty()){

           sort_dir_path.push_back(short_path);
        }

        end_point = file_path.size();


     }while(file_path.size()>repo_dir.size());

     sort_dir_path.shrink_to_fit();
}



void CMAKE_Executable_Target_Constructor::Find_Construction_Directory(std::string & dir, std::string file_path){

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

void CMAKE_Executable_Target_Constructor::CMAKE_Sub_Directory_File_Path_Determination(std::string & path){

     std::string warehouse_location = this->Des_Reader.Get_Repo_Directory_Location();

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


void CMAKE_Executable_Target_Constructor::CMAKE_SubDir_Determination(std::string & sub_dir_path){

     std::string git_dir = 
     
     this->Des_Reader.Get_Repo_Directory_Location() + "\\" + this->dep_ptr->src_git_record_dir;


     if(this->opr_sis == 'w'){

          for(size_t i=0;i<git_dir.size();i++){

               if(git_dir[i]=='\\'){

                    git_dir[i] = '/';
               }
          }
     }     
     
     sub_dir_path = git_dir;
}



void CMAKE_Executable_Target_Constructor::Convert_CMAKE_Format(std::string & str){

     for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
     }
}

void CMAKE_Executable_Target_Constructor::Clear_String_Vector(std::vector<std::string> & str){

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




void CMAKE_Executable_Target_Constructor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}
