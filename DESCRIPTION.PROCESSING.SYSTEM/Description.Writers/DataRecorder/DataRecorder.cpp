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

#include "DataRecorder.h"

DataRecorder::DataRecorder(char * Path, char opr_sis) : Des_Reader(opr_sis)

{
    if(!this->File_Manager.Is_Path_Exist(Path)){

       std::cout << "\n The project file is not exist on the given path";

       exit(EXIT_FAILURE);
    }

    if(this->File_Manager.Is_This_File_Empty(Path)){

       std::cout << "\n The project file is empty";

       exit(EXIT_FAILURE);
    }

    this->Des_Reader.Receive_Descriptor_File_Path(Path);

    bool Data_Receive_Cond = true;

    this->Des_Reader.Receive_Data_Record_Condition(Data_Receive_Cond);

    this->File_Manager.SetFilePath(Path);

    this->Memory_Delete_Condition = false;
}

DataRecorder::~DataRecorder(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Object_Memory();
     }
}

void DataRecorder::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Dynamic_Memory();

        this->File_Manager.Clear_Dynamic_Memory();

        this->Des_Reader.Clear_Dynamic_Memory();
     }
}

void DataRecorder::Clear_Dynamic_Memory(){

     this->Clear_Data_Memory();
}


void DataRecorder::Add_Data_Record(char * Data_Type, char * Data_Record){
    
     this->Receive_Decriptor_File();

     std::string data_type, data_record;

     this->Place_String_Data(Data_Type,data_type);

     this->Place_String_Data(Data_Record,data_record);

     if(data_type == "PROJECT-ROOT-DIR"){

        this->Clear_String_Memory(this->root_dir);
        
        this->Place_String_Data(data_record,this->root_dir);
     }

     if(data_type == "INCLUDE-DIRECTORIES"){

        this->Include_Directories.push_back(data_record);
     }

     if(data_type == "SOURCE-FILE-DIRECTORIES"){

        this->Source_File_Directories.push_back(data_record);
     }

     if(data_type == "LIBRARY-DIRECTORIES"){

        this->Library_Directories.push_back(data_record);
     }

     if(data_type == "LIBRARY-FILES"){

        this->Library_Files.push_back(data_record);
     }

     if(data_type == "PROJECT-WAREHOUSE-LOCATION"){

        this->Clear_String_Memory(this->warehouse_location);

        this->Place_String_Data(this->warehouse_location,data_record);
     }

     if(data_type == "EXECUTABLE-FILE-NAMES"){

        this->Exe_File_Names.push_back(data_record);
     }

     if(data_type == "MAIN-FILE-NAMES"){

        this->Main_File_Names.push_back(data_record);
     }                    

     if(data_type == "C++-STANDARD"){

        this->Clear_String_Memory(this->standard);

        this->Place_String_Data(this->standard,data_record);
     }  

     if(data_type == "OPTIONS"){

        this->Clear_String_Memory(this->options);

        this->Place_String_Data(this->options,data_record);       
     }    

     this->Update_Descriptor_File();
}


void DataRecorder::Clear_Data_Record(char * Data_Type){
          
     this->Receive_Decriptor_File();

     std::string data_type;

     this->Place_String_Data(Data_Type,data_type);


     if(data_type == "PROJECT-ROOT-DIR"){

        this->Clear_String_Memory(this->root_dir);        
     }

     if(data_type == "INCLUDE-DIRECTORIES"){

        this->Clear_String_Vector(this->Include_Directories);
     }


     if(data_type == "SOURCE-FILE-DIRECTORIES"){

        this->Clear_String_Vector(this->Source_File_Directories);
     }

     if(data_type == "LIBRARY-DIRECTORIES"){

        this->Clear_String_Vector(this->Library_Directories);
     }

     if(data_type == "LIBRARY-FILES"){

        this->Clear_String_Vector(this->Library_Files);
     }

     if(data_type == "PROJECT-WAREHOUSE-LOCATION"){

        this->Clear_String_Memory(this->warehouse_location);
     }

     if(data_type == "EXECUTABLE-FILE-NAMES"){

        this->Clear_String_Vector(this->Exe_File_Names);
     }

     if(data_type == "MAIN-FILE-NAMES"){

        this->Clear_String_Vector(this->Main_File_Names);
     }                    

     if(data_type == "C++-STANDARD"){

        this->Clear_String_Memory(this->standard);
     }  

     if(data_type == "OPTIONS"){

        this->Clear_String_Memory(this->options);
     }     

     this->Update_Descriptor_File();
}


void DataRecorder::Update_Descriptor_File(){
     
     this->File_Manager.FileOpen(RWCf);

     this->File_Manager.WriteToFile("\n\n");

     this->File_Manager.WriteToFile("DESCRIPTOR FILE FOR PCYNLITX BUILD SYSTEM");

     int two_lines = 2, single_line=1;


     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[PROJECT-ROOT-DIR]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->root_dir);
     
     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");



     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[PROJECT-WAREHOUSE-LOCATION]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->warehouse_location);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");



     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[C++-STANDARD]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->standard);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[INCLUDE-DIRECTORIES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Include_Directories);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[SOURCE-FILE-DIRECTORIES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Source_File_Directories);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[LIBRARY-DIRECTORIES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Library_Directories);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);



     this->File_Manager.WriteToFile("[LIBRARY-FILES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Library_Files);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[OPTIONS]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->options);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[MAIN-FILE-NAMES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Main_File_Names);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[EXECUTABLE-FILE-NAMES]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Exe_File_Names);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     this->File_Manager.WriteToFile("[END]:");

     this->WriteNewLines(two_lines);

     this->File_Manager.FileClose();
}



void DataRecorder::Replace_Data_Record(char * Data_Type,  char * Data_Record){

     this->Receive_Decriptor_File();

     std::string data_type, data_record;

     this->Place_String_Data(Data_Type,data_type);

     this->Place_String_Data(Data_Record,data_record);

     if(data_type == "PROJECT-ROOT-DIR"){

        this->Clear_String_Memory(this->root_dir);
        
        this->Place_String_Data(data_record,this->root_dir);
     }

     if(data_type == "PROJECT-WAREHOUSE-LOCATION"){

        this->Clear_String_Memory(this->warehouse_location);

        this->Place_String_Data(data_record,this->warehouse_location);
     }

     if(data_type == "C++-STANDARD"){

        this->Clear_String_Memory(this->standard);

        this->Place_String_Data(data_record,this->standard);

     }  

     if(data_type == "OPTIONS"){

        this->Clear_String_Memory(this->options);

        this->Place_String_Data(data_record,this->options);
     }     

     this->Update_Descriptor_File();
}



void DataRecorder::Replace_Data_Record(char * Data_Type,  std::vector<std::string> & vec){

     this->Receive_Decriptor_File();


     std::string data_type, data_record;

     this->Place_String_Data(Data_Type,data_type);

     if(data_type == "INCLUDE-DIRECTORIES"){

        this->Clear_String_Vector(this->Include_Directories);
  
        this->Place_Vector_Data(this->Include_Directories,vec);
     }

     if(data_type == "SOURCE-FILE-DIRECTORIES"){

        this->Clear_String_Vector(this->Source_File_Directories);

        this->Place_Vector_Data(this->Source_File_Directories,vec);
     }

     if(data_type == "LIBRARY-DIRECTORIES"){

        this->Clear_String_Vector(this->Library_Directories);

        this->Place_Vector_Data(this->Library_Directories,vec);
     }

     if(data_type == "LIBRARY-FILES"){

        this->Clear_String_Vector(this->Library_Files);

        this->Place_Vector_Data(this->Library_Files,vec);
     }


     if(data_type == "EXECUTABLE-FILE-NAMES"){

        this->Clear_String_Vector(this->Exe_File_Names);

        this->Place_Vector_Data(this->Exe_File_Names,vec);
     }

     if(data_type == "MAIN-FILE-NAMES"){

        this->Clear_String_Vector(this->Main_File_Names);

        this->Place_Vector_Data(this->Main_File_Names,vec);
     }                    

     this->Update_Descriptor_File();
}


void DataRecorder::Receive_Decriptor_File(){

     this->Des_Reader.Read_Descriptor_File();

     this->Place_Vector_Data(this->Des_Reader.Get_Include_Directories(),this->Include_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Source_File_Directories(),this->Source_File_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Library_Directories(),this->Library_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Library_Files(),this->Library_Files);

     this->Place_String_Data(this->Des_Reader.Get_Warehouse_Location(),this->warehouse_location);

     this->Place_String_Data(this->Des_Reader.Get_Repo_Directory_Location(),this->root_dir);

     this->Place_String_Data(this->Des_Reader.Get_Options(),this->options);

     this->Place_String_Data(this->Des_Reader.Get_Standard(),this->standard);   
}


void DataRecorder::WriteNewLines(int line_number){

     for(int i=0;i<line_number;i++){

        this->File_Manager.WriteToFile("\n");
     }
}

void DataRecorder::Write_Vector_Data(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         this->File_Manager.WriteToFile("\n ");   

         this->File_Manager.WriteToFile(vec.at(i));
     }     
}


void DataRecorder::Write_String_Data(std::string dt){

     this->File_Manager.WriteToFile("\n  ");   

     this->File_Manager.WriteToFile(dt);
}

void DataRecorder::Clear_Data_Memory(){

     this->Clear_String_Vector(this->Include_Directories);

     this->Clear_String_Vector(this->Source_File_Directories);

     this->Clear_String_Vector(this->Library_Directories);

     this->Clear_String_Vector(this->Library_Files);

     this->Clear_String_Memory(this->standard);

     this->Clear_String_Memory(this->options);

     this->Clear_String_Memory(this->warehouse_location);

     this->Clear_String_Memory(this->root_dir);
}


void DataRecorder::Place_Vector_Data(const std::vector<std::string> & base_vec, 

     std::vector<std::string> & target_vec){

     for(size_t i=0;i<base_vec.size();i++){

         target_vec.push_back(base_vec.at(i));
     }

     target_vec.shrink_to_fit();
}


void DataRecorder::Place_String_Data(const std::string & base_str, std::string & target_str){

     for(size_t i=0;i<base_str.size();i++){

         target_str.push_back(base_str.at(i));
     }

     target_str.shrink_to_fit();
}


void DataRecorder::Place_String_Data(char * base_str, std::string & target_str){

     for(size_t i=0;i<strlen(base_str);i++){

         target_str.push_back(base_str[i]);
     }

     target_str.shrink_to_fit();
}




void DataRecorder::Clear_String_Vector(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     if(!vec.empty()){

        for(size_t i=0;i<vec.size();i++){

            this->Clear_String_Memory(vec.at(i));
        }

        vec.clear();

        vec.shrink_to_fit();
     }
}


void DataRecorder::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}



