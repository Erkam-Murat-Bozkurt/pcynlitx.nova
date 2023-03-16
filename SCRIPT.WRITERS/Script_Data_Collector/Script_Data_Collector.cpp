
#include "Script_Data_Collector.hpp"

Script_Data_Collector::Script_Data_Collector(char * DesPATH, char opr_sis) :
  
  Dep_Determiner(DesPATH,opr_sis), Des_File_Reader(DesPATH),

  Dir_Lister(DesPATH,opr_sis)
{
     this->Memory_Delete_Condition = false;

     this->Src_Data_Pointer = nullptr;

     this->Des_File_Reader.Read_Descriptor_File();

     this->Dir_Lister.Determine_Git_Repo_Info();

     this->warehouse_path = this->Des_File_Reader.Get_Warehouse_Location();

     this->opr_sis = opr_sis;
}

Script_Data_Collector::~Script_Data_Collector(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Src_Data_Pointer = nullptr;

      this->warehouse_path = nullptr;

      this->Dep_Determiner.Clear_Dynamic_Memory();

      this->Dir_Lister.Clear_Dynamic_Memory();
   }
}


void Script_Data_Collector::Receive_Compiler_Data(Compiler_Data * ptr){

     this->Cmp_Data_Ptr = ptr;
}

void Script_Data_Collector::Determine_Source_File_Compilation_Information(Script_Data * ptr,

     int src_num){

     ptr->warehouse_path = this->warehouse_path;

     std::string git_record_dir = this->Dir_Lister.Get_Source_File_Git_Record_Directory(src_num);


     this->Place_String(&ptr->source_file_git_record_dir,git_record_dir);


     std::string src_file_name = this->Dir_Lister.Get_Source_File_Name(src_num);


     this->Place_String(&ptr->source_file_name,src_file_name);



     std::string src_dir = this->Dir_Lister.Get_Source_File_Directory(src_num);

     this->Place_String(&ptr->source_file_dir,src_dir);




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


void Script_Data_Collector::Delete_Spaces_on_String(std::string * str){

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


void Script_Data_Collector::Clear_Data_Memory(Script_Data * ptr, int src_num){

     ptr->dependency = 0;

     this->Clear_Vector_Memory(&ptr->header_files_git_dir);

     this->Clear_Vector_Memory(&ptr->header_file_names);

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
