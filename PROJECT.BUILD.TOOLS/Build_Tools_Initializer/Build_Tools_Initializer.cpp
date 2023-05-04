
#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis) : 

 Rep_Init(DesPATH,opr_sis), Mk_Builder(DesPATH,opr_sis),
 Script_Writer(DesPATH,opr_sis), Des_Reader(DesPATH)
{
   this->Des_Reader.Read_Descriptor_File();



}

Build_Tools_Initializer::~Build_Tools_Initializer(){

  if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
  }

}

void Build_Tools_Initializer::Clear_Dynamic_Memory(){


}

void Build_Tools_Initializer::Setup_Build_Tools(){

     std::cout << "\n Descriptor File Readed ..";

     this->Rep_Init.Build_Project_Warehouse();

     std::cout << "\n Project warehouse constructed ..";

     this->Mk_Builder.Build_Make_Files();

     std::cout << "\n Project make files constructed ..";

     this->Script_Writer.Build_Compiler_Script();

     std::cout << "\n Project Script File constructed ..";
}
