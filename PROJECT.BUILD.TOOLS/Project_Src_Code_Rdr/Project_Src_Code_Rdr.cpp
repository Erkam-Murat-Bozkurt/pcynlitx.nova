

#include "Project_Src_Code_Rdr.hpp"


Project_Src_Code_Rdr::Project_Src_Code_Rdr(char opr_sis)
{
   this->Memory_Delete_Condition = false;

   this->opr_sis = opr_sis;
}



Project_Src_Code_Rdr::~Project_Src_Code_Rdr(){

    if(!this->Memory_Delete_Condition){
    
        this->Clear_Object_Memory();       
    }   
}




void Project_Src_Code_Rdr::Receive_Git_Data_Processor(Git_Data_Processor * ptr)
{
     this->Git_Data_Proc = ptr;

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

     if(repo_size >= 50){
     
        this->Read_For_Large_Data_Set(repo_size);
     }
     else{

         if(repo_size>16){

             this->Read_For_Middle_Data_Set(repo_size);
         }
         else{

             this->Read_For_Small_Data_Set(repo_size);
         }
     }

     if(!this->threadPool.empty()){

         this->threadPool.clear();
     }

     this->Code_Dt.shrink_to_fit();


     for(size_t i=0;i<this->Code_Dt.size();i++){

         this->Map_Path.insert(std::make_pair(this->Code_Dt.at(i).sys_path, &this->Code_Dt.at(i)));
            
         this->Map_Name.insert(std::make_pair(this->Code_Dt.at(i).file_name,&this->Code_Dt.at(i)));

         this->Map_Cmbn.insert(std::make_pair(this->Code_Dt.at(i).cmbn_name,&this->Code_Dt.at(i)));
     }

     this->Clear_Thread_Objects_Memory();
}


void Project_Src_Code_Rdr::Read_For_Large_Data_Set(size_t repo_size){

     size_t str=0, end=0;

     size_t thread_num = repo_size/20;

     if(thread_num > 64){

        thread_num = 64;
     }

     size_t remaining_job = 0;

     size_t range =this->Split_Range(repo_size,thread_num,remaining_job);


     for(int i=0;i<thread_num;i++){

         if(i==0){

            str = 0;

            end = range;
         }
         else{
               str  = end;

               end  = end + range;

               if(remaining_job > 0){

                  end = end+1;

                  remaining_job--;
               }
         }

         if(i==(thread_num-1)){
            
            end = repo_size;
         }

         this->threadPool.push_back(std::thread(&Project_Src_Code_Rdr::Read_Source_Code,this,str,end));
     }
    
     for(size_t i=0;i<thread_num;i++){
            
         this->threadPool[i].join();
     }
}




void Project_Src_Code_Rdr::Read_For_Middle_Data_Set(size_t repo_size){

     int thread_number = 16;
     
     int division = repo_size/thread_number;
        
     for(int i=0;i<thread_number;i++){

         int str  = i*division;

         int end  = (i+1)*division;

         if(i==(thread_number-1)){

            end = repo_size;
         }

         this->threadPool.push_back(std::thread(&Project_Src_Code_Rdr::Read_Source_Code,this,str,end));
     }
    
     for(int i=0;i<thread_number;i++){
     
         this->threadPool[i].join();
     }
}

void Project_Src_Code_Rdr::Read_For_Small_Data_Set(size_t repo_size){

     this->Read_Source_Code(0,repo_size);
}


size_t Project_Src_Code_Rdr::Split_Range(size_t range_size, size_t partition, size_t & remaining_job){

    if(range_size == 0){

        range_size = 1;
    }

    if(partition == 0){

        partition = 1;
    }

    int range  = range_size/partition; 

    if(range<1){

        range = 1;
    }

    remaining_job = range_size- partition*range;

    return range;    
}


void Project_Src_Code_Rdr::Read_Source_Code(int start_point, int end_point){

     std::unique_lock<std::mutex> mt(this->mtx);

     mt.unlock();


     Header_File_Determiner Hdr_Determiner(this->opr_sis);

     Hdr_Determiner.Receive_Git_Data_Processor(this->Git_Data_Proc);

     Source_File_Determiner Src_Determiner;

     Cpp_FileOperations FileManager;

     FileManager.Receive_Operating_System(this->opr_sis);

     StringOperator StringManager;

     StringManager.Receive_Operating_System(this->opr_sis);


     for(int i=start_point;i<end_point;i++){

         Hdr_Determiner.Clear_Dynamic_Memory();

         Src_Determiner.Clear_Dynamic_Memory();
     
         std::string file_sys_path = this->FilePaths.at(i);
         
         bool is_header   = Hdr_Determiner.Is_Header(file_sys_path);

         bool is_src_file = Src_Determiner.Is_Source_File(file_sys_path);


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
            buffer.inclusion_number = 0;


            if(is_header){

               buffer.is_header_file = true;
               buffer.is_main_file   = false;
               buffer.is_source_file = false;
            }

            FileManager.Read_File(file_sys_path);

            int FileSize = FileManager.GetFileSize();

            for(int k=0;k<FileSize;k++){
         
                std::string string_line = FileManager.GetFileLine(k);

                this->Delete_Spaces_on_String(&string_line);


                if(is_src_file){

                   std::string main_file_key   = "main(";

                   bool is_main_key_exist 
                   
                   = StringManager.CheckStringInclusion(string_line,main_file_key);


                   if(is_main_key_exist){

                      buffer.is_main_file   = true;
                      buffer.is_header_file = false;
                      buffer.is_source_file = false;
                   }

                                
                   bool is_member_function_key_exist 
                   
                   = StringManager.CheckStringInclusion(string_line,class_function_pattern);


                   // It is the member function scop resolution key word 
                   // For member function sample::function, it is "sample::"

                   if(is_member_function_key_exist){      

                      buffer.is_source_file = true;
                      buffer.is_header_file = false;
                      buffer.is_main_file   = false;
                   }
                }

                bool is_include_decleration = this->Include_Decleration_Test(string_line,StringManager);

                if(is_include_decleration){

                   std::string include_decleration = this->Extract_Include_Decleration(string_line);

                   if(this->Is_This_A_Combined_Include_Delaration(include_decleration)){

                      std::string comb_dec;

                      this->Extract_Directory_File_Name_Combination(include_decleration,comb_dec);
                      
                      if(this->Is_There_Upper_Directory_Symbol(comb_dec)){

                         std::string real_inc = this->Find_Real_Include_Decleration(file_sys_path,include_decleration);

                         buffer.include_declerations.push_back(real_inc);
                    }
                    else{

                        buffer.include_declerations.push_back(comb_dec);
                    }
                   }
                   else{

                        buffer.include_declerations.push_back(include_decleration);
                   }

                   buffer.inclusion_number++;
                }
            }

            FileManager.Clear_Dynamic_Memory();
            
            StringManager.Clear_Dynamic_Memory();

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


bool Project_Src_Code_Rdr::Is_There_Upper_Directory_Symbol(std::string inc_dec){

     bool is_there = false;

     StringOperator StringManager;

     std::string up_w = "..\\";

     std::string up_l = "../";

     bool is_there_w = StringManager.CheckStringInclusion(inc_dec,up_w);

     bool is_there_l = StringManager.CheckStringInclusion(inc_dec,up_l);

     if(is_there_l || is_there_w){

        is_there = true;
     }
     
     return is_there;
}


int Project_Src_Code_Rdr::How_Many_UpDir_Symbol_Exist(std::string inc_dec){

     int point_num = 0, up_dir_num=0;

     for(size_t i=0;i<inc_dec.length();i++){

         if(inc_dec[i] == '.'){

             point_num++;
         }
     }

     up_dir_num = point_num/2;

     return up_dir_num;
}



std::string Project_Src_Code_Rdr::Find_Real_Include_Decleration(std::string file_path, std::string inc_dec){

     int stage_num = this->How_Many_UpDir_Symbol_Exist(inc_dec) +1;

     size_t path_start_point = 0, path_end_point =0, dec_start_point =0;

     for(size_t i=file_path.length()-1;i>0;i--){

         if((file_path.at(i)== '\\') || (file_path.at(i) == '/')){

             if(stage_num>0){

                stage_num--;
             }
             else{ 

                  path_start_point = i+1;

                  break;
             }
         }
     }

     for(size_t i=path_start_point;i<file_path.length()-1;i++){

         if((file_path.at(i)== '\\') || (file_path.at(i) == '/')){

             path_end_point = i;

             break;
         }
     }

     for(size_t i=inc_dec.length()-1;i>0;i--){

         if((inc_dec.at(i)== '\\') || (inc_dec.at(i) == '/')){

             dec_start_point = i+1;

             break;
         }
     }

     std::string real_dec;

     for(size_t i=path_start_point;i<path_end_point;i++){

         real_dec.push_back(file_path.at(i));
     }

     if(this->opr_sis == 'w'){

        if(real_dec.back()!='\\'){

            real_dec.push_back('\\');
        }
     }


     if(this->opr_sis == 'l'){

        if(real_dec.back()!='/'){

            real_dec.push_back('/');
        }
     }

     for(size_t i=dec_start_point;i<inc_dec.length();i++){

         real_dec.push_back(inc_dec.at(i));
     } 

     return real_dec;
}


bool Project_Src_Code_Rdr::Is_This_A_Combined_Include_Delaration(std::string name)
{
     bool is_combined = false;

     size_t name_size = name.length();

     for(size_t i=0;i<name_size;i++){

         if(((name[i]=='/') || (name[i]=='\\'))){

            is_combined = true;

            return is_combined;
         }
     }

     return is_combined;
}


void Project_Src_Code_Rdr::Extract_Directory_File_Name_Combination(std::string inc_dec, 

     std::string & dir_file_com)
{
     size_t dec_size = inc_dec.length();

     size_t dir_char_num = 0, start_point = dec_size;

     for(size_t i=dec_size;i>0;i--){

         if((inc_dec[i] == '/') || (inc_dec[i] == '\\')){

            dir_char_num++;

            if(dir_char_num>1){

               start_point = i+1;        

               break;
            }
         }
         
         start_point--;        
     }
    
     for(size_t i=start_point;i<dec_size;i++){

         dir_file_com.push_back(inc_dec[i]);
     }

     dir_file_com.shrink_to_fit();
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


bool Project_Src_Code_Rdr::Include_Decleration_Test(std::string string, StringOperator & str_opr)
{
     bool include_decleration_cond = false;

     char include_key_1 [] = "#include\"";  // double_quotation_mark

     char include_key_2 [] = "#include<";  // double_quotation_mark


     bool include_dec_cond_1 = false;

     bool include_dec_cond_2 = false;
     

     include_dec_cond_1 = str_opr.CheckStringInclusion(string,include_key_1);

     include_dec_cond_2 = str_opr.CheckStringInclusion(string,include_key_2);


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