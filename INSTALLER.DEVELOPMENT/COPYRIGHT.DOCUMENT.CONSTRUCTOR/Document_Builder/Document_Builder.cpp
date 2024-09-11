
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

#include "Document_Builder.h"

Document_Builder::Document_Builder(){

     this->Memory_Delete_Condition = true;

     this->File_Path_Receive_Status = false;

     this->Document_Name_Receive_Status = false;
}

Document_Builder::Document_Builder(const Document_Builder & orig){}

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

     size_t File_Name_Size = this->FilePath.size();

     for(size_t i= 0;i<File_Name_Size;i++){

         file_name.push_back(this->FilePath[i]);
     }

     file_name.shrink_to_fit();

     std::string FileHeader = "\n\nFILE NAME: " + file_name;

     for(int i=0;i<80;i++){

         FileHeader = FileHeader + "-";
     }

     FileHeader = FileHeader + "\n\n";

     this->FileManager.WriteToFile(FileHeader);

     for(size_t i=0;i<this->File_Content.size();i++){

         this->FileManager.WriteToFile(this->File_Content[i]);
     }

     std::string File_Footer = "\n\nTHE END OF FILE \n\n";

     this->FileManager.WriteToFile(File_Footer);

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

void Document_Builder::Clear_Std_String(std::string & str){

      if(!str.empty()){

          str.clear();

          str.shrink_to_fit();
      }
}