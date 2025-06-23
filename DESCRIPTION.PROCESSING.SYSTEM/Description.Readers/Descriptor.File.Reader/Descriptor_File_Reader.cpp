
/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Descriptor_File_Reader.hpp"

Descriptor_File_Reader::Descriptor_File_Reader(char opr_sis, char build_type) :

   Data_Collector(opr_sis), Syntax_Controller(opr_sis)
{
   
   this->opr_sis = opr_sis;

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

   this->lack_of_decleration_error = false;

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

         this->Clear_Vectory_Memory(&this->compiler_paths);

         this->Clear_String_Memory(&this->standard);

         this->Clear_String_Memory(&this->warehouse_location);

         this->Clear_String_Memory(&this->root_dir);

         this->Clear_String_Memory(&this->descriptor_file_path);

         this->Clear_String_Memory(&this->build_system);

         this->Clear_String_Memory(&this->project_name);

         this->Clear_String_Memory(&this->version_number);

         for(size_t i=0;i<this->library_data_list.size();i++){

             this->Clear_String_Memory(&this->library_data_list.at(i).library_dir);

             this->Clear_String_Memory(&this->library_data_list.at(i).library_name_with_ext);
             
             this->Clear_String_Memory(&this->library_data_list.at(i).library_name_without_ext);
         }

         this->library_data_list.clear();

         this->library_data_list.shrink_to_fit();



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

          this->Line_Reader.Receive_Descriptor_File_Data_Collector(&this->Data_Collector);

          this->Number_Determiner.Receive_Descriptor_File_Data_Collector(&this->Data_Collector);

          this->Number_Determiner.Determine_Record_Numbers();

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

              this->Read_Compiler_Paths();
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

                      this->Read_Compiler_Paths();
                  }
               }
           }
     }

     this->Extract_Library_Names_From_Path();

     this->Data_Collector.Clear_Dynamic_Memory();
}


void Descriptor_File_Reader::Read_Root_Directory_Location(){

     
     int record_num = this->Number_Determiner.Get_Root_Directory_Location_Record_Number();

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

            this->lack_of_decleration_error = true;

            this->gui_read_success = false;
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

           this->lack_of_decleration_error = true;

           this->gui_read_success = false;
        }

     }


     if(this->gui_read_status){

        if(this->gui_read_success){

           if(record_num >0){

              this->Line_Reader.Read_Root_Directory_Location(this->root_dir);
            }
        }
     }
     else{

         if(record_num >0){

            this->Line_Reader.Read_Root_Directory_Location(this->root_dir);           
         }
     }
}


void Descriptor_File_Reader::Read_Warehouse_Location(){

     int record_num = this->Number_Determiner.Get_Warehouse_Location_Record_Number();

     std::cout << "\n record_num:" << record_num;

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

               this->lack_of_decleration_error = true;

               this->gui_read_success = false;
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

            this->lack_of_decleration_error = true;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

           this->Line_Reader.Read_Warehouse_Location(this->warehouse_location);
        }
     }
     else{
           
          this->Line_Reader.Read_Warehouse_Location(this->warehouse_location);
     }

}



void Descriptor_File_Reader::Read_Standard(){

     int record_num = this->Number_Determiner.Get_Standard_Record_Number();

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

                  this->lack_of_decleration_error = true;

            }
         }

     
     if(this->gui_read_status){

        if(this->gui_read_success){
          
           this->Line_Reader.Read_Standard(this->standard);         
        }
     }
     else{

           this->Line_Reader.Read_Standard(this->standard);         
     }
}





void Descriptor_File_Reader::Read_Build_System_Type(){

     int record_num = this->Number_Determiner.Get_Build_System_Type_Record_Number();

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

            this->lack_of_decleration_error = true;
        }
     }


     if(this->gui_read_status){

        if(this->gui_read_success){

           this->Line_Reader.Read_Build_System_Type(this->build_system);
        }
     }
     else{
           
         this->Line_Reader.Read_Build_System_Type(this->build_system);
     }

}




void Descriptor_File_Reader::Read_Project_Name(){

     this->Clear_String_Memory(&this->project_name);

     int record_num = this->Number_Determiner.Get_Project_Name_Record_Number();

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

            this->lack_of_decleration_error = true;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

            this->Line_Reader.Read_Project_Name(this->project_name);
        }
     }
     else{
           
            this->Line_Reader.Read_Project_Name(this->project_name);
     }
}



void Descriptor_File_Reader::Read_Version_Number(){

     this->Clear_String_Memory(&this->version_number);

     int record_num = this->Number_Determiner.Get_Version_Number_Record_Number();

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

            this->lack_of_decleration_error = true;
        }
     }

     if(this->gui_read_status){

        if(this->gui_read_success){

           this->Line_Reader.Read_Version_Number(this->version_number);
        }
     }
     else{
           this->Line_Reader.Read_Version_Number(this->version_number);
     }
}




void Descriptor_File_Reader::Read_Include_Directories(){

     this->include_dir_num = this->Number_Determiner.Get_Include_Directories_Record_Number();

      if(this->include_dir_num > 0){

         this->Memory_Delete_Condition = false;

         this->Line_Reader.Read_Include_Directories(this->Include_Directories);
      }

      this->Include_Directories.shrink_to_fit();

      this->include_dir_num = this->Include_Directories.size();
}



void Descriptor_File_Reader::Read_Source_File_Directories(){

     this->source_file_dir_num = this->Number_Determiner.Get_Source_File_Directories_Record_Number();

     if(this->source_file_dir_num > 0){

        this->Memory_Delete_Condition = false;

        this->Line_Reader.Read_Source_File_Directories(this->Source_File_Directories);
     }

     this->Source_File_Directories.shrink_to_fit();

     this->source_file_dir_num = this->Source_File_Directories.size();
}



void Descriptor_File_Reader::Read_Compiler_Paths(){

     this->compiler_path_number = this->Number_Determiner.Get_Compiler_Paths_Record_Number();

     if(this->compiler_path_number > 0){

        this->Memory_Delete_Condition = false;

        this->Line_Reader.Read_Compiler_Paths(this->compiler_paths);
     }
     else{

           if(this->Data_Record_Cond == false) {

              std::cout << "\n\n";

              std::cout << "\n Error:";

              this->Clear_String_Memory(&this->error_message);

              this->error_message = "\nThere is no any decleration about compiler path";

              std::cout << this->error_message;

              std::cout << "\n\n\n";

              if(!this->gui_read_status){

                 exit(0);
              }
              else{

                    this->gui_read_success = false;

                   this->lack_of_decleration_error = true;
              }
          }
     }

     this->compiler_paths.shrink_to_fit();

     this->compiler_path_number = this->compiler_paths.size();
}





void Descriptor_File_Reader::Read_Library_Directories(){

     this->lib_dir_num = this->Number_Determiner.Get_Library_Directories_Record_Number();

     if(this->lib_dir_num > 0){

        this->Memory_Delete_Condition = false;

        this->Line_Reader.Read_Library_Directories(this->Library_Directories);
     }

     this->Library_Directories.shrink_to_fit();

     this->lib_dir_num = this->Library_Directories.size();
}



void Descriptor_File_Reader::Read_Library_Files(){

     this->lib_file_num = this->Number_Determiner.Get_Library_Files_Record_Number();

     if(this->lib_file_num > 0){

        this->Memory_Delete_Condition = false;

        this->Line_Reader.Read_Library_Files(this->Library_Files);
     }

     this->Library_Files.shrink_to_fit();

     this->lib_file_num = this->Library_Files.size();
}



void Descriptor_File_Reader::Read_Compiler_Options(){

     int record_num = this->Number_Determiner.Get_Compiler_Options_Record_Number();
         
      if(record_num < 1){

         this->compiler_options.clear();   // There is no any decleration about the options

         this->compiler_options.shrink_to_fit();
      }
      else{
          
          this->Line_Reader.Read_Compiler_Options(this->compiler_options);
      }

      this->compiler_options.shrink_to_fit();
}




void Descriptor_File_Reader::Read_Linker_Options(){

     int record_num = this->Number_Determiner.Get_Linker_Options_Record_Number();
   
     if(record_num < 1){

         this->linker_options.clear();   // There is no any decleration about the options

         this->linker_options.shrink_to_fit();
     }
     else{

         this->Line_Reader.Read_Linker_Options(this->linker_options);
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


void Descriptor_File_Reader::Clear_Vectory_Memory(std::vector<std::string> * pointer)
{
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



void Descriptor_File_Reader::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}



void Descriptor_File_Reader::Delete_Spaces_on_String_Start(std::string * str)
{
   if(!str->empty()){

       while(!str->empty()){

           if(str->at(0) == ' '){

              str->erase(0,1);

              str->shrink_to_fit();
           }
           else{

               break;
           }
      }
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





 void Descriptor_File_Reader::Extract_Library_Names_From_Path()
 {
      const std::vector<std::string> & lib_name_list = this->Get_Library_Files();

      if(lib_name_list.size()>0){

          bool path_cond = false;

          for(auto str: lib_name_list){

              path_cond = this->Is_This_String_A_File_Path(str);

              Library_Data data;

              if(path_cond){

                  this->Extract_Directory_From_Path(str,data.library_dir);

                  this->Determine_File_Name_Without_Ext(str,data.library_name_without_ext);

                  this->Extract_File_Name_From_Path(str,data.library_name_with_ext);   
                  
                  this->library_data_list.push_back(data);
              }
              else{

                  this->Determine_File_Name_Without_Ext(str,data.library_name_without_ext);

                  data.library_name_with_ext = str;   

                  data.library_dir = "";
                  
                  data.library_dir.clear();

                  data.library_dir.shrink_to_fit();

                  this->library_data_list.push_back(data);
              }
         }  
      }
}


void Descriptor_File_Reader::Extract_Directory_From_Path(std::string path, std::string & dir)
{
     size_t path_size = path.size();

     size_t end_point = path_size;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(path[i]== '\\'){

                break;
            }
            else{

                 end_point--;
            }
         }

         if(this->opr_sis == 'l'){

            if(path[i]== '/'){

                break;
            }
            else{

                 end_point--;
            }
         }         
    }

    for(size_t i=0;i<end_point;i++)
    {
        dir.push_back(path[i]);
    }

    dir.shrink_to_fit();    
}


void Descriptor_File_Reader::Determine_File_Name_Without_Ext(std::string path, std::string & file_name)
{
     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;

     size_t file_extention_start_point = file_path_size;


    for(size_t i=file_path_size;i>0;i--){

        if((path[i] == '/') || (path[i] == '\\')){

            break;
        }
        else{

              dir_size--;
        }
     }

     for(size_t i=file_path_size;i>0;i--){

         if(path[i] == '.'){

           break;
         }
            else{

                file_extention_start_point--;
          }

          if(file_extention_start_point <= dir_size){

             file_extention_start_point = dir_size;
          }
     }

     size_t file_name_size = 0;

     if(file_extention_start_point <= dir_size){

        file_name_size = file_path_size - dir_size;

        // It is the case in which the file does not have extenton
     }

     if(file_extention_start_point > dir_size){

        file_name_size = file_extention_start_point - dir_size;
     }


     size_t name_start_point = 0;

     if(dir_size != 0){

        name_start_point = dir_size +1;
     }

     for(size_t i=name_start_point;i<file_extention_start_point;i++){

         file_name.push_back(path[i]);
     }
}


void Descriptor_File_Reader::Determine_File_Name_Without_Ext(char * path, std::string & name){

     std::string file_path;

     size_t path_size = strlen(path);

     for(size_t i=0;i<path_size;i++){
     
         file_path.push_back(path[i]);
     }

     file_path.shrink_to_fit();

     this->Determine_File_Name_Without_Ext(file_path,name);
}


void Descriptor_File_Reader::Extract_File_Name_From_Path(std::string string,  std::string & name){

     size_t string_size = string.length();

     size_t start_point = 0;

     for(size_t i=string_size;i>0;i--){

        if(((string[i] == '/') || (string[i] == '\\'))){

            start_point = i+1;

            break;
        }
     }

     for(size_t i=start_point;i<string_size;i++)
     {
         name.push_back(string[i]) ;
     }

     name.shrink_to_fit();
}


bool Descriptor_File_Reader::Is_This_String_A_File_Path(std::string str)
{
     bool path_cond = false;

     if(this->opr_sis == 'w'){

        for(auto str_index : str){
               
            if(str_index == '\\'){

               path_cond = true;

               break;
            }
         }
      }
      else{
            if(this->opr_sis == 'l'){

               for(auto str_index : str){

                   if(str_index == '/'){
     
                      path_cond = true;

                      break;
                   }
               }                     
            }
      }     

      return path_cond;
}


const std::vector<Library_Data> & Descriptor_File_Reader::Get_Library_File_Data_List(){

      return this->library_data_list;
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

const std::vector<std::string> & Descriptor_File_Reader::Get_Compiler_Paths(){

      return this->compiler_paths;
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

bool Descriptor_File_Reader::Get_Lack_of_Decleration_Error_Status(){

     return this->lack_of_decleration_error;
}
