


/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Source_File_Dependency_Selector.hpp"

Source_File_Dependency_Selector::Source_File_Dependency_Selector(){

   this->Memory_Delete_Condition = false;

   this->Dependent_List = nullptr;

   this->Dep_Counter = 0;
}

Source_File_Dependency_Selector::Source_File_Dependency_Selector(const

          Source_File_Dependency_Selector & orig){

}

Source_File_Dependency_Selector::~Source_File_Dependency_Selector(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Source_File_Dependency_Selector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         for(int i=0;i<this->Dep_Counter;i++){

             delete [] this->Dependent_List[i].Header_Name;

             delete [] this->Dependent_List[i].repo_warehouse_path;
         }

         if(this->Dependent_List != nullptr){

            delete [] this->Dependent_List;
         }

         this->Dep_Counter = 0;
     }
}


void Source_File_Dependency_Selector::Receive_Source_File_Information_Collector(

     Source_File_Information_Collector * pointer){

     this->Info_Collector = pointer;
}

void Source_File_Dependency_Selector::Determine_Source_File_Dependencies(char * path){

     this->Receive_Collector_Info();

     this->Extract_Dependency_Data(path);
}

void Source_File_Dependency_Selector::Receive_Collector_Info(){

     this->header_file_number = this->Info_Collector->Get_Compiler_Data_Size();

     this->Data_Ptr_CString   = this->Info_Collector->Get_Compiler_Data();

     this->warehouse_head_dir = this->Info_Collector->Get_Warehouse_Headers_Dir();

     this->Memory_Delete_Condition = false;

     this->Dependent_List = new Header_Dependency [5*this->header_file_number];
}

void Source_File_Dependency_Selector::Extract_Dependency_Data(char * path){

     int inclusion_number = 0;

     /*  Determination of the inclusion number */

     Cpp_FileOperations FileStream;

     FileStream.Read_File_as_CString(path);

     int FileSize = FileStream.GetFileSize();

     for(int k=0;k<FileSize;k++){

         char * string = FileStream.GetFileLine(k);

         // In order to remove possible spaces on the string

         // a temporary string is constructed

         char * tmp_string = nullptr;

         this->Construct_Temporary_String(&tmp_string,string);

         this->Delete_Spaces_on_String(&tmp_string);

         bool is_include_decleration = this->Include_Decleration_Test(tmp_string);

         if(is_include_decleration){

            inclusion_number++;
         }

         this->Clear_Pointer_Memory(&tmp_string);
     }

     if(inclusion_number>0){

        FileStream.Read_File_as_CString(path);

        int FileSize = FileStream.GetFileSize();

        for(int k=0;k<FileSize;k++){

            char * string = FileStream.GetFileLine(k);

            // In order to remove possible spaces on the string

            // a temporary string is constructed

            char * tmp_string = nullptr;

            this->Construct_Temporary_String(&tmp_string,string);

            this->Delete_Spaces_on_String(&tmp_string);


            bool is_include_decleration = this->Include_Decleration_Test(tmp_string);

            if(is_include_decleration){

               char * header_name = nullptr;

               char * wrd_path = nullptr;

               this->Extract_Header_File_Name_From_Decleration(&header_name,tmp_string);

               this->Determine_Header_Repo_Warehouse_Path(&wrd_path,

                    header_name,'w');

               bool is_repo_header_file = this->Is_This_Repo_HeaderFile(wrd_path);

               bool is_already_searched = this->Is_This_File_Aready_Searched(header_name);


               if((is_repo_header_file) && (!is_already_searched)){

                 this->Place_String(&this->Dependent_List[this->Dep_Counter].Header_Name,header_name);

                 this->Place_String(&this->Dependent_List[this->Dep_Counter].repo_warehouse_path,wrd_path);

                 this->Dependent_List[this->Dep_Counter].rcr_srch_complated = true;

                 this->Dep_Counter++;

                 this->Extract_Dependency_Data(wrd_path);
               }
             }

             this->Clear_Pointer_Memory(&tmp_string);
         }
      }
  }

  bool Source_File_Dependency_Selector::Is_This_Repo_HeaderFile(char * path){

       this->is_this_repo_header = false;

       bool is_header = this->Header_Determiner.Is_Header(path);

       int index_size = this->Info_Collector->Get_Compiler_Data_Size();

       if(is_header){

          //char * header_path = nullptr;

          for(int i=0;i<index_size;i++){

              char * repo_file_path = this->Data_Ptr_CString[i].repo_path;

              bool is_equal = this->CompareString(repo_file_path,path);

              if(is_equal){

                 this->is_this_repo_header = true;

                 return this->is_this_repo_header;
              };
          }
      };

      return this->is_this_repo_header;
  }


  bool Source_File_Dependency_Selector::Is_This_File_Aready_Searched(char * name){

       this->This_File_Exist = false;

       for(int i=0;i<this->Dep_Counter;i++){

           bool is_exist_on_the_list =

           this->CompareString(name,this->Dependent_List[i].Header_Name);

           if(is_exist_on_the_list){

              this->This_File_Exist = true;

              return this->This_File_Exist;
            }
        }

        return this->This_File_Exist;
  }

  void Source_File_Dependency_Selector::Determine_Header_Repo_Warehouse_Path(char ** wrd_path,

       char * file_name, char opr_sis){

       size_t name_size = strlen(file_name);

       size_t wrd_path_size = strlen(this->warehouse_head_dir);

       size_t path_size = name_size + wrd_path_size;

       *wrd_path = new char [5*path_size];

       size_t index = 0;

       for(size_t i=0;i<wrd_path_size;i++){

           (*wrd_path)[index] = this->warehouse_head_dir[i];

           index++;
       }

       if(opr_sis == 'w'){

         (*wrd_path)[index] = '\\';
       }
       else{

         (*wrd_path)[index] = '/';
       }

       index++;

       for(size_t i=0;i<name_size;i++){

           (*wrd_path)[index] = file_name[i];

           index++;
       }

       (*wrd_path)[index] = '\0';
  }

  void Source_File_Dependency_Selector::Extract_Header_File_Name_From_Decleration(char ** header_name,

       char * string){

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


  void Source_File_Dependency_Selector::Delete_Spaces_on_String(char ** pointer){

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

  void Source_File_Dependency_Selector::Construct_Temporary_String(char ** tmp_string,

       char * string){

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


  bool Source_File_Dependency_Selector::Include_Decleration_Test(char * string){

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


  bool Source_File_Dependency_Selector::CompareString(char * firstString, char * secondString){

       size_t firstStringLength  = this->CharListLength(firstString);

       size_t secondStringLength = this->CharListLength(secondString);

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

  size_t Source_File_Dependency_Selector::CharListLength(char * Characterlist){

      this->ListLength = 0;

      if((Characterlist[this->ListLength] != '\0') && (Characterlist[this->ListLength] != '\n') ){

          while((Characterlist[this->ListLength] != '\0') && (Characterlist[this->ListLength] != '\n')){

               this->ListLength++;
          }
      }

      return this->ListLength;
  }

  void Source_File_Dependency_Selector::Place_String(char ** str_pointer, char * string){

       size_t string_size = strlen(string);

       *str_pointer = new char [5*string_size];

       for(size_t i=0;i<string_size;i++){

           (*str_pointer)[i] = string[i];
       }

       (*str_pointer)[string_size] = '\0' ;
  }

  void Source_File_Dependency_Selector::Print_Dependency_List(){

       for(int i=0;i<this->Dep_Counter;i++){

           std::cout << "\n list - " << i << " " << this->Dependent_List[i].Header_Name;
       }
  }

  void Source_File_Dependency_Selector::Clear_Pointer_Memory(char ** Pointer){

       if(*Pointer != nullptr){

          delete [] *Pointer;

          *Pointer = nullptr;
       }
  }

  Header_Dependency * Source_File_Dependency_Selector::Get_Header_Dependency_List(){

        return this->Dependent_List;
  }

  char * Source_File_Dependency_Selector::Get_Dependent_Header(int i){

        return this->Dependent_List[i].Header_Name;
  }

  char * Source_File_Dependency_Selector::Get_Dependent_Header_Path(int i){

        return this->Dependent_List[i].repo_warehouse_path;
  }

  int Source_File_Dependency_Selector::Get_Dependency_List_Size(){

       return this->Dep_Counter;
  }
