

/*
 *
 * Copyright ©  2025,  Erkam Murat Bozkurt
 *
 * This file is part of the research project which is carried by Erkam Murat Bozkurt.
 * 
 * This is a free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation
 * either version 3 of the License, or any later version.
 * 
 * This software is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 */



#include "Executable_MakeFile_ComConstructor.hpp"

Executable_MakeFile_ComConstructor::Executable_MakeFile_ComConstructor(char opr_sis) :

   Information_Collector(opr_sis)

{
       this->opr_sis = opr_sis;

}

Executable_MakeFile_ComConstructor::~Executable_MakeFile_ComConstructor()
{
       this->Clear_Dynamic_Memory();
}


void Executable_MakeFile_ComConstructor::Clear_Dynamic_Memory(){

     this->Clear_Vector_Memory(&this->header_file_list);

     this->Clear_Vector_Memory(&this->header_file_dirs);

     this->Clear_Vector_Memory(&this->header_file_paths);

     this->Clear_Vector_Memory(&this->object_file_list);

     this->Clear_String_Memory(&this->git_src_dir);

     this->Clear_String_Memory(&this->src_file_dir);

     this->Clear_String_Memory(&this->source_file_name);

     this->Clear_String_Memory(&this->make_file_name);

     this->Clear_String_Memory(&this->Compiler_System_Command);

     this->Clear_String_Memory(&this->Dependency_Determination_Command);

     this->Clear_String_Memory(&this->include_directory_list_for_compiler_command);

     this->Clear_String_Memory(&this->source_file_directory_list_for_compiler_command);

     this->Clear_String_Memory(&this->library_directory_list_for_compiler_command);

     this->Clear_String_Memory(&this->include_file_list_for_compiler_command);

     this->Clear_String_Memory(&this->library_path_list_for_compiler_command);

     this->Clear_String_Memory(&this->external_include_directory_list_for_compiler_command);

     this->Clear_String_Memory(&this->compiler_options_list_for_compiler_command);

     this->Clear_String_Memory(&this->linker_options_list_for_compiler_command);
}



void Executable_MakeFile_ComConstructor::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){
     
     this->Des_Reader = ptr;

     this->Information_Collector.Receive_Descriptor_File_Reader(ptr);
}


void Executable_MakeFile_ComConstructor::Receive_Dependency_Determiner(Source_File_Dependency_Determiner * ptr){

     this->Dep_Determiner = ptr;

     this->Information_Collector.Receive_Dependency_Determiner(this->Dep_Determiner);
}



void Executable_MakeFile_ComConstructor::Receive_ExeFileName(std::string name){

     this->Exe_Name = name;
}


void Executable_MakeFile_ComConstructor::Receive_Construction_Strategy(char strategy){

     this->constraction_strategy = strategy;

     this->Information_Collector.Receive_Construction_Strategy(strategy);
}


void Executable_MakeFile_ComConstructor::Construct_Compiler_Commands(std::string main_file_path){

     // Receiving the compiler data from the member objects

     this->warehouse_obj_dir  = this->Dep_Determiner->Get_Warehouse_Objetcs_Dir();

     this->warehouse_path     = this->Dep_Determiner->Get_Warehouse_Path();


     this->Information_Collector.Determine_Src_File_Dir(main_file_path,this->src_file_dir);

     this->Information_Collector.Determine_Git_Src_Dir(this->git_src_dir,this->src_file_dir);

     this->Information_Collector.Determine_Make_File_Name(this->make_file_name,main_file_path,this->src_file_dir);

     this->Information_Collector.Determine_Source_File_Name(this->source_file_name,main_file_path,this->src_file_dir);

     this->Information_Collector.Construct_Library_Directory_List_For_Compiler_Command(this->library_directory_list_for_compiler_command);

     this->Information_Collector.Determine_Project_Library_Name(this->project_library_name);

     this->Information_Collector.Determine_Library_File_Path_List_For_Compiler_Command(this->library_path_list_for_compiler_command);

     this->Information_Collector.Determine_External_Include_Directory_List_For_Compiler_Command(this->external_include_directory_list_for_compiler_command);
    
     this->Information_Collector.Determine_Compiler_Options_For_Compiler_Command(this->compiler_options_list_for_compiler_command);

     this->Information_Collector.Determine_Linker_Options_For_Compiler_Command(this->linker_options_list_for_compiler_command);



     if(this->constraction_strategy == 'a'){

        this->Comp_Data_ptr =  this->Dep_Determiner->Get_Compiler_Data_Address();

        this->Construct_Header_File_List();

        this->Construct_Object_File_List();

        this->Dependency_Determination_Command_Construction();

        this->Determine_Compiler_System_Command();
     }
     else{

          this->Simple_Data_Ptr = this->Dep_Determiner->Get_Simple_File_Dependencies();

          this->Construct_Header_File_List_For_Simple_Construction();

          this->Information_Collector.Determine_Include_Directory_List_For_Simple_Construction(this->include_directory_list_for_compiler_command,
            
               this->header_file_dirs);

          this->Information_Collector.Determine_Source_File_Directory_List_For_Simple_Construction(this->source_file_directory_list_for_compiler_command);

          this->Information_Collector.Determine_Include_File_List_For_Simple_Construction(this->include_file_list_for_compiler_command,this->header_file_paths);

          this->Determine_Dependency_Determination_Command_For_Simple_Construction();

          this->Determine_Compiler_System_Command_For_Simple_Construction();
     }
}


void Executable_MakeFile_ComConstructor::Determine_Compiler_System_Command(){

     std::string object_file_name = this->Comp_Data_ptr->at(0).object_file_name;

     std::string dependency_file_name = this->Comp_Data_ptr->at(0).source_file_name_witout_ext + "_depends.d" ;

     std::string make_target_name = object_file_name + ": $(" +  dependency_file_name + ") \n";

     std::string go_to_new_line = "\\\n\t";

     this->Compiler_System_Command = make_target_name + "\n\t";

     this->Compiler_System_Command += go_to_new_line;

     const std::vector<Library_Data> & data_list = this->Des_Reader->Get_Library_File_Data_List();

     for(size_t i=0;i<data_list.size();i++){

         this->Compiler_System_Command += data_list.at(i).library_name_with_ext;

         this->Compiler_System_Command += " ";

         this->Compiler_System_Command += go_to_new_line;
     }
     
     this->Compiler_System_Command += go_to_new_line;



     std::string compiler_input_command = "g++ -Wall -c -std=c++17"; 

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     std::string Space_Character = " ";


     this->Place_String(&this->Compiler_System_Command,compiler_input_command);

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);

     if(!compiler_options.empty()){

        for(size_t i=0;i<compiler_options.size();i++){

            this->Place_String(&this->Compiler_System_Command,compiler_options.at(i));

            this->Place_String(&this->Compiler_System_Command,Space_Character);

            this->Place_String(&this->Compiler_System_Command,go_to_new_line);
        }
     }     

     this->Compiler_System_Command +=  " $@ ";

     this->Compiler_System_Command.shrink_to_fit();
}


void Executable_MakeFile_ComConstructor::Construct_Header_File_List(){

     Compiler_Data Data = this->Comp_Data_ptr->at(0);

     size_t list_size = Data.dependent_headers.size();

     for(int i=0;i<list_size;i++){

         std::string header_name = Data.dependent_headers.at(i);

         std::string header_dir = Data.dependent_headers_dir.at(i);

         std::string upper_dir  = Data.upper_directories.at(i);

         std::string header_path;

         if(!header_name.empty()){
                  
            this->header_file_list.push_back(header_name);
            
            this->header_file_dirs.push_back(header_dir);

            header_path += header_dir;

            if(this->opr_sis=='w'){

               header_path.push_back('\\');
            }

            if(this->opr_sis=='l'){

               header_path.push_back('/');
            }

            header_path += header_name;

            this->header_file_paths.push_back(header_path);

            this->header_file_upper_dirs.push_back(upper_dir);
         }
     }
}


void Executable_MakeFile_ComConstructor::Construct_Object_File_List(){

     size_t list_size = this->Comp_Data_ptr->size();

     size_t counter = 0;

     for(int i=0;i<list_size;i++){

         std::string Object_File_Name = this->Comp_Data_ptr->at(i).object_file_name;

         if(!Object_File_Name.empty()){

            this->object_file_list.push_back(Object_File_Name);
         }
     }

     this->object_file_list.shrink_to_fit();
}


void Executable_MakeFile_ComConstructor::Dependency_Determination_Command_Construction()
{
     this->Clear_String_Memory(&this->Dependency_Determination_Command);

     const std::vector<std::string> & compiler_options = this->Des_Reader->Get_Compiler_Options();

     const std::vector<std::string> & linker_options   = this->Des_Reader->Get_Linker_Options();

     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] ="$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] ="$(PROJECT_OBJECTS_LOCATION)";

     char Library_Location [] = "$(PROJECT_LIBRARY_LOCATION)";

     char Source_Location []  ="$(SOURCE_LOCATION)";


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;



     std::string compiler_input_command = "g++ -std=c++17 ";

     std::string file_name_ = this->source_file_name_without_ext + "_depends.d " ;

     compiler_input_command += "-c -MD -MF ";
     
     compiler_input_command += file_name_;

     compiler_input_command += "-o ";



     this->Place_Information(&this->Dependency_Determination_Command,compiler_input_command);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,this->Exe_Name);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     this->Dependency_Determination_Command += this->compiler_options_list_for_compiler_command;

     this->Dependency_Determination_Command += this->linker_options_list_for_compiler_command;

     
     std::vector<std::string> dir_buffer;

     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     for(size_t i=0;i<this->header_file_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,this->header_file_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&this->Dependency_Determination_Command,Include_Character);

             this->Place_Information(&this->Dependency_Determination_Command,this->header_file_dirs[i]);

             this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

             this->Place_Information(&this->Dependency_Determination_Command,slash);

             this->Place_Information(&this->Dependency_Determination_Command,new_line);

             this->Place_Information(&this->Dependency_Determination_Command,tab);
         }

         dir_buffer.push_back(this->header_file_dirs[i]);
     }


     for(size_t i=0;i<this->header_file_upper_dirs.size();i++){

         bool is_dir_exist = this->Check_Include_Directory_Existance(&dir_buffer,this->header_file_upper_dirs[i]);

         if(!is_dir_exist){

             this->Place_Information(&this->Dependency_Determination_Command,Include_Character);

             this->Place_Information(&this->Dependency_Determination_Command,this->header_file_upper_dirs[i]);

             this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

             this->Place_Information(&this->Dependency_Determination_Command,slash);

             this->Place_Information(&this->Dependency_Determination_Command,new_line);

             this->Place_Information(&this->Dependency_Determination_Command,tab);
         }

         dir_buffer.push_back(this->header_file_upper_dirs[i]);
     }

     this->Clear_Vector_Memory(&dir_buffer); 


     this->Place_Information(&this->Dependency_Determination_Command,Include_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     int  included_dir_num = this->Des_Reader->Get_Include_Directory_Number();


     char include_dir_symbol [] = "$(EXTERNAL_INCLUDE_DIR_";

     char makro_end [] = ")";

     int  sizer = 0;

     for(int i=0;i<included_dir_num;i++){

         std::string included_dir = this->Des_Reader->Get_Include_Directory(i);

         std::string dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Dependency_Determination_Command,Include_Character);

         this->Place_Information(&this->Dependency_Determination_Command,include_dir_symbol);

         this->Place_Information(&this->Dependency_Determination_Command,dir_index);

         this->Place_Information(&this->Dependency_Determination_Command,makro_end);

         this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

         this->Place_Information(&this->Dependency_Determination_Command,slash);

         this->Place_Information(&this->Dependency_Determination_Command,new_line);

         this->Place_Information(&this->Dependency_Determination_Command,tab);
     }




     this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Library_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);



     this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Objects_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     int  library_dir_num = this->Des_Reader->Get_Library_Directory_Number();

     sizer = 0;

     for(int i=0;i<library_dir_num;i++){

         std::string library_dir = this->Des_Reader->Get_Library_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

         this->Place_Information(&this->Dependency_Determination_Command,library_dir);

         this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

         this->Place_Information(&this->Dependency_Determination_Command,slash);

         this->Place_Information(&this->Dependency_Determination_Command,new_line);

         this->Place_Information(&this->Dependency_Determination_Command,tab);
     }




     std::string go_to_new_line = "\\\n\t";


     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,this->source_file_name);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,go_to_new_line);


     size_t obj_list_size = this->object_file_list.size();


     for(size_t i=1;i<obj_list_size;i++){

         this->Place_Information(&this->Dependency_Determination_Command,Objects_Location);

         this->Place_Information(&this->Dependency_Determination_Command,slash);

         this->Place_Information(&this->Dependency_Determination_Command,this->object_file_list[i]);

         this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

         this->Place_Information(&this->Dependency_Determination_Command,go_to_new_line);
     }

     size_t hdr_list_size = this->header_file_paths.size();

     for(size_t i=0;i<hdr_list_size;i++){

         this->Place_Information(&this->Dependency_Determination_Command,include_word);

         this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

         this->Place_Information(&this->Dependency_Determination_Command,this->header_file_paths[i]);

         this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

         if(i<(hdr_list_size-1)){
         
            this->Place_Information(&this->Dependency_Determination_Command,go_to_new_line);            
         }
     }

     this->Place_Information(&this->Dependency_Determination_Command,go_to_new_line);            


     const std::vector<Library_Data> & data_list = this->Des_Reader->Get_Library_File_Data_List();

     for(size_t i=0;i<data_list.size();i++){

         this->Dependency_Determination_Command += "-l";

         this->Dependency_Determination_Command += data_list.at(i).library_name_with_ext;

         this->Dependency_Determination_Command += " ";

         this->Dependency_Determination_Command += go_to_new_line;
     }
     
     this->Dependency_Determination_Command += this->project_library_name;

     this->Dependency_Determination_Command += "\n\n\t";
}





void Executable_MakeFile_ComConstructor::Determine_Compiler_System_Command_For_Simple_Construction(){
     
     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] = "$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] = "$(PROJECT_OBJECTS_LOCATION)";

     char Library_Location [] = "$(PROJECT_LIBRARY_LOCATION)";

     char Source_Location  [] = "$(SOURCE_LOCATION)";


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     std::string go_to_new_line = "\\\n\t";



     std::string object_file_name = this->Simple_Data_Ptr->object_file_name;

     std::string dependency_file_name = this->Simple_Data_Ptr->source_file_name_without_ext + "_depends.d " ;

     std::string make_target_name = this->Exe_Name + ": dep_list ";

     make_target_name += go_to_new_line;

     make_target_name += dependency_file_name;

     this->Compiler_System_Command = make_target_name;



     this->Compiler_System_Command += go_to_new_line;


     this->Compiler_System_Command += object_file_name;

     this->Compiler_System_Command += " ";

     this->Compiler_System_Command += go_to_new_line;



     const std::vector<Library_Data> & data_list = this->Des_Reader->Get_Library_File_Data_List();

     for(size_t i=0;i<data_list.size();i++){

         this->Compiler_System_Command += data_list.at(i).library_name_with_ext;

         this->Compiler_System_Command += " ";

         this->Compiler_System_Command += go_to_new_line;
     }
     
     this->Compiler_System_Command += this->project_library_name;

     this->Compiler_System_Command += "\n\n\t";



     
     std::string compiler_input_command = "g++ -Wall -std=c++17 -o ";
     


     this->Place_String(&this->Compiler_System_Command,compiler_input_command);

     this->Compiler_System_Command += this->Exe_Name;

     this->Compiler_System_Command += " ";

     this->Place_String(&this->Compiler_System_Command,go_to_new_line);

     this->Compiler_System_Command += this->compiler_options_list_for_compiler_command;


     this->Compiler_System_Command += go_to_new_line;

     this->Compiler_System_Command += this->include_directory_list_for_compiler_command;


     this->Place_Information(&this->Compiler_System_Command,Include_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     // THE ADDITION OF EXTERNAL INCLUDE DIRECTORIES PATHS

     this->Compiler_System_Command += this->external_include_directory_list_for_compiler_command;

     this->Compiler_System_Command += this->library_directory_list_for_compiler_command;



     // THE ADDITION OF PROJECT LIBRARY LOCATION TO THE DIRECTORY PATHS

     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Library_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);


     // THE ADDITION OF THE TARGET SOURCE FILE LOCATION TO THE DIRECTORY PATHS

     this->Place_Information(&this->Compiler_System_Command,Link_Character);

     this->Place_Information(&this->Compiler_System_Command,Source_Location);

     this->Place_Information(&this->Compiler_System_Command,Space_Character);

     this->Place_Information(&this->Compiler_System_Command,slash);

     this->Place_Information(&this->Compiler_System_Command,new_line);

     this->Place_Information(&this->Compiler_System_Command,tab);





     this->Compiler_System_Command += object_file_name;

     this->Compiler_System_Command += " ";

     this->Compiler_System_Command += go_to_new_line;


     this->Compiler_System_Command += this->linker_options_list_for_compiler_command;

     this->Compiler_System_Command += go_to_new_line;

     this->Compiler_System_Command += this->include_file_list_for_compiler_command;

     this->Compiler_System_Command += go_to_new_line;

     this->Compiler_System_Command += "$(PROJECT_LIBRARY_LOCATION)\\";

     this->Compiler_System_Command += this->project_library_name;

     this->Compiler_System_Command += " ";

     this->Compiler_System_Command += go_to_new_line;

     this->Compiler_System_Command += this->library_path_list_for_compiler_command;

     this->Compiler_System_Command.shrink_to_fit();
}



void Executable_MakeFile_ComConstructor::Determine_Dependency_Determination_Command_For_Simple_Construction(){

     this->Clear_String_Memory(&this->Dependency_Determination_Command);


     char Include_Character [] = "-I";

     char Link_Character [] = "-L";

     char include_word [] = "-include";

     char Space_Character [] = {' ','\0'};

     char Headers_Location [] = "$(PROJECT_HEADERS_LOCATION)";

     char Objects_Location [] = "$(PROJECT_OBJECTS_LOCATION)";

     char Library_Location [] = "$(PROJECT_LIBRARY_LOCATION)";

     char Source_Location  [] = "$(SOURCE_LOCATION)";


     char slash [] = "\\";

     char new_line [] = "\n";

     char tab [] = "\t";

     int index_counter = 0;

     
     std::string compiler_input_command = "g++ -Wall -std=c++17 ";

     std::string file_name_ = this->Simple_Data_Ptr->source_file_name_without_ext + "_depends.d " ;

     compiler_input_command += "-c -MD -MF ";
     
     compiler_input_command += file_name_;




     this->Place_Information(&this->Dependency_Determination_Command,compiler_input_command);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);



     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     this->Dependency_Determination_Command += this->compiler_options_list_for_compiler_command;

     this->Dependency_Determination_Command += this->linker_options_list_for_compiler_command;


     // THE ADDITION OF INCLUDE DIRECTORIES PATHS

     this->Dependency_Determination_Command += this->include_directory_list_for_compiler_command;


     this->Place_Information(&this->Dependency_Determination_Command,Include_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     // THE ADDITION OF EXTERNAL INCLUDE DIRECTORIES PATHS

     this->Dependency_Determination_Command += this->external_include_directory_list_for_compiler_command;

  

     // THE ADDITION OF PROJECT LIBRARY LOCATION TO THE DIRECTORY PATHS

     this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Library_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     // THE ADDITION OF THE TARGET SOURCE FILE LOCATION TO THE DIRECTORY PATHS

     this->Place_Information(&this->Dependency_Determination_Command,Link_Character);

     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,new_line);

     this->Place_Information(&this->Dependency_Determination_Command,tab);


     // THE ADDITION OF THE LIST OF LIBRARY DIRECTORIES TO THE DIRECTORY PATHS

     this->Dependency_Determination_Command += this->library_directory_list_for_compiler_command;


     std::string go_to_new_line = "\\\n\t";



     // THE ADDITION OF THE SOURCE FILE TO THE COMPILER COMMAND

     this->Place_Information(&this->Dependency_Determination_Command,Source_Location);

     this->Place_Information(&this->Dependency_Determination_Command,slash);

     this->Place_Information(&this->Dependency_Determination_Command,this->source_file_name);

     this->Place_Information(&this->Dependency_Determination_Command,Space_Character);

     this->Place_Information(&this->Dependency_Determination_Command,go_to_new_line);


     this->Dependency_Determination_Command += this->include_file_list_for_compiler_command;

     this->Dependency_Determination_Command += go_to_new_line;

     this->Dependency_Determination_Command.shrink_to_fit();
}




bool Executable_MakeFile_ComConstructor::Check_Include_Directory_Existance(std::vector<std::string> * hdr_dir_list, 

     std::string dir){
     
     size_t dir_list_size = hdr_dir_list->size();

     bool is_exist = false;

     for(size_t j=0;j<dir_list_size;j++){

          std::string header_dir = hdr_dir_list->at(j);

          if(header_dir == dir){

             is_exist = true;

             break;
          }
     }

     return is_exist;

}


void Executable_MakeFile_ComConstructor::Construct_Header_File_List_For_Simple_Construction(){

     size_t list_size = this->Simple_Data_Ptr->Dependent_Header_Names.size();

     for(int i=0;i<list_size;i++){

         std::string header_name = this->Simple_Data_Ptr->Dependent_Header_Names.at(i);

         std::string header_dir  = this->Simple_Data_Ptr->Dependent_Header_Directories.at(i);

         std::string header_path = this->Simple_Data_Ptr->Dependent_Header_Paths.at(i);

         if(!header_name.empty()){
                  
            this->header_file_list.push_back(header_name);
            
            this->header_file_dirs.push_back(header_dir);

            this->header_file_paths.push_back(header_path);
         }
     }
}


void Executable_MakeFile_ComConstructor::Add_String(std::string * list, std::string string){

     size_t string_size = string.length();

     for(size_t i=0;i<string_size;i++){

         list->push_back(string[i]);
      }
}




void Executable_MakeFile_ComConstructor::Place_String(std::string * str_pointer,std::string str){

     size_t string_size = str.length();

     for(size_t i=0;i<string_size;i++){

         str_pointer->push_back(str[i]) ;
     }
}



void Executable_MakeFile_ComConstructor::Place_Information(std::string * Pointer,

     char * Information){

     int String_Size = strlen(Information);

     for(int i=0;i<String_Size;i++){

         Pointer->push_back(Information[i]);
     }
 }
 



void Executable_MakeFile_ComConstructor::Place_Information(std::string * Pointer,

      std::string Information){

      int String_Size = Information.length();

      for(int i=0;i<String_Size;i++){

          Pointer->push_back(Information[i]);
     }
}



void Executable_MakeFile_ComConstructor::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
    }
}




void Executable_MakeFile_ComConstructor::Clear_Vector_Memory(std::vector<std::string> * pointer)
{

     if(!pointer->empty()){

        std::vector<std::string>::iterator it;

        auto begin = pointer->begin();

        auto end   = pointer->end();

        for(auto it=begin;it<end;it++){

            if(!it->empty()){

                it->clear();

                it->shrink_to_fit();
            }
         }

         pointer->clear();

         pointer->shrink_to_fit();
      }
}



std::vector<std::string> * Executable_MakeFile_ComConstructor::Get_Object_File_List()
{
       return &this->object_file_list;
}



std::vector<std::string> * Executable_MakeFile_ComConstructor::Get_Header_File_List()
{
       return &this->header_file_list;
}


std::string Executable_MakeFile_ComConstructor::Get_Src_File_Dr(){

      return this->src_file_dir;
}



std::string Executable_MakeFile_ComConstructor::Get_Git_Src_Dr(){

      return this->git_src_dir;
}



std::string Executable_MakeFile_ComConstructor::Get_Make_File_Name(){

      return this->make_file_name;
}



std::string Executable_MakeFile_ComConstructor::Get_Compiler_System_Command(){

       return this->Compiler_System_Command;
}


std::string Executable_MakeFile_ComConstructor::Get_Dependency_Determination_Command(){

     return this->Dependency_Determination_Command;
}

std::string Executable_MakeFile_ComConstructor::Get_Project_Library_Name(){

    return this->project_library_name;
}