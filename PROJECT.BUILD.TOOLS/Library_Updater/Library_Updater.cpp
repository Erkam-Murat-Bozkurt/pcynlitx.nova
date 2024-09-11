


/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Library_Updater.h"

Library_Updater::Library_Updater(char opr_sis, char build_type):

    Des_Reader(opr_sis,build_type)
{

    this->opr_sis = opr_sis;

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


void Library_Updater::Receive_Descriptor_File_Path(char * DesPATH){

    this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

    this->Des_Reader.Read_Descriptor_File();
}


void Library_Updater::Receive_Descriptor_File_Path(std::string DesPATH){

    this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

    this->Des_Reader.Read_Descriptor_File();
}


void Library_Updater::Build_Library(){

     this->Determine_Project_Library_Name();

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

        this->Object_File_List.shrink_to_fit();

        closedir(d);
     }

     char Library_Construction_Command [] = {'a','r',' ','r','s',' ','l','i','b','\0'};

     char Library_Add_word [] = {'.','a','\0'};


     this->Place_Information(this->Archive_Build_Command,Library_Construction_Command);

     this->Place_Information(this->Archive_Build_Command,this->library_name);

     this->Place_Information(this->Archive_Build_Command,Library_Add_word);

     this->Place_Information(this->Archive_Build_Command,Space_Character);

     this->Place_Information(this->Archive_Build_Command,this->Object_File_List);

     chdir(this->warehouse_obj_dir.c_str());

     size_t cmd_size = this->Archive_Build_Command.length();
    
     char * cmd = new char [5*cmd_size];

     int index = 0;

     for(size_t i=0;i<this->Archive_Build_Command.length();i++){

         cmd[index] = this->Archive_Build_Command[i]; 

         index++;        
     }

     cmd[index] = '\0';


     this->System_Interface.System_Function(cmd);

     this->Send_Library_To_Libraries_Location();

     delete [] cmd;

     this->Clear_String_Memory(this->Archive_Build_Command);
}



void Library_Updater::Determine_Warehouse_Object_Dir(){

     char object_directory [] = "OBJECT.FILES";

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

     char directory_folder_name [] = "LIBRARY.FILES";

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

     char object_directory_folder_name [] = "OBJECT.FILES";

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



void Library_Updater::Determine_Project_Library_Name(){

    std::string repo_dir_path = this->Des_Reader.Get_Repo_Directory_Location();

    std::string repo_dir_name;

    this->Extract_Repo_Directory_Name(repo_dir_name,repo_dir_path);

    this->library_name = repo_dir_name;     
}



void Library_Updater::Send_Library_To_Libraries_Location(){

     char * cur_dir = nullptr;
     char * tar_dir = nullptr;

     this->Place_CString(&cur_dir,this->Current_Library_Path);

     this->Place_CString(&tar_dir,this->Target_Library_Path);

     this->FileManager.MoveFile_Win(cur_dir,tar_dir);
}




void Library_Updater::Extract_Repo_Directory_Name(std::string & name, 

     std::string root_dir){

     size_t root_dir_size = root_dir.size();

     size_t start_point = root_dir_size;

     for(size_t i=root_dir_size;i>0;i--){

         if((root_dir[i] == '\\') || (root_dir[i] == '/') ){

             start_point = i+1;
             break;
         }   
     }    

     for(size_t i=start_point;i<root_dir_size;i++){

         name.push_back(tolower(root_dir[i]));
     }

     name.shrink_to_fit();
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
