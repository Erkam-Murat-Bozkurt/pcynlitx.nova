

#include "Kernel.hpp"

Kernel::Kernel(char * DesPATH, char opr_sis) : Bld_Init(DesPATH,opr_sis),  

     Exe_Bld(DesPATH,opr_sis), Des_Reader(opr_sis), Git_Prog(opr_sis), 
     
     Dep_Determiner(DesPATH,opr_sis)
{     
     this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

     this->Des_Reader.Read_Descriptor_File();


     
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

     this->Exe_Bld.Receive_Build_Type(BuildType);

     this->Bld_Init.Receive_Build_Type(BuildType);

     this->Dep_Determiner.Receive_Run_Type(BuildType);
}

void Kernel::Receive_System_Interface(Custom_System_Interface * Int){

     this->SysInt = Int;

     this->Dep_Determiner.Receive_System_Interface(Int);
}

void Kernel::Setup_Build_Tools(){

     this->Bld_Init.Receive_System_Interface(this->SysInt);

     this->Bld_Init.Setup_Build_Tools();
}


void Kernel::Build_MakeFile(char * src_path, 

     char * Exe_Name, char strategy){

     this->Exe_Bld.Receive_System_Interface(this->SysInt);

     this->Exe_Bld.Build_MakeFile(src_path,Exe_Name,strategy);
}


void Kernel::Clear_Dynamic_Memory(){

     this->Bld_Init.Clear_Dynamic_Memory();

     this->Exe_Bld.Clear_Dynamic_Memory();
}
