


#include "Repo_Warehouse_Initializer.h"

Repo_Warehouse_Initializer::Repo_Warehouse_Initializer(char * DesPath, char opr_sis): 

 Git_List_Writer(opr_sis),       Git_Receiver(opr_sis), 
 Ignoring_Files_Lister(DesPath,opr_sis), Dir_Lister(DesPath,opr_sis), 
 Des_Reader(DesPath,opr_sis) 

{
     std::cout << "\n The start of the Repo_Warehouse_Initializer constructor";
     std::cin.get();

     this->Des_Reader.Read_Descriptor_File();

     std::cout << "\n Descriptor File Readed";;
     std::cin.get();    

     this->Git_Receiver.Determine_Git_Repo_Info();

     std::cout << "\n Git Repo Information Received";
     std::cin.get();    

     this->Dir_Lister.Determine_Git_Repo_Info();
     
     this->opr_sis = opr_sis;

     std::cout << "\n The start of the Repo_Warehouse_Initializer constructor";
     std::cin.get();
}



Repo_Warehouse_Initializer::~Repo_Warehouse_Initializer(){

     this->Clear_Dynamic_Memory();
}

 void Repo_Warehouse_Initializer::Receive_Source_File_Dependency_Determiner(Source_File_Dependency_Determiner * dtr){

      this->Dep_Determiner = dtr;
 }


void Repo_Warehouse_Initializer::Build_Project_Warehouse(){

     this->warehouse_location = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Current_Directory();

     this->Determine_Warehouse_Path();

     this->Determine_Header_Files_Directory();

     this->Determine_Object_Files_Directory();

     this->Determine_Library_Files_Directory();

     this->Determine_Compiler_Output_Directory();

     this->Construct_Warehouse_Path();

     this->Construct_Header_Files_Directory();

     this->Construct_Object_Files_Directory();

     this->Construct_Library_Files_Directory();

     this->Construct_Compiler_Outputs_Directory();

     this->DirectoryManager.ChangeDirectory(this->current_directory.c_str());

     this->source_files_number

     = this->Dir_Lister.Get_Source_File_Number();

     this->Determine_Header_File_Paths();

     this->Determine_Independent_Header_Paths();

     this->Copy_Header_Files_To_Project_Headers_Location();

     this->Copy_Independent_Header_Files_To_Project_Headers_Location();

     this->Ignoring_Files_Lister.Write_Ignoring_File_List();
}

void Repo_Warehouse_Initializer::Update_Warehaouse_Headers(){

     this->Git_List_Writer.Write_Git_Repo_List_File();

     this->warehouse_location = this->Des_Reader.Get_Warehouse_Location();

     this->Determine_Current_Directory();

     this->Determine_Warehouse_Path();

     this->Determine_Header_Files_Directory();

     this->DirectoryManager.ChangeDirectory(this->current_directory.c_str());

     this->Construct_Header_Files_Directory();

     this->source_files_number

     = this->Dir_Lister.Get_Source_File_Number();

     this->Determine_Header_File_Paths();

     this->Determine_Independent_Header_Paths();

     this->Copy_Header_Files_To_Project_Headers_Location();

     this->Copy_Independent_Header_Files_To_Project_Headers_Location();
}

void Repo_Warehouse_Initializer::Determine_Current_Directory(){

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t dir_name_size = strlen(Current_Directory);
     
     this->Clear_String_Memory(&this->current_directory);

     for(size_t i=0;i<dir_name_size;i++){
     
         this->current_directory.push_back(Current_Directory[i]);
     }

     this->current_directory.shrink_to_fit();
}

void Repo_Warehouse_Initializer::Determine_Warehouse_Path(){

     std::string warehouse_word  ="WAREHOUSE";

     size_t word_size = warehouse_word.length();

     size_t wr_location_size = this->warehouse_location.length();


     for(size_t i=0;i<wr_location_size;i++){

         this->warehouse_path.push_back(this->warehouse_location[i]);
     }

     if(this->opr_sis == 'w'){

        this->warehouse_path.push_back('\\');        
     }
     else{

          if(this->opr_sis == 'l'){

             this->warehouse_path.push_back('/');        
          }
     }

     for(size_t i=0;i<word_size;i++){

         this->warehouse_path.push_back(warehouse_word[i]);
     }

     this->warehouse_path.shrink_to_fit();
}

void Repo_Warehouse_Initializer::Determine_Header_Files_Directory(){

     std::string header_directory_folder_name = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t head_folder_size= header_directory_folder_name.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Headers_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

       this->Headers_Directory.push_back('\\');
     }
     else{

          if(this->opr_sis == 'l'){
                    
             this->Headers_Directory.push_back('/');
          }
     }


     for(size_t i=0;i<head_folder_size;i++){

         this->Headers_Directory.push_back(header_directory_folder_name[i]);         
     }
     
     this->Headers_Directory.shrink_to_fit();
}

void Repo_Warehouse_Initializer::Determine_Object_Files_Directory(){

     std::string object_directory_folder_name = "PROJECT.OBJECT.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t object_folder_size= object_directory_folder_name.length();

     for(size_t i=0;i<warehouse_path_size;i++){

         this->Object_Files_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis == 'w'){

        this->Object_Files_Directory.push_back('\\');
     }
     else{

        this->Object_Files_Directory.push_back('/');
     }


     for(size_t i=0;i<object_folder_size;i++){

         this->Object_Files_Directory.push_back(object_directory_folder_name[i]);
     }

     this->Object_Files_Directory.shrink_to_fit();
}

void Repo_Warehouse_Initializer::Determine_Library_Files_Directory(){

     std::string directory_folder_name = "PROJECT.LIBRARY.FILES";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t name_size= directory_folder_name.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->Library_Files_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis=='w'){
     
        this->Library_Files_Directory.push_back('\\');
     } 
     else{
           if(this->opr_sis == 'l'){
           
              this->Library_Files_Directory.push_back('/');              
           }         
     }     

     for(size_t i=0;i<name_size;i++){

         this->Library_Files_Directory.push_back(directory_folder_name[i]);         
     }

     this->Library_Files_Directory.shrink_to_fit();
}



void Repo_Warehouse_Initializer::Determine_Compiler_Output_Directory(){

     std::string directory_folder_name = "COMPILER.OUTPUTS";

     size_t warehouse_path_size = this->warehouse_path.length();

     size_t name_size= directory_folder_name.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->Compiler_Outputs_Directory.push_back(this->warehouse_path[i]);
     }

     if(this->opr_sis=='w'){
     
        this->Compiler_Outputs_Directory.push_back('\\');
     } 
     else{
           if(this->opr_sis == 'l'){
           
              this->Compiler_Outputs_Directory.push_back('/');              
           }         
     }     

     for(size_t i=0;i<name_size;i++){

         this->Compiler_Outputs_Directory.push_back(directory_folder_name[i]);         
     }

     this->Compiler_Outputs_Directory.shrink_to_fit();
}


void Repo_Warehouse_Initializer::Construct_Warehouse_Path(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->warehouse_path.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->warehouse_path.c_str());

        if(const_cond == 0){

            std::cout << "\n The project warehouse can not be constructed on:";

            std::cout << "\n";

            std::cout << this->warehouse_location;

            exit(0);
        }
     }
}



void Repo_Warehouse_Initializer::Construct_Header_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Headers_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Headers_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The headers files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Headers_Directory;

           exit(0);
        }
     }
}

void Repo_Warehouse_Initializer::Construct_Object_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Object_Files_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Object_Files_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The object files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Object_Files_Directory;

           exit(0);
        }
     }
}


void Repo_Warehouse_Initializer::Construct_Library_Files_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Library_Files_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Library_Files_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The Library files directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Library_Files_Directory;

           exit(0);
        }
     }
}


void Repo_Warehouse_Initializer::Construct_Compiler_Outputs_Directory(){

     int return_condition = this->DirectoryManager.ChangeDirectory(this->Compiler_Outputs_Directory.c_str());

     if(return_condition == 0){

        int const_cond = this->DirectoryManager.MakeDirectory(this->Compiler_Outputs_Directory.c_str());

        if(const_cond == 0){

           std::cout << "\n The compiler outputs directory can not be constructed on:";

           std::cout << "\n";

           std::cout << this->Compiler_Outputs_Directory;

           exit(0);
        }
     }
}



void Repo_Warehouse_Initializer::Determine_Header_File_Paths(){

     int index_size = this->Git_Receiver.Get_Git_File_Index_Size();

     std::string repo_dir = this->Git_Receiver.Get_Git_Repo_Directory();
     

      for(int i=0;i<index_size;i++){
      
          std::string file_sys_path = this->Git_Receiver.Get_File_System_Path(i);

          bool is_hdr = this->Dep_Determiner->Is_Header_File(file_sys_path);

          if(is_hdr){
          
             this->Header_File_Paths.push_back(file_sys_path);

             this->Determine_Header_File_Name_With_Extention(file_sys_path);       

             std::string head_name = this->Header_File_Name_With_Extention;

             std::string header_warehouse_path;

             for(size_t k=0;k<this->Headers_Directory.length();k++){
          
                 header_warehouse_path.push_back(this->Headers_Directory[k]);          
             }

             if(this->opr_sis == 'w'){
          
                header_warehouse_path.push_back('\\');    
      
             }
             else{
                    
                  if(this->opr_sis == 'l'){
             
                     header_warehouse_path.push_back('/');
                  }
             }

             for(size_t k=0;k<head_name.length();k++){
          
                 header_warehouse_path.push_back(head_name[k]);
             }

             header_warehouse_path.shrink_to_fit();

             this->Headers_New_Paths.push_back(header_warehouse_path);
          }
     }
}


void Repo_Warehouse_Initializer::Determine_Independent_Header_Paths(){

     this->ind_hdr_number

     = this->Dir_Lister.Get_Indenpendent_Header_Files_Number();

     for(int i=0;i<this->ind_hdr_number;i++){

         std::string path =  this->Dir_Lister.Get_Independent_Header_File(i);

         if(!path.empty()){

             this->Independent_Header_Paths.push_back(path);

             this->Determine_Header_File_Name_With_Extention(path);       

             std::string head_name = this->Header_File_Name_With_Extention;

             size_t wrd_path_size = this->Headers_Directory.length();

             std::string header_new_path;

             for(size_t k=0;k<wrd_path_size;k++){
             
                 header_new_path.push_back(this->Headers_Directory[k]);                 
             }            

             if(this->opr_sis == 'w'){
             
                 header_new_path.push_back('\\');             
             }
             else{
             
                  if(this->opr_sis == 'l'){
                  
                     header_new_path.push_back('/');                               
                  }             
             }
             
             for(size_t k=0;k<wrd_path_size;k++){
             
                 header_new_path.push_back(head_name[k]);                 
             }

             header_new_path.shrink_to_fit();

             this->Independent_Header_New_Paths.push_back(header_new_path);           
         }
     }
}


void Repo_Warehouse_Initializer::Copy_Header_Files_To_Project_Headers_Location(){
     
     size_t hdr_list_size = this->Header_File_Paths.size();

     size_t new_hdr_size  = this->Headers_New_Paths.size();

     if(hdr_list_size != new_hdr_size){
     
        std::cout << "\n The header file paths is not equal to the ";
        std::cout << "\n paths to be copied to the warehouse header location";
        
        exit(EXIT_FAILURE);
     }

     for(int i=0;i<hdr_list_size;i++){
         
         this->FileManager.CpFile(this->Header_File_Paths.at(i),

         this->Headers_New_Paths.at(i));            
     }
}

void Repo_Warehouse_Initializer::Copy_Independent_Header_Files_To_Project_Headers_Location(){

     size_t ind_hdr_num  = this->Independent_Header_Paths.size();

     size_t ind_new_path = this->Independent_Header_New_Paths.size(); 

     if(ind_hdr_num != ind_new_path){
     
        std::cout << "\n The independent header file paths is not equal to the ";
        std::cout << "\n paths to be copied to the warehouse header location";
        
        exit(EXIT_FAILURE);   
     }

     for(int i=0;i<ind_hdr_num;i++){

         this->FileManager.CpFile(this->Independent_Header_Paths.at(i),

         this->Independent_Header_New_Paths.at(i));        
     }
}


void Repo_Warehouse_Initializer::Determine_Header_File_Name_With_Extention(std::string path){

     size_t file_path_size = path.length();

     this->Clear_String_Memory(&this->Header_File_Name_With_Extention);


     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

          if(((path[i] == '/') || (path[i] == '\\'))){

             break;
          }
          else{

              dir_size--;
          }
     }

     for(size_t i=dir_size+1;i<file_path_size;i++){

        this->Header_File_Name_With_Extention.push_back(path[i]);
     }
}



void Repo_Warehouse_Initializer::Clear_Dynamic_Memory(){
  
     this->Clear_Vector_Memory(&this->Header_File_Paths);

     this->Clear_Vector_Memory(&this->Headers_New_Paths);

     this->Clear_String_Memory(&this->Headers_Directory);

     this->Clear_String_Memory(&this->Object_Files_Directory);

     this->Clear_String_Memory(&this->Library_Files_Directory);

     this->Clear_String_Memory(&this->warehouse_path);

     this->Clear_String_Memory(&this->warehouse_location);

     this->Clear_String_Memory(&this->current_directory);

     this->Des_Reader.Clear_Dynamic_Memory();
}


void Repo_Warehouse_Initializer::Clear_Vector_Memory(std::vector<std::string> * pointer)
{
     if(!pointer->empty()){

         std::vector<std::string>::iterator it;

         auto begin = pointer->begin();

         auto end   = pointer->end();

         for(auto it=begin;it<end;it++)
         {
             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
             }
         }

         pointer->clear();

         pointer->shrink_to_fit();
      }
}


void Repo_Warehouse_Initializer::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}
