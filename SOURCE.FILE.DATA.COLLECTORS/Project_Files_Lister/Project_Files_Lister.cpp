
#include "Project_Files_Lister.h"

Project_Files_Lister::Project_Files_Lister(char * DesPATH, char opr_sis) :

   Src_Data_Col(DesPATH,opr_sis), Des_Reader(DesPATH), Git_Data_Receiver(DesPATH),

   Header_Determiner(DesPATH,opr_sis), File_Data_Cltr(opr_sis)
{

    this->Initialize_Members(opr_sis);
}


Project_Files_Lister::~Project_Files_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}

void Project_Files_Lister::Initialize_Members(char opr_sis){

     this->operating_sis = opr_sis;

     this->Source_File_Number = 0;

     this->Memory_Delete_Condition = false;

     this->git_record_size = 0;

     this->Header_File_Number = 0;

     this->independent_header_files_number = 0;
}


void Project_Files_Lister::Determine_Git_Repo_Info()
{
     this->Git_Data_Receiver.Determine_Git_Repo_Info();

     this->git_record_size = this->Git_Data_Receiver.Get_Git_File_Index_Size();

     this->Repo_Dir = this->Git_Data_Receiver.Get_Git_Repo_Directory();
;
     this->Determine_Source_File_Number();

     this->Determine_Header_File_Number();

     this->Collect_Source_Files_Data();

     this->Collect_Independent_Header_Files_Data();

     this->Determine_Class_Header_Files();
}


void Project_Files_Lister::Determine_Source_File_Number()
{
     for(int i=0;i<this->git_record_size-1;i++){

         std::string file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_source_file   = this->Source_Determiner.Is_Source_File(file_path);

         if(is_source_file){

            this->Source_File_Number++;
         }
    }
}


void Project_Files_Lister::Determine_Header_File_Number()
{
     for(int i=0;i<this->git_record_size-1;i++){

         std::string file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_header_file   = this->Header_Determiner.Is_Header(file_path);

         if(is_header_file){

            this->Header_File_Number++;
         }
     }
}


void Project_Files_Lister::Collect_Source_Files_Data()
{
     for(int i=0;i<this->git_record_size-1;i++){

         std::string file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         bool is_source_file  = this->Source_Determiner.Is_Source_File(file_path);


         if(is_source_file){

            Build_System_Data Temp_Data;

            this->Src_Data_Col.Clear_Dynamic_Memory();

            this->Place_Source_File_Data(&Temp_Data,file_path);

            this->Place_Source_File_Headers_Data(&Temp_Data);

            this->Data.push_back(Temp_Data);
         }
      }
}


void Project_Files_Lister::Place_Source_File_Data(Build_System_Data * Data, std::string src_path)
{
     this->Src_Data_Col.Receive_Source_File_Data(src_path);

     this->Src_Data_Col.Determine_Git_Record_Source_File_Path(&Data->git_record_path,src_path);

     this->Src_Data_Col.Determine_Git_Record_Source_File_Directory(&Data->git_record_dir,src_path);

     Data->is_this_a_source_file = true;

     Data->is_this_a_header_file = false;

     Data->File_Path = "";              // The file exact path ( System Path )

     this->File_Data_Cltr.Determine_File_Exact_Path(&Data->File_Path,this->Repo_Dir,src_path);

     this->File_Data_Cltr.Extract_Upper_Directory_Path(&Data->File_Directory,Data->File_Path);

     this->File_Data_Cltr.Determine_File_Name(&Data->File_Name,Data->File_Path);

     this->File_Data_Cltr.Determine_Source_File_Name_With_Ext(&Data->File_Name_With_Ext,Data->File_Name);
}


void Project_Files_Lister::Place_Source_File_Headers_Data(Build_System_Data * Data){

     int Inc_Header_Number = this->Src_Data_Col.Get_Included_File_Number();

     Data->Included_Header_Files_Number = Inc_Header_Number;

     if(Inc_Header_Number > 0){

        for(int k=0;k<Inc_Header_Number;k++){

            this->Place_Headers_Data(Data,k);
        }
     }
}


void Project_Files_Lister::Place_Headers_Data(Build_System_Data * Data, int hdr_num)
{
     std::string Included_File =

     this->Src_Data_Col.Get_Include_File_Name(hdr_num);

     std::string Included_File_Directory =

     this->Src_Data_Col.Get_Include_File_Directory(hdr_num);

     std::string Include_File_Git_Record_Dir =

     this->Src_Data_Col.Get_Include_File_Git_Record_Directory(hdr_num);

     std::string Include_File_Git_Record_Path =

     this->Src_Data_Col.Get_Include_File_Git_Record_Path(hdr_num);


     Data->Included_Header_Files.push_back(Included_File);

     Data->Included_Header_Files_Directories.push_back(Included_File_Directory);

     Data->Included_Header_Files_Git_Record_Dir.push_back(Include_File_Git_Record_Dir);

     Data->Included_Header_Files_Git_Record_Path.push_back(Include_File_Git_Record_Path);


     if(this->operating_sis == 'w'){

        std::string path;

        std::string dir  = Data->Included_Header_Files_Directories[0];

        std::string name = Data->Included_Header_Files[0];

        this->Src_Data_Col.Determine_Header_Files_System_Paths(&path,dir,name);

        Data->Included_Header_Files_System_Path.push_back(path);
     }
}


void Project_Files_Lister::Determine_Class_Header_Files()
{
     int src_num = this->Get_Source_File_Number();

     for(int i=0;i<src_num;i++){

         this->Determine_Class_Header_File_Name(i);
     }
}


void Project_Files_Lister::Determine_Class_Header_File_Name(int data_num)
{
     // This is the case when the source file include more than one header
     // file and one of them is the definition of the source file (the definition of the class)

     int total_hdr_number = this->Get_Source_File_Include_File_Number(data_num);

     std::string  src_name  = this->Get_Source_File_Name(data_num);

     for(int i=0;i<total_hdr_number;i++){

         std::string  hdr_name = this->Get_Source_File_Header(data_num,i);

         size_t hdr_name_size = hdr_name.length();

         std::string hdr_temp;

         for(size_t i=0;i<hdr_name_size;i++){

            if(hdr_name[i] == '.'){

               break;
            }
            else{

              hdr_temp.append(1,hdr_name[i]);
            }
         }

         bool is_equal = this->Check_String_Equality(src_name,hdr_temp);

         std::string hdr_path = this->Get_Source_File_Header_System_Path(data_num,i);

         if(is_equal){

            this->Data[data_num].class_header_file_name = src_name;

            this->Data[data_num].class_header_file_path = hdr_path;

            break;
         }
     }
}



void Project_Files_Lister::Collect_Independent_Header_Files_Data()
{
     this->independent_header_files_number = 0;

     for(int i=0;i<this->git_record_size-1;i++){

         std::string file_path = this->Git_Data_Receiver.Get_Git_File_Index(i);

         std::string file_name = "";

         bool is_header_file = this->Header_Determiner.Is_Header(file_path);

         bool is_this_included_already = false;

         if(is_header_file){

            this->File_Data_Cltr.Determine_File_Name_With_Ext(&file_name,file_path);

            for(int k=0;k<this->Get_Source_File_Number();k++){

                int inc_file_num = this->Get_Source_File_Include_File_Number(k);

                for(int j=0;j<inc_file_num;j++){

                    std::string included_file_name = this->Get_Source_File_Header(k,j);

                    is_this_included_already = this->CheckStringInclusion(file_name,included_file_name);

                    if(is_this_included_already){

                       break;
                    }
                }

                if(is_this_included_already){

                   break;
                }
            }

            if(!is_this_included_already){

               if(this->operating_sis == 'w'){

                   this->Header_Determiner.Clear_Dynamic_Memory();

                   this->Header_Determiner.Determine_Header_File_System_Path(this->Repo_Dir,file_path);

                   std::string Header_System_Path = this->Header_Determiner.Get_Header_File_System_Path();

                   this->independent_header_files.push_back(Header_System_Path);

                   this->independent_header_files_number++;
               }
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

void Project_Files_Lister::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         if(!this->independent_header_files.empty()){

             this->independent_header_files.clear();
         }

         if(!this->Data.empty()){

            this->Data.clear();
         }
      }
}


int Project_Files_Lister::Get_Source_File_Number(){

    return this->Source_File_Number;
}

std::string Project_Files_Lister::Get_Source_File_Directory(int num){

    return this->Data[num].File_Directory;
}

std::string Project_Files_Lister::Get_Source_File_Git_Record_Path(int num){

    return this->Data[num].git_record_path;
}

std::string Project_Files_Lister::Get_Source_File_System_Path(int num){

    return this->Data[num].File_Path;
}

std::string Project_Files_Lister::Get_Source_File_Name(int num){

    return this->Data[num].File_Name;
}

std::string Project_Files_Lister::Get_Source_File_Name_With_Ext(int num){

    return this->Data[num].File_Name_With_Ext;
}

int  Project_Files_Lister::Get_Source_File_Include_File_Number(int num){

     return this->Data[num].Included_Header_Files_Number;
}

int Project_Files_Lister::Get_Indenpendent_Header_Files_Number(){

    return this->independent_header_files_number;
}

std::string Project_Files_Lister::Get_Source_File_Header(int src_num, int hdr_num){

    return this->Data[src_num].Included_Header_Files[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_Directory(int src_num, int hdr_num){

    return this->Data[src_num].Included_Header_Files_Directories[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_System_Path(int src_num, int hdr_num){

    return this->Data[src_num].Included_Header_Files_System_Path[hdr_num];
}

std::string Project_Files_Lister::Get_Class_File_Header_System_Path(int src_num){

    return this->Data[src_num].class_header_file_path;
}

std::string Project_Files_Lister::Get_Class_File_Header_Name(int src_num){

    return this->Data[src_num].class_header_file_name;
}

std::string Project_Files_Lister::Get_Source_File_Header_Git_Record_Path(int src_num, int hdr_num){

    return this->Data[src_num].Included_Header_Files_Git_Record_Path[hdr_num];
}

std::string Project_Files_Lister::Get_Source_File_Header_Git_Record_Dir(int src_num, int hdr_num){

    return this->Data[src_num].Included_Header_Files_Git_Record_Dir[hdr_num];
}

std::string Project_Files_Lister::Get_Independent_Header_File(int num){

    return this->independent_header_files[num];
}

std::string Project_Files_Lister::Get_Source_File_Git_Record_Directory(int src_num){

    return this->Data[src_num].git_record_dir;
}
