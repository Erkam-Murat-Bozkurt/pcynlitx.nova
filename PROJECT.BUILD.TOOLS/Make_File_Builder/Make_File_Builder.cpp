
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

   this->Class_Name = nullptr;

   this->Class_Header_File_Name = nullptr;

   this->Class_Object_File_Name = nullptr;

   this->Class_Source_File_Name = nullptr;

   this->Included_Header_Files = nullptr;

   this->Dependency_Code_Line = nullptr;

   this->Header_File_Directory = nullptr;

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

         if(this->Class_Name != nullptr){

            delete [] this->Class_Name;

            this->Class_Name = nullptr;
         }

         if(this->Class_Header_File_Name != nullptr){

            delete [] this->Class_Header_File_Name;

            this->Class_Header_File_Name = nullptr;
         }

         if(this->Class_Source_File_Name != nullptr){

            delete [] this->Class_Source_File_Name;

            this->Class_Source_File_Name = nullptr;
         }

         if(this->Class_Object_File_Name != nullptr){

            delete [] this->Class_Object_File_Name;

            this->Class_Object_File_Name = nullptr;
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

         if(this->Header_File_Path != nullptr){

            delete [] this->Header_File_Path;

            this->Header_File_Path = nullptr;
         }

         if(this->Header_File_Directory != nullptr){

            delete [] this->Header_File_Directory;

            this->Header_File_Directory = nullptr;
         }
     }
}



void Make_File_Builder::Receive_Header_File_Path(char * header_path){

     size_t header_path_size = strlen(header_path);

     this->Header_File_Path = new char [5*header_path_size];

     for(size_t i=0;i<header_path_size;i++){

         this->Header_File_Path[i] = header_path[i];
     }

     this->Header_File_Path[header_path_size] = '\0';
}

void Make_File_Builder::Determine_Header_File_Directory(char operating_sis){

     size_t header_path_size = strlen(this->Header_File_Path);

     this->Header_File_Directory = new char [5*header_path_size];

     size_t directory_size = header_path_size;

     for(size_t i=header_path_size;i>0;i--){

         if(operating_sis == 'w'){

            if(this->Header_File_Path[i] == '\\'){

                break;
            }
            else{

                directory_size--;
            }
         }

         if(operating_sis == 'l'){

            if(this->Header_File_Path[i] == '/'){

                break;
            }
            else{

                directory_size--;
            }
         }
     }

     for(size_t i=0;i<directory_size;i++){

          this->Header_File_Directory[i] = this->Header_File_Path[i];
     }

     this->Header_File_Directory[directory_size] = '\0';
}



void Make_File_Builder::Build_MakeFile(char * Head_Dir, char * obj_dir){

     this->Determine_Header_File_Directory('w');

     this->Find_Class_Name(this->Header_File_Directory);

     this->Determine_Included_Header_Files_Number();

     this->Read_Include_File_Names();

     this->Determine_Compiler_System_Command(this->Header_File_Directory);

     this->Determine_Dependency_Code_Line();

     this->FileManager.SetFilePath("auto_make_file.make");

     this->FileManager.FileOpen(RWCf);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("HEADERS_LOCATION=");

     this->FileManager.WriteToFile(Head_Dir);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("OBJECTS_LOCATION=");

     this->FileManager.WriteToFile(obj_dir);

     char * Current_Directory = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=");

     this->FileManager.WriteToFile(Current_Directory);

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

void Make_File_Builder::Find_Class_Name(char * Class_Directory){

     this->DirectoryManager.ChangeDirectory(Class_Directory);

      this->NameReader.ReadClassName(this->Header_File_Path);

      char * class_name = this->NameReader.getClassName();

      size_t class_name_size = strlen(class_name);

      this->Class_Name = new char [5*class_name_size];

      for(size_t i=0;i<class_name_size;i++){

          this->Class_Name[i] = class_name[i];
      }

      this->Class_Name[class_name_size] = '\0';

      this->NameReader.Clear_Dynamic_Memory();

     size_t Class_Name_Size = strlen(this->Class_Name);

     this->Class_Header_File_Name = new char [5*Class_Name_Size];

     int index = 0;

     for(size_t i=0;i<Class_Name_Size;i++){

         this->Class_Header_File_Name[index] = this->Class_Name[i];

         index++;
     }

     this->Class_Header_File_Name[index] = '.';

     index++;

     this->Class_Header_File_Name[index] = 'h';

     index++;

     this->Class_Header_File_Name[index] = '\0';

     this->Class_Object_File_Name = new char [5*Class_Name_Size];

     index = 0;

     for(int i=0;i<Class_Name_Size;i++){

         this->Class_Object_File_Name[index] = this->Class_Name[i];

         index++;
     }

     this->Class_Object_File_Name[index] = '.';

     index++;

     this->Class_Object_File_Name[Class_Name_Size+1] = 'o';

     index++;

     this->Class_Object_File_Name[Class_Name_Size+2] = '\0';

     index++;



     index = 0;

     this->Class_Source_File_Name = new char [5*Class_Name_Size];

     for(int i=0;i<Class_Name_Size;i++){

         this->Class_Source_File_Name[index] = this->Class_Name[i];

         index++;
     }

     this->Class_Source_File_Name[index] = '.';

     index++;

     this->Class_Source_File_Name[index] = 'c';

     index++;

     this->Class_Source_File_Name[index] = 'p';

     index++;

     this->Class_Source_File_Name[index] = 'p';

     index++;

     this->Class_Source_File_Name[index] = '\0';

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

     size_t Source_File_Name_Size = strlen(this->Class_Source_File_Name);

     size_t Header_File_Name_Size = strlen(this->Class_Header_File_Name);

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


     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,this->Class_Source_File_Name,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,new_line,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,tab,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);


     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Source_Location,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,slash,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,this->Class_Header_File_Name,&index_counter);

     this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);


     // The include commands definition

     int  sizer = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,include_word,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         this->Place_Information(&this->Compiler_System_Command,this->Included_Header_Files[i],&index_counter);

         this->Place_Information(&this->Compiler_System_Command,Space_Character,&index_counter);

         sizer++;

         if(((sizer >= 3) && (i!=(this->Included_Header_Files_Number -1)))){

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

     this->FileManager.SetFilePath(this->Header_File_Path);

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

                         std::cout << this->Class_Header_File_Name << " decleration..";

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

     this->FileManager.SetFilePath(this->Header_File_Path);

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

     size_t Object_File_Name_Size = strlen(this->Class_Object_File_Name);

     size_t Header_File_Name_Size = strlen(this->Class_Header_File_Name);

     size_t Source_File_Name_Size = strlen(this->Class_Source_File_Name);

     size_t Included_Header_Files_Name_Size = 0;

     for(int i=0;i<this->Included_Header_Files_Number;i++){

        Included_Header_Files_Name_Size = Included_Header_Files_Name_Size +

          strlen(this->Included_Header_Files[i]);
     }

     size_t Code_Line_Size = Object_File_Name_Size + Source_File_Name_Size +

                          Header_File_Name_Size + Included_Header_Files_Name_Size;

     this->Dependency_Code_Line =  new char [10*Code_Line_Size];

     int index_counter = 0;

     this->Place_Information(&this->Dependency_Code_Line,this->Class_Object_File_Name,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,double_quotes,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Class_Source_File_Name,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

     this->Place_Information(&this->Dependency_Code_Line,this->Class_Header_File_Name,&index_counter);

     int  sizer = 0;

     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     for(int i=0;i<this->Included_Header_Files_Number;i++){

         this->Place_Information(&this->Dependency_Code_Line,space,&index_counter);

         this->Place_Information(&this->Dependency_Code_Line,this->Included_Header_Files[i],&index_counter);

         sizer++;

         if(((sizer >= 3) && (i!=(this->Included_Header_Files_Number -1)))){

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
