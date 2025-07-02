
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



#include "DirectoryOperations.h"


DirectoryOperations::DirectoryOperations()
{
    this->Initialize_Mermbers();
};


DirectoryOperations::~DirectoryOperations()
{
     if(!this->Memory_Delete_Condition){

        this->Clear_Dynamic_Memory();
     }
};


void DirectoryOperations::Initialize_Mermbers(){

     this->CurrentDirectory = nullptr;

     this->Sub_Directory = nullptr;

     this->Upper_Directory = nullptr;

     this->RecordDirectoryPATH = nullptr;

     this->SystemCommand = nullptr;

     this->File_List = nullptr;

     this->c_str = nullptr;

     this->Memory_Delete_Condition = false;

     this->ReturnCondition = 0;

     this->File_Number = 0;
}

void DirectoryOperations::Clear_Dynamic_Memory(){

     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_Pointer_Memory(&this->CurrentDirectory);

         this->Clear_Pointer_Memory(&this->Sub_Directory);

         this->Clear_Pointer_Memory(&this->Upper_Directory);

         this->Clear_Pointer_Memory(&this->RecordDirectoryPATH);

         this->Clear_Pointer_Memory(&this->SystemCommand);

         this->Clear_String_Memory(&this->File_List);

         this->Clear_Pointer_Memory(&this->c_str);
     }
}

void DirectoryOperations::Clear_Pointer_Memory(char ** ptr){

     if(*ptr != nullptr){
               
        delete [] *ptr;

        *ptr = nullptr;
     }
}

void DirectoryOperations::Clear_String_Memory(std::string ** ptr)
{
     if(*ptr != nullptr){
               
        delete [] *ptr;

        *ptr = nullptr;
     }
}

void DirectoryOperations::DetermineCurrentDirectory(){

     this->Clear_Pointer_Memory(&this->CurrentDirectory);

     CHAR Buffer[BUFSIZE];

     GetCurrentDirectory(BUFSIZE, Buffer);

     char * Directory = Buffer;

     size_t Directory_Name_Size = strlen(Directory);

     this->Memory_Delete_Condition = false;

     this->CurrentDirectory = new char [5*Directory_Name_Size];

     this->Place_String(&this->CurrentDirectory,Directory,Directory_Name_Size);
}

void DirectoryOperations::DetermineSubDirectoryName(char * DirectoryName){

     this->Clear_Pointer_Memory(&this->Sub_Directory);

     this->DetermineCurrentDirectory();

     char Directory_Character [] {'\\','\0'};

     int CurrentDirectory_Name_Size = strlen(this->GetCurrentlyWorkingDirectory());

     int SubDirectory_Name_Size = strlen(DirectoryName);

     int NewDirectory_Name_Size = CurrentDirectory_Name_Size + SubDirectory_Name_Size;

     this->Memory_Delete_Condition = false;

     this->Sub_Directory  = new char [5*NewDirectory_Name_Size];

     int index_counter = 0;

     this->Place_Information(&this->Sub_Directory,this->GetCurrentlyWorkingDirectory(),&index_counter);

     this->Place_Information(&this->Sub_Directory,Directory_Character,&index_counter);

     this->Place_Information(&this->Sub_Directory,DirectoryName,&index_counter);

     this->Sub_Directory[index_counter] = '\0';
}

void DirectoryOperations::DetermineUpperDirectoryName(){

     this->Clear_Pointer_Memory(&this->Upper_Directory);

     this->DetermineCurrentDirectory();

     int CurrentDirectory_Name_Size = strlen(this->GetCurrentlyWorkingDirectory());

     int upper_directory_point = CurrentDirectory_Name_Size;

     for(int i=CurrentDirectory_Name_Size;i>0;i--){

          if(this->GetCurrentlyWorkingDirectory()[i] == '\\'){

             upper_directory_point--;

             break;
          }
          else{

              upper_directory_point--;
          }
     }

     upper_directory_point++;

     this->Memory_Delete_Condition = false;

     this->Upper_Directory = new char [5*upper_directory_point];

     this->Place_String(&this->Upper_Directory,this->GetCurrentlyWorkingDirectory(),upper_directory_point);
}

int DirectoryOperations::MakeSubDirectory(char * DirectoryName){

     this->DetermineSubDirectoryName(DirectoryName);

     this->ReturnCondition = this->MakeDirectory(this->GetSubDirectoryName());

     if(this->ReturnCondition == -1){

         this->RemoveSubDirectory(DirectoryName);

         this->ReturnCondition = this->MakeDirectory(this->GetSubDirectoryName());
     }

     return this->ReturnCondition;
}

int DirectoryOperations::RemoveSubDirectory(char * DirectoryName){

     this->DetermineSubDirectoryName(DirectoryName);

     this->ReturnCondition = this->RemoveDirectory(this->GetSubDirectoryName());

     if(this->ReturnCondition == -1){

        this->Remove_Directory_Recursively(DirectoryName);
     }

     return this->ReturnCondition;
}

int DirectoryOperations::MakeDirectory(char * path){

    int return_condition = this->ChangeDirectory(path);

    if(return_condition == 0){

       this->ReturnCondition = CreateDirectoryA(path,NULL);
    }
    else{

            this->RemoveDirectory(path);

            this->ReturnCondition = CreateDirectoryA(path,NULL);
    }

    return this->ReturnCondition;
};

int DirectoryOperations::MakeDirectory(std::string std_string_path){
    
    size_t length = std_string_path.length();

    char * path = new char [5*length];  // Converting std::string to cstring

    for(size_t i=0;i<length;i++){
    
        path[i] = std_string_path[i];
    }

    path[length] = '\0';

    int return_condition = this->ChangeDirectory(path);

    if(return_condition == 0){


       this->ReturnCondition = CreateDirectoryA(path,NULL);
    }
    else{

            this->RemoveDirectory(path);

            this->ReturnCondition = CreateDirectoryA(path,NULL);
    }

    this->Clear_Pointer_Memory(&path);

    return this->ReturnCondition;
};

int DirectoryOperations::ChangeDirectory(const char * path){

    this->DetermineCurrentDirectory();

    char * CurrentDirectory = this->GetCurrentlyWorkingDirectory();


    std::string CurrentDirectory_String;

    std::string TargetDirectory_String;

    int CurrentDirectory_Size = strlen(CurrentDirectory);

    for(int i=0;i<CurrentDirectory_Size;i++){

        CurrentDirectory_String.push_back(CurrentDirectory[i]);
    }

    CurrentDirectory_String.shrink_to_fit();

    int TargetDirectory_Size = strlen(path);

    for(int i=0;i<TargetDirectory_Size;i++){

       TargetDirectory_String.push_back(path[i]);
    }

    TargetDirectory_String.shrink_to_fit();


    this->ReturnCondition = 0;

    if(TargetDirectory_String != CurrentDirectory_String){

       this->ReturnCondition = SetCurrentDirectory(path);
    }

    return this->ReturnCondition;
};



int DirectoryOperations::ChangeDirectory(char * path){


    this->DetermineCurrentDirectory();

    char * CurrentDirectory = this->GetCurrentlyWorkingDirectory();


    std::string CurrentDirectory_String;

    std::string TargetDirectory_String;

    int CurrentDirectory_Size = strlen(CurrentDirectory);

    for(int i=0;i<CurrentDirectory_Size;i++){

        CurrentDirectory_String.push_back(CurrentDirectory[i]);
    }

    CurrentDirectory_String.shrink_to_fit();

    int TargetDirectory_Size = strlen(path);

    for(int i=0;i<TargetDirectory_Size;i++){

       TargetDirectory_String.push_back(path[i]);
    }

    TargetDirectory_String.shrink_to_fit();


    this->ReturnCondition = 0;

    if(TargetDirectory_String != CurrentDirectory_String){

       this->ReturnCondition = SetCurrentDirectory(path);
    }

    return this->ReturnCondition;
};


int DirectoryOperations::ChangeDirectory(std::string path){

    return this->ChangeDirectory(path.c_str());
};


int DirectoryOperations::RemoveDirectory(char * path){

    std::string std_path;

    size_t path_size = strlen(path);

    for(size_t i=0;i<path_size;i++){

        std_path.push_back(path[i]);
    }

    std_path.shrink_to_fit();

    this->Delete_Directory(std_path); // Quick Delete function is used 

    // Remove_Recursively_Directory_WINAPI member function can be also used.

    // But, it leads significant performance degradetion

    return this->ReturnCondition;
};

int DirectoryOperations::GoToUpperDirectory(){

    this->DetermineUpperDirectoryName();

    this->ReturnCondition = this->ChangeDirectory(this->GetUpperDirectoryName());

    return this->ReturnCondition;
};

int DirectoryOperations::GoToSubDirectory(char * DirectoryName){

     this->DetermineSubDirectoryName(DirectoryName);

     this->ReturnCondition = this->ChangeDirectory(this->GetSubDirectoryName());

     return this->ReturnCondition;
};

void DirectoryOperations::LoadSystemFunctionCommand(char * Command,char * DirectoryName){

     this->Clear_Pointer_Memory(&this->SystemCommand);

     int command_name_size   = strlen(Command);

     int Directory_Name_Size = strlen(DirectoryName);

     int System_Command_Name_Size = Directory_Name_Size + command_name_size;

     this->Memory_Delete_Condition = false;

     this->SystemCommand = new char [10*System_Command_Name_Size];

     int index_counter = 0;

     this->Place_Information(&this->SystemCommand,Command,&index_counter);

     this->Place_Information(&this->SystemCommand,DirectoryName,&index_counter);

     this->SystemCommand[index_counter] = '\0';
}

void DirectoryOperations::RecordCurrentDirectoryPATH(){

     this->Clear_Pointer_Memory(&this->RecordDirectoryPATH);

     this->DetermineCurrentDirectory();

     int Name_Size = strlen(this->GetCurrentlyWorkingDirectory());

     this->Memory_Delete_Condition = false;

     this->RecordDirectoryPATH = new char [5*Name_Size];

     this->Place_String(&this->RecordDirectoryPATH,this->GetCurrentlyWorkingDirectory(),Name_Size);
}

void DirectoryOperations::ReturnRecordedDirectoryPATH(){

     int return_condition = this->ChangeDirectory(this->GetRecordedDirectoryPATH());

     if(return_condition == -1){

        std::cout << "\n The directory can not be change ..";
     }
}

void DirectoryOperations::Determine_File_List_In_Directory_WINAPI(std::string Directory_Path, 

     std::vector<Directory_Data> & data){


     Directory_Data Temp_Dir_Data;

     std::string dir_path_std;

     size_t dir_path_size = Directory_Path.length();

     for(size_t i=0;i<dir_path_size;i++){

         dir_path_std.push_back(Directory_Path[i]);
     }

     dir_path_std.shrink_to_fit();


     Temp_Dir_Data.directory_path = dir_path_std;








     // Conversion from char data type to TCHAR

     size_t dir_name_length = Directory_Path.length();

     TCHAR dir_path[MAX_PATH];

     int index = 0;

     for(size_t k=0;k<dir_name_length;k++){

        dir_path[index] = Directory_Path[k];

        index++;
     }

     dir_path[index] = '\\';

     index++;

     dir_path[index] = '*';

     index++;

     size_t next_start = index;

     for(size_t k=next_start;k<MAX_PATH;k++){

         dir_path[index] = '\0';

         index++;
     }



     // Construction of winapi data structures for file search

     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;


     hFind = FindFirstFile(dir_path, &ffd);

     if (INVALID_HANDLE_VALUE == hFind)
     {
         std::cout << "\n Error in DirectoryOperations::Determine_File_List_In_Directory";
     }


     // List all the files in the directory with some info about them.

     do{
          if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
          {
                 
          }
          else{

                char * File_Name = ffd.cFileName;

                size_t file_name_size = strlen(File_Name);

                std::string file_name;

                for(size_t i=0;i<file_name_size;i++){

                    file_name.push_back(File_Name[i]) ;
                }           


                std::string filePath;

                this->Extract_Path(Directory_Path,File_Name,filePath);

                Temp_Dir_Data.file_paths.push_back(filePath);

          }
      }
      while (FindNextFile(hFind, &ffd) != 0);

      FindClose(hFind); 



      if(Temp_Dir_Data.sub_directory_paths.size()>0){

         Temp_Dir_Data.sub_dir_search_complation_status = false;
      }
      else{

         Temp_Dir_Data.sub_dir_search_complation_status = true;
      }

      data.push_back(Temp_Dir_Data);

      this->Clear_String_Vector(Temp_Dir_Data.file_paths);

      this->Clear_String_Vector(Temp_Dir_Data.sub_directory_paths);

}





void DirectoryOperations::Determine_File_List_In_Directory_WINAPI(std::string Directory_Path, 

     std::vector<std::string> & filePaths){


     // Conversion from char data type to TCHAR

     size_t dir_name_length = Directory_Path.length();

     TCHAR dir_path[MAX_PATH];

     int index = 0;

     for(size_t k=0;k<dir_name_length;k++){

        dir_path[index] = Directory_Path[k];

        index++;
     }

     dir_path[index] = '\\';

     index++;

     dir_path[index] = '*';

     index++;

     size_t next_start = index;

     for(size_t k=next_start;k<MAX_PATH;k++){

         dir_path[index] = '\0';

         index++;
     }



     // Construction of winapi data structures for file search

     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;


     hFind = FindFirstFile(dir_path, &ffd);

     if (INVALID_HANDLE_VALUE == hFind)
     {
         std::cout << "\n Error in DirectoryOperations::Determine_File_List_In_Directory";
     }


     // List all the files in the directory with some info about them.

     do{
          if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
          {
              // Sub-directory determination
                           
          }
          else{

                char * File_Name = ffd.cFileName;

                size_t file_name_size = strlen(File_Name);

                std::string file_name;

                for(size_t i=0;i<file_name_size;i++){

                    file_name.push_back(File_Name[i]) ;
                }           


                std::string filePath;

                this->Extract_Path(Directory_Path,File_Name,filePath);

                filePaths.push_back(filePath);
          }
      }
      while (FindNextFile(hFind, &ffd) != 0);

      FindClose(hFind); 

      filePaths.shrink_to_fit();
}









bool DirectoryOperations::Is_There_Subdirectory(std::string Directory_Path, std::string & subDirPath){
     
     subDirPath.clear();

     subDirPath.shrink_to_fit();

     bool is_exist = false;

     // Conversion from char data type to TCHAR

     size_t dir_name_length = Directory_Path.length();

     TCHAR dir_path[MAX_PATH];

     int index = 0;

     for(size_t k=0;k<dir_name_length;k++){

        dir_path[index] = Directory_Path[k];

        index++;
     }

     dir_path[index] = '\\';

     index++;

     dir_path[index] = '*';

     index++;

     size_t next_start = index;

     for(size_t k=next_start;k<MAX_PATH;k++){

         dir_path[index] = '\0';

         index++;
     }

     //std::cout << "\n Inside DirectoryOperations::Is_There_Subdirectory";

     //std::cout << "\n dir_path:" << dir_path;

     // Construction of winapi data structures for file search

     WIN32_FIND_DATA ffd;

     ffd.dwFileAttributes = FILE_ATTRIBUTE_DIRECTORY;

     HANDLE hFind = INVALID_HANDLE_VALUE;


     hFind = FindFirstFile(dir_path, &ffd);

     if (INVALID_HANDLE_VALUE == hFind)
     {
         std::cout << "\n Error: Invalid file handle on";
         std::cout << "\n DirectoryOperations::Is_There_Subdirectory";

         exit(EXIT_FAILURE);
     }
     else{

         do{
              if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
              {
                  // Sub-directory determination
           
                  char * dirName = ffd.cFileName;

                  
                  bool is_dir = true; 

                  if((strcmp(dirName, ".") == 0) || (strcmp(dirName, "..") == 0)){

                     is_dir = false;
                  }

                  if(is_dir){

                     this->Extract_Path(Directory_Path,dirName,subDirPath);

                     is_exist = true;

                     return is_exist;
                  }
              }
         
         }while(FindNextFile(hFind, &ffd) != 0);
     }
     
     FindClose(hFind); 

     return is_exist;
}


void DirectoryOperations::Determine_File_List_In_Directory(const char * dir_path){

     this->Clear_String_Vector(this->Path_List);

     DIR * d;

     struct dirent * dir;


     d = opendir(dir_path);

     if (d!=NULL){

          while ((dir = readdir(d)) != NULL)
          {

              bool is_element = true; 

              if((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)){

                  is_element = false;
              }
              

              if(is_element){

                 DIR *sub_d;


                 std::string path;

                 this->Extract_Path(dir_path,dir->d_name,path);


                 bool is_directory = false;

                 sub_d = opendir(path.c_str());

                 if( sub_d != NULL){

                    is_directory = true;

                    closedir(sub_d);
                 };

                 if(is_directory){

                    this->Determine_File_List_In_Directory(path.c_str());
                 }
                 else{

                    std::string str;

                    for(size_t i=0;i<path.length();i++){

                        str.push_back(path[i]);
                    }

                    this->Path_List.push_back(str);
                 }                 
              }
          }

          closedir(d);

          this->Path_List.shrink_to_fit();
     }
}


int DirectoryOperations::Remove_Directory_Recursively(const char * directory_path){

    int ret = 0;

    DIR *d;

    struct dirent * dir;

    d = opendir(directory_path);

    if (d!=NULL){

        while ((dir = readdir(d)) != NULL)
        {

          bool is_element = true; 

          if((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)){

              is_element = false;
          }

          if(is_element){

             std::string path;

             this->Extract_Path(directory_path,dir->d_name,path);

             DIR * sub_d;

             bool is_directory = false;

             sub_d = opendir(path.c_str());

             if(sub_d != NULL){

                is_directory = true;

                closedir(sub_d);
             };


             if(is_directory){ 
                    
                ret = this->Remove_Directory_Recursively(path.c_str());

                if(ret != 0){

                   return ret;
                }
             }     
             else{
   
                  unlink(path.c_str());
             }

           }
        }

        closedir(d);
     }

     ret = rmdir(directory_path);

     if(ret != 0){

        std::cerr << "\n The directory can not be removed";

        ret = -1;
     }

     return ret;
}



void DirectoryOperations::Extract_Path(const char * up_dir, char * name, std::string & path){

     size_t up_dir_size = strlen(up_dir);

     size_t name_size = strlen(name);

     for(size_t i=0;i<up_dir_size;i++){

         path.push_back(up_dir[i]);         
     }

     if(path.back()!= '\\'){

        path.push_back('\\');
     }

     for(size_t i=0;i<name_size;i++){

         path.push_back(name[i]);         
     }

     path.shrink_to_fit();     
}


void DirectoryOperations::Extract_Path(std::string up_dir, char * name, std::string & path){

     size_t up_dir_size = up_dir.length();

     size_t name_size = strlen(name);

     for(size_t i=0;i<up_dir_size;i++){

         path.push_back(up_dir[i]);         
     }

     if(path.back()!= '\\'){

        path.push_back('\\');
     }

     for(size_t i=0;i<name_size;i++){

         path.push_back(name[i]);         
     }

     path.shrink_to_fit();     
}

bool DirectoryOperations::Search_File_in_Directory(char * Director_Name, char * File_Name){

     this->Determine_File_List_In_Directory(Director_Name);

     size_t file_name_size = strlen(File_Name);

     std::string File_Name_String = "";

     for(size_t i=0;i<file_name_size;i++){

         File_Name_String.append(1,File_Name[i]);
     }

     File_Name_String.append(1,'\0');

     this->File_Exist_Condition = false;

     int File_Number = this->Get_File_Number_In_Directory();

     for(int i=0;i<File_Number;i++){

         if(File_Name_String == this->Get_File_List_In_Directory()[i]){

            this->File_Exist_Condition = true;

            break;
         }
     }

     return this->File_Exist_Condition;
}


void DirectoryOperations::Remove_Directory_Recursively_WINAPI(std::string Root_Dir_Path){

     std::string nextDir  = Root_Dir_Path;

     std::string firstDir = Root_Dir_Path;

     std::string subDir;

     bool root_subdir_status = this->Is_There_Subdirectory(firstDir,subDir);

     nextDir = subDir;

     while(root_subdir_status){

           bool next_sub_dir_status = false;

           do{
                next_sub_dir_status = this->Is_There_Subdirectory(subDir,nextDir);

                if(next_sub_dir_status){

                   subDir = nextDir;
                }
           }
           while(next_sub_dir_status);


           std::vector<std::string> file_paths;

           this->Determine_File_List_In_Directory_WINAPI(subDir,file_paths);

           for(size_t i=0;i<file_paths.size();i++){

               this->Delete_File(file_paths.at(i));
           }

           this->Delete_Directory(subDir);

           this->Clear_String_Vector(file_paths);

           root_subdir_status = this->Is_There_Subdirectory(firstDir,subDir);

     }

     this->Delete_Directory(Root_Dir_Path);
}


void DirectoryOperations::Delete_Directory(std::string path){

     size_t path_length = path.length();

     TCHAR  Tpath[5*path_length];


     for(size_t i=0;i<5*path_length;i++){

         Tpath[i] = '\0';
     }


     for(size_t i=0;i<path_length;i++){

         Tpath[i] = path[i];
     }

     Tpath[path_length] = '\0';

     Tpath[path_length+1] = '\0';

     SHFILEOPSTRUCT fileop;

     fileop.wFunc = FO_DELETE;

     fileop.pFrom = Tpath;

     fileop.pTo = NULL;

     fileop.hwnd = NULL;

     fileop.fFlags =  FOF_NOCONFIRMATION | FOF_NO_UI;

     this->ReturnCondition = SHFileOperationA(&fileop);

     if(this->ReturnCondition != 0) {

        std::cout << "\n The file can not be removed ..";
     }
}


void DirectoryOperations::Delete_File(std::string path){

     size_t path_length = path.length();

     TCHAR Tpath[5*path_length];

     for(size_t i=0;i<5*path_length;i++){

         Tpath[i] = '\0';
     }

     for(size_t i=0;i<path_length;i++){

         Tpath[i] = path[i];
     }

     Tpath[path_length] = '\0';

     Tpath[path_length+1] = '\0';

     SHFILEOPSTRUCT fileop;

     fileop.wFunc = FO_DELETE;

     fileop.pFrom = Tpath;

     fileop.pTo = NULL;

     fileop.hwnd = NULL;

     fileop.fFlags = FOF_FILESONLY | FOF_NOCONFIRMATION;

     this->ReturnCondition = SHFileOperationA(&fileop);

     if(this->ReturnCondition != 0) {

        std::cout << "\n The file can not be removed ..";
     }
}

std::string * DirectoryOperations::Get_File_List_In_Directory(){

    return this->File_List;
}

int DirectoryOperations::Get_File_Number_In_Directory(){

   return this->File_Number;
}

void DirectoryOperations::Place_String(char ** Pointer, char * String, size_t String_Size){

     for(size_t i=0;i<String_Size;i++){

        (*Pointer)[i] = String[i];
     }

     (*Pointer)[String_Size] = '\0';
}

void DirectoryOperations::Place_Information(char ** Pointer, char * Information, 

     int * index_counter){

     int Information_Size = strlen(Information);

     for(int i=0;i<Information_Size;i++){

        (*Pointer)[(*index_counter)] = Information[i];

        (*index_counter)++;
     }
}

void DirectoryOperations::Place_Information(char ** Pointer, const char * Information, 

     int * index_counter){

     int Information_Size = strlen(Information);

     for(int i=0;i<Information_Size;i++){

        (*Pointer)[(*index_counter)] = Information[i];

        (*index_counter)++;
     }
}

char * DirectoryOperations::Convert_Std_String_To_CString(std::string st)
{
       this->Clear_Pointer_Memory(&this->c_str);

       size_t string_size = st.length();

       this->c_str = new char [5*string_size];

       for(size_t i=0;i<5*string_size;i++){
       
           this->c_str[i] = '\0';    
       }

       for(size_t i=0;i<string_size;i++){
       
           this->c_str[i] = st[i];
       }

       this->c_str[string_size] = '\0';

       return this->c_str;
}


void DirectoryOperations::Clear_String_Vector(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     if(!vec.empty()){
        
        for(size_t i=0;i<vec.size();i++){

            this->Clear_String_Memory(vec.at(i));
        }

        vec.clear();

        vec.shrink_to_fit();
     }
}


void DirectoryOperations::Clear_String_Memory(std::string & vec){

     vec.shrink_to_fit();

     if(!vec.empty()){

         vec.clear();

         vec.shrink_to_fit();
     }
}


char * DirectoryOperations::GetCurrentlyWorkingDirectory(){

       this->DetermineCurrentDirectory();

       return this->CurrentDirectory;
}

char * DirectoryOperations::GetRecordedDirectoryPATH(){

       return this->RecordDirectoryPATH;
}

char * DirectoryOperations::GetSystemFunctionCommand(){

       return this->SystemCommand;
}

char * DirectoryOperations::GetSubDirectoryName(){

       return this->Sub_Directory;
}

char * DirectoryOperations::GetUpperDirectoryName(){

       return this->Upper_Directory;
}
