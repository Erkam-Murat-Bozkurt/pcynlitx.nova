


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



#include "CMAKE_Target_List_Data_Processor.hpp"

CMAKE_Target_List_Data_Processor::CMAKE_Target_List_Data_Processor(char build_type)
{
     this->Memory_Delete_Condition = false;

     this->build_type = build_type;
}


CMAKE_Target_List_Data_Processor::~CMAKE_Target_List_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Target_List_Data_Processor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(!this->Compiler_DataMap.empty()){

             this->Compiler_DataMap.clear();
         }

         if(!this->Target_List_Dependeny_Data.empty()){

             for(size_t i=0;i<this->Target_List_Dependeny_Data.size();i++){

                 if(!this->Target_List_Dependeny_Data.at(i).dep_dt.empty()){

                     this->Target_List_Dependeny_Data.at(i).dep_dt.clear();

                     this->Target_List_Dependeny_Data.at(i).dep_dt.shrink_to_fit();
                 }

                 if(!this->Target_List_Dependeny_Data.at(i).dependent_header_dirs.empty()){

                     this->Target_List_Dependeny_Data.at(i).dependent_header_dirs.clear();

                     this->Target_List_Dependeny_Data.at(i).dependent_header_dirs.shrink_to_fit();
                 }

                 if(!this->Target_List_Dependeny_Data.at(i).dependent_source_dirs.empty()){

                     this->Target_List_Dependeny_Data.at(i).dependent_source_dirs.clear();

                     this->Target_List_Dependeny_Data.at(i).dependent_source_dirs.shrink_to_fit();
                 }
             }

             this->Target_List_Dependeny_Data.clear();

             this->Target_List_Dependeny_Data.shrink_to_fit();
         }
     }
}




void CMAKE_Target_List_Data_Processor::Process_Target_List_Data(){
      
     this->Construct_Compiler_Data_Map();

     for(size_t i=0;i<this->Target_List_Data_Ptr->size();i++){

         this->Process_Target_List_Data(i);
     }
}

void CMAKE_Target_List_Data_Processor::Process_Target_List_Data(int i){

     cmake::target_list_dtr target_dt = this->Target_List_Data_Ptr->at(i);

     cmake::target_data cmake_target;

     std::unordered_map<std::string,cmake::target_dependency_dt> TARGET_DEPENDENCY_REPETITION_CONTROL_MAP;

     this->Process_Target(target_dt,cmake_target,TARGET_DEPENDENCY_REPETITION_CONTROL_MAP);

     if(!TARGET_DEPENDENCY_REPETITION_CONTROL_MAP.empty()){

         TARGET_DEPENDENCY_REPETITION_CONTROL_MAP.clear();
     }

     this->Determine_Target_Dependent_Directories(cmake_target);

     this->Target_List_Dependeny_Data.push_back(cmake_target);

     this->Target_List_Dependeny_Data.shrink_to_fit();
}

void CMAKE_Target_List_Data_Processor::Determine_Target_Dependent_Directories(cmake::target_data & cmake_target){

     std::unordered_map<std::string,std::string> DEPENDENT_HEADER_DIRECTORY;

     std::unordered_map<std::string,std::string> DEPENDENT_SOURCE_DIRECTORY;

     size_t dependency_size = cmake_target.dep_dt.size();

     for(size_t i=0;i<dependency_size;i++){

         if(cmake_target.dep_dt.at(i).is_header_file){

            std::string hdr_path = cmake_target.dep_dt.at(i).dep_file_path;

            std::string hdr_git_record_dir = cmake_target.dep_dt.at(i).dep_file_git_record_dir;

            if(!DEPENDENT_HEADER_DIRECTORY.empty()){

               if(DEPENDENT_HEADER_DIRECTORY.find(hdr_path)==DEPENDENT_HEADER_DIRECTORY.end()){

                  DEPENDENT_HEADER_DIRECTORY.insert(std::make_pair(hdr_path,hdr_git_record_dir));

                  cmake_target.dependent_header_dirs.push_back(hdr_git_record_dir);

                  cmake_target.dependent_header_dirs.shrink_to_fit();
               }
            }
            else{

                  DEPENDENT_HEADER_DIRECTORY.insert(std::make_pair(hdr_path,hdr_git_record_dir));

                  cmake_target.dependent_header_dirs.push_back(hdr_git_record_dir);

                  cmake_target.dependent_header_dirs.shrink_to_fit();
            }
         }
         else{

               std::string src_path = cmake_target.dep_dt.at(i).dep_file_path;

               std::string src_git_record_dir = cmake_target.dep_dt.at(i).dep_file_git_record_dir;

               if(!DEPENDENT_SOURCE_DIRECTORY.empty()){

               if(DEPENDENT_SOURCE_DIRECTORY.find(src_path)==DEPENDENT_SOURCE_DIRECTORY.end()){

                  DEPENDENT_SOURCE_DIRECTORY.insert(std::make_pair(src_path,src_path));

                  cmake_target.dependent_source_dirs.push_back(src_git_record_dir);

                  cmake_target.dependent_source_dirs.shrink_to_fit();
               }
            }
            else{

                  DEPENDENT_SOURCE_DIRECTORY.insert(std::make_pair(src_path,src_git_record_dir));

                  cmake_target.dependent_source_dirs.push_back(src_git_record_dir);

                  cmake_target.dependent_source_dirs.shrink_to_fit();
            }
         }
     }     

     if(!DEPENDENT_HEADER_DIRECTORY.empty()){

         DEPENDENT_HEADER_DIRECTORY.clear();
     }

     if(!DEPENDENT_SOURCE_DIRECTORY.empty()){

         DEPENDENT_SOURCE_DIRECTORY.clear();
     }
}

void CMAKE_Target_List_Data_Processor::Process_Target(cmake::target_list_dtr & target_dt, 
    
     cmake::target_data & target, std::unordered_map<std::string,cmake::target_dependency_dt> & REPETITION_CONTROL_MAP){

     target.target_sys_dir = target_dt.DATA_PTR->src_sys_dir;

     target.target_git_record_dir = target_dt.DATA_PTR->src_git_record_dir;

     target.target_name_with_file_extention = target_dt.DATA_PTR->source_file_name;

     target.target_name = target_dt.DATA_PTR->source_file_name_witout_ext;

     target.target_file_path = target_dt.DATA_PTR->source_file_path;

     cmake::target_dependency_dt source_file_dependency_dt;

     this->Set_Target_Dependency_Data_For_Source(source_file_dependency_dt,target_dt.DATA_PTR);


     REPETITION_CONTROL_MAP.insert(std::make_pair(target.target_file_path,source_file_dependency_dt));
        
     this->Process_Target_Depenendecies(target_dt.DATA_PTR,target.dep_dt,REPETITION_CONTROL_MAP);
}


void CMAKE_Target_List_Data_Processor::Process_Target_Depenendecies(const Compiler_Data * DATA_PTR, 
    
     std::vector<cmake::target_dependency_dt> & target_dep,
     
     std::unordered_map<std::string,cmake::target_dependency_dt> & REPETITION_CONTROL_MAP){
     

     const std::vector<std::string> * dep_headers      = &(DATA_PTR->dependent_headers);
         
     const std::vector<std::string> * dep_headers_dirs = &(DATA_PTR->dependent_headers_dir);


     for(size_t k=0;k<dep_headers->size();k++){

         cmake::target_dependency_dt hdr_dependency_dt;

         this->Set_Target_Dependency_Data_For_Header(hdr_dependency_dt,dep_headers->at(k),dep_headers_dirs->at(k));

         std::string hdr_path = hdr_dependency_dt.dep_file_path;

         if(!REPETITION_CONTROL_MAP.empty()){

            if(REPETITION_CONTROL_MAP.find(hdr_path)==REPETITION_CONTROL_MAP.end()){

               REPETITION_CONTROL_MAP.insert(std::make_pair(hdr_path,hdr_dependency_dt));

               target_dep.push_back(hdr_dependency_dt);

               target_dep.shrink_to_fit();
            }
         }
         else{

             REPETITION_CONTROL_MAP.insert(std::make_pair(hdr_path,hdr_dependency_dt));

             target_dep.push_back(hdr_dependency_dt);

             target_dep.shrink_to_fit();
         }

         // The controlling stage: Control whether the header file has a source file ".cpp" 

         // If there is a corresponding source file, its dependencies must be also researched.

         std::string file_name_without_ext;

         this->Find_File_Name_Without_Extension(dep_headers->at(k),file_name_without_ext);

         const Compiler_Data * COM_PTR = Find_Compiler_Data_From_File_Name(file_name_without_ext);

         if(COM_PTR != nullptr){

            std::string src_path = COM_PTR->source_file_path;

            if(!REPETITION_CONTROL_MAP.empty()){

                if(REPETITION_CONTROL_MAP.find(src_path)==REPETITION_CONTROL_MAP.end()){

                   cmake::target_dependency_dt source_file_dependency_dt;

                   this->Set_Target_Dependency_Data_For_Source(source_file_dependency_dt,COM_PTR);

                   REPETITION_CONTROL_MAP.insert(std::make_pair(src_path,source_file_dependency_dt));

                   target_dep.push_back(source_file_dependency_dt);

                   target_dep.shrink_to_fit();

                   this->Process_Target_Depenendecies(COM_PTR,target_dep,REPETITION_CONTROL_MAP);
                }
            }
            else{

                   cmake::target_dependency_dt source_file_dependency_dt;

                   this->Set_Target_Dependency_Data_For_Source(source_file_dependency_dt,COM_PTR);

                   REPETITION_CONTROL_MAP.insert(std::make_pair(src_path,source_file_dependency_dt));

                   target_dep.push_back(source_file_dependency_dt);

                   target_dep.shrink_to_fit();

                   this->Process_Target_Depenendecies(COM_PTR,target_dep,REPETITION_CONTROL_MAP);
            }
        }
        else{

           cmake::target_dependency_dt header_file_dependency_dt;

           this->Set_Target_Dependency_Data_For_Header(header_file_dependency_dt,
            
                 dep_headers->at(k),dep_headers_dirs->at(k));

           std::string hdr_path = header_file_dependency_dt.dep_file_path;

           if(REPETITION_CONTROL_MAP.find(hdr_path)==REPETITION_CONTROL_MAP.end()){

              REPETITION_CONTROL_MAP.insert(std::make_pair(hdr_path,header_file_dependency_dt));

              target_dep.push_back(header_file_dependency_dt);

              target_dep.shrink_to_fit();
           }
        }
    }
}


void CMAKE_Target_List_Data_Processor::Set_Target_Dependency_Data_For_Header(cmake::target_dependency_dt & target_dep,

     std::string header_name, std::string header_dir){

     std::string file_name_without_ext;

     this->Find_File_Name_Without_Extension(header_name,file_name_without_ext);

     target_dep.dep_file_name = file_name_without_ext;

     target_dep.dep_file_name_with_file_extention = header_name; // The file name with file extention such as ".hpp"

     target_dep.dep_file_sys_dir = header_dir;

     target_dep.dep_file_path = header_dir + "/" + header_name;

     target_dep.dep_file_git_record_dir = this->Extract_Git_Record_Path(header_dir); 
     
     target_dep.is_source_file = false;

     target_dep.is_header_file = true;
}



void CMAKE_Target_List_Data_Processor::Set_Target_Dependency_Data_For_Source(cmake::target_dependency_dt & target_dep,

     const Compiler_Data * COM_PTR){

     target_dep.dep_file_name  =  COM_PTR->source_file_name_witout_ext;

     target_dep.dep_file_git_record_dir = COM_PTR->src_git_record_dir;

     target_dep.dep_file_path = COM_PTR->source_file_path;

     target_dep.dep_file_git_record_dir = COM_PTR->src_git_record_dir;

     target_dep.dep_file_sys_dir = COM_PTR->src_sys_dir;

     target_dep.dep_file_name_with_file_extention =  COM_PTR->source_file_name;

     target_dep.is_source_file = true;

     target_dep.is_header_file = false;
}


void CMAKE_Target_List_Data_Processor::Construct_Compiler_Data_Map(){
    
      for(size_t i=0;i<this->Compiler_Data_Pointer->size();i++){

          std::string name_without_ext = this->Compiler_Data_Pointer->at(i).source_file_name_witout_ext;

          this->Compiler_DataMap.insert(std::make_pair(name_without_ext,&this->Compiler_Data_Pointer->at(i)));
      }
}


const Compiler_Data * CMAKE_Target_List_Data_Processor::Find_Compiler_Data_From_File_Name(std::string hdr_name) const
{
    try {        

         return this->Compiler_DataMap.at(hdr_name);
    }
    catch (const std::out_of_range & oor) {
        
         return nullptr;
    }     
}


void CMAKE_Target_List_Data_Processor::Find_File_Name_Without_Extension(std::string hdr_name, 

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



std::string CMAKE_Target_List_Data_Processor::Extract_Git_Record_Path(std::string path){

            std::string repo_dir = this->Des_Reader->Get_Repo_Directory_Location();

            repo_dir.shrink_to_fit();

            std::string git_path;

            for(size_t i=repo_dir.size()+1;i<path.size();i++){
                 
                git_path.push_back(path.at(i));
            }

            git_path.shrink_to_fit();

            this->Convert_CMAKE_Format(git_path);

            return git_path;
}


void CMAKE_Target_List_Data_Processor::Print_Processed_Data(){

     for(size_t i=0;i<this->Target_List_Dependeny_Data.size();i++){
        
         std::vector<cmake::target_data> * Dep_Data_Ptr = 

         &this->Target_List_Dependeny_Data;

         std::cout << "\n\n";

         std::cout << "\n TARGET NAME:" << Dep_Data_Ptr->at(i).target_name;

         std::cout << "\n ----------------------------------------------------------------------";

         for(size_t k=0;k<Dep_Data_Ptr->at(i).dep_dt.size();k++){

             std::cout << "\n Target Name:" << Dep_Data_Ptr->at(i).dep_dt.at(k).dep_file_name;

             std::cout << "\n\n";
         }

         std::cout << "\n\n";
     }

     //exit(0);
}