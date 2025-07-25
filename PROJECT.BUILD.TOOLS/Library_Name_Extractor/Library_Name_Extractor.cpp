/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Library_Name_Extractor.hpp"

Library_Name_Extractor::Library_Name_Extractor(){

   this->dll_files = nullptr;
   this->archive_files = nullptr;
   this->dll_files_number = 0;
   this->archive_files_number = 0;
   this->Memory_Delete_Condition = true;
};

Library_Name_Extractor::Library_Name_Extractor(const Library_Name_Extractor & orig){

};

Library_Name_Extractor::~Library_Name_Extractor(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};

void Library_Name_Extractor::Clear_Dynamic_Memory(){

     if(this->Memory_Delete_Condition){

        if(this->dll_files != nullptr){

           for(int i=0;i<this->dll_files_number;i++){

              delete [] this->dll_files[i];
           }
        }

        if(this->archive_files != nullptr){

           for(int i=0;i<this->archive_files_number;i++){

              delete [] this->archive_files[i];
           }
        }

        if(this->director_path != nullptr){

           delete [] this->director_path;
        }
     }
}
void Library_Name_Extractor::Determine_Library_Names(char * path){

     this->Receive_Directory_Path(path);

     this->Enum.List_Files_On_Directory(this->director_path);

     this->Determine_Dll_Files_Number();

     this->Determine_Archive_Files_Number();

     if(this->dll_files_number>0){

        this->Extract_Dll_Files();
     }

     if(this->archive_files_number > 0){

        this->Extract_Archive_Files();
     }
}

void Library_Name_Extractor::Determine_Dll_Files_Number(){

     this->dll_files_number = 0;

     char dll_ext [] = ".dll";

     int file_num = this->Enum.Get_File_Number();

     std::vector<std::string> * file_list = this->Enum.Get_File_List();

     for(int i=0;i<file_num;i++){

         bool is_dll =  this->StringManager.CheckStringInclusion(file_list->at(i),dll_ext);

         if(is_dll){

              this->dll_files_number++;
           }
     }
}


void Library_Name_Extractor::Determine_Archive_Files_Number(){

     this->archive_files_number = 0;

     char archive_ext [] =".a";

     int file_num = this->Enum.Get_File_Number();

     std::vector<std::string> * file_list =this->Enum.Get_File_List();

     for(int i=0;i<file_num;i++){

         bool is_archive =  this->StringManager.CheckStringInclusion(file_list->at(i),archive_ext);

         if(is_archive){

              this->archive_files_number++;
           }
     }
}

void Library_Name_Extractor::Extract_Dll_Files(){

     if(this->dll_files_number > 0){

        this->dll_files = new char * [5*this->dll_files_number];

        char dll_ext [] = ".dll";

        int file_num = this->Enum.Get_File_Number();

        std::vector<std::string> * file_list = this->Enum.Get_File_List();

        int index = 0;

        for(int i=0;i<file_num;i++){

            bool is_dll =  this->StringManager.CheckStringInclusion(file_list->at(i),dll_ext);

            if(is_dll){

               this->Place_String(&(this->dll_files[index]),file_list->at(i).c_str());

               index++;
            }
        }
     }
}

void Library_Name_Extractor::Extract_Archive_Files(){

     if(this->archive_files_number > 0){

        this->archive_files = new char * [5*this->archive_files_number];

        char archive_ext [] =".a";

        int file_num = this->Enum.Get_File_Number();

        std::vector<std::string> * file_list =this->Enum.Get_File_List();

        int index = 0;

        for(int i=0;i<file_num;i++){

            bool is_archive =  this->StringManager.CheckStringInclusion(file_list->at(i),archive_ext);

            if(is_archive){

               this->Place_String(&(this->archive_files[index]),file_list->at(i));

               index++;
            }
        }
     }
}

/*

void Library_Name_Extractor::Extract_Library_Files(){

     char archive_ext [] =".a";

     char dll_ext [] = ".dll";

     int file_num = this->Enum.Get_File_Number();

     std::cout << "\n file_num:" << file_num;

     std::cin.get();

     char **  file_list =this->Enum.Get_File_List();

     int index = 0;

     for(int i=0;i<file_num;i++){

         bool is_archive = this->StringManager.CheckStringInclusion(file_list[i],archive_ext);

         bool is_dll =  this->StringManager.CheckStringInclusion(file_list[i],dll_ext);

         if(is_archive || is_dll){

            std::cout << "\n archive file -" << index << ": " << file_list[i];

            index++;
         }
     }
}

*/

void Library_Name_Extractor::Receive_Directory_Path(char * path){

     size_t path_size = strlen(path);

     this->director_path = new char [5*path_size];

     for(size_t i=0;i<path_size;i++){

        this->director_path[i] = path[i];
     }

     this->director_path[path_size] = '\0';
}

void Library_Name_Extractor::Place_String(char ** pointer, char * string){

     size_t string_size = strlen(string);

     (*pointer) = new char [5*string_size];

     for(size_t i =0; i<string_size;i++){

        (*pointer)[i] = string[i];
     }

     (*pointer)[string_size] = '\0';
}

void Library_Name_Extractor::Place_String(char ** pointer, std::string string){

     size_t string_size = string.length();

     (*pointer) = new char [5*string_size];

     for(size_t i =0; i<string_size;i++){

        (*pointer)[i] = string[i];
     }

     (*pointer)[string_size] = '\0';
}


char * Library_Name_Extractor::Get_Archive_File(int index){

       return this->archive_files[index];
}

char * Library_Name_Extractor::Get_Dll_File(int index){

       return this->dll_files[index];
}

int  Library_Name_Extractor::Get_DLL_Files_Number(){

      return this->dll_files_number;
}

int  Library_Name_Extractor::Get_Arcive_Files_Number(){

     return this->archive_files_number;
}
