


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

    : Info_Collector(des_file_path,opr_sis), Header_Processor(des_file_path,opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->Dep_Counter = 0;

   this->descriptor_file_path = des_file_path;
}


Source_File_Dependency_Selector::~Source_File_Dependency_Selector()
{
    this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_Selector::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Object_Memory();
}

void Source_File_Dependency_Selector::Clear_Dynamic_Memory()
{

    if(!this->Dependency_Data.empty()){
    
        std::vector<std::vector<Header_Dependency>>::iterator it;

        for(auto it=this->Dependency_Data.begin();it<this->Dependency_Data.end();it++){
     
            std::vector<Header_Dependency> * ptr = &(*it);

            this->Clear_Vector_Memory(ptr);     
        }

        this->Dependency_Data.clear();

        this->Dependency_Data.shrink_to_fit();
    }


     this->Clear_String_Memory(&this->warehouse_head_dir);

     this->Clear_String_Memory(&this->descriptor_file_path);

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Dep_Counter = 0;
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

     this->Extract_Dependency_Data(path);

     this->Set_Included_Header_Number(&this->Dependent_List,this->Dep_Counter);

     this->Dep_Counter = 0;

     this->Dependency_Data.push_back(this->Dependent_List);
 
     this->Dependency_Data.shrink_to_fit();


     // THE DEPENDENCIES COLLECTED FOR THE ROOT PATH

     size_t list_size = this->Dependent_List.size();

     std::vector<Header_Dependency> Temp_List = this->Dependent_List;

     this->Clear_Vector_Memory(&this->Dependent_List);  


     for(size_t i=0;i<list_size;i++){

         Header_Dependency Data = Temp_List.at(i);

         std::string sub_path = Data.root_header_path;

         this->Extract_Dependency_Data(sub_path);

         this->Set_Included_Header_Number(&this->Dependent_List,this->Dep_Counter);

         this->Dep_Counter = 0;

         this->Dependency_Data.push_back(this->Dependent_List);

         this->Dependency_Data.shrink_to_fit();

         this->Clear_Vector_Memory(&this->Dependent_List);  
     }

     this->Clear_Vector_Memory(&this->Dependent_List);      

     this->Info_Collector.Clear_Dynamic_Memory();  
}


void Source_File_Dependency_Selector::Determine_Source_File_Dependencies(){

     this->Clear_Dynamic_Memory();

     this->Info_Collector.Clear_Dynamic_Memory();

     this->Info_Collector.Extract_Dependency_Data();

     this->warehouse_head_dir = this->Info_Collector.Get_Warehouse_Headers_Dir();

     this->Headers_Data_Ptr   = this->Info_Collector.Get_Headers_Data_Address();

     this->Extract_Dependency_Data();

     this->Dependency_Data.shrink_to_fit();   

     this->Info_Collector.Clear_Dynamic_Memory();    
}

void Source_File_Dependency_Selector::Extract_Dependency_Data(){

     size_t data_size = this->Headers_Data_Ptr->size();

     for(size_t i=0;i<data_size;i++){
     
         std::string path =this->Headers_Data_Ptr->at(i).system_path;

         this->Extract_Dependency_Data(path);

         this->Set_Included_Header_Number(&this->Dependent_List,this->Dep_Counter);

         this->Dep_Counter = 0;

         this->Dependency_Data.push_back(this->Dependent_List);
 
         this->Dependency_Data.shrink_to_fit();

         this->Clear_Vector_Memory(&this->Dependent_List);  
     }     
}

void Source_File_Dependency_Selector::Extract_Dependency_Data(std::string path){

     int inclusion_number = 0;

     FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     /*  Determination of the inclusion number */


     size_t FileSize = FileDtPtr->FileContent.size();


     for(size_t k=0;k<FileSize;k++){

         std::string tmp_string = FileDtPtr->FileContent.at(k);

         //this->Delete_Spaces_on_String(&tmp_string);

         bool is_include_decleration = this->Include_Decleration_Test(tmp_string);

         if(is_include_decleration){

            inclusion_number++;
         }

         this->Clear_String_Memory(&tmp_string);
     }

     /*  The inclusion number determined */

     if(inclusion_number>0){

        for(size_t k=0;k<FileSize;k++){

            std::string tmp_string =  FileDtPtr->FileContent.at(k);

            //this->Delete_Spaces_on_String(&tmp_string);

            bool is_include_decleration = this->Include_Decleration_Test(tmp_string);

            if(is_include_decleration){

               std::string root_header;

               std::string header_name;

               std::string wrd_path;

               this->Extract_File_Name_From_Path(&root_header,path);

               this->Extract_Header_File_Name_From_Decleration(&header_name,tmp_string);

               this->Determine_Header_Repo_Warehouse_Path(&wrd_path,

                    header_name,'w');

               bool is_repo_header_file = this->Is_This_Repo_HeaderFile(wrd_path);

               bool is_already_searched = this->Is_This_File_Aready_Searched(header_name);


               if((is_repo_header_file) && (!is_already_searched)){

                   Header_Dependency temp;
                 
                   this->Place_String(&temp.Header_Name,header_name);

                   this->Place_String(&temp.repo_warehouse_path,wrd_path);

                   this->Place_String(&temp.root_header,root_header);

                   this->Place_String(&temp.root_header_path,path);

                   temp.rcr_srch_complated= true;

                   this->Dependent_List.push_back(temp);

                   this->Dep_Counter++;
     
                   this->Clear_Temporary_String_Memory(&temp);

                   FileData * Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);

                   this->Extract_Dependency_Data(Ptr->sys_path);
               }

               this->Clear_String_Memory(&header_name);

               this->Clear_String_Memory(&wrd_path);

               this->Clear_String_Memory(&root_header);
             }

             this->Clear_String_Memory(&tmp_string);
        }
      }
      else{
      
             if(this->Dep_Counter == 0){
             
                Header_Dependency temp;

                std::string root_header;

                this->Extract_File_Name_From_Path(&root_header,path);
                 
                this->Place_String(&temp.root_header,root_header);

                this->Place_String(&temp.root_header_path,path);

                temp.rcr_srch_complated= true;

                this->Dependent_List.push_back(temp);

                this->Dependent_List.shrink_to_fit();

                this->Clear_Temporary_String_Memory(&temp);
             
             }
      }


      this->Dependent_List.shrink_to_fit();
}


void Source_File_Dependency_Selector::Set_Included_Header_Number(std::vector<Header_Dependency> * ptr, 

     int dep_num){

     std::vector<Header_Dependency>::iterator it;

     for(auto it=ptr->begin();it<ptr->end();it++){
     
         it->base_included_hdr_num = dep_num;
         it->included_file_hdr_num = 0;
     }     
}


bool Source_File_Dependency_Selector::Is_This_Repo_HeaderFile(std::string path)
{
     this->is_this_repo_header = false;

     bool is_header = this->Header_Processor.Is_Header(path);

     int index_size = this->Info_Collector.Get_Dependency_Data_Size();

     if(is_header)
     {
       for(int i=0;i<index_size;i++){

           Headers_Data temp_data = this->Info_Collector.Get_Dependency_Data(i);

           std::string repo_file_path = temp_data.repo_path;

           bool is_equal = this->CompareString(repo_file_path,path);

           this->Clear_String_Memory(&repo_file_path);

           if(is_equal){

              this->is_this_repo_header = true;

              return this->is_this_repo_header;
           };
        }
     };

     return this->is_this_repo_header;
}


bool Source_File_Dependency_Selector::Is_This_File_Aready_Searched(std::string name)
{
     this->This_File_Exist = false;

     size_t list_size = this->Dependent_List.size();

     for(int i=0;i<list_size;i++){

         bool is_exist_on_the_list =

         this->CompareString(name,this->Dependent_List[i].Header_Name);

         if(is_exist_on_the_list){

            this->This_File_Exist = true;

            return this->This_File_Exist;
         }
      }

      return this->This_File_Exist;
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



void Source_File_Dependency_Selector::Extract_Header_File_Name_From_Decleration(std::string * header_name,

       std::string string)
{

     size_t size = string.length();

     int start_point = 0;


     for(size_t k=0;k<size;k++){

         if(string[k] == '\"'){

            break;
         }
         else{

            start_point++;
         }
     }

     start_point = start_point + 1;

     size_t end_point = start_point;

     for(size_t k=start_point;k<size;k++){

         if(string[k] == '\"'){

            break;
         }
         else{

              end_point++;
         }
     }

     for(size_t i=start_point;i<end_point;i++){

         header_name->push_back(string[i]);
     }
}

void Source_File_Dependency_Selector::Delete_Spaces_on_String(std::string * str)
{
     size_t string_size = str->length();

     bool search_cond = true;

     do{

         search_cond = false;

         for(size_t i=0;i<str->length();i++){

             if((*str)[i] == ' '){

               search_cond = true;

               str->erase(i,1);
             }
         }

     }while(search_cond);

     str->shrink_to_fit();
}



bool Source_File_Dependency_Selector::Include_Decleration_Test(std::string string)
{
     this->include_decleration_cond = false;

     char include_key [] = "#include\"";  // double_quotation_mark

     bool is_this_include_dec

     = this->StringManager.CheckStringInclusion(string,include_key);

     bool char_before_sharp = false; //  sharp symbol = #

     if(string[0]!= '#'){

        char_before_sharp = true;
     }

     // In metaprograms, #include key is used on the inside code

     // Therefore, there may be false include therms which is used in the metaprograms

     // in order to produce header files. If there is a character before the sharp symbol,

     // it is a meta program code. ( simething like write{ #include \"sample.h\" })

     if(!char_before_sharp){

        if(is_this_include_dec){

           this->include_decleration_cond = true;
        }
     }

     return this->include_decleration_cond;
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


bool Source_File_Dependency_Selector::CompareString(std::string firstString, 

     std::string secondString){

     size_t firstStringLength  = firstString.length();

     size_t secondStringLength = secondString.length();

     if(firstStringLength==secondStringLength){

        for(size_t i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

            this->isStringsEqual = false;

            return this->isStringsEqual;
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

         std::vector<Header_Dependency> * ptr = &this->Dependency_Data.at(i);

         std::cout << "\n\n\n";

         std::vector<Header_Dependency>::iterator it;         

         if(ptr->size()>0){
         
            std::cout << "\n FILE RESEARCHED:" << ptr->at(0).root_header;

            int counter=0;

            for(auto it=ptr->begin();it<ptr->end();it++){
         
                std::cout << "\n list - " << counter << " " << it->Header_Name;     

                counter++;
            }

            std::cout << "\n INCLUDED HEADER FILES NUM FOR BASE FILE:" 
            
            << ptr->at(0).base_included_hdr_num;

            std::cout << "\n INCLUDED HEADER FILES NUM FOR INCL FILE:" 
            
            << ptr->at(0).included_file_hdr_num;
         }
      }
}


void Source_File_Dependency_Selector::Clear_String_Memory(std::string * Pointer)
{
     if(!Pointer->empty()){

         Pointer->clear();

         Pointer->shrink_to_fit();
     }
}

void Source_File_Dependency_Selector::Clear_Vector_Memory(std::vector<Header_Dependency> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->Header_Name.empty()){

            it->Header_Name.clear();
            it->Header_Name.shrink_to_fit();
        }

        if(!it->repo_warehouse_path.empty()){

            it->repo_warehouse_path.clear();
            it->repo_warehouse_path.shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}



 void Source_File_Dependency_Selector::Clear_Temporary_String_Memory(Header_Dependency * temp){
 

       this->Clear_String_Memory(&temp->Header_Name);

       this->Clear_String_Memory(&temp->root_header);

       this->Clear_String_Memory(&temp->root_header_path);

       this->Clear_String_Memory(&temp->repo_warehouse_path);

 }


std::vector<std::vector<Header_Dependency>> * Source_File_Dependency_Selector::Get_Dependency_List_Adress()
{
      return &this->Dependency_Data;
}


std::vector<Header_Dependency> * Source_File_Dependency_Selector::Get_Dependency_List_Element_Adress(int i)
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
