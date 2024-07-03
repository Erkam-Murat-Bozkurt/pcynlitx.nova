
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

#include "GUI_List_Data_Recorder.hpp"


GUI_List_Data_Recorder::GUI_List_Data_Recorder(char opr_sis) : Des_Reader (opr_sis,'g') , File_Manager(opr_sis)
{
    this->opr_sis = opr_sis;

    this->Des_Reader.Set_Gui_Read_Status(true);

    bool Data_Receive_Cond = true;

    this->Des_Reader.Receive_Data_Record_Condition(Data_Receive_Cond);

    this->Memory_Delete_Condition = false;
}


GUI_List_Data_Recorder::~GUI_List_Data_Recorder(){

     if(!this->Memory_Delete_Condition){

        this->Clear_Object_Memory();
     }
}

void GUI_List_Data_Recorder::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_Dynamic_Memory();

        this->File_Manager.Clear_Dynamic_Memory();

        this->Des_Reader.Clear_Dynamic_Memory();
     }
}

void GUI_List_Data_Recorder::Clear_Dynamic_Memory(){

     this->Clear_Data_Memory();
}


void GUI_List_Data_Recorder::Receive_Descriptor_File_Path(std::string DesPATH){

     this->Descriptor_File_Path = DesPATH;

     this->File_Manager.SetFilePath(DesPATH);

     this->Des_Reader.Receive_Descriptor_File_Path(DesPATH);
}


void GUI_List_Data_Recorder::Receive_Descriptions_Record_Data(Record_Data_For_Gui * Data){

     this->Clear_Data_Memory();

     this->Place_Vector_Data(Data->Include_Directories,this->Include_Directories);

     this->Place_Vector_Data(Data->Source_File_Directories,this->Source_File_Directories);

     this->Place_Vector_Data(Data->Library_Directories,this->Library_Directories);

     this->Place_Vector_Data(Data->Library_Files,this->Library_Files);

     this->Place_String_Data(Data->warehouse_location,this->warehouse_location);

     this->Place_String_Data(Data->root_dir,this->root_dir);

     this->Place_String_Data(Data->options,this->options);

     this->Place_String_Data(Data->standard,this->standard); 
}


void GUI_List_Data_Recorder::Record_Data(std::string Data_Type, std::string Data_Record){
    
     this->Clear_Data_Memory();

     this->Receive_Decriptor_File();

     std::string data_type, data_record;

     this->Place_String_Data(Data_Type,data_type);

     this->Place_String_Data(Data_Record,data_record);

     if(data_type == "PROJECT-ROOT-DIR")
     {
        if(this->Is_Data_List(data_record)){

           std::cout << "\n There are more than one decleration for root directory";

           exit(EXIT_FAILURE);
        }

        this->Clear_String_Memory(this->root_dir);
        
        this->Place_String_Data(data_record,this->root_dir);
     }


     if(data_type == "PROJECT-WAREHOUSE-LOCATION"){

        if(this->Is_Data_List(data_record)){

           std::cout << "\n There are more than one decleration for project warhouse";

           exit(EXIT_FAILURE);
        }

        this->Clear_String_Memory(this->warehouse_location);

        this->Place_String_Data(data_record,this->warehouse_location);
     }

     if(data_type == "INCLUDE-DIRECTORIES"){

        this->Clear_String_Vector(this->Include_Directories);

        this->Extract_Data_List(this->Include_Directories,data_record);    
     }

     if(data_type == "SOURCE-FILE-DIRECTORIES"){

        this->Clear_String_Vector(this->Source_File_Directories);

        this->Extract_Data_List(this->Source_File_Directories,data_record);  
     }

     if(data_type == "LIBRARY-DIRECTORIES"){

        this->Clear_String_Vector(this->Library_Directories);

        this->Extract_Data_List(this->Library_Directories,data_record);        
     }

     if(data_type == "LIBRARY-FILES"){

        this->Clear_String_Vector(this->Library_Files);

        this->Extract_Data_List(this->Library_Files,data_record);        
     }

     if(data_type == "EXECUTABLE-FILE-NAMES"){

        this->Clear_String_Vector(this->Exe_File_Names);

        this->Extract_Data_List(this->Exe_File_Names,data_record);        
     }

     if(data_type == "MAIN-FILE-NAMES"){

        this->Clear_String_Vector(this->Main_File_Names);

        this->Extract_Data_List(this->Main_File_Names,data_record);        
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



void GUI_List_Data_Recorder::Update_Descriptor_File(){
     
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


void GUI_List_Data_Recorder::Receive_Decriptor_File(){

     this->Clear_Data_Memory();

     this->Des_Reader.Read_Descriptor_File();

     this->Place_Vector_Data(this->Des_Reader.Get_Include_Directories(),this->Include_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Source_File_Directories(),this->Source_File_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Library_Directories(),this->Library_Directories);

     this->Place_Vector_Data(this->Des_Reader.Get_Library_Files(),this->Library_Files);

     this->Place_String_Data(this->Des_Reader.Get_Warehouse_Location(),this->warehouse_location);

     this->Place_String_Data(this->Des_Reader.Get_Repo_Directory_Location(),this->root_dir);

     std::string compiler_options = this->Des_Reader.Get_Compiler_Options();

     std::string linker_options   = this->Des_Reader.Get_Linker_Options();

     std::string total_options = compiler_options + linker_options;

     this->Place_String_Data(total_options,this->options);

     this->Place_String_Data(this->Des_Reader.Get_Standard(),this->standard);   
}


void GUI_List_Data_Recorder::WriteNewLines(int line_number){

     for(int i=0;i<line_number;i++){

        this->File_Manager.WriteToFile("\n");
     }
}

void GUI_List_Data_Recorder::Write_Vector_Data(std::vector<std::string> & vec){

     for(size_t i=0;i<vec.size();i++){

         this->File_Manager.WriteToFile("\n ");

         this->File_Manager.WriteToFile(vec.at(i));         
     }     
}


void GUI_List_Data_Recorder::Write_String_Data(std::string dt){

     this->File_Manager.WriteToFile("\n  ");   

     this->File_Manager.WriteToFile(dt);
}

void GUI_List_Data_Recorder::Clear_Data_Memory(){

     this->Clear_String_Vector(this->Include_Directories);

     this->Clear_String_Vector(this->Source_File_Directories);

     this->Clear_String_Vector(this->Library_Directories);

     this->Clear_String_Vector(this->Library_Files);

     this->Clear_String_Memory(this->standard);

     this->Clear_String_Memory(this->options);

     this->Clear_String_Memory(this->warehouse_location);

     this->Clear_String_Memory(this->root_dir);
}


bool GUI_List_Data_Recorder::Is_Data_List(std::string data){

     bool is_data_list = false;

     size_t new_line_counter=0;

     data.shrink_to_fit();

     for(size_t i=0;i<data.size();i++){

         if(data.at(i) == '\n') {

             new_line_counter++;
         }
     }

     if(new_line_counter>1){

        is_data_list = true;
     }

     return is_data_list;
}


void GUI_List_Data_Recorder::Extract_Data_List(std::vector<std::string> & vec, std::string data){

     std::vector<std::string> temp_list;

     data.shrink_to_fit();

     size_t data_size = data.size();
    
     size_t start_point = 0, next_point=0;

     for(size_t i=0;i<data_size;i++){

         std::string line_data;

         for(size_t k=start_point;k<data_size;k++){

             if(data.at(k) == '\n'){

                next_point = k+1; 

                break;
             }
         }

         for(size_t k=start_point;k<data_size;k++){

             if(data.at(k) != '\n'){

                line_data.push_back(data.at(k));
            
                i++;
             }
             else{

                break;
             }
         }

         if(line_data.back()!='\n'){

            line_data.push_back('\n');
         }

         line_data.shrink_to_fit();

         if(line_data.size()>0){

            temp_list.push_back(line_data);
         }

         start_point = next_point;
     }

     temp_list.shrink_to_fit();

     for(size_t i=0;i<temp_list.size();i++){

         vec.push_back(temp_list.at(i));
     }

     vec.shrink_to_fit();

     this->Clear_String_Vector(temp_list);
}

void GUI_List_Data_Recorder::Place_Vector_Data(const std::vector<std::string> & base_vec, 

     std::vector<std::string> & target_vec){

     for(size_t i=0;i<base_vec.size();i++){

         target_vec.push_back(base_vec.at(i));
     }

     target_vec.shrink_to_fit();
}


void GUI_List_Data_Recorder::Place_String_Data(const std::string & base_str, std::string & target_str){

     for(size_t i=0;i<base_str.size();i++){

         target_str.push_back(base_str.at(i));
     }

     target_str.shrink_to_fit();
}


void GUI_List_Data_Recorder::Place_String_Data(char * base_str, std::string & target_str){

     for(size_t i=0;i<strlen(base_str);i++){

         target_str.push_back(base_str[i]);
     }

     target_str.shrink_to_fit();
}




void GUI_List_Data_Recorder::Clear_String_Vector(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     if(!vec.empty()){

        for(size_t i=0;i<vec.size();i++){

            this->Clear_String_Memory(vec.at(i));
        }

        vec.clear();

        vec.shrink_to_fit();
     }
}


void GUI_List_Data_Recorder::Clear_String_Memory(std::string & str){

     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}



