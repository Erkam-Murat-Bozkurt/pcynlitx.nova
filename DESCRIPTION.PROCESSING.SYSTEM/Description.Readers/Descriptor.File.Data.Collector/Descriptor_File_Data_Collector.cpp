
#include "Descriptor_File_Data_Collector.hpp"

Descriptor_File_Data_Collector::Descriptor_File_Data_Collector(){

  for(int i=0;i<2;i++){

      this->Library_Directories_Record_Area[i] = 0;
      this->Library_Files_Record_Area[i] = 0;
      this->Source_File_Directories_Record_Area[i] = 0;
      this->Include_Directories_Record_Area[i] = 0;
      this->Standard_Record_Area[i] = 0;
      this->Options_Record_Area[i] = 0;
      this->Warehouse_Location_Record_Area[i] = 0;
      this->Main_File_Name_Record_Area[i] = 0;
      this->Executable_File_Name_Area[i] = 0;
      this->Root_Directory_Record_Area[i] = 0;
  }

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

     this->Determine_Root_Directory_Record_Area();

     this->Determine_Warehouse_Location_Record_Area();

     this->Determine_Standard_Record_Area();

     this->Determine_Include_Directories_Record_Area();

     this->Determine_Source_File_Directories_Record_Area();

     this->Determine_Library_Directories_Record_Area();

     this->Determine_Library_Files_Record_Area();

     this->Determine_Options_Record_Area();

     this->Determine_Main_File_Des_Record_Area();

     this->Determine_Executable_File_Name_Record_Area();
}

void Descriptor_File_Data_Collector::Receive_Descriptor_File_Path(char * path){

     size_t path_size = strlen(path);

     this->Descriptor_File_Path = new char [5*path_size];

     for(size_t i=0;i<path_size;i++){

        this->Descriptor_File_Path[i] = path[i];
     }

     this->Descriptor_File_Path[path_size] = '\0';

     this->StringManager.SetFilePath(this->Descriptor_File_Path);

     this->FileManager.SetFilePath(this->Descriptor_File_Path);
}

void Descriptor_File_Data_Collector::Determine_Root_Directory_Record_Area(){

     char key_word [] = "[PROJECT-ROOT-DIR]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);

     char start_brace [] = "{";

     char end_brace []   = "}";

     this->Root_Directory_Record_Area[0] =

           this->FindStringPoint(start_brace,keyword_line);

     int start_brace_line = this->Root_Directory_Record_Area[0];

     this->Root_Directory_Record_Area[1] =

           this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Warehouse_Location_Record_Area(){

     char key_word [] = "[PROJECT-WAREHOUSE-LOCATION]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);

     char start_brace [] = "{";

     char end_brace []   = "}";

     this->Warehouse_Location_Record_Area[0] =

         this->FindStringPoint(start_brace,keyword_line);

     int start_brace_line = this->Warehouse_Location_Record_Area[0];

         this->Warehouse_Location_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Standard_Record_Area(){

     char key_word [] = "[C++-STANDARD]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Standard_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Standard_Record_Area[0];

     this->Standard_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Include_Directories_Record_Area(){

     char key_word [] = "[INCLUDE-DIRECTORIES]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);

     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Include_Directories_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Include_Directories_Record_Area[0];

     this->Include_Directories_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);

}

void Descriptor_File_Data_Collector::Determine_Source_File_Directories_Record_Area(){

     char key_word [] = "[SOURCE-FILE-DIRECTORIES]";


     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Source_File_Directories_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Source_File_Directories_Record_Area[0];

     this->Source_File_Directories_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}


void Descriptor_File_Data_Collector::Determine_Library_Directories_Record_Area(){

     char key_word [] = "[LIBRARY-DIRECTORIES]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Library_Directories_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Library_Directories_Record_Area[0];

     this->Library_Directories_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Library_Files_Record_Area(){

     char key_word [] = "[LIBRARY-FILES]";


     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Library_Files_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Library_Files_Record_Area[0];

     this->Library_Files_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}


void Descriptor_File_Data_Collector::Determine_Options_Record_Area(){

     char key_word [] = "[OPTIONS]";


     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Options_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Options_Record_Area[0];

     this->Options_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Main_File_Des_Record_Area(){

     char key_word [] = "[MAIN-FILE-NAMES]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Main_File_Name_Record_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Main_File_Name_Record_Area[0];

     this->Main_File_Name_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

void Descriptor_File_Data_Collector::Determine_Executable_File_Name_Record_Area(){

     char key_word [] = "[EXECUTABLE-FILE-NAMES]";


     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);


     char start_brace [] = "{";

     char end_brace []   = "}";


     this->Executable_File_Name_Area[0] =

     this->FindStringPoint(start_brace,keyword_line);


     int start_brace_line = this->Executable_File_Name_Area[0];

     this->Executable_File_Name_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

int Descriptor_File_Data_Collector::FindStringPoint(char * search_word,int startPoint){

    this->FileManager.FileOpen(Rf);

    for(int i=1;i<startPoint;i++){

        this->FileManager.ReadLine();
    }

    this->wordPosition = startPoint;

    do{
          char * string_line = this->FileManager.ReadLine_as_Cstring();

          this->Delete_Spaces_on_String(&string_line);

          if(this->FileManager.Control_End_of_File()){

              break;
          }

          if(this->StringManager.CheckStringLine(string_line)){

             this->StringManager.ReceiveFileLine(string_line);

             bool include_condition

             = this->StringManager.CheckStringInclusion(this->StringManager.GetStringBuffer(),search_word);

             if(include_condition){

                break;
             }
          }

          this->wordPosition++;


    }while(!this->FileManager.Control_End_of_File());

    this->FileManager.FileClose();

    return this->wordPosition;
}


void Descriptor_File_Data_Collector::Delete_Spaces_on_String(char ** pointer){

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

int Descriptor_File_Data_Collector::Get_Root_Directory_Record_Area(int index){

    return this->Root_Directory_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Library_Directories_Record_Area(int index) {

      return this->Library_Directories_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Library_Files_Record_Area(int index) {

      return this->Library_Files_Record_Area[index];
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

int Descriptor_File_Data_Collector::Get_Main_File_Name_Record_Area(int index){

     return this->Main_File_Name_Record_Area[index];
}

int Descriptor_File_Data_Collector::Get_Executable_File_Name_Record_Area(int index){

    return this->Executable_File_Name_Area[index];
}
