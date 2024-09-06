

#include "Descriptor_File_Syntax_Controller.hpp"

Descriptor_File_Syntax_Controller::Descriptor_File_Syntax_Controller(char opr_sis) :

  StringManager(opr_sis), FileManager(opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->syntax_error_status = false;

   this->invalid_descriptor_file_status = false;

   this->syntax_error_number = 0;
}

Descriptor_File_Syntax_Controller::~Descriptor_File_Syntax_Controller(){

    if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
    }
}

void Descriptor_File_Syntax_Controller::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Vector_Memory(&this->File_Index);

         this->StringManager.Clear_Dynamic_Memory();

         this->FileManager.Clear_Dynamic_Memory();

         this->syntax_error_status = false;

         this->invalid_descriptor_file_status = false;

         this->syntax_error_number = 0;
     }
}


void Descriptor_File_Syntax_Controller::Receive_Descriptor_File_Path(char * DesPATH){

     size_t des_path_size = strlen(DesPATH);

     for(size_t i=0;i<des_path_size;i++){

         this->Descriptor_File_Path.push_back(DesPATH[i]);
     }

     this->Descriptor_File_Path.shrink_to_fit();

     
}


void Descriptor_File_Syntax_Controller::Set_Gui_Read_Status(bool status){

     this->gui_read_status = status;
}

void Descriptor_File_Syntax_Controller::Receive_Descriptor_File_Path(std::string DesPATH){

     this->Descriptor_File_Path = DesPATH;
}

void Descriptor_File_Syntax_Controller::Control_Descriptor_File_Syntax(){

     this->syntax_error_status = false;

     this->invalid_descriptor_file_status = false;

     this->syntax_error_number = 0;

     this->Memory_Delete_Condition = false;

     this->FileManager.SetFilePath(this->Descriptor_File_Path);

     this->Receive_Descriptor_File_Index();

     this->Control_Keywords();

     this->Control_Braces();

     
     if(this->gui_read_status){

        if(this->syntax_error_status){

           if(this->syntax_error_number>1){

              this->invalid_descriptor_file_status = true;
           }
        }
     }
}


void Descriptor_File_Syntax_Controller::Receive_Descriptor_File_Index(){

     this->Memory_Delete_Condition = false;

     this->Clear_Vector_Memory(&this->File_Index);

     this->FileManager.FileOpen(Rf);

     do{
          std::string string_line = this->FileManager.ReadLine();

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

     char compiler_options [] = "[COMPILER-OPTIONS]";

     char linker_options [] = "[LINKER-OPTIONS]";

     char build_system_type [] = "[BUILD-SYSTEM]";

     char project_name [] = "[PROJECT-NAME]";

     char version_number [] = "[VERSION-NUMBER]";

     char compiler_paths [] = "[COMPILER-PATHS]";





     this->syntax_error_status = false;

     this->invalid_descriptor_file_status = false;

     this->syntax_error_number = 0;


     if(!this->Control_String_Inclusion(root_dir)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


     if(!this->Control_String_Inclusion(warehouse_location)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


     if(!this->Control_String_Inclusion(standard)){

        std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
        std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


     if(!this->Control_String_Inclusion(include_dir)){

        std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
        std::cout << "\n\n";

        if(this->gui_read_status){

           this->syntax_error_status = true;

           this->syntax_error_number++;
        }
        else{

            exit(0);
        }
     };


     if(!this->Control_String_Inclusion(src_dir)){

        std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
        std::cout << "\n\n";

        if(this->gui_read_status){

           this->syntax_error_status = true;

           this->syntax_error_number++;
        }
        else{

            exit(0);
        }
     };


     if(!this->Control_String_Inclusion(lib_files)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


     if(!this->Control_String_Inclusion(lib_dir)){

        std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
        std::cout << "\n\n";

        if(this->gui_read_status){

           this->syntax_error_status = true;

           this->syntax_error_number++;
        }
        else{

            exit(0);
        }
     };

     if(!this->Control_String_Inclusion(compiler_options)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";


         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };

     
     if(!this->Control_String_Inclusion(linker_options)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";


         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };

      
     if(!this->Control_String_Inclusion(build_system_type)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


       
     if(!this->Control_String_Inclusion(project_name)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };


     if(!this->Control_String_Inclusion(version_number)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };

     if(!this->Control_String_Inclusion(compiler_paths)){

         std::cout << "\nERROR REPORT: There is a syntax error on descriptor file \n";
         std::cout << "\n\n";

         if(this->gui_read_status){

            this->syntax_error_status = true;

            this->syntax_error_number++;
         }
         else{

            exit(0);
         }
     };

}

void Descriptor_File_Syntax_Controller::Control_Braces(){

     char start_brace [] = "{";

     char end_brace []   = "}";

     int start_brace_number = this->Determine_Repitation(start_brace);

     int end_brace_number = this->Determine_Repitation(end_brace);

     if(start_brace_number!=end_brace_number){

        std::cout << "\n ERROR REPORT:";

        std::cout << "\n Missing braces";

        std::cout << "\n There is a syntax error on descriptor file";

        if(this->gui_read_status){

           this->syntax_error_status = true;

           this->syntax_error_number++;
        }
        else{

            exit(0);
        }
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


void Descriptor_File_Syntax_Controller::Clear_Vector_Memory(std::vector<std::string> * pointer){

     size_t vec_size = pointer->size();

     for(size_t i=0;i<vec_size;i++){

         pointer->at(i).clear();

         pointer->at(i).shrink_to_fit();
     }

     pointer->clear();

     pointer->shrink_to_fit();
}

void Descriptor_File_Syntax_Controller::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}


void Descriptor_File_Syntax_Controller::Delete_Spaces_on_String(std::string * str)
{
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


bool Descriptor_File_Syntax_Controller::GetSyntaxErrorStatus() const {

       return this->syntax_error_status;
}


bool Descriptor_File_Syntax_Controller::Get_Invalid_Descriptor_File_Status() const {

     return this->invalid_descriptor_file_status;
}