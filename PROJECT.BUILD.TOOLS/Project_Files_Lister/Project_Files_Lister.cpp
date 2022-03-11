
#include "Project_Files_Lister.h"

Project_Files_Lister::Project_Files_Lister(){

    this->Source_File_Number = 0;

    this->Memory_Delete_Condition = true;

    this->git_record_size = 0;

    this->Data = nullptr;

    this->Header_System_Path_Number = 0;

    this->Header_File_Number = 0;

    this->Header_Files_System_Paths = nullptr;
}

Project_Files_Lister::Project_Files_Lister(const

                  Project_Files_Lister & orig){


}

Project_Files_Lister::~Project_Files_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Project_Files_Lister::Receive_Descriptor_File_Reader(Descriptor_File_Reader * Pointer){

     this->Des_Reader_Pointer = Pointer;

     this->Git_Data_Receiver.Receive_Descriptor_File_Reader(Pointer);
}

void Project_Files_Lister::Determine_Git_Repo_Info(Descriptor_File_Reader * Des_Reader){

     this->Receive_Descriptor_File_Reader(Des_Reader);

     this->Git_Data_Receiver.Determine_Git_Repo_Info();

     this->git_record_size = this->Git_Data_Receiver.Get_Git_File_Index_Size();

     this->Repo_Dir = this->Git_Data_Receiver.Get_Git_Repo_Directory();

     this->Determine_Source_File_Number();

     this->Determine_Header_File_Number();

     this->Initialize_Data_Structures();

     this->Collect_Source_Files_Data('w');

     this->Collect_Independent_Header_Files_Data('w');

     this->Determine_Header_Files_System_Paths();
}

void Project_Files_Lister::Determine_Source_File_Number(){

     this->Source_File_Number = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         char * file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_source_file = this->Source_Determiner.Is_Source_File(file_path);

         if(is_source_file){

            this->Source_File_Number++;
         }
    }
}

void Project_Files_Lister::Determine_Header_File_Number(){

     this->Header_File_Number = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         char * file_path    = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_header_file = this->Header_Determiner.Is_Header(file_path);

         if(is_header_file){

            this->Header_File_Number++;
         }
    }
}

void Project_Files_Lister::Collect_Source_Files_Data(char operating_sis){

     int index = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         char * file_path    = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_source_file = this->Source_Determiner.Is_Source_File(file_path);

         if(is_source_file){

            this->Src_Data_Col.Clear_Dynamic_Memory();

            this->Src_Data_Col.Receive_Source_File_Data(&this->Git_Data_Receiver,file_path);


            this->Data[index].is_this_a_source_file = true;

            this->Data[index].is_this_a_header_file = false;

            this->Data[index].git_record_path = file_path;       // file path in git record

            this->Data[index].File_Path = nullptr;              // The file exact path ( System Path )


            this->Data_Cltr.Determine_File_Exact_Path(&(this->Data[index].File_Path),

                  this->Repo_Dir,file_path,'w');

            // The directory of the file which is record constructed

            this->Data_Cltr.Extract_Upper_Directory_Path(&(this->Data[index].File_Directory),

            this->Data[index].File_Path,'w');

            this->Data_Cltr.Determine_File_Name(&(this->Data[index].File_Name),

            this->Data[index].File_Path);

            this->Data_Cltr.Determine_Source_File_Name_With_Ext(&(this->Data[index].File_Name_With_Ext),

            this->Data[index].File_Name);



            int Inc_Header_Number = this->Src_Data_Col.Get_Included_File_Number();

            this->Data[index].Included_Header_Files_Number = Inc_Header_Number;

            if(Inc_Header_Number > 0){

              this->Data[index].Included_Header_Files =

                    new char * [5*Inc_Header_Number];

              this->Data[index].Included_Header_Files_Directories =

                    new char * [5*Inc_Header_Number];


              this->Data[index].Included_Header_Files_System_Path =

                   new char * [5*Inc_Header_Number];

              this->Data[index].Included_Header_Files_Git_Record_Path =

                   new char * [5*Inc_Header_Number];


              this->Data[index].Included_Header_Files_Git_Record_Dir =

                  new char * [5*Inc_Header_Number];


              for(int k=0;k<Inc_Header_Number;k++){

                 char * Included_File = this->Src_Data_Col.Get_Include_File_Name(k);

                 char * Included_File_Directory =

                 this->Src_Data_Col.Get_Include_File_Directory(k);

                 char * Include_File_Git_Record_Dir =

                 this->Src_Data_Col.Get_Include_File_Git_Record_Directory(k);

                 char * Include_File_Git_Record_Path =

                 this->Src_Data_Col.Get_Include_File_Git_Record_Path(k);



                 this->Place_String(&(this->Data[index].Included_Header_Files[k]),

                      Included_File);

                 this->Place_String(&(this->Data[index].Included_Header_Files_Directories[k]),

                      Included_File_Directory);


                 this->Place_String(&(this->Data[index].Included_Header_Files_Git_Record_Dir[k]),

                      Include_File_Git_Record_Dir);


                 this->Place_String(&(this->Data[index].Included_Header_Files_Git_Record_Path[k]),

                     Include_File_Git_Record_Path);


                 if(operating_sis == 'w'){

                    this->Src_Data_Col.Determine_Header_Files_System_Paths(

                    &(this->Data[index].Included_Header_Files_System_Path[k]),

                    this->Data[index].Included_Header_Files_Directories[k],

                    this->Data[index].Included_Header_Files[k],operating_sis);

                  }
              }
            }

            index++;
         }
       }
}

void Project_Files_Lister::Collect_Independent_Header_Files_Data(char operating_sis){

     int head_num = this->Header_File_Number;

     this->independent_header_files_number = 0;

     this->independent_header_files = new char * [5*head_num];

     int index = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         char * file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         char * file_name = nullptr;

         bool is_header_file = this->Header_Determiner.Is_Header(file_path);

         bool is_this_included_already = false;

         if(is_header_file){

            this->Data_Cltr.Determine_File_Name_With_Ext(&file_name,file_path);

            for(int k=0;k<this->Get_Source_File_Number();k++){

                int inc_file_num = this->Get_Source_File_Include_File_Number(k);

                for(int j=0;j<inc_file_num;j++){

                    char * included_file_name = this->Get_Source_File_Header(k,j);

                    is_this_included_already =

                         this->StringManager.CheckStringInclusion(file_name,included_file_name);

                    if(is_this_included_already){

                       break;
                    }
                }

                if(is_this_included_already){

                   break;
                }
            }

            if(!is_this_included_already){

               if(operating_sis == 'w'){

                   this->Header_Determiner.Clear_Dynamic_Memory();

                   this->Header_Determiner.Determine_Header_File_System_Path(this->Repo_Dir,file_path,'w');

                   char * Header_System_Path = this->Header_Determiner.Get_Header_File_System_Path();

                   this->Place_String(&(this->independent_header_files[index]),Header_System_Path);

                   this->independent_header_files_number++;

                   index++;
               }
            }
     }
   }
}

void Project_Files_Lister::Initialize_Data_Structures(){

     int total_project_file_num = this->Source_File_Number

                                + this->Header_File_Number;

     this->Data = new Build_System_Data [5*total_project_file_num];

     for(int i=0;i<5*total_project_file_num;i++){

         this->Data[i].is_this_a_source_file = false;
         this->Data[i].is_this_a_header_file = false;
         this->Data[i].git_record_path = nullptr;       // The file path in git record
         this->Data[i].File_Directory = nullptr;        // The directory of the file which is record constructed
         this->Data[i].File_Path = nullptr;             // The file exact path ( System Path )
         this->Data[i].File_Name = nullptr;             // The file name witout extentation
         this->Data[i].File_Name_With_Ext = nullptr;    // The header file name with extention
         this->Data[i].Included_Header_Files = nullptr; // The list of included header files if the file is a source file
         this->Data[i].Included_Header_Files_Directories = nullptr;
         this->Data[i].Included_Header_Files_System_Path = nullptr;
         this->Data[i].Included_Header_Files_Git_Record_Path = nullptr;
         this->Data[i].Included_Header_Files_Git_Record_Dir = nullptr;
         this->Data[i].Included_Header_Files_Number = 0;// The number of the header file included if the file is a source file
      }
}

void Project_Files_Lister::Place_String(char ** pointer, std::string string_line){

     size_t string_size = string_line.length();

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string_line[i];
     }

     (*pointer)[string_size] = '\0';
}

void Project_Files_Lister::Place_String(char ** pointer, char * string_line){

     size_t string_size = strlen(string_line);

     *pointer = new char [5*string_size];

     for(size_t i=0;i<string_size;i++){

        (*pointer)[i] = string_line[i];
     }

     (*pointer)[string_size] = '\0';
}

void Project_Files_Lister::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Source_File_Number > 0){

           for(int i=0;i<this->Source_File_Number;i++){

               this->Clear_Pointer_Memory(&(this->Data[i].git_record_path));

               this->Clear_Pointer_Memory(&(this->Data[i].File_Directory));

               this->Clear_Pointer_Memory(&(this->Data[i].File_Path));

               this->Clear_Pointer_Memory(&(this->Data[i].File_Name));

               this->Clear_Pointer_Memory(&(this->Data[i].File_Name_With_Ext));

               if(this->Data[i].Included_Header_Files != nullptr){

                  int inc_file_num = this->Data[i].Included_Header_Files_Number;

                  for(int k=0;k<inc_file_num;k++){

                      this->Clear_Pointer_Memory(&(this->Data[i].Included_Header_Files[k]));

                      this->Clear_Pointer_Memory(&(this->Data[i].Included_Header_Files_Directories[k]));

                      this->Clear_Pointer_Memory(&(this->Data[i].Included_Header_Files_System_Path[k]));

                  }

                  delete [] this->Data[i].Included_Header_Files;
                }
           }
         }
       }
}

void Project_Files_Lister::Determine_Header_Files_System_Paths(){

     this->Header_Files_System_Paths = new char * [5*this->Header_File_Number];

     for(int i=0;i<this->Header_File_Number;i++){

         this->Header_Files_System_Paths[i] = nullptr;
     }

     int index = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         char * file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         char * file_name = nullptr;

         bool is_header_file = this->Header_Determiner.Is_Header(file_path);

         if(is_header_file){

            this->Header_Determiner.Determine_Header_File_System_Path(this->Repo_Dir,file_path,'w');

            char * Header_System_Path = this->Header_Determiner.Get_Header_File_System_Path();

            this->Place_String(&this->Header_Files_System_Paths[index],Header_System_Path);

            this->Header_System_Path_Number++;

            index++;
         }
     }
}

void Project_Files_Lister::Clear_Pointer_Memory(char ** Pointer){

     if(*Pointer != nullptr){

       delete [] *Pointer;

       *Pointer = nullptr;
     }
}

int Project_Files_Lister::Get_Source_File_Number(){

    return this->Source_File_Number;
}

char * Project_Files_Lister::Get_Source_File_Directory(int num){

       return this->Data[num].File_Directory;
}

char * Project_Files_Lister::Get_Source_File_Git_Record_Path(int num){

      return this->Data[num].git_record_path;
}

char * Project_Files_Lister::Get_Source_File_System_Path(int num){

       return this->Data[num].File_Path;
}

char * Project_Files_Lister::Get_Source_File_Name(int num){

       return this->Data[num].File_Name;
}

char * Project_Files_Lister::Get_Source_File_Name_With_Ext(int num){

       return this->Data[num].File_Name_With_Ext;
}

int  Project_Files_Lister::Get_Source_File_Include_File_Number(int num){

     return this->Data[num].Included_Header_Files_Number;
}

int Project_Files_Lister::Get_Header_System_Paths_Number(){

    return this->Header_System_Path_Number;
}

int Project_Files_Lister::Get_Indenpendent_Header_Files_Number(){

    return this->independent_header_files_number;
}

char * Project_Files_Lister::Get_Source_File_Header(int src_num, int hdr_num){

      return this->Data[src_num].Included_Header_Files[hdr_num];
}

char * Project_Files_Lister::Get_Source_File_Header_Directory(int src_num, int hdr_num){

       return this->Data[src_num].Included_Header_Files_Directories[hdr_num];
}

char * Project_Files_Lister::Get_Source_File_Header_System_Path(int src_num, int hdr_num){

       return this->Data[src_num].Included_Header_Files_System_Path[hdr_num];
}

char * Project_Files_Lister::Get_Source_File_Header_Git_Record_Path(int src_num, int hdr_num){

       return this->Data[src_num].Included_Header_Files_Git_Record_Path[hdr_num];
}

char * Project_Files_Lister::Get_Source_File_Header_Git_Record_Dir(int src_num, int hdr_num){

       return this->Data[src_num].Included_Header_Files_Git_Record_Dir[hdr_num];
}

char * Project_Files_Lister::Get_Independent_Header_File(int num){

       return this->independent_header_files[num];
}

char * Project_Files_Lister::Get_Header_File_System_Path(int num){

       return this->Header_Files_System_Paths[num];
}
