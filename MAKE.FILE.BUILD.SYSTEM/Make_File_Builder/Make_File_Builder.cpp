
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

Make_File_Builder::Make_File_Builder(){

   this->Memory_Delete_Condition = false;

}

Make_File_Builder::Make_File_Builder(const Make_File_Builder & orig){

}

Make_File_Builder::~Make_File_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Make_File_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Data_Collector.Clear_Dynamic_Memory();
     }
}

void Make_File_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Des_Reader_Pointer = Des_Reader;
}

void Make_File_Builder::Receive_Git_Record_Data(Project_Files_Lister * Lister_Pointer){

     this->File_Lister_Pointer = Lister_Pointer;
}

void Make_File_Builder::Build_MakeFile(int git_index){

     this->Data_Collector.Receive_Descriptor_File_Reader(this->Des_Reader_Pointer);


     /*

     this->Data_Collector.Receive_Git_Record_Data(this->File_Lister_Pointer,git_index);


     std::cout << "\n --3";

     std::cin.get();

     */


     this->Data_Collector.Collect_Make_File_Data(this->File_Lister_Pointer,git_index);

     char * Header_File_Directory = this->Data_Collector.Get_System_Header_File_Dir();

     this->DirectoryManager.ChangeDirectory(Header_File_Directory);

     char * Make_File_Name = this->Data_Collector.Get_Make_File_Name();

     this->FileManager.SetFilePath(Make_File_Name);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_HEADERS_LOCATION=");

     char * warehouse_head_dir = this->Data_Collector.Get_Warehouse_Header_Dir();

     this->FileManager.WriteToFile(warehouse_head_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");


     char * warehouse_obj_dir = this->Data_Collector.Get_Warehouse_Object_Dir();

     this->FileManager.WriteToFile(warehouse_obj_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("REPO_DIRECTORY=");

     char * project_repo_dir = this->Data_Collector.Get_Repo_Dir();

     this->FileManager.WriteToFile(project_repo_dir);

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=$(REPO_DIRECTORY)");

     char * source_file_dir =

     this->File_Lister_Pointer->Get_Source_File_Git_Record_Directory(git_index);



     if(strlen(source_file_dir) != 0){

        this->FileManager.WriteToFile("\\");

        this->FileManager.WriteToFile(source_file_dir);
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

     char * Dependency_Code_Line = this->Data_Collector.Get_Dependency_Code_Line();

     char * Compiler_System_Command= this->Data_Collector.Get_Compiler_System_Command();


     this->FileManager.WriteToFile(Dependency_Code_Line);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(Compiler_System_Command);

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}
