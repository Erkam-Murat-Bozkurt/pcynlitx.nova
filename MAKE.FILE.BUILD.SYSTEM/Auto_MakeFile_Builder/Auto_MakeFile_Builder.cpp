

#include "Auto_MakeFile_Builder.h"

Auto_MakeFile_Builder::Auto_MakeFile_Builder(char * DesPath, char opr_sis) :
   
   Mk_Builder(DesPath,opr_sis), Mk_File_Clnr(DesPath,opr_sis), Des_Reader(DesPath)
{
     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;

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


void Auto_MakeFile_Builder::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->Dep_Determiner = dep_ptr;

     this->Mk_Builder.Receive_Compiler_Data_Pointer(dep_ptr->Get_Compiler_Data_Address());
}

void Auto_MakeFile_Builder::Build_Make_Files(){

     // Determination of the directories recorded on the git repo

     this->Mk_File_Clnr.Clear_Make_Files_Exist_On_Repo();
    
     std::cout << "\n\e[1;32mThe current make files on the project have been cleaned..\e[0m\n";

     this->Determine_Project_Directories();

     std::vector<Compiler_Data> * Com_Data = this->Dep_Determiner->Get_Compiler_Data_Address();

     Com_Data->shrink_to_fit();

     size_t data_size = Com_Data->size();
    
     
     for(size_t i=0;i<data_size;i++){

         std::string source_file_name = Com_Data->at(i).source_file_name;


         this->Mk_Builder.Build_MakeFile(source_file_name);

         std::cout << "\n\e[0;37m[\e[1;32m+\e[0m] Target make file: [\e[0;33m " << source_file_name << ".make \e[0m]";
         std::cout << "\n\n    The construction complated.";
         std::cout << "\n\n";

         this->Mk_Builder.Clear_Dynamic_Memory();
     }


     std::cout << "\n";

     std::cout << "\n\e[1;32mThe new makefiles have been constructed..\e[0m";
     std::cout << "\n";

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