



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

#include "Source_File_Dependency_Selector_For_Single_File.hpp"

Source_File_Dependency_Selector_For_Single_File::Source_File_Dependency_Selector_For_Single_File( char opr_sis)

    : Info_Collector(opr_sis), Data_Setter(opr_sis)
{

   this->Memory_Delete_Condition = false;

   this->opr_sis = opr_sis;
   
   this->Dep_Data_Collectors = nullptr;

   this->Construct_Dependency_Data_Extractors();

}


Source_File_Dependency_Selector_For_Single_File::~Source_File_Dependency_Selector_For_Single_File()
{
    this->Clear_Dynamic_Memory();
}






/* THE CLASS INPUTS (THE MEMBER FUNCTIONS RECEIVING INFORMATION) */


void Source_File_Dependency_Selector_For_Single_File::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Info_Collector.Receive_Git_Data_Processor(ptr);

     this->Data_Setter.Receive_Git_Data_Processor(ptr);

     this->Git_Data_Proc = ptr;
}


void Source_File_Dependency_Selector_For_Single_File::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Info_Collector.Receive_Source_Code_Reader(ptr);

     this->Data_Setter.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;
}


void Source_File_Dependency_Selector_For_Single_File::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Info_Collector.Receive_Descriptor_File_Reader(ptr);
}






/* THE CONTROL FUNCTIONS (THE MEMBER FUNCTION PERFORMS CONTROL OPERATIONS) */

bool Source_File_Dependency_Selector_For_Single_File::Is_Header_File(std::string hpath){

      return this->Info_Collector.Is_Header_File(hpath);
}





/* THE MEMBER FUNCTIONS PERFORMING MAIN OPERATIONS  */


void Source_File_Dependency_Selector_For_Single_File::Determine_Source_File_Dependencies(std::string path){
     
     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data(path);

     this->Source_File_Data_Ptr = this->Info_Collector.Get_Source_File_Data_Address();


     size_t data_size = this->Source_File_Data_Ptr->size();

     if(data_size>16){

       int division = data_size/16;

       for(int i=0;i<16;i++){

           int str  = i*division;

           int end  = (i+1)*division;


           if(i==15){
            
               end = data_size;
           }

           this->threads[i] 
                
                = std::thread(Source_File_Dependency_Selector_For_Single_File::Extract_Dependency_Data,this,i,str,end);     
       }
    
       for(int i=0;i<16;i++){
     
          this->threads[i].join();
       }
    }
    else{

        this->Extract_Dependency_Data(0,0,data_size);
    }

    this->Dependency_Data.shrink_to_fit();   

    this->Info_Collector.Clear_Dynamic_Memory();    

    this->Clear_Dependency_Data_Extractors();
}


void Source_File_Dependency_Selector_For_Single_File::Extract_Dependency_Data(int thr_num, int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();



     for(size_t i=start;i<end;i++){
     
         std::string path =this->Source_File_Data_Ptr->at(i).system_path;

    
         this->Extract_Dependency_Tree(path,thr_num);

         this->Set_Included_Header_Number(&this->Dependent_List[thr_num]);


         mt.lock();

         this->Dependency_Data.push_back(this->Dependent_List[thr_num]);

         this->Dependency_Data.shrink_to_fit();

         mt.unlock();


         this->Clear_Vector_Memory(&this->Dependent_List[thr_num]);  
     }     

}






void Source_File_Dependency_Selector_For_Single_File::Extract_Dependency_Tree(std::string path,int thr_num){

     this->Dep_Data_Collectors[thr_num] = new Dependency_Data_Extractor(this->opr_sis);

     this->Dep_Data_Collectors[thr_num]->Receive_Source_Code_Reader(this->Code_Rd);

     this->Dep_Data_Collectors[thr_num]->Extract_Dependency_Tree(path);

     std::vector<Search_Data> * Dep_Data_Ptr = this->Dep_Data_Collectors[thr_num]->Get_Search_Data();

     size_t data_size = Dep_Data_Ptr->size();

     if(data_size>0){   // The header file have dependencies

        for(size_t i=0;i<data_size;i++){

            Source_File_Dependency Data;

            std::string header_name = Dep_Data_Ptr->at(i).name;

            this->Set_Dependency_Data(Data,path,header_name);

            this->Dependent_List[thr_num].push_back(Data);
        }
     }


     this->Dep_Data_Collectors[thr_num]->Clear_Object_Memory();

     delete this->Dep_Data_Collectors[thr_num];

     this->Dep_Data_Collectors[thr_num] = nullptr;
}




void Source_File_Dependency_Selector_For_Single_File::Set_Dependency_Data(Source_File_Dependency & data,

     std::string path, std::string header_name){
    
     std::string src_file_name, hdr_sys_path, file_dir, object_file_name, 
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

     this->Data_Setter.Copy_String(data.object_file_name,object_file_name);

     this->Data_Setter.Copy_String(data.source_file_name_without_ext,file_name_without_ext);

     this->Data_Setter.Copy_String(data.src_git_record_dir,src_git_record_dir);

     this->Data_Setter.Copy_String(data.src_sys_dir,src_sys_dir);



     data.rcr_srch_complated= true;

     this->Clear_String_Memory(src_file_name);

     this->Clear_String_Memory(object_file_name);

     this->Clear_String_Memory(hdr_sys_path);
     
}



void Source_File_Dependency_Selector_For_Single_File::Set_Included_Header_Number(std::vector<Source_File_Dependency> * ptr){

     std::vector<Source_File_Dependency>::iterator it;

     for(auto it=ptr->begin();it<ptr->end();it++){
     
         it->base_included_hdr_num = ptr->size();
         it->included_file_hdr_num = 0;
     }     
}



void Source_File_Dependency_Selector_For_Single_File::Print_Dependency_List()
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
         
                std::cout << "\n list - " << counter << " header name:" << it->Header_Name;     

                std::cout << "\n list - " << counter << " header dir: " << it->dir;     

                counter++;
            }

            std::cout << "\n INCLUDED HEADER FILES NUM FOR BASE FILE:" 
            
            << ptr->at(0).base_included_hdr_num;

            std::cout << "\n INCLUDED HEADER FILES NUM FOR INCL FILE:" 
            
            << ptr->at(0).included_file_hdr_num;
         }

         std::cout << "\n\n\n";

      }
}


void Source_File_Dependency_Selector_For_Single_File::Construct_Dependency_Data_Extractors(){

     this->Dep_Data_Collectors = new Dependency_Data_Extractor * [16];   

     for(int i=0;i<16;i++){

        this->Dep_Data_Collectors[i] = nullptr;
     }
}





/* THE MEMBER FUNCTIONS WHICH ARE RESPONSIBLE FROM MEMORY MENAGEMENT */


void Source_File_Dependency_Selector_For_Single_File::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;
        
        this->Clear_Dynamic_Memory();

        this->Clear_String_Memory(this->descriptor_file_path);

        this->Info_Collector.Clear_Dynamic_Memory();

        this->Info_Collector.Clear_Object_Memory();
     }
}

void Source_File_Dependency_Selector_For_Single_File::Clear_Dynamic_Memory()
{
    if(!this->Dependency_Data.empty()){
    
        std::vector<std::vector<Source_File_Dependency>>::iterator it;

        for(auto it=this->Dependency_Data.begin();it<this->Dependency_Data.end();it++){
     
            std::vector<Source_File_Dependency> * ptr = &(*it);

            this->Clear_Vector_Memory(ptr);     
        }

        this->Dependency_Data.clear();

        this->Dependency_Data.shrink_to_fit();
    }
}


void Source_File_Dependency_Selector_For_Single_File::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}


void Source_File_Dependency_Selector_For_Single_File::Clear_Dependency_Data_Extractors(){

     if(this->Dep_Data_Collectors!=nullptr){

        for(int i=0;i<8;i++){

            if(this->Dep_Data_Collectors[i]!= nullptr){

               this->Dep_Data_Collectors[i]->Clear_Dynamic_Memory();

               delete this->Dep_Data_Collectors[i];

               this->Dep_Data_Collectors[i] = nullptr;
           }
        }

        delete [] this->Dep_Data_Collectors;

        this->Dep_Data_Collectors = nullptr;
     }
}



void Source_File_Dependency_Selector_For_Single_File::Clear_Vector_Memory(std::vector<Source_File_Dependency> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->Header_Name.empty()){

            it->Header_Name.clear();
            it->Header_Name.shrink_to_fit();
        }

        if(!it->header_sys_path.empty()){

            it->header_sys_path.clear();
            it->header_sys_path.shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}




//  GETTER MEMBER FUNCTIONS  



std::string Source_File_Dependency_Selector_For_Single_File::Get_Header_System_Path(std::string header_name){

     std::string sys_path;

     const FileData * Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);

     sys_path = Ptr->sys_path;

     return sys_path;
}



std::vector<std::vector<Source_File_Dependency>> * Source_File_Dependency_Selector_For_Single_File::Get_Dependency_List_Adress()
{
      return &this->Dependency_Data;
}


std::vector<Source_File_Dependency> * Source_File_Dependency_Selector_For_Single_File::Get_Dependency_List_Element_Adress(int i)
{
      return &this->Dependency_Data[i];
}


size_t Source_File_Dependency_Selector_For_Single_File::Get_Dependency_List_Size(){

    return this->Dependency_Data.size();
}


std::string Source_File_Dependency_Selector_For_Single_File::Get_Warehouse_Objetcs_Dir(){

     return this->Info_Collector.Get_Warehouse_Objetcs_Dir();
}

std::string Source_File_Dependency_Selector_For_Single_File::Get_Warehouse_Path(){

     return this->Info_Collector.Get_Warehouse_Path();
}
