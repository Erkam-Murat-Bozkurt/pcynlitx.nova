

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

#include "Directory_Enumerator.h"
#include <iostream>

Directory_Enumerator::Directory_Enumerator(){

     this->Directory_List = nullptr;

     this->dir_path = nullptr;

     this->Directory_Number = 0;

     this->List_Index = 0;

     this->Memory_Delete_Condition = false;

     this->File_List = nullptr;

     this->c_str = nullptr;
};


Directory_Enumerator::~Directory_Enumerator(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void Directory_Enumerator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Pointer_List(&this->Directory_List,this->Directory_Number);

         this->Directory_Number = 0;


         this->Clear_Pointer_List(&this->File_List,this->File_Number);

         this->File_Number = 0;


         this->Clear_CString_Memory(&this->c_str);

         this->List_Index = 0;
     
         
         if(!this->std_str.empty()){
       
            this->std_str.clear();

            this->std_str.shrink_to_fit();
         }

         this->Clear_Vector_Memory(&this->File_List_StdStr);

         this->Clear_Vector_Memory(&this->Directory_List_StdStr);
     }
}

void Directory_Enumerator::Find_Sub_Directories(char * Root_Dir_Path){

     this->Clear_Dynamic_Memory();

     this->Memory_Delete_Condition = false;

     this->Determine_Sub_Directory_Number(Root_Dir_Path);

     int alloc_size = 5*this->Directory_Number;

     this->Directory_List = new char * [5*alloc_size];

     for(int i=0;i<5*alloc_size;i++){

         this->Directory_List[i] = nullptr;
     }

     this->Determine_Sub_Directories(Root_Dir_Path);
}

void Directory_Enumerator::Determine_Sub_Directory_Number(char * Directory_Path){

     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;

     TCHAR * search_path = nullptr;

     char * dir_path = nullptr;

     char current_dir [] = ".";

     char upper_dir [] = "..";

     this->Receive_Directory_Path(Directory_Path,&dir_path);

     this->Determine_Search_Path(dir_path,&search_path);

     // Find the first file in the directory.

     hFind = FindFirstFile(search_path,&ffd);

     if (INVALID_HANDLE_VALUE != hFind)
     {
          // Determine how many sub directory exist.

         while (FindNextFile(hFind,&ffd) != 0){

            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                 bool is_current_dir = this->CompareString(ffd.cFileName,current_dir);

                 bool is_upper_dir = this->CompareString(ffd.cFileName,upper_dir);

                 if(((!is_current_dir) && (!is_upper_dir))){

                    this->Directory_Number++;

                    char * sub_dir_path = nullptr;

                    this->Find_Sub_Directory_Path(dir_path,ffd.cFileName,&sub_dir_path);

                    this->Determine_Sub_Directory_Number(sub_dir_path);

                    if(sub_dir_path != nullptr){

                       delete [] sub_dir_path;
                    }
                 }
            }
         };
     }

     this->Clear_CString_Memory(&dir_path);


     if(search_path != nullptr){

        delete [] search_path;
     }

     FindClose(hFind);
}

void Directory_Enumerator::Determine_Sub_Directories(char * Directory_Path){

     this->Memory_Delete_Condition = false;

     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;

     char * dir_path = nullptr;

     TCHAR * search_path = nullptr;

     char current_dir [] = ".";

     char upper_dir [] = "..";

     this->Receive_Directory_Path(Directory_Path,&dir_path);

     this->Determine_Search_Path(dir_path,&search_path);

     hFind = FindFirstFile(search_path, &ffd);

     if (INVALID_HANDLE_VALUE != hFind)
     {
       // List all the files in the directory with some info about them.

       while (FindNextFile(hFind, &ffd) != 0){

             if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
             {
                 bool is_current_dir = this->CompareString(ffd.cFileName,current_dir);

                 bool is_upper_dir   = this->CompareString(ffd.cFileName,upper_dir);

                 if(((!is_current_dir) && (!is_upper_dir))){

                      char * sub_dir_path = nullptr;

                      this->Find_Sub_Directory_Path(dir_path,ffd.cFileName,&sub_dir_path);

                      this->Construct_Directory_List_Element(&(this->Directory_List[this->List_Index]),

                              ffd.cFileName,dir_path);

                      this->List_Index++;


                      this->Determine_Sub_Directories(sub_dir_path);

                      if(sub_dir_path != nullptr){

                          delete [] sub_dir_path;
                      }
                  }
              }
        };
     }

     this->Clear_CString_Memory(&dir_path);


     if(search_path != nullptr){

        delete [] search_path;
     }

     FindClose(hFind);

     
     this->Clear_Vector_Memory(&this->Directory_List_StdStr);


     for(int i=0;i<this->Directory_Number;i++){
     
        this->Directory_List_StdStr.push_back(this->Directory_List[i]);          
     }

     this->Directory_List_StdStr.shrink_to_fit();
}

void Directory_Enumerator::Construct_Directory_List_Element(char ** list_element,

     char * Dir_Name, char * dir_path){

     this->Memory_Delete_Condition = false;

     size_t dir_name_size = strlen(Dir_Name);

     size_t dir_path_size = strlen(dir_path);

     size_t memory_size = dir_name_size + dir_path_size;

     *list_element = new char [5*memory_size];

     int index = 0;

     for(size_t i=0;i<dir_path_size;i++){

         (*list_element)[index] = dir_path[i] ;

         index++;
     }

     if((*list_element)[dir_path_size-1] != '\\'){

          (*list_element)[index] = '\\';

          index++;
     }

     for(size_t i=0;i<dir_name_size;i++){

         (*list_element)[index] = Dir_Name[i] ;

         index++;
     }

     (*list_element)[index] = '\0';
}

void Directory_Enumerator::Receive_Directory_Path(char * Directory_Path,

     char ** dir_path){

     this->Memory_Delete_Condition = false;

     size_t dir_path_size = strlen(Directory_Path);

     *dir_path = new char [5*dir_path_size];

     for(size_t i=0;i<5*dir_path_size;i++){

         (*dir_path)[i] = '\0';
     }

     int index_counter = 0;

     for(size_t i=0;i<dir_path_size;i++){

         (*dir_path)[index_counter] = Directory_Path[i];

         index_counter++;
     }

     (*dir_path)[index_counter] = '\0';
}

void Directory_Enumerator::Determine_Search_Path(char * path, TCHAR ** pointer){

     size_t dir_path_length = strlen(path);

     *pointer = new TCHAR [MAX_PATH];

     for(size_t i=0;i<MAX_PATH;i++){

         (*pointer)[i] = '\0';
     }

     int index = 0;

     for(size_t k=0;k<dir_path_length;k++){

         (*pointer)[index] = path[k];

         index++;
     }

     if((*pointer)[index] !='\\'){

        (*pointer)[index] = '\\';

        index++;
     }

     (*pointer)[index] = '*';

     index++;

     size_t next_start = index;

     for(size_t k=next_start;k<MAX_PATH;k++){

         (*pointer)[index] = '\0';

         index++;
     }
}

void Directory_Enumerator::Find_Sub_Directory_Path(char * dir_root_path, char * dir_name,

     char ** sub_dir_path){

     size_t dir_root_path_size = strlen(dir_root_path);

     size_t dir_name_size = strlen(dir_name);

     size_t sub_dir_path_size = dir_root_path_size + dir_name_size;

     *sub_dir_path = new char [5*sub_dir_path_size];

     for(size_t i=0;i<5*sub_dir_path_size;i++){

         (*sub_dir_path)[i] = '\0';
     }

     int index_counter = 0;

     for(size_t i=0;i<dir_root_path_size;i++){

         (*sub_dir_path)[index_counter] = dir_root_path[i];

         index_counter++;
     }

     if((*sub_dir_path)[index_counter-1] != '\\'){

        (*sub_dir_path)[index_counter] = '\\';

        index_counter++;
     }

     for(size_t i=0;i<dir_name_size;i++){

        (*sub_dir_path)[index_counter] = dir_name[i] ;

        index_counter++;
     }

     (*sub_dir_path)[index_counter] = '\0';
}


void Directory_Enumerator::List_Files_On_Directory(std::string dir_path){

     char * path = this->Convert_StdStr_CStr(dir_path);

     this->List_Files_On_Directory(path);
}

void Directory_Enumerator::List_Files_On_Directory(char * dir_path){
     
     this->Memory_Delete_Condition = false;
     
     this->Clear_Pointer_List(&this->File_List,this->File_Number);

     this->File_Number = 0;


     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes =  FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;

     TCHAR * search_path = nullptr;

     this->Determine_Search_Path(dir_path,&search_path);

     // Find the first file in the directory.

     hFind = FindFirstFile(search_path,&ffd);

     if(INVALID_HANDLE_VALUE == hFind){

        std::cout << "\n Invalid handle in file enumaration..";

        exit(EXIT_FAILURE);
     }

     if (INVALID_HANDLE_VALUE != hFind)
     {
            while (FindNextFile(hFind,&ffd) != 0){

              if (ffd.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY)
              {
              }
               else{

                 this->File_Number++;
              }
            };
     }

     FindClose(hFind);


     this->File_List = new char * [5*this->File_Number];

     hFind = FindFirstFile(search_path,&ffd);


     if(INVALID_HANDLE_VALUE == hFind){

        std::cout << "\n Invalid handle in file enumaration..";

        exit(EXIT_FAILURE);
     }

     if (INVALID_HANDLE_VALUE != hFind)
     {
         // Determine how many sub directory exist.

         int index = 0;

         while (FindNextFile(hFind,&ffd) != 0){

            if (ffd.dwFileAttributes &  FILE_ATTRIBUTE_DIRECTORY)
            {

             }
             else{

                  size_t file_name_size = strlen(ffd.cFileName);

                  this->File_List[index] = new char [5*file_name_size];

                  for(size_t i=0;i<file_name_size;i++){

                      this->File_List[index][i] = ffd.cFileName[i];
                  }

                  this->File_List[index][file_name_size] = '\0';

                  index++;
             }
          };
     }

     FindClose(hFind);

     if(search_path != nullptr){

        delete [] search_path;
     }

     this->Clear_Vector_Memory(&this->File_List_StdStr);


     for(int i=0;i<this->File_Number;i++){
     
        this->File_List_StdStr.push_back(this->File_List[i]);          
     }

     this->File_List_StdStr.shrink_to_fit();
}


bool Directory_Enumerator::CompareString(char * firstString, char * secondString){

     int firstStringLength  = strlen(firstString);

     int secondStringLength = strlen(secondString);

     if(firstStringLength==secondStringLength){

        for(int i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

          this->isStringsEqual = false;

          return this->isStringsEqual;
     }
}

char * Directory_Enumerator::Convert_StdStr_CStr(std::string string)
{

       this->Clear_CString_Memory(&this->c_str);

       size_t str_size = string.length();

       this->c_str = new char [2*str_size];

       for(size_t i=0;i<str_size;i++){
       
           this->c_str[i] = string[i];
       }

       this->c_str[str_size] = '\0';

       return this->c_str;
}

std::string Directory_Enumerator::Convert_CStr_StdStr(char * string) 
{
       if(!this->std_str.empty()){
       
           this->std_str.clear();

           this->std_str.shrink_to_fit();
       }

       size_t str_size = strlen(string);

       for(size_t i=0;i<str_size;i++){
       
           this->std_str.push_back(string[i]);
       
       }

       return this->std_str;
}

void Directory_Enumerator::Clear_CString_Memory(char ** ptr){

     if(*ptr != nullptr){
     
        delete [] *ptr;

        *ptr = nullptr;
     }
}

void Directory_Enumerator::Clear_Pointer_List(char *** ptr, int list_size)
{     
     if(*ptr != nullptr){

         for(int i=0;i<list_size;i++){

            if((*ptr)[i] != nullptr){
     
              delete [] (*ptr)[i];

              (*ptr)[i] = nullptr;
            }
         }

         delete [] (*ptr);
      }
}

void Directory_Enumerator::Clear_Vector_Memory(std::vector<std::string> * pointer){

     if(!pointer->empty()){

         std::vector<std::string>::iterator it;

         auto begin = pointer->begin();

         auto end   = pointer->end();

         for(auto it=begin;it<end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
          }

          pointer->clear();

          pointer->shrink_to_fit();
     }
  }



bool Directory_Enumerator::getStringEquality(){

     return this->isStringsEqual;
}

char * Directory_Enumerator::Get_Directory_List_Element(int num) const
{
    return this->Directory_List[num];
}

std::string Directory_Enumerator::Get_Directory_List_Element_As_StdStr(int num) const {

     return this->Directory_List_StdStr[num];
}


int Directory_Enumerator::Get_Directory_Number_In_Directory() const
{
   return this->Directory_Number;
}

char ** Directory_Enumerator::Get_File_List(){

     return this->File_List;
}

std::vector<std::string> * Directory_Enumerator::Get_File_List_As_StdStr()
{
     return &this->File_List_StdStr;
}

int Directory_Enumerator::Get_File_Number(){

     return this->File_Number;
}
