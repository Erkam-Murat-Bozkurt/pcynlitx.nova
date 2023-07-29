
#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(char opr_sis) :

  Syntax_Controller(opr_sis), Data_Collector(opr_sis)
{
   this->Initialize_Members();
}


Descriptor_File_Reader::~Descriptor_File_Reader(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}


void Descriptor_File_Reader::Receive_Descriptor_File_Path(char * DesPATH){

     this->Data_Collector.Receive_Descriptor_File_Path(DesPATH);

     this->Syntax_Controller.Receive_Descriptor_File_Path(DesPATH);
}


void Descriptor_File_Reader::Receive_Descriptor_File_Path(std::string DesPATH){

     this->Data_Collector.Receive_Descriptor_File_Path(DesPATH);

     this->Syntax_Controller.Receive_Descriptor_File_Path(DesPATH);
}


void Descriptor_File_Reader::Initialize_Members(){

     this->include_dir_num     = 0;
     this->source_file_dir_num = 0;
     this->lib_dir_num         = 0;
     this->lib_file_num        = 0;
     this->Memory_Delete_Condition = false;
}


void Descriptor_File_Reader::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Vectory_Memory(&this->Include_Directories);

         this->Clear_Vectory_Memory(&this->Source_File_Directories);

         this->Clear_Vectory_Memory(&this->Library_Directories);

         this->Clear_Vectory_Memory(&this->Library_Files);

         this->Clear_String_Memory(&this->standard);

         this->Clear_String_Memory(&this->options);

         this->Clear_String_Memory(&this->warehouse_location);

         this->Clear_String_Memory(&this->root_dir);

         this->Data_Collector.Clear_Dynamic_Memory();

         this->Syntax_Controller.Clear_Dynamic_Memory();

         this->StringManager.Clear_Dynamic_Memory();
     }
}



void Descriptor_File_Reader::Read_Descriptor_File(){
     
     this->Syntax_Controller.Control_Descriptor_File_Syntax();

     this->Syntax_Controller.Clear_Dynamic_Memory();

     this->Data_Collector.Collect_Descriptor_File_Data();

     this->Read_Root_Directory_Location();

     this->Read_Warehouse_Location();

     this->Read_Standard();

     this->Read_Include_Directories();

     this->Read_Source_File_Directories();

     this->Read_Library_Directories();

     this->Read_Library_Files();

     this->Read_Options();

     this->Data_Collector.Clear_Dynamic_Memory();
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

     int end_line   = this->Data_Collector.Get_Include_Directories_Record_Area(1);

     this->include_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            this->include_dir_num++;
         }
      }

      if(this->include_dir_num > 0){

         this->Memory_Delete_Condition = false;

         for(int i=start_line+1;i<end_line-1;i++){

             std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

             if(this->StringManager.CheckStringLine(line)){

                this->Include_Directories.push_back(line);
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

         this->Clear_String_Memory(&line);
     }


     if(this->source_file_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

                this->Source_File_Directories.push_back(line);
            }

            this->Clear_String_Memory(&line);
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

         this->Clear_String_Memory(&line);
     }

     if(this->lib_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

              this->Library_Directories.push_back(line);
            }

            this->Clear_String_Memory(&line);
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

         this->Clear_String_Memory(&line);
     }

     if(this->lib_file_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Library_Files.push_back(line);
            }

            this->Clear_String_Memory(&line);
        }
     }
}



void Descriptor_File_Reader::Read_Options(){

     int start_line = this->Data_Collector.Get_Options_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         this->Clear_String_Memory(&line);
      }

      if(record_num < 1){

         this->options.clear();   // There is no any decleration about the options

         this->options.shrink_to_fit();
      }
      else{


           for(int i=start_line+1;i<end_line-1;i++){

               std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

               if(this->StringManager.CheckStringLine(line)){

                  this->options += line;

                  this->Clear_String_Memory(&line);

                  break;
               }

               this->Clear_String_Memory(&line);
            }
      }

      this->Divide_Options();
}


void Descriptor_File_Reader::Divide_Options(){

     if(!this->options.empty()){

        std::string temp_opts = this->options;

        
        if(!this->options.empty()){
        
           this->options.clear();

           this->options.shrink_to_fit();
        }


        size_t options_size = temp_opts.length();

        char space = ' ';

        int space_counter = 0;

        for(int i=0;i<options_size;i++){

           if(temp_opts[i] == ' '){

              space_counter++;
            }
        }

        int index = 0;

        if(space_counter>2){

           space_counter = 0;

           for(size_t i=0;i<options_size;i++){

               this->options.push_back(temp_opts[i]);

               if(temp_opts[i] == ' '){

                  space_counter++;
                }

                if(space_counter>2){

                   this->options.push_back('\\');

                   this->options.push_back('\n');

                   this->options.push_back('\t');

                   space_counter = 0;
                }
            }
          }
       }
}


void Descriptor_File_Reader::Clear_Vectory_Memory(std::vector<std::string> * pointer){

     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();

     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();

            it->shrink_to_fit();
        }
     }

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}

void Descriptor_File_Reader::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
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
