



#include "Git_Modification_Receiver.hpp"

Git_Modification_Receiver::Git_Modification_Receiver(char * DesPath, char opr_sis): 

  Des_Reader(DesPath), Header_Determiner(DesPath,opr_sis)

{
     this->Des_Reader.Read_Descriptor_File();
     
     this->warehouse_location = this->Des_Reader.Get_Warehouse_Location();

     this->Repo_Dir  = this->Des_Reader.Get_Repo_Directory_Location();

     this->opr_sis = opr_sis;
}



Git_Modification_Receiver::~Git_Modification_Receiver(){

     this->Clear_Dynamic_Memory();
}



void Git_Modification_Receiver::Receive_Git_Modifications()
{
     this->Determine_Warehouse_Path();

     this->Determine_Header_Files_Directory();

     this->Determine_Object_Files_Directory();

     this->Determine_Library_Files_Directory();

     this->Determine_Git_Modification_File_Path();

     this->Read_Modification_File();

     this->Determine_File_System_Paths();

     this->Determine_Updated_Header_Files();

     this->Determine_Updated_Source_Files();
}


void Git_Modification_Receiver::Determine_Warehouse_Path(){

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

void Git_Modification_Receiver::Determine_Header_Files_Directory(){

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



void Git_Modification_Receiver::Determine_Object_Files_Directory(){

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



void Git_Modification_Receiver::Determine_Library_Files_Directory(){

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



void Git_Modification_Receiver::Determine_Git_Modification_File_Path()
{
     std::string file_name  = "modified_files.txt";

     size_t file_name_size = file_name.length();

     size_t warehouse_path_size = this->warehouse_path.length();
      
     for(size_t i=0;i<warehouse_path_size;i++){

         this->modification_file_path.push_back(this->warehouse_path[i]) ;
     }

     if(this->warehouse_path[warehouse_path_size-1] != '\\'){

        this->modification_file_path.push_back('\\') ;
     }

     for(size_t i=0;i<file_name_size;i++){

        this->modification_file_path.push_back(file_name[i]) ;
     }
}





void Git_Modification_Receiver::Read_Modification_File()
{
     this->Memory_Delete_Condition = false;

     this->File_Line_Number = 0;

     this->FileManager.SetFilePath(this->modification_file_path);

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          std::string str = this->FileManager.ReadLine();

          this->Delete_Spaces_on_String(str);

          if(this->CheckStringLine(str)){
          
             this->File_Content.push_back(str);

             this->File_Line_Number++;
          }

          str.clear();

          str.shrink_to_fit();

     }while(!this->FileManager.Control_Stop_Condition());

     this->File_Content.shrink_to_fit();

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();


     if(this->opr_sis = 'w'){

        this->Convert_Windows_Paths();
     }
}



void Git_Modification_Receiver::Determine_File_System_Paths(){

     size_t list_size = this->File_Content.size();    

     for(size_t i=0;i<list_size;i++){

         std::string sys_path;

         this->Convert_to_System_path(sys_path,this->File_Content[i]);

         this->File_System_Paths.push_back(sys_path);

         sys_path.clear();

         sys_path.shrink_to_fit();
     }

     this->File_System_Paths.shrink_to_fit();
}




void Git_Modification_Receiver::Determine_Updated_Header_Files()
{
     size_t list_size = this->File_Content.size();

     for(size_t i=0;i<list_size;i++){

         bool is_header = this->Header_Determiner.Is_Header(this->File_Content.at(i));

         if(is_header){
         
            std::string sys_path;

            this->Convert_to_System_path(sys_path,this->File_Content.at(i));

            this->Updated_Header_Files.push_back(sys_path);

            sys_path.clear();

            sys_path.shrink_to_fit();
         }
     }

     this->Updated_Header_Files.shrink_to_fit();
}




void Git_Modification_Receiver::Determine_Updated_Source_Files()
{
     size_t list_size = this->File_Content.size();

     for(size_t i=0;i<list_size;i++){

         bool is_source = this->Src_Determiner.Is_Source_File(this->File_System_Paths.at(i));

         if(is_source){
         
            this->Updated_Source_Files.push_back(this->File_System_Paths.at(i));
         }
     }

     this->Updated_Source_Files.shrink_to_fit();
}


void Git_Modification_Receiver::Convert_to_System_path(std::string & sys_path, std::string path){

     sys_path+=this->Repo_Dir;

     if(this->opr_sis == 'w'){

        if(path.back()!= '\\'){

           sys_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(path.back() != '/'){

           sys_path.push_back('/');
        }
     }

     sys_path+=path;
}


void Git_Modification_Receiver::Convert_Windows_Paths(){

     size_t list_size = this->File_Content.size();

     for(size_t i=0;i<list_size;i++){

         size_t path_size = this->File_Content[i].size();

         for(size_t k=0;k<path_size;k++){

             if(this->File_Content[i][k] == '/'){

                this->File_Content[i][k] = '\\';
             }
         }
     }
}



void Git_Modification_Receiver::Delete_Spaces_on_String(std::string & str){

    size_t string_size = str.length();

    bool search_cond = true;

    do{

      search_cond = false;

      for(size_t i=0;i<str.length();i++){

          if(str[i] == ' '){

            search_cond = true;

            str.erase(i,1);
          }
      }

    }while(search_cond);
}


bool Git_Modification_Receiver::CheckStringLine(std::string readedline){

     this->isStringLine = false;

     bool isNewLine = false , isNull = false;

     if(readedline[0] == '\n'){

        isNewLine = true;
     }

     if(readedline[0] == '\0'){

        isNull = true;
     }

     if((!isNewLine) && (!isNull)){

          this->isStringLine = true;
     }

     return this->isStringLine;
}




void Git_Modification_Receiver::Clear_Dynamic_Memory(){
  
     this->Clear_String_Memory(&this->Headers_Directory);

     this->Clear_String_Memory(&this->Object_Files_Directory);

     this->Clear_String_Memory(&this->Library_Files_Directory);

     this->Clear_String_Memory(&this->warehouse_path);

     this->Clear_String_Memory(&this->warehouse_location);

     this->Clear_Vector_Memory(&this->File_Content);

     this->Clear_Vector_Memory(&this->File_System_Paths);

     this->Clear_Vector_Memory(&this->Updated_Header_Files);

     this->Clear_Vector_Memory(&this->Updated_Source_Files);

     this->Des_Reader.Clear_Dynamic_Memory();
}


void Git_Modification_Receiver::Clear_Vector_Memory(std::vector<std::string> * pointer)
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


void Git_Modification_Receiver::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}


std::vector<std::string> * Git_Modification_Receiver::Get_File_System_Path_Address()  
{
     return &this->File_System_Paths;
    
}

std::vector<std::string> * Git_Modification_Receiver::Get_Updated_Header_Files()  
{
     return &this->Updated_Header_Files;
    
}

std::vector<std::string> * Git_Modification_Receiver::Get_Updated_Source_Files()  
{
     return &this->Updated_Source_Files;
}