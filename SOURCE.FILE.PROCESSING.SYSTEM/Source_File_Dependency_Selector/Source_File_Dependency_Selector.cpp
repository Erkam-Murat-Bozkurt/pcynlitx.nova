


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

#include "Source_File_Dependency_Selector.hpp"

Source_File_Dependency_Selector::Source_File_Dependency_Selector( char opr_sis)

    : Dep_Data_Proccessor(opr_sis), Info_Collector(opr_sis), Data_Setter(opr_sis)
{
   this->Memory_Delete_Condition = false;
}


Source_File_Dependency_Selector::~Source_File_Dependency_Selector()
{
    this->Clear_Dynamic_Memory();
}






/* THE CLASS INPUTS (THE MEMBER FUNCTIONS RECEIVING INFORMATION) */


void Source_File_Dependency_Selector::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Info_Collector.Receive_Git_Data_Processor(ptr);

     this->Data_Setter.Receive_Git_Data_Processor(ptr);
}


void Source_File_Dependency_Selector::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Info_Collector.Receive_Source_Code_Reader(ptr);

     this->Data_Setter.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;

     this->Dep_Data_Proccessor.Receive_Source_Code_Reader(ptr);
}


void Source_File_Dependency_Selector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Info_Collector.Receive_Descriptor_File_Reader(ptr);

     this->Dep_Data_Proccessor.Receive_Descriptor_File_Reader(ptr);
}




/* THE CONTROL FUNCTIONS (THE MEMBER FUNCTION PERFORMS CONTROL OPERATIONS) */

bool Source_File_Dependency_Selector::Is_Header_File(std::string hpath){

      return this->Info_Collector.Is_Header_File(hpath);
}




/* THE MEMBER FUNCTIONS PERFORMING MAIN OPERATIONS  */

void Source_File_Dependency_Selector::Determine_Source_File_Dependencies(){

     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data();

     this->Source_File_Data_Ptr = this->Info_Collector.Get_Source_File_Data_Address();

     this->Dep_Data_Proccessor.Perform_Dependency_Search();

     this->Search_Data_Ptr = this->Dep_Data_Proccessor.Get_Search_Data();

     size_t data_size =  this->Search_Data_Ptr->size();
    

     std::cout << "\nThe source file data construction started";


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


     this->Dependency_Data.shrink_to_fit();   


     if(!this->threadPool.empty()){

         this->threadPool.clear();

         this->threadPool.shrink_to_fit();
     }

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Dep_Data_Proccessor.Clear_Dynamic_Memory();

     std::cout << "\nThe source file data construction complated";
}



void Source_File_Dependency_Selector::Search_For_Large_Data_Set(size_t data_size){

     size_t str=0, end=0;

     size_t thread_num = data_size/20;

     if(thread_num > 200){

        thread_num = 200;
     }

     size_t remaining_job = 0;

     size_t range =this->Split_Range(data_size,thread_num,remaining_job);


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

         this->threadPool.push_back(std::thread(Source_File_Dependency_Selector::Arrange_Dependency_Data,this,str,end));
     }
    
     for(size_t i=0;i<thread_num;i++){
            
         this->threadPool[i].join();
     }

}

void Source_File_Dependency_Selector::Search_For_Middle_Data_Set(size_t data_size){

     int division = data_size/16;

     for(int i=0;i<16;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==15){

            end = data_size;
         }

         this->threadPool.push_back(std::thread(Source_File_Dependency_Selector::Arrange_Dependency_Data,this,str,end));
     }
    
     for(int i=0;i<16;i++){
     
         this->threadPool[i].join();
     }
}


void Source_File_Dependency_Selector::Search_For_Small_Data_Set(size_t data_size){

     for(size_t i=0;i<data_size;i++){

         std::vector<Source_File_Dependency> Dep_List;

         this->Construct_Dependency_Data_Vector(i,Dep_List);

         this->Set_Included_Header_Number(&Dep_List);

         this->Dependency_Data.push_back(Dep_List);

         this->Dependency_Data.shrink_to_fit();

         this->Clear_Source_File_Dependency_Data(Dep_List);  
     } 
}



size_t Source_File_Dependency_Selector::Split_Range(size_t range_size, size_t partition, size_t & remaining_job){

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


void Source_File_Dependency_Selector::Arrange_Dependency_Data(int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();

     for(size_t i=start;i<end;i++){

         std::vector<Source_File_Dependency> Dep_List;

         this->Construct_Dependency_Data_Vector(i,Dep_List);

         this->Set_Included_Header_Number(&Dep_List);


         mt.lock();

         this->Dependency_Data.push_back(Dep_List);

         this->Dependency_Data.shrink_to_fit();

         mt.unlock();


         this->Clear_Source_File_Dependency_Data(Dep_List);  
     }     
}






void Source_File_Dependency_Selector::Construct_Dependency_Data_Vector(size_t index, 

     std::vector<Source_File_Dependency> & Dep_List){

     const Search_Data_Records * Ptr = &this->Search_Data_Ptr->at(index);

     const std::vector<Search_Data> * Dep_Data_Ptr = &Ptr->Dependent_Headers;

     std::string path = Ptr->path;

     size_t data_size = Dep_Data_Ptr->size();
          
     if(data_size>0){   // The header file have dependencies

        for(size_t i=0;i<data_size;i++){

            Source_File_Dependency Data;

            std::string header_name = Dep_Data_Ptr->at(i).name;

            this->Set_Dependency_Data(Data,path,header_name);
            
            const std::vector<std::string> * Ext_Hdr 
            
               = &Ptr->External_Headers;

            this->Set_External_Header_File_Dependencies(Data,Ext_Hdr);

            Dep_List.push_back(Data);
        }
     }
}




void Source_File_Dependency_Selector::Set_Dependency_Data(Source_File_Dependency & data,

     std::string path, std::string header_name){
    
     std::string src_file_name,
     
     hdr_sys_path, file_dir, object_file_name,
     
     src_git_record_dir, file_name_without_ext, src_sys_dir;

     
     const FileData * Data = this->Code_Rd->Find_File_Data_From_Name(header_name);


     std::string file_path = Data->sys_path;

     this->Data_Setter.Extract_Directory_From_Path(file_path,file_dir);

     this->Data_Setter.Extract_File_Name_From_Path(src_file_name,path);



     this->Data_Setter.Determine_Git_Record_Source_File_Directory(path,src_git_record_dir);

     this->Data_Setter.Determine_File_Name_Without_Ext(path,file_name_without_ext);

     this->Data_Setter.Determine_Header_System_Path(hdr_sys_path,header_name);

     this->Data_Setter.Determine_Object_File_Name(object_file_name,src_file_name);

     this->Data_Setter.Extract_Directory_From_Path(path,src_sys_dir);




     this->Data_Setter.Copy_String(data.source_file_name,src_file_name);

     this->Data_Setter.Copy_String(data.Header_Name,header_name);

     this->Data_Setter.Copy_String(data.header_sys_path,hdr_sys_path);

     this->Data_Setter.Copy_String(data.source_file_path,path);

     this->Data_Setter.Copy_String(data.dir,file_dir);

     this->Data_Setter.Copy_String(data.source_file_name_without_ext,file_name_without_ext);

     this->Data_Setter.Copy_String(data.src_git_record_dir,src_git_record_dir);

     this->Data_Setter.Copy_String(data.src_sys_dir,src_sys_dir);

     this->Data_Setter.Copy_String(data.object_file_name,object_file_name);

     data.rcr_srch_complated= true;



     this->Clear_String_Memory(src_file_name);

     this->Clear_String_Memory(hdr_sys_path);

     this->Clear_String_Memory(file_dir);

     this->Clear_String_Memory(object_file_name);

     this->Clear_String_Memory(src_git_record_dir);

     this->Clear_String_Memory(file_name_without_ext);
     
     this->Clear_String_Memory(src_sys_dir);
}



void Source_File_Dependency_Selector::Set_Included_Header_Number(std::vector<Source_File_Dependency> * ptr){

     std::vector<Source_File_Dependency>::iterator it;

     for(auto it=ptr->begin();it<ptr->end();it++){
     
         it->base_included_hdr_num = ptr->size();

         it->included_file_hdr_num = 0;
     }     
}


void Source_File_Dependency_Selector::Set_External_Header_File_Dependencies(Source_File_Dependency & data, 

     const std::vector<std::string> * vec){

     size_t vec_size = vec->size();

     for(size_t i=0;i<vec_size;i++){

        data.External_Headers.push_back(vec->at(i));
     }

     data.External_Headers.shrink_to_fit();
}






/* THE MEMBER FUNCTIONS WHICH ARE RESPONSIBLE FROM MEMORY MENAGEMENT */


void Source_File_Dependency_Selector::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;
        
        this->Clear_Dynamic_Memory();

        this->Info_Collector.Clear_Object_Memory();
     }
}


void Source_File_Dependency_Selector::Clear_Dynamic_Memory()
{
    this->Dependency_Data.shrink_to_fit();

    if(!this->Dependency_Data.empty()){
    
        for(size_t i=0;i<this->Dependency_Data.size();i++){

            this->Clear_Source_File_Dependency_Data(this->Dependency_Data.at(i));     
        }

        this->Dependency_Data.clear();

        this->Dependency_Data.shrink_to_fit();
    }

     this->Info_Collector.Clear_Dynamic_Memory();
}


void Source_File_Dependency_Selector::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}


void Source_File_Dependency_Selector::Clear_Source_File_Dependency_Data(std::vector<Source_File_Dependency> & vec){
     
     vec.shrink_to_fit();

     if(!vec.empty()){

         for(size_t i=0;i<vec.size();i++){

             this->Clear_String_Memory(vec.at(i).Combined_Header_Name);

             this->Clear_String_Memory(vec.at(i).dir);
         
             this->Clear_String_Memory(vec.at(i).Header_Name);

             this->Clear_String_Memory(vec.at(i).header_sys_path);

             this->Clear_String_Memory(vec.at(i).object_file_name);

             this->Clear_String_Memory(vec.at(i).source_file_name);

             this->Clear_String_Memory(vec.at(i).source_file_name_without_ext);

             vec.at(i).External_Headers.shrink_to_fit();

             for(size_t j=0;j<vec.at(i).External_Headers.size();j++){

                 this->Clear_String_Memory(vec.at(i).External_Headers.at(j));
             }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}




void Source_File_Dependency_Selector::Print_Dependency_List()
{
     size_t data_size = this->Dependency_Data.size();

     for(size_t i=0;i<data_size;i++){

         std::vector<Source_File_Dependency> * ptr = &this->Dependency_Data.at(i);

         std::cout << "\n\n\n";

         if(ptr->size()>0){
         
            std::cout << "\n FILE RESEARCHED:" << ptr->at(0).source_file_name;

            std::vector<Source_File_Dependency>::iterator it;         

            int counter=0;

            for(auto it=ptr->begin();it<ptr->end();it++){
         
                std::cout << "\n";

                std::cout << "\n list - " << counter << " " << it->Header_Name;     

                std::cout << "\n list - " << counter << " " << it->dir;     

                counter++;
            }

            std::cout << "\n INCLUDED HEADER FILES NUM FOR BASE FILE:" 
            
            << ptr->at(0).base_included_hdr_num;

            std::cout << "\n INCLUDED HEADER FILES NUM FOR INCL FILE:" 
            
            << ptr->at(0).included_file_hdr_num;

            std::cout << "\n External Header Files:";

            std::vector<std::string> * ext_headers = &ptr->at(0).External_Headers;

            for(size_t k=0;k<ext_headers->size();k++){

                 std::cout << "\n External Hdr [" << k << "]:" << ext_headers->at(k);
            }

            sleep(0.1);
         }
      }
}







//  GETTER MEMBER FUNCTIONS  

std::string Source_File_Dependency_Selector::Get_Header_System_Path(std::string header_name){

     const FileData * Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);

     std::string sys_path = Ptr->sys_path;
    
     return sys_path;
}



std::vector<std::vector<Source_File_Dependency>> * Source_File_Dependency_Selector::Get_Dependency_List_Adress()
{
      return &this->Dependency_Data;
}


std::vector<Source_File_Dependency> * Source_File_Dependency_Selector::Get_Dependency_List_Element_Adress(int i)
{
      return &this->Dependency_Data[i];
}


size_t Source_File_Dependency_Selector::Get_Dependency_List_Size(){

    return this->Dependency_Data.size();
}


std::string Source_File_Dependency_Selector::Get_Warehouse_Objetcs_Dir(){

     return this->Info_Collector.Get_Warehouse_Objetcs_Dir();
}



std::string Source_File_Dependency_Selector::Get_Warehouse_Path(){

     return this->Info_Collector.Get_Warehouse_Path();
}
