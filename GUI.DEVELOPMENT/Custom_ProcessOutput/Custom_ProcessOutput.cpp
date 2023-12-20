
#include "Custom_ProcessOutput.hpp"

Custom_ProcessOutput::Custom_ProcessOutput(wxFrame *parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{

     this->log_num =0;

     this->Default_Font = new wxFont(12,wxFONTFAMILY_MODERN ,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,"Segoe UI");

     this->SetFont(*(this->Default_Font));

     this->Memory_Delete_Condition = false;

     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

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

}



Custom_ProcessOutput::~Custom_ProcessOutput(){


}


void Custom_ProcessOutput::Construct_Output(int size){


     this->text_ctrl_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,600));

     this->dialog_panel = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(900,30));


     this->textctrl = new wxTextCtrl(this->text_ctrl_panel,wxID_ANY, wxT(""), 
     
                      wxDefaultPosition, wxSize(900,600), wxTE_MULTILINE | wxTE_RICH);



     this->dialog = new wxGauge(this->dialog_panel,wxID_ANY,size,
     
                    wxDefaultPosition,wxSize(900,30),wxGA_HORIZONTAL | wxGA_SMOOTH );

     


     this->ctrl_box = new wxBoxSizer(wxHORIZONTAL);

     this->ctrl_box->Add(this->text_ctrl_panel,1,wxEXPAND);

     this->ctrl_box->Layout();



     this->dialog_box = new wxBoxSizer(wxHORIZONTAL);

     this->dialog_box->Add(this->dialog_panel,1,wxEXPAND | wxALL,2);
       
     this->dialog_box->Layout();




     this->frame_box = new wxBoxSizer(wxVERTICAL);

     this->frame_box->Add(this->ctrl_box,1, wxEXPAND | wxTOP | wxALL,5);

     this->frame_box->Add(this->dialog_box,0, wxEXPAND | wxBOTTOM |  wxALL,5);

     this->frame_box->Layout();


     this->SetSizer(this->frame_box);

     this->frame_box->SetSizeHints(this);


     this->frame_box->Fit(this);



     this->text_ctrl_panel->SetSize(this->text_ctrl_panel->GetClientSize());

     this->dialog_panel->SetSize(this->dialog_panel->GetClientSize());

     this->text_ctrl_panel->Update();

     this->dialog_panel->Update();


     this->textctrl->Update();

     this->dialog->Update();



     this->SetSize(this->GetClientSize());

     this->PostSizeEvent();

     this->Centre(wxBOTH);

     this->Update();
}

void Custom_ProcessOutput::Receive_Process_End_Status(bool * status){

     this->process_end_status = status;
}


void Custom_ProcessOutput::PrintProcessOutput(){

     /*

     wxInputStream * stream = this->Process_Manager_Ptr->GetInputStream();

     wxTextInputStream tStream(*stream);

     do{

        wxString log_string = tStream.ReadLine() + wxT("\n");
                     
        if(!log_string.empty()){

           this->textctrl->AppendText(log_string);

           this->log_num++;
        }

     }while(stream->CanRead());

     */     
}




void Custom_ProcessOutput::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

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


void Custom_ProcessOutput::OnClose(wxCloseEvent & event){
     
     if(*this->process_end_status == false){
          
         if(wxMessageBox("The construction Process continuos", "Please Confirm",
     
             wxICON_QUESTION |wxYES_NO) != wxYES){

             event.Veto();

             return;
         }
     }
     else{

          this->Destroy();
     }
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