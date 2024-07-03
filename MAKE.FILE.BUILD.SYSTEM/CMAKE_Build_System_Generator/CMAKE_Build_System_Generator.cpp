


#include "CMAKE_Build_System_Generator.hpp"

CMAKE_Build_System_Generator::CMAKE_Build_System_Generator(char * DesPath, char opr_sis) : CMAKE_ListFileBuilder(DesPath,opr_sis)
{
     this->Memory_Delete_Condition = true;

     this->opr_sis = opr_sis;

     this->CMAKE_MainFileBuilder.Receive_Operating_System('w');
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


void CMAKE_Build_System_Generator::Receive_Git_Data_Processor(Git_Data_Processor * proc){

     this->CMAKE_MainFileBuilder.Receive_Git_Data_Processor(proc);
}


void CMAKE_Build_System_Generator::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->CMAKE_ListFileBuilder.Receive_Descriptor_File_Reader(ptr);

     this->CMAKE_MainFileBuilder.Receive_Descriptor_File_Reader(ptr);

}


void CMAKE_Build_System_Generator::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner 

     * dep_ptr){

     this->CMAKE_ListFileBuilder.Receive_Source_File_Dependency_Determiner(dep_ptr);

     this->CMAKE_MainFileBuilder.Receive_Source_File_Dependency_Determiner(dep_ptr);

}


void CMAKE_Build_System_Generator::Construct_Build_System(){

     this->CMAKE_ListFileBuilder.Build_Make_Files();

     this->CMAKE_MainFileBuilder.Receive_CMAKE_Lists_Construction_Directories(this->CMAKE_ListFileBuilder.Get_CMAKE_Lists_Construction_Directories());

     this->CMAKE_MainFileBuilder.Build_Main_CMAKE_File();
}
