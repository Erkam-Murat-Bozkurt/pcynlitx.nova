


#include "CMAKE_Build_System_Generator.hpp"

CMAKE_Build_System_Generator::CMAKE_Build_System_Generator(char * DesPath, char opr_sis, char build_type) 

  : Des_Reader(opr_sis,build_type),  Data_Processor(opr_sis,build_type), 

    Dep_Determiner(DesPath,opr_sis), CMAKE_ListFileBuilder(DesPath,opr_sis)
{

     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;

     this->Des_Reader.Receive_Descriptor_File_Path(DesPath);

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\n Descriptor File Readed";


     this->Data_Processor.Receive_Descriptor_File_Path(DesPath);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  

     std::cout << "\n Git repo information collected";


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Collect_Dependency_Information();

     std::cout << "\n Dependency information collected";


     this->CMAKE_MainFileBuilder.Receive_Operating_System(this->opr_sis);

     this->CMAKE_ListFileBuilder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->CMAKE_MainFileBuilder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->CMAKE_MainFileBuilder.Receive_Git_Data_Processor(&this->Data_Processor);



     this->CMAKE_ListFileBuilder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->CMAKE_MainFileBuilder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     std::cout << "\n Build System Construction information collected";
}


CMAKE_Build_System_Generator::~CMAKE_Build_System_Generator(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Build_System_Generator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;


     }
}


void CMAKE_Build_System_Generator::Construct_Build_System(){

     this->CMAKE_MainFileBuilder.Build_Main_CMAKE_File();

     this->CMAKE_ListFileBuilder.Build_Make_Files();
}
