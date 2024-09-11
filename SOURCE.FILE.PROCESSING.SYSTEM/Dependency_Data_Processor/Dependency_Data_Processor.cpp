

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Dependency_Data_Processor.hpp"

Dependency_Data_Processor::Dependency_Data_Processor(char opr_sis) : 
    
    Info_Collector(opr_sis), Hdr_Dep_Extractor(opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->Hdr_Dep_Extractor.Receive_Dependency_Data_Stack_Container(&this->Stack_Container);
}


Dependency_Data_Processor::~Dependency_Data_Processor()
{
    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Object_Memory();
    }    
}




void Dependency_Data_Processor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Info_Collector.Receive_Descriptor_File_Reader(ptr);

     this->Hdr_Dep_Extractor.Receive_Descriptor_File_Reader(ptr);
}


void Dependency_Data_Processor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Info_Collector.Receive_Source_Code_Reader(ptr);

     this->Hdr_Dep_Extractor.Receive_Source_Code_Reader(ptr);

     this->Code_Rdr = ptr;
}



void Dependency_Data_Processor::Perform_Dependency_Search(){

     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data();

     this->Hdr_Dep_Extractor.Perform_Dependency_Search();

     this->Hdr_Dep_Extractor.Clear_Dynamic_Memory();
    
    
     this->Source_File_Data_Ptr   = this->Info_Collector.Get_Source_File_Data_Address();

     size_t data_size = this->Source_File_Data_Ptr->size();

     if(data_size>50){

        this->Search_For_Large_Data_Set(data_size);        
     }
     else{

         if(data_size>16){

            this->Search_For_Middle_Data_Set(data_size);
         }
         else{

             this->Search_For_Small_Data_Set(data_size);
         }
     }


     this->Dependency_Search_Data.shrink_to_fit();    

     std::cout << "\nDependency data collected";

     this->Clear_Temporary_Memory();

     this->Perform_Data_Reordering(data_size);
}


void Dependency_Data_Processor::Search_For_Large_Data_Set(size_t data_size){

     size_t thread_number = data_size/10;

     if(thread_number > 64){

        thread_number = 64;
     }


     int division = data_size/thread_number;

     int remaining_job = data_size - (division*thread_number);

     int str=0, end=0;

     for(int i=0;i<thread_number;i++){

         if(i==0){

            str = 0;
            end = division;              
         }
         else{

            str = end;

            end = end + division;

            if(remaining_job>0){

               end = end+1;

               remaining_job--;
            }
         }

         if(i==(thread_number-1)){
            
            end = data_size;
         }

         this->threadPool.push_back(std::thread(Dependency_Data_Processor::Extract_Dependency_Search_Data,this,str,end));   
     }
    
     for(int i=0;i<threadPool.size();i++){
     
         this->threadPool[i].join();
     }


     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}


void Dependency_Data_Processor::Search_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(Dependency_Data_Processor::Extract_Dependency_Search_Data,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}


void Dependency_Data_Processor::Search_For_Small_Data_Set(size_t data_size){

     for(size_t i=0;i<data_size;i++){
     
         std::string path =this->Source_File_Data_Ptr->at(i).system_path;

         this->Search_Dependency_Data_For_Path(path);
     }  
}



void Dependency_Data_Processor::Extract_Dependency_Search_Data(int start, int end){

     for(size_t i=start;i<end;i++){
     
         std::string path =this->Source_File_Data_Ptr->at(i).system_path;

         this->Search_Dependency_Data_For_Path(path);
     }     
}



void Dependency_Data_Processor::Search_Dependency_Data_For_Path(std::string path){

     Dependency_Data_Extractor Dep_Data_Collector;

     Dep_Data_Collector.Receive_Source_Code_Reader(this->Code_Rdr);

     Dep_Data_Collector.Receive_Stack_Container(&this->Stack_Container);

     Dep_Data_Collector.Determine_Source_File_Dependencies(path);

     const Search_Data_Records * Dep_Data_Ptr = Dep_Data_Collector.Get_Search_Data();

     std::unique_lock<std::mutex> mt(this->mtx);

     this->Stack_Container.Receive_New_Search_Data(path,Dep_Data_Ptr);

     this->Dependency_Search_Data.push_back(*Dep_Data_Ptr);

     mt.unlock();

     Dep_Data_Collector.Clear_Dynamic_Memory();
}



void Dependency_Data_Processor::Perform_Data_Reordering(size_t data_size){

     if(data_size>100){

        this->ReOrdering_For_Large_Data_Set(data_size);        
     }
     else{

         if(data_size>16){

            this->ReOrdering_For_Middle_Data_Set(data_size);
         }
         else{

             this->ReOrdering_For_Small_Data_Set(data_size);
         }
     }

    this->Dependency_Search_Data.shrink_to_fit();    
    
    std::cout << "\nDependency data re-arranged..";
}



void Dependency_Data_Processor::ReOrdering_For_Large_Data_Set(size_t data_size){

     size_t search_data_size = this->Dependency_Search_Data.size();

     size_t thread_number = search_data_size/10;

     if(thread_number > 64){

        thread_number = 64;
     }

     int division = search_data_size/thread_number;

     int remaining_job = search_data_size - (division*thread_number);

     int str=0, end=0;

     for(int i=0;i<thread_number;i++){

         if(i==0){

            str = 0;
              
            end = division;              
         }
         else{

            str = end;

            end = end + division;

            if(remaining_job>0){

               end = end+1;

               remaining_job--;
            }
        }


        if(i==(thread_number-1)){
            
           end = search_data_size;
        }

        this->threadPool.push_back(std::thread(Dependency_Data_Processor::Re_Order_Dependency_Data,this,str,end));   
     }
    
     for(int i=0;i<this->threadPool.size();i++){
     
         this->threadPool[i].join();
     }

     this->Dependency_Search_Data.shrink_to_fit();    
}



void Dependency_Data_Processor::ReOrdering_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(Dependency_Data_Processor::Re_Order_Dependency_Data,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}



void Dependency_Data_Processor::ReOrdering_For_Small_Data_Set(size_t data_size){

     for(size_t i=0;i<data_size;i++){

         this->ReOrder_Stack_Data(&this->Dependency_Search_Data.at(i));
     }
}


void Dependency_Data_Processor::Re_Order_Dependency_Data(int str, int end){

     for(size_t i=str;i<end;i++){

         this->ReOrder_Stack_Data(&this->Dependency_Search_Data.at(i));
     }
}


void Dependency_Data_Processor::ReOrder_Stack_Data(Search_Data_Records * Data){
     
     std::vector<Search_Data> * ptr = &Data->Dependent_Headers;
       
     if(ptr->size()>0){

        for(size_t j=0;j<ptr->size();j++){

            std::string _path = ptr->at(j).path;

            if(this->Is_Exist_OnSearchStack(_path)){

               const Search_Data_Records *  record = this->Find_Search_Data_From_Path(_path);
                    
               ptr->at(j).dep_counter = record->Dependent_Headers.size();
            } 
        }

        std::sort(ptr->begin(),ptr->end(),
    
            [](Search_Data a, Search_Data b){ return a.dep_counter > b.dep_counter;});

    }
}



bool Dependency_Data_Processor::Is_Exist_OnSearchStack(std::string path){

     return this->Stack_Container.Is_Exist_OnSearchStack(path);
}



const Search_Data_Records * Dependency_Data_Processor::Find_Search_Data_From_Path(std::string path) const
{
      return this->Stack_Container.Find_Search_Data_From_Path(path);
}


void Dependency_Data_Processor::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         for(size_t i=0;i<vec.size();i++){

             this->Clear_String_Memory(vec.at(i));
         }
     }
}



void Dependency_Data_Processor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}



void Dependency_Data_Processor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();     
}



void Dependency_Data_Processor::Clear_Dynamic_Memory()
{
      if(!this->Dependency_Search_Data.empty()){

          for(size_t i=0;i<this->Dependency_Search_Data.size();i++){

              this->Clear_Search_Data_Memory(this->Dependency_Search_Data.at(i).Dependent_Headers);

              this->Clear_Vector_Memory(this->Dependency_Search_Data.at(i).External_Headers);

              this->Clear_String_Memory(this->Dependency_Search_Data.at(i).path);
          }        

          this->Dependency_Search_Data.clear();

          this->Dependency_Search_Data.shrink_to_fit();
      }

      this->Stack_Container.Clear_Object_Memory();
}


void Dependency_Data_Processor::Clear_Search_Data_Memory(std::vector<Search_Data> & data){
    
     if(!data.empty()){

         for(size_t i=0;i<data.size();i++){

             this->Clear_String_Memory(data.at(i).path);
             
             this->Clear_String_Memory(data.at(i).name);
             
             this->Clear_String_Memory(data.at(i).include_decleration);         
         }
    
         data.clear();
     
         data.shrink_to_fit();
     }
}


void Dependency_Data_Processor::Clear_Temporary_Memory(){

     if(!this->threadPool.empty()){

         this->threadPool.clear();

         this->threadPool.shrink_to_fit();
     }

     this->Info_Collector.Clear_Object_Memory();
}



const std::vector<Search_Data_Records> * Dependency_Data_Processor::Get_Search_Data() const {

       return &this->Dependency_Search_Data;
}
