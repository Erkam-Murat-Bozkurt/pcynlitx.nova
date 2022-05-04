
#include "Project_Files_Lister.h"

Project_Files_Lister::Project_Files_Lister(){

    this->Source_File_Number = 0;

    this->Memory_Delete_Condition = true;

    this->git_record_size = 0;

    this->Data = nullptr;

    this->Header_File_Number = 0;
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

     this->Determine_Class_Header_Files();
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

         char * file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_source_file = this->Source_Determiner.Is_Source_File(file_path);

         if(is_source_file){

            this->Place_Source_File_Data(index,file_path,'w');

            this->Place_Source_File_Headers_Data(index,'w');

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
         this->Data[i].git_record_dir = nullptr;        // The git record directory
         this->Data[i].File_Directory = nullptr;        // The directory of the file which is record constructed
         this->Data[i].File_Path = nullptr;             // The file exact path ( System Path )
         this->Data[i].File_Name = nullptr;             // The file name witout extentation
         this->Data[i].File_Name_With_Ext = nullptr;    // The header file name with extention
         this->Data[i].class_header_file_name = nullptr;
         this->Data[i].class_header_file_path = nullptr;
         this->Data[i].Included_Header_Files = nullptr; // The list of included header files if the file is a source file
         this->Data[i].Included_Header_Files_Directories = nullptr;
         this->Data[i].Included_Header_Files_System_Path = nullptr;
         this->Data[i].Included_Header_Files_Git_Record_Path = nullptr;
         this->Data[i].Included_Header_Files_Git_Record_Dir = nullptr;
         this->Data[i].Included_Header_Files_Number = 0;// The number of the header file included if the file is a source file
      }
}


void Project_Files_Lister::Place_Source_File_Data(int index, char * src_path, char opr_sis){


     this->Src_Data_Col.Clear_Dynamic_Memory();

     this->Src_Data_Col.Receive_Source_File_Data(&this->Git_Data_Receiver,src_path);


     this->Data[index].is_this_a_source_file = true;

     this->Data[index].is_this_a_header_file = false;

     this->Data[index].File_Path = nullptr;              // The file exact path ( System Path )


     char ** path = &this->Data[index].File_Path;

     char * repo = this->Repo_Dir;

     this->Data_Cltr.Determine_File_Exact_Path(path,repo,src_path,opr_sis);


     // The directory of the file which is record constructed


     char ** dir =  &this->Data[index].File_Directory;

     this->Data_Cltr.Extract_Upper_Directory_Path(dir,*path,'w');



     char ** name = &this->Data[index].File_Name;

     this->Data_Cltr.Determine_File_Name(name,*path);


     char ** name_ext = &this->Data[index].File_Name_With_Ext;

     this->Data_Cltr.Determine_Source_File_Name_With_Ext(name_ext,*name);



     char ** git_path = &this->Data[index].git_record_path;

     this->Src_Data_Col.Determine_Git_Record_Source_File_Path(git_path,src_path,opr_sis);


     char ** git_dir = &this->Data[index].git_record_dir;

     this->Src_Data_Col.Determine_Git_Record_Source_File_Directory(git_dir,src_path,opr_sis);
}


void Project_Files_Lister::Place_Source_File_Headers_Data(int index,char opr_sis){

    int Inc_Header_Number = this->Src_Data_Col.Get_Included_File_Number();

    this->Data[index].Included_Header_Files_Number = Inc_Header_Number;

    if(Inc_Header_Number > 0){

       this->Allocate_Memory_For_Headers_Data(index,Inc_Header_Number);

       for(int k=0;k<Inc_Header_Number;k++){

           this->Place_Headers_Data(index,k,opr_sis);
       }
    }
}


void Project_Files_Lister::Allocate_Memory_For_Headers_Data(int index,int hdr_num){

     this->Data[index].Included_Header_Files =

           new char * [5*hdr_num];

     this->Data[index].Included_Header_Files_Directories =

           new char * [5*hdr_num];

     this->Data[index].Included_Header_Files_System_Path =

           new char * [5*hdr_num];

     this->Data[index].Included_Header_Files_Git_Record_Path =

           new char * [5*hdr_num];

     this->Data[index].Included_Header_Files_Git_Record_Dir =

           new char * [5*hdr_num];
}

void Project_Files_Lister::Place_Headers_Data(int index,int hdr_num, char operating_sis){

     char * Included_File =

     this->Src_Data_Col.Get_Include_File_Name(hdr_num);


     char * Included_File_Directory =

     this->Src_Data_Col.Get_Include_File_Directory(hdr_num);


     char * Include_File_Git_Record_Dir =

     this->Src_Data_Col.Get_Include_File_Git_Record_Directory(hdr_num);


     char * Include_File_Git_Record_Path =

     this->Src_Data_Col.Get_Include_File_Git_Record_Path(hdr_num);


     char ** name = &this->Data[index].Included_Header_Files[hdr_num];

     this->Place_String(name,Included_File);


     char ** dir = &this->Data[index].Included_Header_Files_Directories[hdr_num];

     this->Place_String(dir,Included_File_Directory);


     char ** git_dir = &this->Data[index].Included_Header_Files_Git_Record_Dir[hdr_num];

     this->Place_String(git_dir,Include_File_Git_Record_Dir);


     char ** git_record_path = &this->Data[index].Included_Header_Files_Git_Record_Path[hdr_num];

     this->Place_String(git_record_path,Include_File_Git_Record_Path);


     if(operating_sis == 'w'){

        char ** path = &this->Data[index].Included_Header_Files_System_Path[hdr_num];

        char * dir  = this->Data[index].Included_Header_Files_Directories[hdr_num];

        char * name = this->Data[index].Included_Header_Files[hdr_num];

        this->Src_Data_Col.Determine_Header_Files_System_Paths(path,dir,name,'w');
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

void Project_Files_Lister::Determine_Class_Header_Files(){

     int src_num = this->Get_Source_File_Number();

     for(int i=0;i<src_num;i++){

         this->Determine_Class_Header_File_Name(i);
     }
}

void Project_Files_Lister::Determine_Class_Header_File_Name(int data_num){

     // This is the case when the source file include more than one header file and one of them is
     // the definition of the source file (the definition of the class)

     int total_hdr_number = this->Get_Source_File_Include_File_Number(data_num);

     for(int i=0;i<total_hdr_number;i++){

        char * src_name = this->Get_Source_File_Name(data_num);

        char * hdr_name = this->Get_Source_File_Header(data_num,i);

        size_t hdr_name_size = strlen(hdr_name);

        char * hdr_temp = new char [2*hdr_name_size];

        int index =0;

        for(size_t i=0;i<hdr_name_size;i++){

           if(hdr_name[i] == '.'){

              break;
           }
           else{

             hdr_temp[index] = hdr_name[i];

             index++;
           }
        }

        hdr_temp[index] = '\0';


        bool is_equal   = this->Check_String_Equality(src_name,hdr_temp);

        char * hdr_path = this->Get_Source_File_Header_System_Path(data_num,i);

        if(is_equal){

           this->Data[data_num].class_header_file_name = src_name;

           this->Data[data_num].class_header_file_path = hdr_path;

           break;
        }

        delete [] hdr_temp;
     }
}


bool Project_Files_Lister::Check_String_Equality(char * firstString,char * secondString){

     size_t firstStringLength  = strlen(firstString);

     size_t secondStringLength = strlen(secondString);

     this->isStringsEqual = false;

     if(firstStringLength==secondStringLength){

        for(size_t i=0;i<firstStringLength;i++){

            if(firstString[i]!=secondString[i]){

               this->isStringsEqual = false;

               return this->isStringsEqual;
            }
        }

        this->isStringsEqual = true;

        return this->isStringsEqual;
     }
     else{

          this->isStringsEqual = false;

          return this->isStringsEqual;
     }
}


void Project_Files_Lister::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(this->Source_File_Number > 0){

           for(int i=0;i<this->Source_File_Number;i++){

               this->Clear_Pointer_Memory(&(this->Data[i].git_record_path));

               this->Clear_Pointer_Memory(&(this->Data[i].git_record_dir));

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

char * Project_Files_Lister::Get_Class_File_Header_System_Path(int src_num){

       return this->Data[src_num].class_header_file_path;
}

char * Project_Files_Lister::Get_Class_File_Header_Name(int src_num){

       return this->Data[src_num].class_header_file_name;
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

char * Project_Files_Lister::Get_Source_File_Git_Record_Directory(int src_num){

       return this->Data[src_num].git_record_dir;
}
