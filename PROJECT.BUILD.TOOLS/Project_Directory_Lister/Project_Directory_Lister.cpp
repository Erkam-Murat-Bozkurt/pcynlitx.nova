
#include "Project_Directory_Lister.h"

Project_Directory_Lister::Project_Directory_Lister(){

    this->Directory_List = nullptr;

    this->Source_File_Directory_List = nullptr;

    this->Source_File_Directory_Number = 0;

    this->Directory_Tree_Size = 0;

    this->project_directory_number = 0;

    this->Repo_Dir = nullptr;

    this->Memory_Delete_Condition = true;
}

Project_Directory_Lister::Project_Directory_Lister(const Project_Directory_Lister & orig){


}


Project_Directory_Lister::~Project_Directory_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Project_Directory_Lister::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(int k=0;k<this->Directory_Number;k++){

             delete [] this->Directory_List[k];

             this->Directory_List[k] = nullptr;
         }

         delete [] this->Directory_List;

         this->Directory_List = nullptr;

         for(int k=0;k<this->Source_File_Directory_Number;k++){

            delete [] this->Source_File_Directory_List[k];
         }

         delete [] this->Source_File_Directory_List;

         this->Source_File_Directory_List = nullptr;

         if(this->Repo_Dir != nullptr){

            delete [] this->Repo_Dir;

            this->Repo_Dir = nullptr;
         }
     }
}

void Project_Directory_Lister::Receive_Repo_Directory(char * repo_dir){

     this->Memory_Delete_Condition = false;

     size_t repo_dir_size = strlen(repo_dir);

     this->Repo_Dir = new char [5*repo_dir_size];

     for(size_t i=0;i<repo_dir_size;i++){

        this->Repo_Dir[i] = repo_dir[i];
     }

     this->Repo_Dir[repo_dir_size] = '\0';
}

void Project_Directory_Lister::Determine_Project_File_List(){

    this->Tree_Size_Determiner.Determine_Directory_Tree_Size(this->Repo_Dir);

    this->Directory_Number = this->Tree_Size_Determiner.Get_Directory_Tree_Size();

    this->Enumerator.Find_Sub_Directories(this->Repo_Dir);

    this->project_directory_number = this->Enumerator.Get_Directory_Number_In_Directory();

    this->Directory_List = new char * [5*this->Directory_Number];

    for(int i=0;i<5*this->Directory_Number;i++){

        this->Directory_List[i] = nullptr;
    }

    int active_directory_num = this->Enumerator.Get_Directory_Number_In_Directory();

    this->Memory_Delete_Condition = false;

    for(int i=0;i<active_directory_num;i++){

         char * dir_string = this->Enumerator.Get_Directory_List_Element(i);

         size_t string_size = strlen(dir_string);

         this->Directory_List[i] = new char [5*string_size];

         for(int k=0;k<5*string_size;k++){

             this->Directory_List[i][k] = '\0';
         }

         for(int k=0;k<string_size;k++){

             this->Directory_List[i][k] = dir_string[k];
         }

         this->Directory_List[i][string_size] = '\0';
    }

    this->Determine_Source_File_Directory_Number();

    this->Extract_Source_File_Directories();
}

void Project_Directory_Lister::Determine_Source_File_Directory_Number(){

     char git_record_files [] = ".git";

     bool is_git_record_file = false;

     int active_directory_num = this->Enumerator.Get_Directory_Number_In_Directory();

     for(int i=0;i<active_directory_num;i++){

         this->Enumerator.Clear_Dynamic_Memory();

         this->Enumerator.Find_Sub_Directories(this->Directory_List[i]);

         int sub_directory_number = this->Enumerator.Get_Directory_Number_In_Directory();

         if(sub_directory_number == 0){

            is_git_record_file = this->StringManager.CheckStringInclusion(this->Directory_List[i],git_record_files);

            if(!is_git_record_file){

                this->Source_File_Directory_Number++;
            }
         }
     }
}

void Project_Directory_Lister::Extract_Source_File_Directories(){

     this->Source_File_Directory_List = new char * [5*this->Source_File_Directory_Number];

     char git_record_files [] = ".git";

     bool is_git_record_file = false;

     int source_folder_index = 0;

     for(int i=0;i<this->project_directory_number;i++){

         is_git_record_file = this->StringManager.CheckStringInclusion(this->Directory_List[i],git_record_files);

         if(!is_git_record_file){

              this->Enumerator.Clear_Dynamic_Memory();

              this->Enumerator.Find_Sub_Directories(this->Directory_List[i]);

              int sub_directory_number = this->Enumerator.Get_Directory_Number_In_Directory();

              if(sub_directory_number == 0){

                size_t directory_name_size = strlen(this->Directory_List[i]);

                this->Source_File_Directory_List[source_folder_index] = new char [5*directory_name_size];

                for(size_t k=0;k<directory_name_size;k++){

                   this->Source_File_Directory_List[source_folder_index][k] = this->Directory_List[i][k];
                }

                this->Source_File_Directory_List[source_folder_index][directory_name_size] = '\0';

                this->Source_File_Directory_List[source_folder_index];

                source_folder_index++;
             }
         }
     }
}

int Project_Directory_Lister::Get_SourceFile_Directory_Number(){

    return this->Source_File_Directory_Number;
}

char * Project_Directory_Lister::Get_Source_File_Directory(int num){

       return this->Source_File_Directory_List[num];
}
