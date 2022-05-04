

#include "Source_File_Script_Writer.hpp"

Source_File_Script_Writer::Source_File_Script_Writer(){

     this->Memory_Delete_Condition = true;

     this->Src_Data_Pointer = nullptr;

     this->script_path = nullptr;

     this->compiler_output_location = nullptr;

     this->headers_locations = nullptr;

     this->object_files_location = nullptr;

     this->Repo_Rood_Dir = nullptr;
}

Source_File_Script_Writer::Source_File_Script_Writer(const Source_File_Script_Writer & orig){


}

Source_File_Script_Writer::~Source_File_Script_Writer(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Clear_Dynamic_Memory();
   }
}

void Source_File_Script_Writer::Clear_Pointer_Memory(char ** pointer){

     if(*pointer != nullptr){

        delete [] *pointer;

        *pointer = nullptr;
     }
}

void Source_File_Script_Writer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Pointer_Memory(&this->script_path);

        this->Clear_Pointer_Memory(&this->headers_locations);

        this->Clear_Pointer_Memory(&this->object_files_location);

        this->Clear_Pointer_Memory(&this->script_path);
     }
}


void Source_File_Script_Writer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader_Ptr = Pointer;

     this->Repo_Rood_Dir = this->Des_Reader_Ptr->Get_Repo_Directory_Location();
}

void Source_File_Script_Writer::Receive_Script_Data(Script_Data * Pointer){

     this->Src_Data_Pointer = Pointer;

     this->warehouse_path   = Pointer->warehouse_path;
}

void Source_File_Script_Writer::Write_Source_File_Script(char operating_sis){

     this->Determine_Script_Path('w');

     this->Determine_Warehouse_Paths('w');

     this->FileManager.SetFilePath(this->script_path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("# The following lines perform decleration about file locations");

     this->FileManager.WriteToFile("\n# ");


     for(int i=0;i<50;i++){

        this->FileManager.WriteToFile("- ");
     }

     //this->FileManager.WriteToFile("-");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("$Repo_Root_Dir=\"");

     this->FileManager.WriteToFile(this->Repo_Rood_Dir);

     this->FileManager.WriteToFile("\"");

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


     if(this->Src_Data_Pointer->included_header_num > 0){

        int head_num = this->Src_Data_Pointer->included_header_num;

        for(int i=0;i<head_num;i++){

            this->FileManager.WriteToFile("\n");

            this->FileManager.WriteToFile("$Header_Location_");

            this->FileManager.WriteToFile(this->Translater.Translate(i));

            this->FileManager.WriteToFile("=\"");

            this->FileManager.WriteToFile(this->Src_Data_Pointer->header_files_git_dir[i]);

            this->FileManager.WriteToFile("\"");

            this->FileManager.WriteToFile("\n");

            this->FileManager.WriteToFile("\n");
        }
     }


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Source_File_Location=\"");

     this->FileManager.WriteToFile(Src_Data_Pointer->source_file_git_record_dir);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("# The start of the scipt commands");

     this->FileManager.WriteToFile("\n# ");


     for(int i=0;i<50;i++){

         this->FileManager.WriteToFile("- ");
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");




     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"");

     this->FileManager.WriteToFile(this->Src_Data_Pointer->source_file_name);

     this->FileManager.WriteToFile(" class object file construction started\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("mingw32-make -f ");

     this->FileManager.WriteToFile(this->Src_Data_Pointer->make_file_name);

     this->FileManager.WriteToFile(" > ");

     this->FileManager.WriteToFile(this->compiler_output_location);

     this->FileManager.WriteToFile("\n");

     std::cout << "\n this->Src_Data_Pointer->included_header_num:" <<

     this->Src_Data_Pointer->included_header_num;

     std::cin.get();


     if(this->Src_Data_Pointer->included_header_num > 0){

        int head_num = this->Src_Data_Pointer->included_header_num;

        for(int i=0;i<head_num;i++){

           this->FileManager.WriteToFile("\n");

           this->FileManager.WriteToFile("Copy-Item ");

           this->FileManager.WriteToFile("$Repo_Root_Dir\\");

           this->FileManager.WriteToFile("$Header_Location_");

           this->FileManager.WriteToFile(this->Translater.Translate(i));

           this->FileManager.WriteToFile("\\");

           this->FileManager.WriteToFile(this->Src_Data_Pointer->header_file_names[i]);

           this->FileManager.WriteToFile(" -Destination ");

           this->FileManager.WriteToFile("$Project_Headers");

           this->FileManager.WriteToFile("\n");
        }
      }

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


      this->FileManager.WriteToFile("$Repo_Root_Dir");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile("$Source_File_Location");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);


      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("if ($Condition){");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path ");

      this->FileManager.WriteToFile("$Project_Objects");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("      rm ");

      this->FileManager.WriteToFile("$Project_Objects");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   }");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   Move-Item -Path ");


      this->FileManager.WriteToFile("$Repo_Root_Dir");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile("$Source_File_Location");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);


      this->FileManager.WriteToFile(" -Destination $Project_Objects");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("}");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("Write-Output \"  # ");


      this->FileManager.WriteToFile(this->Src_Data_Pointer->source_file_name);


      this->FileManager.WriteToFile(" class has been compiled\"");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("Write-Output \"\"");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.FileClose();
}


void Source_File_Script_Writer::Determine_Script_Path(char opr_sis){

     if(this->script_path != nullptr){

        delete [] this->script_path;

        this->script_path = nullptr;
     }


     this->Memory_Delete_Condition = false;


     char script_add_win [] = ".ps1";

     char script_add_bash [] = ".sh";


     char * src_dir  = this->Src_Data_Pointer->source_file_dir;

     char * src_name = this->Src_Data_Pointer->source_file_name;



     size_t name_size = strlen(src_name);

     size_t dir_size = strlen(src_dir);

     size_t path_size = name_size + dir_size;

     this->script_path = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<dir_size;i++){

         this->script_path[index] = src_dir[i];

         index++;
     }

     if(opr_sis == 'w'){

        this->script_path[index] = '\\';

        index++;
     }

     if(opr_sis == 'l'){

        this->script_path[index] = '/';

        index++;
     }

     for(size_t i=0;i<name_size;i++){

        this->script_path[index] = src_name[i];

        index++;
     }

     if(opr_sis == 'w'){

        size_t add_size = strlen(script_add_win);

        for(size_t i=0;i<add_size;i++){

           this->script_path[index] = script_add_win[i];

           index++;
        }
     }

     if(opr_sis == 'l'){

        size_t add_size = strlen(script_add_bash);

        for(size_t i=0;i<add_size;i++){

            this->script_path[index] = script_add_bash[i];

            index++;
        }
     }

     this->script_path[index] = '\0';
}



void Source_File_Script_Writer::Determine_Warehouse_Paths(char opr_sis){

     size_t warehouse_path_size = strlen(this->warehouse_path);

     char headers_location_add [] = "PROJECT.HEADER.FILES";

     char object_files_location_add [] = "PROJECT.OBJECT.FILES";

     char compiler_output_location_add [] = "Compiler_Output.txt";


     size_t headers_location_size = warehouse_path_size +

            strlen(headers_location_add);

     size_t object_files_location_size = warehouse_path_size +

            strlen(object_files_location_add);

     size_t compiler_output_location_size = warehouse_path_size +

            strlen(compiler_output_location_add);


     this->Memory_Delete_Condition = false;

     this->headers_locations = new char [5*headers_location_size];

     this->object_files_location = new char [5*object_files_location_size];

     this->compiler_output_location = new char [5*compiler_output_location_size];


     this->Construct_Path(&this->headers_locations,headers_location_add,opr_sis);

     this->Construct_Path(&this->object_files_location,object_files_location_add,opr_sis);

     this->Construct_Path(&this->compiler_output_location,compiler_output_location_add,opr_sis);
}


void Source_File_Script_Writer::Construct_Path(char ** pointer,

     char * string, char opr_sis){

     int index = 0;

     char warehouse_word [] = "WAREHOUSE";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     for(size_t i=0;i<warehouse_path_size;i++){

         (*pointer)[index] = warehouse_path[i];

         index++;
     }

     if(opr_sis == 'w'){

       if(warehouse_path[warehouse_path_size-1] != '\\'){

          (*pointer)[index] = '\\';

          index++;
       }
     }


     if(opr_sis == 'l'){

       if(warehouse_path[warehouse_path_size-1] != '/'){

          (*pointer)[index] = '/';

          index++;
       }
     }

     size_t warehouse_word_size = strlen(warehouse_word);

     for(size_t i=0;i<warehouse_word_size;i++){

         (*pointer)[index] = warehouse_word[i];

         index++;
     }


     if(opr_sis == 'w'){

        (*pointer)[index] = '\\';

        index++;
     }


     if(opr_sis == 'l'){

        (*pointer)[index] = '/';

        index++;
     }


     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string[i];

        index++;
     }

     (*pointer)[index] = '\0';
}
