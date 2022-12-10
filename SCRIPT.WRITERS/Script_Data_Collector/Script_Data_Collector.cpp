
#include "Script_Data_Collector.hpp"

Script_Data_Collector::Script_Data_Collector(){

     this->Memory_Delete_Condition = true;
     this->Src_Data_Pointer = nullptr;
     this->warehouse_path = nullptr;
}

Script_Data_Collector::Script_Data_Collector(const Script_Data_Collector & orig){


}

Script_Data_Collector::~Script_Data_Collector(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Src_Data_Pointer = nullptr;

      this->warehouse_path = nullptr;
   }
}

void Script_Data_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Des_File_Reader = Des_Reader;

     this->Dir_Lister.Determine_Git_Repo_Info(this->Des_File_Reader);

     this->Dep_Determiner.Receive_Descriptor_File_Reader(this->Des_File_Reader);

     this->warehouse_path = this->Des_File_Reader->Get_Warehouse_Location();
}

void Script_Data_Collector::Determine_Source_File_Compilation_Information(Script_Data * Src_Data_Pointer,

     int src_num, char operating_sis){


     Src_Data_Pointer->warehouse_path = this->warehouse_path;

     char * git_record_dir = this->Dir_Lister.Get_Source_File_Git_Record_Directory(src_num);

     this->Place_String(&Src_Data_Pointer->source_file_git_record_dir,git_record_dir);


     char * src_file_name = this->Dir_Lister.Get_Source_File_Name(src_num);

     this->Place_String(&Src_Data_Pointer->source_file_name,src_file_name);


     char * src_dir = this->Dir_Lister.Get_Source_File_Directory(src_num);

     this->Place_String(&Src_Data_Pointer->source_file_dir,src_dir);



     int src_head_num =

     this->Dir_Lister.Get_Source_File_Include_File_Number(src_num);

     Src_Data_Pointer->included_header_num = src_head_num;


     if(src_head_num>0){

        Src_Data_Pointer->header_files_git_dir = new char * [5*src_head_num];

        Src_Data_Pointer->header_file_names = new char * [5*src_head_num];

         for(int i=0;i<src_head_num;i++){

             char * src_hd_git_dir

               = this->Dir_Lister.Get_Source_File_Header_Git_Record_Dir(src_num,i);

             char * src_hd_name

               =  this->Dir_Lister.Get_Source_File_Header(src_num,i);

             this->Place_String(&Src_Data_Pointer->header_files_git_dir[i],src_hd_git_dir);

             this->Place_String(&Src_Data_Pointer->header_file_names[i],src_hd_name);
         }
     }


     size_t src_name_size = strlen(src_file_name);

     size_t dir_size = strlen(src_dir);


     Src_Data_Pointer->object_file_name = new char [5*src_name_size];


     int index = 0;

     for(size_t k=0;k<src_name_size;k++){

         Src_Data_Pointer->object_file_name[index] = src_file_name[k];

         index++;
     }

     Src_Data_Pointer->object_file_name[index] = '.';

     index++;

     Src_Data_Pointer->object_file_name[index] = 'o';

     index++;

     Src_Data_Pointer->object_file_name[index] = '\0';



     Src_Data_Pointer->object_file_path = new char[5*dir_size];

     index = 0;

     for(size_t k=0;k<dir_size;k++){

         Src_Data_Pointer->object_file_path[index] = src_dir[k];

         index++;
     }

     if(operating_sis == 'w'){

        if(src_dir[dir_size-1] != '\\'){

           Src_Data_Pointer->object_file_path[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(src_dir[dir_size-1] != '/'){

           Src_Data_Pointer->object_file_path[index] = '/';

           index++;
        }
     }

     for(size_t k=0;k<src_name_size;k++){

        Src_Data_Pointer->object_file_path[index] = src_file_name[k];

        index++;
     }

     Src_Data_Pointer->object_file_path[index] = '.';

     index++;

     Src_Data_Pointer->object_file_path[index] = 'o';

     index++;

     Src_Data_Pointer->object_file_path[index] = '\0';
}


void Script_Data_Collector::Determine_Header_Files_Inclusion_Number(Script_Data * Src_Data_Pointer,

     int src_num){

     char * src_file_path = this->Dir_Lister.Get_Source_File_System_Path(src_num);

     this->Dep_Determiner.Clear_Dynamic_Memory();

     this->Dep_Determiner.Determine_Particular_Source_File_Dependencies(src_file_path);

     // Dependencies of a particular source file.

     int dep_size = this->Dep_Determiner.Get_Dependency_List_Size();

     Src_Data_Pointer->dependency = dep_size;
}


void Script_Data_Collector::Determine_Make_File_Name(Script_Data * Src_Data_Pointer, int src_num){

     char * source_file_name = this->Dir_Lister.Get_Source_File_Name(src_num);

     size_t file_name_size = strlen(source_file_name);

     int string_index = 0;

     Src_Data_Pointer->make_file_name = new char [5*file_name_size];

     for(size_t k=0;k<file_name_size;k++){

         Src_Data_Pointer->make_file_name[string_index] = source_file_name[k];

         string_index++;
     }

     Src_Data_Pointer->make_file_name[string_index] = '.';

     string_index++;

     Src_Data_Pointer->make_file_name[string_index] = 'm';

     string_index++;

     Src_Data_Pointer->make_file_name[string_index] = 'a';

     string_index++;

     Src_Data_Pointer->make_file_name[string_index] = 'k';

     string_index++;

     Src_Data_Pointer->make_file_name[string_index] = 'e';

     string_index++;

     Src_Data_Pointer->make_file_name[string_index] = '\0';
}


void Script_Data_Collector::Delete_Spaces_on_String(char ** pointer){

     size_t string_size = strlen(*pointer);

     int remove_index = 0;

     for(size_t i=0;i<string_size;i++){

         if((*pointer)[i] == ' '){

            for(size_t k=i;k<string_size;k++){

               (*pointer)[k] = (*pointer)[k+1];
            }

            remove_index++;
         }
     }

     (*pointer)[string_size - remove_index+1] = '\0';
}


void Script_Data_Collector::Initialize_Data_Structure(Script_Data * Src_Data_Pointer, int src_num){

     Src_Data_Pointer->object_file_name = nullptr;

     Src_Data_Pointer->object_file_path = nullptr;

     Src_Data_Pointer->source_file_name = nullptr;

     Src_Data_Pointer->source_file_dir = nullptr;

     Src_Data_Pointer->header_files_git_dir = nullptr;

     Src_Data_Pointer->header_file_names = nullptr;

     Src_Data_Pointer->make_file_name = nullptr;

     Src_Data_Pointer->warehouse_path = nullptr;

     Src_Data_Pointer->dependency = 0;

     Src_Data_Pointer->compile_oder = 0;
}


void Script_Data_Collector::Clear_Data_Memory(Script_Data * Src_Data_Pointer, int src_num){

     Src_Data_Pointer->dependency = 0;

     delete [] Src_Data_Pointer->object_file_name;

     delete [] Src_Data_Pointer->object_file_path;

     delete [] Src_Data_Pointer->source_file_name;

     delete [] Src_Data_Pointer->source_file_dir;

     delete [] Src_Data_Pointer->make_file_name;

     int src_head_num = Src_Data_Pointer->included_header_num;

     for(int i=0;i<src_head_num;i++){

         delete [] Src_Data_Pointer->header_files_git_dir[i];

         delete [] Src_Data_Pointer->header_file_names[i];
     }

     for(int i=0;i<src_head_num;i++){

         Src_Data_Pointer->header_files_git_dir[i] = nullptr;

         Src_Data_Pointer->header_file_names[i] = nullptr;
     }

     delete [] Src_Data_Pointer->header_files_git_dir;

     delete [] Src_Data_Pointer->header_file_names;


     Src_Data_Pointer->header_files_git_dir = nullptr;

     Src_Data_Pointer->header_file_names  = nullptr;

     Src_Data_Pointer->object_file_name = nullptr;

     Src_Data_Pointer->object_file_path = nullptr;

     Src_Data_Pointer->source_file_name = nullptr;

     Src_Data_Pointer->source_file_dir = nullptr;

     Src_Data_Pointer->make_file_name = nullptr;

     Src_Data_Pointer->warehouse_path = nullptr;
}


void Script_Data_Collector::Place_String(char ** pointer, char * string){

     size_t string_size = strlen(string);

     *pointer = new char [5*string_size];

     for(size_t i=0;i<5*string_size;i++){

         (*pointer)[i] = '\0';
     }

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string[i];
     }

     (*pointer)[string_size] = '\0';
}
