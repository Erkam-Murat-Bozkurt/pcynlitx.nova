

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

   this->Dependency_Code_Line = nullptr;

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

void Executable_MakeFile_Builder::Build_MakeFile(char * mn_src_path){

     this->Data_Collector.Collect_Make_File_Data();

     this->Dep_Determiner.Receive_Executable_MakeFile_DataCollector(&this->Data_Collector);

     this->Dep_Determiner.Determine_Dependencies();

     this->ComConstructor.Receice_DataCollector(&this->Data_Collector);

     this->ComConstructor.Receive_DepDeterminer(&this->Dep_Determiner);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);

     // Receiving the compiler data from the member objects

      this->warehouse_head_dir = this->Dep_Determiner.Get_Warehouse_Headers_Dir();

      this->warehouse_obj_dir  = this->Dep_Determiner.Get_Warehouse_Objetcs_Dir();

      this->warehouse_path     = this->Dep_Determiner.Get_Warehouse_Path();

      this->Determine_Src_File_Dir(mn_src_path,'w');

      this->Determine_Make_File_Name(mn_src_path);

      std::cout << "\n this->Make_File_Name:" << this->Make_File_Name;

      std::cout << "\n this->Src_File_Dir:" << this->Src_File_Dir;

      std::cout << "\n WAREHOUSE HEADER DIR:" << this->warehouse_head_dir;

      std::cout << "\n WAREHOUSE OBJECT DIR:" << this->warehouse_obj_dir;

      std::cout << "\n WAREHOUSE PATH      :" << this->warehouse_path;

      this->Determine_Git_Src_Dir();

      std::cout << "\n this->git_src_dir:" << this->git_src_dir;

      std::cin.get();

      this->Write_MakeFile();
}


void Executable_MakeFile_Builder::Print_Compiler_Orders(){

     /*

     int head_number = this->Dep_Determiner.Get_Compiler_Data_Size();

     for(int i=0;i<head_number;i++){

         std::cout << "\n\n";

         std::cout << "\n --------------------------------------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Data_Ptr_CString[i].header_name;

         std::cout << "\n PRIORITY:"

         <<  this->Data_Ptr_CString[i].priority;

         std::cout << "\n INCLUSION NUMBER:"

         <<  this->Data_Ptr_CString[i].inclusion_number;

         std::cout << "\n\n";
     }

     */
}


void Executable_MakeFile_Builder::Determine_Git_Src_Dir(){

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t src_dir_size = strlen(this->Src_File_Dir);

     size_t git_dr_size = src_dir_size - warehouse_path_size;

     this->git_src_dir = new char [5*git_dr_size];

     int index = 0;

     for(size_t i=warehouse_path_size+1;i<src_dir_size;i++){

        this->git_src_dir[index] = this->Src_File_Dir[i];

        index++;
     }

     this->git_src_dir[index] = '\0';
}

void Executable_MakeFile_Builder::Determine_Src_File_Dir(char * file_path, char opr_sis){

     size_t path_size = strlen(file_path);

     size_t dir_size = path_size;

     for(int i=path_size;i>0;i--){

         if(opr_sis == 'w'){

              if(file_path[i] == '\\'){

                 break;
              }
              else{

                 dir_size--;
              }
         }

         if(opr_sis == 'l'){

              if(file_path[i] == '/'){

                 break;
              }
              else{

                 dir_size--;
              }
         }
     }

     this->Src_File_Dir = new char [5*dir_size];

     int index = 0;

     for(int i=0;i<dir_size;i++){

         this->Src_File_Dir[index] = file_path[i];

         index++;
     }

     this->Src_File_Dir[index] = '\0';
}


void Executable_MakeFile_Builder::Determine_Make_File_Name(char * file_path){

     char file_ext [] = ".make";

     size_t ext_size  = strlen(file_ext);

     size_t path_size = strlen(file_path);

     size_t dir_size  = strlen(this->Src_File_Dir);

     size_t name_size = path_size - dir_size + ext_size;

     this->Make_File_Name = new char [5*name_size];


     int index = 0;

     for(size_t i=dir_size+1;i<path_size;i++){

        if(file_path[i] == '.'){

           break;
        }
        else{

            this->Make_File_Name[index] = file_path[i];

            index++;
        }
     }

     for(size_t i=0;i<ext_size;i++){

         this->Make_File_Name[index] = file_ext[i];

         index++;
     }

     this->Make_File_Name[index] ='\0';
}

void Executable_MakeFile_Builder::Write_MakeFile(){

     this->DirectoryManager.ChangeDirectory(this->Src_File_Dir);


     this->FileManager.SetFilePath(this->Make_File_Name);

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

     /*

     char * Dependency_Code_Line = this->Data_Collector.Get_Dependency_Code_Line();

     char * Compiler_System_Command= this->Data_Collector.Get_Compiler_System_Command();


     this->FileManager.WriteToFile(Dependency_Code_Line);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(Compiler_System_Command);

     */

     char * header_file_list = this->ComConstructor.Get_Header_File_List();

     char * object_file_list = this->ComConstructor.Get_Object_File_List();

     this->FileManager.WriteToFile(object_file_list);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile(header_file_list);

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();


}


void Executable_MakeFile_Builder::Determine_Dependency_Code_Line(){

     char double_quotes [] = " : ";

     char space [] = " ";

     char * header_file_list = this->ComConstructor.Get_Header_File_List();

     char * object_file_list = this->ComConstructor.Get_Object_File_List();

     size_t header_file_list_size = strlen(header_file_list);

     size_t object_file_list_size = strlen(object_file_list);

     size_t Code_Line_Size = header_file_list_size + object_file_list_size;

     this->Dependency_Code_Line =  new char [10*Code_Line_Size];

     int index_counter = 0;

     int  sizer = 0;

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     this->Place_Information(&this->Dependency_Code_Line,this->Object_File_Name,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,double_quotes,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Source_File_Name_With_Ext,&index_counter);


     this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);


     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

         this->Place_Information(&this->Dependency_Code_Line,this->Included_Header_Files[i],&index_counter);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);

            sizer = 0;
         }
     }

     this->Dependency_Code_Line[index_counter] = '\0';
}

void Executable_MakeFile_Builder::Place_Information(char ** Pointer,

     char * Information, int * index_counter){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         (*Pointer)[(*index_counter)] = Information[i];

         (*index_counter)++;
     }
 }
