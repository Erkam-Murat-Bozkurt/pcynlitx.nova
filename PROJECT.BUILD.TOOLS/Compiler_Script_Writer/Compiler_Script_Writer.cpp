

#include "Compiler_Script_Writer.h"

Compiler_Script_Writer::Compiler_Script_Writer(){

     this->Memory_Delete_Condition = true;

     this->project_dir_num = 0;

     this->Compiler_Data_Pointer = nullptr;

     this->compiler_output_location = nullptr;

     this->headers_locations = nullptr;

     this->object_files_location = nullptr;

     this->script_path = nullptr;
}

Compiler_Script_Writer::Compiler_Script_Writer(const Compiler_Script_Writer & orig){


}

Compiler_Script_Writer::~Compiler_Script_Writer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Compiler_Script_Writer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Compiler_Data_Pointer != nullptr){

           for(int i=0;i<this->project_dir_num;i++){

               this->Compiler_Data_Pointer[i].dependency = 0;

               delete [] this->Compiler_Data_Pointer[i].header_file_path;

               delete [] this->Compiler_Data_Pointer[i].header_file_name;

               delete [] this->Compiler_Data_Pointer[i].object_file_name;

               delete [] this->Compiler_Data_Pointer[i].object_file_path;

               delete [] this->Compiler_Data_Pointer[i].source_file_name;

               delete [] this->Compiler_Data_Pointer[i].source_file_dir;

               delete [] this->Compiler_Data_Pointer[i].make_file_name;


               this->Compiler_Data_Pointer[i].header_file_path = nullptr;

               this->Compiler_Data_Pointer[i].header_file_name = nullptr;

               this->Compiler_Data_Pointer[i].object_file_name = nullptr;

               this->Compiler_Data_Pointer[i].object_file_path = nullptr;

               this->Compiler_Data_Pointer[i].source_file_name = nullptr;

               this->Compiler_Data_Pointer[i].source_file_dir = nullptr;

               this->Compiler_Data_Pointer[i].make_file_name = nullptr;
           }

           delete [] this->Compiler_Data_Pointer;

           this->Compiler_Data_Pointer = nullptr;
         }
     }
}

void Compiler_Script_Writer::Build_Compiler_Script(char * repo_dir, char * warehouse_path){

     this->Dir_Lister.Determine_Git_Repo_Info(repo_dir,warehouse_path);

     this->project_dir_num

            = this->Dir_Lister.Get_Make_Data_Number();

     if(this->project_dir_num > 0){

        this->Compiler_Data_Pointer = new Compiler_Data [2*this->project_dir_num];

        for(int i=0;i<2*this->project_dir_num;i++){

            this->Compiler_Data_Pointer[i].dependency = 0;

            this->Compiler_Data_Pointer[i].header_file_path = nullptr;

            this->Compiler_Data_Pointer[i].header_file_name = nullptr;

            this->Compiler_Data_Pointer[i].object_file_name = nullptr;

            this->Compiler_Data_Pointer[i].object_file_path = nullptr;

            this->Compiler_Data_Pointer[i].source_file_name = nullptr;

            this->Compiler_Data_Pointer[i].source_file_dir = nullptr;

            this->Compiler_Data_Pointer[i].make_file_name = nullptr;

            this->Compiler_Data_Pointer[i].compile_oder = i;
        }

        this->Determine_Script_Information();

        this->Determine_Header_Files_Inclusion_Number();

        this->Determine_Make_File_Names();

        this->Determine_Compiler_Order();

        this->Determine_Warehouse_Paths(warehouse_path);

        this->Write_The_Script(warehouse_path);
     }
}

void Compiler_Script_Writer::Determine_Script_Information(){

     for(int i=0;i<this->project_dir_num;i++){

           this->Determine_Source_File_Compilation_Information(i,'w');
     }
}

void Compiler_Script_Writer::Determine_Source_File_Compilation_Information(int dir_num, char operating_sis){

     char * header_path = this->Dir_Lister.Get_Make_Header_Exact_Path(dir_num);

     size_t header_path_size = strlen(header_path);

     this->Compiler_Data_Pointer[dir_num].header_file_path = new char [5*header_path_size];

     for(size_t i=0;i<header_path_size;i++){

        this->Compiler_Data_Pointer[dir_num].header_file_path[i] = header_path[i];
     }

     this->Compiler_Data_Pointer[dir_num].header_file_path[header_path_size] = '\0';




     char * src_dir = this->Dir_Lister.Get_Make_Directory(dir_num);


     size_t dir_size = strlen(src_dir);


     // Source file directory Assignment

     this->Compiler_Data_Pointer[dir_num].source_file_dir = new char [5*dir_size];

     for(size_t i=0;i<dir_size;i++){

         this->Compiler_Data_Pointer[dir_num].source_file_dir[i] = src_dir[i];
     }

     this->Compiler_Data_Pointer[dir_num].source_file_dir[dir_size] = '\0';



     char * src_file_name = this->Dir_Lister.Get_Make_Source_File_Name(dir_num);

     size_t src_name_size = strlen(src_file_name);

     this->Compiler_Data_Pointer[dir_num].source_file_name = new char [5*src_name_size];

     int index = 0;

     for(size_t i=0;i<src_name_size;i++){

         this->Compiler_Data_Pointer[dir_num].source_file_name[index] = src_file_name[i];

         index++;
     }

     this->Compiler_Data_Pointer[dir_num].source_file_name[index] = '.';

     index++;

     this->Compiler_Data_Pointer[dir_num].source_file_name[index] = 'c';

     index++;

     this->Compiler_Data_Pointer[dir_num].source_file_name[index] = 'p';

     index++;

     this->Compiler_Data_Pointer[dir_num].source_file_name[index] = 'p';

     index++;

     this->Compiler_Data_Pointer[dir_num].source_file_name[index] = '\0';




     this->Compiler_Data_Pointer[dir_num].object_file_name = new char [5*src_name_size];

     index = 0;

     for(size_t i=0;i<src_name_size;i++){

         this->Compiler_Data_Pointer[dir_num].object_file_name[index] = src_file_name[i];

         index++;
     }

     this->Compiler_Data_Pointer[dir_num].object_file_name[index] = '.';

     index++;

     this->Compiler_Data_Pointer[dir_num].object_file_name[index] = 'o';

     index++;

     this->Compiler_Data_Pointer[dir_num].object_file_name[index] = '\0';


     this->Compiler_Data_Pointer[dir_num].object_file_path = new char[5*dir_size];

     index = 0;

     for(size_t i=0;i<dir_size;i++){

        this->Compiler_Data_Pointer[dir_num].object_file_path[index] = src_dir[i];

        index++;
     }

     if(operating_sis == 'w'){

        if(src_dir[dir_size-1] != '\\'){

          this->Compiler_Data_Pointer[dir_num].object_file_path[index] = '\\';

          index++;
        }
     }

     if(operating_sis == 'l'){

        if(src_dir[dir_size-1] != '/'){

          this->Compiler_Data_Pointer[dir_num].object_file_path[index] = '/';

          index++;
        }
     }

     for(size_t i=0;i<src_name_size;i++){

        this->Compiler_Data_Pointer[dir_num].object_file_path[index] = src_file_name[i];

        index++;
     }

     this->Compiler_Data_Pointer[dir_num].object_file_path[index] = '.';

     index++;

     this->Compiler_Data_Pointer[dir_num].object_file_path[index] = 'o';

     index++;

     this->Compiler_Data_Pointer[dir_num].object_file_path[index] = '\0';
}


void Compiler_Script_Writer::Determine_Header_Files_Inclusion_Number(){

     for(int n=0;n<this->project_dir_num;n++){

         char * header_file_name = this->Dir_Lister.Get_Make_Header_File_Name_With_Extention(n);

         for(int k=0;k<this->project_dir_num;k++){

             this->FileManager.SetFilePath(this->Compiler_Data_Pointer[k].header_file_path);

             this->FileManager.FileOpen(Rf);

             this->Included_Header_Files_Number = 0;

             this->String_Line = "";

             while(!this->FileManager.Control_End_of_File()){

                    this->String_Line = this->FileManager.ReadLine();

                    char * string_line = this->FileManager.Conver_Std_String_To_Char(this->String_Line);

                    bool is_header_included = this->StringManager.CheckStringInclusion(string_line,header_file_name);

                    if(is_header_included){

                       this->Compiler_Data_Pointer[n].dependency++;
                    }
              }

              this->FileManager.FileClose();
          }
      }
}

void Compiler_Script_Writer::Determine_Compiler_Order(){

     for(int i=0;i<this->project_dir_num;i++){

           for(int j=0;j<this->project_dir_num;j++){

             int dep_i = this->Compiler_Data_Pointer[i].dependency;

             int dep_j = this->Compiler_Data_Pointer[j].dependency;

             Compiler_Data  temp;

             if( dep_i > dep_j){

                 temp  = this->Compiler_Data_Pointer[j];

                 this->Compiler_Data_Pointer[j] = this->Compiler_Data_Pointer[i];

                 this->Compiler_Data_Pointer[i] = temp;
             }
           }
     }
}

bool Compiler_Script_Writer::Include_Line_Determiner(std::string String_Line){

     this->Include_Line_Condition = false;

     char Include_Word [] = "include";

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

     int file_index = 0;

     for(int i=0;i<this->project_dir_num;i++){

          char * source_file_name = this->Dir_Lister.Get_Make_Source_File_Name(i);

          size_t file_name_size = strlen(source_file_name);

          int string_index = 0;

          this->Compiler_Data_Pointer[i].make_file_name = new char [5*file_name_size];

          for(size_t k=0;k<file_name_size;k++){

              this->Compiler_Data_Pointer[i].make_file_name[string_index] = source_file_name[k];

              string_index++;
          }

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = '.';

          string_index++;

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = 'm';

          string_index++;

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = 'a';

          string_index++;

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = 'k';

          string_index++;

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = 'e';

          string_index++;

          this->Compiler_Data_Pointer[i].make_file_name[string_index] = '\0';

          file_index++;
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

     for(int i=0;i<this->project_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(change_dir);

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].source_file_dir);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f ");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].make_file_name);

         this->FileManager.WriteToFile(" > ");

         this->FileManager.WriteToFile(this->compiler_output_location);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Copy-Item ");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].header_file_path);

         this->FileManager.WriteToFile(" -Destination ");

         this->FileManager.WriteToFile("$Project_Headers");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("$Condition = Test-Path -Path \'");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].object_file_path);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if ($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path \'");

         this->FileManager.WriteToFile(this->object_files_location);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].object_file_name);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("      rm \'");

         this->FileManager.WriteToFile(this->object_files_location);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].object_file_name);

         this->FileManager.WriteToFile("\'");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   }");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Move-Item -Path ");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].object_file_path);

         this->FileManager.WriteToFile(" -Destination $Project_Objects");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"  # ");

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].source_file_name);


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
