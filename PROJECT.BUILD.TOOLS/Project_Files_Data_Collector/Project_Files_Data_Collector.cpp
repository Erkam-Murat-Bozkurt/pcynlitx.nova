
#include "Project_Files_Data_Collector.hpp"

Project_Files_Data_Collector::Project_Files_Data_Collector(){


}

Project_Files_Data_Collector::~Project_Files_Data_Collector(){

}

void Project_Files_Data_Collector::Determine_File_Exact_Path(char ** pointer,

     char * repo_dir, char * string_line, char operating_sis){

     size_t repo_dir_size = strlen(repo_dir);

     size_t string_size = strlen(string_line);

     size_t dir_size = repo_dir_size + string_size;

     int index = 0;

     *pointer = new char [5*dir_size];

     for(size_t i=0;i<repo_dir_size;i++){

         (*pointer)[index] = repo_dir[i];

         index++;

         if(operating_sis == 'w'){

            if((*pointer)[index] == '/'){

               (*pointer)[index] = '\\';
            }
          }
     }

     if(operating_sis == 'w'){

       if(repo_dir[repo_dir_size-1] != '\\'){

          (*pointer)[index] = '\\';

          index++;
       }
     }

     if(operating_sis == 'l'){

       if(repo_dir[repo_dir_size-1] != '/'){

          (*pointer)[index] = '/';
       }
     }

     for(size_t i=0;i<string_size;i++){

        (*pointer)[index] = string_line[i];

        if(string_line[i] == '/'){

           if(operating_sis == 'w'){

              (*pointer)[index] = '\\';
            }
        }

        index++;
     }

     (*pointer)[index] = '\0';
}


void Project_Files_Data_Collector::Extract_Upper_Directory_Path(char ** pointer,

     char * string_line, char operating_sis){

     size_t file_path_size = strlen(string_line);

     size_t dir_size = file_path_size;

     if(operating_sis == 'l'){

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

           if(operating_sis == 'w'){

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

     *pointer = new char [5*dir_size];

     for(size_t i=0;i<dir_size;i++){

         (*pointer)[i] = string_line[i];

         if(string_line[i] == '/'){

            if(operating_sis == 'w'){

               (*pointer)[i] = '\\';
             }
         }
     }

     (*pointer)[dir_size] = '\0';
}

void Project_Files_Data_Collector::Determine_File_Name(char ** pointer, char * string_line){

     size_t string_size = strlen(string_line);

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

     int index = 0;

     *pointer = new char [5*string_size];

     for(size_t i=dir_size+1;i<file_extention_start_point;i++){

          (*pointer)[index] = string_line[i];

           index++;
     }

     (*pointer)[index] = '\0';
}

void Project_Files_Data_Collector::Determine_Source_File_Name_With_Ext(char ** pointer,

     char * file_name){

     char source_file_ext [] = ".cpp";

     size_t file_name_size = strlen(file_name);

     int index = 0;

     *pointer = new char [5*file_name_size];

     for(size_t i=0;i<file_name_size;i++){

         (*pointer)[index] = file_name[i];

         index++;
     }

     size_t ext_size = strlen(source_file_ext);

     for(size_t i=0;i<ext_size;i++){

         (*pointer)[index] = source_file_ext[i];

         index++;
     }

    (*pointer)[index] = '\0';
}
