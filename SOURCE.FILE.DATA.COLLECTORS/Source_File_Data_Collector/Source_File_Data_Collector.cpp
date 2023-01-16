


#include "Source_File_Data_Collector.hpp"

Source_File_Data_Collector::Source_File_Data_Collector(char * DesPath, char opr_sis) :

    Git_Receiver(DesPath)
{
    this->operating_sis = opr_sis;

    this->Initialize_Members();

    this->Git_Receiver.Determine_Git_Repo_Info();
}


Source_File_Data_Collector::~Source_File_Data_Collector(){

        this->Clear_Dynamic_Memory();    
}

void Source_File_Data_Collector::Initialize_Members(){


     this->File_Content_Size = 0;

     this->included_header_file_number = 0;

     this->git_record_size = 0;
}

void Source_File_Data_Collector::Receive_Source_File_Data(std::string file_path)
{
     this->git_record_size = this->Git_Receiver.Get_Git_File_Index_Size();

     this->Git_Repo_Dir    = this->Git_Receiver.Get_Git_Repo_Directory();

     this->FilePATH = file_path;

     this->Read_File(file_path);

     this->Determine_Include_Line_Number();

     this->Receive_Include_File_Names();
}



void Source_File_Data_Collector::Read_File(std::string path){

     this->FileManager.Clear_Dynamic_Memory();

     this->FileManager.SetFilePath(path);

     // File size Determination

     this->FileManager.FileOpen(Rf);

     this->File_Content_Size = 0;

     do {
            std::string file_line = this->FileManager.ReadLine();

            this->Delete_Spaces_on_String(&file_line);

            this->File_Content.push_back(file_line);

            this->File_Content_Size++;

     }while(!this->FileManager.Control_Stop_Condition());

     this->FileManager.FileClose();
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

void Source_File_Data_Collector::Receive_Include_File_Names(){

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
                }
              }
          }
      }
}

void Source_File_Data_Collector::Determine_Git_Record_Header_File_Path(std::string * header_path,

     std::string header_name){

     for(int i=0;i<this->git_record_size;i++){

         std::string file_path = this->Git_Receiver.Get_Git_File_Index(i);

         std::string file_name = "";

         this->Extract_Include_File_Name_From_Path(&file_name,file_path);

         bool is_equal = this->CompareString(file_name,header_name);

         if(is_equal){

            size_t header_path_size = file_path.length();

            for(size_t k=0;k<header_path_size;k++){

               (*header_path).append(1,file_path[k]);

               if(this->operating_sis == 'w'){

                  if((*header_path)[k] == '/'){

                     (*header_path)[k] = '\\';
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

        std::cerr << "\n please check header decleration";

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

       (*header_dir).append(1,header_path[i]);

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

        (*directory).append(1,this->Git_Repo_Dir[k]);
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

        (*directory).append(1,file_path[k]);

        if(this->operating_sis == 'w'){

           if((*directory)[k]  == '/'){

             (*directory)[k] = '\\';
           }
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

     int index = 0;

     for(size_t i=start_point;i<end_point;i++){

         (*pointer).append(1,string[i]) ;
     }
}



void Source_File_Data_Collector::Extract_Include_File_Name_From_Path(std::string * pointer,

     std::string string ){

     size_t string_size = string.length();

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(string[i] == '/'){

            start_point = i+1;

            break;
        }
     }

     size_t name_size = string_size - start_point;

     for(size_t i=start_point;i<string_size;i++){

         (*pointer).append(1,string[i]) ;
     }
}

void Source_File_Data_Collector::Determine_Git_Record_Source_File_Directory(std::string * record_dir,

     std::string git_record_path){

     size_t path_size = git_record_path.length();

     size_t dir_size = path_size;

     size_t end_point = 0;

     for(int i=path_size;i>0;i--){

         if(git_record_path[i] == '/'){

           end_point = i;

           break;
         }
     }

     dir_size = end_point;

     for(size_t i=0;i<dir_size;i++){

         (*record_dir).append(1,git_record_path[i]) ;

         if(this->operating_sis =='w'){

            if((*record_dir)[i] == '/'){

               (*record_dir)[i] = '\\';
            }
         }
    }
}


void Source_File_Data_Collector::Determine_Git_Record_Source_File_Path(std::string * source_file_path,

     std::string file_path){

     size_t path_size = file_path.length();

     for(size_t i=0;i<path_size;i++){

         (*source_file_path).append(1,file_path[i]) ;

         if(this->operating_sis =='w'){

            if((*source_file_path)[i] == '/'){

               (*source_file_path)[i] = '\\';
            }
         }
     }
}



void Source_File_Data_Collector::Determine_Header_Files_System_Paths(std::string * pointer,

     std::string directory, std::string file_name){

     size_t directory_size = directory.length();

     size_t file_name_size = file_name.length();


     for(size_t i=0;i<directory_size;i++){

        (*pointer).append(1,directory[i]);
     }


     if(this->operating_sis == 'w'){

       if((*pointer)[directory_size-1] != '\\'){

          (*pointer).append(1,'\\') ;
       }

     }
     else{

         if((*pointer)[directory_size-1] != '/'){

            (*pointer).append(1,'/') ;
         }
     }

     for(size_t i=0;i<file_name_size;i++){

        (*pointer).append(1,file_name[i]) ;
     }
}

void Source_File_Data_Collector::Delete_Spaces_on_String(std::string * pointer)
{
     size_t string_size = (*pointer).length();

     int remove_index = 0;

     if(string_size>0){

        for(size_t i=0;i<string_size;i++){

            if((*pointer)[i] == ' '){

                for(size_t k=i;k<string_size;k++){

                   (*pointer)[k] = (*pointer)[k+1];
                }

                remove_index++;
            }
        }

        for(size_t i=0;i<remove_index;i++){

            (*pointer).pop_back();
        }
     }
}


bool Source_File_Data_Collector::CompareString(std::string firstString,

     std::string secondString){

     size_t firstStringLength  = firstString.length();

     size_t secondStringLength = secondString.length();

     this->isStringsEqual = false;

     if(firstStringLength==secondStringLength){

        for(size_t i=0;i<firstStringLength;i++){

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

     if(!this->Head_Data.empty()){

         this->Head_Data.clear();
     }

     if(!this->File_Content.empty()){

         this->File_Content.clear();
     }

     this->FileManager.Clear_Dynamic_Memory();
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
