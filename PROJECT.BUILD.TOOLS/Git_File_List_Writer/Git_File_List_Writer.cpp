



#include "Git_File_List_Writer.hpp"


Git_File_List_Writer::Git_File_List_Writer(char * DesPath) :

    Des_Reader(DesPath)
{

    this->Initialize_Mermbers();

    this->Des_Reader.Read_Descriptor_File();

    std::string str_wr = this->Des_Reader.Get_Warehouse_Location();

    for(size_t i=0;i<str_wr.length();i++){

        this->Warehouse.push_back(str_wr[i]);
    }

    std::string str_dr = this->Des_Reader.Get_Repo_Directory_Location();

    for(size_t i=0;i<str_dr.length();i++){

        this->Repo_Dir.push_back(str_dr[i]);
    }

    this->Des_Reader.Clear_Dynamic_Memory();

    this->Write_Git_Repo_List_File();
}



Git_File_List_Writer::Git_File_List_Writer(std::string DesPath) :

    Des_Reader(DesPath)
{
    this->Initialize_Mermbers();

    this->Des_Reader.Read_Descriptor_File();

    this->Warehouse = this->Des_Reader.Get_Warehouse_Location();

    this->Repo_Dir  = this->Des_Reader.Get_Repo_Directory_Location();

    this->Des_Reader.Clear_Dynamic_Memory();
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

     this->Determine_Git_File_List_Path();

     this->Determine_Git_Listing_Command();

     this->List_Files_in_Repo();
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

     this->git_listing_command.push_back('\"');

     git_command.clear();
     git_command.shrink_to_fit();
}



void Git_File_List_Writer::List_Files_in_Repo()
{
     if(this->FileManager.Is_Path_Exist(this->git_file_list_path)){

        this->FileManager.Delete_File(this->git_file_list_path.c_str());
     }

     this->DirectoryManager.ChangeDirectory(this->Repo_Dir.c_str());

     this->Clear_CString_Buffer();

     char * system_cmd = this->From_Std_String_To_Char(this->git_listing_command);

     this->Execute_System_Call(system_cmd);
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
