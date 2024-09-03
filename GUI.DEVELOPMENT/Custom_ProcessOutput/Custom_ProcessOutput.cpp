
#include "Custom_ProcessOutput.hpp"


BEGIN_EVENT_TABLE(Custom_ProcessOutput,wxFrame)
    EVT_BUTTON(ID_CLOSE_WINDOW,Custom_ProcessOutput::CloseWindow)
END_EVENT_TABLE()

Custom_ProcessOutput::Custom_ProcessOutput(wxFrame *parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{

     this->log_num =0;

     this->Default_Font = new wxFont(12,wxFONTFAMILY_MODERN ,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,"Calibri");

     this->SetFont(*(this->Default_Font));

     this->Memory_Delete_Condition = false;

     this->dir_list_show_cnd = false;

     wxIcon Frame_Icon(wxT("C:\\Development.Files\\Project.Test.platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Custom_ProcessOutput::OnSize,this,wxID_ANY);

     this->GetEventHandler()->Bind(wxEVT_CLOSE_WINDOW,&Custom_ProcessOutput::OnClose,this,wxID_ANY);


     this->SetThemeEnabled(true);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);


     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();


     this->SetAutoLayout(true);

     this->ClearBackground();

     this->PaintNow(this);

     this->Show(true);

     this->window_open_status = true;

}



Custom_ProcessOutput::~Custom_ProcessOutput(){


}



void Custom_ProcessOutput::Directory_List_Show_Cond(bool cond){

     this->dir_list_show_cnd = cond;
}

void Custom_ProcessOutput::Construct_Output(int size){

     this->window_open_status = true;

     this->process_interrrupt_status = false;

     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(750,-1));

     this->dialog_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(750,30));

     this->close_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(750,70));

     this->CloseButton  = new wxButton(this,ID_CLOSE_WINDOW,wxT("CLOSE"),wxDefaultPosition, wxSize(100, 50));



     this->textctrl = new wxTextCtrl(this->text_ctrl_panel,wxID_ANY, wxT(""), 
     
                      wxDefaultPosition, wxSize(750,500), wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY);



     this->dialog = new wxGauge(this->dialog_panel,wxID_ANY,size,
     
                    wxDefaultPosition,wxSize(750,30),wxGA_HORIZONTAL | wxGA_SMOOTH );

     


     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->text_ctrl_panel,1,wxEXPAND,2);

     this->ctrl_box->Layout();



     this->dialog_box = new wxBoxSizer(wxHORIZONTAL);

     this->dialog_box->Add(this->dialog_panel,1,wxEXPAND | wxALL,2);
       
     this->dialog_box->Layout();



     this->close_button_sizer = new wxBoxSizer(wxVERTICAL);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Add(this->CloseButton,0, wxALIGN_CENTER_HORIZONTAL | wxFIXED_MINSIZE  | wxALL,15);

     this->close_button_sizer->AddStretchSpacer();

     this->close_button_sizer->Layout();

     

     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1,    wxEXPAND | wxTOP    |  wxALL,5);
 
     this->frame_box->Add(this->dialog_box,0,  wxEXPAND | wxBOTTOM |  wxALL,5);

     this->frame_box->Add(this->close_button_sizer,0,   wxEXPAND | wxBOTTOM  | wxALL,5);



     this->frame_box->Layout();


     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);

     this->frame_box->Fit(this);



     this->text_ctrl_panel->SetSize(this->text_ctrl_panel->GetClientSize());

     this->dialog_panel->SetSize(this->dialog_panel->GetClientSize());

     this->close_panel->SetSize(this->close_panel->GetClientSize());


     this->text_ctrl_panel->Update();

     this->dialog_panel->Update();


     this->textctrl->Update();

     this->dialog->Update();



     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->Update();
}

void Custom_ProcessOutput::PrintProcessOutput(wxString text){

     this->textctrl->AppendText(text);  
}

void Custom_ProcessOutput::Receive_Tree_View_Panel(Custom_Tree_View_Panel * ptr){

     this->dir_list_ptr = ptr;
}


void Custom_ProcessOutput::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_ProcessOutput::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}


void Custom_ProcessOutput::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);
}



void Custom_ProcessOutput::Receive_System_Interface(Custom_System_Interface * Sys){

     this->SysPtr = Sys;
}


void Custom_ProcessOutput::CloseWindow(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_WINDOW){

        event.Skip(false);

        if(!this->process_end_status){

           wxString message_1 = "The construction process continuos!";

           wxString message_2 = "\nDo you want to cancel construction process?";
        
           wxString close_message = message_1 + message_2;


           wxBitmap * exclamation_mark_bmp
  
           = new wxBitmap(wxT("C:\\Development.Files\\Project.Test.platform\\icons\\exclamation_icon.png"),
           
           wxBITMAP_TYPE_ANY);

    
           Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,close_message,
            
           wxT("INTERRUPT CONFIRMATION"),wxID_ANY,
               
           wxT("THE PROCESS STOP CONFIRMATION"),
               
           *exclamation_mark_bmp, wxDefaultPosition,wxT("YES_NO"),wxSize(700,600));

           dial->ShowModal();

           if(dial->GetYesNoCond()){

              this->process_interrrupt_status = true;

              if(this->IsChildProcessStillAlive()){

                 this->ProcessTermination();
              }
           }

     }
     else{

          this->Destroy();

          if(this->dir_list_show_cnd){

             wxMilliSleep(100);

             if(!this->dir_list_ptr->Get_Panel_Open_Status()){

                 this->dir_list_ptr->Load_Project_Directory(wxString(this->directory_open_location));
             }   
          }
     }
   }
}

bool Custom_ProcessOutput::ProcessTermination(){

     bool termination_status = false;

     HANDLE processHandle = INVALID_HANDLE_VALUE;

     processHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, this->SysInt.Child_PID);

     if(processHandle == INVALID_HANDLE_VALUE){

        std::cout << "\n The child process can not be openned";

        std::cout << "\n in process termination process";

        exit(EXIT_FAILURE);
     }
     else{

          if(processHandle!=NULL){

             UINT uExitCode;

             BOOL success_status = TerminateProcess(processHandle,uExitCode);

             if(success_status == 0 ){

             }               
             else{

                termination_status = true;
             }
          }
     }

     return termination_status;
}

bool Custom_ProcessOutput::IsChildProcessStillAlive(){

     bool is_alive = false;

     DWORD ExitCode;

     if(GetExitCodeProcess(this->SysInt.piProcInfo.hProcess,&ExitCode) == FALSE){

     }
     else{

          if(ExitCode ==  STILL_ACTIVE){

             is_alive = true;
          }
     }
               
     return is_alive;
}


void Custom_ProcessOutput::OnClose(wxCloseEvent & event){
     
     if(!this->process_end_status){
          
        wxString message_1 = "The construction process continuos!";

        wxString message_2 = "\nDo you want to cancel construction process?";
        
        wxString close_message = message_1 + message_2;


        wxBitmap * exclamation_mark_bmp
  
           = new wxBitmap(wxT("C:\\Development.Files\\Project.Test.platform\\icons\\exclamation_icon.png"),
           
           wxBITMAP_TYPE_ANY);

    
        Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,close_message,
            
           wxT("INTERRUPT CONFIRMATION"),wxID_ANY,
               
           wxT("THE PROCESS STOP CONFIRMATION"),
               
           *exclamation_mark_bmp, wxDefaultPosition,wxT("YES_NO"),wxSize(700,600));

           dial->ShowModal();

           if(dial->GetYesNoCond()){
              
               if(this->SysInt.IsChildProcessStillAlive()){

                  this->SysInt.TerminateChildProcess();
               }

              event.Veto();
           }
     }
     else{

          event.Veto();

          this->Destroy();
     }
}



void Custom_ProcessOutput::ReadProcessOutput(wxString start_text){

     this->SysInt.CreateProcessWith_NamedPipe_From_Parent(this->cmd);

     this->progress_point = 0;

     int max=20;

     do{

        if(this->SysInt.IsPipeReadytoRead()){

            break;
        }
        else{

            sleep(0.05);
        }

     }while(!this->SysInt.IsPipeReadytoRead());


     this->SetBoldFont();

     this->GetTextControl()->AppendText(start_text);

     this->SetLightFont();


     std::string total_text;

     size_t text_size = 0;


     for(;;)
     {
        std::string pipeStr = this->SysInt.ReadNamedPipe_From_Parent();

        total_text = total_text + pipeStr;

        total_text.shrink_to_fit();

        size_t next_size = total_text.size();

        if(next_size > text_size){

           this->progress_point += 2;
        }

        text_size = next_size;



        wxString text(pipeStr);

        std::string space = "  ";

        wxString space_text(space);

        this->PrintProcessOutput(space_text);

        this->PrintProcessOutput(text);

        if(this->GetWindowsOpenStatus()){

           if(this->SysInt.IsChildProcessStillAlive() && 
           
             !this->process_interrrupt_status){

              this->GetDialogAddress()->SetValue(this->progress_point);
           }
        }
 
        if(!this->SysInt.IsChildProcessStillAlive() &&
        
            !this->process_interrrupt_status){

            if(this->GetWindowsOpenStatus()){

               this->GetDialogAddress()->SetValue(max);
            }

            break;
        }

        if(this->process_interrrupt_status){

           break;
        }
     }

     if(!this->process_interrrupt_status){

         this->process_end_status = true;
     }
     else{

          this->Destroy();
     }

     this->SysInt.Close_Parent_Handles_For_Named_Pipe_Connection();
}



void Custom_ProcessOutput::SetBoldFont(){

     wxTextAttr AttrBold(wxColor(100, 100, 120));

     AttrBold.SetFontWeight(wxFONTWEIGHT_BOLD);

     AttrBold.SetFontSize(12);

     AttrBold.SetFontFaceName(wxT("Calibri"));

     this->GetTextControl()->SetDefaultStyle(AttrBold);

}

void Custom_ProcessOutput::SetLightFont(){

     wxTextAttr AttrLigth(wxColor(50,50,50));

     AttrLigth.SetFontWeight(wxFONTWEIGHT_LIGHT);

     AttrLigth.SetFontSize(12);

     AttrLigth.SetFontFaceName(wxT("Calibri")); 

     this->GetTextControl()->SetDefaultStyle(AttrLigth);
}


void Custom_ProcessOutput::SetWindowOpenStatus(bool status){

      this->window_open_status = status;
}

void Custom_ProcessOutput::Receive_Directory_Open_Location(wxString loc){

     this->directory_open_location = loc;
}


wxGauge * Custom_ProcessOutput::GetDialogAddress() {

     return this->dialog;
}


wxTextCtrl * Custom_ProcessOutput::GetTextControl() const {

     return this->textctrl;
}

int Custom_ProcessOutput::GetLogNumber(){

     return this->log_num;
}

bool Custom_ProcessOutput::GetWindowsOpenStatus(){

     return this->window_open_status;
}