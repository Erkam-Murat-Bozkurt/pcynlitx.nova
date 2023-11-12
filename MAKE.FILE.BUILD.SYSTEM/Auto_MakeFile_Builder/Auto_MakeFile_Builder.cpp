

#include "Auto_MakeFile_Builder.h"

Auto_MakeFile_Builder::Auto_MakeFile_Builder(char * DesPath, char opr_sis) 
{
     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;

     for(int i=0;i<32;i++){

         this->Mk_Builder[i].Receive_Operating_System(opr_sis);
     }

     this->Mk_Dir_Constructor.Receive_Operating_System(opr_sis);
}


Auto_MakeFile_Builder::~Auto_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Auto_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(&this->repo_obj_dir);

         this->DataMap.clear();

         for(int i=0;i<32;i++){

            this->Mk_Builder[i].Clear_Dynamic_Memory();
         }
     }
}


void Auto_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Warehouse_Path = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader->Get_Repo_Directory_Location();

     for(int i=0;i<32;i++){

         this->Mk_Builder[i].Receive_Descriptor_File_Reader(ptr);      
     }

     this->Mk_Dir_Constructor.Receive_Descriptor_File_Reader(ptr);
}


void Auto_MakeFile_Builder::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->Dep_Determiner = dep_ptr;

     for(int i=0;i<32;i++){

         this->Mk_Builder[i].Receive_Compiler_Data_Pointer(dep_ptr->Get_Compiler_Data_Address());      
     }

     this->Mk_Dir_Constructor.Receive_Compiler_Data_Pointer(dep_ptr->Get_Compiler_Data_Address());
}



void Auto_MakeFile_Builder::Build_Make_Files(){

     // Determination of the directories recorded on the git repo

     this->Mk_Dir_Constructor.Collect_Directory_Info();

     this->Mk_Dir_Constructor.Construct_MakeFile_Directories();

     this->Determine_Project_Directories();

     this->Compiler_Data_Pointer = this->Dep_Determiner->Get_Compiler_Data_Address();

     this->Compiler_Data_Pointer->shrink_to_fit();

     this->Perform_Data_Map_Construction();

     this->Perform_MakeFile_Construction();

     std::cout << "\n";

     std::cout << "\n\e[1;32mThe new makefiles have been constructed..\e[0m";
     std::cout << "\n";     
}


void Auto_MakeFile_Builder::Perform_MakeFile_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     if(data_size>32){

       int division = data_size/32;

       for(int i=0;i<32;i++){

           int str  = i*division;

           int end  = (i+1)*division;

           if(i==31){
            
               end = data_size;
           }

           this->threads[i] 
                
                = std::thread(Auto_MakeFile_Builder::Write_MakeFiles,this,i,str,end);     
       }
    
       for(int i=0;i<32;i++){
     
          this->threads[i].join();
       }
     }
     else{

          this->Write_MakeFiles(0,0,data_size);
     }
}


void Auto_MakeFile_Builder::Perform_Data_Map_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     for(size_t i=0;i<data_size;i++){

         std::string source_file_path= this->Compiler_Data_Pointer->at(i).source_file_path;

         this->DataMap.insert(std::make_pair(source_file_path,this->Compiler_Data_Pointer->at(i)));
     }

     for(size_t i=0;i<32;i++){

         this->Mk_Builder[i].Receive_DataMap(&this->DataMap);
     }
}


void Auto_MakeFile_Builder::Write_MakeFiles(int thr_num, int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);
     
     mt.unlock();


     for(size_t i=start;i<end;i++){

         std::string source_file_path = this->Compiler_Data_Pointer->at(i).source_file_path;

         mt.lock();
         
         this->Mk_Builder[thr_num].Build_MakeFile(source_file_path);

         mt.unlock();

         this->Mk_Builder[thr_num].Clear_Dynamic_Memory();
     }
}



void Auto_MakeFile_Builder::Determine_Project_Directories(){

     this->Memory_Delete_Condition = false;

     std::string Objects_Folder = "OBJECT.FILES";

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