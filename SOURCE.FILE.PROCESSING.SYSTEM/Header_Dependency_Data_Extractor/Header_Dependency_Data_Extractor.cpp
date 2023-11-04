






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

#include "Header_Dependency_Data_Extractor.hpp"

Header_Dependency_Data_Extractor::Header_Dependency_Data_Extractor(char opr_sis) : Info_Collector(opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->Hdr_Processor.Receive_Operating_System(opr_sis);
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

     this->Construct_Dependency_Data_Extractors();

     size_t data_size = this->Header_Files.size();

     size_t thread_number = data_size/10;

     this->total_thread_num = thread_number;

     size_t thread_div = thread_number/10;

     size_t thread_div_2 = thread_number - thread_div;


     if(data_size>20){

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

           this->threadPool.push_back(std::thread(Header_Dependency_Data_Extractor::Extract_Dependency_Search_Data,this,i,str,end));
       }
    
       for(int i=0;i<thread_number;i++){
     
          this->threadPool[i].join();
       }
    }
    else{

        this->Extract_Dependency_Search_Data(0,0,data_size);
    }    
}


int Header_Dependency_Data_Extractor::Split_Range(int range_size, int partition, int & ramaining_job){

    if(range_size ==0){

        range_size = 1;
    }

    int range  = range_size/partition; 

    if(range<1){

        range = 1;
    }

    ramaining_job = range_size%partition;

    return range;
    
}



void Header_Dependency_Data_Extractor::Extract_Dependency_Search_Data(int thr_num, int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();

     for(size_t i=start;i<end;i++){
     
         std::string path = this->Header_Files.at(i).Header_File;

         this->Search_Dependency_Data_For_Path(path,thr_num);
     }     
}


void Header_Dependency_Data_Extractor::Search_Dependency_Data_For_Path(std::string path,int thr_num){

     this->Dep_Data_Collectors[thr_num]->Extract_Dependency_Tree(path);

     const Search_Data_Records * Dep_Data_Ptr = this->Dep_Data_Collectors[thr_num]->Get_Search_Data();

     std::unique_lock<std::mutex> mt(this->mtx);

     this->Stack_Container->Receive_New_Search_Data(path,Dep_Data_Ptr);

     mt.unlock();

     this->Dep_Data_Collectors[thr_num]->Clear_Dynamic_Memory();
}



void Header_Dependency_Data_Extractor::Construct_Dependency_Data_Extractors(){

     size_t data_size = this->Header_Files.size();

     size_t data_extractor_num = data_size/10;

     for(int i=0;i<data_extractor_num;i++){

         Dependency_Data_Extractor * Dep_Ext = new Dependency_Data_Extractor;

         this->Dep_Data_Collectors.push_back(Dep_Ext);

         this->Dep_Data_Collectors.back()->Receive_Source_Code_Reader(this->Code_Rdr);

         this->Dep_Data_Collectors.back()->Receive_Dependency_Data_Stack_Container(this->Stack_Container);
     } 
}


void Header_Dependency_Data_Extractor::Clear_Dynamic_Memory(){

     if(!this->Dep_Data_Collectors.empty()){

        size_t object_num = this->Dep_Data_Collectors.size();

        for(size_t i=0;i<object_num;i++){

             this->Dep_Data_Collectors.at(i)->Clear_Object_Memory();

             delete this->Dep_Data_Collectors.at(i);
        }

        this->Dep_Data_Collectors.clear();

        this->Dep_Data_Collectors.shrink_to_fit();
     }

     if(!this->threadPool.empty()){

        this->threadPool.clear();

        this->threadPool.shrink_to_fit();
     }
}



bool Header_Dependency_Data_Extractor::Is_This_File_Searched(std::string path){

     return this->Stack_Container->Is_Exist_OnSearchStack(path);     
}



const Search_Data_Records Header_Dependency_Data_Extractor::Find_Search_Data_From_Path(std::string path) const
{
    return this->Stack_Container->Find_Search_Data_From_Path(path);
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
