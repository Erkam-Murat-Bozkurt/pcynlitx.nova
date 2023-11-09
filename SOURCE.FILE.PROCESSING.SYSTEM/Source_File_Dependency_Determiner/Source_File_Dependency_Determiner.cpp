


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

#include "Source_File_Dependency_Determiner.hpp"

Source_File_Dependency_Determiner::Source_File_Dependency_Determiner(char * des_file_path, char opr_sis) :

    Code_Rd(opr_sis), Com_Data_Extractor(opr_sis), DepSelector(opr_sis), 
    
    DepSelector_For_Single_File(opr_sis), Simple_Dep_Extractor(opr_sis)
{

}


Source_File_Dependency_Determiner::~Source_File_Dependency_Determiner(){

    this->Clear_Dynamic_Memory();
}


void Source_File_Dependency_Determiner::Clear_Object_Memory(){

     this->Com_Data_Extractor.Clear_Dynamic_Memory();

     this->Code_Rd.Clear_Object_Memory();

     this->DepSelector.Clear_Object_Memory();

     this->Clear_Dynamic_Memory();
}



void Source_File_Dependency_Determiner::Clear_Dynamic_Memory(){

     this->DepSelector.Clear_Dynamic_Memory();  

     this->DepSelector_For_Single_File.Clear_Dynamic_Memory();

     this->Dependency_Map.clear();   
}



void Source_File_Dependency_Determiner::Receive_Descriptor_File_Reader(Descriptor_File_Reader *ptr){
     
     this->DepSelector.Receive_Descriptor_File_Reader(ptr);

     this->DepSelector_For_Single_File.Receive_Descriptor_File_Reader(ptr);

     this->Simple_Dep_Extractor.Receive_Descriptor_File_Reader(ptr);
}



void Source_File_Dependency_Determiner::Receive_Git_Data_Processor(Git_Data_Processor * ptr){

     this->Git_Data_Proc = ptr;

     this->Code_Rd.Receive_Git_Data_Processor(this->Git_Data_Proc);

     this->Code_Rd.Read_Project_Source_Code_Files();

     this->DepSelector.Receive_Source_Code_Reader(&this->Code_Rd);

     this->DepSelector_For_Single_File.Receive_Source_Code_Reader(&this->Code_Rd);

     this->Src_Processor.Receive_Source_Code_Reader(&this->Code_Rd); 

     this->DepSelector.Receive_Git_Data_Processor(ptr);

     this->DepSelector_For_Single_File.Receive_Git_Data_Processor(ptr);


     this->Simple_Dep_Extractor.Receive_Git_Data_Processor(ptr);

     this->Simple_Dep_Extractor.Receive_Source_Code_Reader(&this->Code_Rd);
}


void Source_File_Dependency_Determiner::Collect_Dependency_Information(std::string path){

     this->Clear_Dynamic_Memory();

     this->DepSelector_For_Single_File.Determine_Source_File_Dependencies(path);

     this->Warehouse_Objetcs_Dir = this->DepSelector_For_Single_File.Get_Warehouse_Objetcs_Dir();

     this->Warehouse_Path = this->DepSelector_For_Single_File.Get_Warehouse_Path();

     this->Com_Data_Extractor.Receive_Single_File_Dependency_Data(&this->DepSelector_For_Single_File);

     this->Com_Data_Extractor.Extract_Compiler_Data();

     this->Compiler_Data_Ptr = this->Com_Data_Extractor.Get_Compiler_Data_Address();

     this->Construct_Dependency_Map();

     /*

     this->Re_Arrange_Priorities();

     this->Order_Priorities();

     */

     this->Clear_Dynamic_Memory();

}


void Source_File_Dependency_Determiner::Collect_Dependency_Information(){

      this->Clear_Dynamic_Memory();

      this->DepSelector.Determine_Source_File_Dependencies();

      this->Warehouse_Objetcs_Dir = this->DepSelector.Get_Warehouse_Objetcs_Dir();

      this->Warehouse_Path = this->DepSelector.Get_Warehouse_Path();

      this->Com_Data_Extractor.Receive_Dependency_Data(&this->DepSelector);

      this->Com_Data_Extractor.Extract_Compiler_Data();

      this->Compiler_Data_Ptr = this->Com_Data_Extractor.Get_Compiler_Data_Address();

      this->Construct_Dependency_Map();

      /*

      this->Re_Arrange_Priorities();

      this->Order_Priorities();

      */

      this->Clear_Dynamic_Memory();

}


 void Source_File_Dependency_Determiner::Simple_Dependency_Determination_For_Single_Source_File(std::string path){

      this->Simple_Dep_Extractor.Extract_Dependency_Data(path);
 }



void Source_File_Dependency_Determiner::Construct_Dependency_Map(){

     for(int i=0;i< this->Compiler_Data_Ptr->size();i++){

         std::string name = this->Compiler_Data_Ptr->at(i).source_file_name_witout_ext;

         int dep_counter  = this->Compiler_Data_Ptr->at(i).priority;

         this->Dependency_Map.insert(std::make_pair(name,dep_counter));
     }
}



void Source_File_Dependency_Determiner::Re_Arrange_Priorities(){

     for(size_t i=0;i<this->Compiler_Data_Ptr->size();i++){

        for(size_t k=0;k<this->Compiler_Data_Ptr->at(i).dependent_headers.size();k++)
        {
            std::string file_name_with_ext;

            std::string header_name = this->Compiler_Data_Ptr->at(i).dependent_headers.at(k);

            this->Extract_File_Name_Without_Extention(file_name_with_ext,header_name);

            if(this->Check_Dependecy_Search_Status(file_name_with_ext)){

               int file_priority = this->Find_File_Priority(file_name_with_ext);

               int current_file_priority = this->Compiler_Data_Ptr->at(i).priority;

               if(file_priority>current_file_priority){

                  this->Compiler_Data_Ptr->at(i).priority = file_priority+1;
               }
            }        
        }     
     }
}


void Source_File_Dependency_Determiner::Extract_File_Name_Without_Extention(std::string & name, std::string name_with_ext){

     size_t name_size = name_with_ext.size();
    
     size_t end_point = 0;

     for(size_t i=0;i<name_size;i++){

         if(name_with_ext[i]== '.'){

            end_point = i;
         }
     }

     for(size_t i=0;i<end_point;i++){

         name.push_back(name_with_ext[i]);
     }

     name.shrink_to_fit();

}

bool Source_File_Dependency_Determiner::Check_Dependecy_Search_Status(std::string name){

     bool is_dependency_exist = false;

     if(this->Dependency_Map.find(name)!=this->Dependency_Map.end()){

        is_dependency_exist = true;
     }

     return is_dependency_exist;
}



int Source_File_Dependency_Determiner::Find_File_Priority(std::string name){

    try {        

         return  this->Dependency_Map.at(name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Source_File_Dependency_Determiner instance,";

         std::cout << "\n Inside Find_File_Priority,";


         std::cout << "\n the file priority information for" << name << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


void Source_File_Dependency_Determiner::Order_Priorities(){

     for(int i=0;i< this->Compiler_Data_Ptr->size();i++){

         for(int j=i;j< this->Compiler_Data_Ptr->size();j++){

             int dep_i = this->Compiler_Data_Ptr->at(i).priority;

             int dep_j = this->Compiler_Data_Ptr->at(j).priority;

             Compiler_Data temp;

             if( dep_i < dep_j){

                 temp  = this->Compiler_Data_Ptr->at(i);

                 this->Compiler_Data_Ptr->at(i) = this->Compiler_Data_Ptr->at(j);

                 this->Compiler_Data_Ptr->at(j) = temp;
              }
          }
      }
}

bool Source_File_Dependency_Determiner::Is_Source_File(std::string path){

     const FileData * ptr = this->Code_Rd.Find_File_Data_From_Path(path);

     bool is_source_file = ptr->is_source_file;

     return is_source_file;
}


bool Source_File_Dependency_Determiner::Is_Header_File(std::string path){

     const FileData * ptr = this->Code_Rd.Find_File_Data_From_Path(path);

     bool is_header_file = ptr->is_header_file;

     return is_header_file;
}


void Source_File_Dependency_Determiner::Print_Compiler_Orders(){

     for(int i=0;i< this->Compiler_Data_Ptr->size();i++){

         std::cout << "\n\n";

         std::cout << "\n ------------------------------------------";

         std::cout << "\n SOURCE FILE NUMBER:" << i;

         std::cout << "\n HEADER NAME:"

         <<  this->Compiler_Data_Ptr->at(i).source_file_name;

         std::cout << "\n HEADER PATH:"

         <<  this->Compiler_Data_Ptr->at(i).source_file_path;

         std::cout << "\n PRIORITY:"

         <<  this->Compiler_Data_Ptr->at(i).priority;

         std::vector<std::string> * Dep_Headers = &this->Compiler_Data_Ptr->at(i).dependent_headers;


         size_t dep_size = Dep_Headers->size();

         for(size_t k=0;k<dep_size;k++){
         
             std::cout << "\n Dependent header:" << Dep_Headers->at(k);         
         }

         std::vector<std::string> * Dep_Headers_Dirs = &this->Compiler_Data_Ptr->at(i).dependent_headers_dir;


         for(size_t k=0;k<dep_size;k++){
         
             std::cout << "\n Dependent header directory:" << Dep_Headers_Dirs->at(k);         
         }

         std::cout << "\n\n";
      }
}

void Source_File_Dependency_Determiner::Print_Dependency_List(){

     this->DepSelector.Print_Dependency_List();
}

Compiler_Data Source_File_Dependency_Determiner::Get_Compiler_Data(int i){

      return this->Compiler_Data_Ptr->at(i);
}

std::vector<Compiler_Data> * Source_File_Dependency_Determiner::Get_Compiler_Data_Address()
{
      return this->Compiler_Data_Ptr;
}

int Source_File_Dependency_Determiner::Get_Compiler_Data_Size(){

    return this->data_size;
}


std::string Source_File_Dependency_Determiner::Get_Warehouse_Objetcs_Dir(){

       return this->Warehouse_Objetcs_Dir;
}

std::string Source_File_Dependency_Determiner::Get_Warehouse_Path(){

       return this->Warehouse_Path;
}


 const Simple_Source_File_Dependency * Source_File_Dependency_Determiner::Get_Simple_File_Dependencies(){

      return this->Simple_Dep_Extractor.Get_Simple_Source_File_Dependency();
 }
