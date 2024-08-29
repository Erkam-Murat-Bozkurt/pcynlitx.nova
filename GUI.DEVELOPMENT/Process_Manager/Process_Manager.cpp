
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

BEGIN_EVENT_TABLE(Process_Manager,wxFrame)
    EVT_BUTTON(ID_CLOSE_PROCESS_OUTPUT_WINDOW,Process_Manager::CloseWindow)
END_EVENT_TABLE()

Process_Manager::Process_Manager(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{
     this->error_stream_status = false;

     this->procCmd = nullptr;

     this->Memory_Delete_Condition = false;

     this->Frame_Ptr = parent;



     this->Default_Font = new wxFont(12,wxFONTFAMILY_MODERN ,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,"Calibri");

     this->SetFont(*(this->Default_Font));

     this->Memory_Delete_Condition = false;

     wxIcon Frame_Icon(wxT("C:\\Development.Files\\Project.Test.platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Process_Manager::OnSize,this,wxID_ANY);


     this->SetThemeEnabled(true);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);


     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();
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

     this->Clear_String_Memory(this->procCmd);

     std::string std_cmd = shell_command.ToStdString();

     size_t cmd_size = std_cmd.length();

     this->procCmd = new char [2*cmd_size];

     size_t index = 0;

     for(size_t i=0;i<cmd_size;i++){

         this->procCmd[index] = std_cmd.at(i);

         index++;
     }

     this->procCmd[index] = '\0';


     bool success_status =  this->SysInt.Create_Process_With_Redirected_Stdout(this->procCmd);

     if(!success_status){

        this->Print_Error_Stream(wxT("ERROR MESSAGE"));
     }
     else{

          this->Process_Exit_Status 
          
           = this->SysInt.Get_Anonymously_PipedProcess_ExitCode();
     }
}


void Process_Manager::Fork_Process_With_Std_Out_Redirection(char * cmd){

     bool success_status =  this->SysInt.Create_Process_With_Redirected_Stdout(cmd);

     this->read_process_output = new std::thread(Process_Manager::ReadStdOut,this);

     this->read_process_output->detach();

     if(!success_status){

        this->Print_Error_Stream(wxT("ERROR MESSAGE"));
     }
     else{

          this->Process_Exit_Status 
          
          = this->SysInt.Get_Anonymously_PipedProcess_ExitCode();
     }
}


void Process_Manager::Fork_Process_With_Named_Pipe_Connection(char * cmd){

     this->SysInt.CreateProcessWith_NamedPipe_From_Parent(cmd);

     this->read_named_pipe = new std::thread(Process_Manager::ReadFromNamedPipe,this);


     std::string process_cmd;

     size_t cmd_size = strlen(cmd);

     for(size_t i=0;i<cmd_size;i++){

         process_cmd.push_back(cmd[i]);
     }

     wxString pr_cmd(process_cmd);


     std::unique_lock<std::mutex> lck(this->mtx);

     this->cv.wait(lck);

     lck.unlock();

     this->read_named_pipe->join();

     this->SysInt.Close_Parent_Handles_For_Named_Pipe_Connection();
}

void Process_Manager::ReadStdOut(){

     this->SysInt.ReadFromPipe();

     this->std_out_put = this->SysInt.GetAnonymousPipe_String();
}


void Process_Manager::ReadFromNamedPipe(){

     do{

        if(this->SysInt.IsPipeReadytoRead()){

            break;
        }

     }while(!this->SysInt.IsPipeReadytoRead());


     for(;;)
     {
        std::string pipeStr = this->SysInt.ReadNamedPipe_From_Parent();

        this->named_pipe_str = this->named_pipe_str + pipeStr;

        this->named_pipe_str.shrink_to_fit();

        if(!this->SysInt.IsChildProcessStillAlive()){

            break;
        }
     } 


     this->cv.notify_all();

     this->is_pipe_open = false;

}


void Process_Manager::Construct_Text_Panel(wxString title, int dialog_size){

     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,-1));

     this->close_panel     = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,70));

     this->dialog_panel    = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,30));



     this->CloseButton     = new wxButton(this,ID_CLOSE_PROCESS_OUTPUT_WINDOW,wxT("CLOSE"),
     
                             wxDefaultPosition, wxSize(100, 50));


     this->textctrl = new wxTextCtrl(this->text_ctrl_panel,wxID_ANY, wxT(""), 
     
                      wxDefaultPosition, wxSize(900,550), wxTE_MULTILINE | wxTE_RICH);


     this->textctrl->SetVirtualSize(wxSize(1000,10000));

     this->textctrl->FitInside();


     this->dialog = new wxGauge(this->dialog_panel,wxID_ANY,dialog_size,
     
                    wxDefaultPosition,wxSize(900,30),wxGA_HORIZONTAL | wxGA_SMOOTH );



     this->dialog_box = new wxBoxSizer(wxHORIZONTAL);

     this->dialog_box->Add(this->dialog_panel,1,wxEXPAND | wxALL,5);
       
     this->dialog_box->Layout();





     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->text_ctrl_panel,1,wxEXPAND  | wxALL,5);

     this->ctrl_box->Layout();



     this->close_button_sizer = new wxBoxSizer(wxVERTICAL);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Add(this->CloseButton,0, wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxALL,15);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Layout();

     

     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1,    wxEXPAND | wxTOP    |  wxALL,5);

     this->frame_box->Add(this->dialog_box,0,    wxEXPAND | wxTOP    |  wxALL,5);

     this->frame_box->Add(this->close_button_sizer,0,   wxEXPAND | wxBOTTOM  | wxALL,5);

     this->frame_box->Layout();


     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);

     this->frame_box->Fit(this);



     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->SetTitle(title);

     this->Show(true);

     this->Update();

}



void Process_Manager::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}


void Process_Manager::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);
}


void Process_Manager::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}


void Process_Manager::CloseWindow(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_PROCESS_OUTPUT_WINDOW){

        this->Destroy();
     }
}


void Process_Manager::Print_Error_Stream(wxString title){

     this->SysInt.ReadFromPipe();

     std::string error_st = this->SysInt.GetAnonymousPipe_String();

     wxString std_err(error_st);

     this->Construct_Text_Panel(title,20);
}

void Process_Manager::Print_Output_Stream(wxString title){

     this->SysInt.ReadFromPipe();

     std::string out = this->SysInt.GetAnonymousPipe_String();
     
     wxString std_out(out);

     this->Construct_Text_Panel(title,20);
}


void Process_Manager::AppendText_To_TextCtrl(wxString text){

     this->textctrl->AppendText(text);

     this->textctrl->Update();
}


void Process_Manager::Receive_Descriptor_File_Path(wxString Path){

     this->Des_Path = Path;
}

void Process_Manager::Receive_Builder_Path(wxString Path){

     this->Builder_Path = Path;
}


void Process_Manager::Find_Source_File_Dependency_Determination_Command(wxString source_file_path){

     this->Clear_String_Memory(this->procCmd);

     char option [] = "-ex_dep_for_gui";

     char space = ' ';

     size_t kernel_str_size = this->Builder_Path.size();

     size_t option_size = strlen(option);

     size_t src_path_size = source_file_path.size();

     size_t des_path_size = this->Des_Path.size();

     size_t cmd_str_size = des_path_size + src_path_size + option_size

                         + kernel_str_size;

     size_t cmd_size = 2*cmd_str_size;

     this->procCmd = new char[cmd_size];


     for(size_t i=0;i<cmd_size;i++){

         this->procCmd[i] = '\0';
     }

     size_t index = 0;

     for(size_t i=0;i<kernel_str_size;i++){

         this->procCmd[index] = this->Builder_Path[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<des_path_size;i++){

         this->procCmd[index] = this->Des_Path[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;


     for(size_t i=0;i<option_size;i++){

         this->procCmd[index] = option[i];

         index++;
     }

     this->procCmd[index] = space;

     index++;

     for(size_t i=0;i<src_path_size;i++){

         this->procCmd[index] = source_file_path[i];

         index++;
     }

     this->procCmd[index] = '\0';
}


void Process_Manager::Exec_Cmd_For_Single_Src_File(std::string src_path, std::string exe_file_name, char strategy){

     char option [] = " -if_for_gui";

     char space = ' ';

     size_t builder_path_size  = this->Builder_Path.size();

     size_t des_path_size = strlen(this->Des_Path.c_str()); 

     size_t option_size   = strlen(option);

     size_t src_path_size = src_path.length();

     size_t name_size     = exe_file_name.length();

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

     this->procCmd[index] = space;

     index++;

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

     index++;

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


std::string Process_Manager::Get_Std_Out(){

     return this->std_out_put;
}


std::string Process_Manager::GetNamedPipeString(){

    return this->named_pipe_str;
}


wxGauge * Process_Manager::GetDialogAddress(){

      return this->dialog;
}


wxTextCtrl * Process_Manager::GetTextControl(){

      return this->textctrl;
}