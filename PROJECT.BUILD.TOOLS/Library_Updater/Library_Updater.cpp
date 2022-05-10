
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

Library_Updater::Library_Updater(){

    this->Memory_Delete_Condition = false;

    this->Object_File_List = nullptr;

    this->Archive_Build_Command = nullptr;

    this->warehouse_obj_dir = nullptr;

    this->warehouse_path = nullptr;

    this->library_name = nullptr;

    this->Current_Library_Path = nullptr;
}

Library_Updater::Library_Updater(const Library_Updater & orig){

}

Library_Updater::~Library_Updater(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}

void Library_Updater::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Pointer_Memory(&this->Object_File_List);

         this->Clear_Pointer_Memory(&this->Archive_Build_Command);

         this->Clear_Pointer_Memory(&this->warehouse_obj_dir);

         this->Clear_Pointer_Memory(&this->library_name);
     }
}


void Library_Updater::Receive_Descriptor_File(char * descriptor_file){

     this->Des_Reader.Read_Descriptor_File(descriptor_file);
}

void Library_Updater::Build_Library(char * Library_Name){

     this->Clear_Dynamic_Memory();

     this->Receive_Library_Name(Library_Name);

     this->warehouse_path = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Warehouse_Object_Dir('w');

     this->Determine_Current_Library_Path();

     this->Determine_Target_Library_Path();

     this->Memory_Delete_Condition = false;

     DIR *d;

     struct dirent *dir;

     int list_character_size = 0;

     d = opendir(this->warehouse_obj_dir);

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

     this->Object_File_List = new char [5*list_character_size];

     int index_counter = 0;

     d = opendir(this->warehouse_obj_dir);

     if (d){

        while ((dir = readdir(d)) != NULL)
        {

            int file_name_size = strlen(dir->d_name);

            char * name = dir->d_name;

            if(((name[file_name_size-1] == 'o') && (name[file_name_size-2] == '.'))){

                this->Place_Information(&this->Object_File_List,name,&index_counter);

                this->Place_Information(&this->Object_File_List,Space_Character,&index_counter);
            }
        }

        this->Object_File_List[index_counter] = '\0';

        closedir(d);
     }

     char Library_Construction_Command [] = {'a','r',' ','r','s',' ','l','i','b','\0'};

     char Library_Add_word [] = {'.','a','\0'};

     index_counter = 0; // Reset index counter value

     int Object_File_List_Character_Size = strlen(this->Object_File_List);

     this->Archive_Build_Command = new char [5*Object_File_List_Character_Size];

     this->Place_Information(&this->Archive_Build_Command,Library_Construction_Command,&index_counter);

     this->Place_Information(&this->Archive_Build_Command,Library_Name,&index_counter);

     this->Place_Information(&this->Archive_Build_Command,Library_Add_word,&index_counter);

     this->Place_Information(&this->Archive_Build_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Archive_Build_Command,this->Object_File_List,&index_counter);

     this->Archive_Build_Command[index_counter-1] = '\0';

     chdir(this->warehouse_obj_dir);

     this->System_Interface.System_Function(this->Archive_Build_Command);

     this->Send_Library_To_Libraries_Location();
}



void Library_Updater::Determine_Warehouse_Object_Dir(char operating_sis){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     char warehouse_word   [] = "WAREHOUSE";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_dir_size = strlen(object_directory);

     size_t wr_word_size  = strlen(warehouse_word);


     size_t path_size = warehouse_path_size

            + object_dir_size + wr_word_size;

     this->warehouse_obj_dir = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_obj_dir[index] = this->warehouse_path[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

            this->warehouse_obj_dir[index] = '/';

            index++;
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir[index] = warehouse_word[i];

         index++;
     }


     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

           this->warehouse_obj_dir[index] = '/';

           index++;
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir[index] = object_directory[i];

         index++;
     }

     this->warehouse_obj_dir[index] = '\0';
}


void Library_Updater::Determine_Target_Library_Path(){

     size_t Library_Name_Size = strlen(this->library_name);

     char library_prefix [] = {'l','i','b','\0'};

     char library_subfix [] = {'.','a','\0'};

     char * Library_File_Name = new char [5*Library_Name_Size];

     int index_counter = 0;

     this->Place_Information(&Library_File_Name,library_prefix,&index_counter);

     this->Place_Information(&Library_File_Name,this->library_name,&index_counter);

     this->Place_Information(&Library_File_Name,library_subfix,&index_counter);

     Library_File_Name[index_counter] = '\0';


     char warehouse_word [] = "WAREHOUSE";

     char directory_folder_name [] = "PROJECT.LIBRARY.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t name_size= strlen(directory_folder_name);

     size_t wr_word_size = strlen(warehouse_word);



     size_t library_dir_size = warehouse_path_size + name_size + wr_word_size;

     this->Target_Library_Path = new char [5*library_dir_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Target_Library_Path[index] = this->warehouse_path[i];

         index++;
     }

     this->Target_Library_Path[index] = '\\';

     index++;

     for(size_t i=0;i<wr_word_size;i++){

        this->Target_Library_Path[index] = warehouse_word[i];

        index++;
     }

     this->Target_Library_Path[index] = '\\';

     index++;

     for(size_t i=0;i<name_size;i++){

         this->Target_Library_Path[index] = directory_folder_name[i];

         index++;
     }


     this->Target_Library_Path[index] = '\\';

     index++;

     size_t library_name_size = strlen(Library_File_Name);

     for(size_t i=0;i<library_name_size;i++){

         this->Target_Library_Path[index] = Library_File_Name[i];

         index++;
     }

     this->Target_Library_Path[index] = '\0';

     delete[] Library_File_Name;
}


void Library_Updater::Determine_Current_Library_Path(){

     size_t Library_Name_Size = strlen(this->library_name);

     char library_prefix [] = {'l','i','b','\0'};

     char library_subfix [] = {'.','a','\0'};

     char * Library_File_Name = new char [5*Library_Name_Size];

     int index_counter = 0;

     this->Place_Information(&Library_File_Name,library_prefix,&index_counter);

     this->Place_Information(&Library_File_Name,this->library_name,&index_counter);

     this->Place_Information(&Library_File_Name,library_subfix,&index_counter);

     Library_File_Name[index_counter] = '\0';



     char object_directory_folder_name [] = "PROJECT.OBJECT.FILES";

     char warehouse_word [] = "WAREHOUSE";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_folder_size= strlen(object_directory_folder_name);

     size_t warehouse_word_size = strlen(warehouse_word);

     size_t object_dir_size = warehouse_path_size + object_folder_size
                             + warehouse_word_size;

     this->Current_Library_Path = new char [5*object_dir_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Current_Library_Path[index] = this->warehouse_path[i];

         index++;
     }

     this->Current_Library_Path[index] = '\\';

     index++;

     for(size_t i=0;i<warehouse_word_size;i++){

         this->Current_Library_Path[index] = warehouse_word[i];

         index++;
     }

     this->Current_Library_Path[index] = '\\';

     index++;


     for(size_t i=0;i<object_folder_size;i++){

         this->Current_Library_Path[index] = object_directory_folder_name[i];

         index++;
     }

     this->Current_Library_Path[index] = '\\';

     index++;

     size_t library_name_size = strlen(Library_File_Name);

     for(size_t i=0;i<library_name_size;i++){

         this->Current_Library_Path[index] = Library_File_Name[i];

         index++;
     }

     this->Current_Library_Path[index] = '\0';

     delete[] Library_File_Name;
}

void Library_Updater::Send_Library_To_Libraries_Location(){

     this->FileManager.MoveFile_Win(this->Current_Library_Path,this->Target_Library_Path);
}

void Library_Updater::Receive_Library_Name(char * lib_name){

     size_t name_size = strlen(lib_name);

     this->library_name = new char [5*name_size];

     for(size_t i=0;i<5*name_size;i++){

         this->library_name[i] = '\0';
     }

     for(size_t i=0;i<name_size;i++){

         this->library_name[i] = lib_name[i];
     }

     this->library_name[name_size] = '\0';
}

void Library_Updater::Place_Information(char ** Pointer, char * Information, int * index_counter){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         (*Pointer)[(*index_counter)] = Information[i];

         (*index_counter)++;
     }
 }

void Library_Updater::Clear_Pointer_Memory(char ** pointer){

     if( *pointer != nullptr ){

        delete [] *pointer;

        *pointer = nullptr;
     }
}
