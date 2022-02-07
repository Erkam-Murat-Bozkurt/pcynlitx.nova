
#include "Build_Tools_Initializer.h"

Build_Tools_Initializer::Build_Tools_Initializer(){


}

Build_Tools_Initializer::Build_Tools_Initializer(const Build_Tools_Initializer & orig){


}

Build_Tools_Initializer::~Build_Tools_Initializer(){

  if(!this->Memory_Delete_Condition){

      this->Clear_Dynamic_Memory();
  }

}

void Build_Tools_Initializer::Clear_Dynamic_Memory(){


}

void Build_Tools_Initializer::Setup_Build_Tools(char * descriptor_file_path){

     this->Des_Reader.Read_Descriptor_File(descriptor_file_path);

     char * repo_dir_path = this->Des_Reader.Get_Root_Directory_Location();

     char * warehouse_path = this->Des_Reader.Get_Warehouse_location();

     this->Rep_Init.Build_Project_Warehouse(repo_dir_path,warehouse_path);

     std::cout << "\n Project warehouse constructed ..";

     this->Mk_Builder.Receive_Repo_Dir_Path(repo_dir_path);

     this->Mk_Builder.Receive_Warehouse_Path(warehouse_path);

     this->Mk_Builder.Build_Make_Files();

     std::cout << "\n Project make files constructed ..";

     this->Script_Writer.Build_Compiler_Script(repo_dir_path,warehouse_path);

     std::cout << "\n Project Script File constructed ..";
}
