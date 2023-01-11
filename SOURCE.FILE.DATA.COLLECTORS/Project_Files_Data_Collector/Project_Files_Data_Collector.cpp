


#include "Project_Files_Data_Collector.hpp"

Project_Files_Data_Collector::Project_Files_Data_Collector(char opr_sis){

    this->operating_sis = opr_sis;
}

Project_Files_Data_Collector::~Project_Files_Data_Collector(){

}

void Project_Files_Data_Collector::Determine_File_Exact_Path(std::string * pointer,

     std::string repo_dir, std::string string_line){

     size_t repo_dir_size = repo_dir.length();

     size_t string_size = string_line.length();

     for(size_t i=0;i<repo_dir_size;i++){

         (*pointer).append(1,repo_dir[i]);

         if(this->operating_sis == 'w'){

            if((*pointer)[i] == '/'){

               (*pointer)[i] = '\\';
            }
          }
     }

     if(this->operating_sis == 'w'){

       if(repo_dir[repo_dir_size-1] != '\\'){

          (*pointer).append(1,'\\');
       }
     }

     if(this->operating_sis == 'l'){

       if(repo_dir[repo_dir_size-1] != '/'){

          (*pointer).append(1,'/');
       }
     }

     for(size_t i=0;i<string_size;i++){

         if(string_line[i] == '/'){

            if(this->operating_sis == 'w'){

              (*pointer).append(1,'\\');
            }
         }
         else{

           (*pointer).append(1,string_line[i]);

         }
     }
}


void Project_Files_Data_Collector::Extract_Upper_Directory_Path(std::string * pointer,

     std::string string_line){

     size_t file_path_size = string_line.length();

     size_t dir_size = file_path_size;

     if(this->operating_sis == 'l'){

        for(size_t i=file_path_size;i>0;i--){

            if(string_line[i] == '/'){

               break;
            }
            else{

               dir_size--;
            }
        }
     }
     else{

           if(this->operating_sis == 'w'){

             for(size_t i=file_path_size;i>0;i--){

                 if(string_line[i] == '\\'){

                    break;
                 }
                 else{

                     dir_size--;
                 }
             }
          }
     }

     for(size_t i=0;i<dir_size;i++){

         (*pointer).append(1,string_line[i]);

         if(string_line[i] == '/'){

            if(this->operating_sis == 'w'){

               (*pointer)[i] = '\\';
             }
         }
     }
}

void Project_Files_Data_Collector::Determine_File_Name(std::string * pointer, std::string string_line){

     size_t string_size = string_line.length();

     size_t dir_size = string_size;

     size_t file_extention_start_point = string_size;

     for(size_t i=string_size;i>0;i--){

         if((string_line[i] == '\\') || (string_line[i] == '/')){

            break;
         }
         else{

              dir_size--;
         }
     }

     for(size_t i=string_size;i>0;i--){

         if((string_line[i] == '.')){

            break;
         }
         else{

              file_extention_start_point--;
         }
     }

     for(size_t i=dir_size+1;i<file_extention_start_point;i++){

          (*pointer).append(1,string_line[i]);
     }
}


void Project_Files_Data_Collector::Determine_File_Name_With_Ext(std::string * pointer,

     std::string string_line){

     size_t string_size = string_line.length();

     size_t dir_size = string_size;

     size_t file_extention_start_point = string_size;

     for(size_t i=string_size;i>0;i--){

         if((string_line[i] == '\\') || (string_line[i] == '/'))
         {
            break;
         }
         else{

              dir_size--;
         }
     }

     for(size_t i=dir_size+1;i<string_size;i++){

          (*pointer).append(1,string_line[i]);
     }
}


void Project_Files_Data_Collector::Determine_Source_File_Name_With_Ext(std::string * pointer,

     std::string file_name){

     char source_file_ext [] = ".cpp";

     size_t file_name_size = file_name.length();


     for(size_t i=0;i<file_name_size;i++){

         (*pointer).append(1,file_name[i]);
     }

     size_t ext_size = strlen(source_file_ext);

     for(size_t i=0;i<ext_size;i++){

         (*pointer).append(1,source_file_ext[i]);
     }
}
