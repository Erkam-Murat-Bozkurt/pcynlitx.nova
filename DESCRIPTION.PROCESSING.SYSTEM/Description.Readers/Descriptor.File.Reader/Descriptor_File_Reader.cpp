
#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(){

    this->root_dir = nullptr;
    this->file_path = nullptr;
    this->standard = nullptr;
    this->options = nullptr;
    this->Include_Directories = nullptr;
    this->Source_File_Directories = nullptr;
    this->Library_Directories = nullptr;
    this->Library_Files = nullptr;
    this->warehouse_location = nullptr;
    this->Main_File_Names = nullptr;
    this->Executable_File_Names = nullptr;
    this->Memory_Delete_Condition = false;
    this->include_dir_num = 0;
    this->source_file_dir_num = 0;
    this->lib_dir_num = 0;
    this->lib_file_num = 0;
}


Descriptor_File_Reader::Descriptor_File_Reader(const Descriptor_File_Reader & orig){


}

Descriptor_File_Reader::~Descriptor_File_Reader(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}

void Descriptor_File_Reader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Include_Directories != nullptr){

            for(int i=0;i<this->include_dir_num;i++){

               delete [] this->Include_Directories[i];

               this->Include_Directories[i] = nullptr;
            }
         }

         if(this->Source_File_Directories != nullptr){

            for(int i=0;i<this->source_file_dir_num;i++){

               delete [] this->Source_File_Directories[i];

               this->Source_File_Directories[i] = nullptr;
            }
         }

         if(this->Library_Directories != nullptr){

            for(int i=0;i<this->lib_dir_num;i++){

               delete [] this->Library_Directories[i];

               this->Library_Directories[i] = nullptr;
            }
         }

         if(this->Library_Files != nullptr){

            for(int i=0;i<this->lib_file_num;i++){

               delete [] this->Library_Files[i];

               this->Library_Files[i] = nullptr;
            }
         }

         if(this->Main_File_Names != nullptr){

            for(int i=0;i<this->main_file_name_num;i++){

               delete [] this->Main_File_Names[i];

               this->Main_File_Names[i] = nullptr;
            }
         }

         if(this->Executable_File_Names != nullptr){

            for(int i=0;i<this->exec_file_name_num;i++){

               delete [] this->Executable_File_Names[i];

               this->Executable_File_Names[i] = nullptr;
            }
         }

         if(this->file_path != nullptr){

            delete [] this->file_path;
         }

         if(this->standard != nullptr){

            delete [] this->standard;
         }

         if(this->options != nullptr){

            delete [] this->options;
         }

         if(this->warehouse_location != nullptr){

            delete [] this->warehouse_location;
         }

         if(this->root_dir != nullptr){

            delete [] this->root_dir;
         }
     }
}


void Descriptor_File_Reader::Read_Descriptor_File(char * path){

     this->Receive_Descriptor_File_Path(path);

     this->Read_Root_Directory_Location();

     this->Read_Warehouse_Location();

     this->Read_Standard();

     this->Read_Include_Directories();

     this->Read_Source_File_Directories();

     this->Read_Library_Directories();

     this->Read_Library_Files();

     this->Read_Options();

     this->Read_Main_File_Names();

     this->Read_Executable_File_Names();
}

void Descriptor_File_Reader::Receive_Descriptor_File_Path(char * path){

     size_t path_size = strlen(path);

     this->file_path = new char [5*path_size];

     for(size_t i=0;i<path_size;i++){

        this->file_path[i] = path[i];
     }

     this->file_path[path_size] = '\0';

     this->StringManager.SetFilePath(this->file_path);

     this->Syntax_Controller.Control_Descriptor_File_Syntax(this->file_path);

     this->Data_Collector.Collect_Descriptor_File_Data(this->file_path);
}


void Descriptor_File_Reader::Read_Root_Directory_Location(){

     int start_line = this->Data_Collector.Get_Root_Directory_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Root_Directory_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         if(record_num > 1){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            std::cout << "\n There are multiple project root directory declerations";

            std::cout << "\n\n";

            exit(0);
         }
     }

     if(record_num == 0){

        std::cout << "\n\n";

        std::cout << "\n Error:";

        std::cout << "\n There is no any decleration about project root directory";

        std::cout << "\n\n";

        exit(0);
     }

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Place_String(&(this->root_dir),line);

            break;
         }
     }
}

void Descriptor_File_Reader::Read_Warehouse_Location(){

     int start_line = this->Data_Collector.Get_Warehouse_Location_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Warehouse_Location_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         if(record_num > 1){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            std::cout << "\n There are multiple project warehouse declerations";

            std::cout << "\n\n";

            exit(0);
         }
     }

     if(record_num == 0){

        std::cout << "\n\n";

        std::cout << "\n Error:";

        std::cout << "\n There is no any decleration about project warehouse location";

        std::cout << "\n\n";

        exit(0);
     }

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Place_String(&(this->warehouse_location),line);

            break;
         }
     }
}

void Descriptor_File_Reader::Read_Standard(){

     int start_line = this->Data_Collector.Get_Standard_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Standard_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         if(record_num > 1){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            std::cout << "\n There are multiple C++ standart declerations";

            std::cout << "\n\n";

            exit(0);
         }
     }

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            this->Place_String(&(this->standard),line);

            break;
         }
     }
}

void Descriptor_File_Reader::Read_Include_Directories(){

     int start_line = this->Data_Collector.Get_Include_Directories_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Include_Directories_Record_Area(1);

     this->include_dir_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            this->include_dir_num++;
         }
      }


      if(this->include_dir_num > 0){

         this->Include_Directories = new char * [5*this->include_dir_num];

         for(int i=0;i<this->include_dir_num;i++){

             this->Include_Directories[i] = nullptr;
         }

         int record_index = 0;

         for(int i=start_line+1;i<end_line;i++){

             char * line = this->StringManager.ReadFileLine(i);

             if(this->StringManager.CheckStringLine(line)){

                this->Place_String(&(this->Include_Directories[record_index]),line);

                record_index++;
             }
          }
      }
}

void Descriptor_File_Reader::Read_Source_File_Directories(){

     int start_line = this->Data_Collector.Get_Source_File_Directories_Record_Area(0);

     int end_line = this->Data_Collector.Get_Source_File_Directories_Record_Area(1);

     this->source_file_dir_num = 0;

     for(int i=start_line+1;i<end_line;i++){

        char * line = this->StringManager.ReadFileLine(i);

        if(this->StringManager.CheckStringLine(line)){

         this->source_file_dir_num++;
        }
     }

     if(this->source_file_dir_num > 0){


        this->Source_File_Directories = new char * [5*this->source_file_dir_num];

        for(int i=0;i<this->source_file_dir_num;i++){

            this->Source_File_Directories[i] = nullptr;
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line;i++){

            char * line = this->StringManager.ReadFileLine(i);

            if(this->StringManager.CheckStringLine(line)){

                this->Place_String(&(this->Source_File_Directories[record_index]),line);

                record_index++;
            }
        }
     }
}

void Descriptor_File_Reader::Read_Library_Directories(){

     int start_line = this->Data_Collector.Get_Library_Directories_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Directories_Record_Area(1);

     this->lib_dir_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

             this->lib_dir_num++;
         }
     }

     if(this->lib_dir_num > 0){

        this->Library_Directories = new char * [5*this->lib_dir_num];

        for(int i=0;i<this->lib_dir_num;i++){

            this->Library_Directories[i] = nullptr;
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line;i++){

            char * line = this->StringManager.ReadFileLine(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Place_String(&(this->Library_Directories[record_index]),line);

                record_index++;
            }
        }
     }
}

void Descriptor_File_Reader::Read_Library_Files(){

     int start_line = this->Data_Collector.Get_Library_Files_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Files_Record_Area(1);

     this->lib_file_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

             this->lib_file_num++;
         }
     }

     if(this->lib_file_num > 0){

        this->Library_Files = new char * [5*this->lib_file_num];

        for(int i=0;i<this->lib_file_num;i++){

            this->Library_Files[i] = nullptr;
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line;i++){

            char * line = this->StringManager.ReadFileLine(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Place_String(&(this->Library_Files[record_index]),line);

                record_index++;
            }
        }
     }
}

void Descriptor_File_Reader::Read_Options(){

     int start_line = this->Data_Collector.Get_Options_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         if(record_num > 1){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            std::cout << "\n There are multiple C++ options declerations";

            std::cout << "\n\n";

            exit(0);
          }
      }

      for(int i=start_line+1;i<end_line;i++){

          char * line = this->StringManager.ReadFileLine(i);

          if(this->StringManager.CheckStringLine(line)){

             this->Place_String(&(this->options),line);

             break;
          }
      }
}

void Descriptor_File_Reader::Read_Main_File_Names(){

     int start_line = this->Data_Collector.Get_Main_File_Name_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Main_File_Name_Record_Area(1);

     this->main_file_name_num = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

             this->main_file_name_num++;
         }
      }

      if(this->main_file_name_num > 0){

        this->Main_File_Names = new char * [5*this->main_file_name_num];

        for(int i=0;i<this->main_file_name_num;i++){

            this->Main_File_Names[i] = nullptr;
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line;i++){

            char * line = this->StringManager.ReadFileLine(i);

            if(this->StringManager.CheckStringLine(line)){

                this->Place_String(&(this->Main_File_Names[record_index]),line);

                record_index++;
            }
          }
       }
}

void Descriptor_File_Reader::Read_Executable_File_Names(){

  int start_line = this->Data_Collector.Get_Executable_File_Name_Record_Area(0);

  int end_line  = this->Data_Collector.Get_Executable_File_Name_Record_Area(1);

  this->exec_file_name_num = 0;

  for(int i=start_line+1;i<end_line;i++){

      char * line = this->StringManager.ReadFileLine(i);

      if(this->StringManager.CheckStringLine(line)){

          this->exec_file_name_num++;
      }
   }

   if(this->exec_file_name_num > 0){

     this->Executable_File_Names = new char * [5*this->exec_file_name_num];

     for(int i=0;i<this->exec_file_name_num;i++){

         this->Executable_File_Names[i] = nullptr;
     }

     int record_index = 0;

     for(int i=start_line+1;i<end_line;i++){

         char * line = this->StringManager.ReadFileLine(i);

         if(this->StringManager.CheckStringLine(line)){

             this->Place_String(&(this->Executable_File_Names[record_index]),line);

             record_index++;
         }
       }
    }

}

void Descriptor_File_Reader::Place_String(char ** pointer, char * string){

     size_t string_size = strlen(string);

     (*pointer) = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

         (*pointer)[i] = string[i];
     }

     (*pointer)[string_size] = '\0';
}


char ** Descriptor_File_Reader::Get_Library_Directories(){

        return this->Library_Directories;
}

char ** Descriptor_File_Reader::Get_Library_Files(){

        return this->Library_Files;
}

char ** Descriptor_File_Reader::Get_Source_File_Directories(){

        return this->Source_File_Directories;
}


char ** Descriptor_File_Reader::Get_Include_Directories(){

       return this->Include_Directories;
}

char ** Descriptor_File_Reader::Get_Main_File_Names(){

      return this->Main_File_Names;
}

char ** Descriptor_File_Reader::Get_Exe_File_Names(){

     return this->Executable_File_Names;
}

char * Descriptor_File_Reader::Get_Standard(){

      return this->standard;
}


char * Descriptor_File_Reader::Get_Options(){

       return this->options;
}

char * Descriptor_File_Reader::Get_Warehouse_Location(){

       return this->warehouse_location;
}

char * Descriptor_File_Reader::Get_Repo_Directory_Location(){

       return this->root_dir;
}

int Descriptor_File_Reader::Get_Library_Directory_Number(){

    return this->lib_dir_num;
}

int Descriptor_File_Reader::Get_Library_Files_Number(){

    return this->lib_file_num;
}

int Descriptor_File_Reader::Get_Source_File_Directory_Number(){

    return this->source_file_dir_num;
}

int Descriptor_File_Reader::Get_Include_Directory_Number(){

    return this->include_dir_num;
}

int Descriptor_File_Reader::Get_Main_File_Name_Number(){

    return this->main_file_name_num;
}

int Descriptor_File_Reader::Get_Exe_File_Name_Number(){

    return this->exec_file_name_num;
}
