

#include "Descriptor_File_Line_Reader.hpp"

Descriptor_File_Line_Reader::Descriptor_File_Line_Reader(){


}

Descriptor_File_Line_Reader::~Descriptor_File_Line_Reader(){


}

void Descriptor_File_Line_Reader::Receive_Descriptor_File_Data_Collector(Descriptor_File_Data_Collector * ptr){

     this->Data_Collector = ptr;
}


void Descriptor_File_Line_Reader::Read_Root_Directory_Location(std::string & str){

     int start_line = this->Data_Collector->Get_Root_Directory_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Root_Directory_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               str = line;

               break;
            }
         }
     }
 }

 void Descriptor_File_Line_Reader::Read_Warehouse_Location(std::string & str){

      int start_line = this->Data_Collector->Get_Warehouse_Location_Record_Area(0);

      int end_line   = this->Data_Collector->Get_Warehouse_Location_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

          if(this->StringManager.CheckStringLine(line)){

             if(this->Is_Include_Character(line)){

                str = line;

                break;
             }
          }
      }
 }


 void Descriptor_File_Line_Reader::Read_Standard(std::string & str){

     int start_line = this->Data_Collector->Get_Standard_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Standard_Record_Area(1);
      
     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            str = line;

            break;
         }
     }
 }


 void Descriptor_File_Line_Reader::Read_Include_Directories(std::vector<std::string> & vec){
    
     int start_line = this->Data_Collector->Get_Include_Directories_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Include_Directories_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

         if(this->StringManager.CheckStringLine(line)){

            if(this->Is_Include_Character(line)){

               vec.push_back(line);
            }
         }
     }
 }

 void Descriptor_File_Line_Reader::Read_Source_File_Directories(std::vector<std::string> & vec){

     int start_line = this->Data_Collector->Get_Source_File_Directories_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Source_File_Directories_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);            

          if(this->StringManager.CheckStringLine(line)){

             if(this->Is_Include_Character(line)){

                vec.push_back(line);
             }
          }
     }
 }



 void Descriptor_File_Line_Reader::Read_Library_Directories(std::vector<std::string> & vec){

      int start_line = this->Data_Collector->Get_Library_Directories_Record_Area(0);

      int end_line   = this->Data_Collector->Get_Library_Directories_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

            std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

            if(this->StringManager.CheckStringLine(line)){

               if(this->Is_Include_Character(line)){

                  vec.push_back(line);
               }
            }
      }
 }



 void Descriptor_File_Line_Reader::Read_Library_Files(std::vector<std::string> & vec){

      int start_line = this->Data_Collector->Get_Library_Files_Record_Area(0);

      int end_line  = this->Data_Collector->Get_Library_Files_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

          if(this->StringManager.CheckStringLine(line)){

               if(this->Is_Include_Character(line)){

                  if(this->Is_There_Multiple_Decleration_on_Same_Line(line)){

                     std::vector<std::string> multi_line;

                     this->Extract_Declerations_Performing_on_Same_Line(line,multi_line);

                     for(size_t k=0;k<multi_line.size();k++){

                         vec.push_back(multi_line.at(k));
                     }
                  }
                  else{

                       vec.push_back(line);
                  }
               }
            }
       }
 }



 void Descriptor_File_Line_Reader::Read_Compiler_Options(std::vector<std::string> & vec){

      int start_line = this->Data_Collector->Get_Compiler_Options_Record_Area(0);

      int end_line   = this->Data_Collector->Get_Compiler_Options_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

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

                       vec.push_back(multi_line.at(k));
                   }
                }
                else{

                       vec.push_back(line);
                }
              }
            }   
       }
 }

 void Descriptor_File_Line_Reader::Read_Linker_Options(std::vector<std::string> & vec){
    
     int start_line = this->Data_Collector->Get_Linker_Options_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Linker_Options_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);

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

                       vec.push_back(multi_line.at(k));
                   }
                }
                else{

                       vec.push_back(line);
                }                    
            }
        }
     }
 }


 void Descriptor_File_Line_Reader::Read_Build_System_Type(std::string & str){
    
      int start_line = this->Data_Collector->Get_Build_System_Type_Record_Area(0);

      int end_line   = this->Data_Collector->Get_Build_System_Type_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

          if(this->StringManager.CheckStringLine(line)){                   

            str = line;

            break;
          }
      }
 }


 void Descriptor_File_Line_Reader::Read_Project_Name(std::string & str){

     int start_line = this->Data_Collector->Get_Project_Name_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Project_Name_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){        

            str = line;

            break;
         }
     }
 }



 void Descriptor_File_Line_Reader::Read_Version_Number(std::string & str){

     int start_line = this->Data_Collector->Get_Version_Number_Record_Area(0);

     int end_line   = this->Data_Collector->Get_Version_Number_Record_Area(1);

     for(int i=start_line+1;i<end_line-1;i++){

         std::string line = this->Data_Collector->Get_Descriptor_File_Line(i);

         if(this->StringManager.CheckStringLine(line)){

            str = line;

            break;
         }
     }
 }



 void Descriptor_File_Line_Reader::Read_Compiler_Paths(std::vector<std::string> & vec){

      int start_line = this->Data_Collector->Get_Compiler_Paths_Record_Area(0);

      int end_line   = this->Data_Collector->Get_Compiler_Paths_Record_Area(1);

      for(int i=start_line+1;i<end_line-1;i++){

          std::string line = this->Data_Collector->Get_Descriptor_File_Line_With_Spaces(i);                   

          if(this->StringManager.CheckStringLine(line)){

             if(this->Is_Include_Character(line)){

                vec.push_back(line);
             }
          
          }
       }
 }


 bool Descriptor_File_Line_Reader::Is_Include_Character(std::string str){

     bool is_include = false;

     for(size_t i=0;i<str.length();i++){

         if((str.at(i) != ' ') && (str.at(i) != '\n')){

              is_include = true;

              return is_include;
         }
     }

     return is_include;
}





bool Descriptor_File_Line_Reader::Is_There_Multiple_Decleration_on_Same_Line(std::string & str_line){

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




void Descriptor_File_Line_Reader::Extract_Declerations_Performing_on_Same_Line(std::string str_line, 
 
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