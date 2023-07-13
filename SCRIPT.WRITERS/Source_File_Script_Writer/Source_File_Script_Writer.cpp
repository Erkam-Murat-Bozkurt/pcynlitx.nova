

#include "Source_File_Script_Writer.hpp"

Source_File_Script_Writer::Source_File_Script_Writer(){

     this->Memory_Delete_Condition = true;
}


Source_File_Script_Writer::~Source_File_Script_Writer(){

   if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Clear_Dynamic_Memory();
   }
}

void Source_File_Script_Writer::Clear_String_memory(std::string & str)
{
     if(!str.empty()){

         str.clear();
         str.shrink_to_fit();        
     }
}

void Source_File_Script_Writer::Clear_Dynamic_Memory(){

     this->Clear_String_memory(this->script_path);

     this->Clear_String_memory(this->headers_locations);

     this->Clear_String_memory(this->object_files_location);

     this->Clear_String_memory(this->script_path);
     
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

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


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

     this->Clear_String_memory(this->script_path);

     this->Memory_Delete_Condition = false;


     std::string script_add_win = ".ps1";

     std::string script_add_bash = ".sh";


     std::string src_dir  = this->Src_Data_Pointer->source_file_dir;

     std::string src_name = this->Src_Data_Pointer->src_name_without_ext;



     size_t name_size = src_name.length();

     size_t dir_size = src_dir.length();

     int index = 0;

     for(size_t i=0;i<dir_size;i++){

         this->script_path.push_back(src_dir[i]);         
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

     this->Clear_String_memory(this->headers_locations);

     this->Clear_String_memory(this->object_files_location);

     this->Clear_String_memory(this->compiler_output_location);


     std::string headers_location_add = "PROJECT.HEADER.FILES";

     std::string object_files_location_add = "PROJECT.OBJECT.FILES";

     std::string compiler_output_location_add = "Compiler_Output.txt";


     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->headers_locations,headers_location_add,opr_sis);

     this->Construct_Path(this->object_files_location,object_files_location_add,opr_sis);

     this->Construct_Path(this->compiler_output_location,compiler_output_location_add,opr_sis);
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
