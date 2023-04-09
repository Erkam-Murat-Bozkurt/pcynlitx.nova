
#include "Script_Data_Collector.hpp"

Script_Data_Collector::Script_Data_Collector(char * DesPATH, char opr_sis) :
  
  Dep_Determiner(DesPATH,opr_sis), Des_File_Reader(DesPATH),

  Dir_Lister(DesPATH,opr_sis)
{
     this->Memory_Delete_Condition = false;

     this->Src_Data_Pointer = nullptr;

     this->Des_File_Reader.Read_Descriptor_File();

     this->Dir_Lister.Determine_Git_Repo_Info();

     this->Build_Dt = this->Dir_Lister.Get_Build_System_Data_Address();

     this->warehouse_path = this->Des_File_Reader.Get_Warehouse_Location();

     this->opr_sis = opr_sis;
}

Script_Data_Collector::~Script_Data_Collector(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Dep_Determiner.Clear_Dynamic_Memory();

      this->Dir_Lister.Clear_Dynamic_Memory();      
   }
}


void Script_Data_Collector::Receive_Compiler_Data(Compiler_Data * ptr){

     this->Cmp_Data_Ptr = ptr;
}

void Script_Data_Collector::Determine_Source_File_Compilation_Information(Script_Data * ptr,

     std::string header_name){

     ptr->warehouse_path = this->warehouse_path;


     int record_index = 0;

     this->Find_Data_Record_Index(header_name,record_index);

     /*

     std::cout << "\n src_hd_git_dir:" << this->Build_Dt->at(record_index).git_record_dir;

     std::cout << "\n File_Name:" << this->Build_Dt->at(record_index).File_Name;

     std::cout << "\n is_this_a_source_file:" << this->Build_Dt->at(record_index).is_this_a_source_file;

     std::cout << "\n is_this_a_header_file:" << this->Build_Dt->at(record_index).is_this_a_header_file;

     std::cout << "\n File_Name_With_Ext:" << this->Build_Dt->at(record_index).File_Name_With_Ext;

     std::cout << "\n class_header_file_name:" << this->Build_Dt->at(record_index).class_header_file_name;

     std::cout << "\n class_header_file_path:" << this->Build_Dt->at(record_index).class_header_file_path;

     std::cin.get();         

     */


     std::string git_record_dir = this->Build_Dt->at(record_index).git_record_dir;


     this->Place_String(&ptr->source_file_git_record_dir,git_record_dir);



     std::string src_file_name = this->Build_Dt->at(record_index).File_Name_With_Ext;


     this->Place_String(&ptr->source_file_name,src_file_name);


     

     std::string src_dir = this->Build_Dt->at(record_index).File_Directory;

     this->Place_String(&ptr->source_file_dir,src_dir);

     /*

     std::string Hdr_Name = this->Build_Dt->at(src_num).class_header_file_name;

     std::cout << "\n Header_Name:" << Hdr_Name;

     std::cout << "\n this->Cmp_Data_Ptr->header_name:" << this->Cmp_Data_Ptr->header_name;

     std::string src_hd_git_dir;

     this->Find_Git_Record_Dir(Hdr_Name,src_hd_git_dir);

     std::cout << "\n src_hd_git_dir:" << src_hd_git_dir;


     this->Find_Data_Record_Index(Hdr_Name,record_index);


     std::cout << "\n src_hd_git_dir:" << this->Build_Dt->at(record_index).git_record_dir;

     exit(0);

     //std::cin.get();

    */

    /*

     size_t dep_dat_size = this->Cmp_Data_Ptr->dependent_headers.size();

     for(size_t i=0;i<dep_dat_size;i++){
     
         int data_record_index = 0;

         std::string dep_header = this->Cmp_Data_Ptr->dependent_headers.at(i);

         this->Find_Data_Record_Index(dep_header,data_record_index);


     }

     */
     
     /*


     int src_head_num =

     this->Dir_Lister.Get_Source_File_Include_File_Number(src_num);

     ptr->included_header_num = src_head_num;


     if(src_head_num>0){

         for(int i=0;i<src_head_num;i++){

             std::string src_hd_git_dir

               = this->Dir_Lister.Get_Source_File_Header_Git_Record_Dir(src_num,i);

             std::string src_hd_name

               =  this->Dir_Lister.Get_Source_File_Header(src_num,i);

             ptr->header_files_git_dir.push_back(src_hd_git_dir);

             ptr->header_file_names.push_back(src_hd_name);
         }
     }


     ptr->header_files_git_dir.shrink_to_fit();
     ptr->header_file_names.shrink_to_fit();

     */


     size_t src_name_size = src_file_name.length();
     
     for(size_t k=0;k<src_name_size;k++){

         ptr->object_file_name.push_back(src_file_name[k]);
     }

     ptr->object_file_name.push_back('.');
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
     }

     ptr->object_file_path.push_back('.');

     ptr->object_file_path.push_back('o');     

     ptr->object_file_path.shrink_to_fit();   
}


void Script_Data_Collector::Determine_Header_Files_Inclusion_Number(Script_Data * ptr,

     int src_num)
{
     // THIS MEMBER FUNCTION DETERMINES COMPLIATION PRIORITY OF THE SOURCE FILE

     //std::string src_file_path = this->Dir_Lister.Get_Source_File_System_Path(src_num);

     //this->Dep_Determiner.Collect_Dependency_Information(src_file_path);

     // Dependencies of a particular source file.

     //size_t dep_size = this->Dep_Determiner.Get_Compiler_Data_Size();

     ptr->dependency = this->Cmp_Data_Ptr->priority;
}


void Script_Data_Collector::Determine_Make_File_Name(Script_Data * ptr, int src_num){

     std::string src_name = this->Dir_Lister.Get_Source_File_Name(src_num);

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

         std::cout << "\n FileName:" << FileName;

         std::cin.get();

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

     //this->Clear_Vector_Memory(&ptr->header_files_git_dir);

     //this->Clear_Vector_Memory(&ptr->header_file_names);

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
