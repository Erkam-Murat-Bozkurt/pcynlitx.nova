

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



#include "Gui_Shell_Script_Executer.hpp"


/*
BEGIN_EVENT_TABLE(Gui_Shell_Script_Executer,wxFrame)
    EVT_BUTTON(ID_CLOSE_PROCESS_OUTPUT_WINDOW,Gui_Shell_Script_Executer::CloseWindow)
END_EVENT_TABLE()
*/


Gui_Shell_Script_Executer::Gui_Shell_Script_Executer(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxFrame(parent,id,title,pos,size,
   
   wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{
     this->error_stream_status = false;

     this->procCmd = nullptr;

     this->Memory_Delete_Condition = false;

     this->Default_Font = new wxFont(12,wxFONTFAMILY_MODERN ,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,"Calibri");

     this->SetFont(*(this->Default_Font));

     this->Memory_Delete_Condition = false;

     
     this->Frame_Bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("FRAME_ICON"));

     wxIcon Frame_Icon;

     Frame_Icon.CopyFromBitmap(*this->Frame_Bitmap);

     this->SetIcon(Frame_Icon);

     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->SetExtraStyle(wxFULL_REPAINT_ON_RESIZE);

     this->GetEventHandler()->Bind(wxEVT_SIZE,&Gui_Shell_Script_Executer::OnSize,this,wxID_ANY);

     wxString label = wxT("The output of the build script");

     this->Process_Output = new Custom_ProcessOutput(parent,wxID_ANY,label);


     this->exclamation_mark_bmp 
  
      = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("EXCLAMATION_ICON"));



     this->script_end_status = false;

     this->Process_Output->Receive_System_Interface(&this->SysInt);

     this->Process_Output->Directory_List_Show_Cond(false);

     this->Process_Output->Receive_Process_End_Status(&this->script_end_status);

     this->Process_Output->Construct_Output(20);

     this->Process_Output->Centre(wxBOTH);

     this->SetThemeEnabled(true);

     this->SetDoubleBuffered(true);

     this->SetExtraStyle(wxCLIP_CHILDREN);


     this->SetBackgroundStyle(wxBG_STYLE_PAINT);

     this->Centre(wxBOTH);

     this->CentreOnParent(wxBOTH);

     this->Fit();
}

Gui_Shell_Script_Executer::~Gui_Shell_Script_Executer(){

    if(!this->Memory_Delete_Condition){

        this->Memory_Delete_Condition = true;

        this->Clear_String_Memory(this->procCmd);
    }
}


void Gui_Shell_Script_Executer::Clear_String_Memory(char * ptr){

     if(ptr != nullptr){

        delete [] ptr;

        ptr = nullptr;
     }
}



void Gui_Shell_Script_Executer::Fork_Process_With_Std_Out_Redirection(char * cmd){

     bool success_status =  this->SysInt.Create_Process_With_Redirected_Stdout(cmd);

     this->read_process_output = new std::thread(Gui_Shell_Script_Executer::ReadStdOut,this);

     this->read_process_output->join();

     if(!success_status){

          wxString std_error = this->Get_Output_Stream();

          this->Process_Output->PrintProcessOutput(std_error);

          this->script_end_status = true;
     }
     else{

          this->Process_Exit_Status 
          
          = this->SysInt.Get_Anonymously_PipedProcess_ExitCode();
     }
}


void Gui_Shell_Script_Executer::Execute_Shell_Script(std::string path){

     if(!this->FileManager.Is_This_File_Empty(path)){

         this->FileManager.Read_File(path);

         this->script_size = this->FileManager.GetFileSize();

         std::string size = std::to_string(this->script_size);

                 Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,wxString(size),
            
               wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("PCYNLITX OPERATION REPORT"),
               
               *this->exclamation_mark_bmp, wxDefaultPosition,wxT("Close"),wxSize(1500,500));

               dial->ShowModal();


         for(int i=0;i<this->script_size;i++){

              std::string str_line = this->FileManager.GetFileLine(i);
               
              if(this->StringManager.CheckStringLine(str_line)){

                 this->c_str =this->Convert_CString(str_line);



               wxString Message = wxString(str_line);
            
               dial = new Custom_Message_Dialog(this,Message,
            
               wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("PCYNLITX OPERATION REPORT"),
               
               *this->exclamation_mark_bmp, wxDefaultPosition);

               dial->ShowModal();



              if(!this->script_end_status){

                 wxString Message = wxT("command line:") + wxString(str_line);
            
                 Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
                 wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("PCYNLITX OPERATION REPORT"),
               
                 *this->exclamation_mark_bmp, wxDefaultPosition,wxT("Close"),wxSize(1500,500));

                 dial->ShowModal();


                 this->Fork_Process_With_Std_Out_Redirection(this->c_str);

                 wxString std_out_put = this->Get_Output_Stream();


               Message = std_out_put;
            
               dial = new Custom_Message_Dialog(this,Message,
            
               wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("PCYNLITX OPERATION REPORT"),
               
               *this->exclamation_mark_bmp, wxDefaultPosition,wxT("Close"),wxSize(1500,500));

               dial->ShowModal();

               if(!std_out_put.ToStdString().empty()){

                  this->Process_Output->PrintProcessOutput(std_out_put);
               }                
              }
            }

         }

         this->script_end_status = true;
     }

}


void Gui_Shell_Script_Executer::script_executer(std::string path){

}

void Gui_Shell_Script_Executer::ReadStdOut(){

     this->SysInt.ReadFromPipe();

     this->std_out_put = this->SysInt.GetAnonymousPipe_String();
}



void Gui_Shell_Script_Executer::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxSize Rect_Size = wxSize(wnd->GetSize().x+5,wnd->GetSize().y+5);

     wxRect rect(Rect_Size);

     this->DrawBackground(dc,wnd,rect);
}


void Gui_Shell_Script_Executer::OnSize(wxSizeEvent & event){

     event.Skip(true);

     this->PaintNow(this);
}


void Gui_Shell_Script_Executer::DrawBackground(wxDC& dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

/*
void Gui_Shell_Script_Executer::CloseWindow(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_PROCESS_OUTPUT_WINDOW){

        this->Destroy();
     }
}
*/


wxString Gui_Shell_Script_Executer::Get_Error_Stream(){

     this->SysInt.ReadFromPipe();

     std::string error_st = this->SysInt.GetAnonymousPipe_String();

     wxString std_err(error_st);

     return std_err;
}

wxString Gui_Shell_Script_Executer::Get_Output_Stream(){

     this->SysInt.ReadFromPipe();

     std::string out = this->SysInt.GetAnonymousPipe_String();
     
     wxString std_out(out);

     return std_out;
}


char * Gui_Shell_Script_Executer::Convert_CString(std::string std_str){

      if(this->c_str != nullptr){

          delete [] this->c_str ;

          this->c_str  = nullptr;
      }

      size_t string_size = std_str.length();

      size_t index = 0;

      this->c_str  = new char [5*string_size];

      for(size_t i=0;i<5*string_size;i++){

           this->c_str [i] = '\0';
      }

      for(size_t i=0;i<string_size;i++){

          this->c_str[index] = std_str[i];

          index++;
      }

      this->c_str [index] = '\0';

      return this->c_str;
}


int Gui_Shell_Script_Executer::Get_Process_Exit_Status(){

     return this->Process_Exit_Status;
}


char * Gui_Shell_Script_Executer::Get_Process_Command(){

     return this->procCmd;
}


std::string Gui_Shell_Script_Executer::Get_Std_Out(){

     return this->std_out_put;
}
