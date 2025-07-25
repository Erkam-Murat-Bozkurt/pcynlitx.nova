
/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



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


void Executable_MakeFile_Script_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Src_Data_Processor.Receive_Descriptor_File_Reader(ptr);

     this->Repo_Root_Dir = this->Des_Reader->Get_Repo_Directory_Location();
}

void Executable_MakeFile_Script_Builder::Receive_Exe_File_Name(char * exe_file_name){

     size_t name_size = strlen(exe_file_name);

     for(size_t i=0;i<name_size;i++){

         this->exe_file_name.push_back(exe_file_name[i]);
     }

     this->exe_file_name.shrink_to_fit();
}


 void Executable_MakeFile_Script_Builder::Receive_Construction_Directory_Path(std::string path){

      this->Construction_Directory_Path = path;
 }


void Executable_MakeFile_Script_Builder::Receive_File_System_Path(char * file_sys_path){

     size_t path_size = strlen(file_sys_path);

     for(size_t i=0;i<path_size;i++){

         this->file_sys_path.push_back(file_sys_path[i]);
     }

     this->file_sys_path.shrink_to_fit();

     size_t start_point = 0, end_point=0;     

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(file_sys_path[i] == '\\'){

               start_point =i+1;

               break;
            }
         }

         if(this->opr_sis == 'l'){

            if(file_sys_path[i] == '/'){

               start_point =i+1;

               break;
            }
         }
         
     }


     for(size_t i=path_size;i>0;i--){

         if(file_sys_path[i]=='.'){

            end_point = i;

            break;
         }
     }     

     // DETERMINATION OF SOURCE FILE NAME WITHOUT FILE EXTANTION

     for(size_t i=start_point;i<end_point;i++){

         this->file_name_without_ext.push_back(file_sys_path[i]);
     }

     this->file_name_without_ext.shrink_to_fit();


     // DETERMINATION OF SOURCE FILE NAME WITH FILE EXTANTION

     for(size_t i=start_point;i<path_size;i++){

         this->src_file_name.push_back(file_sys_path[i]);
     }

     this->src_file_name.shrink_to_fit();
}


void Executable_MakeFile_Script_Builder::Build_Compiler_Script_For_Executable_File(char * src_name){

     this->Src_Data_Processor.Process_Script_Data();
     
     this->Data_Pointer = this->Src_Data_Processor.Get_Script_Data_Address();

     std::string src_file_name;

     size_t name_size = strlen(src_name);

     for(size_t i=0;i<name_size;i++){

          src_file_name.push_back(src_name[i]);
     }

     src_file_name.shrink_to_fit();
     

     this->source_file_num = this->Src_Data_Processor.Get_Source_File_Number();

     this->warehouse_path = this->Des_Reader->Get_Warehouse_Location();

     this->Determine_MakeFiles_Root_Directory();

     this->Determine_Object_Files_Location('w');

     this->Construct_Script_Path();

     this->Determine_Script_Builder_Make_File_Name();

     this->Write_The_Executable_Make_File_Update_Script(src_file_name);
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



     this->FileManager.WriteToFile("# MakeFiles_Location is the root directory of make files ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n$MakeFiles_Location=\"");

     this->FileManager.WriteToFile(this->MakeFiles_Root_Directory);

     this->FileManager.WriteToFile("\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     char cd_word [] = "Set-Location ";

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Host  \"The object files related with ");

     this->FileManager.WriteToFile(this->src_file_name);


     this->FileManager.WriteToFile(" will be updated\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("Write-Output \"Total number of the source file: ");

     this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

     this->FileManager.WriteToFile("\"");


     this->FileManager.WriteToFile("\n\n");


     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n\n");




     for(int i=0;i<this->source_file_num-1;i++){

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");

         this->Change_Directory(i);

         this->Compile_The_Source_File(i);

         this->Print_Build_Output_To_Screen(i);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile("\n");
     }


     
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     std::string des_path = this->Des_Reader->Get_Descriptor_File_Path();


     this->FileManager.WriteToFile("\nPcynlitx_Kernel.exe ");

     this->FileManager.WriteToFile(des_path);

     this->FileManager.WriteToFile(" -up_lib");


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");



     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(cd_word);

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile(this->Construction_Directory_Path);

     this->FileManager.WriteToFile("\n");
         
     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


     this->FileManager.WriteToFile(this->Construction_Directory_Path);

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->exe_file_name);


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("if($Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   Remove-Item ");

     this->FileManager.WriteToFile(this->Construction_Directory_Path);

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->exe_file_name);


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("}");



     this->Determine_Compiler_Output_Path(this->exe_file_name);




     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("mingw32-make -f ");


     this->FileManager.WriteToFile(this->script_builder_make_file_name);

     this->FileManager.WriteToFile(" 2>&1 > ");

     std::string output_file_name;

     this->Determine_Compiler_Output_File_Name(output_file_name,this->Data_Pointer->back().src_name_without_ext);


     this->FileManager.WriteToFile(output_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");



     this->FileManager.WriteToFile("if($LASTEXITCODE -ne 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   Write-Output \"# Compiler fails on ");

     this->FileManager.WriteToFile(this->exe_file_name);

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

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\n");

     this->FileManager.WriteToFile("Write-Output \"THE EXECUTABLE FILE CONSTRUCTED\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Output \"\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}


int Executable_MakeFile_Script_Builder::Determine_Decimal_Space(int total_src_num, int current_number){
     
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


 void Executable_MakeFile_Script_Builder::Change_Directory(int index){ 
   
      // Writing Code for directory change 

      // THIS IS THE META FUNCTION WRITING THE CODES FOR DIRECTORY CHANGE OPERATION
      
      char cd_word [] = "Set-Location ";

      this->FileManager.WriteToFile("\n");

      this->FileManager.WriteToFile("\n\n");

      this->FileManager.WriteToFile("# Dependency: ");

      std::string dep = std::to_string(this->Data_Pointer->at(index).dependency);

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


      this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_git_record_dir);      
 }



void Executable_MakeFile_Script_Builder::Determination_of_Up_to_date_Status(int index){
   
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("mingw32-make -q ");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).make_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$UP_TO_DATE_COND=$LASTEXITCODE");

     this->FileManager.WriteToFile("\n");
}




void Executable_MakeFile_Script_Builder::Remove_The_Current_Object_File(int index){
      
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Condition = Test-Path -Path ");


     this->FileManager.WriteToFile("$MakeFiles_Location");

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_git_record_dir);

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("if($Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("  Remove-Item ");

     this->FileManager.WriteToFile("$MakeFiles_Location");

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_git_record_dir);

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("}");

     this->FileManager.WriteToFile("\n");

}



void Executable_MakeFile_Script_Builder::Compile_The_Source_File(int index){

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



     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_git_record_dir);

     if(this->opr_sis == 'w'){

        this->FileManager.WriteToFile("\\");
     }

     if(this->opr_sis == 'l'){

        this->FileManager.WriteToFile("/");
     }


     this->FileManager.WriteToFile(this->Data_Pointer->at(index).src_name_without_ext);

     this->FileManager.WriteToFile(".ps1");
}




void Executable_MakeFile_Script_Builder::Check_Build_Success_Status(int index){

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("if($LASTEXITCODE -ne 0){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   Write-Output \"# Compiler fails on ");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

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

}


void Executable_MakeFile_Script_Builder::Determine_MakeFile_Directory(std::string & mkf_dir, 

     std::string git_record_dir){

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

void Executable_MakeFile_Script_Builder::Determine_Compiler_Output_File_Name(std::string & name, std::string class_name){

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


void Executable_MakeFile_Script_Builder::Move_Object_File_To_The_Warehouse(int index){
     
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("$Condition = Test-Path -Path ");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_dir);

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("if($Condition){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   $Exists_On_Obj_Dir = Test-Path -Path $Project_Objects_Location");

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   if($Exists_On_Obj_Dir){");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("      Remove-Item ");

     this->FileManager.WriteToFile("$Project_Objects_Location");

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   }");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("   Move-Item -Path ");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_dir);

     this->FileManager.WriteToFile("\\");

     this->FileManager.WriteToFile(this->Data_Pointer->at(index).object_file_name);

     this->FileManager.WriteToFile(" -Destination $Project_Objects_Location");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("}");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");
}


void Executable_MakeFile_Script_Builder::Print_Build_Output_To_Screen(int index){

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Host \"[\" -NoNewline ");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     int decimal_space = this->Determine_Decimal_Space(this->source_file_num,index+1);

     this->FileManager.WriteToFile("Write-Host \"");

     for(int k=0;k<decimal_space;k++){

         this->FileManager.WriteToFile(" ");       
     }

     this->FileManager.WriteToFile("\" -NoNewline");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("Write-Host \"");

     this->FileManager.WriteToFile(this->Translater.Translate(index+1));

     this->FileManager.WriteToFile("\" -ForegroundColor Green -NoNewline");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Host \"");

     this->FileManager.WriteToFile(" / ");

     this->FileManager.WriteToFile(this->Translater.Translate(this->source_file_num));

     this->FileManager.WriteToFile("\" -ForegroundColor White -NoNewline");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("Write-Host \"] Built for ");


     this->FileManager.WriteToFile(this->Data_Pointer->at(index).source_file_name);

     this->FileManager.WriteToFile(" complated\"");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");
}




void Executable_MakeFile_Script_Builder::Determine_MakeFiles_Root_Directory(){

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


void Executable_MakeFile_Script_Builder::Clear_Dynamic_Memory(){

     this->Src_Data_Processor.Clear_Dynamic_Memory(); 

     this->Clear_String_Memory(&this->script_path);

     this->Clear_String_Memory(&this->file_sys_path);

     this->Clear_String_Memory(&this->file_sys_dir);

     this->Clear_String_Memory(&this->file_name_without_ext);

     this->Clear_String_Memory(&this->script_builder_make_file_name);

     this->Clear_String_Memory(&this->exe_file_name);

     this->Clear_String_Memory(&this->src_file_name);

}

void Executable_MakeFile_Script_Builder::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
    }
}


void Executable_MakeFile_Script_Builder::Determine_Script_Builder_Make_File_Name(){

     this->script_builder_make_file_name = this->file_name_without_ext;

     std::string file_ext = "_exe_builder.make";

     for(size_t i=0;i<file_ext.size();i++){

         this->script_builder_make_file_name.push_back(file_ext[i]);
     }
}



void Executable_MakeFile_Script_Builder::Determine_Object_Files_Location(char opr_sis){

     this->Clear_String_Memory(this->object_files_location);

     std::string object_files_location_add = "OBJECT.FILES";

     this->Memory_Delete_Condition = false;

     this->Construct_Path(this->object_files_location,object_files_location_add,opr_sis);
}


void Executable_MakeFile_Script_Builder::Determine_Compiler_Output_Path(std::string class_name)
{
     this->Clear_String_Memory(this->compiler_output_location);

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



void Executable_MakeFile_Script_Builder::Construct_Script_Path(){

     std::string file_sys_dir;

     std::string name_without_ext;

     this->Determine_File_Name(name_without_ext);

     for(size_t i=0;i<this->Construction_Directory_Path.size();i++){

         this->script_path.push_back(this->Construction_Directory_Path[i]);
     }

     if(this->opr_sis == 'w'){

        if(this->script_path.back()!='\\'){

           this->script_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->script_path.back()!='/'){

           this->script_path.push_back('/');
        }
     }
     
     for(size_t i=0;i<name_without_ext.size();i++){

         this->script_path.push_back(name_without_ext[i]);
     }

     std::string script_path_add = "_exe_build_script.ps1";


     size_t string_size = script_path_add.length();

     for(size_t i=0;i<string_size;i++){

        this->script_path.push_back(script_path_add[i]);        
     }     

     this->script_path.shrink_to_fit();
}



void Executable_MakeFile_Script_Builder::Determine_Src_File_Sys_Dir(std::string & file_sys_dir){

     size_t path_size = this->file_sys_path.length();

     size_t dir_size = path_size;

     for(size_t i=path_size;i>0;i--){

        if(this->opr_sis == 'w'){

           if(this->file_sys_path[i] == '\\'){

              break;
           }
           else{

              dir_size--;
           }
        }

        if(this->opr_sis == 'l'){

           if(this->file_sys_path[i] == '/'){

              break;
           }
           else{

              dir_size--;
           }
        }
     }

     for(size_t i=0;i<dir_size;i++){

         file_sys_dir.push_back(this->file_sys_path[i]);        
     }
}


void Executable_MakeFile_Script_Builder::Determine_File_Name(std::string & FileName_Without_Ext){

     size_t path_size = this->file_sys_path.length();

     size_t start_point = path_size, end_point;

     for(size_t i=path_size;i>0;i--){

         if(this->file_sys_path[i] == '.'){

            end_point = i;

            break;
         }
     }

     for(size_t i=path_size;i>0;i--){

        if(this->opr_sis == 'w'){

           if(this->file_sys_path[i] == '\\'){

              start_point++;

              break;
           }
           else{

              start_point--;
           }
        }

        if(this->opr_sis == 'l'){

           if(this->file_sys_path[i] == '/'){

              start_point++;

              break;
           }
           else{

              start_point--;
           }
        }         
     }

    
     for(size_t i=start_point;i<end_point;i++){

         FileName_Without_Ext.push_back(this->file_sys_path[i]);
     }

     FileName_Without_Ext.shrink_to_fit();
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


std::string Executable_MakeFile_Script_Builder::Get_Src_File_Name_Without_Ext(){

     return this->file_name_without_ext;   
}

std::string Executable_MakeFile_Script_Builder::Get_Src_File_Name(){

     return this->src_file_name;   
}

std::string Executable_MakeFile_Script_Builder::Get_Construction_Directory_Path(){

     return this->Construction_Directory_Path;
}