
#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis) : 

 Rep_Init(DesPATH,opr_sis),  Dep_Determiner(DesPATH,opr_sis) , 
 Mk_Builder(DesPATH,opr_sis), Script_Writer(opr_sis), 
 Git_Data_Proc(opr_sis), Des_Reader(opr_sis)
 
{    
    this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);

    this->Des_Reader.Read_Descriptor_File();

    std::cout << "\n\n\e[1;32mThe project descriptor file read \e[0m\n\n";



    this->Git_Data_Proc.Receive_Descriptor_File_Path(DesPATH);

    this->Git_Data_Proc.Write_Git_Repo_List_File();

    this->Git_Data_Proc.Determine_Git_Repo_Info();

    this->Git_Data_Proc.Set_Git_Ignoring_Files();

    std::cout << "\n\n\e[1;32mThe data for git version controller has been collected \e[0m\n\n";



    this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

    this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    this->Dep_Determiner.Collect_Dependency_Information();

    std::cout << "\n\n\e[1;32mSource file dependencies has been determined \e[0m\n\n";


    this->Rep_Init.Receive_Descriptor_File_Reader(&this->Des_Reader);

    this->Rep_Init.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    this->Rep_Init.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);


    std::cout << "\n\n\e[1;32mProject warehouse constructed \e[0m\n\n";


    this->Mk_Builder.Receive_Descriptor_File_Reader(&this->Des_Reader);

    this->Mk_Builder.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);


    this->Script_Writer.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    this->Script_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

    this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

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
