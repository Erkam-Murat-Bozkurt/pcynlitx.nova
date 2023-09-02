

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

   Des_Reader(opr_sis), Git_Data_Proc(opr_sis),
 
   Dep_Determiner(des_path,opr_sis), ComConstructor(opr_sis), Script_Builder(opr_sis)

{
     this->Des_Reader.Receive_Descriptor_File_Path(des_path);

     this->Des_Reader.Read_Descriptor_File();

     this->Git_Data_Proc.Receive_Descriptor_File_Path(des_path);

     this->Git_Data_Proc.Write_Git_Repo_List_File();

     this->Git_Data_Proc.Determine_Git_Repo_Info();
}


Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

       this->Clear_Dynamic_Memory();
   
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     this->Dep_Determiner.Clear_Dynamic_Memory();

     this->ComConstructor.Clear_Dynamic_Memory();

     this->Script_Builder.Clear_Dynamic_Memory();
}


void Executable_MakeFile_Builder::Build_MakeFile(char * mn_src_path, char * Exe_Name){

     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Dep_Determiner.Collect_Dependency_Information(mn_src_path);


     this->Com_Data_ptr = this->Dep_Determiner.Get_Compiler_Data_Address();


     this->ComConstructor.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->ComConstructor.Receive_Depepndency_Determiner(&this->Dep_Determiner);

     this->ComConstructor.Receive_ExeFileName(Exe_Name);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);

     
     this->Script_Builder.Receive_File_System_Path(mn_src_path);

     this->Script_Builder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Script_Builder.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Script_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Builder.Build_Compiler_Script_For_Executable_File(mn_src_path);


     // Receiving the compiler data from the member objects


     this->warehouse_head_dir = this->Dep_Determiner.Get_Warehouse_Headers_Dir();

     this->warehouse_obj_dir  = this->Dep_Determiner.Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner.Get_Warehouse_Path();

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

     this->FileManager.WriteToFile("SOURCE_LOCATION=");


     if(!this->Src_File_Dir.empty()){

        this->FileManager.WriteToFile(this->Src_File_Dir);
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


     char link_dir_alias [] = "EXTERNAL_LINK_DIR_";



     this->FileManager.WriteToFile("\n");

     int library_dir_num = this->Des_Reader.Get_Library_Directory_Number();

     for(int i=0;i<library_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         std::string link_dir = this->Des_Reader.Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(link_dir_alias);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile("=");

         this->FileManager.WriteToFile(link_dir);
     }

     this->FileManager.WriteToFile("\n");



     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     size_t compiler_data_size = this->Com_Data_ptr->size();

     size_t dep_header_size = this->Com_Data_ptr->at(0).dependent_headers.size();

     for(size_t i=0;i<dep_header_size;i++){

          std::string header_name = this->Com_Data_ptr->at(0).dependent_headers.at(i);

          std::string dir = this->Com_Data_ptr->at(0).dependent_headers_dir.at(i);

          this->FileManager.WriteToFile(header_name);

          this->FileManager.WriteToFile("_PATH=");

          this->FileManager.WriteToFile(dir);

          this->FileManager.WriteToFile("\n");
     }




     char PathSpecifier [] = "VPATH = ";
     char Ident [] =         "        ";


     char NextLine [] = " \\";

     char header_add [] = ".h";

     char object_add [] = ".o";



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);


     this->FileManager.WriteToFile("$(PROJECT_HEADERS_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);


     this->FileManager.WriteToFile("$(PROJECT_OBJECTS_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);



     for(int i=0;i<library_dir_num;i++){

         this->FileManager.WriteToFile("$(");

         std::string link_dir = this->Des_Reader.Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(link_dir_alias);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile("_PATH");

         this->FileManager.WriteToFile(")");

         this->FileManager.WriteToFile(NextLine);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(Ident);
     }



     for(size_t i=0;i<dep_header_size;i++){

          std::string header_name = this->Com_Data_ptr->at(0).dependent_headers.at(i);

          std::string dir = this->Com_Data_ptr->at(0).dependent_headers_dir.at(i);

          this->FileManager.WriteToFile("$(");

          this->FileManager.WriteToFile(header_name);

          this->FileManager.WriteToFile("_PATH");

          this->FileManager.WriteToFile(")");

          this->FileManager.WriteToFile(NextLine);

          this->FileManager.WriteToFile("\n");

          this->FileManager.WriteToFile(Ident);
     }



     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("$(");

         this->FileManager.WriteToFile(include_symbol);

         std::string included_dir = this->Des_Reader.Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile(")");

         this->FileManager.WriteToFile(NextLine);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(Ident);
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

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

         this->FileManager.WriteToFile(" \\");

         this->FileManager.WriteToFile("\n\t");     
     }

     for(size_t i=0;i<header_list_size;i++){
     
         this->FileManager.WriteToFile(header_list->at(i));

         this->FileManager.WriteToFile(" \\");

         this->FileManager.WriteToFile("\n\t");     
     }

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.FileClose();

}
