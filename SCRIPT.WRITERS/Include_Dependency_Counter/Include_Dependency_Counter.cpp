
#include "Include_Dependency_Counter.hpp"

Include_Dependency_Counter::Include_Dependency_Counter(){

   this->git_record_size = 0;

}

Include_Dependency_Counter::Include_Dependency_Counter(const Include_Dependency_Counter & orig){


}

Include_Dependency_Counter::~Include_Dependency_Counter(){

}



void Include_Dependency_Counter::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Git_Data_Receiver.Receive_Descriptor_File_Reader(Pointer);

     this->Git_Data_Receiver.Determine_Git_Repo_Info();

     this->git_record_size = this->Git_Data_Receiver.Get_Git_File_Index_Size();
}


bool Include_Dependency_Counter::Is_This_Repo_Header(char * string_line, char * file_path){

     this->is_this_repo_header = false;

     if(strlen(string_line) == 0){

     }
     else{

            char * header_name = nullptr;

            this->Extract_Header_Name_From_String_Line(&header_name,string_line,file_path);

            if(strlen(header_name)>0){

               for(int i=0;i<this->git_record_size;i++){

                   char * file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

                   char * file_name = nullptr;

                   this->Extract_Include_File_Name_From_Path(&file_name,file_path);

                   bool is_equal = this->CompareString(file_name,header_name);

                   delete [] file_name;

                   if(is_equal){

                      this->is_this_repo_header = true;

                      break;
                    }
                }

                delete [] header_name;
            }
     }


    return this->is_this_repo_header;
}



void Include_Dependency_Counter::Extract_Header_Name_From_String_Line(char ** pointer, char * string_line, char * file_path){

     size_t string_size = strlen(string_line);

     size_t start_point = 0, end_point = 0;

     for(size_t i=0;i<string_size;i++){

          if(((string_line[i] == '\"') || (string_line[i] == '<'))){

              start_point = i+1;

              break;
          }
      }


      for(size_t i=string_size;i>0;i--){

           if(((string_line[i] == '\"') || (string_line[i] == '>'))){

               end_point = i;

               break;
           }
       }


       size_t name_size = end_point - start_point;

       if(name_size <= 0){

          std::cout << "\n wrong header file decleration detected on ";

          std::cout << file_path;

          exit(0);
       }

       *pointer = new char [5*name_size];


       int index = 0;

       for(size_t i=start_point;i<end_point;i++){

           (*pointer)[index] = string_line[i];

           index++;
       }

       (*pointer)[index] = '\0';
}


void Include_Dependency_Counter::Extract_Include_File_Name_From_Path(char ** pointer, char * string ){

     size_t string_size = strlen(string);

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(string[i] == '/'){

            start_point = i+1;

            break;
        }
     }


     size_t name_size = string_size - start_point;

     *pointer = new char [5*name_size];


     int index = 0;

     for(size_t i=start_point;i<string_size;i++){

         (*pointer)[index] = string[i];

         index++;
     }

     (*pointer)[index] = '\0';
}


bool Include_Dependency_Counter::CompareString(char * firstString,char * secondString){

     size_t firstStringLength  = strlen(firstString);

     size_t secondStringLength = strlen(secondString);

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
