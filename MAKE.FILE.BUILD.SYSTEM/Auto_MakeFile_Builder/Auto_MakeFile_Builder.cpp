

#include "Auto_MakeFile_Builder.h"

Auto_MakeFile_Builder::Auto_MakeFile_Builder(){

     this->Memory_Delete_Condition = true;

     this->Warehouse_Path = nullptr;

     this->Repo_Dir = nullptr;

     this->repo_head_dir = nullptr;

     this->repo_obj_dir = nullptr;
}

Auto_MakeFile_Builder::Auto_MakeFile_Builder(const Auto_MakeFile_Builder & orig){


}


Auto_MakeFile_Builder::~Auto_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Auto_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->repo_head_dir != nullptr){

            delete [] this->repo_head_dir;

            this->repo_head_dir = nullptr;
         }

         if(this->repo_obj_dir != nullptr){

            delete [] this->repo_obj_dir;

            this->repo_obj_dir = nullptr;
         }
     }
}


void Auto_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Memory_Delete_Condition = false;

     this->Des_Reader_Pointer = Des_Reader;

     this->Warehouse_Path = this->Des_Reader_Pointer->Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader_Pointer->Get_Repo_Directory_Location();
}

void Auto_MakeFile_Builder::Build_Make_Files(){

     // Determination of the directories recorded on the git repo

     this->File_Lister.Determine_Git_Repo_Info(this->Des_Reader_Pointer);

     // Determination of the

     this->Determine_Project_Directories();

     int dir_num = this->File_Lister.Get_Source_File_Number();

     for(int i=0;i<dir_num;i++){

         char * source_file_name = this->File_Lister.Get_Source_File_Name(i);

         if(source_file_name != nullptr){

            this->Mk_Builder.Clear_Dynamic_Memory();

            this->Mk_Builder.Receive_Descriptor_File_Reader(this->Des_Reader_Pointer);

            this->Mk_Builder.Receive_Git_Record_Data(&this->File_Lister);

            this->Mk_Builder.Build_MakeFile(i);
         }
     }
}

void Auto_MakeFile_Builder::Determine_Project_Directories(){

     this->Memory_Delete_Condition = false;

     char Headers_Folder [] = "PROJECT.HEADER.FILES";

     char Objects_Folder [] = "PROJECT.OBJECT.FILES";

     size_t Warehouse_Path_Size = strlen(this->Warehouse_Path);

     this->repo_head_dir = new char [5*Warehouse_Path_Size];

     this->repo_obj_dir =  new char [5*Warehouse_Path_Size];

     this->Construct_Path(&(this->repo_head_dir),Headers_Folder,this->Warehouse_Path);

     this->Construct_Path(&(this->repo_obj_dir),Objects_Folder,this->Warehouse_Path);
}

void Auto_MakeFile_Builder::Construct_Path(char ** pointer, char * string, char * warehouse_path){

     int index = 0;

     size_t warehouse_path_size = strlen(warehouse_path);

     for(size_t i=0;i<warehouse_path_size;i++){

         (*pointer)[index] = warehouse_path[i];

         index++;
     }

     if(warehouse_path[warehouse_path_size-1] != '\\'){

        (*pointer)[index] = '\\';

        index++;
     }

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string[i];

        index++;
     }

     (*pointer)[index] = '\0';
}
