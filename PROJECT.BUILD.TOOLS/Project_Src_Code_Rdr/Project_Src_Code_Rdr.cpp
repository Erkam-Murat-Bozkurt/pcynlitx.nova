

#include "Project_Src_Code_Rdr.hpp"


Project_Src_Code_Rdr::Project_Src_Code_Rdr(char opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->opr_sis = opr_sis;

   this->Hdr_Determiner = new Header_File_Determiner * [16];

   this->Src_Determiner = new Source_File_Determiner * [16];

   for(int i=0;i<16;i++){
   
       this->Hdr_Determiner[i] = new Header_File_Determiner(opr_sis);

       this->Src_Determiner[i] = new Source_File_Determiner;
   }

   for(int i=0;i<16;i++){
   
       this->FileManager[i].Receive_Operating_System(opr_sis);

       this->StringManager[i].Receive_Operating_System(opr_sis);
   }
}



Project_Src_Code_Rdr::~Project_Src_Code_Rdr(){

    if(!this->Memory_Delete_Condition){
    
        this->Clear_Object_Memory();       
    }   
}




void Project_Src_Code_Rdr::Receive_Git_Data_Processor(Git_Data_Processor * ptr)
{
     this->Git_Data_Proc = ptr;

     for(int i=0;i<16;i++){
   
         this->Hdr_Determiner[i]->Receive_Git_Data_Processor(ptr);
     }

     this->root_directory = this->Git_Data_Proc->Get_Git_Repo_Directory();
}



void Project_Src_Code_Rdr::Receive_File_Paths(){
  
     size_t file_number = this->Git_Data_Proc->Get_Git_File_Index_Size();

     for(int i=0;i<file_number;i++){

         std::string file_sys_path = this->Git_Data_Proc->Get_File_System_Path(i);

         this->FilePaths.push_back(file_sys_path);
     }

     this->FilePaths.shrink_to_fit();
}



void Project_Src_Code_Rdr::Read_Project_Source_Code_Files(){

     this->Receive_File_Paths();

     size_t repo_size = this->FilePaths.size();      

     if(repo_size >= 16){
     
        int division = repo_size/16;
        
        for(int i=0;i<16;i++){

            int str  = i*division;

            int end  = (i+1)*division;

            if(i==15){

                end = repo_size;
            }

            this->threads[i] = std::thread(Project_Src_Code_Rdr::Read_Source_Code,this,i,str,end);     
        }
    
        for(int i=0;i<16;i++){
     
            this->threads[i].join();
        }

     }else{
     
           this->Read_Source_Code_Single_Thread();
     }

     this->Code_Dt.shrink_to_fit();


     for(size_t i=0;i<this->Code_Dt.size();i++){

         this->Map_Path.insert(std::make_pair(this->Code_Dt.at(i).sys_path, &this->Code_Dt.at(i)));
            
         this->Map_Name.insert(std::make_pair(this->Code_Dt.at(i).file_name,&this->Code_Dt.at(i)));

         this->Map_Cmbn.insert(std::make_pair(this->Code_Dt.at(i).cmbn_name,&this->Code_Dt.at(i)));
     }



     this->Clear_Thread_Objects_Memory();
}


void Project_Src_Code_Rdr::Read_Source_Code(int trn, int start_point, int end_point){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();

     

     for(int i=start_point;i<end_point;i++){
     
         std::string file_sys_path = this->FilePaths.at(i);

         bool is_header   = this->Hdr_Determiner[trn]->Is_Header(file_sys_path);

         bool is_src_file = this->Src_Determiner[trn]->Is_Source_File(file_sys_path);


         if(is_header || is_src_file){
                             
            std::string class_function_pattern;

            if(is_src_file){

               this->Determine_Class_Function_Pattern(file_sys_path,class_function_pattern);               
            }


            FileData buffer;  // DATA BUFFER DECLERATION

            buffer.sys_path = file_sys_path;

            buffer.is_header_file = false;
            buffer.is_main_file   = false;
            buffer.is_source_file = false;

            if(is_header){

               buffer.is_header_file = true;
               buffer.is_main_file   = false;
               buffer.is_source_file = false;
            }

            this->FileManager[trn].Read_File(file_sys_path);

            int FileSize = this->FileManager[trn].GetFileSize();

            for(int k=0;k<FileSize;k++){
         
                std::string string_line = this->FileManager[trn].GetFileLine(k);

                this->Delete_Spaces_on_String(&string_line);


                if(is_src_file){

                   std::string main_file_key   = "main(";

                   bool is_main_key_exist 
                   
                   = this->StringManager[trn].CheckStringInclusion(string_line,main_file_key);


                   if(is_main_key_exist){

                      buffer.is_main_file   = true;
                      buffer.is_header_file = false;
                      buffer.is_source_file = false;
                   }

                                
                   bool is_member_function_key_exist 
                   
                   = this->StringManager[trn].CheckStringInclusion(string_line,class_function_pattern);


                   // It is the member function scop resolution key word 
                   // For member function sample::function, it is "sample::"

                   if(is_member_function_key_exist){      

                      buffer.is_source_file = true;
                      buffer.is_header_file = false;
                      buffer.is_main_file   = false;
                   }
                }

                bool is_include_decleration = this->Include_Decleration_Test(string_line,trn);

                if(is_include_decleration){

                   std::string include_decleration = this->Extract_Include_Decleration(string_line);

                   buffer.include_declerations.push_back(include_decleration);
                }
            }


            this->FileManager[trn].Clear_Dynamic_Memory();
            
            this->StringManager[trn].Clear_Dynamic_Memory();

            this->Determine_File_Name(file_sys_path,buffer.file_name);

            this->Determine_File_Combined_Name(file_sys_path,buffer.cmbn_name);
                        

            if(is_src_file){

                if(!buffer.is_main_file){

                    if(!buffer.is_source_file){  // The source file is not a class but it is a source file

                        buffer.is_source_file = true;
                    }
                }
            }

            mt.lock();

            this->Code_Dt.push_back(buffer);
        
            mt.unlock();


            this->Clear_Buffer_Memory(buffer);
         }
     }

}



void Project_Src_Code_Rdr::Read_Source_Code_Single_Thread(){

     for(size_t i=0;i<this->FilePaths.size();i++){
     
         std::string file_sys_path = this->FilePaths.at(i);

         bool is_header   = this->Hdr_Determiner[0]->Is_Header(file_sys_path);

         bool is_src_file = this->Src_Determiner[0]->Is_Source_File(file_sys_path);

         if(is_header || is_src_file){
                             
            FileData buffer;

            buffer.sys_path = file_sys_path;


            std::string class_function_pattern;

            if(is_src_file){

               this->Determine_Class_Function_Pattern(file_sys_path,class_function_pattern);               
            }


            this->FileManager[0].Read_File(file_sys_path);

            int FileSize = this->FileManager[0].GetFileSize();

            for(int k=0;k<FileSize;k++){
         
                std::string string_line = this->FileManager[0].GetFileLine(k);

                this->Delete_Spaces_on_String(&string_line);

                this->Include_Decleration_Test(string_line,0);

                if(is_src_file){

                   std::string main_file_key   = "main(";

                   bool is_main_key_exist 
                   
                   = this->StringManager[0].CheckStringInclusion(string_line,main_file_key);


                   if(is_main_key_exist){

                      buffer.is_main_file   = true;
                      buffer.is_header_file = false;
                      buffer.is_source_file = false;
                   }

                                
                   bool is_member_function_key_exist 
                   
                   = this->StringManager[0].CheckStringInclusion(string_line,class_function_pattern);


                   // It is the member function scop resolution key word 
                   // For member function sample::function, it is "sample::"

                   if(is_member_function_key_exist){      

                      buffer.is_source_file = true;
                      buffer.is_header_file = false;
                      buffer.is_main_file   = false;
                   }
                }


                bool is_include_decleration = this->Include_Decleration_Test(string_line,0);

                if(is_include_decleration){

                    std::string include_decleration = this->Extract_Include_Decleration(string_line);

                    buffer.include_declerations.push_back(include_decleration);
                }                
            }
            

            this->Determine_File_Name(file_sys_path,buffer.file_name);

            this->Determine_File_Combined_Name(file_sys_path,buffer.cmbn_name);



            this->Code_Dt.push_back(buffer);

            this->Clear_Buffer_Memory(buffer);

         }
     }

     this->Clear_Thread_Objects_Memory();    
}



void Project_Src_Code_Rdr::Delete_Spaces_on_String(std::string * str){

    size_t string_size = str->length();

    bool search_cond = true;

    do{

      search_cond = false;

      for(size_t i=0;i<str->length();i++){

          if((*str)[i] == ' '){

            search_cond = true;

            str->erase(i,1);
          }
        }

    }while(search_cond);
}


void Project_Src_Code_Rdr::Determine_File_Name(std::string path, std::string & file_name){

     this->Clear_String_Memory(file_name);

     size_t file_path_size = path.length();

     size_t dir_size = file_path_size;


     for(size_t i=file_path_size;i>0;i--){

        if((path[i] == '/') || (path[i] == '\\')){

          break;
        }
        else{

            dir_size--;
        }
     }

     size_t file_name_size = file_path_size - dir_size;

     int index = 0;

     for(size_t i=dir_size+1;i<file_path_size;i++){

         file_name.push_back(path[i]);        
     }

     file_name.shrink_to_fit();
}

void Project_Src_Code_Rdr::Determine_File_Combined_Name(std::string path, std::string & file_name){

     this->Clear_String_Memory(file_name);

     size_t file_path_size = path.length();

     size_t upper_dir_size = file_path_size;

     size_t root_dir_size  = this->root_directory.length(); 

     
     int dir_counter = 0;

     for(size_t i=file_path_size;i>root_dir_size;i--){

        if((path[i] == '/') || (path[i] == '\\')){

           dir_counter++;

           if(dir_counter>1){

              break;
           }  
           else{

                 upper_dir_size--;
           }      
        }
        else{

            upper_dir_size--;
        }
     }

     size_t file_name_size = file_path_size - upper_dir_size;

     int index = 0;

     for(size_t i=upper_dir_size+1;i<file_path_size;i++){

         file_name.push_back(path[i]);
     }

     file_name.shrink_to_fit();
}


bool Project_Src_Code_Rdr::Include_Decleration_Test(std::string string, int thr_num)
{
     bool include_decleration_cond = false;

     char include_key_1 [] = "#include\"";  // double_quotation_mark
     char include_key_2 [] = "#include<";  // double_quotation_mark


     bool include_dec_cond_1 = false;

     bool include_dec_cond_2 = false;


     include_dec_cond_1 = this->StringManager[thr_num].CheckStringInclusion(string,include_key_1);

     include_dec_cond_2 = this->StringManager[thr_num].CheckStringInclusion(string,include_key_2);


     bool char_before_sharp = false; //  sharp symbol = #

     if(string[0]!= '#'){

        char_before_sharp = true;
     }

     // In metaprograms, #include key is used on the inside code

     // Therefore, there may be false include therms which is used in the metaprograms

     // in order to produce header files. If there is a character before the sharp symbol,

     // it is a meta program code. ( simething like write{ #include \"sample.h\" })

     if(!char_before_sharp){

        if(include_dec_cond_1 || include_dec_cond_2){

           include_decleration_cond = true;
        }
     }

     return include_decleration_cond;
}


void Project_Src_Code_Rdr::Determine_Class_Function_Pattern(std::string file_sys_path, std::string & pattern)
{
     std::string file_name;

     this->Determine_File_Name(file_sys_path,file_name);

     size_t file_name_size = file_name.length();

     this->Clear_String_Memory(pattern);

     for(size_t i=0;i<file_name_size;i++)
     {
         if(file_name[i]=='.'){

            break;
         }
         else{

              pattern.push_back(file_name[i]);

         }
     }

     std::string name_space_opr = "::";

     size_t opr_size = name_space_opr.length();

     for(size_t i=0;i<opr_size;i++){
     
         pattern.push_back(name_space_opr[i]);
     }

     pattern.shrink_to_fit();
}




std::string Project_Src_Code_Rdr::Extract_Include_Decleration(std::string string)
{
     size_t size = string.length();

     int start_point = 0;


     for(size_t k=0;k<size;k++){

         if((string[k] == '\"') || (string[k] == '<')) {

            break;
         }
         else{

            start_point++;
         }
     }

     start_point = start_point + 1;

     size_t end_point = start_point;

     for(size_t k=start_point;k<size;k++){

         if((string[k] == '\"') || (string[k] == '>')){

            break;
         }
         else{

              end_point++;
         }
     }

     std::string include_declaration;

     for(size_t i=start_point;i<end_point;i++){

         include_declaration.push_back(string[i]);
     }


     if(this->opr_sis == 'w'){

        for(size_t i=0;i<include_declaration.length();i++){

            if(include_declaration[i] == '/'){

               include_declaration[i] = '\\';
            }
        }
     }

     return include_declaration;
}

void Project_Src_Code_Rdr::Clear_Buffer_Memory(FileData & buffer){

     this->Clear_Vector_Memory(buffer.include_declerations);

     this->Clear_String_Memory(buffer.sys_path);

     this->Clear_String_Memory(buffer.file_name);

     this->Clear_String_Memory(buffer.cmbn_name);
}



const std::vector<std::string> * Project_Src_Code_Rdr::Get_Include_Declerations(int i) const
{    
     return &this->Code_Dt.at(i).include_declerations;
}

std::string Project_Src_Code_Rdr::Get_File_Path(int i) const {

     return this->Code_Dt.at(i).sys_path;
}

std::string Project_Src_Code_Rdr::Get_File_Name(int i) const {

     return this->Code_Dt.at(i).file_name;
}


std::string Project_Src_Code_Rdr::Get_Combined_File_Name(int i) const {

     return this->Code_Dt.at(i).file_name;
}


const FileData * Project_Src_Code_Rdr::Find_File_Data_From_Path(std::string path) const
{
    try {        

         return  this->Map_Path.at(path);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Path,";

         std::cout << "\n the file located on " << path << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


const  FileData * Project_Src_Code_Rdr::Find_File_Data_From_Name(std::string name) const
{
    try {        

         return this->Map_Name.at(name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Name,";

         std::cout << "\n the file located on " << name << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


const FileData * Project_Src_Code_Rdr::Find_File_Data_From_Directory_File_Name_Combination(std::string combined_name) const
{
    try {        

         return this->Map_Cmbn.at(combined_name);
    }
    catch (const std::out_of_range & oor) {
        
         std::cerr << "\n Out of Range error: " << oor.what() << '\n';

         std::cout << "\n Inside Project_Src_Code_Rdr instance,";

         std::cout << "\n Inside Find_File_Data_From_Combined_Name,";

         std::cout << "\n the file located on " << combined_name << " can not find!.\n";

         exit(EXIT_FAILURE);
    }     
}


bool Project_Src_Code_Rdr::Is_This_Repo_File(std::string path){

     bool is_this_repo_file = false;

     if(this->Map_Path.find(path)!=this->Map_Path.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}


bool Project_Src_Code_Rdr::Check_Repo_File_Status(std::string name){

     bool is_this_repo_file = false;

     if(this->Map_Name.find(name)!=this->Map_Name.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}


bool Project_Src_Code_Rdr::Check_Repo_File_Status_From_Directory_File_Name_Combination(std::string combined_name){
     
     bool is_this_repo_file = false;

     if(this->Map_Cmbn.find(combined_name)!=this->Map_Cmbn.end()){

        is_this_repo_file = true;
     }

     return is_this_repo_file;
}



const std::vector<std::string> * Project_Src_Code_Rdr::Get_Included_Headers_From_Path( std::string path) const 
{
     const FileData * ptr = this->Find_File_Data_From_Path(path);

     return &ptr->include_declerations;
}


size_t Project_Src_Code_Rdr::Get_Project_Files_Number() const
{
       return this->Code_Dt.size();
}












/*  THE MEMORY MANAGEMENT FUNCTIONS  ------------------------------------- */


void Project_Src_Code_Rdr::Clear_Object_Memory(){

     if(!this->Memory_Delete_Condition){
     
         this->Memory_Delete_Condition = true;

         this->Clear_Dynamic_Memory();
     }
}


void Project_Src_Code_Rdr::Clear_Dynamic_Memory(){
     
     std::vector<FileData>::iterator it;

     for(auto it=this->Code_Dt.begin();it<this->Code_Dt.end();it++){
       
         this->Clear_Vector_Memory(it->include_declerations);
         this->Clear_String_Memory(it->sys_path);
         this->Clear_String_Memory(it->file_name);
         this->Clear_String_Memory(it->cmbn_name);
     }

     this->Code_Dt.clear();

     this->Code_Dt.shrink_to_fit();


     this->Map_Path.clear();

     this->Map_Name.clear();

     this->Map_Cmbn.clear();
}



void Project_Src_Code_Rdr::Clear_Thread_Objects_Memory(){

     for(int i=0;i<16;i++){
     
         if(this->Hdr_Determiner[i] != nullptr){
              
            delete this->Hdr_Determiner[i];

            this->Hdr_Determiner[i] = nullptr;
         }             
     }
         
     delete [] this->Hdr_Determiner;

     this->Hdr_Determiner = nullptr;
     
     
     for(int i=0;i<16;i++){

         if(this->Src_Determiner[i]!= nullptr){

            delete this->Src_Determiner[i];

            this->Src_Determiner[i] = nullptr;
         }                 
     }

     delete [] this->Src_Determiner;

     this->Src_Determiner = nullptr;


     for(int i=0;i<16;i++){

        this->FileManager[i].Clear_Dynamic_Memory();
     }

     this->Clear_Vector_Memory(this->FilePaths);
}


void Project_Src_Code_Rdr::Clear_Vector_Memory(std::vector<std::string> & vec){

     if(!vec.empty()){

         std::vector<std::string>::iterator it;

         auto begin = vec.begin();

         auto end   = vec.end();

         for(auto it=begin;it<end;it++){

             if(!it->empty()){

                 it->clear();

                 it->shrink_to_fit();
              }
         }

         vec.clear();

         vec.shrink_to_fit();
     }
}

void Project_Src_Code_Rdr::Clear_String_Memory(std::string & str){

    if(!str.empty()){
    
        str.clear();

        str.shrink_to_fit();
    }
}