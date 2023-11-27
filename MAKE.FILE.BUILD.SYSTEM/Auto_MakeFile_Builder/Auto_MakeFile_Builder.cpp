

#include "Auto_MakeFile_Builder.h"

Auto_MakeFile_Builder::Auto_MakeFile_Builder(char * DesPath, char opr_sis) 
{
     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;

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

         this->Clear_String_Memory(this->repo_obj_dir);

         this->Clear_String_Memory(this->Warehouse_Path);

         this->Clear_String_Memory(this->Repo_Dir);

         this->Mk_Dir_Constructor.Clear_Dynamic_Memory();

         this->DataMap.clear();
     }
}


void Auto_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Warehouse_Path = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader->Get_Repo_Directory_Location();

     this->Mk_Dir_Constructor.Receive_Descriptor_File_Reader(ptr);
}


void Auto_MakeFile_Builder::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->Dep_Determiner = dep_ptr;

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


void Auto_MakeFile_Builder::Construct_For_Large_Data_Set(size_t data_size){

     size_t str=0, end=0;

     size_t thread_num = data_size/50;

     if(thread_num > 200){

        thread_num = 200;
     }

     size_t remaining_job = 0;

     size_t range = this->Split_Range(data_size,thread_num,remaining_job);


     for(int i=0;i<thread_num;i++){

         if(i==0){

            str = 0;

            end = range;
         }
         else{

            str  = end;

            end  = end + range;

            if(remaining_job > 0){

               end = end+1;

               remaining_job--;
            }
         }

         if(i==(thread_num-1)){
            
               end = data_size;
         }

         this->threadPool.push_back(std::thread(Auto_MakeFile_Builder::Write_MakeFiles,this,str,end));
     }
    
     for(size_t i=0;i<thread_num;i++){
            
         this->threadPool[i].join();
     }
}

void Auto_MakeFile_Builder::Construct_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(Auto_MakeFile_Builder::Write_MakeFiles,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }
}

void Auto_MakeFile_Builder::Construct_For_Small_Data_Set(size_t data_size){

     this->Write_MakeFiles(0,data_size);    
}



void Auto_MakeFile_Builder::Perform_MakeFile_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     if(data_size > 50){

        this->Construct_For_Large_Data_Set(data_size);        
     }
     else{

         if(data_size>16){

             this->Construct_For_Middle_Data_Set(data_size);
         }
         else{

             this->Construct_For_Small_Data_Set(data_size);
         }
     }

    if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
    }

}

size_t Auto_MakeFile_Builder::Split_Range(size_t range_size, size_t partition, size_t & remaining_job){

    if(range_size ==0){

        range_size = 1;
    }

    if(partition == 0){

       partition = 1;
    }

    int range  = range_size/partition; 

    if(range<1){

        range = 1;
    }

    remaining_job = range_size%partition;

    return range;    
}



void Auto_MakeFile_Builder::Perform_Data_Map_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     for(size_t i=0;i<data_size;i++){

         std::string source_file_path= this->Compiler_Data_Pointer->at(i).source_file_path;

         this->DataMap.insert(std::make_pair(source_file_path,this->Compiler_Data_Pointer->at(i)));
     }
}


void Auto_MakeFile_Builder::Write_MakeFiles(int start, int end){

     Make_File_Builder Mk_Builder;

     Mk_Builder.Receive_Compiler_Data_Pointer(this->Dep_Determiner->Get_Compiler_Data_Address());

     Mk_Builder.Receive_Operating_System(this->opr_sis);

     Mk_Builder.Receive_DataMap(&this->DataMap);

     Mk_Builder.Receive_Descriptor_File_Reader(this->Des_Reader);

     for(size_t i=start;i<end;i++){

         std::string source_file_path = this->Compiler_Data_Pointer->at(i).source_file_path;
         
         Mk_Builder.Build_MakeFile(source_file_path);

         Mk_Builder.Clear_Dynamic_Memory();
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


void Auto_MakeFile_Builder::Clear_Vector_Memory(std::vector<std::string> & vec){

    vec.shrink_to_fit();

    for(size_t i=0;i<vec.size();i++){

        this->Clear_String_Memory(vec.at(i));
    }

    vec.shrink_to_fit();

    vec.clear();
}

void Auto_MakeFile_Builder::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}