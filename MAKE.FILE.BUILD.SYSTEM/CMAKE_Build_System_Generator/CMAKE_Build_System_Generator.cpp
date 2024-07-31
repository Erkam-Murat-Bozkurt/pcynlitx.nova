


#include "CMAKE_Build_System_Generator.hpp"

CMAKE_Build_System_Generator::CMAKE_Build_System_Generator(char * DesPath, char opr_sis, char build_type) 

  : CMAKE_SysCon(DesPath,opr_sis,build_type),
   
    Executable_Target_Constructor(DesPath,opr_sis,build_type)
{
     this->Memory_Delete_Condition = false;

     this->build_type = build_type;
}


CMAKE_Build_System_Generator::~CMAKE_Build_System_Generator(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Build_System_Generator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->CMAKE_SysCon.Clear_Dynamic_Memory();

         this->CMAKE_SysCon.Clear_Dynamic_Memory();

         this->Executable_Target_Constructor.Clear_Dynamic_Memory();

         this->Executable_Target_Constructor.Clear_Dynamic_Memory();
     }
}


void CMAKE_Build_System_Generator::Receive_System_Interface(Custom_System_Interface * sysInt){

     this->SysInt = sysInt;

     this->CMAKE_SysCon.Receive_System_Interface(sysInt);

     this->Executable_Target_Constructor.Receive_System_Interface(sysInt);
}



void CMAKE_Build_System_Generator::Construct_Build_System(std::string project_name, 

     std::string version_num){

     this->CMAKE_SysCon.Build_Make_Files(project_name,version_num);
     
     char build_system_geration [] = "\n  CMAKE Build System Generated..\n\n";

     std::cout << build_system_geration;

     if(this->build_type == 'g'){

        this->SysInt->WriteTo_NamedPipe_FromChild(build_system_geration);
     }
}


 void CMAKE_Build_System_Generator::Construct_Exe_Build_System(std::string target_main_file_path, 
 
      std::string exe_name){

      this->Executable_Target_Constructor.Build_MakeFile(target_main_file_path,exe_name);
     
      char build_system_geration [] = "\n   CMAKE Target Generated..\n\n";

      std::cout << build_system_geration;

      if(this->build_type == 'g'){

         this->SysInt->WriteTo_NamedPipe_FromChild(build_system_geration);
      }
 }
