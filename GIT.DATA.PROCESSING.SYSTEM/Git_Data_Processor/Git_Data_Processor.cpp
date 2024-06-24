

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

#include "Git_Data_Processor.hpp"



Git_Data_Processor::Git_Data_Processor(char opr_sis, char build_type) :

    Modf_Receiver(opr_sis), Modf_Lister(opr_sis), List_Writer(opr_sis), 
    List_Receiver(opr_sis), Des_Reader(opr_sis,build_type) 
{
    this->opr_sis = opr_sis;

    if(build_type == 'g'){

       this->Set_Gui_Read_Status(true);
    }
    else{

       this->Set_Gui_Read_Status(false);
    }

    this->Memory_Delete_Condition = false;
}


Git_Data_Processor::~Git_Data_Processor(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_Data_Processor::Set_Gui_Read_Status(bool status){

     this->gui_read_status = status;
}

void Git_Data_Processor::Receive_Descriptor_File_Path(char * DesPath){

     this->Des_Reader.Receive_Descriptor_File_Path(DesPath);

     this->Des_Reader.Read_Descriptor_File();

     this->List_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->List_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);
}

void Git_Data_Processor::Receive_Descriptor_File_Path(std::string DesPath){

     this->Des_Reader.Receive_Descriptor_File_Path(DesPath);

     this->Des_Reader.Read_Descriptor_File();

     this->List_Writer.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->List_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);
}


 void Git_Data_Processor::Extract_Directory_Tree(){

      std::vector<std::string> *  dir_list =  this->Get_Git_Record_Directory_Address();
      
      for(size_t i=0;i<dir_list->size();i++)
      {
          bool is_exist = false;

          for(size_t j=0;j<this->Directory_Tree.size();j++){

              if(this->Directory_Tree.at(j) == dir_list->at(i)){

                  is_exist = true;

                  break;
              }
          }

          if(!is_exist){

             if(dir_list->at(i).size()>0){

                this->Directory_Tree.push_back(dir_list->at(i));

                this->Directory_Tree.shrink_to_fit();
             }
          }
      }

      this->Directory_Tree.shrink_to_fit();





      // Determination of upper directories

      
      CharOperator Cr_Opr;

      char dir_char;

      if(this->opr_sis == 'w'){

          dir_char = '\\';
      }

      if(this->opr_sis == 'l'){

          dir_char = '/';
      }


      for(size_t i=0;i<this->Directory_Tree.size();i++)
      {
          bool is_upper_directort_exist = false;

          int reputation = Cr_Opr.DetermineCharacterRepitation(this->Directory_Tree.at(i),dir_char);

          if(reputation>0){

             std::string upper_dir;

             this->Find_Upper_Directory(upper_dir,this->Directory_Tree.at(i));

             bool is_exist_ = false;


             for(size_t j=0;j<this->Directory_Tree.size();j++){

                 if(this->Directory_Tree.at(j) == upper_dir){

                    is_exist_ = true;

                    break;
                 }
             }

             if(!is_exist_){

               if(upper_dir.size()>0){

                  this->Directory_Tree.push_back(upper_dir);

                  this->Directory_Tree.shrink_to_fit();
                }
             }
          }
      }

      this->Directory_Tree.shrink_to_fit();



      // THE ORDERING OPERATIONS


      int dir_data[2*this->Directory_Tree.size()];

      for(size_t i=0;i<this->Directory_Tree.size();i++){

          dir_data[i] = Cr_Opr.DetermineCharacterRepitation(this->Directory_Tree.at(i),dir_char);
      }

      for(size_t i=0;i<this->Directory_Tree.size();i++){

           for(size_t j=0;j<this->Directory_Tree.size();j++){

               if(dir_data[i]<dir_data[j]){

                  std::string temp_dir_str = this->Directory_Tree.at(j);

                  this->Directory_Tree.at(j) = this->Directory_Tree.at(i);

                  this->Directory_Tree.at(i) = temp_dir_str;

                  int dir_dat = dir_data[j];

                  dir_data[j] = dir_data[i];

                  dir_data[i] = dir_dat;
               }
           }
      }


      
      for(size_t i=0;i<this->Directory_Tree.size();i++){

           for(size_t j=0;j<this->Directory_Tree.size();j++){

               if(this->Directory_Tree.at(i).size() <= this->Directory_Tree.at(j).size()){

                  std::string temp_dir_str = this->Directory_Tree.at(j);

                  this->Directory_Tree.at(j) = this->Directory_Tree.at(i);

                  this->Directory_Tree.at(i) = temp_dir_str;
               }
           }
      }

      this->Construct_SubDirectory_Data();

      this->Filtering_Root_Directories();
}



void Git_Data_Processor::Find_Upper_Directory(std::string & upper, std::string dir){

     size_t dir_size = dir.size();

     size_t end_point = dir_size;

     for(size_t i=dir_size;i>0;i--){

         if((dir[i]=='/') || (dir[i]=='\\')){

            end_point = i;

            break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         upper.push_back(dir[i]);
     }

     upper.shrink_to_fit();
}



void Git_Data_Processor::Construct_SubDirectory_Data()
{
     StringOperator StrOpr;

     CharOperator Cr_Opr;

     char dir_char;

     if(this->opr_sis == 'w'){

        dir_char = '\\';
     }

     if(this->opr_sis == 'l'){

        dir_char = '/';
     }

     for(size_t i=0;i<this->Directory_Tree.size();i++){

          std::string dir = this->Directory_Tree.at(i);

          int dir_rep = Cr_Opr.DetermineCharacterRepitation(this->Directory_Tree.at(i),dir_char);

          Git_Sub_Directory_Data Temp_Data;

          Temp_Data.dir_path = dir;

          for(size_t j=0;j<this->Directory_Tree.size();j++){

              bool is_sub_dir = false;

              if(StrOpr.CheckStringInclusion(this->Directory_Tree.at(j),dir)){

                 int sub_dir_rep = Cr_Opr.DetermineCharacterRepitation(this->Directory_Tree.at(j),dir_char);

                 if((sub_dir_rep - dir_rep) == 1){

                    if(this->Directory_Tree.at(j).size()>dir.size()){

                       is_sub_dir = true;
                    }
                 }
              }

              if(is_sub_dir){

                 Temp_Data.sub_dirs.push_back(this->Directory_Tree.at(j));
              }
          }

          Temp_Data.sub_dirs.shrink_to_fit();

          Sub_Dir_Data.push_back(Temp_Data);

          this->Clear_Sub_Directory_Data(Temp_Data);
     }
}


void Git_Data_Processor::Filtering_Root_Directories(){

     CharOperator Cr_Opr;

     char dir_char;

     if(this->opr_sis == 'w'){

        dir_char = '\\';
     }

     if(this->opr_sis == 'l'){

        dir_char = '/';
     }

     for(size_t i=0;i<this->Sub_Dir_Data.size();i++){

         size_t sub_dir_size = this->Sub_Dir_Data.at(i).sub_dirs.size();

         if(sub_dir_size>0){

            this->Root_Dirs.push_back(this->Sub_Dir_Data.at(i));
         }

         if(sub_dir_size == 0){

            std::string dir_path = this->Sub_Dir_Data.at(i).dir_path;

            int dir_char_rep = Cr_Opr.DetermineCharacterRepitation(dir_path,dir_char);

            if(dir_char_rep ==0){

               this->Root_Dirs.push_back(this->Sub_Dir_Data.at(i));
            }
         }
     }

     this->Root_Dirs.shrink_to_fit();
}


void Git_Data_Processor::Clear_Sub_Directory_Data(Git_Sub_Directory_Data & Data){

     this->Clear_Std_String(Data.dir_path);

     if(!Data.sub_dirs.empty()){

         for(size_t i=0;i<Data.sub_dirs.size();i++){

             this->Clear_Std_String(Data.sub_dirs.at(i));
         }
     }

     Data.sub_dirs.shrink_to_fit();
}


void Git_Data_Processor::Clear_Std_String(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}

void Git_Data_Processor::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->List_Receiver.Clear_Dynamic_Memory();

         this->List_Writer.Clear_Dynamic_Memory();

         this->Modf_Lister.Clear_Dynamic_Memory();

         this->Modf_Receiver.Clear_Dynamic_Memory();

         this->Des_Reader.Clear_Dynamic_Memory();

         if(!this->Sub_Dir_Data.empty()){

            for(size_t i=0;i<this->Sub_Dir_Data.size();i++){

                this->Clear_Sub_Directory_Data(this->Sub_Dir_Data.at(i));
            }

            this->Sub_Dir_Data.clear();

            this->Sub_Dir_Data.shrink_to_fit();
         }


         if(!this->Directory_Tree.empty()){

            for(size_t i=0;i<this->Directory_Tree.size();i++){

                this->Clear_Std_String(this->Directory_Tree.at(i));
            }

            this->Directory_Tree.clear();

            this->Directory_Tree.shrink_to_fit();
         }
     }
}


void Git_Data_Processor::Write_Git_Repo_List_File()
{     
     this->List_Writer.Write_Git_Repo_List_File();
}


void Git_Data_Processor::Determine_Git_Repo_Info(){

     this->List_Receiver.Determine_Git_Repo_Info();     
}


void Git_Data_Processor::Write_Git_Modification_File(){
     
     this->Modf_Lister.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Modf_Lister.Write_Git_Modification_File();
}


void Git_Data_Processor::Receive_Git_Modifications(){

     this->Modf_Receiver.Receive_Descriptor_File_Reader(&this->Des_Reader);

     this->Modf_Receiver.Receive_Git_List_Receiver(&this->List_Receiver);

     this->Modf_Receiver.Receive_Git_Modifications();
}


std::string Git_Data_Processor::Get_File_System_Path(int num){

     return this->List_Receiver.Get_File_System_Path(num);
}

std::string Git_Data_Processor::Get_Git_File_Index(int num)
{
      return this->List_Receiver.Get_Git_File_Index(num);
}


std::string Git_Data_Processor::Get_Git_Repo_Directory(){

       return this->List_Receiver.Get_Git_Repo_Directory();
}


size_t Git_Data_Processor::Get_Git_File_Index_Size(){

    return this->List_Receiver.Get_Git_File_Index_Size();
}


std::string Git_Data_Processor::Get_Git_Record_Directory(int num){
 
      return this->List_Receiver.Get_Git_Record_Directory(num);
}


std::string Git_Data_Processor::Get_Git_Record_Path(int num){
 
      return this->List_Receiver.Get_Git_Record_Path(num);
}

std::string Git_Data_Processor::Get_File_Name(int num){
 
      return this->List_Receiver.Get_File_Name(num);    
}

std::vector<std::string> * Git_Data_Processor::Get_Git_File_Index_Address(){
 
     return this->List_Receiver.Get_Git_File_Index_Address();
}
  
std::vector<std::string> * Git_Data_Processor::Get_File_System_Path_Address(){
 
     return this->List_Receiver.Get_File_System_Path_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_Git_Record_Directory_Address(){
 
     return this->List_Receiver.Get_Git_Record_Directory_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_Git_Record_Path_Address(){
 
      return this->List_Receiver.Get_Git_Record_Path_Address();
}
 
 
std::vector<std::string> * Git_Data_Processor::Get_File_Name_Address(){
 
      return this->List_Receiver.Get_File_Name_Address();    
}


std::vector<std::string> * Git_Data_Processor::Get_Updated_Header_Files()  
{
     return this->Modf_Receiver.Get_Updated_Header_Files();
    
}

std::vector<std::string> * Git_Data_Processor::Get_Updated_Source_Files()  
{
     return  this->Modf_Receiver.Get_Updated_Source_Files();
}


std::vector<std::string> * Git_Data_Processor::Get_Directory_Tree(){

      return &this->Directory_Tree;
}


std::vector<Git_Sub_Directory_Data> * Git_Data_Processor::Get_Directory_Tree_Data(){

     return &this->Sub_Dir_Data;
}


 std::vector<Git_Sub_Directory_Data> * Git_Data_Processor::Get_Git_Root_Dirs(){

     return &this->Root_Dirs;
 }
