

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

#include "Convert_Repo_To_Single_File.h"

Convert_Repo_To_Single_File::Convert_Repo_To_Single_File(){

     this->Memory_Delete_Condition = true;

     this->Repo_Directory_Receive_Status = false;

     this->Repo_Directory = nullptr;
}


Convert_Repo_To_Single_File::~Convert_Repo_To_Single_File(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
}

void Convert_Repo_To_Single_File::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Repo_Directory != nullptr){

            delete [] this->Repo_Directory;

            this->Repo_Directory = nullptr;
         }

         if(!this->File_List_Content.empty()){

            this->File_List_Content.clear();

            this->File_List_Content.shrink_to_fit();
         }

         this->FileManager.Clear_Dynamic_Memory();

         this->DirectoryManager.Clear_Dynamic_Memory();
     }
}

void Convert_Repo_To_Single_File::Receive_Document_Path(char * path){

     size_t path_size = strlen(path);

     for(size_t i=0;i<path_size;i++){

         this->Document_Path.push_back(path[i]);
     }

     this->Document_Path.shrink_to_fit();

     this->Doc_Builder.Receive_Document_Path(this->Document_Path);
}


void Convert_Repo_To_Single_File::Receive_Repo_Directory(char * Directory){

    if(*Directory != '\0'){

       this->Memory_Delete_Condition = false;

       this->Repo_Directory_Receive_Status = true;

       this->Place_String(&this->Repo_Directory,Directory);

       size_t repo_dir_size = strlen(Directory);

       for(size_t i=0;i<repo_dir_size;i++){

           this->repo_dir_std_str.push_back(Directory[i]);
       }

       this->repo_dir_std_str.shrink_to_fit();       
    }
    else{
           std::cout << "\n\n ERROR:";

           std::cout << "\n Inside Convert_Repo_To_Single_File class";

           std::cout << "\n A valid directory name must be entered..";

           std::cout << "\n\n";

           exit(0);
    }
}

void Convert_Repo_To_Single_File::List_Files_in_Repo(){

     char repo_list_file [] = "repo_files.txt";

     if(this->FileManager.Is_Path_Exist(repo_list_file)){

        this->FileManager.Delete_File(repo_list_file);
     }

     char Listing_Command [] = "powershell git ls-files \'*.cpp\' \'*.h\' \'*.hpp\' \'*.ps1\' \'*.txt\' > repo_files.txt";

     this->DirectoryManager.ChangeDirectory(this->Repo_Directory);

     int system_return_value = system(Listing_Command);

     if(system_return_value == -1){

         std::cout << "\n git repo file list can not be printed ..";

         exit(0);
     }
}


void Convert_Repo_To_Single_File::Read_File(){

     char Repo_File_List [] = "repo_files.txt";

     this->FileManager.SetFilePath(Repo_File_List);

     this->FileManager.FileOpen(Rf);

     do {

          std::string str_line = this->repo_dir_std_str + '\\' + this->FileManager.ReadLine();

          for(size_t i=0;i<str_line.length();i++){

               if(str_line[i] == '/'){

                  str_line[i] = '\\';
               }
          }

          this->File_List_Content.push_back(str_line);

     }while(!this->FileManager.Control_Stop_Condition());

     this->File_List_Content.shrink_to_fit();

     this->FileManager.FileClose();
}

void Convert_Repo_To_Single_File::Construct_Source_File(){

     if(this->Repo_Directory_Receive_Status){

        this->List_Files_in_Repo();

        this->Read_File();

        for(int i=0;i<this->File_List_Content.size()-1;i++){

            this->Doc_Builder.Receive_File_Path(this->File_List_Content[i]);

            this->Doc_Builder.Add_File_To_Document();
        }
     }
}


void Convert_Repo_To_Single_File::Place_String(char ** Pointer, char * String){

     int String_Size = strlen(String);

     *Pointer = new char [10*String_Size];

     for(int i=0;i<String_Size;i++){

        (*Pointer)[i] = String[i];
     }

     (*Pointer)[String_Size] = '\0';
}
