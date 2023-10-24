

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

   Des_Reader(opr_sis), Git_Data_Proc(opr_sis), Dep_Determiner(des_path,opr_sis), 
   
   ComConstructor(opr_sis), Script_Builder(opr_sis), Project_Rebuild_Script_Writer(opr_sis)   
{
     this->opr_sis = opr_sis;

     this->Des_Reader.Receive_Descriptor_File_Path(des_path);

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\nProject descriptions received";

     this->Git_Data_Proc.Receive_Descriptor_File_Path(des_path);

     this->Git_Data_Proc.Write_Git_Repo_List_File();

     this->Git_Data_Proc.Determine_Git_Repo_Info();

     std::cout << "\nGit version control data collected";
}


Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

       this->Clear_Dynamic_Memory();
   
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     this->Dep_Determiner.Clear_Dynamic_Memory();

     this->ComConstructor.Clear_Dynamic_Memory();

     this->Script_Builder.Clear_Dynamic_Memory();
}


void Executable_MakeFile_Builder::Build_MakeFile(char * mn_src_path, 

     char * Exe_Name, char strategy){

     if(strategy == 'a'){

        this->Advanced_MakeFile_Construction(mn_src_path,Exe_Name,strategy);
     }
     else{

          if(strategy == 's'){

             this->Simple_MakeFile_Construction(mn_src_path,Exe_Name,strategy);
          }
          else{

                std::cout << "\nThe build strategy must be one of the following characters:";
                std::cout << "\n";
                std::cout << "\na: Advanced build";
                std::cout << "\ns: Simple build";
                std::cout << "\n\n";

                exit(0);
          }
     }   
}



void Executable_MakeFile_Builder::Advanced_MakeFile_Construction(char * mn_src_path, char * Exe_Name, char strategy){

     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Dep_Determiner.Collect_Dependency_Information(mn_src_path);


     this->warehouse_obj_dir  = this->Dep_Determiner.Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner.Get_Warehouse_Path();

     
     std::cout << "\nThe source file dependencies determined";


     this->Receive_Exe_File_Name(Exe_Name);

     this->Determine_New_Directory_Path();

     this->Construct_New_Directory_For_Build_Files();



     this->Script_Builder.Receive_File_System_Path(mn_src_path);

     this->Script_Builder.Receive_Exe_File_Name(Exe_Name);

     this->Script_Builder.Receive_Construction_Directory_Path(this->new_dir_path);

     this->Script_Builder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Script_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Builder.Build_Compiler_Script_For_Executable_File(mn_src_path);

     std::cout << "\nThe construction script writed";


     this->Com_Data_ptr = this->Dep_Determiner.Get_Compiler_Data_Address();

     this->ComConstructor.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->ComConstructor.Receive_Dependency_Determiner(&this->Dep_Determiner);

     this->ComConstructor.Receive_ExeFileName(Exe_Name);

     this->ComConstructor.Receive_Construction_Strategy(strategy);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);



     this->source_file_name = this->Script_Builder.Get_Src_File_Name();

     // Receiving the compiler data from the member objects


     this->Src_File_Dir       = this->ComConstructor.Get_Src_File_Dr();

     this->git_src_dir        = this->ComConstructor.Get_Git_Src_Dr();

     this->make_file_name     = this->ComConstructor.Get_Make_File_Name();

     this->Compiler_System_Command = this->ComConstructor.Get_Compiler_System_Command();

     this->Write_MakeFile(Exe_Name);

}


void Executable_MakeFile_Builder::Simple_MakeFile_Construction(char * mn_src_path, char * Exe_Name, char strategy){

     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Dep_Determiner.Collect_Dependency_Information();

    


     this->warehouse_obj_dir  = this->Dep_Determiner.Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner.Get_Warehouse_Path();

     

     this->Receive_Exe_File_Name(Exe_Name);

     this->Determine_New_Directory_Path();

     this->Construct_New_Directory_For_Build_Files();



     this->Project_Rebuild_Script_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Project_Rebuild_Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);


     

     std::string script_name;

     this->Script_Name_Determination(script_name,mn_src_path);


     this->Project_Rebuild_Script_Writer.Set_Script_Path(this->new_dir_path,script_name);
     
     this->Project_Rebuild_Script_Writer.Build_Update_Script();

     this->Project_Rebuild_Script_Writer.Clear_Dynamic_Memory();

     std::cout << "\nThe project compiler script has been constructed";


     this->Dep_Determiner.Clear_Dynamic_Memory();

     this->Dep_Determiner.Simple_Dependency_Determination_For_Single_Source_File(mn_src_path);

     this->Simple_Data_Ptr = this->Dep_Determiner.Get_Simple_File_Dependencies();


     this->ComConstructor.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->ComConstructor.Receive_Dependency_Determiner(&this->Dep_Determiner);

     this->ComConstructor.Receive_ExeFileName(Exe_Name);

     this->ComConstructor.Receive_Construction_Strategy(strategy);

     this->ComConstructor.Construct_Compiler_Commands(mn_src_path);


     this->source_file_name = this->Simple_Data_Ptr->source_file_name;


     this->Src_File_Dir       = this->ComConstructor.Get_Src_File_Dr();

     this->git_src_dir        = this->ComConstructor.Get_Git_Src_Dr();

     this->make_file_name     = this->ComConstructor.Get_Make_File_Name();

     this->Compiler_System_Command = this->ComConstructor.Get_Compiler_System_Command();

     this->Write_MakeFile_For_Simple_Construction(Exe_Name);
      
}



void Executable_MakeFile_Builder::Write_MakeFile(char * Exe_Name){

     this->DirectoryManager.ChangeDirectory(this->new_dir_path.c_str());

     this->FileManager.SetFilePath(this->make_file_name);

     this->FileManager.FileOpen(RWCf);


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_obj_dir);


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");


     std::string library_directory = "PROJECT_LIBRARY_LOCATION=";

     library_directory += this->warehouse_path; 

     if(this->opr_sis == 'w'){

        library_directory.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        library_directory.push_back('/');
     }

     library_directory += "WAREHOUSE";

     if(this->opr_sis == 'w'){

        library_directory.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        library_directory.push_back('/');
     }

     library_directory += "LIBRARY.FILES";


     this->FileManager.WriteToFile(library_directory);



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


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");
     
     this->FileManager.WriteToFile("TARGET_LOCATION=");


     if(!this->new_dir_path.empty()){

         this->FileManager.WriteToFile(this->new_dir_path);
     }

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

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

     char object_add [] = ".o";



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);


     this->FileManager.WriteToFile("$(PROJECT_OBJECTS_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);


    this->FileManager.WriteToFile("$(PROJECT_LIBRARY_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);


     this->FileManager.WriteToFile("$(SOURCE_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);

     
     this->FileManager.WriteToFile("$(TARGET_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);

     

     for(int i=0;i<library_dir_num;i++){

         this->FileManager.WriteToFile("$(");

         std::string link_dir = this->Des_Reader.Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(link_dir_alias);

         this->FileManager.WriteToFile(dir_index);

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

     this->FileManager.WriteToFile("$(TARGET_LOCATION)");

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(Exe_Name);

     this->FileManager.WriteToFile(": ");


     this->FileManager.WriteToFile(this->source_file_name);

     this->FileManager.WriteToFile(" \\");

     this->FileManager.WriteToFile("\n\t");     



     std::vector<std::string> * object_list = this->ComConstructor.Get_Object_File_List();

     std::vector<std::string> * header_list = this->ComConstructor.Get_Header_File_List();

     object_list->shrink_to_fit();

     header_list->shrink_to_fit();

     size_t object_list_size = object_list->size();

     size_t header_list_size = header_list->size();

     for(size_t i=1;i<object_list_size;i++){
     
         this->FileManager.WriteToFile(object_list->at(i));

         this->FileManager.WriteToFile(" \\");

         this->FileManager.WriteToFile("\n\t");     
     }

     for(size_t i=0;i<header_list_size;i++){
     
         this->FileManager.WriteToFile(header_list->at(i));

         this->FileManager.WriteToFile(" \\");

         this->FileManager.WriteToFile("\n\t");     
     }

    this->project_library_name =  this->ComConstructor.Get_Project_Library_Name();


     this->FileManager.WriteToFile("lib");

     this->FileManager.WriteToFile(this->project_library_name);

     this->FileManager.WriteToFile(".a");

     this->FileManager.WriteToFile(" \\");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.FileClose();

}


void Executable_MakeFile_Builder::Script_Name_Determination(std::string & name, char * src_file_path){

     size_t src_name_size = strlen(src_file_path);

     size_t start_point = 0;

     for(size_t i=src_name_size;i>0;i--){

         if((src_file_path[i] == '\\') || (src_file_path[i] == '/')){

             start_point = i+1;

             break;
         }
     }

     size_t end_point = src_name_size;

     for(size_t i=src_name_size;i>0;i--){

         if(src_file_path[i] == '.'){

             end_point = i;

             break;
         }
     }


     std::string script_add = "_Build.ps1";

     for(size_t i=start_point;i<end_point;i++){

         name.push_back(src_file_path[i]);
     }

     for(size_t i=0;i<script_add.length();i++){

         name.push_back(script_add[i]);
     }

     name.shrink_to_fit();
}

void Executable_MakeFile_Builder::Write_MakeFile_For_Simple_Construction(char * Exe_Name){


     this->DirectoryManager.ChangeDirectory(this->new_dir_path.c_str());

     this->FileManager.SetFilePath(this->make_file_name);

     this->FileManager.FileOpen(RWCf);



     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_obj_dir);



     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");


     std::string library_directory = "PROJECT_LIBRARY_LOCATION=";

     library_directory += this->warehouse_path; 

     if(this->opr_sis == 'w'){

        library_directory.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        library_directory.push_back('/');
     }

     library_directory += "WAREHOUSE";

     if(this->opr_sis == 'w'){

        library_directory.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        library_directory.push_back('/');
     }

     library_directory += "LIBRARY.FILES";


     this->FileManager.WriteToFile(library_directory);




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


     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");
     
     this->FileManager.WriteToFile("TARGET_LOCATION=");


     if(!this->new_dir_path.empty()){

         this->FileManager.WriteToFile(this->new_dir_path);
     }

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");

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

     

     size_t dep_header_size = this->Simple_Data_Ptr->Dependent_Header_Names.size();

     for(size_t i=0;i<dep_header_size;i++){

          std::string header_name = this->Simple_Data_Ptr->Dependent_Header_Names.at(i);

          std::string dir = this->Simple_Data_Ptr->Dependent_Header_Directories.at(i);

          this->FileManager.WriteToFile(header_name);

          this->FileManager.WriteToFile("_PATH=");

          this->FileManager.WriteToFile(dir);

          this->FileManager.WriteToFile("\n");
     }




     char PathSpecifier [] = "VPATH = ";
     char Ident [] =         "        ";


     char NextLine [] = " \\";




     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);


     this->FileManager.WriteToFile("$(PROJECT_OBJECTS_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);


     this->FileManager.WriteToFile("$(PROJECT_LIBRARY_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);



     this->FileManager.WriteToFile("$(SOURCE_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);

     
     this->FileManager.WriteToFile("$(TARGET_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);

     

     for(int i=0;i<library_dir_num;i++){

         this->FileManager.WriteToFile("$(");

         std::string link_dir = this->Des_Reader.Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(link_dir_alias);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile(")");

         this->FileManager.WriteToFile(NextLine);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(Ident);
     }



     for(size_t i=0;i<dep_header_size;i++){

          std::string header_name = this->Simple_Data_Ptr->Dependent_Header_Names.at(i);

          std::string dir = this->Simple_Data_Ptr->Dependent_Header_Directories.at(i);

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

     this->FileManager.WriteToFile("$(TARGET_LOCATION)");

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(Exe_Name);

     this->FileManager.WriteToFile(": ");


     this->FileManager.WriteToFile(this->source_file_name);

     this->FileManager.WriteToFile(" \\");

     this->FileManager.WriteToFile("\n\t");     



     std::vector<std::string> * header_list = this->ComConstructor.Get_Header_File_List();

     header_list->shrink_to_fit();


     size_t header_list_size = header_list->size();

     for(size_t i=0;i<header_list_size;i++){
     
         this->FileManager.WriteToFile(header_list->at(i));

         this->FileManager.WriteToFile(" \\");

         this->FileManager.WriteToFile("\n\t");     
     }

     this->project_library_name =  this->ComConstructor.Get_Project_Library_Name();


     this->FileManager.WriteToFile("lib");

     this->FileManager.WriteToFile(this->project_library_name);

     this->FileManager.WriteToFile(".a");

     this->FileManager.WriteToFile(" \\");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\t");


     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.FileClose();

}





void Executable_MakeFile_Builder::Determine_New_Directory_Path(){

     std::string warehouse_word  ="WAREHOUSE";

     this->new_dir_path = this->warehouse_path;

     if(this->opr_sis == 'w'){

        if(this->new_dir_path.back()!='\\'){

            this->new_dir_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->new_dir_path.back()!='/'){

            this->new_dir_path.push_back('/');
        }
     }


     for(size_t i=0;i<warehouse_word.length();i++){

         this->new_dir_path.push_back(warehouse_word[i]);
     }



     if(this->opr_sis == 'w'){

        if(this->new_dir_path.back()!='\\'){

            this->new_dir_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->new_dir_path.back()!='/'){

            this->new_dir_path.push_back('/');
        }
     }



     size_t name_size = this->Exe_File_Name.length();

     for(size_t i=0;i<name_size;i++){
 
         char upper_case = toupper(this->Exe_File_Name[i]);

         if(upper_case == '.'){

            upper_case = '_';
         }

         this->new_dir_path.push_back(upper_case);
     }

     std::string dir_add_word = "_BUILDER";

     for(size_t i=0;i<dir_add_word.length();i++){

         this->new_dir_path.push_back(dir_add_word[i]);
     }
}


void Executable_MakeFile_Builder::Receive_Exe_File_Name(char * Exe_Name){

    size_t name_size = strlen(Exe_Name);

    for(size_t i=0;i<name_size;i++){

        this->Exe_File_Name.push_back(Exe_Name[i]);
    }

    this->Exe_File_Name.shrink_to_fit();
}


void Executable_MakeFile_Builder::Construct_New_Directory_For_Build_Files(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->new_dir_path.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->new_dir_path.c_str());

        if(const_cond == 0){

           std::cout << "\n The new directory for executable ";
           
           std::cout <<   this->Exe_File_Name;
           
           std::cout << " can not be constructed on:";

           std::cout << "\n";

           std::cout << this->new_dir_path;

           exit(0);
        }
     }
}