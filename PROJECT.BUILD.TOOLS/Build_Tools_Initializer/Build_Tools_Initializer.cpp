
#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis) : 

 Rep_Init(DesPATH,opr_sis),  Dep_Determiner(DesPATH,opr_sis) , 
 Mk_Builder(DesPATH,opr_sis), Script_Writer(DesPATH,opr_sis)
 
{
    this->Dep_Determiner.Collect_Dependency_Information();

    std::cout << "\n\n\e[1;32mC++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED\e[0m\n";

}

Build_Tools_Initializer::~Build_Tools_Initializer(){

  if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
  }
}

void Build_Tools_Initializer::Clear_Dynamic_Memory(){


}

void Build_Tools_Initializer::Setup_Build_Tools(){

     this->Rep_Init.Build_Project_Warehouse();

     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Mk_Builder.Build_Make_Files();

     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Writer.Build_Compiler_Script();
}
