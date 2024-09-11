

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

#include "Header_Dependency_Data_Extractor.hpp"

Header_Dependency_Data_Extractor::Header_Dependency_Data_Extractor(char opr_sis) : Info_Collector(opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->Hdr_Processor.Receive_Operating_System(opr_sis);

   this->opr_sis = opr_sis;
}


Header_Dependency_Data_Extractor::~Header_Dependency_Data_Extractor()
{
    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;
    }    
}


void Header_Dependency_Data_Extractor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Info_Collector.Receive_Descriptor_File_Reader(ptr);
}

void Header_Dependency_Data_Extractor::Receive_Dependency_Data_Stack_Container(Dependency_Data_Stack_Container * ptr){

     this->Stack_Container = ptr;

}

void Header_Dependency_Data_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}



void Header_Dependency_Data_Extractor::Find_Header_Files(){

     size_t code_file_num =  this->Code_Rdr->Get_Project_Files_Number();

     for(size_t i=0;i<code_file_num;i++){

         std::string path = this->Code_Rdr->Get_File_Path(i);
        
         if(this->Hdr_Processor.Is_Header(path)){

            const FileData * Data =  this->Code_Rdr->Find_File_Data_From_Path(path);

            Header_File_Data Hdr_Dt;

            Hdr_Dt.Header_File = Data->sys_path;

            Hdr_Dt.include_number = Data->inclusion_number;

            this->Header_Files.push_back(Hdr_Dt);
         }
     }  

     this->Header_Files.shrink_to_fit();

     for(size_t i=0;i<this->Header_Files.size();i++){

         for(size_t j=0;j<this->Header_Files.size();j++){

             if(this->Header_Files.at(i).include_number < this->Header_Files.at(j).include_number){

                Header_File_Data Hdr_Dt;

                Hdr_Dt = this->Header_Files.at(j);

                this->Header_Files.at(j) = this->Header_Files.at(i);

                this->Header_Files.at(i) = Hdr_Dt;
             }
         }
     }
}


void Header_Dependency_Data_Extractor::Perform_Dependency_Search(){

     this->Find_Header_Files();

     size_t data_size = this->Header_Files.size();

     if(data_size>50){

        this->Search_For_Large_Data_Set(data_size);
     }
     else{

         if(data_size>16){

            this->Search_For_Middle_Data_Set(data_size);
         }
         else{

            this->Search_For_Middle_Data_Set(data_size);
         }
     }
}


void Header_Dependency_Data_Extractor::Search_For_Large_Data_Set(size_t data_size){

     size_t thread_number = data_size/10;
 
     if(thread_number > 64){

        thread_number = 64;
     }


     size_t thread_div = thread_number/10;

     size_t thread_div_2 = thread_number - thread_div;


     int str=0, end=0;

     int first_division  = 9*data_size/10;

     int second_division = data_size/10;

     int remaining_thread_num = thread_number - thread_div;

     int first_range_remaining_job = 0;
        
     int second_range_remaining_job = 0;


     int first_range_  = this->Split_Range(first_division,thread_div,first_range_remaining_job);

     int second_range_ = this->Split_Range(second_division,remaining_thread_num,second_range_remaining_job);


     for(int i=0;i<thread_number;i++){
            
         if(i==0){

            str = 0;

            end = first_range_;
         }
         else{

            if(i<thread_div){

               str  = end;

               end  = end + first_range_;

               if(first_range_remaining_job > 0){

                  end = end+1;

                  first_range_remaining_job--;
               }
            }
            else{                

                str  = end;

                end  = end + second_range_;

                if(second_range_remaining_job > 0){

                   end = end+1;

                   second_range_remaining_job--;
                }
           }
        }            

        if(i==(thread_number-1)){
            
           end = data_size;
        }

        this->threadPool.push_back(std::thread(&Header_Dependency_Data_Extractor::Extract_Dependency_Search_Data,this,str,end));
     }
    
     for(int i=0;i<thread_number;i++){
     
        this->threadPool[i].join();
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}


void Header_Dependency_Data_Extractor::Search_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(&Header_Dependency_Data_Extractor::Extract_Dependency_Search_Data,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}


void Header_Dependency_Data_Extractor::Search_For_Small_Data_Set(size_t data_size){

     for(size_t i=0;i<data_size;i++){
     
         std::string path = this->Header_Files.at(i).Header_File;

         this->Search_Dependency_Data_For_Path(path);
     }  
}



int Header_Dependency_Data_Extractor::Split_Range(int range_size, int partition, int & remaining_job){

    if(range_size == 0){

        range_size = 1;
    }

    if(partition == 0){

        partition = 1;
    }

    int range  = range_size/partition; 

    if(range<1){

        range = 1;
    }

    remaining_job = range_size - (range*partition);

    return range;
}



void Header_Dependency_Data_Extractor::Extract_Dependency_Search_Data(int start, int end){

     for(size_t i=start;i<end;i++){
     
         std::string path = this->Header_Files.at(i).Header_File;

         this->Search_Dependency_Data_For_Path(path);
     }     
}


void Header_Dependency_Data_Extractor::Search_Dependency_Data_For_Path(std::string path){

     Dependency_Data_Extractor Dep_Ext;

     Dep_Ext.Receive_Operating_System(this->opr_sis);

     Dep_Ext.Receive_Source_Code_Reader(this->Code_Rdr);

     Dep_Ext.Receive_Stack_Container(this->Stack_Container);

     Dep_Ext.Extract_Dependency_Tree(path);

     const Search_Data_Records * Dep_Data_Ptr = Dep_Ext.Get_Search_Data();

     std::unique_lock<std::mutex> mt(this->mtx);

     this->Stack_Container->Receive_New_Search_Data(path,Dep_Data_Ptr);

     mt.unlock();

     Dep_Ext.Clear_Dynamic_Memory();
}



void Header_Dependency_Data_Extractor::Clear_Dynamic_Memory(){

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }

     if(!this->Header_Files.empty()){

        for(size_t i=0;i<this->Header_Files.size();i++){

            this->Clear_String_Memory(this->Header_Files.at(i).Header_File);
        }

        this->Header_Files.clear();

        this->Header_Files.shrink_to_fit();
     }

     this->Hdr_Processor.Clear_Object_Memory();
}



void Header_Dependency_Data_Extractor::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         for(size_t i=0;i<vec.size();i++){

             this->Clear_String_Memory(vec.at(i));
         }
     }
}



void Header_Dependency_Data_Extractor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}



void Header_Dependency_Data_Extractor::Clear_Search_Data_Memory(std::vector<Search_Data> & data){
    
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





const std::vector<Search_Data_Records> * Header_Dependency_Data_Extractor::Get_Search_Data() const {

       return this->Stack_Container->Get_Search_Stack();
}
