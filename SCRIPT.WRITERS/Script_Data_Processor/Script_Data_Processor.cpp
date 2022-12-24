

#include "Script_Data_Processor.hpp"

Script_Data_Processor::Script_Data_Processor(){

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->Data_Pointer = nullptr;
}

Script_Data_Processor::Script_Data_Processor(const Script_Data_Processor & orig){


}

Script_Data_Processor::~Script_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();

       std::cout << "\n After Script_Data_Processor::Clear_Dynamic_Memory()";
   }
}

void Script_Data_Processor::Process_Script_Data(Descriptor_File_Reader * Des_File_Reader){

     if(Des_File_Reader->Get_Warehouse_Location() == nullptr){

        std::cout << "\n There is no any decleration about";
        std::cout << "\n project warehouse location";

        exit(0);
     }

     this->Dir_Lister.Determine_Git_Repo_Info(Des_File_Reader);

     this->source_file_num = this->Dir_Lister.Get_Source_File_Number();

     this->Dir_Lister.Clear_Dynamic_Memory();

     this->Data_Collector.Receive_Descriptor_File_Reader(Des_File_Reader);

     if(this->source_file_num > 0){

        this->Initialize_Data_Structures();

        this->Determine_Script_Information();

        this->Determine_Header_Files_Inclusion_Number();

        this->Determine_Make_File_Names();

        this->Determine_Script_Order();
     }
}

void Script_Data_Processor::Determine_Script_Information(){

     for(int i=0;i<this->source_file_num;i++){

        this->Data_Collector.Determine_Source_File_Compilation_Information(&this->Data_Pointer[i],i,'w');
     }
}

void Script_Data_Processor::Determine_Header_Files_Inclusion_Number(){

     for(int n=0;n<this->source_file_num;n++){

        this->Data_Collector.Determine_Header_Files_Inclusion_Number(&this->Data_Pointer[n],n);
     }
}

void Script_Data_Processor::Determine_Script_Order(){

     for(int i=0;i<this->source_file_num;i++){

           for(int j=i;j<this->source_file_num;j++){

             int dep_i = this->Data_Pointer[i].dependency;

             int dep_j = this->Data_Pointer[j].dependency;

             Script_Data temp;

             if( dep_i > dep_j){

                 temp  = this->Data_Pointer[j];

                 this->Data_Pointer[j] = this->Data_Pointer[i];

                 this->Data_Pointer[i] = temp;
             }
           }
     }
}

void Script_Data_Processor::Determine_Make_File_Names()
{
     for(int i=0;i<this->source_file_num;i++){

         this->Data_Collector.Determine_Make_File_Name(&this->Data_Pointer[i],i);
     }
}

void Script_Data_Processor::Initialize_Data_Structures(){

     this->Memory_Delete_Condition = false;

     this->Data_Pointer = new Script_Data [2*this->source_file_num];

     for(int i=0;i<2*this->source_file_num;i++){

         this->Data_Collector.Initialize_Data_Structure(&this->Data_Pointer[i],i);
     }
}

void Script_Data_Processor::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Data_Pointer != nullptr){

           for(int i=0;i<this->source_file_num;i++){

               this->Data_Collector.Clear_Data_Memory(&this->Data_Pointer[i],i);
           }

           delete [] this->Data_Pointer;

           this->Data_Pointer = nullptr;
         }
     }

     std::cout << "\n After Script_Data_Processor::Clear_Dynamic_Memory()";

     std::cin.get();
}

Script_Data * Script_Data_Processor::Get_Script_Data(){

     return this->Data_Pointer;
}

Script_Data Script_Data_Processor::Get_SrcFile_Script_Data(char * file_name){

     for(int i=0;i<this->source_file_num;i++){

         char * src_file_name = this->Data_Pointer[i].source_file_name;

         bool is_equal = this->CString_Proccessor.CompareString(src_file_name,file_name);

         if(is_equal){

            return this->Data_Pointer[i];
         }
     }

     std::cout << "\n There is no any script data for ";
     std::cout << file_name;

     exit(0);
}

int Script_Data_Processor::Get_Source_File_Number(){

    return this->source_file_num;
}
