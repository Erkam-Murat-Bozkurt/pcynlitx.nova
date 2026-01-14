
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


#include "Kernel.hpp"

Kernel::Kernel(char * DesPATH, char opr_sis, char build_type) : Bld_Init(DesPATH,opr_sis,build_type),  

     CMAKE_Builder(DesPATH,opr_sis,build_type),
     
     Exe_Bld(DesPATH,opr_sis,build_type), Des_Reader(opr_sis),
     
     Git_Prog(opr_sis), 
     
     Dep_Determiner(DesPATH,opr_sis), Lib_Up(opr_sis)
{     

     this->Receive_Build_Type(build_type); 
     
     // Build type is the selection between GUI application or Command line operation


     this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

     this->Des_Reader.Read_Descriptor_File();

     this->Build_System_Type = this->Des_Reader.Get_Build_System_Type();

     // Build system type is the selction between CMAKE or Native script builder

     this->Lib_Up.Receive_Descriptor_File_Path(DesPATH);
     
     this->Git_Prog.Receive_Descriptor_File_Path(DesPATH);

     this->Git_Prog.Write_Git_Repo_List_File();

     this->Git_Prog.Determine_Git_Repo_Info();
     
     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Prog);
}

Kernel::~Kernel(){

}

void Kernel::Determine_Source_File_Dependency_List(char * src_path){

     this->Dep_Determiner.Collect_Dependency_Information(src_path);
}

std::vector<Compiler_Data> * Kernel::Get_Src_Dependency_List(){

      return this->Dep_Determiner.Get_Compiler_Data_Address();
}

void Kernel::Receive_Build_Type(char BuildType){

     this->build_type = BuildType;

     this->Dep_Determiner.Receive_Run_Type(BuildType);
}

void Kernel::Receive_System_Interface(Custom_System_Interface * Int){

     this->SysInt = Int;

     this->Dep_Determiner.Receive_System_Interface(Int);

     this->CMAKE_Builder.Receive_System_Interface(Int);
}


void Kernel::Setup_Build_Tools(){

     if(this->Build_System_Type == "CMAKE"){

        std::cout << "\n\nCMAKE BUILD SYSTEM CONSTRUCTION PROCESS INITIATED \n";

        std::string project_name   = this->Des_Reader.Get_Project_Name();

        std::string version_number = this->Des_Reader.Get_Version_Number(); 

        this->CMAKE_Builder.Construct_Build_System(project_name,version_number);
     }
     else{

          if(this->Build_System_Type == "Shell-Scripting"){

             std::cout << "\n\nC++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED \n";

             this->Bld_Init.Receive_System_Interface(this->SysInt);

             this->Bld_Init.Setup_Build_Tools();
          }
     }
}


void Kernel::Build_MakeFile(char * src_path, 

     char * Exe_Name, char strategy){

     if(strategy=='c'){

        this->CMAKE_Builder.Construct_Exe_Build_System(src_path,Exe_Name);
     }
     else{

        this->Exe_Bld.Receive_System_Interface(this->SysInt);

        this->Exe_Bld.Build_MakeFile(src_path,Exe_Name,strategy);
     }
}

void Kernel::Update_Library(){

     this->Lib_Up.Build_Library();
}

void Kernel::Clear_Dynamic_Memory(){

     this->Bld_Init.Clear_Dynamic_Memory();

     this->Exe_Bld.Clear_Dynamic_Memory();
}
