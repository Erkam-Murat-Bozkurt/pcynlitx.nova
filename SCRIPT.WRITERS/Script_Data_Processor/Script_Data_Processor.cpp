

#include "Script_Data_Processor.hpp"

Script_Data_Processor::Script_Data_Processor(char * DesPATH, char opr_sis) :

 File_Lister(DesPATH,opr_sis), Des_Reader(DesPATH),

 Data_Collector(DesPATH,opr_sis), Dep_Determiner(DesPATH,opr_sis)

{
     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->Des_Reader.Read_Descriptor_File();

     this->File_Lister.Determine_Git_Repo_Info();

     this->source_file_num 
     
     = this->File_Lister.Get_Source_File_Number();

     this->Dep_Determiner.Collect_Dependency_Information();
}


Script_Data_Processor::~Script_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Object_Memory();
   }
}


void Script_Data_Processor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();

     this->Des_Reader.Clear_Dynamic_Memory();

     this->File_Lister.Clear_Dynamic_Memory();     
}


void Script_Data_Processor::Process_Script_Data(){

     if(this->Des_Reader.Get_Warehouse_Location().empty()){

        std::cout << "\n There is no any decleration about";
        std::cout << "\n project warehouse location";

        exit(0);
     }

     this->File_Lister.Clear_Dynamic_Memory();

     std::cout << "\n this->source_file_num:" 

     << this->source_file_num;

     std::cin.get();

     if(this->source_file_num > 0){

        this->Determine_Script_Information();

        this->Determine_Script_Order();
     }
     
     std::cout << "\n The end of Process_Script_Data";

     std::cin.get();
}

void Script_Data_Processor::Determine_Script_Information(){

     for(int i=0;i<this->source_file_num;i++){

        Compiler_Data Cmp_Dt = this->Dep_Determiner.Get_Compiler_Data(i);

        this->Data_Collector.Receive_Compiler_Data(&Cmp_Dt);

        this->Data_Collector.Determine_Source_File_Compilation_Information(&this->Temp_Data,i);

        std::cout << "\n --1";

        this->Data_Collector.Determine_Header_Files_Inclusion_Number(&this->Temp_Data,i);

        std::cout << "\n --2";

        this->Data_Collector.Determine_Make_File_Name(&this->Temp_Data,i);

        std::cout << "\n --3";

        this->Data.push_back(this->Temp_Data);

        std::cout << "\n --4";

        this->Clear_Script_Data(&this->Temp_Data);

        std::cout << "\n --5";

        std::cout << "\n temp data loaded";
     }

     std::cout << "\n this->Data.size():" << this->Data.size();

     std::cin.get();
}


void Script_Data_Processor::Determine_Script_Order(){

     for(int i=0;i<this->source_file_num;i++){

           for(int j=i;j<this->source_file_num;j++){

             int dep_i = this->Data.at(i).dependency;

             int dep_j = this->Data.at(i).dependency;

             Script_Data temp;

             if( dep_i > dep_j){

                 temp  = this->Data.at(i);

                 this->Data.at(i) = this->Data.at(i);

                 this->Data.at(i) = temp;
             }
           }
     }
}


void Script_Data_Processor::Clear_Dynamic_Memory(){

     this->Clear_Script_Data(&this->Data);
}

std::vector<Script_Data> *  Script_Data_Processor::Get_Script_Data_Address(){

     return &this->Data;
}

Script_Data Script_Data_Processor::Get_SrcFile_Script_Data(char * file_name){

     for(int i=0;i<this->source_file_num;i++){

         std::string src_file_name = this->Data.at(i).source_file_name;

         bool is_equal = this->CString_Proccessor.CompareString(src_file_name,file_name);

         if(is_equal){

            return this->Data.at(i);
         }
     }

     std::cout << "\n There is no any script data for ";
     std::cout << file_name;

     exit(0);
}

int Script_Data_Processor::Get_Source_File_Number(){

    return this->source_file_num;
}


void Script_Data_Processor::Clear_Script_Data(std::vector<Script_Data> * ptr){

     size_t data_size = ptr->size();

     for(size_t i=0;i<data_size;i++){
     
         this->Clear_String_Vector(&ptr->at(i).header_files_git_dir);

         this->Clear_String_Vector(&ptr->at(i).header_file_names);

         this->Clear_String_Memory(&ptr->at(i).object_file_name);
         
         this->Clear_String_Memory(&ptr->at(i).object_file_path);

         this->Clear_String_Memory(&ptr->at(i).source_file_name);

         this->Clear_String_Memory(&ptr->at(i).source_file_dir);

         this->Clear_String_Memory(&ptr->at(i).source_file_git_record_dir);

         this->Clear_String_Memory(&ptr->at(i).make_file_name);

         this->Clear_String_Memory(&ptr->at(i).warehouse_path);
     }
 
}

void Script_Data_Processor::Clear_String_Memory(std::string * ptr){

     if(!ptr->empty()){
     
        ptr->clear();

        ptr->shrink_to_fit();     
     }
}

 void Script_Data_Processor::Clear_String_Vector(std::vector<std::string> * ptr){
 
      size_t data_size = ptr->size();

      for(size_t i=0;i<data_size;i++){
      
          this->Clear_String_Memory(&ptr->at(i));
      }

      ptr->clear();

      ptr->shrink_to_fit();
}


void Script_Data_Processor::Clear_Script_Data(Script_Data * ptr){

     this->Clear_String_Vector(&this->Temp_Data.header_files_git_dir);

     this->Clear_String_Vector(&this->Temp_Data.header_file_names);
  
     this->Clear_String_Memory(&this->Temp_Data.object_file_name);

     this->Clear_String_Memory(&this->Temp_Data.object_file_path);


     this->Clear_String_Memory(&this->Temp_Data.source_file_name);

     this->Clear_String_Memory(&this->Temp_Data.source_file_dir);

     this->Clear_String_Memory(&this->Temp_Data.source_file_git_record_dir);

     this->Clear_String_Memory(&this->Temp_Data.make_file_name);

     this->Clear_String_Memory(&this->Temp_Data.warehouse_path);
}
