
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

#include "Library_Updater.h"

Library_Updater::Library_Updater(char * DesPATH, char opr_sis):

    Des_Reader(opr_sis)
{

    this->opr_sis = opr_sis;

    this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

    this->Des_Reader.Read_Descriptor_File();

    this->Memory_Delete_Condition = false;
}



Library_Updater::~Library_Updater(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}

void Library_Updater::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(this->Object_File_List);

         this->Clear_String_Memory(this->Archive_Build_Command);

         this->Clear_String_Memory(this->warehouse_obj_dir);

         this->Clear_String_Memory(this->library_name);
     }
}


void Library_Updater::Build_Library(char * Library_Name){

     this->Clear_Dynamic_Memory();

     this->Receive_Library_Name(Library_Name);

     this->Determine_Library_File_Name();

     this->warehouse_path = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Warehouse_Object_Dir();

     this->Determine_Current_Library_Path();

     this->Determine_Target_Library_Path();

     this->Memory_Delete_Condition = false;

     DIR * d;

     struct dirent *dir;

     int list_character_size = 0;

     d = opendir(this->warehouse_obj_dir.c_str());

     if (d){

        while ((dir = readdir(d)) != NULL)
        {

            int file_name_size = strlen(dir->d_name);

            char * name = dir->d_name;

            if(((name[file_name_size-1] == 'o') && (name[file_name_size-2] == '.'))){

                list_character_size = list_character_size + file_name_size;
            }
        }

        closedir(d);
     }

     char Space_Character [] = {' ','\0'};

     int index_counter = 0;

     d = opendir(this->warehouse_obj_dir.c_str());

     if (d){

        while ((dir = readdir(d)) != NULL)
        {

            int file_name_size = strlen(dir->d_name);

            char * name = dir->d_name;

            if(((name[file_name_size-1] == 'o') && (name[file_name_size-2] == '.'))){

                this->Place_Information(this->Object_File_List,name);

                this->Place_Information(this->Object_File_List,Space_Character);
            }
        }

        this->Object_File_List[index_counter] = '\0';

        closedir(d);
     }

     char Library_Construction_Command [] = {'a','r',' ','r','s',' ','l','i','b','\0'};

     char Library_Add_word [] = {'.','a','\0'};


     this->Place_Information(this->Archive_Build_Command,Library_Construction_Command);

     this->Place_Information(this->Archive_Build_Command,Library_Name);

     this->Place_Information(this->Archive_Build_Command,Library_Add_word);

     this->Place_Information(this->Archive_Build_Command,Space_Character);

     this->Place_Information(this->Archive_Build_Command,this->Object_File_List);

     chdir(this->warehouse_obj_dir.c_str());

     size_t cmd_size = this->Archive_Build_Command.length();
    
     char * cmd = new char [5*cmd_size];

     for(size_t i=0;i<cmd_size;i++){

         cmd[i] = this->Archive_Build_Command[i];         
     }

     cmd[cmd_size] = '\0';


     this->System_Interface.System_Function(cmd);

     this->Send_Library_To_Libraries_Location();

     delete [] cmd;

     this->Clear_String_Memory(this->Archive_Build_Command);
}



void Library_Updater::Determine_Warehouse_Object_Dir(){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     char warehouse_word   [] = "WAREHOUSE";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_dir_size = strlen(object_directory);

     size_t wr_word_size    = strlen(warehouse_word);


     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_obj_dir.push_back(this->warehouse_path[i]);
     }


     this->Add_Directory_Character(this->warehouse_obj_dir);


     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir.push_back(warehouse_word[i]);
     }


    this->Add_Directory_Character(this->warehouse_obj_dir);


     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir.push_back(object_directory[i]);         
     }

     this->warehouse_obj_dir.shrink_to_fit();
}


void Library_Updater::Determine_Target_Library_Path(){

     char warehouse_word [] = "WAREHOUSE";

     char directory_folder_name [] = "PROJECT.LIBRARY.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t name_size= strlen(directory_folder_name);

     size_t wr_word_size = strlen(warehouse_word);



     for(size_t i=0;i<warehouse_path_size;i++){

         this->Target_Library_Path.push_back(this->warehouse_path[i]);
     }


     this->Add_Directory_Character(this->Target_Library_Path);



     for(size_t i=0;i<wr_word_size;i++){

        this->Target_Library_Path.push_back(warehouse_word[i]);        
     }


     this->Add_Directory_Character(this->Target_Library_Path);


     for(size_t i=0;i<name_size;i++){

         this->Target_Library_Path.push_back(directory_folder_name[i]);         
     }


     this->Add_Directory_Character(this->Target_Library_Path);


     size_t library_name_size = this->Library_File_Name.length();

     for(size_t i=0;i<library_name_size;i++){

         this->Target_Library_Path.push_back(this->Library_File_Name[i]);         
     }

     this->Target_Library_Path.shrink_to_fit();
}


void Library_Updater::Determine_Current_Library_Path(){

     char object_directory_folder_name [] = "PROJECT.OBJECT.FILES";

     char warehouse_word [] = "WAREHOUSE";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_folder_size = strlen(object_directory_folder_name);

     size_t warehouse_word_size = strlen(warehouse_word);

     size_t library_name_size = this->Library_File_Name.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->Current_Library_Path.push_back(this->warehouse_path[i]);         
     }


     this->Add_Directory_Character(this->Current_Library_Path);



     for(size_t i=0;i<warehouse_word_size;i++){

         this->Current_Library_Path.push_back(warehouse_word[i]);         
     }

     this->Add_Directory_Character(this->Current_Library_Path);


     for(size_t i=0;i<object_folder_size;i++){

         this->Current_Library_Path.push_back(object_directory_folder_name[i]);         
     }


     this->Add_Directory_Character(this->Current_Library_Path);


     for(size_t i=0;i<library_name_size;i++){

         this->Current_Library_Path.push_back(this->Library_File_Name[i]);
     } 
}



void Library_Updater::Determine_Library_File_Name(){
     
     char library_prefix [] = {'l','i','b','\0'};

     char library_subfix [] = {'.','a','\0'};


     this->Place_Information(this->Library_File_Name,library_prefix);

     this->Place_Information(this->Library_File_Name,this->library_name);

     this->Place_Information(this->Library_File_Name,library_subfix);
}


void Library_Updater::Send_Library_To_Libraries_Location(){

     char * cur_dir = nullptr;
     char * tar_dir = nullptr;

     this->Place_CString(&cur_dir,this->Current_Library_Path);

     this->Place_CString(&tar_dir,this->Target_Library_Path);

     this->FileManager.MoveFile_Win(cur_dir,tar_dir);
}

void Library_Updater::Receive_Library_Name(char * lib_name){

     size_t name_size = strlen(lib_name);

     for(size_t i=0;i<name_size;i++){

         this->library_name.push_back(lib_name[i]);
     }

     this->library_name.shrink_to_fit();
}


void Library_Updater::Add_Directory_Character(std::string & str){

     if(this->opr_sis == 'w'){

        if(str.back() != '\\'){

            str.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

         if(str.back() != '/'){

            str.push_back('/');
        }
     }
}

void Library_Updater::Place_Information(std::string & Pointer, std::string Information){

     size_t String_Size = Information.length();

     for(size_t i=0;i<String_Size;i++){
         
         Pointer.push_back(Information[i]);         
     }
}

void Library_Updater::Place_CString(char ** str, std::string s){

     size_t length = s.length();

     *str = new char [5*length];

     for(size_t i=0;i<length;i++){

         (*str)[i] = s[i];
     }

     (*str)[length] = '\0';
}


void Library_Updater::Clear_CString(char ** str){

     if(*str!= nullptr){

        delete [] (*str);

        *str = nullptr;
     }
}

void Library_Updater::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();
        
         str.shrink_to_fit();
     }
}
