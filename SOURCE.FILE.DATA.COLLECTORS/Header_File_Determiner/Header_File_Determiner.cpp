/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Header_File_Determiner.h"

Header_File_Determiner::Header_File_Determiner(char opr_sis) :

   StringManager(opr_sis)
{

    this->include_decleration_cond = false;

    this->Memory_Delete_Condition = false;

    this->is_header_file = false;

    this->operating_sis = opr_sis;
}


Header_File_Determiner::~Header_File_Determiner(){

     this->Clear_Object_Memory();  
}

void Header_File_Determiner::Clear_Object_Memory(){

     this->Clear_String_Memory(&this->Repo_Dir);

     this->Clear_Dynamic_Memory();
}

void Header_File_Determiner::Clear_Dynamic_Memory(){

     this->Clear_String_Memory(&this->Header_File_Directory);
     this->Clear_String_Memory(&this->Header_File_Name);
     this->Clear_String_Memory(&this->Header_File_Name_With_Extention);
     this->Clear_String_Memory(&this->Header_File_System_Path);

     this->StringManager.Clear_Dynamic_Memory();
}


void Header_File_Determiner::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->git_record_size = this->Git_Data_Proc->Get_Git_File_Index_Size();

     this->Repo_Dir  = this->Git_Data_Proc->Get_Git_Repo_Directory();
}




bool Header_File_Determiner::Include_Decleration_Test(std::string string){

     this->include_decleration_cond = false;

     char include_key_1 [] = "#include\"";  // double_quotation_mark
     char include_key_2 [] = "#include<";  // left bracked


     bool is_this_include_dec_1

     = this->StringManager.CheckStringInclusion(string,include_key_1);



     bool is_this_include_dec_2

     = this->StringManager.CheckStringInclusion(string,include_key_2);


     bool char_before_sharp = false; //  sharp symbol = #

     if(string[0]!= '#'){

        char_before_sharp = true;
     }

     // In metaprograms, #include key is used on the inside code

     // Therefore, there may be false include therms which is used in the metaprograms

     // in order to produce header files. If there is a character before the sharp symbol,

     // it is a meta program code. ( simething like write{ #include \"sample.h\" })

     if(!char_before_sharp){

        if(is_this_include_dec_1 || is_this_include_dec_2){

           this->include_decleration_cond = true;
        }
     }

     return this->include_decleration_cond;
}

void Header_File_Determiner::Extract_Header_File_Name_From_Decleration(std::string * header_name,

     std::string string)
{

     size_t size = string.length();

     int start_point = 0;

     for(size_t k=0;k<size;k++){

         if(string[k] == '\"'){

            break;
         }
         else{

            start_point++;
         }


         if(string[k] == '<'){

            break;
         }
         else{

            start_point++;
         }
     }

     start_point = start_point + 1;

     int end_point = start_point;

     for(size_t k=start_point;k<size;k++){

        if(string[k] == '\"'){

           break;
        }
        else{

             end_point++;
        }



        if(string[k] == '>'){

            break;
        }
        else{

            end_point++;
        }
     }

     for(int i=start_point;i<end_point;i++){

          header_name->push_back(string[i]);
     }
}

 bool Header_File_Determiner::Is_This_Repo_Header(std::string file_path){
 

      this->is_this_repo_header = false;

      this->Determine_Header_File_Name_With_Extention(file_path);
   
      std::string file_name_wit_ext =this->Get_Header_File_Name_With_Ext();
 
      if(this->Is_Header(file_path)){
      
         int size = this->Git_Data_Proc->Get_Git_File_Index_Size();

         for(int i=0;i<size;i++){
         
             std::string repo_file_system_path = this->Git_Data_Proc->Get_File_System_Path(i);

             this->Determine_Header_File_Name_With_Extention(repo_file_system_path);

             std::string repo_file_name_with_ext = this->Get_Header_File_Name_With_Ext();

             bool is_equal = this->CompareString(repo_file_name_with_ext,file_name_wit_ext);

             if(is_equal){
             
                this->is_this_repo_header = true;

                return this->is_this_repo_header;
             }
         }      
      }

      return this->is_this_repo_header; 
 }




bool Header_File_Determiner::Is_Header(std::string file_path){

     std::string inclusion_guard  = "#ifndef";

     std::string header_add_h = ".h";

     std::string header_add_hpp  = ".hpp";

     std::string source_file_ext_cpp  = ".cpp";

     std::string source_file_ext_cc  = ".cc";


     std::string file_extention;

     bool is_there_file_ext = false;

     this->Extract_File_Extention(file_extention,file_path,is_there_file_ext);

     if(!is_there_file_ext){

         this->is_header_file = false;

         return this->is_header_file;
     }


     this->is_header_file = false;

     if(this->StringManager.CompareString(file_extention,source_file_ext_cpp)){

        this->is_header_file = false;

        return this->is_header_file;
     }


     if(this->StringManager.CompareString(file_extention,source_file_ext_cc)){

        this->is_header_file = false;

        return this->is_header_file;
     }


     bool include_header_ext = this->StringManager.CompareString(file_extention,header_add_h);

     if(include_header_ext){

        this->is_header_file = true;

        return this->is_header_file;
     }
     else{

          include_header_ext = this->StringManager.CompareString(file_extention,header_add_hpp);

          if(include_header_ext){
        
             this->is_header_file = true;

            return this->is_header_file;
          }
    }


    return this->is_header_file;
}


bool Header_File_Determiner::Is_Config_File(std::string file_path){

     
     bool is_config_file = false;

     std::string auto_conf_file_add = ".in";


     std::string file_extention;

     bool is_there_file_ext = false;

     this->Extract_File_Extention(file_extention,file_path,is_there_file_ext);

     if(!is_there_file_ext){

         return is_config_file;
     }

     
     bool include_header_ext = this->StringManager.CompareString(file_extention,auto_conf_file_add);

     if(include_header_ext){

        is_config_file = true;

        return is_config_file;
     }

     return is_config_file;
}


void Header_File_Determiner::Extract_File_Extention(std::string & ext, std::string file_path, 

     bool & is_there_ext){

     size_t name_size   = file_path.length();
     size_t start_point = 0;

     is_there_ext = false;
     
     for(size_t i=name_size;i>0;i--){

         if(file_path[i] == '.'){

            is_there_ext = true;

            start_point=i;

            break;
         }
     }

     for(size_t i=start_point;i<name_size;i++){

         ext.push_back(file_path[i]);
     }

     ext.shrink_to_fit();     
}

void Header_File_Determiner::Determine_Header_File_Directory(std::string path){

     this->Clear_String_Memory(&this->Header_File_Directory);

     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

        if(((path[i] == '/') || (path[i] == '\\'))){

           break;
        }
        else{

            dir_size--;
        }
     }

     for(size_t i=0;i<dir_size;i++){

         this->Header_File_Directory.append(1,path[i]);
     }
}

void Header_File_Determiner::Determine_Header_File_Name(std::string path){

     this->Clear_String_Memory(&this->Header_File_Name);


     size_t file_path_size = path.length();

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

          if( path[i] == '.'){

              break;
          }

          this->Header_File_Name.append(1,path[i]);
      }
}


void Header_File_Determiner::Determine_Header_File_Name_With_Extention(std::string path){

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

        this->Header_File_Name_With_Extention.append(1,path[i]);
     }
}

void Header_File_Determiner::Determine_Header_File_System_Path(std::string repo_dir,

     std::string git_record_path){

     this->Clear_String_Memory(&this->Header_File_System_Path);


     size_t repo_dir_size   = repo_dir.length();

     size_t git_record_size = git_record_path.length();

     size_t path_size = repo_dir_size + git_record_size;


     for(size_t i=0;i<repo_dir_size;i++){

         this->Header_File_System_Path.append(1,repo_dir[i]);

         if(this->operating_sis == 'w'){

            if(this->Header_File_System_Path[i] == '/'){

               this->Header_File_System_Path[i] = '\\' ;
            }
         }
     }

     if(this->operating_sis == 'w'){

        if(repo_dir[repo_dir_size] != '\\' ){

          this->Header_File_System_Path.append(1,'\\');
        }
     }

     if(this->operating_sis == 'l'){

       if(repo_dir[repo_dir_size] != '/' ){

         this->Header_File_System_Path.append(1,'/');
       }
     }

     for(size_t i=0;i<git_record_size;i++){

        if((git_record_path[i] == '/') || (git_record_path[i] == '\\')){

           if(this->operating_sis == 'w'){

              if(git_record_path[i] == '/'){

                this->Header_File_System_Path.append(1,'\\');
              }
           }
           else{

                 if(this->operating_sis == 'l'){

                  if(git_record_path[i] == '\\'){

                     this->Header_File_System_Path.append(1,'/');
                  }
             }
           }
        }
        else{

            this->Header_File_System_Path.append(1,git_record_path[i]);

        }
     }
}


void Header_File_Determiner::Determine_Git_Record_File_System_Path(std::string * sys_path,

     std::string file_path){

     size_t repo_dir_size = this->Repo_Dir.length();

     size_t path_size = file_path.length();

     size_t sys_path_size = repo_dir_size + path_size;

     int index=0;

     for(size_t i=0;i<repo_dir_size;i++){

        (*sys_path).append(1,this->Repo_Dir[i]);

        if(this->operating_sis =='w'){

          if((*sys_path)[i] == '/'){

             (*sys_path)[i] = '\\';
          }
       }
     }

     if(this->operating_sis =='w'){

        (*sys_path).append(1,'\\');
     }
     else{

        (*sys_path).append(1,'/');
     }


     for(size_t i=0;i<path_size;i++){

        (*sys_path).append(1,file_path[i]);

        if(operating_sis =='w'){

           if((*sys_path)[i] == '/'){

              (*sys_path)[i] = '\\';
           }
        }
     }
}


bool Header_File_Determiner::CompareString(std::string firstString, std::string secondString){

     int firstStringLength  = firstString.length();

     int secondStringLength = secondString.length();

     this->isStringsEqual = false;

     if(firstStringLength==secondStringLength){

        for(int i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

          this->isStringsEqual = false;

          return this->isStringsEqual;
     }
}

void Header_File_Determiner::Delete_Spaces_on_String(std::string * str){

    size_t string_size = str->length();

    bool search_cond = true;

    do{

      search_cond = false;

      for(size_t i=0;i<str->length();i++){

          if((*str)[i] == ' '){

            search_cond = true;

            str->erase(i,1);
          }
        }

    }while(search_cond);
}


void Header_File_Determiner::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

        pointer->clear();

        pointer->shrink_to_fit();
     }
}

std::string Header_File_Determiner::Get_Header_Directory(){

       return this->Header_File_Directory;
}

std::string Header_File_Determiner::Get_Header_File_Name_Without_Ext(){

       return this->Header_File_Name;
}

std::string Header_File_Determiner::Get_Header_File_Name_With_Ext(){

       return this->Header_File_Name_With_Extention;
}

std::string Header_File_Determiner::Get_Header_File_System_Path(){

      return this->Header_File_System_Path;
}
