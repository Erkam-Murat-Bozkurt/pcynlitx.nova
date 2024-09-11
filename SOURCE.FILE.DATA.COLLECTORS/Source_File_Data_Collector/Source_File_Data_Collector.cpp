

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


#include "Source_File_Data_Collector.hpp"

Source_File_Data_Collector::Source_File_Data_Collector( char opr_sis) :

   FileManager(opr_sis), StringManager(opr_sis)
{
    this->operating_sis = opr_sis;
}


Source_File_Data_Collector::~Source_File_Data_Collector()
{
    this->Clear_Dynamic_Memory();

    this->Clear_String_Memory(&this->Git_Repo_Dir);
}



void Source_File_Data_Collector::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->Initialize_Members();
}

void Source_File_Data_Collector::Initialize_Members()
{
     this->File_Content_Size = 0;

     this->included_header_file_number = 0;

     this->git_record_size = this->Git_Data_Proc->Get_Git_File_Index_Size();

     std::string dir = this->Git_Data_Proc->Get_Git_Repo_Directory();

     for(size_t i=0;i<dir.length();i++)
     {
        this->Git_Repo_Dir.push_back(dir[i]);
     }
}

void Source_File_Data_Collector::Process_Source_File_Data(Build_System_Data * Ptr, std::string path)
{
     this->Data_Pointer = Ptr;

     this->Clear_Dynamic_Memory();

     for(size_t i=0;i<path.length();i++){

         this->FilePATH.push_back(path[i]);
     }

     this->Read_File(path);

     this->Determine_Include_Line_Number();

     this->Receive_Include_File_Names();

     this->Place_Data_To_Container();
}

void Source_File_Data_Collector::Place_Data_To_Container()
{
     this->Place_Source_File_Data();

     this->Place_Source_File_Headers_Data();

     this->Determine_Class_Header_File_Name();
}


void Source_File_Data_Collector::Read_File(std::string path)
{
     this->FileManager.Clear_Dynamic_Memory();

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(Rf);

     this->File_Content_Size = 0;

     do {
            std::string file_line = this->FileManager.ReadLine();

            this->Delete_Spaces_on_String(&file_line);

            this->File_Content.push_back(file_line);

            this->Clear_String_Memory(&file_line);

            this->File_Content_Size++;

     }while(!this->FileManager.Control_Stop_Condition());

     this->FileManager.FileClose();

     this->FileManager.Clear_Dynamic_Memory();
}



void Source_File_Data_Collector::Determine_Include_Line_Number()
{
     char include_db_key [] = "#include\"";  // double_quotation_mark

     this->included_header_file_number = 0;

     for(int i=0;i<this->File_Content_Size;i++){

         bool is_include_line_db

         = this->StringManager.CheckStringInclusion(this->File_Content[i],include_db_key);

         bool char_before_sharp = false; //  sharp symbol = #

         if(this->File_Content[i][0]!= '#'){

             char_before_sharp = true;
         }

         // In metaprograms, #include key is used on the inside code

         // Therefore, there may be false include therms which is used in the metaprograms

         // in order to produce header files. If there is a character before the sharp symbol,

         // it is a meta program code. ( simething like write{ #include \"sample.h\" })

         if(!char_before_sharp){

           if(is_include_line_db){

              this->included_header_file_number++;
           }
         }
     }
}

void Source_File_Data_Collector::Receive_Include_File_Names()
{
     char include_db_key []   = "#include\"";  // double_quotation_mark

     for(int i=0;i<this->File_Content_Size;i++){

         bool is_include_line_db

         = this->StringManager.CheckStringInclusion(this->File_Content[i],include_db_key);

         bool char_before_sharp = false;

         if(this->File_Content[i][0]!= '#'){

            char_before_sharp = true;
         }

         if(!char_before_sharp){ // In metaprograms, #include key is used on the inside code

             if(is_include_line_db){

                bool syntax_error_cond = this->Control_Include_Syntax(this->File_Content[i]);

                if(syntax_error_cond){

                   std::cout << "\n There is a syntax error on the header file declerations";
                   std::cout << "\n which is performed on the source file path:\n";

                   std::cout << "\n " << this->FilePATH;

                   std::cout << "\n\n";

                   exit(EXIT_FAILURE);
                }

                if(!syntax_error_cond){

                    // Determination of header file name

                    Include_File_Data Data;

                    this->Receive_Include_File_Name(&(Data.Include_File_Name),

                          this->File_Content[i]);

                    // Determination of the header file directory

                    this->Determine_Git_Record_Header_File_Path(&(Data.Include_File_Git_Record_Path),

                           Data.Include_File_Name);


                    this->Determine_Git_Record_Header_File_Directory(&(Data.Include_File_Git_Record_Dir),

                           Data.Include_File_Git_Record_Path);


                    this->Determine_Header_File_Directory(&(Data.Include_File_Directory),

                            Data.Include_File_Git_Record_Path);

                    Data.Include_File_Number++;

                    this->Head_Data.push_back(Data);

                    this->Clear_Include_File_Data(&Data);
                }
              }
          }
      }
}



void Source_File_Data_Collector::Place_Source_File_Data(){

     this->Determine_Git_Record_Source_File_Path(&this->Data_Pointer->git_record_path,this->FilePATH);

     this->Determine_Git_Record_Source_File_Directory(&this->Data_Pointer->git_record_dir,this->FilePATH);

     this->Data_Pointer->is_this_a_source_file = true;

     this->Data_Pointer->is_this_a_header_file = false;

     this->Determine_Source_File_System_Path(&this->Data_Pointer->File_Path,this->FilePATH);

     this->Extract_Upper_Directory_Path(&this->Data_Pointer->File_Directory,this->Data_Pointer->File_Path);

     this->Determine_File_Name(&this->Data_Pointer->File_Name,this->Data_Pointer->File_Path);

     this->Determine_Source_File_Name_With_Ext(&this->Data_Pointer->File_Name_With_Ext,this->Data_Pointer->File_Name);
}

void Source_File_Data_Collector::Place_Source_File_Headers_Data(){

     int Inc_Header_Number = this->Get_Included_File_Number();

     this->Data_Pointer->Included_Header_Files_Number = Inc_Header_Number;

     if(Inc_Header_Number > 0){

        for(int k=0;k<Inc_Header_Number;k++){

            this->Place_Headers_Data(k);
        }
     }
}

void Source_File_Data_Collector::Place_Headers_Data(int hdr_num)
{
     std::string Included_File =

     this->Get_Include_File_Name(hdr_num);

     std::string Included_File_Directory =

     this->Get_Include_File_Directory(hdr_num);

     std::string Include_File_Git_Record_Dir =

     this->Get_Include_File_Git_Record_Directory(hdr_num);

     std::string Include_File_Git_Record_Path =

     this->Get_Include_File_Git_Record_Path(hdr_num);

     this->Data_Pointer->Included_Header_Files.push_back(Included_File);

     this->Data_Pointer->Included_Header_Files_Directories.push_back(Included_File_Directory);

     this->Data_Pointer->Included_Header_Files_Git_Record_Dir.push_back(Include_File_Git_Record_Dir);

     this->Data_Pointer->Included_Header_Files_Git_Record_Path.push_back(Include_File_Git_Record_Path);

     if(this->operating_sis == 'w'){

        std::string path;

        std::string dir  = this->Data_Pointer->Included_Header_Files_Directories[0];

        std::string name = this->Data_Pointer->Included_Header_Files[0];

        this->Determine_Header_Files_System_Paths(&path,dir,name);

        this->Data_Pointer->Included_Header_Files_System_Path.push_back(path);
     }
}




void Source_File_Data_Collector::Determine_Git_Record_Header_File_Path(std::string * header_path,

     std::string header_name){

     for(int i=0;i<this->git_record_size;i++){

         std::string file_path = this->Git_Data_Proc->Get_Git_File_Index(i);

         std::string file_name;

         this->Extract_Include_File_Name_From_Path(&file_name,file_path);

         bool is_equal = this->CompareString(file_name,header_name);

         if(is_equal){

            size_t header_path_size = file_path.length();

            for(size_t k=0;k<header_path_size;k++){

              if(this->operating_sis == 'w'){

                 if(file_path[k] == '/'){

                    header_path->push_back('\\');
                 }
                 else{

                   header_path->push_back(file_path[k]);
                 }
              }
            }

            break;
         }
      }



      if(*header_path == ""){

        std::cerr << "\n\n";

        std::cerr << "\n The user defined header file decleration :" << header_name;

        std::cerr << "\n is not macth with the git records :";

        std::cerr << "\n please check header decleration on the path:";

        std::cerr << "\n ";

        std::cerr << this->FilePATH;

        std::cerr << "\n\n";

        exit(EXIT_FAILURE);
      }
}

void Source_File_Data_Collector::Determine_Git_Record_Header_File_Directory(std::string * header_dir,

     std::string header_path){

     size_t path_size = header_path.length();

     size_t dir_size = path_size;

     for(size_t i=path_size;i>0;i--){

        if(((header_path[i] == '/') || (header_path[i] == '\\')))
        {
           break;
        }
        else{

           dir_size--;
        }
    }

    for(size_t i=0;i<dir_size;i++){

        header_dir->push_back(header_path[i]);

       if(this->operating_sis == 'w'){

          if((*header_dir)[i] == '/'){

             (*header_dir)[i] = '\\';
          }
       }

       if(this->operating_sis == 'l'){

          if((*header_dir)[i] == '\\'){

             (*header_dir)[i] = '/';
          }
       }
    }
}

void Source_File_Data_Collector::Determine_Header_File_Directory(std::string * directory,

     std::string file_path){

     size_t header_path_size = file_path.length();

     size_t dir_size = header_path_size;

     size_t repo_dir_size = this->Git_Repo_Dir.length();

     for(size_t k=header_path_size;k>0;k--){

        if(((file_path[k] == '\\') || (file_path[k] == '/'))){

           break;
        }
        else{

            dir_size--;
        }
     }


     for(size_t k=0;k<repo_dir_size;k++){

         directory->push_back(this->Git_Repo_Dir[k]);
     }

     if(this->operating_sis == 'w'){

        if(this->Git_Repo_Dir[repo_dir_size-1] != '\\'){

          (*directory)[repo_dir_size-1] = '\\';
        }
     }

     if(this->operating_sis == 'l'){

        if(this->Git_Repo_Dir[repo_dir_size-1] != '\\'){

          (*directory)[repo_dir_size-1] = '/';
        }
     }

     for(size_t k=0;k<dir_size;k++){

         directory->push_back(file_path[k]);

        if(this->operating_sis == 'w'){

           if((*directory)[k]  == '/'){

             (*directory)[k] = '\\';
           }
        }
     }
}

void Source_File_Data_Collector::Determine_Class_Header_File_Name()
{
     int total_hdr_number    = this->Data_Pointer->Included_Header_Files_Number;

     std::string  file_name  = this->Data_Pointer->File_Name;

     for(int i=0;i<total_hdr_number;i++){

         std::string  hdr_name =

         this->Data_Pointer->Included_Header_Files[i];

         size_t hdr_name_size = hdr_name.length();

         std::string hdr_temp;

         for(size_t i=0;i<hdr_name_size;i++){

            if(hdr_name[i] == '.'){

               break;
            }
            else{

              hdr_temp.push_back(hdr_name[i]);
            }
         }

         bool is_equal = this->CompareString(file_name,hdr_temp);

         if(is_equal){

           std::string hdr_path = this->Data_Pointer->Included_Header_Files_System_Path[i];

           std::string header_name;

           this->Extract_Include_File_Name_From_Path(&header_name,hdr_path);

           this->Data_Pointer->class_header_file_name = header_name;

           this->Data_Pointer->class_header_file_path = hdr_path;

           header_name.clear();

           header_name.shrink_to_fit();

           break;
         }
     }
}


void Source_File_Data_Collector::Receive_Include_File_Name(std::string * pointer,

     std::string string ){

     size_t string_size = string.length();

     size_t start_point = 0, end_point =0;

     for(size_t i=0;i<string_size;i++){

        if(string[i] == '\"'){

            start_point = i+1;

            break;
        }
     }

     for(size_t i=start_point;i<string_size;i++){

        if(string[i] == '\"'){

           end_point = i;
        }
     }

     
     /* The following lines control directory character existanse on the 
     
        include file decleration 

        For istance "sample/sample.h"
     
     */

     for(size_t i=start_point;i<end_point;i++){

        if(((string[i] == '\\') || (string[i] == '/'))){

           start_point = i+1;
        }
     }

     
     int index = 0;

     for(size_t i=start_point;i<end_point;i++){

         pointer->push_back(string[i]) ;
     }
}

void Source_File_Data_Collector::Extract_Upper_Directory_Path(std::string * pointer,

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

         pointer->push_back(string_line[i]);

         if(string_line[i] == '/'){

            if(this->operating_sis == 'w'){

               (*pointer)[i] = '\\';
             }
         }
     }
}


void Source_File_Data_Collector::Determine_File_Name(std::string * pointer, std::string string_line){

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

         pointer->push_back(string_line[i]);
     }
}

void Source_File_Data_Collector::Extract_Include_File_Name_From_Path(std::string * pointer,

     std::string string ){

     size_t string_size = string.length();

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(((string[i] == '/') || (string[i] == '\\'))){

            start_point = i+1;

            break;
        }
     }

     for(size_t i=start_point;i<string_size;i++)
     {
         pointer->push_back(string[i]) ;
     }
}

void Source_File_Data_Collector::Determine_Git_Record_Source_File_Directory(std::string * record_dir,

     std::string git_record_system_path){

     size_t path_size = git_record_system_path.length();

     size_t dir_size = path_size;

     size_t end_point = 0;

     for(int i=path_size;i>0;i--){

         if(this->operating_sis =='w'){

           if(git_record_system_path[i] == '\\'){

             end_point = i;

             break;
           }
         }

         if(this->operating_sis =='l'){

           if(git_record_system_path[i] == '/'){

             end_point = i;

             break;
           }
         }
     }


     size_t repo_dir_size = this->Git_Repo_Dir.length();

     size_t start_point = repo_dir_size;

     char start_point_character = git_record_system_path[start_point];

     if(((start_point_character == '\\' )

         || (start_point_character== '/' ))){

         start_point++;
     }

     for(size_t i=start_point;i<end_point;i++){

         record_dir->push_back(git_record_system_path[i]) ;
     }

     record_dir->shrink_to_fit();
}


void Source_File_Data_Collector::Determine_Git_Record_Source_File_Path(std::string * source_file_path,

     std::string file_path){

     size_t path_size = file_path.length();

     for(size_t i=0;i<path_size;i++){

         source_file_path->push_back(file_path[i]) ;
     }

     source_file_path->shrink_to_fit();
}

void Source_File_Data_Collector::Determine_Source_File_System_Path(std::string * pointer,

    std::string path) {

     size_t path_size = path.length();

     for(size_t i=0;i<path_size;i++){

         pointer->push_back(path[i]);
     }

     pointer->shrink_to_fit();
}


void Source_File_Data_Collector::Determine_Header_Files_System_Paths(std::string * pointer,

     std::string directory, std::string file_name){

     size_t directory_size = directory.length();

     size_t file_name_size = file_name.length();


     for(size_t i=0;i<directory_size;i++){

         pointer->push_back(directory[i]);
     }

     if(this->operating_sis == 'w'){

       if((*pointer)[directory_size-1] != '\\'){

           pointer->push_back('\\');
       }
     }

     if(this->operating_sis == 'l'){

         if((*pointer)[directory_size-1] != '/'){

             pointer->push_back('/') ;
         }
     }

     for(size_t i=0;i<file_name_size;i++){

         pointer->push_back(file_name[i]);
     }
}

void Source_File_Data_Collector::Determine_Source_File_Name_With_Ext(std::string * pointer,

     std::string file_name){

     char source_file_ext [] = ".cpp";

     size_t file_name_size = file_name.length();

     for(size_t i=0;i<file_name_size;i++){

         pointer->push_back(file_name[i]);
     }

     size_t ext_size = strlen(source_file_ext);

     for(size_t i=0;i<ext_size;i++){

         pointer->push_back(source_file_ext[i]);
     }
}

void Source_File_Data_Collector::Delete_Spaces_on_String(std::string * str)
{
      size_t string_size = str->length();

      bool search_cond = true;

      do{

         search_cond = false;

         for(size_t i=0;i<str->length();i++)
         {
           if((*str)[i] == ' '){

             search_cond = true;

             str->erase(i,1);
           }
         }

      }while(search_cond);

      str->shrink_to_fit();
}


bool Source_File_Data_Collector::CompareString(std::string sr1, std::string sr2)
{
     return this->StringManager.CompareString(sr1,sr2);
}


bool Source_File_Data_Collector::Control_Include_Syntax(std::string string){

     size_t string_size = string.length();

     this->syntax_error = true;

     bool include_double_quotation_mark = this->Character_Inclusion_Check(string,'\"');

     bool include_start_cond = include_double_quotation_mark;

     if(!include_start_cond){

        this->syntax_error = true;

        return this->syntax_error;
     }

     int double_quotation_mark_number = 0;

     if(include_double_quotation_mark){

        for(size_t i=0;i<string_size;i++){

            if(string[i] == '\"'){

               double_quotation_mark_number++;
            }
        }

        if(double_quotation_mark_number>1){

           this->syntax_error = false;

           return this->syntax_error;
        }
        else{

            this->syntax_error = true;

            return this->syntax_error;
        }
     }

     return this->syntax_error;
}

bool Source_File_Data_Collector::Character_Inclusion_Check(std::string string, char chr){

     this->Character_Inclusion_Status = false;

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         if(string[i] == chr){

            this->Character_Inclusion_Status = true;

            break;
         }
     }

     return this->Character_Inclusion_Status;
}


void Source_File_Data_Collector::Clear_Dynamic_Memory(){

     std::vector<Include_File_Data>::iterator it;

     auto begin = this->Head_Data.begin();
     auto end   = this->Head_Data.end();

     for(auto it=begin;it<end;it++){

         Include_File_Data * ptr = &(*it);

         this->Clear_Include_File_Data(ptr);
     }

     if(!this->Head_Data.empty()){

         this->Head_Data.clear();
         this->Head_Data.shrink_to_fit();
     }

     this->Clear_Vector_Memory(&this->File_Content);
     this->Clear_String_Memory(&this->FilePATH);

     this->FileManager.Clear_Dynamic_Memory();

     this->StringManager.Clear_Dynamic_Memory();
}

void Source_File_Data_Collector::Clear_Include_File_Data(Include_File_Data * pointer){

      this->Clear_String_Memory(&pointer->Include_File_Name);
      this->Clear_String_Memory(&pointer->Include_File_Directory);
      this->Clear_String_Memory(&pointer->Include_File_Git_Record_Path);
      this->Clear_String_Memory(&pointer->Include_File_Git_Record_Dir);
}


void Source_File_Data_Collector::Clear_Vector_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();
            it->shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void Source_File_Data_Collector::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();
         pointer->shrink_to_fit();
     }
}


Build_System_Data * Source_File_Data_Collector::Get_Data_Pointer(){

    return this->Data_Pointer;
}

int Source_File_Data_Collector::Get_Included_File_Number(){

    return this->included_header_file_number;
}

std::string Source_File_Data_Collector::Get_Include_File_Name(int num){

       return this->Head_Data[num].Include_File_Name;
}

std::string Source_File_Data_Collector::Get_Include_File_Directory(int num){

       return this->Head_Data[num].Include_File_Directory;
}

std::string Source_File_Data_Collector::Get_Include_File_Git_Record_Directory(int num){

       return this->Head_Data[num].Include_File_Git_Record_Dir;
}

std::string Source_File_Data_Collector::Get_Include_File_Git_Record_Path(int num){

       return this->Head_Data[num].Include_File_Git_Record_Path;
}
