
#include "Descriptor_File_Data_Collector.hpp"

Descriptor_File_Data_Collector::Descriptor_File_Data_Collector(){

  for(int i=0;i<2;i++){

      this->Library_Directories_Record_Area[i] = 0;
      this->Source_File_Directories_Record_Area[i] = 0;
      this->Include_Directories_Record_Area[i] = 0;
      this->Standard_Record_Area[i] = 0;
      this->Options_Record_Area[i] = 0;
      this->Warehouse_Location_Record_Area[i] = 0;
  }

  this->File_Content_Size = 0;
  this->Library_Directories_Record_Number = 0;
  this->Source_File_Directories_Record_Number = 0;
  this->Include_Directories_Record_Number = 0;
  this->Memory_Delete_Condition = true;

  this->Descriptor_File_Path = nullptr;

}

Descriptor_File_Data_Collector::Descriptor_File_Data_Collector(const Descriptor_File_Data_Collector & orig){


}

Descriptor_File_Data_Collector::~Descriptor_File_Data_Collector(){

  if(!this->Memory_Delete_Condition){

     this->Clear_Dynamic_Memory();
  }
}


void Descriptor_File_Data_Collector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Descriptor_File_Path != nullptr){

            delete [] this->Descriptor_File_Path;
         }

         this->Descriptor_File_Path = nullptr;
     }
}


void Descriptor_File_Data_Collector::Collect_Descriptor_File_Data(char * path){

     this->Receive_Descriptor_File_Path(path);

     this->Determine_Warehouse_Location_Record_Area();

     this->Determine_Standard_Record_Area();

     this->Determine_Include_Directories_Record_Area();

     this->Determine_Source_File_Directories_Record_Area();

     this->Determine_Library_Directories_Record_Area();

     this->Determine_Options_Record_Area();
}

void Descriptor_File_Data_Collector::Receive_Descriptor_File_Path(char * path){

     size_t path_size = strlen(path);

     this->Descriptor_File_Path = new char [5*path_size];

     for(size_t i=0;i<path_size;i++){

        this->Descriptor_File_Path[i] = path[i];
     }

     this->Descriptor_File_Path[path_size] = '\0';

     this->StringManager.SetFilePath(this->Descriptor_File_Path);
}

void Descriptor_File_Data_Collector::Determine_Warehouse_Location_Record_Area(){

     char warehouse_key [] = "[PROJECT WAREHOUSE LOCATION]";

     char include_key [] = "[C++ STANDARD]";

     int record_stard = 0, record_end = 0;

     this->Warehouse_Location_Record_Area[0] =

           this->StringManager.FindNextWordLine(warehouse_key,record_stard) + 2;

     this->Warehouse_Location_Record_Area[1] =

           this->StringManager.FindNextWordLine(include_key,record_end);
}

void Descriptor_File_Data_Collector::Determine_Standard_Record_Area(){

     char standard_key [] = "[C++ STANDARD]";

     char include_key [] = "[INCLUDE DIRECTORIES]";

     int record_stard = 0, record_end = 0;


     this->Standard_Record_Area[0] =

                this->StringManager.FindNextWordLine(standard_key,record_stard) + 2;

     this->Standard_Record_Area[1] =

                this->StringManager.FindNextWordLine(include_key,record_end);

}

void Descriptor_File_Data_Collector::Determine_Include_Directories_Record_Area(){

     char include_key [] = "[INCLUDE DIRECTORIES]";

     char source_files_key [] = "[SOURCE FILE DIRECTORIES]";

     int record_stard = 0, record_end = 0;


     this->Include_Directories_Record_Area[0] =

              this->StringManager.FindNextWordLine(include_key,record_stard) + 2;

     this->Include_Directories_Record_Area[1] =

              this->StringManager.FindNextWordLine(source_files_key,record_end);
}

void Descriptor_File_Data_Collector::Determine_Source_File_Directories_Record_Area(){

     char source_files_key [] = "[SOURCE FILE DIRECTORIES]";

     char library_dir_key [] = "[LIBRARY DIRECTORIES]";


     int record_stard = 0, record_end = 0;

     this->Source_File_Directories_Record_Area[0] =

                this->StringManager.FindNextWordLine(source_files_key,record_stard) + 2;

     this->Source_File_Directories_Record_Area[1] =

                this->StringManager.FindNextWordLine(library_dir_key,record_end);
}


void Descriptor_File_Data_Collector::Determine_Library_Directories_Record_Area(){

     char library_dir_key [] = "[LIBRARY DIRECTORIES]";

     char options_key [] = "[OPTIONS]";

     int record_stard = 0, record_end = 0;

     this->Library_Directories_Record_Area[0] =

              this->StringManager.FindNextWordLine(library_dir_key,record_stard) + 2;

     this->Library_Directories_Record_Area[1] =

              this->StringManager.FindNextWordLine(options_key,record_end);
}

void Descriptor_File_Data_Collector::Determine_Options_Record_Area(){

     char options_key [] = "[OPTIONS]";

     char end_key [] = "[END]";

     int record_stard = 0, record_end = 0;

     this->Options_Record_Area[0] =

            this->StringManager.FindNextWordLine(options_key,record_stard) + 2;

     this->Options_Record_Area[1] =

            this->StringManager.FindNextWordLine(end_key,record_end);
}

int Descriptor_File_Data_Collector::Get_Library_Directories_Record_Area(int index) {

      return this->Library_Directories_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Source_File_Directories_Record_Area(int index) {

     return this->Source_File_Directories_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Include_Directories_Record_Area(int index) {

      return this->Include_Directories_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Standard_Record_Area(int index) {

      return this->Standard_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Options_Record_Area(int index){

     return this->Options_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Warehouse_Location_Record_Area(int index){

    return this->Warehouse_Location_Record_Area[index];
}
