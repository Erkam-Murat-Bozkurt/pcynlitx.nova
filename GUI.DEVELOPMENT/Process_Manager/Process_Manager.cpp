
/*

Copyright ©  2021,  Erkam Murat Bozkurt

This file is part of the research project which is carried by Erkam Murat Bozkurt.

This is a free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation
either version 3 of the License, or any later version.

This software is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program. If not, see <http://www.gnu.org/licenses/>.

*/

#include "Process_Manager.hpp"

Process_Manager::Process_Manager(wxFrame * Frame, int ID) : wxProcess(Frame,ID)
{
     this->error_stream_status = false;

     this->Frame_Ptr = Frame;

     this->procCmd = nullptr;

     this->Memory_Delete_Condition = false;
}

Process_Manager::~Process_Manager(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_String_Memory(this->procCmd);
    }
}


void Process_Manager::Clear_String_Memory(char * ptr){

     if(ptr != nullptr){

        delete [] ptr;

        ptr = nullptr;
     }
}

void Process_Manager::Fork_Process(wxString shell_command){

     this->Process_Exit_Status = 0;

     this->Redirect();

     this->Process_Exit_Status = wxExecute(shell_command,wxEXEC_ASYNC

       | wxEXEC_MAKE_GROUP_LEADER ,this);

     if(this->Process_Exit_Status == 0){

        this->Print_Error_Stream();
     }
}

void Process_Manager::Print_Text(wxString std_out, wxString title){

     wxDialog * Succes_Dialog = new wxDialog(this->Frame_Ptr,

                             -1,title,wxDefaultPosition,wxSize(950,650));

     Succes_Dialog->Centre(wxBOTH);


     wxTextCtrl * Succes_Text = new wxTextCtrl(Succes_Dialog,wxID_ANY,std_out,

                wxDefaultPosition,wxSize(950,650), wxTE_MULTILINE | wxTE_LEFT);

     Succes_Text->Centre(wxBOTH);

     Succes_Dialog->ShowWindowModal();

     delete Succes_Text;
}

void Process_Manager::Print_Error_Stream(){

     this->error_stream_status = true;

     wxInputStream * Error_Stream =  this->GetErrorStream();

     wxTextInputStream tStream(*Error_Stream);

     wxString log_string = wxT("");

     while(!Error_Stream->Eof())
     {
        log_string = log_string + tStream.ReadLine() + wxT("\n");
     }

     if(log_string != wxT("")){

        wxRichMessageDialog * dial = new wxRichMessageDialog(this->Frame_Ptr,

        log_string, wxT("Error in construction"), wxOK|wxCENTRE);

        dial->ShowModal();

        return;
     }
}

void Process_Manager::Print_Output_Stream(wxString title){

     wxInputStream * stream = this->GetInputStream();

     wxChar buffer = '\0';

     wxString std_out = "";

     if(stream->CanRead()){

        do{

            stream->Read(&buffer,1);

            std_out.Append(buffer,1);

        }while(!stream->Eof());

        this->Print_Text(std_out,title);
     }

     this->CloseOutput();
}



void Process_Manager::Receive_Descriptor_File_Path(wxString Path){

     this->Des_Path = Path;
}

void Process_Manager::Receive_Builder_Path(wxString Path){

     this->Builder_Path = Path;
}

void Process_Manager::Exec_Cmd_For_Single_Src_File(char * src_path, char * exe_file_name, char strategy){

     char option [] = " -if_for_gui";

     char space = ' ';

     size_t builder_path_size  = this->Builder_Path.size();

     size_t des_path_size = strlen(this->Des_Path.c_str()); 

     size_t option_size   = strlen(option);

     size_t src_path_size = strlen(src_path);

     size_t name_size     = strlen(exe_file_name);

     size_t cmd_str_size  = builder_path_size + des_path_size 
     
                          + option_size + src_path_size + name_size;


     // Command initialization

     this->Clear_String_Memory(this->procCmd);

     size_t cmd_size = 2*cmd_str_size;

     this->procCmd = new char[cmd_size];

     for(size_t i=0;i<cmd_size;i++){

         this->procCmd[i] = '\0';
     }


     // Command construction

     size_t index = 0;

     for(size_t i=0;i<builder_path_size;i++){

         this->procCmd[index] = this->Builder_Path[i];

         index++;
     }

     for(size_t i=0;i<des_path_size;i++){

         this->procCmd[index] = this->Des_Path.c_str()[i];

         index++;
     }

     for(size_t i=0;i<option_size;i++){

         this->procCmd[index] = option[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<src_path_size;i++){

         this->procCmd[index] = src_path[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<name_size;i++){

         this->procCmd[index] = exe_file_name[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     this->procCmd[index] = strategy;

     this->procCmd[index] = '\0';
}



void Process_Manager::Determine_Build_System_Initialization_Command(){

     char option [] = "-ip_for_gui";

     char space = ' ';

     size_t builder_path_size  = this->Builder_Path.size();

     size_t des_path_size = strlen(this->Des_Path.c_str()); 

     size_t option_size   = strlen(option);

     size_t cmd_str_size = builder_path_size + des_path_size + option_size;

     size_t cmd_size = 2*cmd_str_size;

     // Command Initialization

     this->Clear_String_Memory(this->procCmd);

     this->procCmd= new char[cmd_size];

     for(size_t i=0;i<cmd_size;i++){

         this->procCmd[i] = '\0';
     }



     size_t index = 0;

     for(size_t i=0;i<builder_path_size;i++){

         this->procCmd[index] = this->Builder_Path[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<des_path_size;i++){

         this->procCmd[index] = this->Des_Path.c_str()[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<option_size;i++){

         this->procCmd[index] = option[i];

         index++;
     }

     this->procCmd[index] = '\0';
}



int Process_Manager::Get_Process_Exit_Status(){

     return this->Process_Exit_Status;
}


char * Process_Manager::Get_Process_Command(){

     return this->procCmd;
}