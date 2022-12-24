

#include "Descriptor_File_Syntax_Controller.hpp"

Descriptor_File_Syntax_Controller::Descriptor_File_Syntax_Controller(){

  this->Memory_Delete_Condition = true;

  this->Descriptor_File_Path = nullptr;

}

Descriptor_File_Syntax_Controller::Descriptor_File_Syntax_Controller(const Descriptor_File_Syntax_Controller & orig){


}

Descriptor_File_Syntax_Controller::~Descriptor_File_Syntax_Controller(){

  if(!this->Memory_Delete_Condition){

     this->Clear_Dynamic_Memory();
  }
}


void Descriptor_File_Syntax_Controller::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Descriptor_File_Path != nullptr){

            delete [] this->Descriptor_File_Path;
         }

         this->Descriptor_File_Path = nullptr;
     }
}


void Descriptor_File_Syntax_Controller::Control_Descriptor_File_Syntax(char * path){

     this->Receive_Descriptor_File_Path(path);

     this->Control_Keywords();

     this->Control_Braces();
}

void Descriptor_File_Syntax_Controller::Receive_Descriptor_File_Path(char * path){

     size_t path_size = strlen(path);

     this->Memory_Delete_Condition = false;

     this->Descriptor_File_Path = new char [5*path_size];

     for(size_t i=0;i<path_size;i++){

        this->Descriptor_File_Path[i] = path[i];
     }

     this->Descriptor_File_Path[path_size] = '\0';

     this->StringManager.SetFilePath(this->Descriptor_File_Path);

     this->FileManager.SetFilePath(this->Descriptor_File_Path);
}

void Descriptor_File_Syntax_Controller::Control_Keywords(){

     char root_dir [] = "[PROJECT-ROOT-DIR]";

     char warehouse_location [] = "[PROJECT-WAREHOUSE-LOCATION]";

     char standard [] = "[C++-STANDARD]";

     char include_dir [] = "[INCLUDE-DIRECTORIES]";

     char src_dir [] = "[SOURCE-FILE-DIRECTORIES]";

     char lib_dir [] = "[LIBRARY-DIRECTORIES]";

     char lib_files [] = "[LIBRARY-FILES]";

     char options [] = "[OPTIONS]";


     if(!this->Control_String_Inclusion(root_dir)){

         std::cout << "\n There is a syntax error on descriptor file";

         exit(0);
     };


     if(!this->Control_String_Inclusion(warehouse_location)){

         std::cout << "\n There is a syntax error on descriptor file";

         exit(0);
     };

     if(!this->Control_String_Inclusion(standard)){

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     };

     if(!this->Control_String_Inclusion(include_dir)){

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     };


     if(!this->Control_String_Inclusion(src_dir)){

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     };



     if(!this->Control_String_Inclusion(lib_files)){

         std::cout << "\n There is a syntax error on descriptor file";

         exit(0);
     };


     if(!this->Control_String_Inclusion(lib_dir)){

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     };

     if(!this->Control_String_Inclusion(options)){

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     };
}

void Descriptor_File_Syntax_Controller::Control_Braces(){

     char start_brace [] = "{";

     char end_brace []   = "}";

     int start_brace_number = this->Determine_Repitation(start_brace);

     int end_brace_number = this->Determine_Repitation(end_brace);

     if(start_brace_number!=end_brace_number){

        std::cout << "\n Missing braces";

        std::cout << "\n There is a syntax error on descriptor file";

        exit(0);
     }
}

bool Descriptor_File_Syntax_Controller::Control_String_Inclusion(char * search_word){

    this->include_condition = false;

    this->FileManager.FileOpen(Rf);

    do{
          char * string_line = this->FileManager.ReadLine_as_Cstring();

          this->Delete_Spaces_on_String(&string_line);

          if(this->FileManager.Control_End_of_File()){

              break;
          }

          if(this->StringManager.CheckStringLine(string_line)){

             this->StringManager.ReceiveFileLine(string_line);

             this->include_condition

             = this->StringManager.CheckStringInclusion(this->StringManager.GetStringBuffer(),search_word);

             if(this->include_condition){

                break;
             }
          }

    }while(!this->FileManager.Control_End_of_File());

    this->FileManager.FileClose();

    return this->include_condition;
}


int Descriptor_File_Syntax_Controller::Determine_Repitation(char * search_word){

    this->repitation = 0;

    this->FileManager.FileOpen(Rf);

    do{
          char * string_line = this->FileManager.ReadLine_as_Cstring();

          this->Delete_Spaces_on_String(&string_line);

          if(this->FileManager.Control_End_of_File()){

              break;
          }

          if(this->StringManager.CheckStringLine(string_line)){

             this->StringManager.ReceiveFileLine(string_line);

             bool include_condition

             = this->StringManager.CheckStringInclusion(this->StringManager.GetStringBuffer(),search_word);

             if(include_condition){

               this->repitation++;
             }
          }

    }while(!this->FileManager.Control_End_of_File());

    this->FileManager.FileClose();

    return this->repitation;
}


void Descriptor_File_Syntax_Controller::Delete_Spaces_on_String(char ** pointer){

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
