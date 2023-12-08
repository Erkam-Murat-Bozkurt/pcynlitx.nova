


#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(char * DesPATH, char opr_sis) : 

 Rep_Init(DesPATH,opr_sis),   Dep_Determiner(DesPATH,opr_sis) , 

 Mk_Builder(DesPATH,opr_sis), Script_Writer(opr_sis), 
 
 Git_Data_Proc(opr_sis), Des_Reader(opr_sis)
 
{    
    this->Memory_Delete_Condition = false;

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

void Build_Tools_Initializer::Setup_Build_Tools(){

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\n\n The project descriptor file read ";


     this->Git_Data_Proc.Write_Git_Repo_List_File();

     this->Git_Data_Proc.Determine_Git_Repo_Info();    

     std::cout << "\n\n The data for git version controller has been collected ";


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Git_Data_Proc);

     this->Dep_Determiner.Collect_Dependency_Information();

     std::cout << "\n\n Source file dependencies has been determined ";



     this->Rep_Init.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Rep_Init.Receive_Git_Data_Processor(&this->Git_Data_Proc);

    
     this->Mk_Builder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);
   

     this->Script_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);
   
     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);    
 

     this->Rep_Init.Build_Project_Warehouse();

     this->Rep_Init.Clear_Dynamic_Memory();

     std::cout << "\n\n The project warehouse constructed ";


     this->Mk_Builder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Mk_Builder.Build_Make_Files();

     this->Mk_Builder.Clear_Dynamic_Memory();
     
     
     std::cout << "\n\n The project makefiles constructed ";

     this->Script_Writer.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Script_Writer.Build_Compiler_Script();

     std::cout << "\n\n The project scripts constructed ";

     std::cout << "\n\n";

}
