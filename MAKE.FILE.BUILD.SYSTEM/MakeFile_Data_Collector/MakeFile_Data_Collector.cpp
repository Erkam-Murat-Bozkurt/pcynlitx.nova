

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

#include "MakeFile_Data_Collector.hpp"

MakeFile_Data_Collector::MakeFile_Data_Collector(char * Des_Path, char opr_sis) :

File_Lister(Des_Path,opr_sis), Des_Reader(Des_Path)

{
     this->Des_Reader.Read_Descriptor_File();

     this->File_Lister.Determine_Git_Repo_Info();

     this->warehouse_path = this->Des_Reader.Get_Warehouse_Location();

     this->repo_dir  = this->Des_Reader.Get_Repo_Directory_Location();

     this->opr_sis = opr_sis;
     
     this->Included_Header_Files_Number = 0;
}


MakeFile_Data_Collector::~MakeFile_Data_Collector(){

     this->Clear_Dynamic_Memory();
   
}

void MakeFile_Data_Collector::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Des_Reader.Clear_Dynamic_Memory();

     this->File_Lister.Clear_Dynamic_Memory();
}

void MakeFile_Data_Collector::Clear_Dynamic_Memory(){

     this->Clear_Vector_Memory(&this->Included_Header_Files);

     this->Clear_Vector_Memory(&this->Included_Header_Directories);

     this->Clear_Vector_Memory(&this->Included_Header_Files_System_Paths);

     this->Clear_Vector_Memory(&this->Included_Header_Files_Git_Record_Paths);

     this->Clear_Vector_Memory(&this->Included_Header_Files_Git_Record_Dir);

     this->Clear_String_Memory(&this->Source_File_Name_With_Ext);

     this->Clear_String_Memory(&this->Object_File_Name);

     this->Clear_String_Memory(&this->Compiler_System_Command);

     this->Clear_String_Memory(&this->Dependency_Code_Line);

     this->Clear_String_Memory(&this->Make_File_Name);

     this->Clear_String_Memory(&this->warehouse_head_dir);

     this->Clear_String_Memory(&this->warehouse_obj_dir);

     this->Clear_String_Memory(&this->Header_File_Exact_Path);
}


void MakeFile_Data_Collector::Collect_Make_File_Data(int git_index){

     this->Clear_Dynamic_Memory();

     this->Determine_Warehouse_Header_Dir();

     this->Determine_Warehouse_Object_Dir();

     this->Receive_Git_Record_Data(git_index);

     this->Collect_Header_Files_Information();

     this->Determine_Compiler_System_Command();

     this->Find_Object_File_Name();

     this->Determine_Dependency_Code_Line();

     this->Determine_Make_File_Name();
}

void MakeFile_Data_Collector::Determine_Warehouse_Header_Dir(){

     std::string warehouse_word = "WAREHOUSE";

     std::string header_directory= "PROJECT.HEADER.FILES";

     size_t wrd_path_size = this->warehouse_path.length();

     size_t head_dir_size = header_directory.length();

     size_t wr_word_size  = warehouse_word.length();


     for(size_t i=0;i<wrd_path_size;i++){

        this->warehouse_head_dir.push_back(this->warehouse_path[i]);        
     }

     if(this->opr_sis == 'w'){

        if(this->warehouse_head_dir.back()!='\\'){

           this->warehouse_head_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_head_dir.back()!='/'){

           this->warehouse_head_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_head_dir.push_back(warehouse_word[i]);
     }


     if(this->opr_sis == 'w'){

        if(this->warehouse_head_dir.back() != '\\'){

           this->warehouse_head_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_head_dir.back() != '/'){

           this->warehouse_head_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir.push_back(header_directory[i]);
     }
}



void MakeFile_Data_Collector::Determine_Warehouse_Object_Dir(){

     std::string object_directory = "PROJECT.OBJECT.FILES";

     std::string warehouse_word = "WAREHOUSE";

     size_t wrd_path_size = this->warehouse_path.length();

     size_t object_dir_size = object_directory.length();

     size_t wr_word_size  = warehouse_word.length();

     for(size_t i=0;i<wrd_path_size;i++){

         this->warehouse_obj_dir.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis== 'w'){

        if(this->warehouse_obj_dir.back() != '\\'){

           this->warehouse_obj_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_obj_dir.back() != '/'){

           this->warehouse_obj_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir.push_back(warehouse_word[i]);
     }


     if(this->opr_sis == 'w'){

        if(this->warehouse_obj_dir.back() != '\\'){

           this->warehouse_obj_dir.push_back('\\');           
        }
     }

     if(this->opr_sis == 'l'){

        if(this->warehouse_obj_dir.back() != '/'){

           this->warehouse_obj_dir.push_back('/');           
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir.push_back(object_directory[i]);         
     }
}


void MakeFile_Data_Collector::Receive_Git_Record_Data(int git_index){

     this->Git_Record_Index = git_index;

     this->Source_File_Name

     = this->File_Lister.Get_Source_File_Name(git_index);


     this->Source_File_Name_With_Ext

     = this->File_Lister.Get_Source_File_Name_With_Ext(git_index);



     this->Source_File_Git_Recort_Path

     = this->File_Lister.Get_Source_File_Git_Record_Path(git_index);



     this->Source_File_Directory

     = this->File_Lister.Get_Source_File_Directory(git_index);


     this->Header_File_Directory

     = this->File_Lister.Get_Source_File_Directory(git_index);

}



void MakeFile_Data_Collector::Collect_Header_Files_Information(){

     this->Receive_Included_Header_Files_Number();

     this->Receive_Header_Files_Data();
}

void MakeFile_Data_Collector::Receive_Included_Header_Files_Number(){

    this->Included_Header_Files_Number

    = this->File_Lister.Get_Source_File_Include_File_Number(this->Git_Record_Index);
}


void MakeFile_Data_Collector::Receive_Header_Files_Data(){

     this->Receive_Source_File_Header_Directory();

     this->Receive_Source_File_Header_System_Path();

     this->Receive_Source_File_Header_Git_Record_Path();

     this->Receive_Header_File_Name();
}

void MakeFile_Data_Collector::Receive_Source_File_Header_Directory(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         std::string dir = this->File_Lister.Get_Source_File_Header_Directory(this->Git_Record_Index,i);

         this->Included_Header_Directories.push_back(dir);
     }
}

void MakeFile_Data_Collector::Receive_Source_File_Header_System_Path(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         std::string path = this->File_Lister.Get_Source_File_Header_System_Path(this->Git_Record_Index,i);

         this->Included_Header_Files_System_Paths.push_back(path);
     }
}

void MakeFile_Data_Collector::Receive_Source_File_Header_Git_Record_Path(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         std::string path = this->File_Lister.Get_Source_File_Header_Git_Record_Path(this->Git_Record_Index,i);

         this->Included_Header_Files_Git_Record_Paths.push_back(path);              
     }
}


void MakeFile_Data_Collector::Receive_Source_File_Header_Git_Record_Dir(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         std::string  dir = this->File_Lister.Get_Source_File_Header_Git_Record_Dir(this->Git_Record_Index,i);

         this->Place_String(&(this->Included_Header_Files_Git_Record_Dir[i]),dir);
     }
}

void MakeFile_Data_Collector::Receive_Header_File_Name(){

     int header_num = this->Included_Header_Files_Number;

     for(int i=0;i<header_num;i++){

         std::string name = this->File_Lister.Get_Source_File_Header(this->Git_Record_Index,i);

         this->Included_Header_Files.push_back(name);         
     }
}

void MakeFile_Data_Collector::Find_Object_File_Name(){

     size_t Source_File_Name_Size = this->Source_File_Name.length();

     // The source file name witout extantion

     for(int i=0;i<Source_File_Name_Size;i++){

         this->Object_File_Name.push_back( this->Source_File_Name[i]);
     }

     this->Object_File_Name.push_back('.');

     this->Object_File_Name.push_back('o');
}

void MakeFile_Data_Collector::Determine_Make_File_Name(){

     std::string make_file_extention = ".make";

     size_t class_name_size = this->Source_File_Name.length();

     size_t extention_size = make_file_extention.length();

     for(size_t i=0;i<class_name_size;i++){

         this->Make_File_Name.push_back(this->Source_File_Name[i]);         
     }

     for(size_t i=0;i<extention_size;i++){

         this->Make_File_Name.push_back(make_file_extention[i]);         
     }
}

void MakeFile_Data_Collector::Determine_Compiler_System_Command(){

     std::string compiler_input_command = "g++ -Wall -c -std=c++17";


     std::string options = this->Des_Reader.Get_Options();

     std::string Include_Character = "-I";

     std::string include_word = "-include";

     std::string Headers_Location ="$(PROJECT_HEADERS_LOCATION)";

     std::string Source_Location  ="$(SOURCE_LOCATION)";

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();


     std::string Space_Character = " ";

     std::string go_to_new_line = "\\\n\t";

     char slash_w [] = "\\";

     char slash_l [] = "/";

     this->Place_String(&this->Compiler_System_Command,compiler_input_command);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);

     if(!options.empty()){

        this->Place_String(&this->Compiler_System_Command,options);

        this->Place_String(&this->Compiler_System_Command,go_to_new_line);
     }
     


     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     this->Place_String(&this->Compiler_System_Command,Include_Character);

     this->Place_String(&this->Compiler_System_Command,Headers_Location);

     this->Place_String(&this->Compiler_System_Command,Space_Character);

     this->Place_String(&this->Compiler_System_Command,Include_Character);

     this->Place_String(&this->Compiler_System_Command,Source_Location);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);




     int  included_dir_num = this->Des_Reader.Get_Include_Directory_Number();

     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         std::string included_dir = this->Des_Reader.Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->Place_String(&this->Compiler_System_Command,Include_Character);

         this->Place_String(&this->Compiler_System_Command,include_dir_symbol);

         this->Place_CString(&this->Compiler_System_Command,dir_index);

         this->Place_CString(&this->Compiler_System_Command,makro_end);

         this->Place_String(&this->Compiler_System_Command,Space_Character);

         this->Place_String(&this->Compiler_System_Command,go_to_new_line);
     }

     this->Place_String(&this->Compiler_System_Command,Source_Location);

     if(this->opr_sis == 'w'){
     
        this->Place_String(&this->Compiler_System_Command,slash_w);
     }
     else{
     
         if(this->opr_sis =='l'){
         
           this->Place_String(&this->Compiler_System_Command,slash_l);
         }
     }


     this->Place_String(&this->Compiler_System_Command,this->Source_File_Name_With_Ext);


     this->Place_String(&this->Compiler_System_Command,Space_Character);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);


     // The include commands definition

     sizer = 0;

     size_t included_hdr_num = this->Included_Header_Files.size();

     for(int i=0;i<included_hdr_num;i++){

         this->Place_String(&this->Compiler_System_Command,include_word);

         this->Place_String(&this->Compiler_System_Command,Space_Character);

         this->Place_String(&this->Compiler_System_Command,this->Included_Header_Files[i]);

         this->Place_String(&this->Compiler_System_Command,Space_Character);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_String(&this->Compiler_System_Command,Space_Character);

            this->Place_String(&this->Compiler_System_Command,go_to_new_line);

            sizer = 0;
          }
     }
}


void MakeFile_Data_Collector::Determine_Dependency_Code_Line(){

     char double_quotes [] = " : ";

     size_t Object_File_Name_Size = this->Object_File_Name.length();

     size_t Header_File_Name_Size = this->Source_File_Name_With_Ext.length();

     size_t Source_File_Name_Size = this->Source_File_Name_With_Ext.length();


     int  sizer = 0;

     std::string Space_Character = " ";

     std::string go_to_new_line = "\\\n\t";

     this->Place_String(&this->Dependency_Code_Line,this->Object_File_Name);

     this->Place_String(&this->Dependency_Code_Line,double_quotes);

     this->Place_String(&this->Dependency_Code_Line,this->Source_File_Name_With_Ext);


     this->Place_String(&this->Dependency_Code_Line,Space_Character);

     this->Place_String(&this->Dependency_Code_Line,go_to_new_line);


     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_String(&this->Dependency_Code_Line,Space_Character);

         this->Place_String(&this->Dependency_Code_Line,this->Included_Header_Files[i]);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_String(&this->Dependency_Code_Line,Space_Character);
            
            this->Place_String(&this->Dependency_Code_Line,go_to_new_line);

            sizer = 0;
         }
     }
}

void MakeFile_Data_Collector::Place_String(std::string * pointer,

     std::string Information){

     int String_Size = Information.length();

     for(int i=0;i<String_Size;i++){

         pointer->push_back(Information[i]);
     }
}

void MakeFile_Data_Collector::Place_CString(std::string * pointer, 

     char * string){

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         pointer->push_back(string[i]);
     }
}

void MakeFile_Data_Collector::Clear_Vector_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();
            it->shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void MakeFile_Data_Collector::Clear_String_Memory(std::string * ptr)
{
     if(!ptr->empty()){

         ptr->clear();

         ptr->shrink_to_fit();
     }
}

std::string MakeFile_Data_Collector::Get_Source_File_Name(){

     return this->Source_File_Name;
}

std::string MakeFile_Data_Collector::Get_Make_File_Name(){

     return this->Make_File_Name;
}

std::string MakeFile_Data_Collector::Get_Compiler_System_Command(){

     return this->Compiler_System_Command;
}

std::string MakeFile_Data_Collector::Get_Dependency_Code_Line(){

     return this->Dependency_Code_Line;
}

std::string MakeFile_Data_Collector::Get_Object_File_Name(){

     return this->Object_File_Name;
}

std::string MakeFile_Data_Collector::Get_Source_File_Name_With_Extention(){

     return this->Source_File_Name_With_Ext;
}

std::vector<std::string> MakeFile_Data_Collector::Get_Included_Header_Files(){

     return this->Included_Header_Files;
}

std::string MakeFile_Data_Collector::Get_Repo_Dir(){

     return this->repo_dir;
}

std::string MakeFile_Data_Collector::Get_Warehouse_Header_Dir(){

     return this->warehouse_head_dir;
}

std::string MakeFile_Data_Collector::Get_Warehouse_Object_Dir(){

     return this->warehouse_obj_dir;
}

std::string MakeFile_Data_Collector::Get_Warehouse_Path(){

     return this->warehouse_path;
}

std::string MakeFile_Data_Collector::Get_System_Header_File_Dir(){

     return this->Header_File_Directory;
}

 int MakeFile_Data_Collector::Get_Included_Header_Files_Number(){

     return this->Included_Header_Files_Number;
 }
