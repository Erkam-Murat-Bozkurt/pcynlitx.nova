
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

#include "GUI_List_Data_Recorder.hpp"


GUI_List_Data_Recorder::GUI_List_Data_Recorder(char opr_sis) 

   : Des_Reader (opr_sis,'g') , File_Manager(opr_sis)
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

     this->Place_Vector_Data(Data->compiler_options,this->compiler_options);

     this->Place_Vector_Data(Data->linker_options,this->linker_options);

     this->Place_Vector_Data(Data->compiler_paths,this->Compiler_Paths);



     this->Place_String_Data(Data->warehouse_location,this->warehouse_location);

     this->Place_String_Data(Data->root_dir,this->root_dir);

     this->Place_String_Data(Data->standard,this->standard); 

     this->Place_String_Data(Data->build_system_type,this->build_system_type); 

     this->Place_String_Data(Data->project_name,this->project_name); 

     this->Place_String_Data(Data->version_number,this->version_number); 
}


void GUI_List_Data_Recorder::Record_Data(std::string Data_Type, std::string Data_Record){
    
     this->Receive_Decriptor_File();

     if(Data_Type == "PROJECT-ROOT-DIR")
     {
        if(this->Is_Data_List(Data_Record)){

           std::cout << "\n There are more than one decleration for root directory";

           exit(EXIT_FAILURE);
        }

        this->Clear_String_Memory(this->root_dir);
        
        this->Place_String_Data(Data_Record,this->root_dir);
     }

     if(Data_Type == "PROJECT-WAREHOUSE-LOCATION"){

        if(this->Is_Data_List(Data_Record)){

           std::cout << "\n There are more than one decleration for project warhouse";

           exit(EXIT_FAILURE);
        }

        this->Clear_String_Memory(this->warehouse_location);

        this->Place_String_Data(Data_Record,this->warehouse_location);
     }

     if(Data_Type == "C++-STANDARD"){

        this->Clear_String_Memory(this->standard);

        this->Place_String_Data(Data_Record,this->standard);
     }  

     if(Data_Type == "BUILD-SYSTEM"){

        this->Clear_String_Memory(this->build_system_type);

        this->Place_String_Data(Data_Record,this->build_system_type);
     }  

     if(Data_Type == "PROJECT-NAME"){

        this->Clear_String_Memory(this->project_name);

        this->Place_String_Data(Data_Record,this->project_name);
     }  

     if(Data_Type == "VERSION-NUMBER"){

        this->Clear_String_Memory(this->version_number);

        this->Place_String_Data(Data_Record,this->version_number);
     }  


     this->Update_Descriptor_File();     
}


void GUI_List_Data_Recorder::Record_Data(std::string Data_Type, 

     std::vector<std::string> & Data_Record){
    
     this->Receive_Decriptor_File();

     if(Data_Type == "INCLUDE-DIRECTORIES"){

        this->Clear_String_Vector(this->Include_Directories);

        this->Place_Vector_Data(this->Include_Directories,Data_Record);    
     }

     if(Data_Type == "SOURCE-FILE-DIRECTORIES"){

        this->Clear_String_Vector(this->Source_File_Directories);

        this->Place_Vector_Data(this->Source_File_Directories,Data_Record);  
     }

     if(Data_Type == "LIBRARY-DIRECTORIES"){

        this->Clear_String_Vector(this->Library_Directories);

        this->Place_Vector_Data(this->Library_Directories,Data_Record);        
     }

     if(Data_Type == "LIBRARY-FILES"){

        this->Clear_String_Vector(this->Library_Files);

        this->Place_Vector_Data(this->Library_Files,Data_Record);        
     }

     if(Data_Type == "COMPILER-OPTIONS"){

        this->Clear_String_Vector(this->compiler_options);

        this->Place_Vector_Data(this->compiler_options,Data_Record);       
     }  

     if(Data_Type == "LINKER-OPTIONS"){

        this->Clear_String_Vector(this->linker_options);

        this->Place_Vector_Data(this->linker_options,Data_Record);       
     }    

     if(Data_Type == "EXECUTABLE-FILE-NAMES"){

        this->Clear_String_Vector(this->Exe_File_Names);

        this->Place_Vector_Data(this->Exe_File_Names,Data_Record);          
     }

     if(Data_Type == "MAIN-FILE-NAMES"){

        this->Clear_String_Vector(this->Main_File_Names);

        this->Place_Vector_Data(this->Main_File_Names,Data_Record);          
     }        

     
     if(Data_Type == "MAIN-FILE-NAMES"){

        this->Clear_String_Vector(this->Main_File_Names);

        this->Place_Vector_Data(this->Main_File_Names,Data_Record);          
     }    

     
     if(Data_Type == "COMPILER-PATHS"){

        this->Clear_String_Vector(this->Compiler_Paths);

        this->Place_Vector_Data(this->Compiler_Paths,Data_Record);          
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


     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[BUILD-SYSTEM]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->build_system_type);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);



     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[PROJECT-NAME]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->project_name);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);


     
     this->WriteNewLines(two_lines);

     this->File_Manager.WriteToFile("[VERSION-NUMBER]{");

     this->WriteNewLines(single_line);

     this->Write_String_Data(this->version_number);

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


     this->File_Manager.WriteToFile("[COMPILER-OPTIONS]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->compiler_options);

     this->WriteNewLines(single_line);

     this->File_Manager.WriteToFile("}");

     this->WriteNewLines(two_lines);



     this->File_Manager.WriteToFile("[LINKER-OPTIONS]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->linker_options);

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


     this->File_Manager.WriteToFile("[COMPILER-PATHS]{");

     this->WriteNewLines(single_line);

     this->Write_Vector_Data(this->Compiler_Paths);

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

     this->Place_String_Data(this->Des_Reader.Get_Standard(),this->standard);   

     this->Place_Vector_Data(this->Des_Reader.Get_Linker_Options(),this->linker_options);

     this->Place_Vector_Data(this->Des_Reader.Get_Compiler_Options(),this->compiler_options);

     this->Place_Vector_Data(this->Des_Reader.Get_Compiler_Paths(),this->Compiler_Paths);


     std::string project_name   = this->Des_Reader.Get_Project_Name();

     std::string version_number = this->Des_Reader.Get_Version_Number();


     this->Place_String_Data(project_name,this->project_name);

     this->Place_String_Data(version_number,this->version_number);
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

     this->Clear_String_Vector(this->Compiler_Paths);

     this->Clear_String_Memory(this->standard);

     this->Clear_String_Vector(this->linker_options);

     this->Clear_String_Vector(this->compiler_options);

     this->Clear_String_Memory(this->warehouse_location);

     this->Clear_String_Memory(this->root_dir);

     this->Clear_String_Memory(this->build_system_type);

     this->Clear_String_Memory(this->project_name);

     this->Clear_String_Memory(this->version_number);
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



