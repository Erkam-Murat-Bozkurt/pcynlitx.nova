


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

#include "Dependency_Data_Extractor.hpp"

Dependency_Data_Extractor::Dependency_Data_Extractor(char opr_sis)

    : Header_Processor(opr_sis)
{
   this->Memory_Delete_Condition = false;
}


Dependency_Data_Extractor::~Dependency_Data_Extractor()
{
    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Object_Memory();
    }    
}


void Dependency_Data_Extractor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Header_Processor.Clear_Object_Memory();
}

void Dependency_Data_Extractor::Clear_Dynamic_Memory()
{
     this->Clear_Vector_Memory(this->External_Header_Files);

     for(size_t i=0;i<this->searched_paths.size();i++){

         this->Clear_String_Memory(this->searched_paths.at(i).path);
         this->Clear_String_Memory(this->searched_paths.at(i).name);
         this->Clear_String_Memory(this->searched_paths.at(i).combined_name);
     }

     this->searched_paths.clear();
     this->searched_paths.shrink_to_fit();
}


void Dependency_Data_Extractor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Header_Processor.Receive_Source_Code_Reader(ptr);

     this->Code_Rd = ptr;

     /*

     size_t src_file_num = this->Code_Rd->Get_Project_Files_Number();

     for(size_t i=0;i<src_file_num;i++){
    
       std::string path = this->Code_Rd->Get_File_Path(i);

       const FileData * Data = this->Code_Rd->Find_File_Data_From_Path(path);

       
       std::cout << "\n\n";
       std::cout << "\n i:"<< i;
       std::cout << "\n Path:" << Data->sys_path << "#";

       std::string combined_name = Data->combined_file_name;
       
       const FileData * Data_Combined_Name = this->Code_Rd->Find_File_Data_From_Combined_Name(combined_name);

       std::cout << "\n File path:"  << Data_Combined_Name->sys_path << "#";

       std::cout << "\n Combined Name:" << Data_Combined_Name->combined_file_name << "#";

       bool is_repo_file = this->Code_Rd->Check_Repo_File_Status_From_Combined_File_Name(Data_Combined_Name->combined_file_name);

       std::cout << "\n is_repo_file:" << is_repo_file;

       std::cout << "\n\n ";           
    }

    */
}



void Dependency_Data_Extractor::Print_Maps(){

     size_t src_file_num = this->Code_Rd->Get_Project_Files_Number();

     for(size_t i=0;i<src_file_num;i++){
    
       std::string path = this->Code_Rd->Get_File_Path(i);

       const FileData * Data = this->Code_Rd->Find_File_Data_From_Path(path);

       
       std::cout << "\n\n";
       std::cout << "\n i:"<< i;
       std::cout << "\n Path:" << Data->sys_path << "#";

       std::string combined_name = Data->combined_file_name;
       
       const FileData * Data_Combined_Name = this->Code_Rd->Find_File_Data_From_Combined_Name(combined_name);

       std::cout << "\n File path:"  << Data_Combined_Name->sys_path << "#";

       std::cout << "\n Combined Name:" << Data_Combined_Name->combined_file_name << "#";

       //bool is_repo_file = this->Code_Rd->Check_Repo_File_Status_From_Combined_File_Name(Data_Combined_Name->combined_file_name);

       //std::cout << "\n is_repo_file:" << is_repo_file;

       std::cout << "\n\n ";           
    }

    std::cout << "\n PRINT COMPLATED";
    std::cin.get();
}

void Dependency_Data_Extractor::Extract_Dependency_Tree(std::string path){

     this->Clear_Dynamic_Memory();

     this->Recursive_Dependency_Determination(path,this->searched_paths);

     this->Re_Order_Dependencies();     
}

int Dependency_Data_Extractor::Recursive_Dependency_Determination(std::string path, 

     std::vector<Search_Data> & data){

     
     Search_Data Head;

     Head.path = path;
     Head.search_complated = false;


     int inc_num = this->Search_Dependencies(Head,data);

     std::cout << "\n Dependency search for path:" << path;
     std::cout << "\n complated..";
     std::cin.get();

     for(size_t i=0;i<data.size();i++){

        if(!data.at(i).search_complated){

            inc_num =  inc_num +  this->Search_Dependencies(data.at(i),data);

            std::cout << "\n The search for " << data.at(i).path;
            std::cout << "\n complated.";
            std::cin.get();

            data.at(i).search_complated = true;

            i=0;
         }
     }


     std::cout << "\n Recursive dependency search complated";
     std::cin.get();

     return inc_num;
}



void Dependency_Data_Extractor::Re_Order_Dependencies(){

     for(size_t i=0;i<this->searched_paths.size();i++){

         std::string sub_path = this->searched_paths.at(i).path;

         std::vector<Search_Data> temp_vec;

         int inc_num = this->Recursive_Dependency_Determination(sub_path,temp_vec);

         if(inc_num != 0){

             this->searched_paths.at(i).dep_counter = temp_vec.size();
         }
         else{

               this->searched_paths.at(i).dep_counter = 0;              
         }

         temp_vec.clear();
         temp_vec.shrink_to_fit();                  
     }


     for(size_t i=0;i<this->searched_paths.size();i++){

         for(size_t j=0;j<this->searched_paths.size();j++){

             int dep_i = this->searched_paths.at(i).dep_counter;

             int dep_j = this->searched_paths.at(j).dep_counter;

             if(dep_j<dep_i){

                Search_Data temp = this->searched_paths.at(i);

                this->searched_paths.at(i) = this->searched_paths.at(j);

                this->searched_paths.at(j) = temp;
             }
         }                
     }
}


int Dependency_Data_Extractor::Search_Dependencies(Search_Data & Src_Data, std::vector<Search_Data> & data)
{

    int inclusion_number = this->Determine_Inclusion_Number(Src_Data.path);

     /*  The inclusion number determined */

    std::cout << "\n inclusion_number:" << inclusion_number;

    Src_Data.search_complated = true;


    if(inclusion_number>0){

       const std::vector<std::string> * FileContent = this->Get_File_Content(Src_Data.path);

       std::cout << "\n Src_Data.path:" << Src_Data.path;

       size_t FileSize = FileContent->size();

       //std::cout << "\n FileSize:" << FileSize;

       for(size_t k=0;k<FileSize;k++){

           std::string string_line = FileContent->at(k);

           bool is_include_decleration = this->Include_Decleration_Test(string_line); 
     
           //std::cout << "\n is_include_decleration:" << is_include_decleration;
           //std::cin.get();

           if(is_include_decleration){

              //std::cout << "\n string_line:" << string_line;
              //std::cin.get();

              bool is_new_dep = this->Find_New_Dependency(string_line,data);
           
              //std::cout << "\n is_new_dep:" << is_new_dep;


              std::string header_name = this->Find_Header_Name(string_line);

              std::string plain_header_name; // This is necessary when the header decleration is combined
      
              Search_Data temp;     // Temporary data decleration            


              const FileData * File_Data_Ptr;

              if(is_new_dep){
              
                 if(this->Is_Header_Name_Combined(header_name)){

                     File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Combined_Name(header_name);

                     this->Extract_Plain_File_Name(plain_header_name,header_name);

                     temp.name = plain_header_name;
                 }
                 else{

                     File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Name(header_name);
                                
                     temp.name = header_name;
                 }

                 std::string hdr_sys_path      =  File_Data_Ptr->sys_path;
                 std::string hdr_combined_name =  File_Data_Ptr->combined_file_name;
            
                 temp.path = hdr_sys_path;
                 temp.combined_name = hdr_combined_name;
                 temp.search_complated = false;

                 data.push_back(temp);
              }    
           }   
        }      
    }
    else{

             if(this->Find_New_Dependency_From_Path(Src_Data.path,data)){

               const FileData * File_Data_Ptr = this->Code_Rd->Find_File_Data_From_Path(Src_Data.path);

               std::string hdr_sys_path      =  File_Data_Ptr->sys_path;   
               std::string hdr_combined_name =  File_Data_Ptr->combined_file_name;
               std::string header_name       =  File_Data_Ptr->file_name;

               Search_Data temp;
               temp.path = hdr_sys_path;
               temp.combined_name = hdr_combined_name;
               temp.name = header_name;
               temp.search_complated = false;

               data.push_back(temp);
            }
      }


      data.shrink_to_fit();

      return inclusion_number;
}



bool Dependency_Data_Extractor::Find_New_Dependency(std::string string_line, std::vector<Search_Data> & data){

     bool is_new_dependency = false;
        
     std::string header_name  = this->Find_Header_Name(string_line);

     bool is_repo_file = false;

     //this->Print_Maps();


     
     if(this->Is_Header_Name_Combined(header_name)){

        std::cout << "\n It is an combined_name";
        std::cout << "\n header_name:" << header_name << "#";
        std::cin.get();

        /*     
        is_repo_file = this->Code_Rd->Check_Repo_File_Status_From_Combined_File_Name(header_name);

        std::cout << "\n is_repo_file:" << is_repo_file;
        */

        const FileData * data = this->Code_Rd->Find_File_Data_From_Combined_Name(header_name);

        std::cout << "\n data->combined_file_name"  << data->combined_file_name;

        std::cin.get();
     }
     else{

          is_repo_file = this->Code_Rd->Check_Repo_File_Status(header_name);
     }


     if(is_repo_file){

        bool is_repo_header_file = this->Is_This_Repo_HeaderFile(header_name);

        if(is_repo_header_file){

           bool is_already_searched = this->Is_This_File_Aready_Searched(header_name,data);

           if(!is_already_searched){

               is_new_dependency = true;

               return is_new_dependency;
            }
        }
     }
     else{

          this->Insert_External_Header_File_For_Dependency(header_name);

          is_new_dependency = false;

          return is_new_dependency;
     }
     
     return is_new_dependency;
}



bool Dependency_Data_Extractor::Is_Header_Name_Combined(std::string name)
{
     bool is_combined = false;

     size_t name_size = name.length();

     for(size_t i=0;i<name_size;i++){

         if(((name[i]=='/') || (name[i]=='\\'))){

            is_combined = true;

            return is_combined;
         }
     }

     return is_combined;
}



bool Dependency_Data_Extractor::Find_New_Dependency_From_Path(std::string path, 

     std::vector<Search_Data> & data){

     bool is_new_dependency = false;

     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     bool is_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

     if(is_header){

        if(this->Code_Rd->Is_This_Repo_File(FileDtPtr->sys_path)){

            if(!this->Is_This_File_Aready_Searched(FileDtPtr->file_name,data)){

               is_new_dependency = true;

               return is_new_dependency;
            }
        }
     }

     return is_new_dependency;
}


int Dependency_Data_Extractor::Determine_Inclusion_Number(std::string path){

     int inclusion_number = 0;

     const std::vector<std::string> * FileContent = this->Get_File_Content(path);

     size_t FileSize = FileContent->size();


     for(size_t k=0;k<FileSize;k++){

         std::string string_line = FileContent->at(k);

         bool is_include_decleration = this->Include_Decleration_Test(string_line);

         if(is_include_decleration){

            inclusion_number++;
         }

         this->Clear_String_Memory(string_line);
     }

     return inclusion_number;
}



bool Dependency_Data_Extractor::Is_This_Repo_HeaderFile(std::string name)
{
     bool is_this_a_repo_header = false;

     const FileData * FileDtPtr;

     bool is_combined_header = this->Is_Header_Name_Combined(name);

     if(is_combined_header){

         FileDtPtr = this->Code_Rd->Find_File_Data_From_Combined_Name(name);
     }
     else{

         FileDtPtr = this->Code_Rd->Find_File_Data_From_Name(name);

     }

     bool is_header = this->Header_Processor.Is_Header(FileDtPtr->sys_path);

     if(is_header){

        if(is_combined_header){

            if(this->Code_Rd->Check_Repo_File_Status_From_Combined_File_Name(name)){

                is_this_a_repo_header = true;

                return is_this_a_repo_header;
            }
        }
     }

     return is_this_a_repo_header;
}




bool Dependency_Data_Extractor::Is_This_File_Aready_Searched(std::string name, std::vector<Search_Data> & data)
{
     this->This_File_Exist = false;

     size_t list_size = data.size();

     for(int i=0;i<list_size;i++){

         bool is_exist_on_the_list =
    
         this->CompareString(name,data.at(i).name);

         if(is_exist_on_the_list){

            this->This_File_Exist = true;

            return this->This_File_Exist;
         }
      }

      return this->This_File_Exist;
}




std::string Dependency_Data_Extractor::Find_Header_Name(std::string string)
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

     std::string header_name;

     for(size_t i=start_point;i<end_point;i++){

         header_name.push_back(string[i]);
     }


     return header_name;
}


void Dependency_Data_Extractor::Extract_Plain_File_Name(std::string & plain_name, std::string combined_name){
 
     size_t name_size   = combined_name.length();

     size_t start_point = 0;

     int dir_symbol_number = 0;

     for(size_t i=0;i<name_size;i++){

         if(combined_name[i]=='/'){

            dir_symbol_number++;

            start_point = i+1;
         }

         if(combined_name[i]=='\\'){

            dir_symbol_number++;

            start_point = i+1;
         }
    }


}


bool Dependency_Data_Extractor::Include_Decleration_Test(std::string string)
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



void Dependency_Data_Extractor::Extract_File_Name_From_Path(std::string * pointer,

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


void Dependency_Data_Extractor::Insert_External_Header_File_For_Dependency(std::string hdr_file_name){

     this->External_Header_Files.push_back(hdr_file_name);

     this->External_Header_Files.shrink_to_fit();
}

bool Dependency_Data_Extractor::CompareString(std::string firstString, 

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



void Dependency_Data_Extractor::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         std::vector<std::string>::iterator it;

         auto begin = vec.begin();

         auto end   = vec.end();

         for(auto it=begin;it<end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}

void Dependency_Data_Extractor::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}


const std::vector<std::string> * Dependency_Data_Extractor::Get_File_Content(std::string path) const 
{
     const FileData * FileDtPtr = this->Code_Rd->Find_File_Data_From_Path(path);

     return &FileDtPtr->FileContent;
}

std::string Dependency_Data_Extractor::Get_Header_System_Path(std::string header_name) const
{
     return this->Code_Rd->Find_File_Data_From_Name(header_name)->sys_path;
}


const std::vector<std::string> * Dependency_Data_Extractor::Get_External_Header_Files() const
{

     return &this->External_Header_Files;
}

std::vector<Search_Data> * Dependency_Data_Extractor::Get_Search_Data(){

      return &this->searched_paths;
}