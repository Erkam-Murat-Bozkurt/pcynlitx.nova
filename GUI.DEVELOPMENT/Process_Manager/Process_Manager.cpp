
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
}

Process_Manager::~Process_Manager(){

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

     wxInputStream * Error_Stream =  this->GetErrorStream( );

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

int Process_Manager::Get_Process_Exit_Status(){

     return this->Process_Exit_Status;
}
