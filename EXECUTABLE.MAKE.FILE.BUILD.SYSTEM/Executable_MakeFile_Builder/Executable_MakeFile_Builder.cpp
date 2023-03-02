

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

#include "Executable_MakeFile_Builder.hpp"

Executable_MakeFile_Builder::Executable_MakeFile_Builder(char * des_path, char opr_sis):

Des_Reader(des_path), Dep_Determiner(des_path,opr_sis),

ComConstructor(des_path,opr_sis), Initializer(des_path,opr_sis)

{
     this->Des_Reader.Read_Descriptor_File();
   
}


Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

       this->Clear_Dynamic_Memory();
   
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     this->Dep_Determiner.Clear_Dynamic_Memory();

     this->ComConstructor.Clear_Dynamic_Memory();
}

void Executable_MakeFile_Builder::Update_Warehaouse_Headers()
{
     this->Initializer.Update_Warehaouse_Headers();

     this->Initializer.Clear_Dynamic_Memory();

     std::cout << "\n Project Warehouse Headers Updated ..";
}

void Executable_MakeFile_Builder::Build_MakeFile(char * mn_src_path, char * Exe_Name){

     this->Dep_Determiner.Collect_Dependency_Information(mn_src_path);

     this->ComConstructor.Receive_ExeFileName(Exe_Name);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);


     // Receiving the compiler data from the member objects

     this->warehouse_head_dir = this->ComConstructor.Get_Warehouse_Headers_Dir();

     this->warehouse_obj_dir  = this->ComConstructor.Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->ComConstructor.Get_Warehouse_Path();

     this->Src_File_Dir       = this->ComConstructor.Get_Src_File_Dr();

     this->git_src_dir        = this->ComConstructor.Get_Git_Src_Dr();

     this->make_file_name     = this->ComConstructor.Get_Make_File_Name();

     this->Compiler_System_Command = this->ComConstructor.Get_Compiler_System_Command();

     this->Write_MakeFile(Exe_Name);
}


void Executable_MakeFile_Builder::Write_MakeFile(char * Exe_Name){

     this->DirectoryManager.ChangeDirectory(this->Src_File_Dir.c_str());

     this->FileManager.SetFilePath(this->make_file_name);

     this->FileManager.FileOpen(RWCf);


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_HEADERS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_head_dir);


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_obj_dir);


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("REPO_DIRECTORY=");

     this->FileManager.WriteToFile(this->warehouse_path);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=$(REPO_DIRECTORY)");


     if(!this->Src_File_Dir.empty()){

        this->FileManager.WriteToFile("\\");

        this->FileManager.WriteToFile(this->git_src_dir);
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

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile(Exe_Name);

     this->FileManager.WriteToFile(": ");

     std::vector<std::string> * object_list = this->ComConstructor.Get_Object_File_List();

     std::vector<std::string> * header_list = this->ComConstructor.Get_Header_File_List();

     object_list->shrink_to_fit();

     header_list->shrink_to_fit();

     size_t object_list_size = object_list->size();

     size_t header_list_size = header_list->size();

     for(size_t i=0;i<object_list_size;i++){
     
         this->FileManager.WriteToFile(object_list->at(i));

         this->FileManager.WriteToFile("\n\t");     
     }

     for(size_t i=0;i<header_list_size;i++){
     
         this->FileManager.WriteToFile(header_list->at(i));

         this->FileManager.WriteToFile("\n\t");     
     }

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.FileClose();

}
