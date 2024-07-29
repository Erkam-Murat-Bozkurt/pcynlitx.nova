




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

#include "CMAKE_Executable_Target_Constructor.hpp"

CMAKE_Executable_Target_Constructor::CMAKE_Executable_Target_Constructor(char * DesPath, char opr_sis, 

    char build_type) : 
  
    Des_Reader(opr_sis,build_type),
    
    Dep_Determiner(DesPath,opr_sis) , Data_Processor(opr_sis,build_type)
{
    this->Memory_Delete_Condition = false;

    this->opr_sis = opr_sis;
 
    this->build_type = build_type;

    size_t des_path_size = strlen(DesPath);

    for(size_t i=0;i<des_path_size;i++){

        this->DesPATH.push_back(DesPath[i]);
    }

    this->DesPATH.shrink_to_fit();
     
    if(this->build_type == 'g'){

       this->Des_Reader.Set_Gui_Read_Status(true);

       this->Data_Processor.Set_Gui_Read_Status(true);
    }
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


     char read_opr [] = "The project descriptor file read\n\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
 

     this->Data_Processor.Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  


     char git_data [] = "The data for git version controller has been collected\n\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Collect_Dependency_Information(file_path);


     char dependency_data [] = "Source file dependencies has been determined\n\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     this->Comp_Data_Ptr = this->Dep_Determiner.Get_Compiler_Data_Address();



     int target_counter = 0;

     std::string target_dep_list;

     std::string space_string = " ";

     for(size_t i=1;i<this->Comp_Data_Ptr->size();i++){

         std::string target_name = "$<TARGET_OBJECTS:" +
         
          this->Comp_Data_Ptr->at(i).source_file_name_witout_ext + ">";

         target_dep_list = target_dep_list + target_name + space_string;

         target_counter++;

         if(target_counter>1){

             target_dep_list = target_dep_list + "\n\t";

             target_counter = 0;
         }      
     }



     this->Data_Ptr = &this->Comp_Data_Ptr->at(0);



     std::string file_dir = this->Data_Ptr->src_sys_dir;

     std::string CMake_File_Path = file_dir;


     if(this->opr_sis == 'w'){

        CMake_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMake_File_Path.push_back('/');
     }

     std::string file_name = this->Data_Ptr->source_file_name_witout_ext  + ".cmake";


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

     this->FileManager.WriteToFile(target_dep_list);

     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\t");

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
     
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     
     this->FileManager.WriteToFile("target_include_directories(");

     this->FileManager.WriteToFile(exe_name);     

     this->FileManager.WriteToFile(" PUBLIC ");
     
     this->FileManager.WriteToFile("\n");
     
     for(size_t i=0;i<this->Data_Ptr->dependent_headers.size();i++){

         this->FileManager.WriteToFile("\n\t");

         std::string dep_header_dir = this->Data_Ptr->dependent_headers_dir.at(i);
      
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



     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_compile_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     this->FileManager.WriteToFile("\n\n    ");

     std::string com_options = this->Des_Reader.Get_Compiler_Options();

     for(size_t i=0;i<com_options.size();i++){

         if(com_options.at(i)=='\\'){

            com_options.erase(i,1);
         }
     }

     this->FileManager.WriteToFile(com_options);


     this->FileManager.WriteToFile(")");


     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_link_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     this->FileManager.WriteToFile("\n\n    ");


     std::string link_options = this->Des_Reader.Get_Linker_Options();

     for(size_t i=0;i<link_options.size();i++){

         if(link_options.at(i)=='\\'){

            link_options.erase(i,1);
         }
     }


     this->FileManager.WriteToFile(link_options);

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

     std::string git_dir = this->Data_Ptr->src_git_record_dir;


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
