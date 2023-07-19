
#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis) : 

 Rep_Init(DesPATH,opr_sis),  Dep_Determiner(DesPATH,opr_sis) , 
 Mk_Builder(DesPATH,opr_sis), Script_Writer(DesPATH,opr_sis)
 
{
    std::cout << "\n\n\e[1;32mC++ BUILD SYSTEM CONSTRUCTION PROCESS INITIATED\e[0m\n";

    
    this->Dep_Determiner.Collect_Dependency_Information();

    std::cout << "\n\n\e[1;32mThe source file dependencies determined \e[0m\n\n";

}

Build_Tools_Initializer::~Build_Tools_Initializer(){

  if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
  }
}

void Build_Tools_Initializer::Clear_Dynamic_Memory(){


}

void Build_Tools_Initializer::Setup_Build_Tools(){

     this->Rep_Init.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Rep_Init.Build_Project_Warehouse();

     this->Rep_Init.Clear_Dynamic_Memory();

     std::cout << "\n\n\e[1;32mThe project warehouse constructed \e[0m\n\n";

     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Mk_Builder.Build_Make_Files();

     this->Mk_Builder.Clear_Dynamic_Memory();

     std::cout << "\n\n\e[1;32mThe project makefiles constructed \e[0m\n\n";

     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Writer.Build_Compiler_Script();

     std::cout << "\n\n\e[1;32mThe project scripts constructed \e[0m\n\n";
}
