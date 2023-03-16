
#include "Project_Src_Code_Rdr.hpp"


Project_Src_Code_Rdr::Project_Src_Code_Rdr(char * DesPath, char opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->Hdr_Determiner = new Header_File_Determiner * [8];
   this->Src_Determiner = new Source_File_Determiner * [8];

   for(int i=0;i<8;i++){
   
       this->Hdr_Determiner[i] = new Header_File_Determiner(DesPath,opr_sis);
       this->Src_Determiner[i] = new Source_File_Determiner;
   }   

   this->fptr = &Project_Src_Code_Rdr::Read_Source_Code;
}


Project_Src_Code_Rdr::~Project_Src_Code_Rdr(){

    if(!this->Memory_Delete_Condition){
    
        this->Clear_Object_Memory();       
    }   
}

void Project_Src_Code_Rdr::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){
     
         this->Memory_Delete_Condition = true;

         this->Clear_Dynamic_Memory();

         for(int i=0;i<8;i++){
     
             delete this->Hdr_Determiner[i];
         }

         delete [] this->Hdr_Determiner;

     
         for(int i=0;i<8;i++){
     
             delete this->Src_Determiner[i];
         }

         delete [] this->Src_Determiner;
     }
}

void Project_Src_Code_Rdr::Clear_Dynamic_Memory(){
     
     std::vector<FileData>::iterator it;

     for(auto it=this->Src_Code_Dt.begin();it<this->Src_Code_Dt.end();it++){
       
         this->Clear_Vector_Memory(&it->FileContent);
         this->Clear_String_Memory(&it->sys_path);
     }

     this->Src_Code_Dt.clear();

     this->Src_Code_Dt.shrink_to_fit();
}

void Project_Src_Code_Rdr::Receive_Git_Repo_Information(Git_File_List_Receiver * ptr){

     this->Git_Data_Ptr = ptr;
}


void Project_Src_Code_Rdr::Receive_File_Paths(){
  
     size_t file_number = this->Git_Data_Ptr->Get_Git_File_Index_Size();

     for(int i=0;i<file_number;i++){

         std::string file_sys_path = this->Git_Data_Ptr->Get_File_System_Path(i);

         this->FilePaths.push_back(file_sys_path);
     }

     this->FilePaths.shrink_to_fit();
}

void Project_Src_Code_Rdr::Read_Project_Source_Code_Files(){

     this->Receive_File_Paths();

     size_t repo_size = this->FilePaths.size();      

     if(repo_size >= 8){
     
        int division = repo_size/8;
        
        for(int i=0;i<8;i++){

            int str  = i*division;

            int end  = (i+1)*division;
                 
            this->threads[i] = std::thread(Project_Src_Code_Rdr::Read_Source_Code,this,i,str,end);     
        }
    
        for(int i=0;i<8;i++){
     
            this->threads[i].join();
        }

     }else{
     
           this->Read_Source_Code_Single_Thread();
     }

     this->Src_Code_Dt.shrink_to_fit();
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

                Temp.FileContent.push_back(string_line);
            }

            Temp.FileContent.shrink_to_fit();


            mt.lock();

            this->Src_Code_Dt.push_back(Temp);    

            this->Clear_Vector_Memory(&Temp.FileContent);

            this->Clear_String_Memory(&Temp.sys_path);

            mt.unlock();
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

                Temp.FileContent.push_back(string_line);
            }

            Temp.FileContent.shrink_to_fit();

            this->Src_Code_Dt.push_back(Temp);    

            this->Clear_Vector_Memory(&Temp.FileContent);

            this->Clear_String_Memory(&Temp.sys_path);
         }
     } 
}


std::vector<std::string> * Project_Src_Code_Rdr::Get_File_Content(int i)
{    
     return &this->Src_Code_Dt.at(i).FileContent;
}

std::string Project_Src_Code_Rdr::Get_File_Path(int i){

     return this->Src_Code_Dt.at(i).sys_path;

}

size_t Project_Src_Code_Rdr::Get_Project_Files_Number(){

       return this->Src_Code_Dt.size();
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