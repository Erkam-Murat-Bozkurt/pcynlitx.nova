
#include "Project_Src_Code_Rdr.hpp"


Project_Src_Code_Rdr::Project_Src_Code_Rdr(char opr_sis)
{
   this->Memory_Delete_Condition = false;
   this->opr_sis = opr_sis;


   this->Hdr_Determiner = new Header_File_Determiner * [16];
   this->Src_Determiner = new Source_File_Determiner * [16];

   for(int i=0;i<16;i++){
   
       this->Hdr_Determiner[i] = new Header_File_Determiner(opr_sis);

       this->Src_Determiner[i] = new Source_File_Determiner;
   }

   for(int i=0;i<16;i++){
   
       this->FileManager->Receive_Operating_System(opr_sis);
   }
}


Project_Src_Code_Rdr::~Project_Src_Code_Rdr(){

    if(!this->Memory_Delete_Condition){
    
        this->Clear_Object_Memory();       
    }   
}




void Project_Src_Code_Rdr::Receive_Git_Data_Processor(Git_Data_Processor * ptr)
{
     this->Git_Data_Proc = ptr;

     for(int i=0;i<16;i++){
   
         this->Hdr_Determiner[i]->Receive_Git_Data_Processor(ptr);
     }

     this->root_directory = this->Git_Data_Proc->Get_Git_Repo_Directory();
}



void Project_Src_Code_Rdr::Receive_File_Paths(){
  
     size_t file_number = this->Git_Data_Proc->Get_Git_File_Index_Size();

     for(int i=0;i<file_number;i++){

         std::string file_sys_path = this->Git_Data_Proc->Get_File_System_Path(i);

         this->FilePaths.push_back(file_sys_path);
     }

     this->FilePaths.shrink_to_fit();
}



void Project_Src_Code_Rdr::Read_Project_Source_Code_Files(){

     this->Receive_File_Paths();

     size_t repo_size = this->FilePaths.size();      

     if(repo_size >= 16){
     
        int division = repo_size/16;
        
        for(int i=0;i<16;i++){

            int str  = i*division;

            int end  = (i+1)*division;

            if(i==15){

                end = repo_size;
            }

            this->threads[i] = std::thread(Project_Src_Code_Rdr::Read_Source_Code,this,i,str,end);     
        }
    
        for(int i=0;i<16;i++){
     
            this->threads[i].join();
        }

     }else{
     
           this->Read_Source_Code_Single_Thread();
     }

     this->Src_Code_Dt.shrink_to_fit();
     
     this->Clear_Thread_Objects_Memory();
}


void Project_Src_Code_Rdr::Read_Source_Code(int trn, int start_point, int end_point){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();

     
     for(int i=start_point;i<end_point;i++){
     
         std::string file_sys_path = this->FilePaths.at(i);

         bool is_header   = this->Hdr_Determiner[trn]->Is_Header(file_sys_path);

         bool is_src_file = this->Src_Determiner[trn]->Is_Source_File(file_sys_path);


         if(is_header || is_src_file){
                             
            FileData Temp;

            Temp.sys_path = file_sys_path;

            this->FileManager[trn].Read_File(file_sys_path);

            int FileSize = this->FileManager[trn].GetFileSize();

            for(int k=0;k<FileSize;k++){
         
                std::string string_line = this->FileManager[trn].GetFileLine(k);

                this->Delete_Spaces_on_String(&string_line);

                Temp.FileContent.push_back(string_line);
            }

            Temp.FileContent.shrink_to_fit();

            this->FileManager[trn].Clear_Dynamic_Memory();


            this->Determine_File_Name(file_sys_path,Temp.file_name);

            this->Determine_File_Combined_Name(file_sys_path,Temp.combined_file_name);
                        
    
            mt.lock();

            this->Src_Code_Dt.push_back(Temp);
        
            this->CodeBase.insert(std::make_pair(this->Src_Code_Dt.back().sys_path,&this->Src_Code_Dt.back()));
            
            this->CodeBase_Name.insert(std::make_pair(this->Src_Code_Dt.back().file_name,&this->Src_Code_Dt.back()));

            this->CodeBase_Combined_Name.insert(std::make_pair(this->Src_Code_Dt.back().combined_file_name,
            
                    &this->Src_Code_Dt.back()));

            mt.unlock();


            this->Clear_Vector_Memory(&Temp.FileContent);

            this->Clear_String_Memory(&Temp.sys_path);

            this->Clear_String_Memory(&Temp.file_name);

            this->Clear_String_Memory(&Temp.combined_file_name);

         }
     }
}

void Project_Src_Code_Rdr::Read_Source_Code_Single_Thread(){

     for(size_t i=0;i<this->FilePaths.size();i++){
     
         std::string file_sys_path = this->FilePaths.at(i);

         bool is_header   = this->Hdr_Determiner[0]->Is_Header(file_sys_path);

         bool is_src_file = this->Src_Determiner[0]->Is_Source_File(file_sys_path);

         if(is_header || is_src_file){
                             
            FileData Temp;

            Temp.sys_path = file_sys_path;

            this->FileManager[0].Read_File(file_sys_path);

            int FileSize = this->FileManager[0].GetFileSize();

            for(int k=0;k<FileSize;k++){
         
                std::string string_line = this->FileManager[0].GetFileLine(k);

                this->Delete_Spaces_on_String(&string_line);

                Temp.FileContent.push_back(string_line);
            }

            
            this->Determine_File_Name(file_sys_path,Temp.file_name);

            this->Determine_File_Combined_Name(file_sys_path,Temp.combined_file_name);


            Temp.FileContent.shrink_to_fit();

            this->Src_Code_Dt.push_back(Temp);


            this->CodeBase.insert(std::make_pair(file_sys_path,&this->Src_Code_Dt.back()));
            
            this->CodeBase_Name.insert(std::make_pair(Temp.file_name,&this->Src_Code_Dt.back()));

            this->CodeBase_Combined_Name.insert(std::make_pair(Temp.combined_file_name,&this->Src_Code_Dt.back()));


            this->Clear_Vector_Memory(&Temp.FileContent);

            this->Clear_String_Memory(&Temp.sys_path);
         }
     }

     this->Clear_Thread_Objects_Memory();    
}



void Project_Src_Code_Rdr::Delete_Spaces_on_String(std::string * str){

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


void Project_Src_Code_Rdr::Determine_File_Name(std::string path, std::string & file_name){

     this->Clear_String_Memory(&file_name);

     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;


     for(size_t i=file_path_size;i>0;i--){

        if((path[i] == '/') || (path[i] == '\\')){

          break;
        }
        else{

            dir_size--;
        }
     }

     size_t file_name_size = file_path_size - dir_size;

     int index = 0;

     for(size_t i=dir_size+1;i<file_path_size;i++){

         file_name.push_back(path[i]);
     }
}

void Project_Src_Code_Rdr::Determine_File_Combined_Name(std::string path, std::string & file_name){

     this->Clear_String_Memory(&file_name);

     size_t file_path_size = path.length();

     size_t upper_dir_size = file_path_size;

     size_t root_dir_size  = this->root_directory.length(); 

     
     int dir_counter = 0;

     for(size_t i=file_path_size;i>root_dir_size;i--){

        if((path[i] == '/') || (path[i] == '\\')){

           dir_counter++;

           if(dir_counter>1){

              break;
           }  
           else{

                 upper_dir_size--;
           }      
        }
        else{

            upper_dir_size--;
        }
     }

     size_t file_name_size = file_path_size - upper_dir_size;

     int index = 0;

     for(size_t i=upper_dir_size+1;i<file_path_size;i++){

         file_name.push_back(path[i]);
     }
}


const std::vector<std::string> * Project_Src_Code_Rdr::Get_File_Content(int i) const
{    
     return &this->Src_Code_Dt.at(i).FileContent;
}

std::string Project_Src_Code_Rdr::Get_File_Path(int i) const {

     return this->Src_Code_Dt.at(i).sys_path;
}

std::string Project_Src_Code_Rdr::Get_File_Name(int i) const {

     return this->Src_Code_Dt.at(i).file_name;
}


const FileData * Project_Src_Code_Rdr::Find_File_Data_From_Path(std::string path) const
{
    try {        

         return  this->CodeBase.at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Path,";

         std::cout << "\n the file located on " << path << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


const  FileData * Project_Src_Code_Rdr::Find_File_Data_From_Name(std::string name) const
{
    try {        

         return this->CodeBase_Name.at(name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Name,";

         std::cout << "\n the file located on " << name << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


const FileData * Project_Src_Code_Rdr::Find_File_Data_From_Combined_Name(std::string combined_name) const
{
    try {        

         return this->CodeBase_Combined_Name.at(combined_name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Combined_Name,";

         std::cout << "\n the file located on " << combined_name << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


bool Project_Src_Code_Rdr::Is_This_Repo_File(std::string path){

     bool is_this_repo_file = false;

     if(this->CodeBase.find(path)!=this->CodeBase.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}


bool Project_Src_Code_Rdr::Check_Repo_File_Status(std::string name){

     bool is_this_repo_file = false;

     if(this->CodeBase_Name.find(name)!=this->CodeBase_Name.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}


bool Project_Src_Code_Rdr::Check_Repo_File_Status_From_Combined_File_Name(std::string combined_name){
     
     bool is_this_repo_file = false;

     if(this->CodeBase_Combined_Name.find(combined_name)!=this->CodeBase_Combined_Name.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}



const std::vector<std::string> * Project_Src_Code_Rdr::Get_File_Content_From_Path( std::string path) const 
{
     const FileData * ptr = this->Find_File_Data_From_Path(path);

     return &ptr->FileContent;
}


size_t Project_Src_Code_Rdr::Get_Project_Files_Number() const
{

       return this->Src_Code_Dt.size();
}












/*  THE MEMORY MANAGEMENT FUNCTIONS  ------------------------------------- */


void Project_Src_Code_Rdr::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){
     
         this->Memory_Delete_Condition = true;

         this->Clear_Dynamic_Memory();

     }
}


void Project_Src_Code_Rdr::Clear_Dynamic_Memory(){
     
     std::vector<FileData>::iterator it;

     for(auto it=this->Src_Code_Dt.begin();it<this->Src_Code_Dt.end();it++){
       
         this->Clear_Vector_Memory(&it->FileContent);
         this->Clear_String_Memory(&it->sys_path);
         this->Clear_String_Memory(&it->file_name);
         this->Clear_String_Memory(&it->combined_file_name);
     }

     this->Src_Code_Dt.clear();

     this->Src_Code_Dt.shrink_to_fit();


     this->CodeBase.clear();

     this->CodeBase_Name.clear();

     this->CodeBase_Combined_Name.clear();
}



void Project_Src_Code_Rdr::Clear_Thread_Objects_Memory(){

     for(int i=0;i<16;i++){
     
         if(this->Hdr_Determiner[i] != nullptr){
              
            delete this->Hdr_Determiner[i];

            this->Hdr_Determiner[i] = nullptr;
         }             
     }
         
     delete [] this->Hdr_Determiner;

     this->Hdr_Determiner = nullptr;
     
     
     for(int i=0;i<16;i++){

         if(this->Src_Determiner[i]!= nullptr){

            delete this->Src_Determiner[i];

            this->Src_Determiner[i] = nullptr;
         }                 
     }

     delete [] this->Src_Determiner;

     this->Src_Determiner = nullptr;


     for(int i=0;i<16;i++){

        this->FileManager[i].Clear_Dynamic_Memory();
     }

     this->Clear_Vector_Memory(&this->FilePaths);
}


void Project_Src_Code_Rdr::Clear_Vector_Memory(std::vector<std::string> * pointer){

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

void Project_Src_Code_Rdr::Clear_String_Memory(std::string * ptr){

    if(!ptr->empty()){
    
        ptr->clear();

        ptr->shrink_to_fit();
    }
}