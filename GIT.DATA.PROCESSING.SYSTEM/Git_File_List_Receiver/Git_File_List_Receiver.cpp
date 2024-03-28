



#include "Git_File_List_Receiver.hpp"


Git_File_List_Receiver::Git_File_List_Receiver(char opr_sis) : FileManager(opr_sis)
{
    this->opr_sis = opr_sis;

    this->Initialize_Mermbers();
}


Git_File_List_Receiver::~Git_File_List_Receiver()
{
   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_File_List_Receiver::Initialize_Mermbers()
{
     this->Memory_Delete_Condition = false;
     this->File_Line_Number = 0;
}


void Git_File_List_Receiver::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Vector_Memory(&this->File_List_Content);

         this->Clear_Vector_Memory(&this->File_System_Paths);

         this->Clear_Vector_Memory(&this->Git_Record_Directories);

         this->Clear_Vector_Memory(&this->File_Names);

         this->Clear_Vector_Memory(&this->Git_Record_Paths);

         this->Clear_String_Memory(&this->Warehouse);

         this->Clear_String_Memory(&this->Repo_Dir);

         this->Clear_String_Memory(&this->git_file_list_path);

         this->FileManager.Clear_Dynamic_Memory();
     }
}


void Git_File_List_Receiver::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;    
}


void Git_File_List_Receiver::Determine_Git_Repo_Info()
{
     this->Memory_Delete_Condition = false;

     this->Warehouse = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir  = this->Des_Reader->Get_Repo_Directory_Location();

     this->Determine_Git_File_List_Path();

     this->Read_Repo_List_File();

     this->Determine_File_System_Paths();

     this->Determine_Git_Record_Directories();

     this->Determine_Git_Record_Paths();

     this->Determine_File_Names();
}


void Git_File_List_Receiver::Determine_Git_File_List_Path()
{
     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     size_t warehouse_path_size = this->Warehouse.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->git_file_list_path.push_back(this->Warehouse[i]) ;
     }

     if(this->opr_sis == 'w'){

       if(this->Warehouse[warehouse_path_size-1] != '\\'){

          this->git_file_list_path.push_back('\\') ;
       }
     }

     if(this->opr_sis == 'l'){

         if(this->Warehouse[warehouse_path_size-1] != '/'){

            this->git_file_list_path.push_back('/') ;
         }
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_file_list_path.push_back(repo_list_file_name[i]) ;
     }
}


void Git_File_List_Receiver::Read_Repo_List_File()
{
     this->Memory_Delete_Condition = false;

     this->File_Line_Number = 0;

     this->FileManager.SetFilePath(this->git_file_list_path);

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          std::string file_line = this->FileManager.ReadLine();

          if(file_line.length()>0){
          
             this->File_List_Content.push_back(file_line);

             this->File_Line_Number++;
          }

          file_line.clear();

          file_line.shrink_to_fit();

     }while(!this->FileManager.Control_Stop_Condition());

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();



     if(this->opr_sis = 'w'){

        this->Convert_Windows_Paths();
     }
}


void Git_File_List_Receiver::Convert_Windows_Paths(){

     size_t list_size = this->File_List_Content.size();

     for(size_t i=0;i<list_size;i++){

         size_t path_size = this->File_List_Content[i].size();

         for(size_t k=0;k<path_size;k++){

             if(this->File_List_Content[i][k] == '/'){

                this->File_List_Content[i][k] = '\\';
             }
         }
     }
}


void Git_File_List_Receiver::Determine_File_System_Paths(){

     size_t list_size = this->File_List_Content.size();    

     for(size_t i=0;i<list_size;i++){

         std::string temp;

         temp+=this->Repo_Dir;
      
         if(this->opr_sis == 'w'){

            if(temp[temp.size()]!= '\\'){

               temp.push_back('\\');
            }
         }

         if(this->opr_sis == 'l'){

            if(temp[temp.size()] != '/'){

               temp.push_back('/');
             }
         }


         temp+=this->File_List_Content[i];

         this->File_System_Paths.push_back(temp);

         temp.clear();

         temp.shrink_to_fit();
     }

     this->File_System_Paths.shrink_to_fit();
}



void Git_File_List_Receiver::Determine_Git_Record_Directories(){

     size_t list_size = this->File_List_Content.size();
    
     for(size_t i=0;i<list_size;i++){

         size_t string_length = this->File_List_Content[i].length();

         size_t end_point = string_length;

         for(size_t k=string_length-1;k>0;k--){
         
             if(this->opr_sis == 'w'){

                if(this->File_List_Content[i].at(k) == '\\'){
                
                   end_point--;

                   break;                
                }
                else{
                
                   end_point--;
                }
             }
             else{
                          
                if(this->File_List_Content[i].at(k) == '/'){
                
                   end_point--;

                   break;                
                }
                else{
                
                   end_point--;
                }                         
             }
         }

         std::string dir;

         if(end_point == 1){
         
            dir.clear();

            dir.shrink_to_fit();
         }
         else{
         
              for(size_t k=0;k<end_point;k++){
         
                  dir.push_back(this->File_List_Content[i].at(k));
              }
         }
                  
         this->Git_Record_Directories.push_back(dir);
         
         dir.clear();

         dir.shrink_to_fit();
     }

     this->Git_Record_Directories.shrink_to_fit();
}


void Git_File_List_Receiver::Determine_File_Names(){

     size_t list_size = this->File_List_Content.size();
    
     for(size_t i=0;i<list_size;i++){

         size_t string_length = this->File_List_Content[i].length();

         size_t start_point = string_length;

         for(size_t k=string_length-1;k>0;k--){
         
             if(this->opr_sis == 'w'){

                if(this->File_List_Content[i].at(k) == '\\'){
                
                   break;                
                }
                else{
                
                   start_point--;
                }
             }
             else{
                          
                if(this->File_List_Content[i].at(k) == '/'){
                
                   break;                
                }
                else{
                
                   start_point--;
                }                         
             }
         }

        if(start_point == 1){
        
           start_point = 0;
        }

         std::string name;

         for(size_t k=start_point;k<string_length;k++){
         
             name.push_back(this->File_List_Content[i].at(k));
         }

         this->File_Names.push_back(name);
         
         name.clear();

         name.shrink_to_fit();
     }

     this->File_Names.shrink_to_fit();
}




void Git_File_List_Receiver::Determine_Git_Record_Paths(){

     size_t list_size = this->File_List_Content.size();
    
     for(size_t i=0;i<list_size;i++){

         size_t string_length = this->File_List_Content[i].length();

         std::string dir;

         for(size_t k=0;k<string_length;k++){
         
             dir.push_back(this->File_List_Content[i].at(k));
         }

         this->Git_Record_Paths.push_back(dir);
         
         dir.clear();

         dir.shrink_to_fit();
     }

     this->Git_Record_Paths.shrink_to_fit();
}



void Git_File_List_Receiver::Delete_Spaces_on_String(std::string * str){

    size_t string_size = str->length();

    bool search_cond = true;

    do{

      search_cond = false;

      for(size_t i=0;i<str->length();i++){

          if((*str)[i] == ' '){

            search_cond = true;

            str->erase(i,1);
          }
        }

    }while(search_cond);
}


void Git_File_List_Receiver::Clear_Vector_Memory(std::vector<std::string> * pointer){

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


void Git_File_List_Receiver::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}


std::string Git_File_List_Receiver::Get_File_System_Path(int num){

     return this->File_System_Paths[num];
}


std::string Git_File_List_Receiver::Get_Git_File_Index(int num)
{
      return this->File_List_Content[num];
}

std::string Git_File_List_Receiver::Get_Git_Repo_Directory(){

       return this->Repo_Dir;
}

size_t Git_File_List_Receiver::Get_Git_File_Index_Size(){

    return this->File_System_Paths.size();
}


std::string Git_File_List_Receiver::Get_Git_Record_Directory(int num){
 
      return this->Git_Record_Directories[num];
}

std::string Git_File_List_Receiver::Get_Git_Record_Path(int num){
 
      return this->Git_Record_Paths[num];
}

std::string Git_File_List_Receiver::Get_File_Name(int num){
 
      return this->File_Names[num];    
}


 std::vector<std::string> * Git_File_List_Receiver::Get_Git_File_Index_Address(){
 
      return &this->File_List_Content;
 }
 
 
 std::vector<std::string> * Git_File_List_Receiver::Get_File_System_Path_Address(){
 
      return &this->File_System_Paths;
 }
 
 
 std::vector<std::string> * Git_File_List_Receiver::Get_Git_Record_Directory_Address(){
 
      return &this->Git_Record_Directories;
 }
 
 
 std::vector<std::string> * Git_File_List_Receiver::Get_Git_Record_Path_Address(){
 
      return &this->Git_Record_Paths;
 }
 
 
 std::vector<std::string> * Git_File_List_Receiver::Get_File_Name_Address(){
 
      return &this->File_Names;    
 }