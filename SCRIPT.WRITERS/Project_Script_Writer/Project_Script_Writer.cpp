

#include "Project_Script_Writer.h"

Project_Script_Writer::Project_Script_Writer(){

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->compiler_output_location = nullptr;

     this->headers_locations = nullptr;

     this->object_files_location = nullptr;

     this->script_path = nullptr;

     this->Data_Pointer = nullptr;
}

Project_Script_Writer::Project_Script_Writer(const Project_Script_Writer & orig){


}

Project_Script_Writer::~Project_Script_Writer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Project_Script_Writer::Build_Compiler_Script(Descriptor_File_Reader * Des_File_Reader){

     if(Des_File_Reader->Get_Warehouse_Location() == nullptr){

        std::cout << "\n There is no any decleration about";
        std::cout << "\n project warehouse location";

        exit(0);
     }

     this->Src_Script_Writer.Receive_Descriptor_File_Reader(Des_File_Reader);

     this->Dir_Lister.Determine_Git_Repo_Info(Des_File_Reader);

     this->source_file_num

     = this->Dir_Lister.Get_Source_File_Number();



    char * warehouse_path

             = Des_File_Reader->Get_Warehouse_Location();



     this->Data_Collector.Receive_Project_Files_Lister(&this->Dir_Lister);

     this->Data_Collector.Receive_Warehouse_Path(warehouse_path);


     if(this->source_file_num > 0){

        this->Initialize_Data_Structures();

        this->Determine_Script_Information();

        this->Determine_Header_Files_Inclusion_Number();

        this->Determine_Make_File_Names();

        this->Determine_Warehouse_Paths(warehouse_path);

        this->Write_Source_File_Scripts();

        this->Determine_Compiler_Order();
     }

}

void Project_Script_Writer::Determine_Script_Information(){

     for(int i=0;i<this->source_file_num;i++){

        this->Data_Collector.Determine_Source_File_Compilation_Information(&this->Data_Pointer[i],i,'w');
     }
}

void Project_Script_Writer::Determine_Header_Files_Inclusion_Number(){

     for(int n=0;n<this->source_file_num;n++){

        this->Data_Collector.Determine_Header_Files_Inclusion_Number(&this->Data_Pointer[n],n);
     }
}

void Project_Script_Writer::Determine_Compiler_Order(){

     for(int i=0;i<this->source_file_num;i++){

           for(int j=0;j<this->source_file_num;j++){

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


void Project_Script_Writer::Determine_Warehouse_Paths(char * warehouse_path){

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

void Project_Script_Writer::Determine_Make_File_Names()
{
     for(int i=0;i<this->source_file_num;i++){

         this->Data_Collector.Determine_Make_File_Name(&this->Data_Pointer[i],i);
     }
}

void Project_Script_Writer::Write_Source_File_Scripts(){

     for(int i=0;i<this->source_file_num;i++){

        char * src_dir = this->Data_Pointer[i].source_file_dir;

        this->DirectoryManager.ChangeDirectory(src_dir);

        this->Src_Script_Writer.Clear_Dynamic_Memory();

        this->Src_Script_Writer.Receive_Script_Data(&this->Data_Pointer[i]);

        this->Src_Script_Writer.Write_Source_File_Script('w');
     }
}

void Project_Script_Writer::Write_The_Project_Script(char * warehouse_path){

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

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f ");


         this->FileManager.WriteToFile(this->Data_Pointer[i].make_file_name);

         this->FileManager.WriteToFile(" > ");

         this->FileManager.WriteToFile(this->compiler_output_location);

         this->FileManager.WriteToFile("\n");


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


void Project_Script_Writer::Initialize_Data_Structures(){

     this->Data_Pointer = new Script_Data [2*this->source_file_num];

     for(int i=0;i<2*this->source_file_num;i++){

         this->Data_Collector.Initialize_Data_Structure(&this->Data_Pointer[i],i);
     }
}

void Project_Script_Writer::Clear_Dynamic_Memory(){

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
}



void Project_Script_Writer::Construct_Path(char ** pointer,

    char * string, char * warehouse_path){

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

void Project_Script_Writer::Place_String(char ** pointer, char * string){

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
