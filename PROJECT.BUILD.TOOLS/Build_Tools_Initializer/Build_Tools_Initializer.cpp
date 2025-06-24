



/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/


#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis, char build_type) : 

 Rep_Init(DesPATH,opr_sis),   Dep_Determiner(DesPATH,opr_sis) , 

 Mk_Builder(DesPATH,opr_sis), Script_Writer(opr_sis), 
 
 Git_Data_Proc(opr_sis), Des_Reader(opr_sis)
{    
    this->Memory_Delete_Condition = false;

    this->build_type = build_type;

    this->opr_sis = opr_sis;

    this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

    this->Git_Data_Proc.Receive_Descriptor_File_Path(DesPATH);
}




Build_Tools_Initializer::~Build_Tools_Initializer(){

  if(!this->Memory_Delete_Condition){

      this->Memory_Delete_Condition = true;

      this->Clear_Dynamic_Memory();
  }
}

void Build_Tools_Initializer::Clear_Dynamic_Memory(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Rep_Init.Clear_Dynamic_Memory();

        this->Dep_Determiner.Clear_Object_Memory();

        this->Des_Reader.Clear_Dynamic_Memory();

        this->Script_Writer.Clear_Dynamic_Memory();

        this->Git_Data_Proc.Clear_Dynamic_Memory();

        this->Mk_Builder.Clear_Dynamic_Memory();
    }  
}


void Build_Tools_Initializer::Receive_System_Interface( Custom_System_Interface * Int){

     this->SysInt = Int;
}

void Build_Tools_Initializer::Receive_Build_Type(char BuildType){

     this->build_type = BuildType;
}


void Build_Tools_Initializer::Setup_Build_Tools(){

     this->Des_Reader.Read_Descriptor_File();

     char read_opr [] = "The project descriptor file read\n\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
 


     this->Git_Data_Proc.Write_Git_Repo_List_File();

     this->Git_Data_Proc.Determine_Git_Repo_Info();    

     char git_data [] = "The data for git version controller has been collected\n\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Dep_Determiner.Collect_Dependency_Information();

     char dependency_data [] = "Source file dependencies has been determined\n\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     this->Rep_Init.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Rep_Init.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    
     this->Mk_Builder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);
   

     this->Script_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);
   
     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);    
 

     this->Rep_Init.Build_Project_Warehouse();

     this->Rep_Init.Clear_Dynamic_Memory();

     char warehouse_constration [] = "The project warehouse constructed\n\n";

     std::cout << warehouse_constration;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(warehouse_constration);
     }



     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Mk_Builder.Build_Make_Files();

     this->Mk_Builder.Clear_Dynamic_Memory();
     
     char make_file_construction [] = "The project makefiles constructed\n\n";

     std::cout << make_file_construction;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(make_file_construction);
     }




     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Writer.Build_Compiler_Script();

     char script_construction [] = "The project scripts constructed\n\n";

     std::cout << script_construction;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(script_construction);
     }

     char endLines [] = "\n\n";

     std::cout << endLines;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(endLines);
     }

     this->Remove_Git_File_List();
}

void Build_Tools_Initializer::Remove_Git_File_List(){

     this->Determine_Git_File_List_Path();

     Cpp_FileOperations FileOperator;

     FileOperator.Delete_File(this->git_file_list_path);

     FileOperator.Clear_Dynamic_Memory();
}


void Build_Tools_Initializer::Determine_Git_File_List_Path()
{
     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     std::string warehouse_path = this->Des_Reader.Get_Warehouse_Location();

     size_t warehouse_path_size = warehouse_path.length();

     if(!this->git_file_list_path.empty()){

        this->git_file_list_path.clear();

        this->git_file_list_path.shrink_to_fit();
     }


     for(size_t i=0;i<warehouse_path_size;i++){

         this->git_file_list_path.push_back(warehouse_path[i]) ;
     }

     if(this->opr_sis == 'w'){

       if(warehouse_path[warehouse_path_size-1] != '\\'){

          this->git_file_list_path.push_back('\\') ;
       }
     }

     if(this->opr_sis == 'l'){

         if(warehouse_path[warehouse_path_size-1] != '/'){

            this->git_file_list_path.push_back('/') ;
         }
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_file_list_path.push_back(repo_list_file_name[i]) ;
     }
}