


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

#include "Source_File_Information_Collector.hpp"

Source_File_Information_Collector::Source_File_Information_Collector(){

   this->Memory_Delete_Condition = true;

   this->Header_Data_Pointer = nullptr;

   this->Data_Ptr_CString = nullptr;

}

Source_File_Information_Collector::Source_File_Information_Collector(const

     Source_File_Information_Collector & orig){

}

Source_File_Information_Collector::~Source_File_Information_Collector(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Source_File_Information_Collector::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         delete [] this->warehouse_head_dir;

         delete [] this->warehouse_path;

         delete [] this->warehouse_obj_dir;

        if(this->Data_Ptr_CString != nullptr){

           for(int i=0;i<this->header_file_number;i++){

               if(this->Data_Ptr_CString[i].repo_path != nullptr){

                  delete [] this->Data_Ptr_CString[i].repo_path;
               }

               if(this->Data_Ptr_CString[i].header_name != nullptr){

                  delete [] this->Data_Ptr_CString[i].header_name;
               }

               if(this->Data_Ptr_CString[i].object_file_name != nullptr){

                  delete [] this->Data_Ptr_CString[i].object_file_name;
               }

               int inc_num = this->Data_Ptr_CString[i].inclusion_number;

               if(inc_num > 0){

                  for(int k=0;k<inc_num;k++){

                      if(this->Data_Ptr_CString[i].included_headers[k] != nullptr){

                         delete [] this->Data_Ptr_CString[i].included_headers[k];

                         delete [] this->Data_Ptr_CString[i].included_headers_path[k];
                      }
                  }

                  delete [] this->Data_Ptr_CString[i].included_headers;
               }
           }
        }

        this->Git_Data_Receiver.Clear_Dynamic_Memory();

        this->File_Lister_Pointer.Clear_Dynamic_Memory();
     }
}

void Source_File_Information_Collector::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->Des_Reader_Pointer = Des_Reader;

     this->warehouse_path = this->Des_Reader_Pointer->Get_Warehouse_Location();
}

void Source_File_Information_Collector::Collect_Make_File_Data(){

     this->Git_Data_Receiver.Receive_Descriptor_File_Reader(this->Des_Reader_Pointer);

     this->Git_Data_Receiver.Determine_Git_Repo_Info();

     this->File_Lister_Pointer.Determine_Git_Repo_Info(this->Des_Reader_Pointer);

     this->Determine_Warehouse_Header_Dir('w');

     this->Determine_Warehouse_Object_Dir('w');

     this->Determine_Header_File_List();

     this->Extract_Compiler_Data();
}

void Source_File_Information_Collector::Determine_Header_File_List(){

     size_t list_str_size = 0;

     int index_size = this->Git_Data_Receiver.Get_Git_File_Index_Size();

     for(int i=0;i<index_size;i++){

         char * path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_header = this->Header_Determiner.Is_Header(path);

         std::string space = " ";

         if(is_header){

            this->Header_Determiner.Determine_Header_File_Name_With_Extention(path);

            char * head_name = this->Header_Determiner.Get_Header_File_Name_With_Ext();

            char * header_path = nullptr;

            this->Determine_Header_Repo_Warehouse_Path(&header_path,head_name,'w');


            Headers_Data Temp_Data;

            size_t path_size = strlen(header_path);

            this->Place_String(&(Temp_Data.repo_path),header_path);


            size_t name_size = strlen(head_name);

            this->Place_String(&(Temp_Data.name),head_name);

            Temp_Data.inclusion_number = 0;

            Temp_Data.priority = 0;

            this->v_head_data.push_back(Temp_Data);

            delete header_path;
         }
      }
}

void Source_File_Information_Collector::Extract_Compiler_Data(){

     std::size_t dt_size = this->v_head_data.size();

     this->Memory_Delete_Condition = false;

     this->Data_Ptr_CString = new Compiler_Data_CString [5*dt_size];

     this->Initialize_Header_Data();

     for(std::size_t i = 0;i<dt_size;i++){

         std::string path = this->v_head_data[i].repo_path;

         char * c_path =nullptr;

         this->Convert_to_CString(&c_path,path);

         this->FileManager.Read_File_as_CString(c_path);

         int FileSize = this->FileManager.GetFileSize();

         for(int k=0;k<FileSize;k++){

             char * string = this->FileManager.GetFileLine(k);

             // In order to remove possible spaces on the string

             // a temporary string is constructed

             char * tmp_string = nullptr;

             this->Construct_Temporary_String(&tmp_string,string);

             this->Delete_Spaces_on_String(&tmp_string);


             bool is_include_decleration = this->Include_Decleration_Test(tmp_string);


             if(is_include_decleration){

                 this->v_head_data[i].inclusion_number++;
             }

             this->Clear_Pointer_Memory(&tmp_string);
          }


          this->Clear_Pointer_Memory(&c_path);
      }

      for(std::size_t i = 0;i<dt_size;i++){

          std::string path = this->v_head_data[i].repo_path;

          std::string name = this->v_head_data[i].name;

          int head_inc_number = this->v_head_data[i].inclusion_number;


          this->Place_CString(&(this->Data_Ptr_CString[i].repo_path),path);

          this->Place_CString(&(this->Data_Ptr_CString[i].header_name),name);

          bool is_indep = this->is_this_independent_header(name);

          if(is_indep){

            this->Data_Ptr_CString[i].object_file_name = nullptr;
          }
          else{

               this->Extract_Obj_File_Name_From_Header_Name(&(this->Data_Ptr_CString[i].object_file_name),name);
          }


          if(head_inc_number > 0){

             this->Data_Ptr_CString[i].included_headers = new char * [5*head_inc_number];

             this->Data_Ptr_CString[i].included_headers_path = new char * [5*head_inc_number];

             this->Data_Ptr_CString[i].inclusion_number = head_inc_number;

             this->Data_Ptr_CString[i].priority = head_inc_number;


             char * c_path =nullptr;

             this->Convert_to_CString(&c_path,path);

             this->FileManager.Read_File_as_CString(c_path);

             int FileSize = this->FileManager.GetFileSize();

             int inclusion_index = 0;

             for(int k=0;k<FileSize;k++){

                 char * string = this->FileManager.GetFileLine(k);

                 // In order to remove possible spaces on the string

                 // a temporary string is constructed

                 char * tmp_string = nullptr;

                 this->Construct_Temporary_String(&tmp_string,string);

                 this->Delete_Spaces_on_String(&tmp_string);

                 bool is_include_decleration = this->Include_Decleration_Test(tmp_string);


                 if(is_include_decleration){

                    char * header_name = nullptr;

                    this->Extract_Header_File_Name_From_Decleration(&header_name,tmp_string);

                    char ** header_address

                    = &(this->Data_Ptr_CString[i].included_headers[inclusion_index]);

                    this->Place_CString(header_address,header_name);

                    char ** header_path_address

                    = &(this->Data_Ptr_CString[i].included_headers_path[inclusion_index]);


                    this->Determine_Header_Repo_Warehouse_Path(header_path_address,header_name,'w');

                    inclusion_index++;

                    this->Clear_Pointer_Memory(&header_name);

                 }

                 this->Clear_Pointer_Memory(&tmp_string);
            }

            this->Clear_Pointer_Memory(&c_path);
          }
        }

        this->v_head_data.clear();
}

void Source_File_Information_Collector::Determine_Header_Repo_Warehouse_Path(char ** wrd_path,

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

void Source_File_Information_Collector::Extract_Header_File_Name_From_Decleration(char ** header_name,

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


void Source_File_Information_Collector::Delete_Spaces_on_String(char ** pointer){

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

void Source_File_Information_Collector::Construct_Temporary_String(char ** tmp_string,

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


bool Source_File_Information_Collector::Include_Decleration_Test(char * string){

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


void Source_File_Information_Collector::Determine_Warehouse_Header_Dir(char operating_sis){

     char warehouse_word   [] = "WAREHOUSE";

     char header_directory [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_dir_size = strlen(header_directory);

     size_t wr_word_size  = strlen(warehouse_word);

     size_t path_size = warehouse_path_size + head_dir_size + wr_word_size;

     this->warehouse_head_dir = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

        this->warehouse_head_dir[index] = this->warehouse_path[i];

        index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '\\'){

           this->warehouse_head_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

         if(this->warehouse_head_dir[warehouse_path_size-1] != '/'){

            this->warehouse_head_dir[index] = '/';

            index++;
         }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_head_dir[index] = warehouse_word[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '\\'){

           this->warehouse_head_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_head_dir[warehouse_path_size-1] != '/'){

           this->warehouse_head_dir[index] = '/';

           index++;
        }
     }

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir[index] = header_directory[i];

         index++;
     }

     this->warehouse_head_dir[index] = '\0';
}


void Source_File_Information_Collector::Determine_Warehouse_Object_Dir(char operating_sis){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     char warehouse_word   [] = "WAREHOUSE";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_dir_size = strlen(object_directory);

     size_t wr_word_size  = strlen(warehouse_word);


     size_t path_size = warehouse_path_size

            + object_dir_size + wr_word_size;


     this->warehouse_obj_dir = new char [5*path_size];

     int index = 0;

     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_obj_dir[index] = this->warehouse_path[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

            this->warehouse_obj_dir[index] = '/';

            index++;
        }
     }

     for(size_t i=0;i<wr_word_size;i++){

         this->warehouse_obj_dir[index] = warehouse_word[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->warehouse_path[warehouse_path_size-1] != '\\'){

           this->warehouse_obj_dir[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->warehouse_path[warehouse_path_size-1] != '/'){

           this->warehouse_obj_dir[index] = '/';

           index++;
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir[index] = object_directory[i];

         index++;
     }

     this->warehouse_obj_dir[index] = '\0';
}


void Source_File_Information_Collector::Clear_Pointer_Memory(char ** Pointer){

     if(*Pointer != nullptr){

        delete [] *Pointer;

        *Pointer = nullptr;
     }
 }

 void Source_File_Information_Collector::Convert_to_CString(char ** pointer, std::string path){

      if(*pointer != nullptr){

         delete [] *pointer;

         *pointer = nullptr;
      }

      size_t string_size = path.length();

      *pointer = new char [5*string_size];

      for(size_t i=0;i<5*string_size;i++){

          (*pointer)[i] = '\0';
      }

      for(size_t i=0;i<string_size;i++){

          (*pointer)[i] = path[i];
      }

      (*pointer)[string_size] = '\0';
  }


  void Source_File_Information_Collector::Print_Header_Data(){

       for(int i=0;i<this->header_file_number;i++){

           if(this->Data_Ptr_CString[i].header_name != nullptr){

              std::cout << "\n\n";

              std::cout << "\n Header Number:" << i;

              std::cout << "\n repo_path:  "   << this->Data_Ptr_CString[i].repo_path;

              std::cout << "\n header_name:" << this->Data_Ptr_CString[i].header_name;

              std::cout << "\n inclusion_number:"

              <<  this->Data_Ptr_CString[i].inclusion_number;

              std::cout << "\n\n";


              int inc_number = this->Data_Ptr_CString[i].inclusion_number;

              for(int k=0;k<inc_number;k++){

                  std::cout << "\n include header -" << k

                  << ":" << this->Data_Ptr_CString[i].included_headers[k];

                  std::cout << "\n include header path -" << k

                  << ":" << this->Data_Ptr_CString[i].included_headers_path[k];

                  std::cout << "\n\n";
              }

              std::cout << "\n\n";
           }
        }
  }


  void Source_File_Information_Collector::Initialize_Header_Data(){

       std::size_t dt_size = this->v_head_data.size();

       this->header_file_number = dt_size;

       for(int i=0;i<this->header_file_number;i++){

           this->Data_Ptr_CString[i].repo_path = nullptr;

           this->Data_Ptr_CString[i].header_name = nullptr;

           this->Data_Ptr_CString[i].inclusion_number = 0;

           this->Data_Ptr_CString[i].rcr_srch_complated = false;
       }
  }


  void Source_File_Information_Collector::Extract_Obj_File_Name_From_Header_Name(char ** object_name,

       std::string header_name){

       size_t header_name_size = header_name.length();

       *object_name = new char [5*header_name_size];

       for(size_t i=0;i<5*header_name_size;i++){

          (*object_name)[i] = '\0';
       }

      size_t index = 0;

      for(size_t i=0;i<header_name_size;i++){

          if(header_name[i] == '.'){

              break;
          }
          else{

            (*object_name)[index] = header_name[i];

            index++;
          }
      }

      (*object_name)[index] = '.';

      index++;

      (*object_name)[index] = 'o';

      index++;

      (*object_name)[index] = '\0';
  }

  bool Source_File_Information_Collector::is_this_independent_header(std::string header_name){

       char * cstring_header = nullptr;

       this->Convert_to_CString(&cstring_header,header_name);

       this->is_independent_header = false;

       int ind_header_num = this->File_Lister_Pointer.Get_Indenpendent_Header_Files_Number();

       for(int i=0;i<ind_header_num;i++){

           char * ind_header_path = this->File_Lister_Pointer.Get_Independent_Header_File(i);

           char * ind_header = nullptr;

           this->Extract_Header_File_Name_From_Path(ind_header_path,&ind_header,'w');

           bool is_equal = this->Char_Processor.CompareString(cstring_header,ind_header);

           this->Clear_Pointer_Memory(&ind_header);

           if(is_equal){

               this->is_independent_header = true;

               break;
           }
       }

       return this->is_independent_header;
  }

  void Source_File_Information_Collector::Extract_Header_File_Name_From_Path(char * path,

       char ** name, char opr_sis){

       size_t string_size = strlen(path);


       size_t header_name_size = 0;

       for(size_t i = string_size;i>0;i--){

           if(opr_sis == 'w'){

              if(path[i] == '\\'){

                 break;
              }
           }
           else{

             if(path[i] == '/'){

                break;
             }
           }

           header_name_size++;
       }


       *name = new char [5*header_name_size];

       size_t start_point = string_size - header_name_size + 1;

       size_t index = 0;

       for(size_t i = start_point;i<string_size;i++){

          (*name)[index] = path[i];

          index++;
       }

       (*name)[index] = '\0';
  }

  void Source_File_Information_Collector::Add_String(char ** list, char * string, int * index){

       size_t string_size = strlen(string);

       for(size_t i=0;i<string_size;i++){

           (*list)[(*index)] = string[i];

           (*index)++;
       }
  }

  void Source_File_Information_Collector::Place_String(std::string * str_pointer, char * string){

       size_t string_size = strlen(string);

       for(size_t i=0;i<string_size;i++){

           (*str_pointer).append(1,string[i]) ;
       }

       (*str_pointer).append(1,'\0') ;
  }

  void Source_File_Information_Collector::Place_CString(char ** str_pointer, std::string string){

       size_t string_size = string.length();

       *str_pointer = new char [5*string_size];

       for(size_t i=0;i<string_size;i++){

           (*str_pointer)[i] = string[i];
       }

       (*str_pointer)[string_size] = '\0' ;
  }

  void Source_File_Information_Collector::Place_CString(char ** str_pointer, char * string){

       size_t string_size = strlen(string);

       *str_pointer = new char [5*string_size];

       for(size_t i=0;i<string_size;i++){

           (*str_pointer)[i] = string[i];
       }

       (*str_pointer)[string_size] = '\0' ;
  }


  Compiler_Data_CString * Source_File_Information_Collector::Get_Compiler_Data(){

    return this->Data_Ptr_CString;
  }

  int Source_File_Information_Collector::Get_Compiler_Data_Size(){

      return this->header_file_number;
  }

  char * Source_File_Information_Collector::Get_Warehouse_Headers_Dir(){

         return this->warehouse_head_dir;
  }

  char * Source_File_Information_Collector::Get_Warehouse_Objetcs_Dir(){

         return this->warehouse_obj_dir;
  }

  char * Source_File_Information_Collector::Get_Warehouse_Path(){

         return this->warehouse_path;
  }
