

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



#include "Build_System_Meta_Data_Collector.hpp"

Build_System_Meta_Data_Collector::Build_System_Meta_Data_Collector(char * DesPath, char opr_sis, char build_type) :

    Des_Reader(opr_sis),
    
    Dep_Determiner(DesPath,opr_sis) , Data_Processor(opr_sis)
{
     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;

     this->Des_Path = DesPath;
     
     this->build_type = build_type;

     size_t des_path_size = strlen(DesPath);

     for(size_t i=0;i<des_path_size;i++){

         this->DesPATH.push_back(DesPath[i]);
     }

     this->DesPATH.shrink_to_fit();

     this->Des_Reader.Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader.Read_Descriptor_File();

     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;
}


Build_System_Meta_Data_Collector::~Build_System_Meta_Data_Collector(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Build_System_Meta_Data_Collector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(this->repo_obj_dir);

         this->Clear_String_Memory(this->Warehouse_Path);

         this->Clear_String_Memory(this->Repo_Dir);

         this->DataMap.clear();
     }
}




void Build_System_Meta_Data_Collector::Collect_Meta_Data()
{
     char read_opr [] = "\nThe project descriptor file read\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
     

     // Determination of the directories recorded on the git repo
          
     this->Data_Processor.Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  

     char git_data [] = "\nThe data for git version controller has been collected\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }
     
     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Collect_Dependency_Information();

     this->Compiler_Data_Pointer = this->Dep_Determiner.Get_Compiler_Data_Address();

     char dependency_data [] = "\nSource file dependencies has been determined\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     this->Perform_Data_Map_Construction();

     char map_construction [] = "\nData Map construction has been performed..\n";

     std::cout << map_construction;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(map_construction);
     }
}

void Build_System_Meta_Data_Collector::Perform_Data_Map_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     for(size_t i=0;i<data_size;i++){

         std::string source_file_path= this->Compiler_Data_Pointer->at(i).source_file_path;

         this->DataMap.insert(std::make_pair(source_file_path,this->Compiler_Data_Pointer->at(i)));
     }
}

void Build_System_Meta_Data_Collector::Clear_Vector_Memory(std::vector<std::string> & vec){

    vec.shrink_to_fit();

    for(size_t i=0;i<vec.size();i++){

        this->Clear_String_Memory(vec.at(i));
    }

    vec.shrink_to_fit();

    vec.clear();
}

void Build_System_Meta_Data_Collector::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}