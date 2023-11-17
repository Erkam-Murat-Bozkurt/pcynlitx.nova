


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

#include "MakeFile_Path_Determiner.hpp"

MakeFile_Path_Determiner::MakeFile_Path_Determiner()
{
   this->Memory_Delete_Condition = false;
}


MakeFile_Path_Determiner::~MakeFile_Path_Determiner(){

    this->Clear_Object_Memory();
}


void MakeFile_Path_Determiner::Clear_Object_Memory(){

     this->Clear_Dynamic_Memory();
}



void MakeFile_Path_Determiner::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Data_Collector.Clear_Dynamic_Memory();

         this->Clear_String_Vector(this->upper_dir_vpaths_alias);

         this->Clear_String_Vector(this->upper_directory_vpaths);

         this->Clear_String_Vector(this->headers_vpath_alias);

         this->Clear_String_Vector(this->headers_vpaths);

         this->Clear_String_Vector(this->new_upper_directories);

         this->Clear_String_Memory(this->source_file_git_record_dir);

         this->Clear_String_Memory(this->make_file_path);

         this->Clear_String_Memory(this->make_file_name);
     }
}


void MakeFile_Path_Determiner::Receive_Operating_System(char opr_sis){

     this->opr_sis = opr_sis;

     this->Data_Collector.Receive_Operating_System(opr_sis);
}


void MakeFile_Path_Determiner::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;

     this->Data_Collector.Receive_Descriptor_File_Reader(ptr);
}

void MakeFile_Path_Determiner::Receive_Compiler_Data_Pointer(std::vector<Compiler_Data> * ptr)
{
     this->Comp_Data_Ptr = ptr;
}


void MakeFile_Path_Determiner::Receive_DataMap(std::unordered_map<std::string, Compiler_Data> * ptr){

     this->DataMap_Pointer = ptr;
}




void MakeFile_Path_Determiner::Determine_MakeFile_Data(std::string file_path){

     this->Clear_Dynamic_Memory();

     this->Memory_Delete_Condition = false;

     this->Data_Ptr = this->Find_Compiler_Data_From_Source_File_Path(file_path);

     this->Determine_Make_File_Name();

     this->Clear_String_Memory(this->make_file_path);

     this->Determine_MakeFile_Path(this->make_file_path,this->make_file_name);

     std::string sys_path = this->Data_Ptr->source_file_path;

     this->Clear_String_Memory(this->source_file_git_record_dir);

     this->Determine_Git_Record_Directory(this->source_file_git_record_dir,sys_path);

     this->Research_For_More_Upper_Directory();
     
     this->Determine_Dependent_Headers_Vpath_Alias();

     this->Determine_Upper_VPATH_Directories();

     this->Determine_Header_Vpaths();


     std::string Source_File_Name = this->Data_Ptr->source_file_name;

     this->Data_Collector.Receive_Compiler_Data_Pointer(this->Data_Ptr);

     this->Data_Collector.Receive_Determined_Upper_Directories(this->Get_Determined_Upper_Directories());

     this->Data_Collector.Collect_Make_File_Data(Source_File_Name);
}


Compiler_Data * MakeFile_Path_Determiner::Find_Compiler_Data_From_Source_File_Path(std::string path)
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


void MakeFile_Path_Determiner::Determine_Make_File_Name(){

     std::string make_file_extention = ".make";

     std::string Source_File_Name = this->Data_Ptr->source_file_name_witout_ext;

     size_t src_name_size = Source_File_Name.length();

     size_t extention_size = make_file_extention.length();

     for(size_t i=0;i<src_name_size;i++){

         this->make_file_name.push_back(Source_File_Name[i]);         
     }

     for(size_t i=0;i<extention_size;i++){

         this->make_file_name.push_back(make_file_extention[i]);         
     }

     this->make_file_name.shrink_to_fit();
}



void MakeFile_Path_Determiner::Determine_Header_Vpaths(){
     
     std::vector<std::string> * header_directories = &this->Data_Ptr->dependent_headers_dir;

     std::vector<std::string> * header_names = &this->Data_Ptr->dependent_headers;

     std::vector<std::string> paths;

     size_t hdr_dir_size = header_directories->size();

     for(size_t i=0;i<hdr_dir_size;i++){

          std::string dir  = header_directories->at(i);

          std::string hdr_name = header_names->at(i);
          
          std::string vpath;

          this->VPATH_Determiner(vpath,hdr_name,dir);

          bool is_exist = this->Check_String_Existance(paths,vpath);

          if(!is_exist){

              this->headers_vpaths.push_back(vpath);

              paths.push_back(vpath);
          }
     }

     this->headers_vpaths.shrink_to_fit();

     this->Clear_String_Vector(paths);
}



void MakeFile_Path_Determiner::Determine_Dependent_Headers_Vpath_Alias(){

     size_t dep_header_size = this->Data_Ptr->dependent_headers.size();

     std::vector<std::string> path_alias_list;

     for(size_t i=0;i<dep_header_size;i++){

          std::string header_name = this->Data_Ptr->dependent_headers.at(i);

          std::string path_alias;

          this->VPATH_Alias_Determiner(path_alias,header_name);

          bool is_exist = this->Check_String_Existance(path_alias_list,path_alias);

          if(!is_exist){
            
             this->headers_vpath_alias.push_back(path_alias);

             path_alias_list.push_back(path_alias);
          }
     }

     this->headers_vpath_alias.shrink_to_fit();

     this->Clear_String_Vector(path_alias_list);
}



void MakeFile_Path_Determiner::VPATH_Determiner(std::string & path, std::string hdr_name, std::string dir){

     std::string vpath_ext = "_Path=";

     for(size_t i=0;i<hdr_name.length();i++){

        path.push_back(hdr_name[i]);
     }

     for(size_t i=0;i<vpath_ext.length();i++){
  
         path.push_back(vpath_ext[i]);
     }

     for(size_t i=0;i<dir.length();i++){
  
         path.push_back(dir[i]);
     }

    path.shrink_to_fit();
}




void MakeFile_Path_Determiner::VPATH_Alias_Determiner(std::string & path_alias, std::string hdr_name){

     std::string Ident = "        ";

     std::string NextLine = " \\\n";

     std::string open_parantes = "$(";

     std::string path_subfix = "_Path";
     
     for(size_t i=0;i<open_parantes.length();i++){

         path_alias.push_back(open_parantes[i]);
     }

     for(size_t i=0;i<hdr_name.length();i++){

         path_alias.push_back(hdr_name[i]);
     }
  
     for(size_t i=0;i<path_subfix.length();i++){

         path_alias.push_back(path_subfix[i]);
     }
  
     path_alias.push_back(')');


     for(size_t i=0;i<NextLine.length();i++){

         path_alias.push_back(NextLine[i]);
     }
  
     for(size_t i=0;i<Ident.length();i++){

         path_alias.push_back(Ident[i]);
     }

     path_alias.shrink_to_fit();
}



bool MakeFile_Path_Determiner::Check_String_Existance(std::vector<std::string> & list, std::string str){

     size_t list_size = list.size();

     bool is_exist = false;

     for(size_t j=0;j<list_size;j++){

         if(list.at(j) == str){

            is_exist = true;

            return is_exist;
          }
     }

     return is_exist;
}





void MakeFile_Path_Determiner::Determine_Upper_VPATH_Directories(){

     size_t dir_num = this->Data_Ptr->upper_directories.size();

     std::vector<std::string> dir_list;

     int index=0;

     for(size_t i=0;i<dir_num;i++){

         std::string dir = this->Data_Ptr->upper_directories.at(i);
      
         bool is_exist = this->Check_String_Existance(dir_list,dir);

         if(!is_exist){

            std::string upper_dir_vpath, updir_vpath_alias;

            this->Upper_Directory_VPATH_Determiner(upper_dir_vpath,dir,index);

            this->Upper_Directory_VPATH_Alias_Determiner(updir_vpath_alias,index);

            index++;

            this->upper_directory_vpaths.push_back(upper_dir_vpath);

            this->upper_dir_vpaths_alias.push_back(updir_vpath_alias);

            this->new_upper_directories.push_back(dir);

            dir_list.push_back(dir);
         }
     }

     this->upper_directory_vpaths.shrink_to_fit();

     this->upper_dir_vpaths_alias.shrink_to_fit();

     this->new_upper_directories.shrink_to_fit();

     this->Clear_String_Vector(dir_list);
}




void MakeFile_Path_Determiner::Upper_Directory_VPATH_Determiner(std::string & upper_dir_vpath, 

     std::string dir, int index){

     std::string vpath_ext = "_Path=";

     std::string upper_dir_key = "UP_DR_";

     for(size_t i=0;i<upper_dir_key.length();i++){

         upper_dir_vpath.push_back(upper_dir_key[i]);
     }

     std::string str_int = std::to_string(index);

     for(size_t i=0;i<str_int.length();i++){

         upper_dir_vpath.push_back(str_int[i]);
     }

     for(size_t i=0;i<vpath_ext.length();i++){

         upper_dir_vpath.push_back(vpath_ext[i]);
     }

     for(size_t i=0;i<dir.length();i++){

         upper_dir_vpath.push_back(dir[i]);
     }
}



void MakeFile_Path_Determiner::Upper_Directory_VPATH_Alias_Determiner(std::string & alias, int index){
     
     std::string Ident = "        ";

     std::string NextLine = " \\\n";

     std::string alias_start = "$(UP_DR_";

     std::string alias_end   = "_Path)";
     
     for(size_t i=0;i<alias_start.length();i++){

         alias.push_back(alias_start.at(i));
     }

     std::string str_int = std::to_string(index);

     for(size_t i=0;i<str_int.length();i++){

         alias.push_back(str_int[i]);
     }

     for(size_t i=0;i<alias_end.length();i++){

         alias.push_back(alias_end.at(i));
     }

     for(size_t i=0;i<NextLine.length();i++){

         alias.push_back(NextLine[i]);
     }

     for(size_t i=0;i<Ident.length();i++){

         alias.push_back(Ident[i]);
     }

     alias.shrink_to_fit();
}



void MakeFile_Path_Determiner::Determine_MakeFile_Path(std::string & make_file_path, 

     std::string make_file_name){

     std::string git_record_dir = this->Data_Ptr->src_git_record_dir;

     std::string warehouse_location = this->Des_Reader->Get_Warehouse_Location();

     std::string warehouse_word = "WAREHOUSE";
     
     std::string make_file_dir_name = "MAKE.FILES";


     size_t warehouse_dir_size  = warehouse_location.length();

     for(size_t i=0;i<warehouse_dir_size;i++){

         make_file_path.push_back(warehouse_location[i]);
     }

     if(this->opr_sis == 'w'){

        if(make_file_path.back()!= '\\'){

           make_file_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(make_file_path.back()!= '/'){

           make_file_path.push_back('/');
        }
     }


     size_t warehouse_word_size = warehouse_word.length();

     for(size_t i=0;i<warehouse_word_size;i++){

         make_file_path.push_back(warehouse_word[i]);
     }

     if(this->opr_sis == 'w'){

        if(make_file_path.back()!= '\\'){

           make_file_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(make_file_path.back()!= '/'){

           make_file_path.push_back('/');
        }
     }

     
     size_t make_dir_size = make_file_dir_name.length();

     for(size_t i=0;i<make_dir_size;i++){

         make_file_path.push_back(make_file_dir_name[i]);
     }

     if(this->opr_sis == 'w'){

        if(make_file_path.back()!= '\\'){

           make_file_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(make_file_path.back()!= '/'){

           make_file_path.push_back('/');
        }
     }


     size_t git_dir_size = git_record_dir.length();

     for(size_t i=0;i<git_dir_size;i++){

         make_file_path.push_back(git_record_dir[i]);
     }

     if(this->opr_sis == 'w'){

        if(make_file_path.back()!= '\\'){

           make_file_path.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(make_file_path.back()!= '/'){

           make_file_path.push_back('/');
        }
     }


     size_t name_size = make_file_name.length();

     for(size_t i=0;i<name_size;i++){

         make_file_path.push_back(make_file_name[i]);
     }

     make_file_path.shrink_to_fit();
}



void MakeFile_Path_Determiner::Research_For_More_Upper_Directory(){
    
    size_t root_dir_size = this->Get_Repo_Dir().size();
 
    for(size_t i=0;i<this->Data_Ptr->upper_directories.size();i++){

        std::string dir = this->Data_Ptr->upper_directories.at(i);
         
        size_t up_dir_size = 0;

        do{

            std::string upper_directory = 
             
            this->Search_For_New_Upper_Directory(this->Data_Ptr->upper_directories,dir);

            this->Clear_String_Memory(dir);

            dir = upper_directory;

            up_dir_size = upper_directory.length();

        }while(up_dir_size>root_dir_size);
    }
}



void MakeFile_Path_Determiner::Determine_Git_Record_Directory(std::string & git_dir, std::string sys_path){

     std::string root_dir = this->Des_Reader->Get_Repo_Directory_Location();

     size_t path_size = sys_path.length();

     size_t end_point = path_size;

     size_t start_point = root_dir.length()+1;

     for(size_t i=path_size;i>0;i--){

         if(this->opr_sis == 'w'){

            if(sys_path[i]== '\\'){

               break;
          
            }
            else{

                  end_point--;
            }
         }


         if(this->opr_sis == 'l'){

            if(sys_path[i]== '/'){

               break;
            }
            else{

                  end_point--;
            }
         }
     }

     git_dir.clear();


     for(size_t i=start_point;i<end_point;i++){

         git_dir.push_back(sys_path[i]);
     }

     git_dir.shrink_to_fit();
}




std::string MakeFile_Path_Determiner::Search_For_New_Upper_Directory(std::vector<std::string> & dir_list,

     std::string dir){
     
     std::string upper_directory;

     this->Find_Upper_Directory(upper_directory,dir);
        
     bool is_exist = this->Check_String_Existance(dir_list,upper_directory);

     if(!is_exist){

         size_t root_dir_size = this->Get_Repo_Dir().size();

         size_t next_dir_size = upper_directory.size();

         if(next_dir_size > root_dir_size){

            dir_list.push_back(upper_directory);
         }

         dir_list.shrink_to_fit();
      }

      return upper_directory;
}



void MakeFile_Path_Determiner::Find_Upper_Directory(std::string & upper_dir, std::string dir){

     size_t dir_size = dir.length();

     size_t end_point = 0;

     for(size_t i=dir_size;i>0;i--){

         if((dir[i]=='\\') || (dir[i]=='/')){

             end_point = i;

             break;
         }
     }

     for(size_t i=0;i<end_point;i++){

         upper_dir.push_back(dir[i]);
     }

     upper_dir.shrink_to_fit();
}


void MakeFile_Path_Determiner::Clear_String_Vector(std::vector<std::string> & str){

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




void MakeFile_Path_Determiner::Clear_String_Memory(std::string & str)
{
     if(!str.empty()){

         str.clear();

         str.shrink_to_fit();
     }
}




std::string MakeFile_Path_Determiner::Get_Warehouse_Object_Dir(){

     return this->Data_Collector.Get_Warehouse_Object_Dir();
}


std::string MakeFile_Path_Determiner::Get_Repo_Dir(){

     return this->Data_Collector.Get_Repo_Dir();
}


std::string MakeFile_Path_Determiner::Get_Compiler_System_Command(){

     return this->Data_Collector.Get_Compiler_System_Command();
}


std::string MakeFile_Path_Determiner::Get_Dependency_Code_Line(){

     return this->Data_Collector.Get_Dependency_Code_Line();
}


std::vector<std::string> * MakeFile_Path_Determiner::Get_Header_Vpaths(){

    return &this->headers_vpaths;
}


std::vector<std::string> * MakeFile_Path_Determiner::Get_Header_Vpath_Alias(){

    return &this->headers_vpath_alias;
}



std::vector<std::string> * MakeFile_Path_Determiner::Get_Upper_Directory_Vpaths(){

    return &this->upper_directory_vpaths;
}


std::vector<std::string> * MakeFile_Path_Determiner::Get_Upper_Directory_Vpaths_Alias(){

    return &this->upper_dir_vpaths_alias;
}


std::vector<std::string> * MakeFile_Path_Determiner::Get_Determined_Upper_Directories(){

    return &this->new_upper_directories;
}


std::string MakeFile_Path_Determiner::Get_MakeFile_Path(){

     return this->make_file_path;
}


std::string MakeFile_Path_Determiner::Get_Source_File_Git_Record_Dir(){

     return this->source_file_git_record_dir;
}
