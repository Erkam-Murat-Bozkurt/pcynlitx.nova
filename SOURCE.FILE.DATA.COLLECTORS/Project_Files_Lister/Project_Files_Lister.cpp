
#include "Project_Files_Lister.h"

Project_Files_Lister::Project_Files_Lister(char * DesPATH, char opr_sis) :

   Git_Data_Receiver(DesPATH,opr_sis), Src_Data_Col(DesPATH,opr_sis),

   Header_Determiner(DesPATH,opr_sis)
{
    this->Git_Data_Receiver.Determine_Git_Repo_Info();

    this->Initialize_Members(opr_sis);
}


Project_Files_Lister::~Project_Files_Lister(){

   if(!this->Memory_Delete_Condition)
   {
       this->Clear_Dynamic_Memory();
   }
}

void Project_Files_Lister::Initialize_Members(char opr_sis){

     this->operating_sis = opr_sis;

     this->Source_File_Number = 0;

     this->Memory_Delete_Condition = false;

     this->independent_header_files_number = 0;

     this->git_record_size = this->Git_Data_Receiver.Get_Git_File_Index_Size();

     this->Repo_Dir        = this->Git_Data_Receiver.Get_Git_Repo_Directory();

     for(int i=0;i<this->git_record_size-1;i++){

         std::string path = this->Git_Data_Receiver.Get_File_System_Path(i);

         this->git_record_paths.push_back(path);
     }

     this->Git_Data_Receiver.Clear_Dynamic_Memory();
}


void Project_Files_Lister::Determine_Git_Repo_Info()
{
     this->Collect_Source_Files_Data();

     this->Collect_Independent_Header_Files_Data();
}

void Project_Files_Lister::Collect_Source_Files_Data()
{
     this->Memory_Delete_Condition = false;

     for(int i=0;i<this->git_record_size-1;i++)
     {
         std::string file_path = this->git_record_paths[i];

         bool is_source_file   = this->Source_Determiner.Is_Source_File(file_path);

         if(is_source_file){

            bool is_main_file = this->Source_Determiner.Is_Main_File(file_path);

            if(!is_main_file){

                this->Source_File_Number++;

                Build_System_Data Temp_Data;

                this->Src_Data_Col.Process_Source_File_Data(&Temp_Data,file_path);

                this->Data.push_back(Temp_Data);

                this->Clear_Build_Data(&Temp_Data);
            }
         }
     }

     this->Data.shrink_to_fit();     
}


void Project_Files_Lister::Collect_Independent_Header_Files_Data()
{
     this->independent_header_files_number = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         std::string file_path = this->git_record_paths[i];

         bool is_header_file = this->Header_Determiner.Is_Header(file_path);

         if(is_header_file){

            std::string file_name;

            this->Determine_File_Name_With_Ext(&file_name,file_path);

            bool src_file_ext = this->Is_There_a_Source_File_With_Same_Name(file_name);

            if(!src_file_ext){
            
                this->independent_header_files.push_back(file_path);

                this->independent_header_files_number++;                                    
            }
         }
      }
}


bool Project_Files_Lister::Check_String_Equality(std::string s1, std::string s2){

     return this->StringManager.CompareString(s1,s2);
}


bool Project_Files_Lister::CheckStringInclusion(std::string str, std::string word){

     return this->StringManager.CheckStringInclusion(str,word);
}


bool Project_Files_Lister::Is_This_Header_File_Included_Anywhere(std::string file_name)
{
     this->is_this_file_included_anywhere = false;

     for(int k=0;k<this->Get_Source_File_Number();k++){

         int inc_file_num = this->Get_Source_File_Include_File_Number(k);

         for(int j=0;j<inc_file_num;j++)
         {
             std::string included_file_name = this->Get_Source_File_Header(k,j);

             this->is_this_file_included_anywhere

             = this->CheckStringInclusion(file_name,included_file_name);

             if(this->is_this_file_included_anywhere){

                return this->is_this_file_included_anywhere;
             }
          }
      }

      return this->is_this_file_included_anywhere;
}


bool Project_Files_Lister::Is_There_a_Source_File_With_Same_Name(std::string file_Name){

     std::string fileName;

     this->Determine_File_Name_Without_Ext(&fileName,file_Name);


     this->Source_File_With_Same_Name = false;          

     for(int i=0;i<this->Get_Source_File_Number();i++){
     
         std::string src_path = this->Get_Source_File_Name(i);

        if(this->Check_String_Equality(fileName,src_path)){
                
           this->Source_File_With_Same_Name = true; 

           break;                 
        }
     }

     return this->Source_File_With_Same_Name;          
}


void Project_Files_Lister::Determine_File_Name_With_Ext(std::string * pointer,

     std::string string_line){

     size_t string_size = string_line.length();

     size_t dir_size = string_size;

     size_t file_extention_start_point = string_size;

     for(size_t i=string_size;i>0;i--){

         if((string_line[i] == '\\') || (string_line[i] == '/'))
         {
            break;
         }
         else{

              dir_size--;
         }
     }

     for(size_t i=dir_size+1;i<string_size;i++){

          pointer->push_back(string_line[i]);
     }
}


void Project_Files_Lister::Determine_File_Name_Without_Ext(std::string * pointer, 

     std::string path){


     /*   
      
        This function extracts the file name from given string.

        If the string is a path, it extracts the string from the last

        directory character to the point character. If the string is not a path, 

        it extracts the string from the beginning of the string to the point 

        chacter.
      
    */


     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;

     
     bool is_path = false;

     for(size_t i=file_path_size;i>0;i--){

        if(((path[i] == '/') || (path[i] == '\\'))){

            is_path = true;

            break;
        }
     }

     if(is_path){
     
        for(size_t i=file_path_size;i>0;i--){

             if(((path[i] == '/') || (path[i] == '\\'))){

                  break;
             }
             else{

                    dir_size--;
             }
        }

        for(size_t i=dir_size+1;i<file_path_size;i++){

            if( path[i] == '.'){

               break;
            }

            pointer->push_back(path[i]);          
        }
     }
     else{
     
     
            for(size_t i=0;i<file_path_size;i++){

               if( path[i] == '.'){

                  break;
               }

               pointer->push_back(path[i]);          
            }
     }
         
}

void Project_Files_Lister::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition)
     {
         this->Memory_Delete_Condition = true;

         this->Clear_Vector_Memory(&this->independent_header_files);

         this->Clear_Build_Data_Memory(&this->Data);

         this->Clear_Vector_Memory(&this->git_record_paths);

         this->Git_Data_Receiver.Clear_Dynamic_Memory();

         this->Src_Data_Col.Clear_Dynamic_Memory();

         this->Header_Determiner.Clear_Dynamic_Memory();

         this->StringManager.Clear_Dynamic_Memory();
      }
}


void Project_Files_Lister::Clear_Vector_Memory(std::vector<std::string> * pointer)
{
     std::vector<std::string>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        if(!it->empty()){

            it->clear();
            it->shrink_to_fit();
        }
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void Project_Files_Lister::Clear_Build_Data_Memory(std::vector<Build_System_Data> * pointer)
{
     std::vector<Build_System_Data>::iterator it;

     auto begin = pointer->begin();
     auto end   = pointer->end();

     for(auto it=begin;it<end;it++){

        this->Clear_Build_Data(&(*it));
     }

     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}


void Project_Files_Lister::Clear_String_Memory(std::string * pointer)
{
     if(!pointer->empty())
     {
         pointer->clear();
         pointer->shrink_to_fit();
     }
}

void Project_Files_Lister::Clear_Build_Data(Build_System_Data * pointer){

     this->Clear_Vector_Memory(&pointer->Included_Header_Files);
     this->Clear_Vector_Memory(&pointer->Included_Header_Files_Directories);
     this->Clear_Vector_Memory(&pointer->Included_Header_Files_System_Path);
     this->Clear_Vector_Memory(&pointer->Included_Header_Files_Git_Record_Path);
     this->Clear_Vector_Memory(&pointer->Included_Header_Files_Git_Record_Dir);

     this->Clear_String_Memory(&pointer->git_record_path);
     this->Clear_String_Memory(&pointer->git_record_dir);
     this->Clear_String_Memory(&pointer->File_Directory);
     this->Clear_String_Memory(&pointer->File_Path);
     this->Clear_String_Memory(&pointer->File_Name);
     this->Clear_String_Memory(&pointer->File_Name_With_Ext);
     this->Clear_String_Memory(&pointer->class_header_file_name);
     this->Clear_String_Memory(&pointer->class_header_file_path);
}


std::vector<Build_System_Data> * Project_Files_Lister::Get_Build_System_Data_Address(){

     return &this->Data;
}


int Project_Files_Lister::Get_Source_File_Number(){

    return this->Source_File_Number;
}

std::string Project_Files_Lister::Get_Source_File_Directory(int num){

    return this->Data.at(num).File_Directory;
}

std::string Project_Files_Lister::Get_Source_File_Git_Record_Path(int num){

    return this->Data.at(num).git_record_path;
}

std::string Project_Files_Lister::Get_Source_File_System_Path(int num){

    return this->Data.at(num).File_Path;
}

std::string Project_Files_Lister::Get_Source_File_Name(int num){

    return this->Data.at(num).File_Name;
}

std::string Project_Files_Lister::Get_Source_File_Name_With_Ext(int num){

    return this->Data.at(num).File_Name_With_Ext;
}

int  Project_Files_Lister::Get_Source_File_Include_File_Number(int num){

     return this->Data.at(num).Included_Header_Files_Number;
}

int Project_Files_Lister::Get_Indenpendent_Header_Files_Number(){

    return this->independent_header_files_number;
}

std::string Project_Files_Lister::Get_Source_File_Header(int src_num, int hdr_num){

    return this->Data.at(src_num).Included_Header_Files[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_Directory(int src_num, int hdr_num){

    return this->Data.at(src_num).Included_Header_Files_Directories[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_System_Path(int src_num, int hdr_num){

    return this->Data.at(src_num).Included_Header_Files_System_Path[hdr_num];
}

std::string Project_Files_Lister::Get_Class_File_Header_System_Path(int src_num){

    return this->Data.at(src_num).class_header_file_path;
}

std::string Project_Files_Lister::Get_Class_File_Header_Name(int src_num){

    return this->Data.at(src_num).class_header_file_name;
}

std::string Project_Files_Lister::Get_Source_File_Header_Git_Record_Path(int src_num, int hdr_num){

    return this->Data.at(src_num).Included_Header_Files_Git_Record_Path[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_Git_Record_Dir(int src_num, int hdr_num){

    return this->Data.at(src_num).Included_Header_Files_Git_Record_Dir[hdr_num];
}

std::string Project_Files_Lister::Get_Independent_Header_File(int num){

    return this->independent_header_files[num];
}

std::string Project_Files_Lister::Get_Source_File_Git_Record_Directory(int src_num){

    return this->Data.at(src_num).git_record_dir;
}
