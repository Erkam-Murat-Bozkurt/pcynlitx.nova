
#include "Header_File_Determiner.h"

Header_File_Determiner::Header_File_Determiner(){

    this->is_header_file = false;

    this->Header_File_Directory = nullptr;

    this->Header_File_Name = nullptr;

    this->Header_File_System_Path = nullptr;

    this->Git_Receiver_Pointer = nullptr;

    this->File_Content_Size = 0;

    this->include_decleration_cond = false;

    this->Repo_Dir = nullptr;

    this->Header_File_Name_With_Extention = nullptr;

    this->Memory_Delete_Condition = true;
}

Header_File_Determiner::Header_File_Determiner(const Header_File_Determiner & orig){


}

Header_File_Determiner::~Header_File_Determiner(){

  if(!this->Memory_Delete_Condition){

     this->Clear_Dynamic_Memory();
  }
}

void Header_File_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Pointer_Memory(&this->Header_File_Directory);

        this->Clear_Pointer_Memory(&this->Header_File_Name);

        this->Clear_Pointer_Memory(&this->Header_File_System_Path);
     }
}

void Header_File_Determiner::Receive_Git_Data(Git_File_List_Receiver * pointer){

     this->Git_Receiver_Pointer = pointer;

     this->git_record_size = this->Git_Receiver_Pointer->Get_Git_File_Index_Size();

     this->Repo_Dir = this->Git_Receiver_Pointer->Get_Git_Repo_Directory();
}

bool Header_File_Determiner::Is_this_file_included_on_anywhere(char * file_path){

     this->Is_this_file_included_on_somewhere = false;

     for(int i=0;i<this->git_record_size-1;i++){

         char * git_record_path = this->Git_Receiver_Pointer->Get_Git_File_Index(i);

         char * record_sys_path = nullptr;

         this->Determine_Git_Record_File_System_Path(git_record_path,&record_sys_path,'w');

         bool is_path_exist = this->FileManager.Is_Path_Exist(record_sys_path);

         this->FileManager.SetFilePath(record_sys_path);

         bool is_file_openned = this->FileManager.TryOpen('r');

         bool file_exist = false;

         if(is_path_exist && is_file_openned){

            file_exist = true;
         }

         this->FileManager.Clear_Dynamic_Memory();

         if(file_exist){

            this->FileManager.Read_File_as_CString(record_sys_path);

            int FileSize = this->FileManager.GetFileSize();

            for(int k=0;k<FileSize;k++){

                char * string = this->FileManager.GetFileLine(k);

                // In order to remove possible spaces on the string

                // a temporary string is constructed

                char * tmp_string = nullptr;

                this->Construct_Temporary_String(&tmp_string,string);

                this->Delete_Spaces_on_String(&tmp_string);

                bool is_include_decleration = this->Include_Decleration_Test(tmp_string);


                char * header_name = nullptr;

                if(is_include_decleration){

                   this->Extract_Header_File_Name_From_Decleration(&header_name,tmp_string);

                   this->Determine_Header_File_Name(file_path);

                   bool is_strings_equal = this->CompareString(header_name,this->Header_File_Name);

                   if(is_strings_equal){

                      this->Is_this_file_included_on_somewhere = true;

                      break;
                    }
                }

                this->Clear_Pointer_Memory(&header_name);

                this->Clear_Pointer_Memory(&tmp_string);
            }
         }
         else{

                std::cout << "\n the git repo file " << record_sys_path <<

                 "\n can not find on the repo directory !..";
         }

         this->Clear_Pointer_Memory(&record_sys_path);

      }

      return this->Is_this_file_included_on_somewhere;
}

bool Header_File_Determiner::Include_Decleration_Test(char * string){

     this->include_decleration_cond = false;

     char include_key [] = "#include\"";  // double_quotation_mark

     bool is_this_include_dec

     = this->StringManager.CheckStringInclusion(string,include_key);

     bool char_before_sharp = false; //  sharp symbol = #

     if(string[0]!= '#'){

        char_before_sharp = true;
     }

     // In metaprograms, #include key is used on the inside code

     // Therefore, there may be false include therms which is used in the metaprograms

     // in order to produce header files. If there is a character before the sharp symbol,

     // it is a meta program code. ( simething like write{ #include \"sample.h\" })

     if(!char_before_sharp){

        if(is_this_include_dec){

           this->include_decleration_cond = true;
        }
     }

     return this->include_decleration_cond;
}

void Header_File_Determiner::Extract_Header_File_Name_From_Decleration(char ** header_name, char * string){

     size_t size = strlen(string);

     int start_point = 0;

     for(size_t k=0;k<size;k++){

         if(string[k] == '\"'){

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
     }

     int Name_Size = end_point - start_point;

     *header_name = new char [5*Name_Size];

     int index_counter = 0;

     for(int i=start_point;i<end_point;i++){

          (*header_name)[index_counter] = string[i];

          index_counter++;
     }

     (*header_name)[index_counter] = '\0';
}


bool Header_File_Determiner::Is_Header(char * file_path){

     char inclusion_guard [] = "#ifndef";

     char header_add_h [] = ".h";

     char header_add_hpp [] = ".hpp";

     char source_file_ext [] = ".cpp";

     this->is_header_file = false;

     if(this->StringManager.CheckStringInclusion(file_path,source_file_ext)){

        return this->is_header_file;
     }

     this->is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_h);

     if(this->is_header_file){

        return this->is_header_file;
     }
     else{

          this->is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_hpp);

          if(this->is_header_file){

              return this->is_header_file;
          }
    }

    if(this->Is_this_file_included_on_anywhere(file_path)){

      this->is_header_file = true;
    }

    return this->is_header_file;
}

void Header_File_Determiner::Determine_Header_File_Directory(char * path){

     this->Clear_Pointer_Memory(&this->Header_File_Directory);

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

        if(((path[i] == '/') || (path[i] == '\\'))){

           break;
        }
        else{

            dir_size--;
        }
     }

     this->Memory_Delete_Condition = false;

     this->Header_File_Directory = new char [5*dir_size];

     for(size_t i=0;i<dir_size;i++){

         this->Header_File_Directory[i] = path[i];
     }

     this->Header_File_Directory[dir_size] = '\0';
}

void Header_File_Determiner::Determine_Header_File_Name(char * path){

     this->Clear_Pointer_Memory(&this->Header_File_Name);

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

          if(((path[i] == '/') || (path[i] == '\\'))){

             break;
          }
          else{

              dir_size--;
          }
      }

      size_t Header_File_Name_Size = file_path_size - dir_size;

      this->Memory_Delete_Condition = false;

      this->Header_File_Name = new char [5*Header_File_Name_Size];

      int index = 0;

      for(size_t i=dir_size+1;i<file_path_size;i++){

          if( path[i] == '.'){

              break;
          }

          this->Header_File_Name[index] = path[i];

          index++;
      }

      this->Header_File_Name[index] = '\0';
}


void Header_File_Determiner::Determine_Header_File_Name_With_Extention(char * path){

     this->Clear_Pointer_Memory(&this->Header_File_Name_With_Extention);

     size_t file_path_size = strlen(path);

     size_t dir_size = file_path_size;

     for(size_t i=file_path_size;i>0;i--){

          if(((path[i] == '/') || (path[i] == '\\'))){

             break;
          }
          else{

              dir_size--;
          }
      }

      size_t Header_File_Name_Size = file_path_size - dir_size;

      this->Memory_Delete_Condition = false;

      this->Header_File_Name_With_Extention = new char [5*Header_File_Name_Size];

      int index = 0;

      for(size_t i=dir_size+1;i<file_path_size;i++){

          this->Header_File_Name_With_Extention[index] = path[i];

          index++;
      }

      this->Header_File_Name_With_Extention[index] = '\0';
}

void Header_File_Determiner::Determine_Header_File_System_Path(char * repo_dir,

     char * git_record_path, char operating_sis){

     this->Clear_Pointer_Memory(&this->Header_File_System_Path);

     size_t repo_dir_size   = strlen(repo_dir);

     size_t git_record_size = strlen(git_record_path);

     size_t path_size = repo_dir_size + git_record_size;

     int index = 0;

     this->Header_File_System_Path = new char [5*path_size];

     for(size_t i=0;i<repo_dir_size;i++){

         this->Header_File_System_Path[index] = repo_dir[i];

         if(operating_sis == 'w'){

            if(this->Header_File_System_Path[index] == '/'){

               this->Header_File_System_Path[index] = '\\' ;
            }
         }

         index++;
     }

     if(operating_sis == 'w'){

        if(repo_dir[repo_dir_size-1] != '\\' ){

           this->Header_File_System_Path[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

       if(repo_dir[repo_dir_size-1] != '/' ){

         this->Header_File_System_Path[index] = '/';

         index++;
       }
     }

     for(size_t i=0;i<git_record_size;i++){

         this->Header_File_System_Path[index] = git_record_path[i];

         if(operating_sis == 'w'){

            if(this->Header_File_System_Path[index] == '/'){

               this->Header_File_System_Path[index] = '\\' ;
             }
          }

         index++;
     }

     this->Header_File_System_Path[index] = '\0';
}



void Header_File_Determiner::Clear_Pointer_Memory(char ** pointer){

     if(*pointer != nullptr){

       delete [] *pointer;

       *pointer = nullptr;
     }
}

void Header_File_Determiner::Construct_Temporary_String(char ** tmp_string, char * string){

     size_t string_size = strlen(string);

     *tmp_string = new char [5*string_size];

     for(size_t n=0;n<5*string_size;n++){

        (*tmp_string)[n] = '\0';
     }

     for(size_t n=0;n<string_size;n++){

        (*tmp_string)[n] = string[n];
     }

     (*tmp_string)[string_size] = '\0';
}

bool Header_File_Determiner::CompareString(char * firstString,char * secondString){

     int firstStringLength  = strlen(firstString);

     int secondStringLength = strlen(secondString);

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

void Header_File_Determiner::Delete_Spaces_on_String(char ** pointer){

     size_t string_size = strlen(*pointer);

     int remove_index = 0;

     for(size_t i=0;i<string_size;i++){

         if((*pointer)[i] == ' '){

            for(size_t k=i;k<string_size;k++){

               (*pointer)[k] = (*pointer)[k+1];
            }

            remove_index++;
         }
     }

     (*pointer)[string_size - remove_index+1] = '\0';
}


void Header_File_Determiner::Determine_Git_Record_File_System_Path(char * file_path, char ** sys_path,

     char operating_sis){

     size_t repo_dir_size = strlen(this->Repo_Dir);

     size_t path_size = strlen(file_path);

     size_t sys_path_size = repo_dir_size + path_size;

     *sys_path =  new char [5*sys_path_size];

     for(size_t i=0;i<5*sys_path_size;i++){

         (*sys_path)[i] = '\0';
     }

     int index=0;

     for(size_t i=0;i<repo_dir_size;i++){

       (*sys_path)[index] = this->Repo_Dir[i];

       index++;

       if(operating_sis =='w'){

          if((*sys_path)[index] == '/'){

             (*sys_path)[index] = '\\';
          }
       }
     }

     //index++;

     if(operating_sis =='w'){

           (*sys_path)[index] = '\\';
     }
     else{

          (*sys_path)[index] = '/';
     }

     index++;

     for(size_t i=0;i<path_size;i++){

        (*sys_path)[index] = file_path[i];

        if(operating_sis =='w'){

           if((*sys_path)[index] == '/'){

              (*sys_path)[index] = '\\';
           }
        }

        index++;
      }

      (*sys_path)[index] = '\0';
}

char * Header_File_Determiner::Get_Header_Directory(){

       return this->Header_File_Directory;
}

char * Header_File_Determiner::Get_Header_File_Name_Without_Ext(){

       return this->Header_File_Name;
}

char * Header_File_Determiner::Get_Header_File_Name_With_Ext(){

       return this->Header_File_Name_With_Extention;
}

char * Header_File_Determiner::Get_Header_File_System_Path(){

      return this->Header_File_System_Path;
}
