
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

#include "Cpp_FileOperations.h"

Cpp_FileOperations::Cpp_FileOperations(){

    this->Initialize_Members();

   // Constructor Function for CString defined paths
};

Cpp_FileOperations::Cpp_FileOperations(char * FilePATH){

    this->Initialize_Members();

    this->SetFilePath(FilePATH);

   // Constructor Function for CString defined paths
};

Cpp_FileOperations::Cpp_FileOperations(std::string FilePATH){

    this->Initialize_Members();

    this->SetFilePath(FilePATH);

   // Constructor Function for CString defined paths
};


Cpp_FileOperations::~Cpp_FileOperations(){

    this->Clear_Dynamic_Memory();

    // Destructor Function
};

void Cpp_FileOperations::Initialize_Members(){

     this->File_line_Number = 0;
     this->Memory_Delete_Condition = false;
     this->Delete_Return_Status = 0;
     this->file_open_status = false;
     this->is_path_exist = false;
}

void Cpp_FileOperations::Clear_Dynamic_Memory(){

     this->Clear_Vector_Memory(&this->File_Content);

     if(!this->String_Line.empty())
     {
         this->String_Line.clear();
         this->String_Line.shrink_to_fit();
     }

     if(!this->string_word.empty())
     {
        this->string_word.clear();
        this->string_word.shrink_to_fit();
     }

     if(!this->FilePath.empty())
     {
         this->FilePath.clear();
         this->FilePath.shrink_to_fit();
     }
}

void Cpp_FileOperations::SetFilePath(std::string FilePATH){

     this->Memory_Delete_Condition = false;

     this->isFilePathReceive = true;

     size_t String_Size = FilePATH.length();

     for(size_t i=0;i<String_Size;i++){

         this->FilePath.push_back(FilePATH[i]);
     }
}

void Cpp_FileOperations::SetFilePath(char * FilePATH){

     this->isFilePathReceive = true;

     size_t String_Size = strlen(FilePATH);

     for(size_t i=0;i<String_Size;i++){

         this->FilePath.push_back(FilePATH[i]);
     }
}

void Cpp_FileOperations::FileOpen(char Open_Mode){

     if(Open_Mode == 'r'){

        this->DataFile.open(this->FilePath,std::ios::in);
     }

     if(Open_Mode == 'w'){

        this->DataFile.open(this->FilePath,std::ios::out);
     }

     if(Open_Mode == 'x'){

        this->DataFile.open(this->FilePath,std::ios::in | std::ios::out);
     }

     if(Open_Mode == 'b'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::trunc);
     }

     if(Open_Mode == 'a'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::app);
     }

     if(!this->DataFile.is_open()){

          std::cout << "\n ERROR:";

          std::cout << "\n";

          std::cout << "\n Class : Cpp_FileOperations";

          std::cout << "\n";

          std::cout << "\n The file " << this->FilePath << " can not be opened ..";

          std::cout << "\n\n";

          exit(0);
     }
}

bool Cpp_FileOperations::TryOpen(char Open_Mode){

     // This function is used in order to determine whether the file exist or not

     if(Open_Mode == 'r'){

        this->DataFile.open(this->FilePath,std::ios::in);
     }

     if(Open_Mode == 'w'){

        this->DataFile.open(this->FilePath,std::ios::out);
     }

     if(Open_Mode == 'x'){

        this->DataFile.open(this->FilePath,std::ios::in | std::ios::out);
     }

     if(Open_Mode == 'b'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::trunc);
     }

     if(Open_Mode == 'a'){

        this->DataFile.open(this->FilePath,std::ios::out | std::ios::app);
     }

     this->file_open_status = false;

     if(this->DataFile.is_open()){

       this->file_open_status = true;
     }
     else{

          this->file_open_status = false;
     }

     return this->file_open_status;
}

void Cpp_FileOperations::FileClose(){

     this->DataFile.close();
}

void Cpp_FileOperations::WriteToFile(std::string string_list){

     this->DataFile <<  string_list;
}

void Cpp_FileOperations::WriteToFile(const char * string_list){

     std::string transfer_string;

     size_t String_Size = strlen(string_list);

     for(size_t i=0;i<String_Size;i++){

         transfer_string.push_back(string_list[i]);
     }

     this->DataFile << transfer_string;
}


void Cpp_FileOperations::WriteToFile(char * string_list){

     std::string transfer_string;

     size_t String_Size = strlen(string_list);

     for(size_t i=0;i<String_Size;i++){

         transfer_string.push_back(string_list[i]);
     }

     this->DataFile << transfer_string;
}

std::string Cpp_FileOperations::ReadLine(){

     this->String_Line.clear();
     this->String_Line.shrink_to_fit();

     if(std::getline(this->DataFile,this->String_Line)){

         if(this->DataFile.good()){

           this->Read_Stop_Condition = false;
         }
         else{

               this->Read_Stop_Condition = true;
         }
     }
     else{

            this->Read_Stop_Condition = true;
     }

     return this->String_Line;
}


std::string Cpp_FileOperations::Read(){

     if(this->DataFile >> this->string_word){

       this->Read_Stop_Condition = false;
     }
     else{

          this->Read_Stop_Condition = true;
     }

     return this->string_word;
}

bool Cpp_FileOperations::Control_Stop_Condition(){

     return this->Read_Stop_Condition;
}



void Cpp_FileOperations::CpFile(char * path, char * target_path){

     this->Read_File(path);
     this->Record_File(target_path);
}


void Cpp_FileOperations::MoveFile_Win(char * current_path, char * target_path){

     CopyFile(current_path,target_path,false);

     if(this->Is_Path_Exist(current_path)){

        int test = DeleteFileA(current_path);

        if(test == 0){

           std::cout << "\n Th file stay in "

           << current_path << " can not be removed .." ;

            exit(0);
        }
    }
}

void Cpp_FileOperations::Read_File(char * path){

     this->File_line_Number = 0;

     this->SetFilePath(path);
     this->FileOpen(Rf);

     this->Clear_Vector_Memory(&this->File_Content);


     std::string new_line = "\n";

     do{
          std::string string_line = this->ReadLine();

          this->File_Content.push_back(string_line);

          this->File_Content.push_back(new_line);

          this->File_line_Number += 2;

     }while(this->DataFile.good());

     this->FileClose();
}

void Cpp_FileOperations::Read_File(std::string path){

     this->File_line_Number = 0;

     this->Clear_Vector_Memory(&this->File_Content);

     this->SetFilePath(path);
     this->FileOpen(Rf);

     std::string new_line = "\n";

     do{
          std::string string_line = this->ReadLine();

          this->File_Content.push_back(string_line);

          this->File_Content.push_back(new_line);

          this->File_line_Number += 2;

     }while(this->DataFile.good());

     this->FileClose();
}

bool Cpp_FileOperations::Is_This_File_Empty(char * path){

     this->Read_File(path);

     this->Is_File_Empty = true;

     if(this->File_line_Number > 0){

        this->Is_File_Empty = false;
     }

     return this->Is_File_Empty;
}

void Cpp_FileOperations::Record_File(char * target_path){

     this->SetFilePath(target_path);
     this->FileOpen(RWCf);

     for(int  i=0;i<this->File_line_Number;i++){

         this->WriteToFile(this->File_Content[i]);
     }

     this->FileClose();
}

void Cpp_FileOperations::Printf(){ // Prints file to the screen

     if(this->File_Content.empty()){

         std::cout << "\n The file did not read yet";
     }
     else{

          for(int i=0;i<this->File_line_Number;i++){

              std::cout << this->File_Content[i];
          }
     }
}


bool Cpp_FileOperations::Is_Path_Exist(char * path){

     this->is_path_exist = true;

     struct _stat buf;

     int result = 0;

     result = _stat( path, &buf );

     if( result != 0 ){

       this->is_path_exist = false;
     }

     return this->is_path_exist;
}

bool Cpp_FileOperations::Is_Path_Exist(std::string path){

     this->is_path_exist = true;

     struct _stat buf;

     int result = 0;

     result = _stat( path.c_str(), &buf );

     if( result != 0 ){

       this->is_path_exist = false;
     }

     return this->is_path_exist;
}

int Cpp_FileOperations::Delete_File(char * path){

     int path_length = strlen(path);

     TCHAR * path_pointer = new TCHAR[5*path_length];

     for(int i=0;i<path_length;i++){

         path_pointer[i] = path[i];
     }

     path_pointer[path_length] = '\0';

     path_pointer[path_length+1] = '\0';

     if(this->Is_Path_Exist(path_pointer)){

        SHFILEOPSTRUCT fileop;

        fileop.wFunc = FO_DELETE;

        fileop.pFrom = path_pointer;

        fileop.pTo = NULL;

        fileop.hwnd = NULL;

        fileop.fFlags = FOF_FILESONLY | FOF_NOCONFIRMATION;

        this->Delete_Return_Status = SHFileOperationA(&fileop);

        if(this->Delete_Return_Status != 0) {

          std::cout << "\n The file can not be removed ..";
        }
     }
     else{

          std::cout << "\n Error inside Cpp_FileOperations";

          std::cout << "\n Inside Delete_File:";

          std::cout << "\n The file " << path_pointer << " is not exist..";
     }

     delete [] path_pointer;

     return this->Delete_Return_Status;
}



int Cpp_FileOperations::Delete_File(const char * path)
{
     int path_length = strlen(path);

     TCHAR * path_pointer = new TCHAR[5*path_length];

     for(int i=0;i<path_length;i++){

         path_pointer[i] = path[i];
     }

     path_pointer[path_length] = '\0';

     path_pointer[path_length+1] = '\0';

     if(this->Is_Path_Exist(path_pointer)){

        SHFILEOPSTRUCT fileop;

        fileop.wFunc = FO_DELETE;

        fileop.pFrom = path_pointer;

        fileop.pTo = NULL;

        fileop.hwnd = NULL;

        fileop.fFlags = FOF_FILESONLY | FOF_NOCONFIRMATION;

        this->Delete_Return_Status = SHFileOperationA(&fileop);

        if(this->Delete_Return_Status != 0) {

          std::cout << "\n The file can not be removed ..";
        }
     }
     else{

          std::cout << "\n Error inside Cpp_FileOperations";

          std::cout << "\n Inside Delete_File:";

          std::cout << "\n The file " << path_pointer << " is not exist..";
     }

     delete [] path_pointer;

     return this->Delete_Return_Status;
}

std::string Cpp_FileOperations::GetFileLine(int index){

       if(!this->File_Content.empty()){

          return this->File_Content[index];
       }
       else{

            std::cout << "\n\n the file did not read yet";

            std::cout << "\n\n the file must be read with";

            std::cout << "\n\n command ReadFile(char * path) ";

            exit(0);
       }
}


void Cpp_FileOperations::Clear_Vector_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();

     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();

            it->shrink_to_fit();
        }
     }

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}

void Cpp_FileOperations::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}

int Cpp_FileOperations::GetFileSize() const {

    return this->File_line_Number;
}
