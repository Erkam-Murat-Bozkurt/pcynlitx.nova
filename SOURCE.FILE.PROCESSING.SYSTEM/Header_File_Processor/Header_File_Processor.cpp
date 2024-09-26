

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Header_File_Processor.hpp"

Header_File_Processor::Header_File_Processor()
{
    this->include_decleration_cond = false;

    this->Memory_Delete_Condition = false;

    this->is_header_file = false;
}


Header_File_Processor::~Header_File_Processor(){

     this->Clear_Object_Memory();  
}

void Header_File_Processor::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void Header_File_Processor::Clear_Dynamic_Memory(){

     this->Clear_String_Memory(&this->Header_File_Directory);
     this->Clear_String_Memory(&this->Header_File_Name);
     this->Clear_String_Memory(&this->Header_File_Name_With_Extention);
     this->Clear_String_Memory(&this->Header_File_System_Path);

     this->StringManager.Clear_Dynamic_Memory();
}


void Header_File_Processor::Receive_Operating_System(char opr_sis){

     this->operating_sis = opr_sis;
}



void Header_File_Processor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


bool Header_File_Processor::Is_this_file_included_on_anywhere(std::string file_path){

     size_t repo_size = this->Code_Rdr->Get_Project_Files_Number();

     this->Is_this_file_included_on_somewhere = false;

     for(int i=0;i<repo_size;i++){

         const std::vector<std::string> * Include_Declerations = this->Code_Rdr->Get_Include_Declerations(i);

         this->Header_File_System_Path = this->Code_Rdr->Get_File_Path(i);
         
         size_t FileSize = Include_Declerations->size();

         for(size_t k=0;k<FileSize;k++){

             std::string file_line = Include_Declerations->at(k);

             // In order to remove possible spaces on the string

             // a temporary string is constructed
             
             std::string header_name;


             this->Extract_Header_File_Name_From_Decleration(&header_name,file_line);

             this->Determine_Header_File_Name(file_path);

             bool is_strings_equal = this->CompareString(header_name,this->Header_File_Name);

             if(is_strings_equal){

                this->Is_this_file_included_on_somewhere = true;

                break;
             }             
         }
      }

      return this->Is_this_file_included_on_somewhere;
}


bool Header_File_Processor::Include_Decleration_Test(std::string string){

     this->include_decleration_cond = false;

     char include_key_1 [] = "#include\"";  // double_quotation_mark

     char include_key_2 [] = "#include<";  // double_quotation_mark


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



void Header_File_Processor::Extract_Header_File_Name_From_Decleration(std::string * header_name,

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



bool Header_File_Processor::Is_Header(std::string file_path){

     std::string inclusion_guard  = "#ifndef";

     std::string header_add_h = ".h";

     std::string header_add_hpp  = ".hpp";

     std::string source_file_ext_cpp  = ".cpp";

     std::string source_file_ext_cc  = ".cc";

     std::string config_file = ".in";


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
          else{

               include_header_ext = this->StringManager.CompareString(file_extention,config_file);

               if(include_header_ext){
        
                  this->is_header_file = true;

                 return this->is_header_file;
               }
          }
    }

    return this->is_header_file;

}




void Header_File_Processor::Extract_File_Extention(std::string & ext, std::string file_path, 

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




void Header_File_Processor::Determine_Header_File_Directory(std::string path){

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

void Header_File_Processor::Determine_Header_File_Name(std::string path){

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


void Header_File_Processor::Determine_Header_File_Name_With_Extention(std::string path){

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



bool Header_File_Processor::CompareString(std::string firstString, std::string secondString){

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

void Header_File_Processor::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

        pointer->clear();

        pointer->shrink_to_fit();
     }
}

std::string Header_File_Processor::Get_Header_Directory(){

       return this->Header_File_Directory;
}

std::string Header_File_Processor::Get_Header_File_Name_Without_Ext(){

       return this->Header_File_Name;
}

std::string Header_File_Processor::Get_Header_File_Name_With_Ext(){

       return this->Header_File_Name_With_Extention;
}

std::string Header_File_Processor::Get_Header_File_System_Path(){

      return this->Header_File_System_Path;
}
