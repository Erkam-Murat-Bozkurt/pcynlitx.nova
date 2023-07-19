




#include "Git_Ignoring_Files_Lister.hpp"


Git_Ignoring_Files_Lister::Git_Ignoring_Files_Lister(char * DesPath, char opr_sis) :

    Des_Reader(DesPath)
{

    this->opr_sis = opr_sis;

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
}



Git_Ignoring_Files_Lister::Git_Ignoring_Files_Lister(std::string DesPath, char opr_sis) :

    Des_Reader(DesPath)
{
    this->opr_sis = opr_sis;

    this->Initialize_Mermbers();

    this->Des_Reader.Read_Descriptor_File();

    this->Warehouse = this->Des_Reader.Get_Warehouse_Location();

    this->Repo_Dir  = this->Des_Reader.Get_Repo_Directory_Location();

    this->Des_Reader.Clear_Dynamic_Memory();
}


Git_Ignoring_Files_Lister::~Git_Ignoring_Files_Lister(){

   if(!this->Memory_Delete_Condition){

       this->Clear_Dynamic_Memory();
   }
}


void Git_Ignoring_Files_Lister::Initialize_Mermbers(){

     this->Memory_Delete_Condition = false;

     this->CString = nullptr;
}


void Git_Ignoring_Files_Lister::Clear_Dynamic_Memory()
{
     if(!this->Memory_Delete_Condition){

         this->Memory_Delete_Condition = true;

         this->Clear_String_Memory(&this->Warehouse);

         this->Clear_String_Memory(&this->Repo_Dir);

         this->Clear_String_Memory(&this->git_ignoring_files_list_path);

         this->Clear_String_Memory(&this->command_for_make);

         this->Clear_String_Memory(&this->command_for_ps);

         this->FileManager.Clear_Dynamic_Memory();

         this->DirectoryManager.Clear_Dynamic_Memory();

         if(this->CString != nullptr){

             delete [] this->CString;

             this->CString = nullptr;
         }
     }
}


void Git_Ignoring_Files_Lister::Write_Ignoring_File_List()
{
     this->Memory_Delete_Condition = false;

     this->Determine_Git_Ignoring_Files_List_Path();

     this->Determine_Git_Ignoring_Files_Lister_Command();

     this->Execute_Listing_Command();

     std::cout << "\nThe Files having \".make\" and \".ps1\" extention will be ignored by Git";
     std::cout << "\n\n";
}


void Git_Ignoring_Files_Lister::Determine_Git_Ignoring_Files_List_Path()
{
     std::string ignoring_files_list_location;

     if(this->opr_sis == 'w'){

        ignoring_files_list_location = ".git\\info\\exclude";
     }

     if(this->opr_sis == 'l'){

        ignoring_files_list_location = ".git/info/exclude";
     }

     size_t file_name_size = ignoring_files_list_location.length();

     size_t repo_path_size = this->Repo_Dir.length();


     for(size_t i=0;i<repo_path_size;i++){

         this->git_ignoring_files_list_path.push_back(this->Repo_Dir[i]) ;
     }

     if(this->Warehouse[repo_path_size-1] != '\\'){

        this->git_ignoring_files_list_path.push_back('\\') ;
     }

     for(size_t i=0;i<file_name_size;i++){

        this->git_ignoring_files_list_path.push_back(ignoring_files_list_location[i]) ;
     }
}


void Git_Ignoring_Files_Lister::Determine_Git_Ignoring_Files_Lister_Command()
{
     std::string git_command = "cmd /c powershell.exe Add-Content -Path ";
     std::string type_make = " -Value \"*.make\"";
     std::string type_ps = " -Value \"*.ps1\"";


     size_t git_command_size = git_command.length();

     size_t type_make_size = type_make.length();

     size_t type_ps_size = type_ps.length();


     size_t file_path_size = this->git_ignoring_files_list_path.length();

     for(size_t i=0;i<git_command_size;i++)
     {
         this->command_for_make.push_back(git_command[i]) ;
     }

     for(size_t i=0;i<file_path_size;i++)
     {
         this->command_for_make.push_back(this->git_ignoring_files_list_path[i]);
     }

     for(size_t i=0;i<type_make_size;i++){

         this->command_for_make.push_back(type_make[i]);
     }

     for(size_t i=0;i<git_command_size;i++)
     {
         this->command_for_ps.push_back(git_command[i]) ;
     }

     for(size_t i=0;i<file_path_size;i++)
     {
         this->command_for_ps.push_back(this->git_ignoring_files_list_path[i]);
     }

     for(size_t i=0;i<type_ps_size;i++){

         this->command_for_ps.push_back(type_ps[i]);
     }


     git_command.clear();
     git_command.shrink_to_fit();
}



void Git_Ignoring_Files_Lister::Execute_Listing_Command()
{
     this->DirectoryManager.ChangeDirectory(this->Repo_Dir.c_str());

     this->Clear_CString_Buffer();

     char * system_cmd = this->From_Std_String_To_Char(this->command_for_make);

     this->Execute_System_Call(system_cmd);

     this->Clear_CString_Buffer();

     system_cmd = this->From_Std_String_To_Char(this->command_for_ps);

     this->Execute_System_Call(system_cmd);

     this->Clear_CString_Buffer();
}




void Git_Ignoring_Files_Lister::Execute_System_Call(char * cmd){

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


char * Git_Ignoring_Files_Lister::From_Std_String_To_Char(std::string str){

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


void Git_Ignoring_Files_Lister::Clear_String_Memory(std::string * pointer){

     if(!pointer->empty()){

         pointer->clear();

         pointer->shrink_to_fit();
     }
}


void Git_Ignoring_Files_Lister::Clear_CString_Buffer(){

     if(this->CString != nullptr){

        delete [] this->CString;

        this->CString = nullptr;
     }
}
