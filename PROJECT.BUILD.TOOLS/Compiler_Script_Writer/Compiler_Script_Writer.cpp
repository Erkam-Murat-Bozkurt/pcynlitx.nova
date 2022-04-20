

#include "Compiler_Script_Writer.h"

Compiler_Script_Writer::Compiler_Script_Writer(){

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->compiler_output_location = nullptr;

     this->headers_locations = nullptr;

     this->object_files_location = nullptr;

     this->script_path = nullptr;

     this->Data_Pointer = nullptr;
}

Compiler_Script_Writer::Compiler_Script_Writer(const Compiler_Script_Writer & orig){


}

Compiler_Script_Writer::~Compiler_Script_Writer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Compiler_Script_Writer::Build_Compiler_Script(Descriptor_File_Reader * Des_File_Reader){

     this->Dir_Lister.Determine_Git_Repo_Info(Des_File_Reader);

     this->source_file_num = this->Dir_Lister.Get_Source_File_Number();

     if(this->source_file_num > 0){

        this->Initialize_Data_Structures();

        this->Determine_Script_Information();

        this->Determine_Header_Files_Inclusion_Number();

        this->Determine_Make_File_Names();

        this->Determine_Compiler_Order();

        if(Des_File_Reader->Get_Warehouse_Location() == nullptr){

            std::cout << "\n There is no any decleration about";
            std::cout << "\n project warehouse location";

            exit(0);
        }

        char * warehouse_path = Des_File_Reader->Get_Warehouse_Location();

        this->Determine_Warehouse_Paths(warehouse_path);

        this->Write_The_Script(warehouse_path);
     }
}

void Compiler_Script_Writer::Determine_Script_Information(){

     for(int i=0;i<this->source_file_num;i++){

        this->Determine_Source_File_Compilation_Information(i,'w');
     }
}

void Compiler_Script_Writer::Determine_Source_File_Compilation_Information(int dir_num,

     char operating_sis){

     char * src_file_name = this->Dir_Lister.Get_Source_File_Name(dir_num);

     this->Place_String(&this->Data_Pointer[dir_num].source_file_name,src_file_name);

     char * src_dir  = this->Dir_Lister.Get_Source_File_Directory(dir_num);


     this->Place_String(&this->Data_Pointer[dir_num].source_file_dir,src_dir);


     char * header_file_path = this->Dir_Lister.Get_Class_File_Header_System_Path(dir_num);


     if(header_file_path!=nullptr){

        this->Place_String(&this->Data_Pointer[dir_num].header_file_path,header_file_path);
     }
     else{

        this->Data_Pointer[dir_num].header_file_path = header_file_path;
     }

     size_t src_name_size = strlen(src_file_name);

     size_t dir_size = strlen(src_dir);


     this->Data_Pointer[dir_num].object_file_name = new char [5*src_name_size];

     int index = 0;

     for(size_t k=0;k<src_name_size;k++){

         this->Data_Pointer[dir_num].object_file_name[index] = src_file_name[k];

         index++;
     }

     this->Data_Pointer[dir_num].object_file_name[index] = '.';

     index++;

     this->Data_Pointer[dir_num].object_file_name[index] = 'o';

     index++;

     this->Data_Pointer[dir_num].object_file_name[index] = '\0';


     this->Data_Pointer[dir_num].object_file_path = new char[5*dir_size];

     index = 0;

     for(size_t k=0;k<dir_size;k++){

         this->Data_Pointer[dir_num].object_file_path[index] = src_dir[k];

         index++;
     }

     if(operating_sis == 'w'){

        if(src_dir[dir_size-1] != '\\'){

           this->Data_Pointer[dir_num].object_file_path[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(src_dir[dir_size-1] != '/'){

           this->Data_Pointer[dir_num].object_file_path[index] = '/';

           index++;
        }
     }

     for(size_t k=0;k<src_name_size;k++){

        this->Data_Pointer[dir_num].object_file_path[index] = src_file_name[k];

        index++;
     }

     this->Data_Pointer[dir_num].object_file_path[index] = '.';

     index++;

     this->Data_Pointer[dir_num].object_file_path[index] = 'o';

     index++;

     this->Data_Pointer[dir_num].object_file_path[index] = '\0';
}


void Compiler_Script_Writer::Determine_Header_Files_Inclusion_Number(){

     for(int n=0;n<this->source_file_num;n++){

         int src_head_num = this->Dir_Lister.Get_Source_File_Include_File_Number(n);

         char * src_file_name = this->Dir_Lister.Get_Source_File_Name(n);

         for(int k=0;k<src_head_num;k++){

             char * header_file_path = this->Dir_Lister.Get_Source_File_Header_System_Path(n,k);

             this->FileManager.SetFilePath(header_file_path);

             this->FileManager.FileOpen(Rf);

             this->Included_Header_Files_Number = 0;

             char include_db_key [] = "#include\"";

             this->String_Line = "";  // double_quotation_mark

             while(!this->FileManager.Control_End_of_File()){

                    this->String_Line = this->FileManager.ReadLine();

                    char * string_line = this->FileManager.Conver_Std_String_To_Char(this->String_Line);

                    this->Delete_Spaces_on_String(&string_line);

                    bool is_header_included = this->StringManager.CheckStringInclusion(string_line,include_db_key);

                    if(is_header_included){

                       this->Data_Pointer[n].dependency++;
                    }
              }

              this->FileManager.FileClose();
          }
      }
}

void Compiler_Script_Writer::Determine_Compiler_Order(){

     for(int i=0;i<this->source_file_num;i++){

           for(int j=0;j<this->source_file_num;j++){

             int dep_i = this->Data_Pointer[i].dependency;

             int dep_j = this->Data_Pointer[j].dependency;

             Compiler_Data  temp;

             if( dep_i > dep_j){

                 temp  = this->Data_Pointer[j];

                 this->Data_Pointer[j] = this->Data_Pointer[i];

                 this->Data_Pointer[i] = temp;
             }
           }
     }
}

bool Compiler_Script_Writer::Include_Line_Determiner(std::string String_Line){

     this->Include_Line_Condition = false;

     char Include_Word [] = "#include";

     size_t Include_Word_Character_Size = strlen(Include_Word);

     for(size_t i=0;i<String_Line.length();i++){

         if(String_Line[i] == Include_Word[0]){

            this->Include_Line_Condition = true;

            for(size_t k=0;k<Include_Word_Character_Size;k++){

               if(String_Line[i+k] != Include_Word[k]){

                  this->Include_Line_Condition = false;

                  break;
               }
            }

            break;
         }
     }

     return this->Include_Line_Condition;
}

void Compiler_Script_Writer::Determine_Warehouse_Paths(char * warehouse_path){

     size_t warehouse_path_size = strlen(warehouse_path);

     char script_path_add [] = "Compiler_Script.ps1";

     char headers_location_add [] = "PROJECT.HEADER.FILES";

     char object_files_location_add [] = "PROJECT.OBJECT.FILES";

     char compiler_output_location_add [] = "Compiler_Output.txt";

     size_t script_path_size = warehouse_path_size + strlen(script_path_add);

     size_t headers_location_size = warehouse_path_size + strlen(headers_location_add);

     size_t object_files_location_size = warehouse_path_size + strlen(object_files_location_add);

     size_t compiler_output_location_size = warehouse_path_size + strlen(compiler_output_location_add);

     this->script_path = new char [5*script_path_size];

     this->headers_locations = new char [5*headers_location_size];

     this->object_files_location = new char [5*object_files_location_size];

     this->compiler_output_location = new char [5*compiler_output_location_size];

     this->Construct_Path(&this->script_path,script_path_add,warehouse_path);

     this->Construct_Path(&this->headers_locations,headers_location_add,warehouse_path);

     this->Construct_Path(&this->object_files_location,object_files_location_add,warehouse_path);

     this->Construct_Path(&this->compiler_output_location,compiler_output_location_add,warehouse_path);
}

void Compiler_Script_Writer::Determine_Make_File_Names(){

     for(int i=0;i<this->source_file_num;i++){

          char * source_file_name = this->Dir_Lister.Get_Source_File_Name(i);

          size_t file_name_size = strlen(source_file_name);

          int string_index = 0;

          this->Data_Pointer[i].make_file_name = new char [5*file_name_size];

          for(size_t k=0;k<file_name_size;k++){

              this->Data_Pointer[i].make_file_name[string_index] = source_file_name[k];

              string_index++;
          }

          this->Data_Pointer[i].make_file_name[string_index] = '.';

          string_index++;

          this->Data_Pointer[i].make_file_name[string_index] = 'm';

          string_index++;

          this->Data_Pointer[i].make_file_name[string_index] = 'a';

          string_index++;

          this->Data_Pointer[i].make_file_name[string_index] = 'k';

          string_index++;

          this->Data_Pointer[i].make_file_name[string_index] = 'e';

          string_index++;

          this->Data_Pointer[i].make_file_name[string_index] = '\0';
     }

}

void Compiler_Script_Writer::Write_The_Script(char * warehouse_path){

     char change_dir [] = "cd ";

     this->FileManager.SetFilePath(this->script_path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Project_Headers=\"");

     this->FileManager.WriteToFile(this->headers_locations);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Project_Objects=\"");

     this->FileManager.WriteToFile(this->object_files_location);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \" THE PROJECT RE-CONSTRUCTION STARTED\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     for(int i=0;i<this->source_file_num;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(change_dir);

         this->FileManager.WriteToFile(this->Data_Pointer[i].source_file_dir);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f ");

         this->FileManager.WriteToFile(this->Data_Pointer[i].make_file_name);

         this->FileManager.WriteToFile(" > ");

         this->FileManager.WriteToFile(this->compiler_output_location);

         this->FileManager.WriteToFile("\n");


         if(this->Data_Pointer[i].header_file_path != nullptr){

            this->FileManager.WriteToFile("\n");

            this->FileManager.WriteToFile("Copy-Item ");

            this->FileManager.WriteToFile(this->Data_Pointer[i].header_file_path);

            this->FileManager.WriteToFile(" -Destination ");

            this->FileManager.WriteToFile("$Project_Headers");

            this->FileManager.WriteToFile("\n");
         }

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("$Condition = Test-Path -Path \'");

         this->FileManager.WriteToFile(this->Data_Pointer[i].object_file_path);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if ($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path \'");

         this->FileManager.WriteToFile(this->object_files_location);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer[i].object_file_name);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("      rm \'");

         this->FileManager.WriteToFile(this->object_files_location);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer[i].object_file_name);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   }");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Move-Item -Path ");

         this->FileManager.WriteToFile(this->Data_Pointer[i].object_file_path);

         this->FileManager.WriteToFile(" -Destination $Project_Objects");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"  # ");

         this->FileManager.WriteToFile(this->Data_Pointer[i].source_file_name);


         this->FileManager.WriteToFile(" class has been compiled\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");
     }


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \" THE PROJECT RE-CONSTRUCTED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}

void Compiler_Script_Writer::Construct_Path(char ** pointer, char * string, char * warehouse_path){

     int index = 0;

     size_t warehouse_path_size = strlen(warehouse_path);

     for(size_t i=0;i<warehouse_path_size;i++){

         (*pointer)[index] = warehouse_path[i];

         index++;
     }

     if(warehouse_path[warehouse_path_size-1] != '\\'){

        (*pointer)[index] = '\\';

        index++;
     }

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string[i];

        index++;
     }

     (*pointer)[index] = '\0';
}


void Compiler_Script_Writer::Delete_Spaces_on_String(char ** pointer){

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


void Compiler_Script_Writer::Place_String(char ** pointer, char * string){

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


void Compiler_Script_Writer::Initialize_Data_Structures(){

     this->Data_Pointer = new Compiler_Data [2*this->source_file_num];

     for(int i=0;i<2*this->source_file_num;i++){

         this->Data_Pointer[i].header_file_path = nullptr;

         this->Data_Pointer[i].header_file_name = nullptr;

         this->Data_Pointer[i].object_file_name = nullptr;

         this->Data_Pointer[i].object_file_path = nullptr;

         this->Data_Pointer[i].source_file_name = nullptr;

         this->Data_Pointer[i].source_file_dir = nullptr;

         this->Data_Pointer[i].make_file_name = nullptr;

         this->Data_Pointer[i].dependency = 0;

         this->Data_Pointer[i].compile_oder = 0;
     }
}

void Compiler_Script_Writer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Data_Pointer != nullptr){

           for(int i=0;i<this->source_file_num;i++){

               this->Data_Pointer[i].dependency = 0;

               delete [] this->Data_Pointer[i].header_file_path;

               delete [] this->Data_Pointer[i].header_file_name;

               delete [] this->Data_Pointer[i].object_file_name;

               delete [] this->Data_Pointer[i].object_file_path;

               delete [] this->Data_Pointer[i].source_file_name;

               delete [] this->Data_Pointer[i].source_file_dir;

               delete [] this->Data_Pointer[i].make_file_name;


               this->Data_Pointer[i].header_file_path = nullptr;

               this->Data_Pointer[i].header_file_name = nullptr;

               this->Data_Pointer[i].object_file_name = nullptr;

               this->Data_Pointer[i].object_file_path = nullptr;

               this->Data_Pointer[i].source_file_name = nullptr;

               this->Data_Pointer[i].source_file_dir = nullptr;

               this->Data_Pointer[i].make_file_name = nullptr;
           }

           delete [] this->Data_Pointer;

           this->Data_Pointer = nullptr;
         }
     }
}
