

#include "Kernel.hpp"

Kernel::Kernel(char * DesPATH, char opr_sis) : Bld_Init(DesPATH,opr_sis),  

     Exe_Bld(DesPATH,opr_sis)
{     
   
}

Kernel::~Kernel(){

}


void Kernel::Receive_System_Interface(Custom_System_Interface * Int){

     this->SysInt = Int;
}

void Kernel::Setup_Build_Tools(char type){

     this->Bld_Init.Receive_System_Interface(this->SysInt);

     this->Bld_Init.Setup_Build_Tools(type);
}


void Kernel::Build_MakeFile(char * src_path, 

     char * Exe_Name, char strategy){

     this->Exe_Bld.Build_MakeFile(src_path,Exe_Name,strategy);
}


void Kernel::Clear_Dynamic_Memory(){

     this->Bld_Init.Clear_Dynamic_Memory();

     this->Exe_Bld.Clear_Dynamic_Memory();
}
