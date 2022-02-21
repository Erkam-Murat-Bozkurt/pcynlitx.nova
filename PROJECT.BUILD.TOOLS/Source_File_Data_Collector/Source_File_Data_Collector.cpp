


#include "Source_File_Data_Collector.hpp"

Source_File_Data_Collector::Source_File_Data_Collector(){

    this->File_Content = nullptr;

    this->Include_File_List = nullptr;

    this->File_Content_Size = 0;

    this->included_header_file_number = 0;
}

Source_File_Data_Collector::Source_File_Data_Collector(const Source_File_Data_Collector & orig){


}

Source_File_Data_Collector::~Source_File_Data_Collector(){


}

void Source_File_Data_Collector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

          this->Memory_Delete_Condition = true;

          if(this->File_Content != nullptr){

             for(int i=0;i<this->File_Content_Size;i++){

                 delete [] this->File_Content[i];

                 this->File_Content[i] = nullptr;
             }

             delete [] this->File_Content;

             this->File_Content = nullptr;
          }

          if(this->Include_File_List != nullptr){

             for(int i=0;i<this->included_header_file_number;i++){

                 delete [] this->Include_File_List[i];

                 this->Include_File_List[i] = nullptr;
             }

             delete [] this->Include_File_List;

             this->Include_File_List = nullptr;
         }
      }
}

void Source_File_Data_Collector::Receive_Source_File_Data(char * file_path){

     this->Read_File(file_path);

     this->Determine_Include_Line_Number();

     this->Receive_Include_File_Names();
}

void Source_File_Data_Collector::Determine_Include_Line_Number(){

     char include_db_key [] = "#include\"";  // double_quotation_mark

     this->included_header_file_number = 0;

     for(int i=0;i<this->File_Content_Size;i++){

         this->Delete_Spaces_on_String(&(this->File_Content[i]));

         bool is_include_line_db

         = this->StringManager.CheckStringInclusion(this->File_Content[i],include_db_key);

         bool char_before_sharp = false; //  sharp symbol = #

         if(this->File_Content[i][0]!= '#'){

             char_before_sharp = true;
         }

         if(!char_before_sharp){ // In metaprograms, #include key is used on the inside code

           if(is_include_line_db){

              this->included_header_file_number++;
           }
         }
     }
}

void Source_File_Data_Collector::Receive_Include_File_Names(){

     int memory_size = 5*this->included_header_file_number;

     this->Include_File_List = new char * [memory_size];

     int index = 0;


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

                this->Delete_Spaces_on_String(&(this->File_Content[i]));

                bool syntax_error_cond = this->Control_Include_Syntax(this->File_Content[i]);

                if(!syntax_error_cond){

                    this->Receive_Include_File_Name(&(this->Include_File_List[index]),

                        this->File_Content[i]);

                    index++;
                }
              }
          }
      }
}

void Source_File_Data_Collector::Receive_Include_File_Name(char ** pointer, char * string ){

     size_t string_size = strlen(string);

     *pointer = new char [5*string_size];

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

         (*pointer)[index] = string[i];

         index++;
     }

     (*pointer)[index] = '\0';
}

bool Source_File_Data_Collector::Control_Include_Syntax(char * string){

     size_t string_size = strlen(string);

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

bool Source_File_Data_Collector::Character_Inclusion_Check(char * string, char chr){

     this->Character_Inclusion_Status = false;

     size_t string_size = strlen(string);

     for(size_t i=0;i<string_size;i++){

         if(string[i] == chr){

            this->Character_Inclusion_Status = true;

            break;
         }
     }

     return this->Character_Inclusion_Status;
}

void Source_File_Data_Collector::Read_File(char * path){

     if(this->File_Content != nullptr){

        for(int i=0;i<this->File_Content_Size;i++){

            delete [] this->File_Content[i];

            this->File_Content[i] = nullptr;
        }

        delete [] this->File_Content;

        this->File_Content = nullptr;
     }

     this->FileManager.SetFilePath(path);

     this->FileManager.FileOpen(Rf);

     this->File_Content_Size = 0;

     do {

            std::string file_line = this->FileManager.ReadLine();

            this->File_Content_Size++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();


     this->File_Content = new char * [5*this->File_Content_Size];

     for(int i=0;i<this->File_Content_Size;i++){

         this->File_Content[i] = nullptr;
     }

     this->FileManager.FileOpen(Rf);

     int index = 0;

     do {

          char * string_line = this->FileManager.ReadLine_as_Cstring();

          size_t string_size = strlen(string_line);

          this->File_Content[index] = new char [5*string_size];

          for(size_t i=0;i<string_size;i++){

              this->File_Content[index][i] = string_line[i];
          }

          this->File_Content[index][string_size] ='\0';

          index++;

     }while(!this->FileManager.Control_End_of_File());

     this->FileManager.FileClose();
}

void Source_File_Data_Collector::Delete_Spaces_on_String(char ** pointer){

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


int Source_File_Data_Collector::Get_Included_File_Number(){

    return this->included_header_file_number;
}

char * Source_File_Data_Collector::Get_Include_File_Name(int num){

       return this->Include_File_List[num];
}
