
#include "Script_Data_Collector.hpp"

Script_Data_Collector::Script_Data_Collector(char opr_sis) :
  
     Dir_Lister(opr_sis)
{
     this->Memory_Delete_Condition = false;

     this->Src_Data_Pointer = nullptr;

     this->opr_sis = opr_sis;
}

Script_Data_Collector::~Script_Data_Collector(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Dir_Lister.Clear_Dynamic_Memory();      
   }
}


void Script_Data_Collector::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->Dir_Lister.Receive_Git_Data_Processor(ptr);

     this->Dir_Lister.Determine_Git_Repo_Info();

     this->Build_Dt = this->Dir_Lister.Get_Build_System_Data_Address();
}


void Script_Data_Collector::Receive_Compiler_Data(Compiler_Data * ptr){

     this->Cmp_Data_Ptr = ptr;
}


void Script_Data_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_File_Reader = ptr;

     this->warehouse_path = this->Des_File_Reader->Get_Warehouse_Location();
}



void Script_Data_Collector::Determine_Source_File_Compilation_Information(Script_Data * ptr,

     std::string header_name){

     ptr->warehouse_path = this->warehouse_path;


     int record_index = 0;

     this->Find_Data_Record_Index(header_name,record_index);

     std::string git_record_dir = this->Build_Dt->at(record_index).git_record_dir;


     this->Place_String(&ptr->source_file_git_record_dir,git_record_dir);



     std::string src_file_name = this->Build_Dt->at(record_index).File_Name_With_Ext;


     this->Place_String(&ptr->source_file_name,src_file_name);


     

     std::string src_dir = this->Build_Dt->at(record_index).File_Directory;

     this->Place_String(&ptr->source_file_dir,src_dir);


     std::string src_name_without_ext = this->Build_Dt->at(record_index).File_Name;

     this->Place_String(&ptr->src_name_without_ext,src_name_without_ext);



     size_t src_name_size = src_file_name.length();
     
     for(size_t k=0;k<src_name_size;k++){

         ptr->object_file_name.push_back(src_file_name[k]);

         if(src_file_name[k]=='.'){

            break;
         }
     }

     ptr->object_file_name.push_back('o');
     ptr->object_file_name.shrink_to_fit();


     size_t dir_size = src_dir.length();


     for(size_t k=0;k<dir_size;k++){

         ptr->object_file_path.push_back(src_dir[k]);
     }

     if(this->opr_sis == 'w'){

        if( ptr->object_file_path.back() != '\\'){

            ptr->object_file_path.push_back('\\');
        }
     }
     else{
     
         if(this->opr_sis == 'l'){

            if(ptr->object_file_path.back() != '/'){

               ptr->object_file_path.push_back('/');
            }
         }
     }
        

     for(size_t k=0;k<src_name_size;k++){

        ptr->object_file_path.push_back(src_file_name[k]);

        if(src_file_name[k]=='.'){

          break;
        }
     }

     ptr->object_file_path.push_back('o');     

     ptr->object_file_path.shrink_to_fit();   
}


void Script_Data_Collector::Determine_Header_Files_Inclusion_Number(Script_Data * ptr,

     int src_num)
{
     // THIS MEMBER FUNCTION DETERMINES COMPLIATION PRIORITY OF THE SOURCE FILE

     ptr->dependency = this->Cmp_Data_Ptr->priority;
}


void Script_Data_Collector::Determine_Make_File_Name(Script_Data * ptr){

   
     std::string src_name = ptr->src_name_without_ext;

     std::string make_ext = ".make";

     size_t file_name_size = src_name.length();

     for(size_t k=0;k<file_name_size;k++){

         ptr->make_file_name.push_back(src_name[k]);
     }

     size_t ext_size = make_ext.length();

     for(size_t k=0;k<ext_size;k++){

         ptr->make_file_name.push_back(make_ext[k]);
     }

     ptr->make_file_name.shrink_to_fit();
}


void Script_Data_Collector::Find_Data_Record_Index(std::string header_name, int & index){

     size_t data_size = this->Build_Dt->size();

     bool directory_determination = false;

     for(size_t i=0;i<data_size;i++){

         std::string search_name;

         this->Find_File_Name(header_name,search_name);

         std::string FileName = this->Build_Dt->at(i).File_Name;

         bool is_equal = this->CompareString(search_name,FileName);

         if(is_equal){
         
            index = i;

            directory_determination = true;

            break;
         }
     }

     if(!directory_determination){
     
         std::cout << "\n Inside Script_Data_Collector::Find_Data_Record_Index";

         std::cout << "\n Record index can not be determined";

         exit(EXIT_FAILURE);     
     }
}

void Script_Data_Collector::Find_File_Name(std::string name_ext, std::string & name){

     size_t name_size = name_ext.length();

     for(size_t i=0;i<name_size;i++){
     
         if(name_ext[i] != '.'){
         
            name.push_back(name_ext[i]);
         }         
         else{
         
            break;
         }         
     }
}

void Script_Data_Collector::Find_Git_Record_Dir(std::string header_name, std::string & dir){

     size_t data_size = this->Build_Dt->size();

     bool directory_determination = false;

     for(size_t i=0;i<data_size;i++){
     
         std::string FileName = this->Build_Dt->at(i).File_Name_With_Ext;

         std::string head_name = this->Build_Dt->at(i).class_header_file_name;

         bool is_equal = this->CompareString(head_name,header_name);

         if(is_equal){
         
            dir = this->Build_Dt->at(i).git_record_dir;

            directory_determination = true;

            break;
         }
     }

     if(!directory_determination){
     
         std::cout << "\n Inside Script_Data_Collector::Find_Git_Record_Dir";

         std::cout << "\n Git record directory can not be determined";

         exit(EXIT_FAILURE);     
     }
}


bool Script_Data_Collector::CompareString(std::string firstString, 

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

void Script_Data_Collector::Clear_Data_Memory(Script_Data * ptr, int src_num){

     ptr->dependency = 0;

     this->Clear_String_Memory(&ptr->object_file_name);

     this->Clear_String_Memory(&ptr->object_file_path);

     this->Clear_String_Memory(&ptr->object_file_name);

     this->Clear_String_Memory(&ptr->source_file_name);

     this->Clear_String_Memory(&ptr->make_file_name);
}


void Script_Data_Collector::Place_String(std::string * pointer, std::string string){

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

        pointer->push_back(string[i]);
     }

     pointer->shrink_to_fit();
}


  void Script_Data_Collector::Clear_Vector_Memory(std::vector<std::string> * pointer){

       if(!pointer->empty()){

           std::vector<std::string>::iterator it;

           auto begin = pointer->begin();

           auto end   = pointer->end();

           for(auto it=begin;it<end;it++){

               if(!it->empty()){

                   it->clear();

                   it->shrink_to_fit();
               }
            }

           pointer->clear();

           pointer->shrink_to_fit();
       }
  }


void Script_Data_Collector::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
      }
}
