


#include "CMAKE_Build_System_Generator.hpp"

CMAKE_Build_System_Generator::CMAKE_Build_System_Generator(char * DesPath, char opr_sis, char build_type) 

  : CMAKE_ListFileBuilder(DesPath,opr_sis)
{

    this->build_type = build_type;

     size_t des_path_size = strlen(DesPath);

     for(size_t i=0;i<des_path_size;i++){

         this->DesPATH.push_back(DesPath[i]);
     }

     this->DesPATH.shrink_to_fit();


     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;

}


CMAKE_Build_System_Generator::~CMAKE_Build_System_Generator(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Build_System_Generator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->CMAKE_ListFileBuilder.Clear_Dynamic_Memory();

         this->CMAKE_MainFileBuilder.Clear_Dynamic_Memory();

         this->Executable_Target_Constructor.Clear_Dynamic_Memory();
     }
}


void CMAKE_Build_System_Generator::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;
}

void CMAKE_Build_System_Generator::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * dep_ptr){

     this->Dep_Determiner = dep_ptr;
}

void CMAKE_Build_System_Generator::Receive_Git_Data_Processor(Git_Data_Processor * Git_Proc){

     this->Data_Processor = Git_Proc;
}

void CMAKE_Build_System_Generator::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     if(this->build_type == 'g'){

        this->Des_Reader->Set_Gui_Read_Status(true);

        this->Data_Processor->Set_Gui_Read_Status(true);
     }
}



void CMAKE_Build_System_Generator::Construct_Build_System(std::string project_name, 

     std::string version_num){

     /*

     char warehouse_constration [] = "The project warehouse constructed\n\n";

     std::cout << warehouse_constration;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(warehouse_constration);
     }

     */

     /*

     this->Des_Reader->Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader->Read_Descriptor_File();


     char read_opr [] = "The project descriptor file read\n\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
 

     this->Data_Processor->Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor->Write_Git_Repo_List_File();

     this->Data_Processor->Determine_Git_Repo_Info();  


     char git_data [] = "The data for git version controller has been collected\n\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }


     this->Dep_Determiner->Receive_Descriptor_File_Reader(this->Des_Reader);

     this->Dep_Determiner->Receive_Git_Data_Processor(this->Data_Processor);

     this->Dep_Determiner->Collect_Dependency_Information();


     char dependency_data [] = "Source file dependencies has been determined\n\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     */


     this->CMAKE_MainFileBuilder.Receive_Operating_System(this->opr_sis);

     this->CMAKE_MainFileBuilder.Receive_Descriptor_File_Reader(this->Des_Reader);

     this->CMAKE_MainFileBuilder.Receive_Git_Data_Processor(this->Data_Processor);

     this->CMAKE_MainFileBuilder.Receive_Source_File_Dependency_Determiner(this->Dep_Determiner);


     this->CMAKE_ListFileBuilder.Receive_Descriptor_File_Reader(this->Des_Reader);

     this->CMAKE_ListFileBuilder.Receive_Source_File_Dependency_Determiner(this->Dep_Determiner);



     this->CMAKE_MainFileBuilder.Build_Main_CMAKE_File(project_name,version_num);

     this->CMAKE_ListFileBuilder.Build_Make_Files();

     
     char build_system_geration [] = "CMAKE Build System Generated..\n\n";

     std::cout << build_system_geration;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(build_system_geration);
     }
}


 void CMAKE_Build_System_Generator::Construct_Exe_Build_System(std::string target_main_file_path, 
 
      std::string exe_name){

     /* 
     this->Des_Reader->Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader->Read_Descriptor_File();

     char read_opr [] = "The project descriptor file read\n\n";

     std::cout << read_opr;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(read_opr);
     }
 

     this->Data_Processor->Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor->Write_Git_Repo_List_File();

     this->Data_Processor->Determine_Git_Repo_Info();  


     char git_data [] = "The data for git version controller has been collected\n\n";

     std::cout << git_data;


     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(git_data);
     }


     this->Dep_Determiner->Receive_Descriptor_File_Reader(this->Des_Reader);

     this->Dep_Determiner->Receive_Git_Data_Processor(this->Data_Processor);

     this->Dep_Determiner->Collect_Dependency_Information(target_main_file_path);


     char dependency_data [] = "Source file dependencies has been determined\n\n";

     std::cout << dependency_data;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(dependency_data);
     }

     */



     this->Executable_Target_Constructor.Receive_Source_File_Dependency_Determiner(this->Dep_Determiner);

     this->Executable_Target_Constructor.Receive_Descriptor_File_Reader(this->Des_Reader);
    
     this->Executable_Target_Constructor.Receive_Operating_System(this->opr_sis);

     this->Executable_Target_Constructor.Build_MakeFile(target_main_file_path,exe_name);

     
     char build_system_geration [] = "CMAKE Target Generated..\n\n";

     std::cout << build_system_geration;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(build_system_geration);
     }
 }
