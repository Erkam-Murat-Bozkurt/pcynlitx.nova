
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

#include "Make_File_Builder.h"

Make_File_Builder::Make_File_Builder(){

   this->Memory_Delete_Condition = false;

   this->Compiler_System_Command = nullptr;

   this->Header_File_Name_With_Ext = nullptr;

   this->Object_File_Name = nullptr;

   this->Source_File_Name_With_Ext = nullptr;

   this->Included_Header_Files = nullptr;

   this->Dependency_Code_Line = nullptr;

   this->Header_File_Directory = nullptr;

   this->Git_Header_File_Path = nullptr;

   this->Header_File_Exact_Path = nullptr;

   this->Source_File_Name = nullptr;

   this->Make_File_Name = nullptr;

   this->warehouse_path = nullptr;

   this->warehouse_head_dir = nullptr;

   this->warehouse_obj_dir = nullptr;

   this->repo_dir = nullptr;

   this->git_header_dir = nullptr;

   this->Included_Header_Files_Number = 0;
}

Make_File_Builder::Make_File_Builder(const Make_File_Builder & orig){

}

Make_File_Builder::~Make_File_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Make_File_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Source_File_Name_With_Ext != nullptr){

            delete [] this->Source_File_Name_With_Ext;

            this->Source_File_Name_With_Ext = nullptr;
         }

         if(this->Object_File_Name != nullptr){

            delete [] this->Object_File_Name;

            this->Object_File_Name = nullptr;
         }

         if(this->Compiler_System_Command != nullptr){

            delete [] this->Compiler_System_Command;

            this->Compiler_System_Command = nullptr;
         }

         if(this->Included_Header_Files != nullptr){

            for(int i=0;i<this->Included_Header_Files_Number;i++){

                delete [] this->Included_Header_Files[i];

                this->Included_Header_Files[i] = nullptr;
            }

            delete [] this->Included_Header_Files;
         }

         if(this->Dependency_Code_Line != nullptr){

            delete [] this->Dependency_Code_Line;

            this->Dependency_Code_Line = nullptr;
         }

         if(this->Git_Header_File_Path != nullptr){

            delete [] this->Git_Header_File_Path;

            this->Git_Header_File_Path = nullptr;
         }

         if(this->Header_File_Directory != nullptr){

            delete [] this->Header_File_Directory;

            this->Header_File_Directory = nullptr;
         }

         if(this->Make_File_Name != nullptr){

            delete [] this->Make_File_Name;

            this->Make_File_Name = nullptr;
         }

         if(this->warehouse_path != nullptr){

            delete [] this->warehouse_path;

            this->warehouse_path = nullptr;
         }

         if(this->warehouse_head_dir != nullptr){

            delete [] this->warehouse_head_dir;

            this->warehouse_head_dir = nullptr;
         }

         if(this->warehouse_obj_dir != nullptr){

            delete [] this->warehouse_obj_dir;

            this->warehouse_obj_dir = nullptr;
         }

         if(this->repo_dir != nullptr){

            delete [] this->repo_dir;

            this->repo_dir = nullptr;
         }

         if(this->git_header_dir != nullptr){

            delete [] this->git_header_dir;

            this->git_header_dir = nullptr;
          }

         if(this->Header_File_Exact_Path != nullptr){

             delete [] this->Header_File_Exact_Path;

             this->Header_File_Exact_Path = nullptr;
         }

         if(this->Source_File_Name != nullptr){

             delete [] this->Source_File_Name;

             this->Source_File_Name = nullptr;
         }


         if(this->Header_File_Name_With_Ext != nullptr){

            delete [] this->Header_File_Name_With_Ext;

            this->Header_File_Name_With_Ext = nullptr;
          }
     }
}

void Make_File_Builder::Receive_Repo_Directory(char * repo_dir){

      size_t repo_dir_size = strlen(repo_dir);

      this->repo_dir = new char [5*repo_dir_size];

      for(size_t i=0;i<repo_dir_size;i++){

          this->repo_dir[i] = repo_dir[i];
      }

      this->repo_dir[repo_dir_size] = '\0';

      if(this->repo_dir[repo_dir_size-1] == '\\'){

         this->repo_dir[repo_dir_size-1] = '\0';
      }
}

void Make_File_Builder::Receive_Git_Header_File_Path(char * header_path){

     size_t header_path_size = strlen(header_path);

     this->Git_Header_File_Path = new char [5*header_path_size];

     for(size_t i=0;i<header_path_size;i++){

         this->Git_Header_File_Path[i] = header_path[i];
     }

     this->Git_Header_File_Path[header_path_size] = '\0';
}

void Make_File_Builder::Receive_Warehouse_Path(char * warehouse_path){

     size_t warehouse_path_size = strlen(warehouse_path);

     this->warehouse_path = new char [5*warehouse_path_size];

     for(size_t i=0;i<warehouse_path_size;i++){

         this->warehouse_path[i] = warehouse_path[i];
     }

     this->warehouse_path[warehouse_path_size] = '\0';
}

void Make_File_Builder::Receive_Source_File_Name(char * Source_File_Name){

     size_t source_file_name_size = strlen(Source_File_Name);

     this->Source_File_Name = new char [5*source_file_name_size];

     for(size_t i=0;i<source_file_name_size;i++){

         this->Source_File_Name[i] = Source_File_Name[i];
     }

     this->Source_File_Name[source_file_name_size] = '\0';
}

void Make_File_Builder::Receive_Header_File_Name_With_Its_Extention(char * Header_File_Name){

     size_t header_file_name_size = strlen(Header_File_Name);

     this->Header_File_Name_With_Ext = new char [5*header_file_name_size];

     for(size_t i=0;i<header_file_name_size;i++){

         this->Header_File_Name_With_Ext[i] = Header_File_Name[i];
     }

     this->Header_File_Name_With_Ext[header_file_name_size] = '\0';
}

void Make_File_Builder::Determine_Warehouse_Header_Dir(char operating_sis){

     char header_directory [] = "PROJECT.HEADER.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t head_dir_size = strlen(header_directory);

     size_t path_size = warehouse_path_size + head_dir_size;

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

     for(size_t i=0;i<head_dir_size;i++){

         this->warehouse_head_dir[index] = header_directory[i];

         index++;
     }

     this->warehouse_head_dir[index] = '\0';
}

void Make_File_Builder::Determine_Warehouse_Object_Dir(char operating_sis){

     char object_directory [] = "PROJECT.OBJECT.FILES";

     size_t warehouse_path_size = strlen(this->warehouse_path);

     size_t object_dir_size = strlen(object_directory);

     size_t path_size = warehouse_path_size + object_dir_size;

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

            this->warehouse_head_dir[index] = '/';

            index++;
        }
     }

     for(size_t i=0;i<object_dir_size;i++){

         this->warehouse_obj_dir[index] = object_directory[i];

         index++;
     }

     this->warehouse_obj_dir[index] = '\0';
}

void Make_File_Builder::Determine_Header_File_Directory(char operating_sis){

     size_t repo_dir_size = strlen(this->repo_dir);

     size_t git_header_dir_size = strlen(this->git_header_dir);

     size_t header_dir_size = repo_dir_size + git_header_dir_size;

     this->Header_File_Directory = new char [5*header_dir_size];

     int index = 0;

     for(size_t i=0;i<repo_dir_size;i++){

         this->Header_File_Directory[index] = this->repo_dir[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->repo_dir[repo_dir_size -1] != '\\'){

           this->Header_File_Directory[index] = '\\';

           index++;
        }
     }

     if(operating_sis == 'l'){

        if(this->repo_dir[repo_dir_size -1] != '/'){

           this->Header_File_Directory[index] = '/';

           index++;
        }
      }

      for(size_t i=0;i<git_header_dir_size;i++){

         this->Header_File_Directory[index] = this->git_header_dir[i];

         index++;
     }

     this->Header_File_Directory[index] = '\0';
}

void Make_File_Builder::Determine_Header_File_Exact_Path(char operating_sis){

     size_t git_header_path_size = strlen(this->Git_Header_File_Path);

     size_t repo_dir_size = strlen(this->repo_dir);

     size_t exact_path_size = git_header_path_size + repo_dir_size;

     this->Header_File_Exact_Path = new char [5*exact_path_size];

     int index = 0;

     for(size_t i=0;i<repo_dir_size;i++){

         this->Header_File_Exact_Path[index] = this->repo_dir[i];

         index++;
     }

     if(operating_sis == 'w'){

        if(this->repo_dir[repo_dir_size -1] != '\\'){

           this->Header_File_Exact_Path[index] = '\\';

           index++;
         }
      }

      if(operating_sis == 'l'){

         if(this->repo_dir[repo_dir_size -1] != '/'){

            this->Header_File_Exact_Path[index] = '/';

            index++;
          }
      }

      for(size_t i=0;i<git_header_path_size;i++){

          this->Header_File_Exact_Path[index] = this->Git_Header_File_Path[i];

          index++;
      }

      this->Header_File_Exact_Path[index] = '\0';
}

void Make_File_Builder::Determine_Git_Header_File_Directory(char operating_sis){

     size_t git_header_path_size = strlen(this->Git_Header_File_Path);

     this->git_header_dir = new char [5*git_header_path_size];

     size_t header_dir_size = git_header_path_size;


     for(size_t i=git_header_path_size;i>0;i--){

          if(this->Git_Header_File_Path[i] == '/'){

              break;
          }
          else{

                header_dir_size--;
          }
      }

     if(operating_sis == 'w'){

        for(size_t i=0;i<header_dir_size;i++){

            this->git_header_dir[i] = this->Git_Header_File_Path[i];

            if(this->git_header_dir[i] == '/'){

               this->git_header_dir[i] = '\\';
            }
        }
     }

     if(operating_sis == 'l'){

       for(size_t i=0;i<header_dir_size;i++){

           this->git_header_dir[i] = this->Git_Header_File_Path[i];
       }
     }

     this->git_header_dir[header_dir_size] = '\0';
}

void Make_File_Builder::Build_MakeFile(char * repo_dir, char * warehouse_path, char * Git_Header_Path){

     this->Receive_Repo_Directory(repo_dir);

     this->Receive_Git_Header_File_Path(Git_Header_Path);

     this->Receive_Warehouse_Path(warehouse_path);

     this->Determine_Warehouse_Header_Dir('w');

     this->Determine_Warehouse_Object_Dir('w');

     this->Determine_Git_Header_File_Directory('w');

     this->Determine_Header_File_Directory('w');

     this->Determine_Header_File_Exact_Path('w');


     this->DirectoryManager.ChangeDirectory(this->Header_File_Directory);


     this->Find_File_Names_With_Extention();

     this->Determine_Included_Header_Files_Number();

     this->Read_Include_File_Names();

     this->Determine_Compiler_System_Command(this->Header_File_Directory);

     this->Determine_Dependency_Code_Line();

     this->Determine_Make_File_Name();

     this->DirectoryManager.ChangeDirectory(this->Header_File_Directory);

     this->FileManager.SetFilePath(this->Make_File_Name);

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("HEADERS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_head_dir);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("OBJECTS_LOCATION=");

     this->FileManager.WriteToFile(this->warehouse_obj_dir);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("REPO_DIRECTORY=");

     this->FileManager.WriteToFile(this->repo_dir);

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=$(REPO_DIRECTORY)\\");

     this->FileManager.WriteToFile(this->git_header_dir);

     char PathSpecifier [] = {'v','p','a','t','h',' ','%','\0'};

     char header_add [] = ".h";

     char object_add [] = ".o";

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);

     this->FileManager.WriteToFile(header_add);

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile("$(HEADERS_LOCATION)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);

     this->FileManager.WriteToFile(object_add);

     this->FileManager.WriteToFile(" ");

     this->FileManager.WriteToFile("$(OBJECTS_LOCATION)");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(this->Dependency_Code_Line);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(this->Compiler_System_Command);

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}

void Make_File_Builder::Find_File_Names_With_Extention(){

     size_t Source_File_Name_Size = strlen(this->Source_File_Name);

     this->Object_File_Name = new char [5*Source_File_Name_Size];

     int index = 0;

     for(int i=0;i<Source_File_Name_Size;i++){

         this->Object_File_Name[index] = this->Source_File_Name[i];

         index++;
     }

     this->Object_File_Name[index] = '.';

     index++;

     this->Object_File_Name[Source_File_Name_Size+1] = 'o';

     index++;

     this->Object_File_Name[Source_File_Name_Size+2] = '\0';



     index = 0;

     this->Source_File_Name_With_Ext = new char [5*Source_File_Name_Size];

     for(int i=0;i<Source_File_Name_Size;i++){

         this->Source_File_Name_With_Ext[index] = this->Source_File_Name[i];

         index++;
     }

     this->Source_File_Name_With_Ext[index] = '.';

     index++;

     this->Source_File_Name_With_Ext[index] = 'c';

     index++;

     this->Source_File_Name_With_Ext[index] = 'p';

     index++;

     this->Source_File_Name_With_Ext[index] = 'p';

     index++;

     this->Source_File_Name_With_Ext[index] = '\0';

}

void Make_File_Builder::Determine_Make_File_Name(){

     char make_file_extention [] = ".make";

     size_t class_name_size = strlen(this->Source_File_Name);

     size_t extention_size = strlen(make_file_extention);

     size_t file_name_size = class_name_size + extention_size;

     this->Make_File_Name = new char [5*file_name_size];

     int index = 0;

     for(size_t i=0;i<class_name_size;i++){

         this->Make_File_Name[index] = this->Source_File_Name[i];

         index++;
     }

     for(size_t i=0;i<extention_size;i++){

         this->Make_File_Name[index] = make_file_extention[i];

         index++;
     }

     this->Make_File_Name[index] = '\0';
}

void Make_File_Builder::Determine_Compiler_System_Command(char * Header_Files_Directory){

     char compiler_input_command [] = "g++ -Wall -c -std=c++17";

     char Include_Character [] = "-I";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(HEADERS_LOCATION)";

     char Source_Location [] ="$(SOURCE_LOCATION)";

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t Include_Directory_Name_Size = strlen(Header_Files_Directory);

     size_t Source_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Header_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Current_Directory_Name_Size = strlen(Current_Directory);

     int Included_Header_Files_Name_Size = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         Included_Header_Files_Name_Size = Included_Header_Files_Name_Size

          + strlen(this->Included_Header_Files[i]);
     }

     size_t compiler_input_command_size = strlen(compiler_input_command);

     size_t compiler_command_size = Include_Directory_Name_Size + Current_Directory_Name_Size +

                                    Header_File_Name_Size + Source_File_Name_Size +

                                    compiler_input_command_size +

                                    + Included_Header_Files_Name_Size;


     this->Compiler_System_Command = new char [10*compiler_command_size];

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     this->Place_Information(&this->Compiler_System_Command,compiler_input_command,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     this->Place_Information(&this->Compiler_System_Command,Include_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Headers_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Include_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,this->Source_File_Name_With_Ext,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,this->Header_File_Name_With_Ext,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     // The include commands definition

     int  sizer = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,this->Included_Header_Files[i],&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);

            this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

            sizer = 0;
          }
     }

     this->Compiler_System_Command[index_counter] = '\0';
}

void Make_File_Builder::Determine_Included_Header_Files_Number(){

     this->FileManager.SetFilePath(this->Header_File_Exact_Path);

     this->FileManager.FileOpen(Rf);

     this->Included_Header_Files_Number = 0;

     while(!this->FileManager.Control_End_of_File()){

            this->String_Line = this->FileManager.ReadLine();

            if(this->Include_Line_Determiner(this->String_Line)){

               for(size_t i=0;i<this->String_Line.length();i++){

                   if(this->String_Line[i] == '\"'){

                      this->Included_Header_Files_Number++;

                      int double_quotes_numner = 0;

                      for(size_t k = 0;k<this->String_Line.length();k++){

                          if(this->String_Line[k] == '\"'){

                              double_quotes_numner++;
                          }
                      }

                      if(double_quotes_numner < 2){

                         std::cout << "\n There is a syntax error in ";

                         std::cout << this->Header_File_Name_With_Ext << " decleration..";

                         std::cout << "\n\n Please check decleraiton ..";

                         std::cout << "\n\n The compiling process will be interrupted ..";

                         exit(0);
                      }

                      break;
                  }
               }
            }
       }

       this->FileManager.FileClose();
}

void Make_File_Builder::Read_Include_File_Names(){

     this->Included_Header_Files = new char * [5*this->Included_Header_Files_Number];

     this->FileManager.SetFilePath(this->Header_File_Exact_Path);

     this->FileManager.FileOpen(Rf);

     int Included_Header_Files_Index_Counter = 0;

     while(!this->FileManager.Control_End_of_File()){

            this->String_Line = this->FileManager.ReadLine();

            if(this->Include_Line_Determiner(this->String_Line)){

                for(size_t i=0;i<this->String_Line.length();i++){

                    if(this->String_Line[i] == '\"'){

                       int Next_Double_Quotation_Position = i+1;

                       while(this->String_Line[Next_Double_Quotation_Position]!= '\"'){

                             Next_Double_Quotation_Position++;
                       }

                       int Header_File_Name_Size = Next_Double_Quotation_Position - i;

                       this->Included_Header_Files[Included_Header_Files_Index_Counter]

                                        = new char [5*Header_File_Name_Size];


                       int index_counter = 0;

                       for(int k=i+1;k<Next_Double_Quotation_Position;k++){

                           this->Included_Header_Files[Included_Header_Files_Index_Counter][index_counter]

                            = this->String_Line[k];

                           index_counter++;
                       }

                       this->Included_Header_Files[Included_Header_Files_Index_Counter][index_counter] = '\0';

                       Included_Header_Files_Index_Counter++;

                       break;
                    }
              }
          }
     }

     this->FileManager.FileClose();
}

bool Make_File_Builder::Include_Line_Determiner(std::string String_Line){

     this->Include_Line_Condition = false;

     char Include_Word [] = {'i','n','c','l','u','d','e','\0'};

     size_t Include_Word_Character_Size = strlen(Include_Word);

     for(size_t i=0;i<String_Line.length();i++){

         if(String_Line[i] == Include_Word[0]){

            this->Include_Line_Condition = true;

            for(size_t k=0;k<Include_Word_Character_Size;k++){

               if(String_Line[i+k] != Include_Word[k]){

                  this->Include_Line_Condition = false;

                  break;
               }
            }

            break;
         }
     }

     return this->Include_Line_Condition;
}

void Make_File_Builder::Determine_Dependency_Code_Line(){

     char double_quotes [] = " : ";

     char space [] = " ";

     size_t Object_File_Name_Size = strlen(this->Object_File_Name);

     size_t Header_File_Name_Size = strlen(this->Header_File_Name_With_Ext);

     size_t Source_File_Name_Size = strlen(this->Source_File_Name_With_Ext);

     size_t Included_Header_Files_Name_Size = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

        Included_Header_Files_Name_Size = Included_Header_Files_Name_Size +

          strlen(this->Included_Header_Files[i]);
     }

     size_t Code_Line_Size = Object_File_Name_Size + Source_File_Name_Size +

                          Header_File_Name_Size + Included_Header_Files_Name_Size;

     this->Dependency_Code_Line =  new char [10*Code_Line_Size];

     int index_counter = 0;

     int  sizer = 0;

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     this->Place_Information(&this->Dependency_Code_Line,this->Object_File_Name,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,double_quotes,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Source_File_Name_With_Ext,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Header_File_Name_With_Ext,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);



     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

         this->Place_Information(&this->Dependency_Code_Line,this->Included_Header_Files[i],&index_counter);

         sizer++;

         if(((sizer >= 2) && (i!=(this->Included_Header_Files_Number -1)))){

            this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,slash,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,new_line,&index_counter);

            this->Place_Information(&this->Dependency_Code_Line,tab,&index_counter);

            sizer = 0;
         }
     }

     this->Dependency_Code_Line[index_counter] = '\0';
}

void Make_File_Builder::Place_Information(char ** Pointer, char * Information, int * index_counter){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         (*Pointer)[(*index_counter)] = Information[i];

         (*index_counter)++;
     }
 }
