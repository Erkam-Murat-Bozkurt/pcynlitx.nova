

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



#include "CMAKE_Executable_Target_Constructor.hpp"

CMAKE_Executable_Target_Constructor::CMAKE_Executable_Target_Constructor(char * DesPath, char opr_sis, 

    char build_type) : 
  
    Target_List_Data_Structure_Constructor(DesPath,opr_sis,build_type),

    Dep_Determiner(DesPath,opr_sis)
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

         for(size_t i=0;i<this->target_library_dependencies.size();i++){

             this->target_library_dependencies.at(i).clear();

             this->target_library_dependencies.at(i).shrink_to_fit();
         }

         this->target_library_dependencies.clear();

         this->Dep_Determiner.Clear_Dynamic_Memory();

         this->FileManager.Clear_Dynamic_Memory();

         this->Target_List_Data_Structure_Constructor.Clear_Dynamic_Memory();
     }
}


void CMAKE_Executable_Target_Constructor::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;

     this->Target_List_Data_Structure_Constructor.Receive_System_Interface(sysInt);

}


void CMAKE_Executable_Target_Constructor::Build_MakeFile(std::string file_path, std::string exe_name, 
    
     std::string rsc_file_path){

     this->Memory_Delete_Condition = false;

     
     // GETTING FUNDAMENTAL BUILD SYSTEM CONSTRUCTION COMPENENTS

     this->Target_List_Data_Structure_Constructor.Construct_Target_List_Data_Structure();

     const Descriptor_File_Reader * Des_Reader 
            
                = this->Target_List_Data_Structure_Constructor.Get_Descriptor_File_Reader();

     Git_Data_Processor * Git_Dt_Ptr 
          
                =  this->Target_List_Data_Structure_Constructor.Get_Git_Data_Processor();

     
     std::string CMake_File_Path;

     std::string make_file_name = exe_name + ".cmake";

     std::string make_file_construction_directory;

     this->Find_Construction_Directory(make_file_construction_directory,file_path);

     CMake_File_Path = make_file_construction_directory;



     if(this->opr_sis == 'w'){

        CMake_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMake_File_Path.push_back('/');
     }


     CMake_File_Path += make_file_name;




     this->Dep_Determiner.Receive_Descriptor_File_Reader(Des_Reader);
     
     this->Dep_Determiner.Receive_Git_Data_Processor(Git_Dt_Ptr);

     this->Dep_Determiner.Receive_System_Interface(this->SysInt);

     this->Dep_Determiner.Simple_Dependency_Determination_For_Single_Source_File(file_path);

     this->Construct_Target_Library_Dependencies_for_Executable();

     this->CONTROL_CLASS_SOURCE_FILE_STATUS(file_path);
     
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

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");  

     if(rsc_file_path != ""){

        this->Convert_CMAKE_Format(rsc_file_path);

        this->FileManager.WriteToFile(rsc_file_path);        

        this->FileManager.WriteToFile("\n\t");  

        this->FileManager.WriteToFile("\n");
     }

     this->FileManager.WriteToFile(")");

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("target_include_directories(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     const std::vector<std::string> & inc_dirs = Des_Reader->Get_Include_Directories();

     for(size_t i=0;i<inc_dirs.size();i++){

         std::string inc_dr = inc_dirs.at(i);

         this->Convert_CMAKE_Format(inc_dr);

         this->FileManager.WriteToFile(inc_dr);

         this->FileManager.WriteToFile("\n\t");
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("target_link_libraries(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\t");

     for(size_t i=0;i<this->target_library_dependencies.size();i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\t");
         
         this->FileManager.WriteToFile(this->target_library_dependencies.at(i));
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\t");

     const std::vector<std::string> & Libs =  Des_Reader->Get_Library_Files();


     for(size_t i=0;i<Libs.size();i++){

         std::string libs = Libs.at(i);

         this->Convert_CMAKE_Format(libs);

         this->FileManager.WriteToFile(libs);

         this->FileManager.WriteToFile("\n\t");
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");



     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("target_compile_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     const std::vector<std::string> & compiler_options = Des_Reader->Get_Compiler_Options();

     for(size_t i=0;i<compiler_options.size();i++){

         this->FileManager.WriteToFile("\n\n    ");

         this->FileManager.WriteToFile(compiler_options.at(i));         
     }

     this->FileManager.WriteToFile("\n\n    ");

     this->FileManager.WriteToFile(")");

     this->FileManager.WriteToFile("\n\n ");



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("target_link_options(");

     this->FileManager.WriteToFile(exe_name);          

     this->FileManager.WriteToFile(" PUBLIC ");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\t");


     const std::vector<std::string> & link_options = Des_Reader->Get_Linker_Options();

     for(size_t i=0;i<link_options.size();i++){

         this->FileManager.WriteToFile("\n\n ");

         this->FileManager.WriteToFile(link_options.at(i));
     }

     this->FileManager.WriteToFile("\n\n ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(")");

     this->FileManager.FileClose();



     std::string directory_list_file_path;

     this->CMAKE_Sub_Directory_File_Path_Determination(directory_list_file_path); // This is used in order to determine  cmake directory list file path (directories.make)

     std::string git_record_dir = this->Extract_Git_Record_Path(file_path);



     std::string add_sub_directory_command = "add_subdirectory(${CMAKE_SOURCE_DIR}/" + git_record_dir + ")";

     this->Convert_CMAKE_Format(add_sub_directory_command);

     if(!this->FileManager.Is_Path_Exist(directory_list_file_path)){
        
        this->FileManager.SetFilePath(directory_list_file_path);

        this->FileManager.FileOpen(Af);  
 
        this->FileManager.WriteToFile("\n\n");

        this->FileManager.WriteToFile(add_sub_directory_command);

        this->FileManager.FileClose();

     }
     else{


          this->StrOpr.SetFilePath(directory_list_file_path);

          bool _exist_status = this->StrOpr.Is_String_Exist_On_File(add_sub_directory_command);

          this->StrOpr.Clear_Dynamic_Memory();

          if(!_exist_status){

             this->FileManager.SetFilePath(directory_list_file_path);

             this->FileManager.FileOpen(Af);  
 
             this->FileManager.WriteToFile("\n\n");

             this->FileManager.WriteToFile(add_sub_directory_command);

             this->FileManager.FileClose();
          }
     }

     
     std::string include_command = "include(" + make_file_name + ")";

     std::string CMAKE_List_File_Path = make_file_construction_directory;
     
     if(this->opr_sis == 'w'){

          CMAKE_List_File_Path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        CMAKE_List_File_Path.push_back('/');
     }
     
     CMAKE_List_File_Path = CMAKE_List_File_Path + "CMakeLists.txt";

     if(this->FileManager.Is_Path_Exist(CMAKE_List_File_Path)){
          
        this->StrOpr.SetFilePath(CMAKE_List_File_Path);

        bool inc_word_exist_status = this->StrOpr.Is_String_Exist_On_File(include_command);

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

void CMAKE_Executable_Target_Constructor::Construct_Target_Library_Dependencies_for_Executable()
{
    const std::vector<cmake::target_data> * target_data_ptr =

           this->Target_List_Data_Structure_Constructor.Get_Target_List_Elements_Dependency_Data();

     const Simple_Source_File_Dependency * Dependency_Data = this->Dep_Determiner.Get_Simple_File_Dependencies();

     for(size_t i=0;i<Dependency_Data->Dependent_Header_Names.size();i++){

         std::string hdr_name = Dependency_Data->Dependent_Header_Names.at(i);

         std::string file_name_without_ext;

         this->Find_File_Name_Without_Extension(hdr_name,file_name_without_ext);

         for(size_t j=0;j<target_data_ptr->size();j++){

             if(target_data_ptr->at(j).target_name == file_name_without_ext){

                this->target_library_dependencies.push_back(file_name_without_ext);
             }
         }
     }
}

// IF A TARGET IS A CLASS SOURCE FILE, THIS MEMBER FUNCTION OBTAINS 
// THE STATUS AND ADD RELATED TARGET TO THE LIST

void CMAKE_Executable_Target_Constructor::CONTROL_CLASS_SOURCE_FILE_STATUS(std::string src_path){

     const std::vector<cmake::target_data> * target_data_ptr =

           this->Target_List_Data_Structure_Constructor.Get_Target_List_Elements_Dependency_Data();

     this->StrOpr.SetFilePath(src_path);

     for(size_t j=0;j<target_data_ptr->size();j++){

        std::string member_function_str = target_data_ptr->at(j).target_name + "::";

         if(this->StrOpr.Is_String_Exist_On_File(member_function_str))
         {
            this->target_library_dependencies.push_back(target_data_ptr->at(j).target_name);
         }
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



void CMAKE_Executable_Target_Constructor::Convert_CMAKE_Format(std::string & str){

     for(size_t i=0;i<str.size();i++){

         if(str[i] == '\\'){

            str[i] = '/';
         }
     }
}




std::string CMAKE_Executable_Target_Constructor::Extract_Git_Record_Path(std::string path){

            const Descriptor_File_Reader * Des_Ptr 
            
                = this->Target_List_Data_Structure_Constructor.Get_Descriptor_File_Reader();

            std::string repo_dir = Des_Ptr->Get_Repo_Directory_Location();

            repo_dir.shrink_to_fit();

            std::string git_record_path, git_record_dir;

            for(size_t i=repo_dir.size()+1;i<path.size();i++){
                 
                git_record_path.push_back(path.at(i));
            }

            git_record_path.shrink_to_fit();


            this->Convert_CMAKE_Format(git_record_path);

            this->Find_Construction_Directory(git_record_dir,git_record_path);

            return git_record_dir;
}


void CMAKE_Executable_Target_Constructor::CMAKE_Sub_Directory_File_Path_Determination(std::string & path){

     const Descriptor_File_Reader * Des_Reader 
            
                = this->Target_List_Data_Structure_Constructor.Get_Descriptor_File_Reader();


     std::string warehouse_location = Des_Reader->Get_Repo_Directory_Location();

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


void CMAKE_Executable_Target_Constructor::Find_File_Name_Without_Extension(std::string hdr_name, 

     std::string & file_name_with_ext){

     size_t end_point =0;

     for(size_t i=hdr_name.size();i>0;i--){

         if(hdr_name[i] == '.'){

            end_point = i;
         }     
     }

     for(size_t i=0;i<end_point;i++){

         file_name_with_ext.push_back(hdr_name[i]);
     }

     file_name_with_ext.shrink_to_fit();
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
