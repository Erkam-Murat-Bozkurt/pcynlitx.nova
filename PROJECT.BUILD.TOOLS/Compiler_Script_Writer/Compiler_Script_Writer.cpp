



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

               delete [] this->Compiler_Data_Pointer[i].class_name;

               delete [] this->Compiler_Data_Pointer[i].class_directory;


               this->Compiler_Data_Pointer[i].header_file_path = nullptr;

               this->Compiler_Data_Pointer[i].header_file_name = nullptr;

               this->Compiler_Data_Pointer[i].object_file_name = nullptr;

               this->Compiler_Data_Pointer[i].object_file_path = nullptr;

               this->Compiler_Data_Pointer[i].class_name = nullptr;

               this->Compiler_Data_Pointer[i].class_directory = nullptr;
           }

           delete [] this->Compiler_Data_Pointer;

           this->Compiler_Data_Pointer = nullptr;
         }
     }
}

void Compiler_Script_Writer::Build_Compiler_Script(char * repo_dir, char * warehouse_path){

     this->Dir_Lister.Receive_Repo_Directory(repo_dir);

     this->Dir_Lister.Determine_Project_File_List();

     this->project_dir_num

            = this->Dir_Lister.Get_SourceFile_Directory_Number();

     if(this->project_dir_num > 0){

        this->Compiler_Data_Pointer = new Compiler_Data [2*this->project_dir_num];

        for(int i=0;i<2*this->project_dir_num;i++){

            this->Compiler_Data_Pointer[i].dependency = 0;

            this->Compiler_Data_Pointer[i].header_file_path = nullptr;

            this->Compiler_Data_Pointer[i].header_file_name = nullptr;

            this->Compiler_Data_Pointer[i].object_file_name = nullptr;

            this->Compiler_Data_Pointer[i].object_file_path = nullptr;

            this->Compiler_Data_Pointer[i].class_name = nullptr;

            this->Compiler_Data_Pointer[i].class_directory = nullptr;

            this->Compiler_Data_Pointer[i].compile_oder = i;
        }

        this->Determine_Header_File_Paths();

        this->Determine_Header_Files_Inclusion_Number();

        this->Determine_Compiler_Order();

        this->Determine_Warehouse_Paths(warehouse_path);

        this->Write_The_Script(warehouse_path);
     }

}

void Compiler_Script_Writer::Determine_Header_File_Paths(){

     for(int i=0;i<this->project_dir_num;i++){

        char * directory = this->Dir_Lister.Get_Source_File_Directory(i);

        this->DirectoryManager.ChangeDirectory(directory);

        this->Determine_Header_Paths(i);
     }
}

void Compiler_Script_Writer::Determine_Header_Paths(int dir_num){

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     this->Enumerator.List_Files_On_Directory(Current_Directory);

     int file_num = this->Enumerator.Get_File_Number();

     char ** file_list = this->Enumerator.Get_File_List();

     char header_add [] = ".h";

     for(int k=0;k<file_num;k++){

         bool is_header = this->StringManager.CheckStringInclusion(file_list[k],header_add);

         if(is_header){

            size_t header_name_size = strlen(file_list[k]);

            this->Compiler_Data_Pointer[dir_num].header_file_name

                      = new char [5*header_name_size];

            for(int i=0;i<5*header_name_size;i++){

                this->Compiler_Data_Pointer[dir_num].header_file_name[i] = '\0';
            }

            for(size_t i=0;i<header_name_size;i++){

                this->Compiler_Data_Pointer[dir_num].header_file_name[i] = file_list[k][i];
            }

            this->Compiler_Data_Pointer[dir_num].header_file_name[header_name_size] = '\0';

            break;
          }
     }

     size_t Directory_Name_Size = strlen(Current_Directory);

     this->Compiler_Data_Pointer[dir_num].header_file_path = new char [5*Directory_Name_Size];

     int index_counter = 0;

     for(size_t i=0;i<Directory_Name_Size;i++){

         this->Compiler_Data_Pointer[dir_num].header_file_path[index_counter] = Current_Directory[i];

         index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].header_file_path[index_counter] = '\\';

     index_counter++;

     size_t header_name_size

            = strlen(this->Compiler_Data_Pointer[dir_num].header_file_name);


     for(size_t i=0;i<header_name_size;i++){

             this->Compiler_Data_Pointer[dir_num].header_file_path[index_counter] =

                 this->Compiler_Data_Pointer[dir_num].header_file_name[i];

             index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].header_file_path[index_counter] = '\0';


     // Class directory Assignment

     this->Compiler_Data_Pointer[dir_num].class_directory = new char [5*Directory_Name_Size];

     index_counter = 0;

     for(size_t i=0;i<Directory_Name_Size;i++){

         this->Compiler_Data_Pointer[dir_num].class_directory[index_counter] = Current_Directory[i];

         index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].class_directory[index_counter] = '\0';



     char * header_path = this->Compiler_Data_Pointer[dir_num].header_file_path;

     this->Cls_Name_Reader.ReadClassName(header_path);

     char * class_name = this->Cls_Name_Reader.getClassName();

     size_t class_name_size = strlen(class_name);


     // Class Name Assignment

     this->Compiler_Data_Pointer[dir_num].class_name = new char [5*class_name_size];

     index_counter = 0;

     for(size_t i=0;i<class_name_size;i++){

         this->Compiler_Data_Pointer[dir_num].class_name[index_counter] = class_name[i];

         index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].class_name[index_counter] = '\0';


     // Object File Name Assingment

     this->Compiler_Data_Pointer[dir_num].object_file_name = new char [5*class_name_size];

     index_counter = 0;

     for(size_t i=0;i<class_name_size;i++){

         this->Compiler_Data_Pointer[dir_num].object_file_name[index_counter] = class_name[i];

         index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].object_file_name[index_counter] = '.';

     index_counter++;

     this->Compiler_Data_Pointer[dir_num].object_file_name[index_counter] = 'o';

     index_counter++;

     this->Compiler_Data_Pointer[dir_num].object_file_name[index_counter] = '\0';


     // Object File Path Assignment

     this->Compiler_Data_Pointer[dir_num].object_file_path = new char [5*Directory_Name_Size];

     index_counter = 0;

     for(size_t i=0;i<Directory_Name_Size;i++){

         this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = Current_Directory[i];

         index_counter++;
     }

     this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = '\\';

     index_counter++;


     for(size_t i=0;i<class_name_size;i++){

         this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = class_name[i];

         index_counter++;
      }

      this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = '.';

      index_counter++;

      this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = 'o';

      index_counter++;

      this->Compiler_Data_Pointer[dir_num].object_file_path[index_counter] = '\0';
}


void Compiler_Script_Writer::Determine_Header_Files_Inclusion_Number(){

     for(int n=0;n<this->project_dir_num;n++){

         char * header_file = this->Compiler_Data_Pointer[n].header_file_name;

         for(int k=0;k<this->project_dir_num;k++){

             this->FileManager.SetFilePath(this->Compiler_Data_Pointer[k].header_file_path);

             this->FileManager.FileOpen(Rf);

             this->Included_Header_Files_Number = 0;

             this->String_Line = "";

              while(!this->FileManager.Control_End_of_File()){

                     this->String_Line = this->FileManager.ReadLine();

                     char * string_line = this->FileManager.Conver_Std_String_To_Char(this->String_Line);

                     bool is_header_included = this->StringManager.CheckStringInclusion(string_line,header_file);

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

            for(int k=0;k<Include_Word_Character_Size;k++){

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

     char change_dir [] = "cd ";

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

void Compiler_Script_Writer::Write_The_Script(char * warehouse_path){

     char change_dir [] = "cd ";

     this->FileManager.SetFilePath(script_path);

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

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].class_directory);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f auto_make_file.make > ");

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

         this->FileManager.WriteToFile(this->Compiler_Data_Pointer[i].class_name);


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
