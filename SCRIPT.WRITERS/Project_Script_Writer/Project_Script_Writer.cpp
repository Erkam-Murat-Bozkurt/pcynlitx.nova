

#include "Project_Script_Writer.h"

Project_Script_Writer::Project_Script_Writer(char * DesPATH, char opr_sis) :

    Src_Data_Processor(DesPATH,opr_sis), Git_Receiver(DesPATH,opr_sis), Des_Reader(DesPATH)
{

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->Data_Pointer = nullptr;

     this->opr_sis = opr_sis;

     this->Des_Reader.Read_Descriptor_File();

     this->Git_Receiver.Determine_Git_Repo_Info();

     this->Src_Data_Processor.Receive_Git_File_List_Info(&this->Git_Receiver);    
}


Project_Script_Writer::~Project_Script_Writer(){

   if(!this->Memory_Delete_Condition){
    
       this->Memory_Delete_Condition = true;

       this->Clear_Dynamic_Memory();
   }
}

void Project_Script_Writer::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Src_Data_Processor.Receive_Source_File_Dependency_Determiner(ptr);
}


void Project_Script_Writer::Build_Compiler_Script(){

    this->Src_Data_Processor.Process_Script_Data();

    this->Src_Script_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

    this->Data_Pointer = this->Src_Data_Processor.Get_Script_Data_Address();

    this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

    std::string warehouse_path = this->Des_Reader.Get_Warehouse_Location();

    this->Determine_Project_Script_Path(warehouse_path);

    this->Write_Source_File_Scripts();

    this->Write_The_Project_Script();
}

void Project_Script_Writer::Determine_Project_Script_Path(std::string warehouse_path){

     std::string script_path_add = "Project_Build_Script.ps1";

     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->script_path,script_path_add,warehouse_path);
}


void Project_Script_Writer::Write_Source_File_Scripts(){

     for(int i=0;i<this->source_file_num;i++){

        std::string src_dir = this->Data_Pointer->at(i).source_file_dir;

        this->DirectoryManager.ChangeDirectory(src_dir);

        this->Src_Script_Writer.Clear_Dynamic_Memory();
         
        this->Src_Script_Writer.Receive_Script_Data(&this->Data_Pointer->at(i));

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

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("mingw32-make -f ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).make_file_name);

     
         std::string compiler_output_location;

         std::string compiler_output_location_add = "Compiler_Output.txt";


         this->Construct_Path(compiler_output_location,compiler_output_location_add,this->opr_sis);



         this->FileManager.WriteToFile(" > ");

         this->FileManager.WriteToFile(compiler_output_location);

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("# Dependency: ");

         std::string dep = std::to_string(this->Data_Pointer->at(i).dependency);

         this->FileManager.WriteToFile(dep);

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Output \"  # ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_name);


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


void Project_Script_Writer::Clear_Dynamic_Memory(){

     this->Src_Data_Processor.Clear_Dynamic_Memory();             
}

void Project_Script_Writer::Construct_Path(std::string & path,

     std::string string, std::string warehouse_path){

     int index = 0;

     size_t warehouse_path_size = warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         path.push_back(warehouse_path[i]);
     }

     if(warehouse_path.back() != '\\'){

        path.push_back('\\');        
     }

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

        path.push_back(string[i]);        
     }     
}




void Project_Script_Writer::Construct_Path(std::string & path,

     std::string string, char opr_sis){

     std::string warehouse_path = this->Des_Reader.Get_Warehouse_Location();


     std::string warehouse_word = "WAREHOUSE";

     size_t warehouse_path_size = warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         path.push_back(warehouse_path[i]);         
     }

     if(opr_sis == 'w'){

       if(warehouse_path.back() != '\\'){

          path.push_back('\\');
       }
     }


     if(opr_sis == 'l'){

       if(warehouse_path.back() != '/'){

          path.push_back('/');          
       }
     }

     size_t warehouse_word_size = warehouse_word.length();

     for(size_t i=0;i<warehouse_word_size;i++){

         path.push_back(warehouse_word[i]);         
     }


     if(opr_sis == 'w'){

        path.push_back('\\');        
     }


     if(opr_sis == 'l'){

        path.push_back('/');        
     }


     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

        path.push_back(string[i]);        
     }

     path.shrink_to_fit();
}
