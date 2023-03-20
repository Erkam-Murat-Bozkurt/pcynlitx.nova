

#include "Header_File_Processor.hpp"

Header_File_Processor::Header_File_Processor(char * DesPath, char opr_sis) :

     Git_Receiver(DesPath,opr_sis)
{
    this->Git_Receiver.Determine_Git_Repo_Info();

    this->git_record_size = this->Git_Receiver.Get_Git_File_Index_Size();

    this->Repo_Dir  = this->Git_Receiver.Get_Git_Repo_Directory();

    this->operating_sis = opr_sis;

    this->include_decleration_cond = false;

    this->Memory_Delete_Condition = false;

    this->is_header_file = false;
}


Header_File_Processor::~Header_File_Processor(){

     this->Clear_Object_Memory();  
}

void Header_File_Processor::Clear_Object_Memory(){

     this->Git_Receiver.Clear_Dynamic_Memory();

     this->Clear_String_Memory(&this->Repo_Dir);

     this->Clear_Dynamic_Memory();
}

void Header_File_Processor::Clear_Dynamic_Memory(){

     this->Clear_String_Memory(&this->Header_File_Directory);
     this->Clear_String_Memory(&this->Header_File_Name);
     this->Clear_String_Memory(&this->Header_File_Name_With_Extention);
     this->Clear_String_Memory(&this->Header_File_System_Path);

     this->StringManager.Clear_Dynamic_Memory();
     this->FileManager.Clear_Dynamic_Memory();   
}

void Header_File_Processor::Receive_Source_Code_Reader(Project_Src_Code_Rdr * ptr){

     this->Code_Rdr = ptr;
}


bool Header_File_Processor::Is_this_file_included_on_anywhere(std::string file_path){

     size_t repo_size = this->Code_Rdr->Get_Project_Files_Number();

     this->Is_this_file_included_on_somewhere = false;

     for(int i=0;i<repo_size;i++){

         std::vector<std::string> * File_Content = this->Code_Rdr->Get_File_Content(i);

         this->Header_File_System_Path = this->Code_Rdr->Get_File_Path(i);
         
         size_t FileSize = File_Content->size();

         for(size_t k=0;k<FileSize;k++){

             std::string file_line = File_Content->at(k);

             // In order to remove possible spaces on the string

             // a temporary string is constructed
             
             bool is_include_decleration = this->Include_Decleration_Test(file_line);


             std::string header_name;

             if(is_include_decleration){

                this->Extract_Header_File_Name_From_Decleration(&header_name,file_line);

                this->Determine_Header_File_Name(file_path);

                bool is_strings_equal = this->CompareString(header_name,this->Header_File_Name);

                if(is_strings_equal){

                   this->Is_this_file_included_on_somewhere = true;

                   break;
                }
             }
         }
      }

      return this->Is_this_file_included_on_somewhere;
}

bool Header_File_Processor::Include_Decleration_Test(std::string string){

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

     for(int i=start_point;i<end_point;i++){

          (*header_name).append(1,string[i]);
     }
}

 bool Header_File_Processor::Is_This_Repo_Header(std::string file_path){
 
      this->is_this_repo_header = false;

      this->Determine_Header_File_Name_With_Extention(file_path);
   
      std::string file_name_wit_ext =this->Get_Header_File_Name_With_Ext();
 
      if(this->Is_Header(file_path)){
      
         int size = this->Git_Receiver.Get_Git_File_Index_Size();

         for(int i=0;i<size;i++){
         
             std::string repo_file_system_path = this->Git_Receiver.Get_File_System_Path(i);

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




bool Header_File_Processor::Is_Header(std::string file_path){

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
