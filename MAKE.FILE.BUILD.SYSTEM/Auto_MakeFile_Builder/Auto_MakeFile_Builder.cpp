

#include "Auto_MakeFile_Builder.h"

Auto_MakeFile_Builder::Auto_MakeFile_Builder(char * DesPath, char opr_sis) :
   
   File_Lister(DesPath,opr_sis),  Mk_Builder(DesPath,opr_sis), 
   Mk_File_Clnr(DesPath,opr_sis), Des_Reader(DesPath)
{
     this->Memory_Delete_Condition = true;

     this->opr_sis;

     this->File_Lister.Determine_Git_Repo_Info();

     this->Des_Reader.Read_Descriptor_File();

     this->Warehouse_Path = this->Des_Reader.Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader.Get_Repo_Directory_Location();
}

Auto_MakeFile_Builder::~Auto_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Auto_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(&this->repo_head_dir);

         this->Clear_String_Memory(&this->repo_obj_dir);
     }
}


void Auto_MakeFile_Builder::Build_Make_Files(){

     // Determination of the directories recorded on the git repo

     this->Mk_File_Clnr.Clear_Make_Files_Exist_On_Repo();

     std::cout << "\n\e[1;32mThe current make files on the project have been cleaned..\e[0m\n";
     sleep(0.5);

     this->Determine_Project_Directories();


     int src_num = this->File_Lister.Get_Source_File_Number();



     for(int i=0;i<src_num;i++){

         std::string source_file_name = this->File_Lister.Get_Source_File_Name(i);

         if(!source_file_name.empty()){

            this->Mk_Builder.Build_MakeFile(i);

            std::cout << "\n\e[0;37m[\e[1;32m+\e[0m] Target make file: [\e[0;33m " << source_file_name << ".make \e[0m]";
            std::cout << "\n\n    The construction complated.";
            std::cout << "\n\n";

            sleep(0.5);
         }
     }

     std::cout << "\n";

     std::cout << "\n\e[1;32mThe new makefiles have been constructed..\e[0m";
     std::cout << "\n";

     sleep(0.5);
}

void Auto_MakeFile_Builder::Determine_Project_Directories(){

     this->Memory_Delete_Condition = false;

     std::string Headers_Folder = "PROJECT.HEADER.FILES";

     std::string Objects_Folder = "PROJECT.OBJECT.FILES";

     this->Construct_Path(&(this->repo_head_dir),Headers_Folder,this->Warehouse_Path);

     this->Construct_Path(&(this->repo_obj_dir),Objects_Folder,this->Warehouse_Path);
}

void Auto_MakeFile_Builder::Construct_Path(std::string * pointer, std::string string, 

     std::string warehouse_path){

     int index = 0;

     size_t warehouse_path_size = warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         pointer->push_back(warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){
      
        if(pointer->back() != '\\'){
         
           pointer->push_back('\\');         
        }      
     }
     else{
      
          if(this->opr_sis == 'l'){
           
            if(pointer->back() != '/'){
         
               pointer->push_back('/');         
            }      
         }      
     }

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         pointer->push_back(string[i]);
     }
}


void Auto_MakeFile_Builder::Clear_Vector_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();
            it->shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void Auto_MakeFile_Builder::Clear_String_Memory(std::string * ptr)
{
     if(!ptr->empty()){

         ptr->clear();

         ptr->shrink_to_fit();
     }
}