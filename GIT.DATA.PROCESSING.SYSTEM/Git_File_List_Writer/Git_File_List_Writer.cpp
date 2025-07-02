
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



#include "Git_File_List_Writer.hpp"



Git_File_List_Writer::Git_File_List_Writer(char opr_sis) : FileManager(opr_sis)
{
    this->opr_sis = opr_sis;

    this->Initialize_Mermbers();
}


Git_File_List_Writer::~Git_File_List_Writer(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_File_List_Writer::Initialize_Mermbers(){

     this->Memory_Delete_Condition = false;

     this->CString = nullptr;
}


void Git_File_List_Writer::Receive_Descriptor_File_Reader(Descriptor_File_Reader * ptr){

     this->Des_Reader = ptr;
}

void Git_File_List_Writer::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(&this->Warehouse);

         this->Clear_String_Memory(&this->Repo_Dir);

         this->Clear_String_Memory(&this->git_file_list_path);

         this->Clear_String_Memory(&this->git_listing_command);

         this->FileManager.Clear_Dynamic_Memory();

         this->DirectoryManager.Clear_Dynamic_Memory();

         if(this->CString != nullptr){

             delete [] this->CString;

             this->CString = nullptr;
         }
     }
}


void Git_File_List_Writer::Write_Git_Repo_List_File()
{
     this->Memory_Delete_Condition = false;

     this->Warehouse = this->Des_Reader->Get_Warehouse_Location();

     this->Repo_Dir  = this->Des_Reader->Get_Repo_Directory_Location();

     this->Determine_Error_Check_File_Path();

     this->Determine_Git_File_List_Path();

     this->Determine_Git_Listing_Command();
     
     this->List_Files_in_Repo();

     this->Control_Std_Error_Status();

}


void Git_File_List_Writer::Determine_Error_Check_File_Path(){
     
     std::string error_text = "std_error.txt";

     std::string wrd_dir = this->Des_Reader->Get_Warehouse_Location();

     size_t wrd_dir_size = wrd_dir.length();

     for(size_t i=0;i<wrd_dir_size;i++){

         this->std_error_file_path.push_back(wrd_dir[i]);
     }

     if(this->opr_sis == 'w'){

        this->std_error_file_path.push_back('\\');
     }

     if(this->opr_sis == 'l'){

        this->std_error_file_path.push_back('/');
     }

     size_t error_text_size = error_text.length();

     for(size_t i=0;i<error_text_size;i++){

         this->std_error_file_path.push_back(error_text[i]);
     }

     this->std_error_file_path.shrink_to_fit();
}


void Git_File_List_Writer::Determine_Git_File_List_Path()
{
     char repo_list_file_name [] = "repo_files.txt";

     size_t file_name_size = strlen(repo_list_file_name);

     size_t warehouse_path_size = this->Warehouse.length();


     for(size_t i=0;i<warehouse_path_size;i++){

         this->git_file_list_path.push_back(this->Warehouse[i]) ;
     }

     if(this->Warehouse[warehouse_path_size-1] != '\\'){

        this->git_file_list_path.push_back('\\') ;
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_file_list_path.push_back(repo_list_file_name[i]) ;
     }
}


void Git_File_List_Writer::Determine_Git_Listing_Command()
{
     std::string git_command = "cmd /c git ls-files > ";

     std::string std_error_re_director = " 2> ";

     size_t git_command_size = git_command.length();

     size_t file_path_size = this->git_file_list_path.length();

     for(size_t i=0;i<git_command_size;i++)
     {
         this->git_listing_command.push_back(git_command[i]) ;
     }

     for(size_t i=0;i<file_path_size;i++)
     {
         this->git_listing_command.push_back(this->git_file_list_path[i]);
     }

     size_t error_redirector_size = std_error_re_director.length();

     for(size_t i=0;i<error_redirector_size;i++)
     {
         this->git_listing_command.push_back(std_error_re_director[i]);
     }
     
     size_t std_error_file_size = this->std_error_file_path.length();

     for(size_t i=0;i<std_error_file_size;i++){

         this->git_listing_command.push_back(this->std_error_file_path[i]);
     }

     this->git_listing_command.shrink_to_fit();

  
     git_command.clear();
     git_command.shrink_to_fit();
}



void Git_File_List_Writer::List_Files_in_Repo()
{
     if(this->FileManager.Is_Path_Exist(this->git_file_list_path)){

        this->FileManager.Delete_File(this->git_file_list_path.c_str());
     }

     this->Determine_Current_Directory();

     if(this->Repo_Dir != this->CurrentDir){

        int dir_chg_cond = this->DirectoryManager.ChangeDirectory(this->Repo_Dir.c_str());

        if(dir_chg_cond == 0){

           std::cerr << "\n";
           std::cerr << "\nERROR IN CONSTRUCTION:";
           std::cerr << "\nGit repo directory is not exist";
           std::cerr << "\nPlease check your declerations about project directory";
           std::cerr << "\n";
           std::cerr << "\n";

           exit(EXIT_FAILURE);
        }
        else{

            this->Clear_CString_Buffer();

            char * system_cmd = this->From_Std_String_To_Char(this->git_listing_command);

            this->Execute_System_Call(system_cmd);
        } 
     }
     else{

            this->Clear_CString_Buffer();

            char * system_cmd = this->From_Std_String_To_Char(this->git_listing_command);

            this->Execute_System_Call(system_cmd);
     }     
}


void Git_File_List_Writer::Determine_Current_Directory(){

     this->Clear_String_Memory(&this->CurrentDir);

     char * current_dir = this->DirectoryManager.GetCurrentlyWorkingDirectory();

     size_t dir_size = strlen(current_dir);

     for(size_t i=0;i<dir_size;i++){

          this->CurrentDir.push_back(current_dir[i]);
     }

     this->CurrentDir.shrink_to_fit();
}



 void Git_File_List_Writer::Control_Std_Error_Status(){

      if(this->FileManager.Is_Path_Exist(this->std_error_file_path)){
     
         if(!this->FileManager.Is_This_File_Empty(this->std_error_file_path)){

            std::cout << "\nERROR IN CODE READING:";

            std::cout << "\n";

            std::cout << "\nThe git can not find information about repository!";
          
            std::cout << "\nPlease check the declerations about project repository";

            std::cout << "\nThe current project repository path specified on the decleration:";

            std::cout << "\nRepo path:" << this->Repo_Dir;

            std::cout << "\n";

            std::cout << "\nGit gives the following error:";

            std::cout << "\n";

            this->FileManager.Read_File(this->std_error_file_path);


            this->FileManager.Printf();


            this->FileManager.Delete_File(this->std_error_file_path.c_str());

            exit(EXIT_FAILURE);
         }
         else{

              this->FileManager.Delete_File(this->std_error_file_path.c_str());
         }
      }
 }


void Git_File_List_Writer::Execute_System_Call(char * cmd){

     STARTUPINFO si;
     PROCESS_INFORMATION pi;

     ZeroMemory( &si, sizeof(si) );
     si.cb = sizeof(si);
     ZeroMemory( &pi, sizeof(pi) );

     // Start the child process.
     if( !CreateProcess( NULL,   // No module name (use command line)
          cmd,        // Command line
          NULL,           // Process handle not inheritable
          NULL,           // Thread handle not inheritable
          FALSE,          // Set handle inheritance to FALSE
          0,              // No creation flags
          NULL,           // Use parent's environment block
          NULL,           // Use parent's starting directory
          &si,            // Pointer to STARTUPINFO structure
          &pi )           // Pointer to PROCESS_INFORMATION structure
       )
     {
          printf( "CreateProcess failed (%d).\n", GetLastError() );
          exit(EXIT_FAILURE);
     }

     // Wait until child process exits.
     WaitForSingleObject( pi.hProcess, INFINITE );

     // Close process and thread handles.
     CloseHandle( pi.hProcess );
     CloseHandle( pi.hThread );
}




char * Git_File_List_Writer::From_Std_String_To_Char(std::string str){

       this->Clear_CString_Buffer();

       size_t size = str.length();

       int index = 0;

       this->CString = new char [5*size];

       for(size_t i=0;i<5*size;i++){

           this->CString[i] = '\0';
       }

       for(size_t i=0;i<size;i++){

           this->CString[index] = str[i];

           index++;
       }

       this->CString[index] = '\0';

       return this->CString;
}


void Git_File_List_Writer::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}


void Git_File_List_Writer::Clear_CString_Buffer(){

     if(this->CString != nullptr){

        delete [] this->CString;

        this->CString = nullptr;
     }
}
