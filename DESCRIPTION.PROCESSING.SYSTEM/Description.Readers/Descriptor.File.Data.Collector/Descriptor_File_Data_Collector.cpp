
#include "Descriptor_File_Data_Collector.hpp"

Descriptor_File_Data_Collector::Descriptor_File_Data_Collector(char * Descriptor_File_Path) :

  StringManager(Descriptor_File_Path), FileManager(Descriptor_File_Path)
{

   size_t path_size = strlen(Descriptor_File_Path);

   this->Descriptor_File_Path = "";

   for(size_t i=0;i<path_size;i++){

       this->Descriptor_File_Path.append(1,Descriptor_File_Path[i]);
   }

   this->Initialize_Members();
}


Descriptor_File_Data_Collector::Descriptor_File_Data_Collector(std::string Descriptor_File_Path) :

  FileManager(Descriptor_File_Path), StringManager(Descriptor_File_Path)

{
   this->Initialize_Members();

   this->Descriptor_File_Path = Descriptor_File_Path;

}


Descriptor_File_Data_Collector::~Descriptor_File_Data_Collector(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}


void Descriptor_File_Data_Collector::Initialize_Members(){

     for(int i=0;i<2;i++){

        this->Library_Directories_Record_Area[i] = 0;
        this->Library_Files_Record_Area[i] = 0;
        this->Source_File_Directories_Record_Area[i] = 0;
        this->Include_Directories_Record_Area[i] = 0;
        this->Standard_Record_Area[i] = 0;
        this->Options_Record_Area[i] = 0;
        this->Warehouse_Location_Record_Area[i] = 0;
        this->Root_Directory_Record_Area[i] = 0;
     }

     this->Library_Directories_Record_Number = 0;
     this->Source_File_Directories_Record_Number = 0;
     this->Include_Directories_Record_Number = 0;
     this->Memory_Delete_Condition = true;

     this->Descriptor_File_Path = "";
}

void Descriptor_File_Data_Collector::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(!this->File_Index.empty()){

           this->File_Index.clear();
         }
     }
}


void Descriptor_File_Data_Collector::Collect_Descriptor_File_Data(){

     this->Receive_Descriptor_File_Index();

     this->Determine_Root_Directory_Record_Area();

     this->Determine_Warehouse_Location_Record_Area();

     this->Determine_Standard_Record_Area();

     this->Determine_Include_Directories_Record_Area();

     this->Determine_Source_File_Directories_Record_Area();

     this->Determine_Library_Directories_Record_Area();

     this->Determine_Library_Files_Record_Area();

     this->Determine_Options_Record_Area();
}


void Descriptor_File_Data_Collector::Receive_Descriptor_File_Index(){

     this->FileManager.FileOpen(Rf);

     this->File_Size = 0;

     int index = 0;

     do{
          std::string string_line = this->FileManager.ReadLine();

          this->Delete_Spaces_on_String(&string_line);

          this->File_Index.push_back(string_line);

          this->File_Size++;

      }while(!this->FileManager.Control_End_of_File());

      this->FileManager.FileClose();
}


void Descriptor_File_Data_Collector::Print_Descriptor_File_Index(){

     std::vector<std::string>::iterator it;

     int i=0;

     for(auto it=this->File_Index.begin();it<this->File_Index.end();it++){

         std::cout << "\n"

         << *it;
     }
}

void Descriptor_File_Data_Collector::Determine_Root_Directory_Record_Area(){

     char key_word [] = "[PROJECT-ROOT-DIR]";

     int record_stard = 1, record_end = 0;

     int keyword_line = this->FindStringPoint(key_word,record_stard);

     char start_brace [] = "{";

     char end_brace []   = "}";

     this->Root_Directory_Record_Area[0] =

           this->FindStringPoint(start_brace,keyword_line-1);

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

         this->FindStringPoint(start_brace,keyword_line-1);

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

     this->FindStringPoint(start_brace,keyword_line-1);


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

     this->FindStringPoint(start_brace,keyword_line-1);


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

     this->FindStringPoint(start_brace,keyword_line-1);


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

     this->FindStringPoint(start_brace,keyword_line-1);


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

     this->FindStringPoint(start_brace,keyword_line-1);


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

     this->FindStringPoint(start_brace,keyword_line-1);


     int start_brace_line = this->Options_Record_Area[0];

     this->Options_Record_Area[1] =

     this->FindStringPoint(end_brace,start_brace_line);
}

int Descriptor_File_Data_Collector::FindStringPoint(std::string search_word,int startPoint){

    this->wordPosition = startPoint;

    for(int i=startPoint;i<this->File_Size;i++){

       if(this->StringManager.CheckStringLine(this->File_Index[i])){

          bool include_condition

          = this->StringManager.CheckStringInclusion(this->File_Index[i],search_word);

          if(include_condition){

             this->wordPosition++;

              break;
          }
       }

       this->wordPosition++;
    }

    return this->wordPosition;
}


void Descriptor_File_Data_Collector::Delete_Spaces_on_String(std::string * pointer)
{
     size_t string_size = (*pointer).length();

     int remove_index = 0;

     for(size_t j=0;j<string_size;j++){

        for(size_t i=0;i<string_size;i++){

           if((((*pointer)[i] == ' ') || (((*pointer)[i] == '\t')))) {

              for(size_t k=i;k<string_size-1;k++){

                 (*pointer)[k] = (*pointer)[k+1];
              }

              remove_index++;
            }
        }
     }

     for(size_t i=0;i<remove_index+1;i++){

         (*pointer).pop_back();
     }
}


int Descriptor_File_Data_Collector::Get_Descriptor_File_Line_Number(){

    return this->File_Size;
}

std::string Descriptor_File_Data_Collector::Get_Descriptor_File_Line(int line_number){

      return this->File_Index[line_number];
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
