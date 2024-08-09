
#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(char opr_sis, char build_type) :

   Data_Collector(opr_sis), Syntax_Controller(opr_sis)
{
   this->Initialize_Members();

   this->Memory_Delete_Condition = false;

   if(build_type == 'g'){

      this->Set_Gui_Read_Status(true);
   }
   else{

      this->Set_Gui_Read_Status(false);
   }

   this->Data_Record_Cond = false;

   this->gui_syntax_error = false;

   this->gui_read_success = true;

   this->is_project_file_invalid = false;
}


Descriptor_File_Reader::~Descriptor_File_Reader(){

    if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
    }
}

void Descriptor_File_Reader::Set_Gui_Read_Status(bool status){

     this->gui_read_status = status;

     this->Syntax_Controller.Set_Gui_Read_Status(status);
}

void Descriptor_File_Reader::Receive_Descriptor_File_Path(char * DesPATH){

     this->Memory_Delete_Condition = false;

     this->Data_Collector.Receive_Descriptor_File_Path(DesPATH);

     this->Syntax_Controller.Receive_Descriptor_File_Path(DesPATH);

     size_t path_size = strlen(DesPATH);

     for(size_t i=0;i<path_size;i++){

        this->descriptor_file_path.push_back(DesPATH[i]);
     }

     this->descriptor_file_path.shrink_to_fit();
}


void Descriptor_File_Reader::Receive_Descriptor_File_Path(std::string DesPATH){

     this->Memory_Delete_Condition = false;

     this->Data_Collector.Receive_Descriptor_File_Path(DesPATH);

     this->Syntax_Controller.Receive_Descriptor_File_Path(DesPATH);

     size_t path_size = DesPATH.length();

     for(size_t i=0;i<path_size;i++){

        this->descriptor_file_path.push_back(DesPATH[i]);
     }

     this->descriptor_file_path.shrink_to_fit();
}


void Descriptor_File_Reader::Receive_Data_Record_Condition(bool cond){

     this->Data_Record_Cond = cond;
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

         this->Clear_Vectory_Memory(&this->compiler_options);

         this->Clear_Vectory_Memory(&this->linker_options);

         this->Clear_String_Memory(&this->standard);

         this->Clear_String_Memory(&this->warehouse_location);

         this->Clear_String_Memory(&this->root_dir);

         this->Clear_String_Memory(&this->descriptor_file_path);

         this->Clear_String_Memory(&this->build_system);

         this->Clear_String_Memory(&this->project_name);

         this->Clear_String_Memory(&this->version_number);

         this->Data_Collector.Clear_Dynamic_Memory();

         this->Syntax_Controller.Clear_Dynamic_Memory();

         this->StringManager.Clear_Dynamic_Memory();

         this->is_project_file_invalid = false;

         this->gui_syntax_error = false;
     }
}



void Descriptor_File_Reader::Read_Descriptor_File(){
     
     this->Memory_Delete_Condition = false;

     this->gui_syntax_error = false;

     this->is_project_file_invalid = false;

     this->Syntax_Controller.Control_Descriptor_File_Syntax();

     if(this->Syntax_Controller.GetSyntaxErrorStatus()){

        this->gui_syntax_error = true;

        if(this->Syntax_Controller.Get_Invalid_Descriptor_File_Status()){

           this->is_project_file_invalid = true;
        }

        this->Syntax_Controller.Clear_Dynamic_Memory();
     }
     else{

          this->Syntax_Controller.Clear_Dynamic_Memory();

          this->Data_Collector.Collect_Descriptor_File_Data();

          if(!this->gui_read_status){

              this->Read_Root_Directory_Location();

              this->Read_Warehouse_Location();

              this->Read_Standard();

              this->Read_Include_Directories();

              this->Read_Source_File_Directories();

              this->Read_Library_Directories();

              this->Read_Library_Files();

              this->Read_Compiler_Options();

              this->Read_Linker_Options();

              this->Read_Build_System_Type();

              this->Read_Project_Name();

              this->Read_Version_Number();
          }
          else{

               if(!this->is_project_file_invalid){

                  if(!this->gui_syntax_error){

                      this->Read_Root_Directory_Location();

                      this->Read_Warehouse_Location();

                      this->Read_Standard();

                      this->Read_Include_Directories();

                      this->Read_Source_File_Directories();

                      this->Read_Library_Directories();

                      this->Read_Library_Files();

                      this->Read_Compiler_Options();

                      this->Read_Linker_Options();
             
                      this->Read_Build_System_Type();

                      this->Read_Project_Name();

                      this->Read_Version_Number();
                  }
               }
           }
     }

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

         if((record_num > 1) && (this->Data_Record_Cond == false)){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            this->Clear_String_Memory(&this->error_message);

            this->error_message =  "\nThere are multiple project root directory declerations";

            std::cout << this->error_message;

            std::cout << "\n\n";

            if(!this->gui_read_status){

               exit(0);
            }
            else{

                this->gui_read_success = false;
            }
         }
     }


     if((record_num == 0) && (this->Data_Record_Cond == false)){

        std::cout << "\n\n";

        std::cout << "\n Error:";

        this->Clear_String_Memory(&this->error_message);

        this->error_message = "\nThere is no any decleration about project root directory";

        std::cout << this->error_message;

        std::cout << "\n\n";

        if(!this->gui_read_status){

            exit(0);
        }
        else{

            this->gui_read_success = false;
        }

     }


     if(this->gui_read_status){

        if(this->gui_read_success){

           if(record_num >0){

              for(int i=start_line+1;i<end_line-1;i++){

                  std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                  if(this->StringManager.CheckStringLine(line)){

                    if(this->Is_Include_Character(line)){

                       this->Delete_Spaces_on_String(&line);

                       this->root_dir = line;

                       break;
                    }
                  }
              }
            }
        }
     }
     else{

         if(record_num >0){

           for(int i=start_line+1;i<end_line-1;i++){

               std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

               if(this->StringManager.CheckStringLine(line)){

                  if(this->Is_Include_Character(line)){

                     this->Delete_Spaces_on_String(&line);

                     this->root_dir = line;

                     break;
                  }
               }
           }
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

         if((record_num > 1)  && (this->Data_Record_Cond == false)){

            std::cout << "\n\n";

            std::cout << "\n Error:";

            this->Clear_String_Memory(&this->error_message);

            this->error_message = "\n There are multiple project warehouse declerations";

            std::cout << this->error_message;

            std::cout << "\n\n";


            if(!this->gui_read_status){

               exit(0);
            }
            else{

                this->gui_read_success = false;
            }
         }
     }

     if((record_num == 0) && (this->Data_Record_Cond == false)) {

        std::cout << "\n\n";

        std::cout << "\n Error:";

        this->Clear_String_Memory(&this->error_message);

        this->error_message = "\nThere is no any decleration about project warehouse location";

        std::cout << this->error_message;

        std::cout << "\n\n";

        if(!this->gui_read_status){

            exit(0);
        }
        else{

            this->gui_read_success = false;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   if(this->Is_Include_Character(line)){

                      this->Delete_Spaces_on_String(&line);

                      this->warehouse_location = line;

                      break;
                   }
                }
            }
        }
     }
     else{
           
            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   if(this->Is_Include_Character(line)){

                       this->Delete_Spaces_on_String(&line);

                       this->warehouse_location = line;

                       break;
                   }
                }
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

         if((record_num > 1) && (this->Data_Record_Cond == false)) {

            std::cout << "\n\n";

            std::cout << "\n Error:";

            this->Clear_String_Memory(&this->error_message);

            this->error_message =  "\nThere are multiple C++ standart declerations";

            std::cout << this->error_message;

            std::cout << "\n\n";

            if(!this->gui_read_status){

               exit(0);
            }
            else{

                  this->gui_read_success = false;
            }
         }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){
          
          for(int i=start_line+1;i<end_line-1;i++){

              std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

              if(this->StringManager.CheckStringLine(line)){

                 this->Delete_Spaces_on_String(&line);

                 this->standard = line;

                 break;
              }
           }
        }
     }
     else{

            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->standard = line;

                   break;
                }
            }      
     }
}





void Descriptor_File_Reader::Read_Build_System_Type(){

     int start_line = this->Data_Collector.Get_Build_System_Type_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Build_System_Type_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }
     }

     if((record_num == 0) && (this->Data_Record_Cond == false)) {

        std::cout << "\n\n";

        std::cout << "\n Error:";

        this->Clear_String_Memory(&this->error_message);

        this->error_message = "\nThere is no any decleration about build system type selection";

        std::cout << this->error_message;

        std::cout << "\n\n";

        if(!this->gui_read_status){

            exit(0);
        }
        else{

            this->gui_read_success = false;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->build_system = line;

                   break;
                }
            }
        }
     }
     else{
           
            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->build_system = line;

                   break;
                }
            }
     }

}




void Descriptor_File_Reader::Read_Project_Name(){

     this->Clear_String_Memory(&this->project_name);

     int start_line = this->Data_Collector.Get_Project_Name_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Project_Name_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);
         
         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }
     }


     if((record_num == 0) && (this->Data_Record_Cond == false)) {

        std::cout << "\n\n";

        std::cout << "\n Error:";

        this->Clear_String_Memory(&this->error_message);

        this->error_message = "\nThere is no any decleration about project name";

        std::cout << this->error_message;

        std::cout << "\n\n";

        if(!this->gui_read_status){

            exit(0);
        }
        else{

            this->gui_read_success = false;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->project_name = line;

                   break;
                }
            }
        }
     }
     else{
           
            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->project_name = line;

                   break;
                }
            }
     }

}



void Descriptor_File_Reader::Read_Version_Number(){

     this->Clear_String_Memory(&this->version_number);

     int start_line = this->Data_Collector.Get_Version_Number_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Version_Number_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }
     }

     if((record_num == 0) && (this->Data_Record_Cond == false)) {

        std::cout << "\n\n";

        std::cout << "\n Error:";

        this->Clear_String_Memory(&this->error_message);

        this->error_message = "\nThere is no any decleration about version number";

        std::cout << this->error_message;

        std::cout << "\n\n";

        if(!this->gui_read_status){

            exit(0);
        }
        else{

            this->gui_read_success = false;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->Delete_Spaces_on_String(&line);

                   this->version_number = line;

                   break;
                }
            }
        }
     }
     else{
           
            for(int i=start_line+1;i<end_line-1;i++){

                std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

                if(this->StringManager.CheckStringLine(line)){

                   this->version_number = line;

                   break;
                }
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

            if(this->Is_Include_Character(line)){

               this->include_dir_num++;
            }
         }
      }

      if(this->include_dir_num > 0){

         this->Memory_Delete_Condition = false;

         for(int i=start_line+1;i<end_line-1;i++){

             std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

             if(this->StringManager.CheckStringLine(line)){

                this->Delete_Spaces_on_String(&line);

                if(this->Is_Include_Character(line)){

                   this->Include_Directories.push_back(line);
                }
             }
          }
      }

      this->Include_Directories.shrink_to_fit();

      this->include_dir_num = this->Include_Directories.size();
}



void Descriptor_File_Reader::Read_Source_File_Directories(){

     int start_line = this->Data_Collector.Get_Source_File_Directories_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Source_File_Directories_Record_Area(1);

     this->source_file_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->source_file_dir_num++;
            }
         }

         this->Clear_String_Memory(&line);
     }


     if(this->source_file_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               this->Delete_Spaces_on_String(&line);

               if(this->Is_Include_Character(line)){

                  this->Source_File_Directories.push_back(line);
               }
            }

            this->Clear_String_Memory(&line);
        }
     }

     this->Source_File_Directories.shrink_to_fit();

     this->source_file_dir_num = this->Source_File_Directories.size();
}



void Descriptor_File_Reader::Read_Library_Directories(){

     int start_line = this->Data_Collector.Get_Library_Directories_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Directories_Record_Area(1);

     this->lib_dir_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               this->lib_dir_num++;
            }
         }

         this->Clear_String_Memory(&line);
     }

     if(this->lib_dir_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               if(this->Is_Include_Character(line)){

                  this->Delete_Spaces_on_String(&line);

                  this->Library_Directories.push_back(line);
               }
            }

            this->Clear_String_Memory(&line);
        }
     }

     this->Library_Directories.shrink_to_fit();

     this->lib_dir_num = this->Library_Directories.size();
}



void Descriptor_File_Reader::Read_Library_Files(){

     int start_line = this->Data_Collector.Get_Library_Files_Record_Area(0);

     int end_line  = this->Data_Collector.Get_Library_Files_Record_Area(1);

     this->lib_file_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

             if(this->Is_Include_Character(line)){

                this->lib_file_num++;
             }
         }

         this->Clear_String_Memory(&line);
     }

     if(this->lib_file_num > 0){

        this->Memory_Delete_Condition = false;

        for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector.Get_Descriptor_File_Line(i);

            if(this->StringManager.CheckStringLine(line)){

               if(this->Is_Include_Character(line)){

                  this->Delete_Spaces_on_String_Start(&line);

                  if(this->Is_There_Multiple_Decleration_on_Same_Line(line)){

                     std::vector<std::string> multi_line;

                     this->Extract_Declerations_Performing_on_Same_Line(line,multi_line);

                     for(size_t k=0;k<multi_line.size();k++){

                         this->Library_Files.push_back(multi_line.at(k));
                     }
                  }
                  else{

                       this->Library_Files.push_back(line);
                  }
               }
            }

            this->Clear_String_Memory(&line);
        }
     }

     this->Library_Files.shrink_to_fit();

     this->lib_file_num = this->Library_Files.size();
}



void Descriptor_File_Reader::Read_Compiler_Options(){

     int start_line = this->Data_Collector.Get_Compiler_Options_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Compiler_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               record_num++;
            }
         }

         this->Clear_String_Memory(&line);
      }
         
      if(record_num < 1){

         this->compiler_options.clear();   // There is no any decleration about the options

         this->compiler_options.shrink_to_fit();
      }
      else{

           for(int i=start_line+1;i<end_line-1;i++){

               std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

               while(line[0] == ' '){

                     line.erase(0,1);
               }


               if(this->StringManager.CheckStringLine(line)){

                  if(this->Is_Include_Character(line)){

                     for(size_t j=0;j<line.size();j++){

                         if(line.at(j)=='\\'){

                            line.erase(j,1);

                            line.shrink_to_fit();
                         }
                     }

                     
                     if(this->Is_There_Multiple_Decleration_on_Same_Line(line)){

                        std::vector<std::string> multi_line;

                        this->Extract_Declerations_Performing_on_Same_Line(line,multi_line);

                        for(size_t k=0;k<multi_line.size();k++){

                            this->compiler_options.push_back(multi_line.at(k));
                        }
                     }
                     else{

                          this->compiler_options.push_back(line);
                     }

                     //this->compiler_options.push_back(line);

                     this->Clear_String_Memory(&line);
                  }
               }
            }
      }

      //this->Divide_Options(this->compiler_options);

      this->compiler_options.shrink_to_fit();
}




void Descriptor_File_Reader::Read_Linker_Options(){

     int start_line = this->Data_Collector.Get_Linker_Options_Record_Area(0);

     int end_line   = this->Data_Collector.Get_Linker_Options_Record_Area(1);

     int record_num = 0;

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            record_num++;
         }

         this->Clear_String_Memory(&line);
      }
   
      if(record_num < 1){

         this->linker_options.clear();   // There is no any decleration about the options

         this->linker_options.shrink_to_fit();
      }
      else{


           for(int i=start_line+1;i<end_line-1;i++){

               std::string line = this->Data_Collector.Get_Descriptor_File_Line_With_Spaces(i);

               while(line[0] == ' '){

                     line.erase(0,1);
               }

               if(this->StringManager.CheckStringLine(line)){

                  if(this->Is_Include_Character(line)){

                    for(size_t j=0;j<line.size();j++){

                      if(line.at(j)=='\\'){

                         line.erase(j,1);

                         line.shrink_to_fit();
                       }
                     }

                     if(this->Is_There_Multiple_Decleration_on_Same_Line(line)){

                        std::vector<std::string> multi_line;

                        this->Extract_Declerations_Performing_on_Same_Line(line,multi_line);

                        for(size_t k=0;k<multi_line.size();k++){

                            this->linker_options.push_back(multi_line.at(k));
                        }
                     }
                     else{

                          this->linker_options.push_back(line);
                     }

                    this->Clear_String_Memory(&line);
                  }
               }
            }
      }

      this->linker_options.shrink_to_fit();
}


void Descriptor_File_Reader::Divide_Options(std::string & options){

     int space_car_num = 0, standard_char = 0;

     if(!options.empty()){

        std::string temp_opts = options;

        temp_opts.shrink_to_fit();


        if(!options.empty()){
        
            options.clear();

            options.shrink_to_fit();
        }


        while(temp_opts[0] == ' '){

              temp_opts.erase(0,1);
        }

        temp_opts.shrink_to_fit();

        size_t options_size = temp_opts.length();

        int space_counter = 0;

        for(size_t i=0;i<options_size;i++){

           if(temp_opts[i] == ' '){

              int index = i+1;

              while(temp_opts[index] == ' '){

                    temp_opts.erase(index,1);
              }

              temp_opts.shrink_to_fit();

              space_car_num++;
            }
        }

        temp_opts.shrink_to_fit();

        options_size = temp_opts.size();

        for(size_t i=0;i<options_size;i++){

           if(temp_opts[i] == ' '){

              space_car_num++;
            }
        }

        if(space_car_num>3){

           space_counter = 0;

           int start_point = 0;

           while(temp_opts[start_point] == ' '){

                 start_point++;
           }

           for(size_t i=start_point;i<options_size;i++){

               options.push_back(temp_opts[i]);

               if((temp_opts[i] != ' ') && (temp_opts[i] != '\n')){

                  standard_char++;
               }

               if(temp_opts[i+1] == ' '){

                  space_car_num++;
               }

               if((temp_opts[i+2] != ' ') && (temp_opts[i+2] != '\n')){

                  standard_char++;
               }

               if((space_car_num > 0) && (standard_char >1 )){

                  space_counter++;

                  space_car_num =0;

                  standard_char =0;                
               }

               if(space_car_num > 1){

                  space_car_num = 1;
               }

               if(temp_opts[i] == '\n'){

                  space_counter=0;
               }


                if(space_counter>=3){

                   options.push_back(' ');

                   options.push_back('\\');

                   options.push_back('\n');

                   options.push_back(' ');

                   space_counter = 0;
                }

                options.shrink_to_fit();
            }
          }
          else{

               options = temp_opts;
          }
       }

       options.shrink_to_fit();
}



bool Descriptor_File_Reader::Is_Include_Character(std::string str){

     bool is_include = false;

     for(size_t i=0;i<str.length();i++){

         if((str.at(i) != ' ') && (str.at(i) != '\n')){

              is_include = true;

              return is_include;
         }
     }

     return is_include;
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



void Descriptor_File_Reader::Delete_Spaces_on_String_Start(std::string * str)
{
     while(str->at(0) == ' '){

           str->erase(0,1);
     }
}


void Descriptor_File_Reader::Delete_Spaces_on_String(std::string * str)
{
    bool search_cond = true;

    do{

        search_cond = false;

        for(size_t i=0;i<str->length();i++){

           if( ((*str)[i] == ' ') || ((*str)[i] == '\t') ){

              search_cond = true;

              str->erase(i,1);
           }
        }

    }while(search_cond);
}


bool Descriptor_File_Reader::Is_There_Multiple_Decleration_on_Same_Line(std::string & str_line){

     // This function also trims the spaces onthe beginning and the end of the string

     bool multiple_dec_status = false;

     while(str_line.at(0) == ' '){

           str_line.erase(0,1);
     }

     str_line.shrink_to_fit();


     while(str_line.at(str_line.size()-1) == ' '){

           str_line.erase(str_line.size()-1,1);

           str_line.shrink_to_fit();
     }


     int space_number=0;

     for(size_t i=0;i<str_line.size();i++){

         if(str_line.at(i) == ' '){

             space_number++;
         }
     }

     if(space_number>0){

         multiple_dec_status = true;
     }

     return multiple_dec_status;
}


void Descriptor_File_Reader::Extract_Declerations_Performing_on_Same_Line(std::string str_line, 
 
      std::vector<std::string> & mt_line){

      int space_counter = 0;

      for(size_t i=0;i<str_line.size();i++){

          if(str_line[i] == ' '){

             space_counter++;
          }
      }

      space_counter++;

      for(size_t i=0;i<str_line.size();i++){

          std::string temp;

          for(size_t j=i;j<str_line.size();j++){

              if(j == (str_line.size()-1)){

                 space_counter--;

                 i=j;
              }

              if(str_line[j] != ' '){

                 temp.push_back(str_line[j]);
              }
              else{

                  i=j;

                  space_counter--;

                  break;
              }
          }

          mt_line.push_back(temp);

          if(space_counter <=0){

             break;
          }
      }

      mt_line.shrink_to_fit();
 }


const std::vector<std::string> & Descriptor_File_Reader::Get_Include_Directories(){

    return this->Include_Directories;
}

const std::vector<std::string> & Descriptor_File_Reader::Get_Library_Directories(){

     return this->Library_Directories;
}

const std::vector<std::string> & Descriptor_File_Reader::Get_Source_File_Directories(){

     return this->Source_File_Directories;
}

const std::vector<std::string> & Descriptor_File_Reader::Get_Library_Files(){

     return this->Library_Files;
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


const std::vector<std::string> & Descriptor_File_Reader::Get_Compiler_Options(){

       return this->compiler_options;
}

const std::vector<std::string> & Descriptor_File_Reader::Get_Linker_Options(){

       return this->linker_options;
}

std::string Descriptor_File_Reader::Get_Warehouse_Location(){

       return this->warehouse_location;
}

std::string Descriptor_File_Reader::Get_Repo_Directory_Location(){

       return this->root_dir;
}

std::string Descriptor_File_Reader::Get_Descriptor_File_Path(){

     return this->descriptor_file_path;
}


std::string Descriptor_File_Reader::Get_Build_System_Type(){

     return this->build_system;
}

std::string Descriptor_File_Reader::Get_Project_Name(){

     return this->project_name;
}

std::string Descriptor_File_Reader::Get_Version_Number(){

     return this->version_number;
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


bool Descriptor_File_Reader::Get_Gui_Read_Success_Status(){

     return this->gui_read_success;
}

std::string Descriptor_File_Reader::Get_Error_Message(){

     return this->error_message;
}


bool Descriptor_File_Reader::Get_Gui_Read_Status(){

     return this->gui_read_status;
}

bool Descriptor_File_Reader::Get_Syntax_Error_Status(){

    return this->gui_syntax_error;
}

bool Descriptor_File_Reader::Get_Invalid_Descriptor_File_Status(){

     return this->is_project_file_invalid;
}

