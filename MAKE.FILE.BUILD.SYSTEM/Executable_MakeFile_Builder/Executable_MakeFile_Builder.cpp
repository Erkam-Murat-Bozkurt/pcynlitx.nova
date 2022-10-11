

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

#include "Executable_MakeFile_Builder.hpp"

Executable_MakeFile_Builder::Executable_MakeFile_Builder(){

   this->Memory_Delete_Condition = false;

   this->object_file_list = nullptr;

   this->header_file_list = nullptr;

}

Executable_MakeFile_Builder::Executable_MakeFile_Builder(const Executable_MakeFile_Builder & orig){

}

Executable_MakeFile_Builder::~Executable_MakeFile_Builder(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Executable_MakeFile_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){


     }
}

void Executable_MakeFile_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Des_Reader){

     this->DataCollector.Receive_Descriptor_File_Reader(Des_Reader);
}

void Executable_MakeFile_Builder::Receive_Git_Record_Data(Git_File_List_Receiver * Pointer){

     this->DataCollector.Receive_Git_Record_Data(Pointer);
}

void Executable_MakeFile_Builder::Receive_Source_File_Info(Project_Files_Lister * Pointer){

     this->DataCollector.Receive_Source_File_Info(Pointer);
}

void Executable_MakeFile_Builder::Build_MakeFile(){

     this->DataCollector.Collect_Make_File_Data();

     this->Receive_DataCollector_Info();

     this->Determine_Compile_Order();


}

  void Executable_MakeFile_Builder::Determine_Compile_Order(){

       //this->DataCollector.Print_Header_Data();

       this->Receive_DataCollector_Info();

       this->Reverse_Order_Priorities();


       for(int i=0;i<this->header_file_number;i++){


          std::cout << "\n\n\n";

          std::cout << "\n RECURSIVE SEARCH STARTED";

          std::cout << "\n this->Data_Ptr_CString[" << i << "].priority: "

          << this->Data_Ptr_CString[i].priority;


          bool rec_search = this->Data_Ptr_CString[i].rcr_srch_complated;

          if(!rec_search){

             this->Search_Recursive_Include_Dependency(i);
          }

          std::cout << "\n this->Data_Ptr_CString[" << i << "].priority: "

          << this->Data_Ptr_CString[i].priority;

          std::cout << "\n RECURSIVE SEARCH ENDED";

          std::cin.get();
       }


       this->Order_Priorities();

       this->DataCollector.Print_Header_Data();

       std::cin.get();



       for(int i=0;i<this->header_file_number;i++){

           std::cout << "\n this->Data_Ptr_CString[" << i << "].priority"

           << this->Data_Ptr_CString[i].priority;
           std::cin.get();


           bool rec_search = this->Data_Ptr_CString[i].rcr_srch_complated;

           this->Search_Recursive_Include_Dependency(i);

           std::cout << "\n this->Data_Ptr_CString[" << i << "].priority"

           << this->Data_Ptr_CString[i].priority;

           std::cin.get();
       }

       this->Order_Priorities();

       std::cout << "\n\n ////////////////////////////////////////// ";

       this->Print_Compiler_Orders();

       std::cin.get();
  }


  void Executable_MakeFile_Builder::Search_Recursive_Include_Dependency(int index){

       int inc_num = this->Data_Ptr_CString[index].inclusion_number;

       std::cout << "\n this->Data_Ptr_CString[" << index << "].header_name:" <<

       this->Data_Ptr_CString[index].header_name;

       std::cout << "\n index:" << index;

       std::cout << "\n inc_num:" << inc_num;

       if(inc_num>0){

          for(int k=0;k<inc_num;k++){

              char * inc_header_name = this->Data_Ptr_CString[index].included_headers[k];

              for(int j=0;j<this->header_file_number;j++){

                  char * repo_header = this->Data_Ptr_CString[j].header_name;

                  bool is_equal = this->Char_Processor.CompareString(inc_header_name,repo_header);

                  if(is_equal){

                     int priority = this->Data_Ptr_CString[j].priority;

                     if(priority == 0){

                        priority = 1;
                     }

                     this->Data_Ptr_CString[index].priority =

                     this->Data_Ptr_CString[index].priority + priority;


                     //this->Search_Recursive_Include_Dependency(j);
                  }
              }
          }
        }
        else{

             this->Data_Ptr_CString[index].rcr_srch_complated = true;
        }

        //std::cout << "\n The recursive call ended ..";
  }

  void Executable_MakeFile_Builder::Order_Priorities(){

       for(int i=0;i<this->header_file_number;i++){

           for(int j=i;j<this->header_file_number;j++){

               int dep_i = this->Data_Ptr_CString[i].priority;

               int dep_j = this->Data_Ptr_CString[j].priority;

               Compiler_Data_CString temp;

               if( dep_i < dep_j){

                   temp  = this->Data_Ptr_CString[j];

                   this->Data_Ptr_CString[j] = this->Data_Ptr_CString[i];

                   this->Data_Ptr_CString[i] = temp;
               }
            }
        }
  }

  void Executable_MakeFile_Builder::Reverse_Order_Priorities(){

       for(int i=0;i<this->header_file_number;i++){

           for(int j=i;j<this->header_file_number;j++){

               int dep_i = this->Data_Ptr_CString[i].priority;

               int dep_j = this->Data_Ptr_CString[j].priority;

               Compiler_Data_CString temp;

               if( dep_i > dep_j){

                   temp  = this->Data_Ptr_CString[j];

                   this->Data_Ptr_CString[j] = this->Data_Ptr_CString[i];

                   this->Data_Ptr_CString[i] = temp;
               }

               dep_i = this->Data_Ptr_CString[i].priority;

               dep_j = this->Data_Ptr_CString[j].priority;
            }
        }
  }

  void Executable_MakeFile_Builder::Receive_DataCollector_Info(){

       this->header_file_number = this->DataCollector.Get_Compiler_Data_Size();

       this->Data_Ptr_CString   = this->DataCollector.Get_Compiler_Data();
  }

  void Executable_MakeFile_Builder::Print_Compiler_Orders(){

       for(int i=0;i<this->header_file_number;i++){

           std::cout << "\n this->Data_Ptr_CString[" << i <<"].header_name:"

           <<  this->Data_Ptr_CString[i].header_name;

           std::cout << "\n this->Data_Ptr_CString[" << i <<"].priority:"

           <<  this->Data_Ptr_CString[i].priority;

           std::cout << "\n\n";


           std::cout << "\n this->Data_Ptr_CString[" << i <<"].inclusion_number:"

           <<  this->Data_Ptr_CString[i].inclusion_number;

           std::cout << "\n\n";


           std::cin.get();
       }
  }
