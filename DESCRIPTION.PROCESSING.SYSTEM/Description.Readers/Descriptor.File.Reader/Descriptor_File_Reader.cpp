
#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(char * FilePATH) :

  Syntax_Controller(FilePATH), Data_Collector(FilePATH),
  StringManager(FilePATH),     FileManager(FilePATH)

{
   this->Initialize_Members();

   size_t path_size = strlen(FilePATH);

   this->descriptor_file_path = "";

   for(size_t i=0;i<path_size;i++){

       this->descriptor_file_path.append(1,FilePATH[i]);
   }

   this->Syntax_Controller.Control_Descriptor_File_Syntax();

   this->Data_Collector.Collect_Descriptor_File_Data();
}


Descriptor_File_Reader::Descriptor_File_Reader(std::string FilePATH) :

  Syntax_Controller(FilePATH), Data_Collector(FilePATH),
  StringManager(FilePATH),     FileManager(FilePATH)
{

   this->Initialize_Members();

   this->descriptor_file_path = FilePATH;

   this->Syntax_Controller.Control_Descriptor_File_Syntax();

   this->Data_Collector.Collect_Descriptor_File_Data();
}


Descriptor_File_Reader::~Descriptor_File_Reader(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}

void Descriptor_File_Reader::Initialize_Members(){

     this->root_dir  = "";
     this->standard  = "";
     this->options   = "";
     this->warehouse_location   = "";
     this->descriptor_file_path = "";
     this->include_dir_num     = 0;
     this->source_file_dir_num = 0;
     this->lib_dir_num         = 0;
     this->lib_file_num        = 0;
     this->Memory_Delete_Condition = true;
}


void Descriptor_File_Reader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(!this->Include_Directories.empty()){

            this->Include_Directories.clear();
         }

         if(!this->Source_File_Directories.empty()){

            this->Source_File_Directories.clear();
         }

         if(!this->Library_Directories.empty()){

            this->Library_Directories.clear();
         }

         if(!this->Library_Files.empty()){

            this->Library_Files.clear();
         }

         this->standard = "";

         this->options = "";

         this->warehouse_location = "";

         this->root_dir = "";
     }
}



void Descriptor_File_Reader::Read_Descriptor_File(){

     this->Read_Root_Directory_Location();

     this->Read_Warehouse_Location();

     this->Read_Standard();

     this->Read_Include_Directories();

     this->Read_Source_File_Directories();

     this->Read_Library_Directories();

     this->Read_Library_Files();

     this->Read_Options();
}


void Descriptor_File_Reader::Read_Root_Directory_Location(){

     int start_line = this->Data_Collector.Get_Root_Directory_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Root_Directory_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

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

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->root_dir = line;

            break;
         }
     }
}


void Descriptor_File_Reader::Read_Warehouse_Location(){

     int start_line = this->Data_Collector.Get_Warehouse_Location_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Warehouse_Location_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

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

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->warehouse_location = line;

            break;
         }
     }
}



void Descriptor_File_Reader::Read_Standard(){

     int start_line = this->Data_Collector.Get_Standard_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Standard_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

       std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

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

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->standard = line;

            break;
         }
     }
}




void Descriptor_File_Reader::Read_Include_Directories(){

     int start_line = this->Data_Collector.Get_Include_Directories_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Include_Directories_Record_Area(1);

     this->include_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->include_dir_num++;
         }
      }


      if(this->include_dir_num > 0){

         this->Memory_Delete_Condition = false;

         for(int i=0;i<this->include_dir_num;i++){

             this->Include_Directories.push_back("");
         }

         int record_index = 0;

         for(int i=start_line+1;i<end_line-1;i++){

             std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

             if(this->StringManager.CheckStringLine(line)){

                this->Include_Directories[record_index] = line;

                record_index++;
             }
          }
      }
}



void Descriptor_File_Reader::Read_Source_File_Directories(){


     int start_line = this->Data_Collector.Get_Source_File_Directories_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Source_File_Directories_Record_Area(1);

     this->source_file_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->source_file_dir_num++;
         }
     }


     if(this->source_file_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=0;i<this->source_file_dir_num;i++){

             this->Source_File_Directories.push_back("");
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

                this->Source_File_Directories[record_index] = line;

                record_index++;
            }
        }
     }
}



void Descriptor_File_Reader::Read_Library_Directories(){

     int start_line = this->Data_Collector.Get_Library_Directories_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Directories_Record_Area(1);

     this->lib_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

             this->lib_dir_num++;
         }
     }

     if(this->lib_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=0;i<this->lib_dir_num;i++){

            this->Library_Directories.push_back("");
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Library_Directories[record_index] = line;

                record_index++;
            }
        }
     }
}



void Descriptor_File_Reader::Read_Library_Files(){

     int start_line = this->Data_Collector.Get_Library_Files_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Files_Record_Area(1);

     this->lib_file_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

             this->lib_file_num++;
         }
     }

     if(this->lib_file_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=0;i<this->lib_file_num;i++){

            this->Library_Files.push_back("");
        }

        int record_index = 0;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Library_Files[record_index] = line;

               record_index++;
            }
        }
     }
}



void Descriptor_File_Reader::Read_Options(){


     int start_line = this->Data_Collector.Get_Options_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }
      }

      if(record_num < 1){

         this->options = "";   // There is no any decleration about the options
      }
      else{


           for(int i=start_line+1;i<end_line-1;i++){

               std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

               if(this->StringManager.CheckStringLine(line)){

                  this->options = line;

                  break;
               }
            }
      }
}

std::string Descriptor_File_Reader::Get_Library_Directory(int i){

        return this->Library_Directories[i];
}

std::string Descriptor_File_Reader::Get_Library_File(int i){

        return this->Library_Files[i];
}

std::string Descriptor_File_Reader::Get_Source_File_Directory(int i){

        return this->Source_File_Directories[i];
}


std::string Descriptor_File_Reader::Get_Include_Directory(int i){

       return this->Include_Directories[i];
}

std::string Descriptor_File_Reader::Get_Standard(){

      return this->standard;
}


std::string Descriptor_File_Reader::Get_Options(){

       return this->options;
}

std::string Descriptor_File_Reader::Get_Warehouse_Location(){

       return this->warehouse_location;
}

std::string Descriptor_File_Reader::Get_Repo_Directory_Location(){

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
