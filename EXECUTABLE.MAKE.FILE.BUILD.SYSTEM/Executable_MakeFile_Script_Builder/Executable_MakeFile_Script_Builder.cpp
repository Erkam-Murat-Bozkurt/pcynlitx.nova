


#include "Executable_MakeFile_Script_Builder.hpp"

Executable_MakeFile_Script_Builder::Executable_MakeFile_Script_Builder(char opr_sis) :

    Src_Data_Processor(opr_sis)
{

     this->Memory_Delete_Condition = true;

     this->source_file_num = 0;

     this->Data_Pointer = nullptr;

     this->opr_sis = opr_sis;
}


Executable_MakeFile_Script_Builder::~Executable_MakeFile_Script_Builder(){

   if(!this->Memory_Delete_Condition){
    
       this->Memory_Delete_Condition = true;

       this->Clear_Dynamic_Memory();
   }
}

void Executable_MakeFile_Script_Builder::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Src_Data_Processor.Receive_Source_File_Dependency_Determiner(ptr);
}

void Executable_MakeFile_Script_Builder::Receive_Git_Data_Processor(Git_Data_Processor * ptr){
     
     this->Src_Data_Processor.Receive_Git_Data_Processor(ptr);   
}

void Executable_MakeFile_Script_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Src_Data_Processor.Receive_Descriptor_File_Reader(ptr);

     this->Repo_Root_Dir = this->Des_Reader->Get_Repo_Directory_Location();

}

void Executable_MakeFile_Script_Builder::Build_Compiler_Script_For_Executable_File(){

     this->Src_Data_Processor.Process_Script_Data();
     
     this->Data_Pointer = this->Src_Data_Processor.Get_Script_Data_Address();

     std::string src_file_name = this->Data_Pointer->at(0).src_name_without_ext;

     this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_Object_Files_Location('w');

     this->Determine_Script_Path(src_file_name);

     this->Write_The_Executable_Make_File_Update_Script(src_file_name);
}


void Executable_MakeFile_Script_Builder::Determine_Script_Path(std::string src_file_name){

     std::string script_path_add = "_Build_Script.ps1";

     std::string script_file_name = src_file_name + script_path_add;

     this->Memory_Delete_Condition = false;

     this->Construct_Script_Path(this->script_path,script_file_name);
}


void Executable_MakeFile_Script_Builder::Write_The_Executable_Make_File_Update_Script(std::string src_file_name){


     this->FileManager.SetFilePath(this->script_path);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n$Project_Objects_Location=\"");

     this->FileManager.WriteToFile(this->object_files_location);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");
     this->FileManager.WriteToFile("\n");



     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Host  \" The object files related with ");

     this->FileManager.WriteToFile(src_file_name);

     this->FileManager.WriteToFile("will be updated\" -ForegroundColor DarkCyan");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("Write-Output \" Total number of the source file: ");

     this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

     this->FileManager.WriteToFile("\"");


     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");


     char cd_word [] = "Set-Location ";


     for(int i=0;i<this->source_file_num;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Output \"\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("# Dependency: ");

         std::string dep = std::to_string(this->Data_Pointer->at(i).dependency);

         this->FileManager.WriteToFile(dep);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(cd_word);

         this->FileManager.WriteToFile(" ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);


         this->FileManager.WriteToFile("\n");
         
         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Remove-Item ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");




         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).make_file_name);

         this->Determine_Compiler_Output_Path(this->Data_Pointer->at(i).src_name_without_ext);


         this->FileManager.WriteToFile(" 2>&1 > ");

         this->FileManager.WriteToFile(this->compiler_output_location);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");



         this->FileManager.WriteToFile("if($LASTEXITCODE -ne 0){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Write-Output \"# Compiler fails on ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile(" creation!\"");

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("   Write-Output \"\"");

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("   Write-Output \"\"");

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("   exit");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if ($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path ");

         this->FileManager.WriteToFile("$Project_Objects_Location");

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("      Remove-Item ");

         this->FileManager.WriteToFile("$Project_Objects_Location");

         this->FileManager.WriteToFile("\\");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   }");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Move-Item -Path ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_dir);

         this->FileManager.WriteToFile("\\");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);




         this->FileManager.WriteToFile(" -Destination $Project_Objects_Location");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");



         this->FileManager.WriteToFile("Write-Host \"[\" -NoNewline ");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Host \" ");

         this->FileManager.WriteToFile(this->Translater.Translate(i+1));

         this->FileManager.WriteToFile(" - ");

         this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

         this->FileManager.WriteToFile("\" -ForegroundColor DarkCyan -NoNewline");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Host \" ] The source file ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_name);


         this->FileManager.WriteToFile(" has been compiled\"");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

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

     this->FileManager.WriteToFile("Write-Output \" THE PROJECT OBJECT FILES CONSTRUCTED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}



void Executable_MakeFile_Script_Builder::Clear_Dynamic_Memory(){

     this->Src_Data_Processor.Clear_Dynamic_Memory();             
}



void Executable_MakeFile_Script_Builder::Determine_Object_Files_Location(char opr_sis){

     this->Clear_String_Memory(this->object_files_location);

     std::string object_files_location_add = "PROJECT.OBJECT.FILES";

     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->object_files_location,object_files_location_add,opr_sis);
}


void Executable_MakeFile_Script_Builder::Determine_Compiler_Output_Path(std::string class_name)
{
     this->Clear_String_Memory(this->compiler_output_location);

     std::string output_directory = "WAREHOUSE\\COMPILER.OUTPUTS";

     std::string compiler_output_location_add = "_Compiler_Output.txt";
     
     int index = 0;

     size_t warehouse_path_size = this->warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->compiler_output_location.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        if(warehouse_path.back() != '\\'){

           this->compiler_output_location.push_back('\\');        
        }
     }
    
     if(this->opr_sis == 'l'){

        if(warehouse_path.back() != '/'){

           this->compiler_output_location.push_back('/');        
        }
     }

     size_t output_directory_size = output_directory.length();

     for(size_t i=0;i<output_directory_size;i++){

         this->compiler_output_location.push_back(output_directory[i]);
     }

     if(this->opr_sis == 'w'){

        if(warehouse_path.back() != '\\'){

           this->compiler_output_location.push_back('\\');        
        }
     }
    
     if(this->opr_sis == 'l'){

        if(warehouse_path.back() != '/'){

           this->compiler_output_location.push_back('/');        
        }
     }

     size_t class_name_size = class_name.length();

     for(size_t i=0;i<class_name_size;i++){

        this->compiler_output_location.push_back(class_name[i]);
     }

     size_t add_string_size = compiler_output_location_add.length();

     for(size_t i=0;i<add_string_size;i++){

         this->compiler_output_location.push_back(compiler_output_location_add[i]);
     }

     this->compiler_output_location.shrink_to_fit();        
}



void Executable_MakeFile_Script_Builder::Construct_Script_Path(std::string & path,

     std::string src_file_name){

     std::string Repo_Root_Dir = this->Des_Reader->Get_Repo_Directory_Location();

     std::string git_record_dir = this->Data_Pointer->at(0).source_file_git_record_dir;
     
     int index = 0;

     size_t repo_root_dir_size_ = Repo_Root_Dir.length();

     for(size_t i=0;i<repo_root_dir_size_;i++){

         path.push_back(Repo_Root_Dir[i]);
     }

     if(Repo_Root_Dir.back() != '\\'){

        path.push_back('\\');        
     }

     
     size_t git_record_dir_size = git_record_dir.length();

     if(git_record_dir_size>0){

        for(size_t i=0;i<git_record_dir_size;i++){

            path.push_back(git_record_dir[i]);        
        }     


        if(git_record_dir.back() != '\\'){

           path.push_back('\\');        
        }
     }



     size_t string_size = src_file_name.length();

     for(size_t i=0;i<string_size;i++){

        path.push_back(src_file_name[i]);        
     }     
}




void Executable_MakeFile_Script_Builder::Construct_Path(std::string & path,

     std::string string, char opr_sis){

     std::string warehouse_path = this->Des_Reader->Get_Warehouse_Location();


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


void Executable_MakeFile_Script_Builder::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();
         str.shrink_to_fit();        
     }
}
