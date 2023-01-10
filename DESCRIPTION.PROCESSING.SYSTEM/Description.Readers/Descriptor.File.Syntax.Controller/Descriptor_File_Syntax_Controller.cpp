

#include "Descriptor_File_Syntax_Controller.hpp"

Descriptor_File_Syntax_Controller::Descriptor_File_Syntax_Controller(char * path) :

  StringManager(path), FileManager(path)
{

   this->Memory_Delete_Condition = false;
}

Descriptor_File_Syntax_Controller::Descriptor_File_Syntax_Controller(std::string path) :

  StringManager(path), FileManager(path)
{

  this->Memory_Delete_Condition = false;

}

Descriptor_File_Syntax_Controller::~Descriptor_File_Syntax_Controller(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}


void Descriptor_File_Syntax_Controller::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->FileManager.Clear_Dynamic_Memory();
     }
}

void Descriptor_File_Syntax_Controller::Control_Descriptor_File_Syntax(){

     this->Receive_Descriptor_File_Index();

     this->Control_Keywords();

     this->Control_Braces();
}


void Descriptor_File_Syntax_Controller::Receive_Descriptor_File_Index(){

     this->FileManager.FileOpen(Rf);

     do{

          std::string string_line = this->FileManager.Read();

          this->Delete_Spaces_on_String(&string_line);

          if(this->StringManager.CheckStringLine(string_line)){

            this->File_Index.push_back(string_line);
          }

      }while(!this->FileManager.Control_Stop_Condition());

      this->FileManager.FileClose();
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



bool Descriptor_File_Syntax_Controller::Control_String_Inclusion(std::string search_word)
{
     this->include_condition = false;

     std::vector<std::string>::iterator it;

     for(auto it=this->File_Index.begin();it<this->File_Index.end();it++){

         if(this->StringManager.CheckStringLine(*it)){

            this->include_condition

            = this->StringManager.CheckStringInclusion(*it,search_word);

            if(this->include_condition){

               break;
            }
          }
     }

    return this->include_condition;
}


int Descriptor_File_Syntax_Controller::Determine_Repitation(std::string search_word)
{
    this->repitation = 0;

    for(auto it=this->File_Index.begin();it<this->File_Index.end();it++){

        if(this->StringManager.CheckStringLine(*it)){

           this->include_condition

           = this->StringManager.CheckStringInclusion(*it,search_word);

           if(this->include_condition){

             this->repitation++;
           }
         }
    }

    return this->repitation;
}


void Descriptor_File_Syntax_Controller::Delete_Spaces_on_String(std::string * pointer){

     size_t string_size = (*pointer).length();

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
