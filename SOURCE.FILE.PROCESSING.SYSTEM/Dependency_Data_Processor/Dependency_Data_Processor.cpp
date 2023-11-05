




/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

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


void Dependency_Data_Processor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
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

     this->Clear_Dynamic_Memory();
     
     

     this->Source_File_Data_Ptr   = this->Info_Collector.Get_Source_File_Data_Address();

     this->Construct_Dependency_Data_Extractors();

     
     size_t data_size = this->Source_File_Data_Ptr->size();

     size_t thread_number = data_size/10;

     if(data_size>20){

       int division = data_size/thread_number;

       int remaining_job = data_size%thread_number;

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

           this->threadPool.push_back(std::thread(Dependency_Data_Processor::Extract_Dependency_Search_Data,this,i,str,end));   
       }
    
       for(int i=0;i<threadPool.size();i++){
     
          this->threadPool[i].join();
       }
    }
    else{

        this->Extract_Dependency_Search_Data(0,0,data_size);
    }

    this->Dependency_Search_Data.shrink_to_fit();    
}




void Dependency_Data_Processor::Construct_Dependency_Data_Extractors(){

     size_t data_size = this->Source_File_Data_Ptr->size();

     size_t data_extractor_num = data_size/10;

     for(int i=0;i<data_extractor_num;i++){

         Dependency_Data_Extractor * Dep_Ext = new Dependency_Data_Extractor;

         this->Dep_Data_Collectors.push_back(Dep_Ext);

         this->Dep_Data_Collectors.back()->Receive_Source_Code_Reader(this->Code_Rdr);

         this->Dep_Data_Collectors.back()->Receive_Stack_Container(&this->Stack_Container);
     } 
}



void Dependency_Data_Processor::Extract_Dependency_Search_Data(int thr_num, int start, int end){

     for(size_t i=start;i<end;i++){
     
         std::string path =this->Source_File_Data_Ptr->at(i).system_path;

         this->Search_Dependency_Data_For_Path(path,thr_num);
     }     
}


void Dependency_Data_Processor::Search_Dependency_Data_For_Path(std::string path,int thr_num){

     this->Dep_Data_Collectors[thr_num]->Determine_Source_File_Dependencies(path);

     const Search_Data_Records * Dep_Data_Ptr = this->Dep_Data_Collectors[thr_num]->Get_Search_Data();

     std::unique_lock<std::mutex> mt(this->mtx);

     this->Stack_Container.Receive_New_Search_Data(path,Dep_Data_Ptr);

     this->Dependency_Search_Data.push_back(*Dep_Data_Ptr);

     mt.unlock();

     this->Dep_Data_Collectors[thr_num]->Clear_Dynamic_Memory();
}



void Dependency_Data_Processor::Set_Dependency_Counters(){

     size_t search_data_size = this->Dependency_Search_Data.size();

     for(size_t i=0;i<search_data_size;i++){

         std::vector<Search_Data> * ptr
         
            = &this->Dependency_Search_Data.at(i).Dependent_Headers;
       
         std::cout << "\n ptr->size():" << ptr->size();
         std::cout << "\n path:" << ptr->at(0).path;


         if(ptr->size()>0){

            for(size_t j=0;j<ptr->size();j++){

                std::string _path = ptr->at(j).path;

                std::cout << "\n _path:" << _path;

                std::cout << "\n dep_counter:" << ptr->at(j).dep_counter;

                std::cout << "\n this->Is_This_File_Searched(_path):" << this->Is_This_File_Searched(_path);

                std::cin.get();

                if(this->Is_This_File_Searched(_path)){

                    const Search_Data_Records *  record = this->Find_Search_Data_From_Path(_path);
                    
                    ptr->at(j).dep_counter = record->Dependent_Headers.size();

                    std::cout << "\n ptr->at(" << j << ").dep_counter" << ptr->at(j).dep_counter;

                    std::cout << "\n record->path:" << record->path;

                    std::cout << "\n record->Dependent_Headers:" << record->Dependent_Headers.size();

                    std::cin.get();

                } 
            }
         }
     }
}




bool Dependency_Data_Processor::Is_This_File_Searched(std::string path){

     bool is_this_file_searched = false;

     if(this->Search_Data_Map.find(path)!=this->Search_Data_Map.end()){

        is_this_file_searched = true;
     }

     return is_this_file_searched;
}



const Search_Data_Records * Dependency_Data_Processor::Find_Search_Data_From_Path(std::string path) const
{
    try {        

         return this->Search_Data_Map.at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Dependency_Data_Holder instance,";

         std::cout << "\n Inside Find_Search_Data_From_Path,";

         std::cout << "\n the file located on " << path << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
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

      if(!this->Search_Data_Map.empty()){

          this->Search_Data_Map.clear();          
      }
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





const std::vector<Search_Data_Records> * Dependency_Data_Processor::Get_Search_Data() const {

       return &this->Dependency_Search_Data;
}
