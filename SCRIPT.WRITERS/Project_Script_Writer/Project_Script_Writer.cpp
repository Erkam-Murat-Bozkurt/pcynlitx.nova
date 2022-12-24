

#include "Project_Script_Writer.h"

Project_Script_Writer::Project_Script_Writer(){

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->script_path = nullptr;

     this->Data_Pointer = nullptr;
}

Project_Script_Writer::Project_Script_Writer(const Project_Script_Writer & orig){


}

Project_Script_Writer::~Project_Script_Writer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();

       std::cout << "\n after Project_Script_Writer::Clear_Dynamic_Memory";

       std::cin.get();
   }
}

void Project_Script_Writer::Build_Compiler_Script(Descriptor_File_Reader * Des_File_Reader){

    this->Src_Data_Processor.Process_Script_Data(Des_File_Reader);

    this->Src_Script_Writer.Receive_Descriptor_File_Reader(Des_File_Reader);

    this->Data_Pointer    = this->Src_Data_Processor.Get_Script_Data();

    this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

    char * warehouse_path = Des_File_Reader->Get_Warehouse_Location();

    this->Determine_Project_Script_Path(warehouse_path);

    this->Write_Source_File_Scripts();

    this->Write_The_Project_Script();
}

void Project_Script_Writer::Determine_Project_Script_Path(char * warehouse_path){

     size_t warehouse_path_size = strlen(warehouse_path);

     char script_path_add [] = "Project_Build_Script.ps1";

     size_t script_path_size = warehouse_path_size + strlen(script_path_add);

     this->Memory_Delete_Condition = false;

     this->script_path = new char [5*script_path_size];

     this->Construct_Path(&this->script_path,script_path_add,warehouse_path);
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

void Project_Script_Writer::Write_The_Project_Script(){

     this->FileManager.SetFilePath(this->script_path);

     this->FileManager.FileOpen(RWCf);

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

     char cd_word [] = "cd ";

     for(int i=0;i<this->source_file_num;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(cd_word);

         this->FileManager.WriteToFile(" ");

         this->FileManager.WriteToFile(this->Data_Pointer[i].source_file_dir);

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("PowerShell .\\");

         this->FileManager.WriteToFile(this->Data_Pointer[i].source_file_name);

         this->FileManager.WriteToFile(".ps1");

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("# Dependency: ");

         std::string dep = std::to_string(this->Data_Pointer[i].dependency);

         this->FileManager.WriteToFile(dep);

         this->FileManager.WriteToFile("\n\n");

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


void Project_Script_Writer::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Src_Data_Processor.Clear_Dynamic_Memory();
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
