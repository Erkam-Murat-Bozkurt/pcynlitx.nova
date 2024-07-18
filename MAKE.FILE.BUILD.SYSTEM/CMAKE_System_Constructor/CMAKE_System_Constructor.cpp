



#include "CMAKE_System_Constructor.hpp"

CMAKE_System_Constructor::CMAKE_System_Constructor(char * DesPath, char opr_sis) 
{
     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;
}


CMAKE_System_Constructor::~CMAKE_System_Constructor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_System_Constructor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(this->repo_obj_dir);

         this->Clear_String_Memory(this->Warehouse_Path);

         this->Clear_String_Memory(this->Repo_Dir);

         this->DataMap.clear();
     }
}


void CMAKE_System_Constructor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Warehouse_Path = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir = this->Des_Reader->Get_Repo_Directory_Location();
}


void CMAKE_System_Constructor::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->Dep_Determiner = dep_ptr;
}



void CMAKE_System_Constructor::Build_Make_Files(){

     // Determination of the directories recorded on the git repo

     this->Compiler_Data_Pointer = this->Dep_Determiner->Get_Compiler_Data_Address();

     this->Compiler_Data_Pointer->shrink_to_fit();

     this->Perform_Data_Map_Construction();

     this->Perform_MakeFile_Construction();

     std::cout << "\n";
     std::cout << "\nThe new makefiles have been constructed..";
     std::cout << "\n";
     std::cout << "\n";
}


void CMAKE_System_Constructor::Construct_For_Large_Data_Set(size_t data_size){

     size_t str=0, end=0;

     size_t thread_num = data_size/50;

     if(thread_num > 64){

        thread_num = 64;
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

         this->threadPool.push_back(std::thread(&CMAKE_System_Constructor::Write_MakeFiles,this,str,end));
     }
    
     for(size_t i=0;i<thread_num;i++){
            
         this->threadPool[i].join();
     }
}

void CMAKE_System_Constructor::Construct_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(&CMAKE_System_Constructor::Write_MakeFiles,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }
}

void CMAKE_System_Constructor::Construct_For_Small_Data_Set(size_t data_size){

     this->Write_MakeFiles(0,data_size);    
}



void CMAKE_System_Constructor::Perform_MakeFile_Construction(){

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

size_t CMAKE_System_Constructor::Split_Range(size_t range_size, size_t partition, size_t & remaining_job){

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

    remaining_job = range_size - range*partition;

    return range;    
}



void CMAKE_System_Constructor::Perform_Data_Map_Construction(){

     size_t data_size = this->Compiler_Data_Pointer->size();

     for(size_t i=0;i<data_size;i++){

         std::string source_file_path= this->Compiler_Data_Pointer->at(i).source_file_path;

         this->DataMap.insert(std::make_pair(source_file_path,this->Compiler_Data_Pointer->at(i)));
     }
}


void CMAKE_System_Constructor::Write_MakeFiles(int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();


     CMAKE_Target_Library_Builder Target_Builder;

     Target_Builder.Receive_Compiler_Data_Pointer(this->Dep_Determiner->Get_Compiler_Data_Address());

     Target_Builder.Receive_Operating_System(this->opr_sis);

     Target_Builder.Receive_DataMap(&this->DataMap);

     Target_Builder.Receive_Descriptor_File_Reader(this->Des_Reader);

     for(size_t i=start;i<end;i++){

         std::string source_file_path = this->Compiler_Data_Pointer->at(i).source_file_path;
         
         Target_Builder.Build_MakeFile(source_file_path);

         mt.lock();

         Target_Builder.Add_Target_Path_To_Directory_List();

         Target_Builder.Construct_SubDirectory_List_File();

         mt.unlock();

         Target_Builder.Clear_Dynamic_Memory();
     }
}


void CMAKE_System_Constructor::Construct_Path(std::string * pointer, std::string string, 

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



void CMAKE_System_Constructor::Clear_Vector_Memory(std::vector<std::string> & vec){

    vec.shrink_to_fit();

    for(size_t i=0;i<vec.size();i++){

        this->Clear_String_Memory(vec.at(i));
    }

    vec.shrink_to_fit();

    vec.clear();
}

void CMAKE_System_Constructor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}