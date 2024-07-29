
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

#include "Make_File_Builder.h"

Make_File_Builder::Make_File_Builder()
{
   this->Memory_Delete_Condition = false;
}


Make_File_Builder::~Make_File_Builder(){

    this->Clear_Object_Memory();
}


void Make_File_Builder::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}

void Make_File_Builder::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;
     }
}


void Make_File_Builder::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;

     this->Path_Determiner.Receive_Operating_System(opr_sis);
}


void Make_File_Builder::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Path_Determiner.Receive_Descriptor_File_Reader(ptr);
}

void Make_File_Builder::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr)
{
     this->Comp_Data_Ptr = ptr;

     this->Path_Determiner.Receive_Compiler_Data_Pointer(ptr);
}


void Make_File_Builder::Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr){

     this->DataMap_Pointer = ptr;

     this->Path_Determiner.Receive_DataMap(ptr);
}


Compiler_Data * Make_File_Builder::Find_Compiler_Data_From_Source_File_Path(std::string path)
{
    try {        

         return  &this->DataMap_Pointer->at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n the file located on path " << path 
         
         << " can not find on Make_File_Builder object!.\n";

         exit(EXIT_FAILURE);
    }     
}


void Make_File_Builder::Build_MakeFile(std::string file_path){

     this->Memory_Delete_Condition = false;

     this->Path_Determiner.Determine_MakeFile_Data(file_path);

     this->Data_Ptr = this->Find_Compiler_Data_From_Source_File_Path(file_path);

     
     std::string Make_File_Path = this->Path_Determiner.Get_MakeFile_Path();


     this->FileManager.SetFilePath(Make_File_Path);

     this->FileManager.FileOpen(RWCf);     

     this->FileManager.WriteToFile("\n");


     this->FileManager.WriteToFile("PROJECT_OBJECTS_LOCATION=");


     std::string warehouse_obj_dir = this->Path_Determiner.Get_Warehouse_Object_Dir();

     this->FileManager.WriteToFile(warehouse_obj_dir);

     this->FileManager.WriteToFile("\n");
     
     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("REPO_DIR=");

     std::string project_repo_dir = this->Path_Determiner.Get_Repo_Dir();

     this->FileManager.WriteToFile(project_repo_dir);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("SOURCE_LOCATION=$(REPO_DIR)");



     std::string source_file_dir = this->Path_Determiner.Get_Source_File_Git_Record_Dir();
     

     if(!source_file_dir.empty()){

        this->FileManager.WriteToFile("\\");

        this->FileManager.WriteToFile(source_file_dir);
     }



     int included_dir_num = this->Des_Reader->Get_Include_Directory_Number();

     char include_symbol [] = "EXTERNAL_INCLUDE_DIR_";

     char underscore [] = "_";

     this->FileManager.WriteToFile("\n");

     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("\n");

         std::string included_dir = this->Des_Reader->Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(include_symbol);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile("=");

         this->FileManager.WriteToFile(included_dir);
     }

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");


     char Ident [] =         "        ";

     char NextLine [] = " \\";




     this->Write_Header_VPaths();

     this->Write_Upper_Directory_VPaths();


     char PathSpecifier [] = "VPATH = ";


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(PathSpecifier);


     this->FileManager.WriteToFile("$(PROJECT_OBJECTS_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);


     this->FileManager.WriteToFile("$(SOURCE_LOCATION)");

     this->FileManager.WriteToFile(NextLine);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile(Ident);



     this->Write_Header_VPaths_Alias();

     this->Write_Upper_Dir_VPaths_Alias();



     for(int i=0;i<included_dir_num;i++){

         this->FileManager.WriteToFile("$(");

         std::string included_dir = this->Des_Reader->Get_Include_Directory(i);

         char * dir_index = this->Translater.Translate(i);

         this->FileManager.WriteToFile(include_symbol);

         this->FileManager.WriteToFile(dir_index);

         this->FileManager.WriteToFile(")");

         this->FileManager.WriteToFile(NextLine);

         this->FileManager.WriteToFile("\n");

         this->FileManager.WriteToFile(Ident);
     }


     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n");
     
     this->FileManager.WriteToFile("\n");



     std::string Dependency_Code_Line    = this->Path_Determiner.Get_Dependency_Code_Line();

     std::string Compiler_System_Command = this->Path_Determiner.Get_Compiler_System_Command();

     this->FileManager.WriteToFile(Dependency_Code_Line);

     this->FileManager.WriteToFile("\n");

     this->FileManager.WriteToFile("\n\t");

     this->FileManager.WriteToFile(Compiler_System_Command);

     this->FileManager.WriteToFile("\n");

     this->FileManager.FileClose();
}




void Make_File_Builder::Write_Upper_Directory_VPaths(){

     std::vector<std::string> * upper_dir_vpaths = 

     this->Path_Determiner.Get_Upper_Directory_Vpaths();

     for(size_t i=0;i<upper_dir_vpaths->size();i++){

         this->FileManager.WriteToFile(upper_dir_vpaths->at(i));

         this->FileManager.WriteToFile("\n");   
     }

}


void Make_File_Builder::Write_Header_VPaths(){
    
     std::vector<std::string> * hdr_vpaths = 

     this->Path_Determiner.Get_Header_Vpaths();

     for(size_t i=0;i<hdr_vpaths->size();i++){

         this->FileManager.WriteToFile(hdr_vpaths->at(i));

         this->FileManager.WriteToFile("\n");   
     }
}



void Make_File_Builder::Write_Header_VPaths_Alias(){

     std::vector<std::string> * hdr_vpath_alias = 

     this->Path_Determiner.Get_Header_Vpath_Alias();

     for(size_t i=0;i<hdr_vpath_alias->size();i++){

         this->FileManager.WriteToFile(hdr_vpath_alias->at(i));
     }
}


 void Make_File_Builder::Write_Upper_Dir_VPaths_Alias(){

      std::vector<std::string> * up_dir_alias = 

      this->Path_Determiner.Get_Upper_Directory_Vpaths_Alias();

      for(size_t i=0;i<up_dir_alias->size();i++){

          this->FileManager.WriteToFile(up_dir_alias->at(i));
     }
 }




void Make_File_Builder::Clear_String_Vector(std::vector<std::string> & str){

     str.shrink_to_fit();

     for(size_t i=0;i<str.size();i++){

         this->Clear_String_Memory(str.at(i));
     }

     if(!str.empty())
     {
         str.clear();
         str.shrink_to_fit();
     }
 }




void Make_File_Builder::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}
