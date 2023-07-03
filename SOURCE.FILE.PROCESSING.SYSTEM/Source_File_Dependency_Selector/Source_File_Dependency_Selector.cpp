


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

Source_File_Dependency_Selector::Source_File_Dependency_Selector(char * des_file_path, char opr_sis)

    : Info_Collector(des_file_path,opr_sis), 
      Header_Processor(des_file_path,opr_sis)
{
   this->Memory_Delete_Condition = false;

   size_t dep_path_size = strlen(des_file_path);

   this->dep_path = new char [5*dep_path_size];

   for(size_t i=0;i<dep_path_size;i++){

       this->dep_path[i] = des_file_path[i];
   }

   this->dep_path[dep_path_size] = '\0';

   this->opr_sis = opr_sis;
   
   this->Dep_Data_Collectors = nullptr;
}


Source_File_Dependency_Selector::~Source_File_Dependency_Selector()
{
    this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_Selector::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;
        
        this->Clear_Dynamic_Memory();

        this->Info_Collector.Clear_Object_Memory();
     }
}

void Source_File_Dependency_Selector::Clear_Dynamic_Memory()
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

     this->Clear_String_Memory(&this->warehouse_head_dir);

     this->Clear_String_Memory(&this->descriptor_file_path);

     this->Info_Collector.Clear_Dynamic_Memory();
}


void Source_File_Dependency_Selector::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Info_Collector.Receive_Source_Code_Reader(ptr);

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;
}


void Source_File_Dependency_Selector::Determine_Source_File_Dependencies(std::string path)
{
     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data(path);

     this->warehouse_head_dir = this->Info_Collector.Get_Warehouse_Headers_Dir();

     this->Construct_Dependency_Data_Extractors();

     this->Extract_Dependency_Tree(path,0);

     this->Set_Included_Header_Number(&this->Dependent_List[0]);

     this->Dependency_Data.push_back(this->Dependent_List[0]);
 
     this->Dependency_Data.shrink_to_fit();

     size_t list_size = this->Dependent_List[0].size();

     if(list_size>0){

        this->Dependent_List_Buffer = this->Dependent_List[0];
        
        this->Clear_Vector_Memory(&this->Dependent_List[0]);  
   
        if(list_size>8){

            int division = list_size/8;

            for(int i=0;i<8;i++){

                int str  = i*division;

                int end  = (i+1)*division;
                 
                this->threads[i] 
                
                = std::thread(Source_File_Dependency_Selector::Process_Dependency_Data,this,i,str,end);     
            }
    
            for(int i=0;i<8;i++){
     
                this->threads[i].join();
            }
        }
        else{

            this->Process_Dependency_Data(0,0,list_size);
        }

        this->Clear_Vector_Memory(&this->Dependent_List_Buffer);
     }

     // THE DEPENDENCIES COLLECTED FOR THE ROOT PATH

     this->Info_Collector.Clear_Dynamic_Memory();  

     this->Clear_Dependency_Data_Extractors();

     this->Dependency_Data.shrink_to_fit();
}


void Source_File_Dependency_Selector::Process_Dependency_Data(int thr_num, int start, int end)
{    

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();


     for(size_t i=start;i<end;i++){

         Source_File_Dependency Data = this->Dependent_List_Buffer.at(i);

         std::string sub_path = Data.header_sys_path;

         this->Extract_Dependency_Tree(sub_path,thr_num);

         this->Set_Included_Header_Number(&this->Dependent_List[thr_num]);

         mt.lock();

         this->Dependency_Data.push_back(this->Dependent_List[thr_num]);

         this->Dependency_Data.shrink_to_fit();

         mt.unlock();

         this->Clear_Vector_Memory(&this->Dependent_List[thr_num]);  
    }
}


void Source_File_Dependency_Selector::Determine_Source_File_Dependencies(){

     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data();

     this->warehouse_head_dir = this->Info_Collector.Get_Warehouse_Headers_Dir();

     this->Headers_Data_Ptr   = this->Info_Collector.Get_Headers_Data_Address();

     this->Construct_Dependency_Data_Extractors();

     size_t data_size = this->Headers_Data_Ptr->size();

    if(data_size>8){

       int division = data_size/8;

       for(int i=0;i<8;i++){

           int str  = i*division;

           int end  = (i+1)*division;


           if(i==7){
            
               end = data_size;
           }

           this->threads[i] 
                
                = std::thread(Source_File_Dependency_Selector::Extract_Dependency_Data,this,i,str,end);     
       }
    
       for(int i=0;i<8;i++){
     
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


void Source_File_Dependency_Selector::Extract_Dependency_Data(int thr_num, int start, int end){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();

     for(size_t i=start;i<end;i++){
     
         std::string path =this->Headers_Data_Ptr->at(i).system_path;

         this->Extract_Dependency_Tree(path,thr_num);

         this->Set_Included_Header_Number(&this->Dependent_List[thr_num]);


         mt.lock();

         this->Dependency_Data.push_back(this->Dependent_List[thr_num]);

         this->Dependency_Data.shrink_to_fit();

         mt.unlock();


         this->Clear_Vector_Memory(&this->Dependent_List[thr_num]);  
     }     
}


void Source_File_Dependency_Selector::Extract_Dependency_Tree(std::string path,int thr_num){

     this->Dep_Data_Collectors[thr_num] = new Dependency_Data_Extractor(this->dep_path,this->opr_sis);

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
}



void Source_File_Dependency_Selector::Set_Dependency_Data(Source_File_Dependency & data,

     std::string path, std::string header_name){
    
     std::string src_file_name, wrd_path, hdr_sys_path, file_dir;

     FileData * Data = this->Code_Rd->Find_File_Data_From_Name(header_name);

     std::string file_path = Data->sys_path;

     this->Extract_Directory_From_Path(file_path,file_dir);

     this->Extract_File_Name_From_Path(&src_file_name,path);

     this->Determine_Header_Repo_Warehouse_Path(&wrd_path,header_name,'w');

     this->Determine_Header_System_Path(hdr_sys_path,header_name);

     this->Place_String(&data.source_file_name,src_file_name);

     this->Place_String(&data.Header_Name,header_name);

     this->Place_String(&data.header_sys_path,hdr_sys_path);

     this->Place_String(&data.source_file_path,path);

     this->Place_String(&data.repo_warehouse_path,wrd_path);

     this->Place_String(&data.dir,file_dir);

     data.rcr_srch_complated= true;

     this->Clear_String_Memory(&src_file_name);

     this->Clear_String_Memory(&wrd_path);

     this->Clear_String_Memory(&hdr_sys_path);
     
}




void Source_File_Dependency_Selector::Extract_Directory_From_Path(std::string path, std::string & dir){

     size_t path_size = path.size();

     size_t end_point = path_size;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(path[i]== '\\'){

                break;
            }
            else{

                 end_point--;
            }
         }

         if(this->opr_sis == 'l'){

            if(path[i]== '/'){

                break;
            }
            else{

                 end_point--;
            }
         }         
    }

    for(size_t i=0;i<end_point;i++)
    {
        dir.push_back(path[i]);
    }

    dir.shrink_to_fit();    
}



void Source_File_Dependency_Selector::Determine_Header_System_Path(std::string & path, std::string name){

     FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(name);

     path = FileDtPtr->sys_path;
}


void Source_File_Dependency_Selector::Set_Included_Header_Number(std::vector<Source_File_Dependency> * ptr){

     std::vector<Source_File_Dependency>::iterator it;

     for(auto it=ptr->begin();it<ptr->end();it++){
     
         it->base_included_hdr_num = ptr->size();
         it->included_file_hdr_num = 0;
     }     
}




void Source_File_Dependency_Selector::Determine_Header_Repo_Warehouse_Path(std::string * wrd_path,

     std::string file_name, char opr_sis)
{

     size_t name_size = file_name.length();

     size_t wrd_path_size = this->warehouse_head_dir.length();

     size_t path_size = name_size + wrd_path_size;

     for(size_t i=0;i<wrd_path_size;i++){

         wrd_path->push_back(this->warehouse_head_dir[i]);
     }

     if(opr_sis == 'w'){

        wrd_path->push_back('\\');
     }

     if(opr_sis == 'l'){

        wrd_path->push_back('/');
     }

     for(size_t i=0;i<name_size;i++){

         wrd_path->push_back(file_name[i]);
     }
}




void Source_File_Dependency_Selector::Extract_File_Name_From_Path(std::string * pointer,

     std::string string ){

     size_t string_size = string.length();

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(((string[i] == '/') || (string[i] == '\\'))){

            start_point = i+1;

            break;
        }
     }

     for(size_t i=start_point;i<string_size;i++)
     {
         pointer->push_back(string[i]) ;
     }
}


void Source_File_Dependency_Selector::Place_String(std::string * str_pointer, std::string str)
{
     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         str_pointer->push_back(str[i]);
     }

     str_pointer->shrink_to_fit();
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
         
                std::cout << "\n list - " << counter << " " << it->Header_Name;     

                std::cout << "\n list - " << counter << " " << it->dir;     

                counter++;
            }

            std::cout << "\n INCLUDED HEADER FILES NUM FOR BASE FILE:" 
            
            << ptr->at(0).base_included_hdr_num;

            std::cout << "\n INCLUDED HEADER FILES NUM FOR INCL FILE:" 
            
            << ptr->at(0).included_file_hdr_num;
         }
      }
}


std::vector<std::string> * Source_File_Dependency_Selector::Get_File_Content(std::string path){

     FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     return &FileDtPtr->FileContent;
}

std::string Source_File_Dependency_Selector::Get_Header_System_Path(std::string header_name){

     std::string sys_path;

     FileData * Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);

     sys_path = Ptr->sys_path;

     return sys_path;
}

void Source_File_Dependency_Selector::Clear_String_Memory(std::string * Pointer)
{
     if(!Pointer->empty()){

         Pointer->clear();

         Pointer->shrink_to_fit();
     }
}

void Source_File_Dependency_Selector::Construct_Dependency_Data_Extractors(){

     this->Dep_Data_Collectors = new Dependency_Data_Extractor * [8];   

     for(int i=0;i<8;i++){

        this->Dep_Data_Collectors[i] = nullptr;
     }
}

void Source_File_Dependency_Selector::Clear_Dependency_Data_Extractors(){

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

void Source_File_Dependency_Selector::Clear_Vector_Memory(std::vector<Source_File_Dependency> * pointer){

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



 void Source_File_Dependency_Selector::Clear_Temporary_String_Memory(Source_File_Dependency * temp){
 
       this->Clear_String_Memory(&temp->Header_Name);

       this->Clear_String_Memory(&temp->source_file_name);

       this->Clear_String_Memory(&temp->source_file_path);

       this->Clear_String_Memory(&temp->header_sys_path);

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

std::string Source_File_Dependency_Selector::Get_Warehouse_Headers_Dir(){

     return this->Info_Collector.Get_Warehouse_Headers_Dir();
}

std::string Source_File_Dependency_Selector::Get_Warehouse_Objetcs_Dir(){

     return this->Info_Collector.Get_Warehouse_Objetcs_Dir();
}

std::string Source_File_Dependency_Selector::Get_Warehouse_Path(){

     return this->Info_Collector.Get_Warehouse_Path();
}
