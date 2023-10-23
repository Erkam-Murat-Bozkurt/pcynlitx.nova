

#include "Source_File_Script_Writer.hpp"

Source_File_Script_Writer::Source_File_Script_Writer(char opr_sis){

     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;
}


Source_File_Script_Writer::~Source_File_Script_Writer(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Clear_Dynamic_Memory();
   }
}

void Source_File_Script_Writer::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();
         str.shrink_to_fit();        
     }
}

void Source_File_Script_Writer::Clear_Dynamic_Memory(){

     this->Clear_String_Memory(this->script_path);

     this->Clear_String_Memory(this->object_files_location);

     this->Clear_String_Memory(this->MakeFiles_Root_Directory);

}


void Source_File_Script_Writer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader_Ptr = Pointer;

     this->Repo_Rood_Dir = this->Des_Reader_Ptr->Get_Repo_Directory_Location();

     this->warehouse_path = this->Des_Reader_Ptr->Get_Warehouse_Location();
}

void Source_File_Script_Writer::Receive_Script_Data(Script_Data * Pointer){

     this->Src_Data_Pointer = Pointer; 
}

void Source_File_Script_Writer::Write_Source_File_Script(char operating_sis){

     this->Determine_MakeFiles_Root_Directory();

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

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("$Make_Files_Root_Dir=\"");

     this->FileManager.WriteToFile(this->MakeFiles_Root_Directory);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Project_Objects=\"");

     this->FileManager.WriteToFile(this->object_files_location);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



     if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

         this->FileManager.WriteToFile("$Make_File_Location=\"");

         this->FileManager.WriteToFile(this->Src_Data_Pointer->source_file_git_record_dir);

         this->FileManager.WriteToFile("\"");

         this->FileManager.WriteToFile("\n\n");
     }


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

     this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


     this->FileManager.WriteToFile("$Make_Files_Root_Dir");

     this->FileManager.WriteToFile("\\");

     
     if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

         this->FileManager.WriteToFile("$Make_File_Location");

         this->FileManager.WriteToFile("\\");
     }

     this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("if ($Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n   Remove-Item ");


     this->FileManager.WriteToFile("$Make_Files_Root_Dir");

     this->FileManager.WriteToFile("\\");

     if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

         this->FileManager.WriteToFile("$Make_File_Location");

         this->FileManager.WriteToFile("\\");
     }


     this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n}");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("mingw32-make -f ");


     this->FileManager.WriteToFile(this->Src_Data_Pointer->make_file_name);

     this->FileManager.WriteToFile(" 2>&1 > ");


     std::string output_file_name;
     
     this->Determine_Compiler_Output_File_Name(output_file_name);

     this->FileManager.WriteToFile("$Make_Files_Root_Dir");

     this->FileManager.WriteToFile("\\");

     if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

         this->FileManager.WriteToFile("$Make_File_Location");

         this->FileManager.WriteToFile("\\");
     }

     this->FileManager.WriteToFile(output_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("if($LASTEXITCODE -ne 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   Write-Output \"# Compiler fails on ");

     this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);

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

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


      this->FileManager.WriteToFile("$Make_Files_Root_Dir");

      this->FileManager.WriteToFile("\\");

     if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

         this->FileManager.WriteToFile("$Make_File_Location");

         this->FileManager.WriteToFile("\\");
     }


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

      this->FileManager.WriteToFile("      Remove-Item ");

      this->FileManager.WriteToFile("$Project_Objects");

      this->FileManager.WriteToFile("\\");

      this->FileManager.WriteToFile(this->Src_Data_Pointer->object_file_name);

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   }");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("   Move-Item -Path ");


      this->FileManager.WriteToFile("$Make_Files_Root_Dir");

      this->FileManager.WriteToFile("\\");


      if(!this->Src_Data_Pointer->source_file_git_record_dir.empty()){

          this->FileManager.WriteToFile("$Make_File_Location");

          this->FileManager.WriteToFile("\\");
      }


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

     this->Clear_String_Memory(this->script_path);

     this->Memory_Delete_Condition = false;


     std::string script_add_win = ".ps1";

     std::string script_add_bash = ".sh";


     std::string src_dir  = this->Src_Data_Pointer->source_file_dir;

     std::string src_name = this->Src_Data_Pointer->src_name_without_ext;

     std::string git_record_dir = this->Src_Data_Pointer->source_file_git_record_dir;



     size_t make_files_dir_size = this->MakeFiles_Root_Directory.size();

     for(size_t i=0;i<make_files_dir_size;i++){

         this->script_path.push_back(this->MakeFiles_Root_Directory[i]);
     }


     if(this->opr_sis == 'w'){

        if(this->script_path.back()!= '\\'){

           this->script_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->script_path.back()!= '/'){

           this->script_path.push_back('/');
        }
     }


     size_t name_size = src_name.length();

     size_t dir_size = git_record_dir.length();

     int index = 0;

     for(size_t i=0;i<dir_size;i++){

         this->script_path.push_back(git_record_dir[i]);         
     }

     if(opr_sis == 'w'){

        this->script_path.push_back('\\');
     }

     if(opr_sis == 'l'){

        this->script_path.push_back('/');        
     }

     for(size_t i=0;i<name_size;i++){

        this->script_path.push_back(src_name[i]);        
     }

     if(opr_sis == 'w'){

        size_t add_size = script_add_win.length();

        for(size_t i=0;i<add_size;i++){

           this->script_path.push_back(script_add_win[i]);
        }
     }

     if(opr_sis == 'l'){

        size_t add_size = script_add_bash.length();

        for(size_t i=0;i<add_size;i++){

            this->script_path.push_back(script_add_bash[i]);            
        }
     }

     this->script_path.shrink_to_fit();
}



void Source_File_Script_Writer::Determine_Warehouse_Paths(char opr_sis){

     this->Clear_String_Memory(this->object_files_location);

     this->Clear_String_Memory(this->compiler_output_location);



     std::string object_files_location_add = "OBJECT.FILES";

     std::string compiler_output_location_add = "Compiler_Output.txt";


     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->object_files_location,object_files_location_add,opr_sis);

     this->Determine_Compiler_Output_Path(this->Src_Data_Pointer->src_name_without_ext);

}


void Source_File_Script_Writer::Determine_MakeFiles_Root_Directory(){

     std::string warehouse_location = this->Des_Reader_Ptr->Get_Warehouse_Location();

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



void Source_File_Script_Writer::Construct_Path(std::string & path,

     std::string string, char opr_sis){

     std::string warehouse_word = "WAREHOUSE";

     size_t warehouse_path_size = this->warehouse_path.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         path.push_back(this->warehouse_path[i]);         
     }

     if(opr_sis == 'w'){

       if(this->warehouse_path.back() != '\\'){

          path.push_back('\\');
       }
     }


     if(opr_sis == 'l'){

       if(this->warehouse_path.back() != '/'){

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


void Source_File_Script_Writer::Determine_Compiler_Output_File_Name(std::string & name){

     std::string compiler_output_file_add = "_Compiler_Output.txt";
     
     std::string class_name = this->Src_Data_Pointer->src_name_without_ext;

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



void Source_File_Script_Writer::Determine_Compiler_Output_Path(std::string class_name)
{
     std::string output_directory = "WAREHOUSE\\OUTPUTS";

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
