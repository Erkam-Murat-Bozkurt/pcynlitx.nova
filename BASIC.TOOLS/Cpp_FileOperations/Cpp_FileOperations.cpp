
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

#include "Cpp_FileOperations.h"

Cpp_FileOperations::Cpp_FileOperations(){

    this->Initialize_Members();

   // Constructor Function for CString defined paths
};

Cpp_FileOperations::Cpp_FileOperations(char opr_sis){

    this->opr_sis = opr_sis;

    this->Initialize_Members();

   // Constructor Function for CString defined paths
};


Cpp_FileOperations::~Cpp_FileOperations(){

    this->Clear_Dynamic_Memory();

    // Destructor Function
};

void Cpp_FileOperations::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;
}

void Cpp_FileOperations::Determine_File_Path(char * FilePATH){

     if(this->Is_Current_Dir_Symbol_Exist_On_the_File_Path(FilePATH)){

        this->DetermineCurrentDirectory();

        size_t CurrentDirectory_Size = strlen(this->CurrentDirectory);

        for(size_t i=0;i<CurrentDirectory_Size;i++){

            this->FilePath.push_back(this->CurrentDirectory[i]);
        }


        if(this->opr_sis == 'w'){

           this->FilePath.push_back('\\');
        }

        if(this->opr_sis == 'l'){

           this->FilePath.push_back('/');
        }

        int name_start = 0;

        this->Find_Start_Point_When_Current_Dir_Symbol_Exist(FilePATH,name_start);

        size_t path_size = strlen(FilePATH);

        for(size_t i=name_start;i<path_size;i++){

            this->FilePath.push_back(FilePATH[i]);
        }

        this->FilePath.shrink_to_fit();
     }
     else{

            size_t path_size = strlen(FilePATH);

            for(size_t i=0;i<path_size;i++){

               this->FilePath.push_back(FilePATH[i]);
            }

            this->FilePath.shrink_to_fit();
     }
}

 void Cpp_FileOperations::Find_Start_Point_When_Current_Dir_Symbol_Exist(char * path, int & start_point){

      size_t path_size = strlen(path);

      start_point = 0;

      for(size_t i=0;i<path_size;i++){

          if(this->opr_sis == 'w'){

             if(path[i] == '\\'){

                break;
             }
             else{

                 start_point++;
             }
          }

          if(this->opr_sis == 'l'){

             if(path[i] == '/'){

                break;
             }
             else{

                 start_point++;
             }
          }
      }

      start_point++;
 }


void Cpp_FileOperations::Initialize_Members(){

     this->File_line_Number = 0;
     this->Memory_Delete_Condition = false;
     this->Delete_Return_Status = 0;
     this->file_open_status = false;
     this->is_path_exist = false;
     this->c_str = nullptr;
     this->CurrentDirectory = nullptr;
}

void Cpp_FileOperations::Clear_Dynamic_Memory(){

     this->Clear_Vector_Memory(&this->File_Content);

     this->Clear_CString_Memory(&this->c_str);

     this->Clear_CString_Memory(&this->CurrentDirectory);


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

     this->isFilePathReceive = true;

     this->Memory_Delete_Condition = false;

     this->Clear_String_Memory(&this->FilePath);

     char * file_path = this->Convert_Std_String_To_CString(FilePATH);

     this->Determine_File_Path(file_path);

     this->Clear_Temporary_CString_Memory();

     this->isFilePathReceive = true;
}

void Cpp_FileOperations::SetFilePath(char * FilePATH){

     this->Memory_Delete_Condition = false;

     this->isFilePathReceive = true;

     this->Clear_String_Memory(&this->FilePath);

     this->Determine_File_Path(FilePATH);
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
     else{

          this->file_open_status = true;

          this->Read_Stop_Condition = false;
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

     this->file_open_status = false;

     this->Read_Stop_Condition = false;
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

     std::string string_line;

     if(std::getline(this->DataFile,string_line)){

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

     return string_line;
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


void Cpp_FileOperations::CpFile(std::string path, std::string target_path){

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

     this->Clear_Dynamic_Memory();

     this->File_line_Number = 0;

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

void Cpp_FileOperations::Read_File(std::string path){

     this->Clear_Dynamic_Memory();

     this->File_line_Number = 0;

     this->SetFilePath(path);
     this->FileOpen(Rf);

     std::string new_line = "\n";

     do{
          std::string string_line = this->ReadLine();

          this->File_Content.push_back(string_line);

          this->File_Content.push_back(new_line);

          this->File_line_Number += 2;

     }while(this->DataFile.good());

     this->File_Content.shrink_to_fit();

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


bool Cpp_FileOperations::Is_This_File_Empty(std::string path){

     this->Clear_Dynamic_Memory();

     bool is_empty = true;


     this->File_line_Number = 0;

     this->SetFilePath(path);
     this->FileOpen(Rf);

     int valid_string_line =0;

     do{
          std::string string_line = this->ReadLine();

          if(!string_line.empty()){

             valid_string_line++;
          }


     }while(this->DataFile.good());

     this->FileClose();


     if(valid_string_line>0){

         is_empty = false;

         return is_empty;
     }
 

     return is_empty;
}


void Cpp_FileOperations::Record_File(char * target_path){

     this->SetFilePath(target_path);
     this->FileOpen(RWCf);

     for(int  i=0;i<this->File_line_Number;i++){

         this->WriteToFile(this->File_Content[i]);
     }

     this->FileClose();
}

void Cpp_FileOperations::Record_File(std::string target_path){

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



int Cpp_FileOperations::Delete_File(std::string path){

    char * cpath = this->Convert_Std_String_To_CString(path);

    return this->Delete_File(cpath);
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


char * Cpp_FileOperations::Convert_Std_String_To_CString(std::string st)
{
       this->Clear_CString_Memory(&this->c_str);

       size_t string_size = st.length();

       this->c_str = new char [5*string_size];

       for(size_t i=0;i<5*string_size;i++){
       
           this->c_str[i] = '\0';    
       }

       for(size_t i=0;i<string_size;i++){
       
           this->c_str[i] = st[i];
       }

       this->c_str[string_size] = '\0';

       return this->c_str;
}


void Cpp_FileOperations::DetermineCurrentDirectory(){

     this->Clear_CString_Memory(&this->CurrentDirectory);

     CHAR Buffer[BUFSIZE];

     GetCurrentDirectory(BUFSIZE, Buffer);

     char * Directory = Buffer;

     int Directory_Name_Size = strlen(Directory);

     this->Memory_Delete_Condition = false;

     this->CurrentDirectory = new char [5*Directory_Name_Size];

     this->Place_String(&this->CurrentDirectory,Directory,Directory_Name_Size);
}

bool Cpp_FileOperations::Is_Current_Dir_Symbol_Exist_On_the_File_Path(char * path){

     bool current_dir_sysmbol_existance = false;

     size_t path_length = strlen(path);
     
     char first_character = '\0';

     size_t first_character_position = 0;

     for(size_t i=0;i<path_length;i++){

         if(path[i]!= ' '){

            first_character = path[i];

            break;            
         }
         else{

              first_character_position++;
         }
     }

     char second_character  = '\0';

     for(size_t i=first_character_position+1;i<path_length;i++){

         if(path[i]!= ' '){

            second_character = path[i];

            break;            
         }
     }

     if(this->opr_sis == 'w'){

        if(first_character == '.'){

           if(second_character == '\\'){

               current_dir_sysmbol_existance = true;
           }
        }
     }

     if(this->opr_sis == 'l'){

        if(first_character == '.'){

           if(second_character == '/'){

               current_dir_sysmbol_existance = true;
           }
        }
     }

     return current_dir_sysmbol_existance;

}


void Cpp_FileOperations::Place_String(char ** Pointer, char * String, int String_Size){

     for(int i=0;i<String_Size;i++){

        (*Pointer)[i] = String[i];
     }

     (*Pointer)[String_Size] = '\0';
}

void Cpp_FileOperations::Clear_CString_Memory(char ** pointer){

     if(*pointer!= nullptr){
     
        delete [] *pointer;

        *pointer = nullptr;     
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

void Cpp_FileOperations::Clear_Temporary_CString_Memory(){

     this->Clear_CString_Memory(&this->c_str);
}

int Cpp_FileOperations::GetFileSize() const {

    return this->File_line_Number;
}


std::string Cpp_FileOperations::GetFilePath() const {

     return this->FilePath;
}