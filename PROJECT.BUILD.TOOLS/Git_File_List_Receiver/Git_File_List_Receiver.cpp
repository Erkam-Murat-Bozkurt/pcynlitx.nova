

#include "Git_File_List_Receiver.hpp"

Git_File_List_Receiver::Git_File_List_Receiver(char * DesPath) :

  Des_Reader(DesPath), DirectoryManager(DesPath)

{
    this->Initialize_Mermbers();

    this->Des_Reader.Read_Descriptor_File();

    this->Warehouse = this->Des_Reader.Get_Warehouse_Location();

    this->Repo_Dir  = this->Des_Reader.Get_Repo_Directory_Location();
}

Git_File_List_Receiver::Git_File_List_Receiver(std::string DesPath) :

  Des_Reader(DesPath), DirectoryManager(DesPath)

{
    this->Initialize_Mermbers();

    this->Des_Reader.Read_Descriptor_File();

    this->Warehouse = this->Des_Reader.Get_Warehouse_Location();

    this->Repo_Dir  = this->Des_Reader.Get_Repo_Directory_Location();
}


Git_File_List_Receiver::~Git_File_List_Receiver(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Git_File_List_Receiver::Initialize_Mermbers(){

     this->Memory_Delete_Condition = true;

     this->File_Line_Number = 0;

     this->CString = nullptr;
}

void Git_File_List_Receiver::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(!this->File_List_Content.empty()){

           this->File_List_Content.clear();
         }

         this->FileManager.Clear_Dynamic_Memory();

         if(this->CString != nullptr){

             delete [] this->CString;

             this->CString = nullptr;
         }
     }
}

void Git_File_List_Receiver::Determine_Git_Repo_Info(){

     this->Determine_Git_File_List_Path();

     this->Determine_Git_Listing_Command();

     this->List_Files_in_Repo();

     this->Read_Repo_List_File();
}

void Git_File_List_Receiver::Determine_Git_File_List_Path(){

     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     size_t warehouse_path_size = this->Warehouse.length();

     this->git_file_list_path = "";


     for(size_t i=0;i<warehouse_path_size;i++){

         this->git_file_list_path.append(1,this->Warehouse[i]) ;
     }


     if(this->Warehouse[warehouse_path_size-1] != '\\'){

        this->git_file_list_path.append(1,'\\') ;
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_file_list_path.append(1,repo_list_file_name[i]) ;
     }

     this->git_file_list_path.append(1,'\0') ;
}


void Git_File_List_Receiver::Determine_Git_Listing_Command(){

     char git_command [] = "git ls-files > ";

     size_t git_command_size = strlen(git_command);

     size_t target_file_path_size = this->git_file_list_path.length();


     this->git_listing_command = "";

     for(size_t i=0;i<git_command_size;i++){

         this->git_listing_command.append(1,git_command[i]) ;
     }

     for(size_t i=0;i<target_file_path_size;i++){

         this->git_listing_command.append(1,this->git_file_list_path[i]);
     }

     this->git_listing_command.append(1,'\0') ;
}

void Git_File_List_Receiver::List_Files_in_Repo(){

     char * path = this->From_Std_String_To_Char(this->git_file_list_path);

     if(this->FileManager.Is_Path_Exist(path)){

        this->FileManager.Delete_File(path);
     }

     char * repo_dir = this->From_Std_String_To_Char(this->Repo_Dir);


     this->DirectoryManager.ChangeDirectory(repo_dir);

     int system_return_value = system(this->git_listing_command.c_str());
}

void Git_File_List_Receiver::Read_Repo_List_File(){

     this->Memory_Delete_Condition = false;

     this->File_Line_Number = 0;

     this->FileManager.SetFilePath(this->git_file_list_path);

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          std::string file_line = this->FileManager.Read();

          this->File_List_Content.push_back(file_line);

          this->File_Line_Number++;

     }while(!this->FileManager.Control_Stop_Condition());

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();
}


char * Git_File_List_Receiver::From_Std_String_To_Char(std::string str){

       if(this->CString != nullptr){

           delete [] this->CString;

           this->CString = nullptr;
       }

       size_t size = str.length();

       int index = 0;

       this->CString = new char [5*size];

       for(size_t i=0;i<5*size;i++){

           this->CString[i] = '\0';
       }

       for(size_t i=0;i<size;i++){

           this->CString[index] = str[i];

           index++;
       }

       this->CString[index] = '\0';

       return this->CString;
}

std::string Git_File_List_Receiver::Get_Git_File_Index(int num){

      return this->File_List_Content[num];
}

std::string Git_File_List_Receiver::Get_Git_Repo_Directory(){

       return this->Repo_Dir;
}

int Git_File_List_Receiver::Get_Git_File_Index_Size(){

    return this->File_Line_Number;
}
