


#include "CMAKE_Build_System_Generator.hpp"

CMAKE_Build_System_Generator::CMAKE_Build_System_Generator(char * DesPath, char opr_sis, char build_type) 

  : Des_Reader(opr_sis,build_type),  Data_Processor(opr_sis,build_type), 

    Dep_Determiner(DesPath,opr_sis), CMAKE_ListFileBuilder(DesPath,opr_sis)
{

     size_t des_path_size = strlen(DesPath);

     for(size_t i=0;i<des_path_size;i++){

         this->DesPATH.push_back(DesPath[i]);
     }

     this->DesPATH.shrink_to_fit();


     this->Memory_Delete_Condition = false;

     this->opr_sis = opr_sis;

}


CMAKE_Build_System_Generator::~CMAKE_Build_System_Generator(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void CMAKE_Build_System_Generator::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Data_Processor.Clear_Dynamic_Memory();

         this->Des_Reader.Clear_Dynamic_Memory();

         this->Dep_Determiner.Clear_Dynamic_Memory();

         this->CMAKE_ListFileBuilder.Clear_Dynamic_Memory();

         this->CMAKE_MainFileBuilder.Clear_Dynamic_Memory();

         this->Executable_Target_Constructor.Clear_Dynamic_Memory();
     }
}


void CMAKE_Build_System_Generator::Construct_Build_System(std::string project_name, 

     std::string version_num){

     this->Des_Reader.Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\n Descriptor File Readed";


     this->Data_Processor.Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  

     std::cout << "\n Git repo information collected";


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Collect_Dependency_Information();


     std::cout << "\n Dependency information collected";


     this->CMAKE_MainFileBuilder.Receive_Operating_System(this->opr_sis);

     this->CMAKE_MainFileBuilder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->CMAKE_MainFileBuilder.Receive_Git_Data_Processor(&this->Data_Processor);

     this->CMAKE_MainFileBuilder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);


     this->CMAKE_ListFileBuilder.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->CMAKE_ListFileBuilder.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);


     this->CMAKE_MainFileBuilder.Build_Main_CMAKE_File(project_name,version_num);

     this->CMAKE_ListFileBuilder.Build_Make_Files();
}


 void CMAKE_Build_System_Generator::Construct_Exe_Build_System(std::string target_main_file_path, 
 
      std::string exe_name){

      
     this->Des_Reader.Receive_Descriptor_File_Path(this->DesPATH);

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\n Descriptor File Readed";


     this->Data_Processor.Receive_Descriptor_File_Path(this->DesPATH);

     this->Data_Processor.Write_Git_Repo_List_File();

     this->Data_Processor.Determine_Git_Repo_Info();  

     std::cout << "\n Git repo information collected";


     this->Dep_Determiner.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Dep_Determiner.Receive_Git_Data_Processor(&this->Data_Processor);

     this->Dep_Determiner.Collect_Dependency_Information(target_main_file_path);


     std::cout << "\n Dependency information collected";

     this->Executable_Target_Constructor.Receive_Source_File_Dependency_Determiner(&this->Dep_Determiner);

     this->Executable_Target_Constructor.Receive_Descriptor_File_Reader(&this->Des_Reader);
    
     this->Executable_Target_Constructor.Receive_Operating_System(this->opr_sis);

     this->Executable_Target_Constructor.Build_MakeFile(target_main_file_path,exe_name);
 }
