
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

#include "Document_Builder.h"

Document_Builder::Document_Builder(){

     this->Memory_Delete_Condition = true;

     this->File_Path_Receive_Status = false;

     this->Document_Name_Receive_Status = false;

     this->File_Number = 1;
}

Document_Builder::~Document_Builder(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
}

void Document_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->FileManager.Clear_Dynamic_Memory();

         if(!this->File_Content.empty()){
            
            this->File_Content.clear();

            this->File_Content.shrink_to_fit();
         }

         if(!this->Document_Name.empty()){
            
            this->Document_Name.clear();

            this->Document_Name.shrink_to_fit();
         }

         if(!this->FilePath.empty()){
            
            this->FilePath.clear();

            this->FilePath.shrink_to_fit();
         }
     }
}

void Document_Builder::Receive_File_Path(std::string path){

    if(!path.empty()){

       this->Memory_Delete_Condition = false;

       this->File_Path_Receive_Status = true;

       this->Clear_Std_String(this->FilePath);

       size_t path_size = path.size();

       for(size_t i=0;i<path_size;i++){

           this->FilePath.push_back(path[i]);
       }

       this->FilePath.shrink_to_fit();
    }
    else{
           std::cout << "\n\n ERROR:";

           std::cout << "\n A valid file name must be entered..";

           std::cout << "\n\n";

           exit(0);
    }
}

void Document_Builder::Receive_Document_Path(std::string Path){

     this->Document_Name_Receive_Status = true;

     size_t name_size = Path.size();

     for(size_t i=0;i<name_size;i++){

         this->Document_Name.push_back(Path[i]);
     }

     this->Document_Name.shrink_to_fit();
}



void Document_Builder::Read_File(){

     for(size_t i=0;i<this->File_Content.size();i++){

         this->File_Content.at(i).clear();

         this->File_Content.at(i).shrink_to_fit();
     }

     this->File_Content.clear();

     this->File_Content.shrink_to_fit();

     this->FileManager.SetFilePath(this->FilePath);

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          std::string str_line = this->FileManager.ReadLine() + "\n";

          this->File_Content.push_back(str_line);

     }while(!this->FileManager.Control_Stop_Condition());

     this->File_Content.shrink_to_fit();

     this->FileManager.FileClose();
}



void Document_Builder::Add_To_Document(){

     this->FileManager.SetFilePath(this->Document_Name);

     this->FileManager.FileOpen(Af);

     std::string file_name;

     this->Extract_File_Name(this->FilePath,file_name);

     std::string FileHeader = "\n\nFILE NAME: \"" + file_name + "\", FILE NUMBER: " + std::to_string(this->File_Number) + "\n";

     for(int i=0;i<100;i++){

         FileHeader = FileHeader + "-";
     }

     FileHeader = FileHeader + "\n\n";

     this->FileManager.WriteToFile(FileHeader);

     for(size_t i=0;i<this->File_Content.size();i++){

         this->FileManager.WriteToFile(this->File_Content[i]);
     }

     std::string File_Footer = "\n\n\n# THE END OF FILE # \n\n\n\n\n";

     this->FileManager.WriteToFile(File_Footer);

     this->File_Number++;

     this->FileManager.FileClose();
}

void Document_Builder::Add_File_To_Document(){

     if(this->File_Path_Receive_Status && this->Document_Name_Receive_Status){

        this->FileManager.SetFilePath(this->Document_Name);

        this->FileManager.FileOpen(Af);

        this->FileManager.FileClose();

        this->Read_File();

        this->Add_To_Document();
     }
     else{

           std::cout << "\n\n ERROR inside Document_Builder class";

           std::cout << "\n\n       File name can not readed..   ";

           exit(0);
     }
}


void Document_Builder::Extract_File_Name(std::string path, std::string & file_name){

     size_t path_size = path.size();

     size_t start_point = path_size;

     for(size_t i=path.size()-1;i>0;i--){

         if(path[i] == '\\'){

            break;
         }
         else{

              start_point--;
         }
     }

     for(size_t i=start_point;i<path.size();i++){

         //std::cout << "\n path[" << i << "]:" << path[i];

         //std::cin.get();

         file_name.push_back(path[i]);


     }

     file_name.shrink_to_fit();     
}


void Document_Builder::Clear_Std_String(std::string & str){

      if(!str.empty()){

          str.clear();

          str.shrink_to_fit();
      }
}