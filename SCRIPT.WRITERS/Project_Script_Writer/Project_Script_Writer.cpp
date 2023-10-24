

#include "Project_Script_Writer.h"

Project_Script_Writer::Project_Script_Writer(char opr_sis) :

    Src_Data_Processor(opr_sis), Src_Script_Writer(opr_sis)
{

     this->Memory_Delete_Condition = true;

     this->is_script_path_setted = true;

     this->source_file_num = 0;

     this->Data_Pointer = nullptr;

     this->opr_sis = opr_sis;
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


void Project_Script_Writer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Src_Data_Processor.Receive_Descriptor_File_Reader(ptr);
}

void Project_Script_Writer::Build_Compiler_Script(){

     this->Src_Data_Processor.Process_Script_Data();

     this->Src_Script_Writer.Receive_Descriptor_File_Reader(this->Des_Reader);

     this->Data_Pointer = this->Src_Data_Processor.Get_Script_Data_Address();

     this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_MakeFiles_Root_Directory();

     this->Determine_Object_Files_Location('w');

     this->Determine_Project_Script_Path();

     this->Write_Source_File_Scripts();

     //this->Write_The_Project_Script();

     this->Write_Project_Build_Script();
}


void Project_Script_Writer::Build_Update_Script(){

     this->Determine_MakeFiles_Root_Directory();

     this->Determine_Object_Files_Location('w');
     
     this->Src_Data_Processor.Process_Script_Data();

     this->Src_Script_Writer.Receive_Descriptor_File_Reader(this->Des_Reader);

     this->Data_Pointer = this->Src_Data_Processor.Get_Script_Data_Address();

     this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     if(!this->is_script_path_setted){

        std::cout << "\n The path for update script can not be determined";

        exit(EXIT_FAILURE);
     }

     this->Write_Project_Build_Script();
}


void Project_Script_Writer::Determine_Project_Script_Path(){

     std::string script_path_add = "Project_Build_Script.ps1";

     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->script_path,script_path_add,this->warehouse_path);
}

void Project_Script_Writer::Set_Script_Path(std::string dir, std::string file_name){

     this->Memory_Delete_Condition = false;

     this->is_script_path_setted = true;
     
     this->Construct_Path(this->script_path,file_name,dir);
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


     std::string Repo_Rood_Dir = this->Des_Reader->Get_Repo_Directory_Location();

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


     this->FileManager.WriteToFile("# MakeFiles_Location is the root directory of make files ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n$MakeFiles_Location=\"");

     this->FileManager.WriteToFile(this->MakeFiles_Root_Directory);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \" THE OBJECT FILE CONSTRUCTION ( RE-CONSTRUCTION ) PROCESS STARTED\"");

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
         
         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);



         this->FileManager.WriteToFile("\n");
         
         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("$Condition = Test-Path -Path ");

         this->FileManager.WriteToFile("$MakeFiles_Location");


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Remove-Item ");

         this->FileManager.WriteToFile("$MakeFiles_Location");


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");




         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("mingw32-make -f ");

         this->FileManager.WriteToFile(this->Data_Pointer->at(i).make_file_name);
         
         this->FileManager.WriteToFile(" 2>&1 > ");

         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         std::string output_file_name;

         this->Determine_Compiler_Output_File_Name(output_file_name,this->Data_Pointer->at(i).src_name_without_ext);

         this->FileManager.WriteToFile(output_file_name);

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


         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }



         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }



         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("if ($Condition){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path ");

         this->FileManager.WriteToFile("$Project_Objects_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("      Remove-Item ");

         this->FileManager.WriteToFile("$Project_Objects_Location");


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   }");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("   Move-Item -Path ");


         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


      
         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);


         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).object_file_name);

         this->FileManager.WriteToFile(" -Destination $Project_Objects_Location");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("}");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");




         this->FileManager.WriteToFile("Write-Host \"[ \" -NoNewline ");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         int decimal_space =  this->Determine_Decimal_Space(this->source_file_num,i+1);


         this->FileManager.WriteToFile("Write-Host \"");

         for(int k=0;k<decimal_space;k++){

             this->FileManager.WriteToFile(" ");

         }


         this->FileManager.WriteToFile("\" -NoNewline");


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Host \"");


         this->FileManager.WriteToFile(this->Translater.Translate(i+1));

         this->FileManager.WriteToFile("\" -ForegroundColor Green -NoNewline");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Host \"");


         this->FileManager.WriteToFile(" / ");

         this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

         this->FileManager.WriteToFile("\" -ForegroundColor White -NoNewline");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Host \" ] Built for ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_name);


         this->FileManager.WriteToFile(" complated\"");

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

     this->FileManager.WriteToFile("Write-Output \"THE PROJECT OBJECT FILES CONSTRUCTED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\nLibrary_Updater.exe ");

     std::string des_path = this->Des_Reader->Get_Descriptor_File_Path();

     this->FileManager.WriteToFile(des_path);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"THE PROJECT LIBRARY UPDATED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");


     this->FileManager.FileClose();
}


void Project_Script_Writer::Write_Project_Build_Script(){

     std::string Repo_Rood_Dir = this->Des_Reader->Get_Repo_Directory_Location();

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


     this->FileManager.WriteToFile("# MakeFiles_Location is the root directory of make files ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n$MakeFiles_Location=\"");

     this->FileManager.WriteToFile(this->MakeFiles_Root_Directory);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \" THE OBJECT FILE CONSTRUCTION ( RE-CONSTRUCTION ) PROCESS STARTED\"");

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

         this->FileManager.WriteToFile("\n\n");

         this->FileManager.WriteToFile("# Dependency: ");

         std::string dep = std::to_string(this->Data_Pointer->at(i).dependency);

         this->FileManager.WriteToFile(dep);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(cd_word);

         this->FileManager.WriteToFile(" ");
         
         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);



         this->FileManager.WriteToFile("\n");
         
         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("powershell.exe ");
         
         this->FileManager.WriteToFile("$MakeFiles_Location");

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }



         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_git_record_dir);

         if(this->opr_sis == 'w'){

            this->FileManager.WriteToFile("\\");
         }

         if(this->opr_sis == 'l'){

            this->FileManager.WriteToFile("/");
         }


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).src_name_without_ext);

         this->FileManager.WriteToFile(".ps1");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Host \"[ \" -NoNewline ");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         int decimal_space =  this->Determine_Decimal_Space(this->source_file_num,i+1);


         this->FileManager.WriteToFile("Write-Host \"");

         for(int k=0;k<decimal_space;k++){

             this->FileManager.WriteToFile(" ");

         }


         this->FileManager.WriteToFile("\" -NoNewline");


         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Host \"");


         this->FileManager.WriteToFile(this->Translater.Translate(i+1));

         this->FileManager.WriteToFile("\" -ForegroundColor Green -NoNewline");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");


         this->FileManager.WriteToFile("Write-Host \"");


         this->FileManager.WriteToFile(" / ");

         this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

         this->FileManager.WriteToFile("\" -ForegroundColor White -NoNewline");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("Write-Host \" ] Built for ");


         this->FileManager.WriteToFile(this->Data_Pointer->at(i).source_file_name);


         this->FileManager.WriteToFile(" complated\"");

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

     this->FileManager.WriteToFile("Write-Output \"THE PROJECT OBJECT FILES CONSTRUCTED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\nLibrary_Updater.exe ");

     std::string des_path = this->Des_Reader->Get_Descriptor_File_Path();

     this->FileManager.WriteToFile(des_path);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"THE PROJECT LIBRARY UPDATED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");


     this->FileManager.FileClose();
}

void Project_Script_Writer::Clear_Dynamic_Memory(){

     this->Src_Data_Processor.Clear_Dynamic_Memory();      

     this->is_script_path_setted = false;
}


int Project_Script_Writer::Determine_Decimal_Space(int total_src_num, int current_number){
     
    int decimal_power_for_total =0;
    int decimal_power_for_current = 0;
    int space = 0;

    int remainder = total_src_num/10;

    if(remainder>=1){

       do{

          decimal_power_for_total++;

          remainder = remainder/10;

       }while(remainder>=1);
    }

    remainder = current_number/10;

    if(remainder>=1){

       do{

          decimal_power_for_current++;

          remainder = remainder/10;

       }while(remainder>=1);
    }


    space = decimal_power_for_total - decimal_power_for_current;

    return space;
}


void Project_Script_Writer::Determine_Object_Files_Location(char opr_sis){

     this->Clear_String_Memory(this->object_files_location);

     std::string object_files_location_add = "OBJECT.FILES";

     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->object_files_location,object_files_location_add,opr_sis);
}


void Project_Script_Writer::Determine_Compiler_Output_File_Name(std::string & name, std::string class_name){

     std::string compiler_output_file_add = "_Compiler_Output.txt";
     
     size_t class_name_size = class_name.length();


     for(size_t i=0;i<class_name_size;i++){

         name.push_back(class_name[i]);
     }


     size_t file_add_size = compiler_output_file_add.length();

     for(size_t i=0;i<file_add_size;i++){

         name.push_back(compiler_output_file_add[i]);
     }

     name.shrink_to_fit();    
}



void Project_Script_Writer::Construct_Path(std::string & path,

     std::string string, std::string warehouse_path){

     int index = 0;

     size_t warehouse_path_size = warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         path.push_back(warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        if(warehouse_path.back() != '\\'){

           path.push_back('\\');        
        }
     }

     if(this->opr_sis == 'l'){

        if(warehouse_path.back() != '/'){

           path.push_back('/');        
        }
     }


     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

        path.push_back(string[i]);        
     }     
}




void Project_Script_Writer::Construct_Path(std::string & path,

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


void Project_Script_Writer::Determine_MakeFiles_Root_Directory(){

     std::string warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     std::string warehouse_word = "WAREHOUSE";
     
     std::string make_file_dir_name = "MAKE.FILES";


     size_t warehouse_dir_size  = warehouse_location.length();

     for(size_t i=0;i<warehouse_dir_size;i++){

         this->MakeFiles_Root_Directory.push_back(warehouse_location[i]);
     }

     if(this->opr_sis == 'w'){

        if(this->MakeFiles_Root_Directory.back()!= '\\'){

           this->MakeFiles_Root_Directory.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->MakeFiles_Root_Directory.back()!= '/'){

           this->MakeFiles_Root_Directory.push_back('/');
        }
     }


     size_t warehouse_word_size = warehouse_word.length();

     for(size_t i=0;i<warehouse_word_size;i++){

         this->MakeFiles_Root_Directory.push_back(warehouse_word[i]);
     }

     if(this->opr_sis == 'w'){

        if(this->MakeFiles_Root_Directory.back()!= '\\'){

           this->MakeFiles_Root_Directory.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->MakeFiles_Root_Directory.back()!= '/'){

           this->MakeFiles_Root_Directory.push_back('/');
        }
     }

     
     size_t make_dir_size = make_file_dir_name.length();

     for(size_t i=0;i<make_dir_size;i++){

         this->MakeFiles_Root_Directory.push_back(make_file_dir_name[i]);
     }

     this->MakeFiles_Root_Directory.shrink_to_fit();
}


void Project_Script_Writer::Determine_MakeFile_Directory(std::string & mkf_dir, std::string git_record_dir){

     size_t root_size = this->MakeFiles_Root_Directory.size();

     for(size_t i=0;i<root_size;i++){

         mkf_dir.push_back(this->MakeFiles_Root_Directory.at(i));
     }
     
     if(this->opr_sis == 'w'){

        if(mkf_dir.back()!= '\\'){

           mkf_dir.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(mkf_dir.back()!= '/'){

           mkf_dir.push_back('/');
        }
     }

     size_t git_dir_size = git_record_dir.size();

     for(size_t i=0;i<git_dir_size;i++){

         mkf_dir.push_back(git_record_dir.at(i));
     }

     mkf_dir.shrink_to_fit();
}



void Project_Script_Writer::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();
         str.shrink_to_fit();        
     }
}
