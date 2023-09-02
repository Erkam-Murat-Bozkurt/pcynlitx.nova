



#include "Git_Modification_Receiver.hpp"

Git_Modification_Receiver::Git_Modification_Receiver(char opr_sis): 

  StringManager(opr_sis)
{
     this->opr_sis = opr_sis;
}



Git_Modification_Receiver::~Git_Modification_Receiver(){

     this->Clear_Dynamic_Memory();
}

void Git_Modification_Receiver::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

}



void Git_Modification_Receiver::Receive_Git_List_Receiver(Git_File_List_Receiver * ptr){

     this->Git_List_Receiver = ptr;
}

void Git_Modification_Receiver::Receive_Git_Modifications()
{     
     this->warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir  = this->Des_Reader->Get_Repo_Directory_Location();

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

         bool is_header = this->Is_Header(this->File_Content.at(i));

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




bool Git_Modification_Receiver::Is_Header(std::string file_path){

     char inclusion_guard [] = "#ifndef";

     char header_add_h [] = ".h";

     char header_add_hpp [] = ".hpp";

     char source_file_ext [] = ".cpp";

     bool is_header_file = false;

     if(this->StringManager.CheckStringInclusion(file_path,source_file_ext)){

        return is_header_file;
     }

     is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_h);

     if(is_header_file){

        return is_header_file;
     }
     else{

          is_header_file = this->StringManager.CheckStringInclusion(file_path,header_add_hpp);

          if(is_header_file){

              return is_header_file;
          }
    }

    if(this->Is_this_file_included_on_anywhere(file_path)){

       is_header_file = true;
    }

    return is_header_file;
}




bool Git_Modification_Receiver::Is_this_file_included_on_anywhere(std::string file_path){

     bool Is_this_file_included_on_somewhere = false;

     size_t git_record_size = this->Git_List_Receiver->Get_Git_File_Index_Size();

     for(int i=0;git_record_size-1;i++){

         std::string git_record_path = this->Git_List_Receiver->Get_Git_File_Index(i);

         std::string record_sys_path = "";

         this->Determine_Git_Record_File_System_Path(&record_sys_path,git_record_path);

         bool is_path_exist = this->FileManager.Is_Path_Exist(record_sys_path);

         this->FileManager.SetFilePath(record_sys_path);

         bool is_file_openned = this->FileManager.TryOpen('r');

         bool file_exist = false;

         if(is_path_exist && is_file_openned){

            file_exist = true;
         }

         this->FileManager.Clear_Dynamic_Memory();

         if(file_exist){

            this->FileManager.Read_File(record_sys_path);

            int FileSize = this->FileManager.GetFileSize();

            for(int k=0;k<FileSize;k++){

                std::string file_line = this->FileManager.GetFileLine(k);

                // In order to remove possible spaces on the string

                // a temporary string is constructed

                this->Delete_Spaces_on_String(&file_line);

                bool is_include_decleration = this->Include_Decleration_Test(file_line);


                std::string header_name;

                if(is_include_decleration){

                   this->Extract_Header_File_Name_From_Decleration(&header_name,file_line);

                   this->Determine_Header_File_Name(file_path);

                   bool is_strings_equal = this->CompareString(header_name,this->Header_File_Name);

                   if(is_strings_equal){

                      Is_this_file_included_on_somewhere = true;

                      break;
                    }
                }
            }
         }
      }

      return Is_this_file_included_on_somewhere;
}



void Git_Modification_Receiver::Determine_Git_Record_File_System_Path(std::string * sys_path,

     std::string file_path){

     size_t repo_dir_size = this->Repo_Dir.length();

     size_t path_size = file_path.length();

     size_t sys_path_size = repo_dir_size + path_size;

     int index=0;

     for(size_t i=0;i<repo_dir_size;i++){

        (*sys_path).push_back(this->Repo_Dir[i]);

        if(this->opr_sis =='w'){

          if((*sys_path)[i] == '/'){

             (*sys_path)[i] = '\\';
          }
       }
     }

     if(this->opr_sis =='w'){

        (*sys_path).push_back('\\');
     }
     else{

        (*sys_path).push_back('/');
     }


     for(size_t i=0;i<path_size;i++){

        (*sys_path).push_back(file_path[i]);

        if(this->opr_sis =='w'){

           if((*sys_path)[i] == '/'){

              (*sys_path)[i] = '\\';
           }
        }
     }
}



bool Git_Modification_Receiver::Include_Decleration_Test(std::string string){

     bool include_decleration_cond = false;

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

           include_decleration_cond = true;
        }
     }

     return include_decleration_cond;
}


void Git_Modification_Receiver::Extract_Header_File_Name_From_Decleration(std::string * header_name,

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



void Git_Modification_Receiver::Determine_Header_File_Name(std::string path){

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

          this->Header_File_Name.push_back(path[i]);
      }
}



bool Git_Modification_Receiver::CompareString(std::string firstString, std::string secondString){

     int firstStringLength  = firstString.length();

     int secondStringLength = secondString.length();

     bool isStringsEqual = false;

     if(firstStringLength==secondStringLength){

        for(int i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               isStringsEqual = false;

               return isStringsEqual;
            }
        }

        isStringsEqual = true;

        return isStringsEqual;
     }
     else{

          isStringsEqual = false;

          return isStringsEqual;
     }
}


void Git_Modification_Receiver::Delete_Spaces_on_String(std::string * str){

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