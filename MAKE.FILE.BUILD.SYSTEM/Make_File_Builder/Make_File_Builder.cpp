
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

#include "Make_File_Builder.h"

Make_File_Builder::Make_File_Builder(char * DesPath, char opr_sis) :

    Data_Collector(DesPath,opr_sis),  Des_Reader(opr_sis) 
{

   this->Memory_Delete_Condition = false;

   this->Des_Reader.Read_Descriptor_File();

   this->opr_sis = opr_sis;
}


Make_File_Builder::~Make_File_Builder(){

    this->Clear_Object_Memory();
}


void Make_File_Builder::Clear_Object_Memory(){

     this->Data_Collector.Clear_Object_Memory();

     this->Des_Reader.Clear_Dynamic_Memory();

     this->DataMap.clear();

     this->Clear_Dynamic_Memory();
}

void Make_File_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Data_Collector.Clear_Dynamic_Memory();

         this->DirectoryManager.Clear_Dynamic_Memory();
     }
}


void Make_File_Builder::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr)
{
     this->Comp_Data_Ptr = ptr;

     this->Construct_Data_Map();
}

void Make_File_Builder::Construct_Data_Map(){

     for(size_t i=0;i<this->Comp_Data_Ptr->size();i++){

         std::string source_file_name = this->Comp_Data_Ptr->at(i).source_file_name;

         this->DataMap.insert(std::make_pair(source_file_name,this->Comp_Data_Ptr->at(i)));
     }
}


Compiler_Data * Make_File_Builder::Find_Compiler_Data_From_Source_File_Name(std::string name)
{
    try {        

         return  &this->DataMap.at(name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n the file named " << name << " can not find on Make_File_Builder object!.\n";

         exit(EXIT_FAILURE);
    }     
}


void Make_File_Builder::Build_MakeFile(std::string file_name){

     this->Data_Collector.Clear_Dynamic_Memory();

     this->Data_Ptr = this->Find_Compiler_Data_From_Source_File_Name(file_name);

     this->Data_Collector.Receive_Compiler_Data_Pointer(this->Data_Ptr);

     std::string Source_File_Name = this->Data_Ptr->source_file_name;

     this->Data_Collector.Collect_Make_File_Data(Source_File_Name);

     std::string Source_File_Directory = this->Data_Collector.Get_Source_File_System_Directory();

     this->DirectoryManager.ChangeDirectory(Source_File_Directory);

     std::string Make_File_Name = this->Data_Collector.Get_Make_File_Name();

     this->FileManager.SetFilePath(Make_File_Name);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_HEADERS_LOCATION=");

     std::string warehouse_head_dir = this->Data_Collector.Get_Warehouse_Header_Dir();

     this->FileManager.WriteToFile(warehouse_head_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");


     std::string warehouse_obj_dir = this->Data_Collector.Get_Warehouse_Object_Dir();

     this->FileManager.WriteToFile(warehouse_obj_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("REPO_DIR=");

     std::string project_repo_dir = this->Data_Collector.Get_Repo_Dir();

     this->FileManager.WriteToFile(project_repo_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=$(REPO_DIR)");


     std::string sys_path = this->Data_Ptr->source_file_path;



     std::string source_file_dir;

     this->Determine_Git_Record_Directory(source_file_dir,sys_path);
     
     if(!source_file_dir.empty()){

        this->FileManager.WriteToFile("\\");

        this->FileManager.WriteToFile(source_file_dir);
     }



     int included_dir_num = this->Des_Reader.Get_Include_Directory_Number();

     char include_symbol [] = "EXTERNAL_INCLUDE_DIR_";

     char underscore [] = "_";

     this->FileManager.WriteToFile("\n");

     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         std::string included_dir = this->Des_Reader.Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(include_symbol);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile("=");

         this->FileManager.WriteToFile(included_dir);
     }

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();


     char PathSpecifier [] = {'v','p','a','t','h',' ','%','\0'};

     char header_add [] = ".h";

     char object_add [] = ".o";

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);

     this->FileManager.WriteToFile(header_add);

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile("$(PROJECT_HEADERS_LOCATION)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);

     this->FileManager.WriteToFile(object_add);

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile("$(PROJECT_OBJECTS_LOCATION)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         std::string included_dir = this->Des_Reader.Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(PathSpecifier);

         this->FileManager.WriteToFile(header_add);

         this->FileManager.WriteToFile(" $(");

         this->FileManager.WriteToFile(include_symbol);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile(")");

     }

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     std::string Dependency_Code_Line    = this->Data_Collector.Get_Dependency_Code_Line();

     std::string Compiler_System_Command = this->Data_Collector.Get_Compiler_System_Command();

     this->FileManager.WriteToFile(Dependency_Code_Line);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(Compiler_System_Command);

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}


void Make_File_Builder::Write_Header_Paths_Shorts_Cuts(){

     
     std::vector<std::string> * header_directories = &this->Data_Ptr->dependent_headers_dir;

     std::vector<std::string> * header_names = &this->Data_Ptr->dependent_headers;

     size_t hdr_dir_size = header_directories->size();


     for(size_t i=0;i<hdr_dir_size;i++){

          std::string dir = header_directories->at(i);
          std::string name = header_names->at(i);
          
          this->FileManager.WriteToFile(name);
          this->FileManager.WriteToFile("_Path=");
          this->FileManager.WriteToFile(dir);
          this->FileManager.WriteToFile("\n\n");        ;
     }   
}

void Make_File_Builder::Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path){

     std::string root_dir = this->Des_Reader.Get_Repo_Directory_Location();

     size_t path_size = sys_path.length();
     size_t end_point = path_size;
     size_t start_point = root_dir.length()+1;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(sys_path[i]== '\\'){

               break;
          
            }
            else{

                  end_point--;
            }
         }


         if(this->opr_sis == 'l'){

            if(sys_path[i]== '/'){

               break;
            }
            else{

                  end_point--;
            }
         }
     }


     for(size_t i=start_point;i<end_point;i++){

         git_dir.push_back(sys_path[i]);
     }

     git_dir.shrink_to_fit();

}