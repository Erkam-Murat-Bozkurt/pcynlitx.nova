

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

Executable_MakeFile_Builder::Executable_MakeFile_Builder(){

   this->Memory_Delete_Condition = false;

   this->object_file_list = nullptr;

   this->header_file_list = nullptr;

   this->Src_File_Dir = nullptr;

   this->git_src_dir = nullptr;

   this->Compiler_System_Command = nullptr;
}

Executable_MakeFile_Builder::Executable_MakeFile_Builder(const

     Executable_MakeFile_Builder & orig){

}

Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Data_Collector.Clear_Dynamic_Memory();

        this->Dep_Determiner.Clear_Dynamic_Memory();

        this->ComConstructor.Clear_Dynamic_Memory();
     }
}

void Executable_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Des_Reader_Pointer = Des_Reader;

     this->Data_Collector.Receive_Descriptor_File_Reader(Des_Reader);
}

void Executable_MakeFile_Builder::Receive_Git_Record_Data(Git_File_List_Receiver * Pointer){

     this->Data_Collector.Receive_Git_Record_Data(Pointer);
}

void Executable_MakeFile_Builder::Receive_Source_File_Info(Project_Files_Lister * Pointer){

     this->Data_Collector.Receive_Source_File_Info(Pointer);
}

void Executable_MakeFile_Builder::Build_MakeFile(char * mn_src_path, char * Exe_Name){

     this->Data_Collector.Collect_Make_File_Data();

     this->Dep_Determiner.Receive_Executable_MakeFile_DataCollector(&this->Data_Collector);

     this->Dep_Determiner.Determine_Dependencies();

     this->ComConstructor.Receice_DataCollector(&this->Data_Collector);

     this->ComConstructor.Receive_DepDeterminer(&this->Dep_Determiner);

     this->ComConstructor.Receive_Descriptor_File_Reader(this->Des_Reader_Pointer);

     this->ComConstructor.Receive_ExeFileName(Exe_Name);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);

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


void Executable_MakeFile_Builder::Print_Compiler_Orders(){

}

void Executable_MakeFile_Builder::Write_MakeFile(char * Exe_Name){

     this->DirectoryManager.ChangeDirectory(this->Src_File_Dir);

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


     if(strlen(this->Src_File_Dir) != 0){

        this->FileManager.WriteToFile("\\");

        this->FileManager.WriteToFile(this->git_src_dir);
     }

     int included_dir_num = this->Des_Reader_Pointer->Get_Include_Directory_Number();

     char include_symbol [] = "EXTERNAL_INCLUDE_DIR_";

     char underscore [] = "_";

     this->FileManager.WriteToFile("\n");

     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         char * included_dir = this->Des_Reader_Pointer->Get_Include_Directories()[i];

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

         char * included_dir = this->Des_Reader_Pointer->Get_Include_Directories()[i];

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



     char * header_file_list = this->ComConstructor.Get_Header_File_List();

     char * object_file_list = this->ComConstructor.Get_Object_File_List();


     this->FileManager.WriteToFile(object_file_list);

     this->FileManager.WriteToFile(header_file_list);

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.FileClose();
}
