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

#include "Event_Table_Header.h"

MainFrame::MainFrame() : wxFrame((wxFrame * )NULL,-1,"PCYNLITX",

        wxDefaultPosition, wxSize(1200,950),wxDEFAULT_FRAME_STYLE )
{

  this->is_custom_panel_constructed = false;

  this->Interface_Manager.SetManagedWindow(this);

  this->SetThemeEnabled(true);

  this->SetDoubleBuffered(true);

  this->SetExtraStyle(wxCLIP_CHILDREN);

  this->SetExtraStyle(wxNO_FULL_REPAINT_ON_RESIZE);

  this->SetBackgroundStyle(wxBG_STYLE_PAINT);

  this->ClearBackground();


  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);

  this->Des_Reader = new Descriptor_File_Reader('w');




  this->Default_Font = new wxFont(10,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false);

  this->is_bold_style_selected = false;


  this->SetBackgroundColour(wxColour(200,200,200));

  this->Interface_Manager.SetFlags(wxAUI_MGR_LIVE_RESIZE);


  this->SetSize(wxSize(1200,950));

  this->SetMinSize(wxSize(1200,950));

  this->Refresh();

  this->SetDoubleBuffered(true);

  this->SetAutoLayout(true);


  // THE CONSTRUCTION OF THE MENU BAR

  this->MB_Options = new Menu_Bar_Options();

  this->SetMenuBar(this->MB_Options->Get_MenuBar());


  // THE CONSTRUCTION OF THE DOCKART POINTER

  this->Dock_Art_Pointer = new Custom_DockArt();

  this->Interface_Manager.SetArtProvider(this->Dock_Art_Pointer);



  // THE CONSTRUCTION OF THE TOOLBAR..


  this->ToolBar_Widget = new ToolBar_Initializer();

  this->ToolBar_Widget->Initialize_ToolBar(this,this->Dock_Art_Pointer,&this->Interface_Manager);

  this->Interface_Manager.Update();

  this->Toolbar_ID = this->ToolBar_Widget->Get_ToolBar_Pointer()->GetId();



  this->Interface_Manager.Update();


  // THE CONSTRUCTION OF THE CUSTOM PANEL FOR NOTEBOOK

  this->Central_Pane_Info.CloseButton(false);

  this->Central_Pane_Info.Centre();

  this->Central_Pane_Info.Dock();

  this->Central_Pane_Info.Show(true);

  this->Central_Pane_Info.Resizable(true);

  this->Central_Pane_Info.MinSize(910,650);



  this->Custom_Main_Panel = new Custom_wxPanel(this,wxID_ANY,wxDefaultPosition,

                            wxDefaultSize,wxColour(200,200,200),&this->Central_Pane_Info);

  this->Custom_Main_Panel->SetSize(this->GetClientSize());

  this->Custom_Main_Panel->Fit();

  this->Custom_Main_Panel->SetAutoLayout(true);


  // THE CONSTRUCTION OF THE NOTEBOOK

  this->Book_Manager = new Custom_Notebook(this->Custom_Main_Panel,&this->Interface_Manager,

                       *(this->Default_Font),this->GetClientSize());


  this->Book_Manager->SetAutoLayout(true);

  this->Custom_Main_Panel->Receive_Book_Manager_Window(this->Book_Manager);

  this->Custom_Main_Panel->Initialize_Sizer();

  this->Interface_Manager.AddPane(this->Custom_Main_Panel,this->Central_Pane_Info);

  this->Interface_Manager.Update();

  this->Book_Manager->Refresh();


  this->is_custom_panel_constructed = true;

  this->Interface_Manager.Update();

  this->GetEventHandler()->Bind(wxEVT_PAINT,&MainFrame::OnPaint,this,wxID_ANY);


  this->Interface_Manager.Update();


  this->is_project_file_selected = false;

  this->Descriptor_File_Path = wxT("");

  this->Construction_Point = wxT("");

  this->Memory_Delete_Condition = false;

  this->Custom_Main_Panel->Refresh(true);

  this->Interface_Manager.Update();



  // THE CONSTRUCTION OF THE DIRECTORY TREE VIEW

  this->Dir_List_Manager = new Custom_Tree_View_Panel(this,wxID_ANY,wxDefaultPosition,

                            wxSize(270,this->GetClientSize().y),&this->Interface_Manager,

                            *(this->Default_Font),this->Book_Manager->GetTabCtrlHeight());

  this->tree_control = this->Dir_List_Manager->GetTreeCtrl();

  this->dir_control = new wxDir;


  wxRect Main_Rect(this->GetSize());

  this->Refresh(true,&Main_Rect);

  this->SetAutoLayout(true);

  this->Centre(wxBOTH);

  this->Custom_Main_Panel->Refresh();

  this->Book_Manager->Refresh();

  this->PaintNow(this->Custom_Main_Panel);

  this->PaintNow(this->Book_Manager);

  this->PaintNow(this);

  wxRect Central_Panel_Rect(this->Custom_Main_Panel->GetSize());

  this->Custom_Main_Panel->Refresh(true,&Central_Panel_Rect);

  this->Custom_Main_Panel->Update();


  wxRect Book_Manager_Rect(this->Custom_Main_Panel->GetSize());

  this->Book_Manager->Refresh(true,&Book_Manager_Rect);

  this->Book_Manager->Update();

  this->Raise();

  this->PostSizeEvent();

  this->Interface_Manager.Update();

  this->is_descriptor_file_open = false;
}

MainFrame::~MainFrame()
{
   this->Interface_Manager.UnInit();

   this->Close(true);
}

void MainFrame::File_Save(wxCommandEvent & event){

     if(event.GetId() == ID_FILE_SAVE){

        if(this->Book_Manager->Get_Open_File_Number() > 0){

           this->Book_Manager->File_Save();
        }
        else{

                  wxMessageDialog * dial = new wxMessageDialog(NULL,

                  wxT(" This is no any file currently open!\n A file must be open ."),

                  wxT("Error Message"), wxOK);

                  dial->ShowModal();
            
        }      
     }
}





void MainFrame::PaintNow(wxWindow * wnd)
{
     wxClientDC dc(wnd);

     wxRect rect(wnd->GetSize());

     this->DrawBackground(dc,wnd,rect);

     if(this->is_custom_panel_constructed)
     {
        this->Custom_Main_Panel->PaintNow(this->Custom_Main_Panel);

        this->Book_Manager->PaintNow(this->Book_Manager);
     }
}

void MainFrame::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(200,200,200));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+10,rect.GetHeight()+5);
}

void MainFrame::OnPaint(wxPaintEvent & event)
{
     event.Skip(false);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);

     if(this->is_custom_panel_constructed)
     {
        this->Custom_Main_Panel->PaintNow(this->Custom_Main_Panel);

        this->Book_Manager->PaintNow(this->Book_Manager);
     }
}

void MainFrame::Show_Project_File(wxCommandEvent & event){

     if(event.GetId() == ID_SHOW_PROJECT_FILE){

        event.Skip(true);

        if(this->is_descriptor_file_open){

           bool is_descriptor_file_open = false;

           for(int i=0;i<20;i++){

               wxString Path_Data =  this->Book_Manager->Get_Notebook_Page_File_Path(i);

               if(Path_Data == this->Descriptor_File_Path){

                  is_descriptor_file_open = true;

                  break;
               }
            }

            if(is_descriptor_file_open){

                this->Book_Manager->Select_File(this->Descriptor_File_Path);
            }
            else{

                  this->Book_Manager->Open_File(this->Descriptor_File_Path);
            }
        }
        else{

             this->Descriptor_File_Selection_Check();
        }
     }
}

void MainFrame::Show_Author(wxCommandEvent & event)
{
     if(event.GetId() == ID_SHOW_AUTOR_INFO){

        wxString message = wxT("\n");

        message = message + wxT("   ERKAM MURAT BOZKURT\n\n");

        message = message + wxT("   PCYNLITX Software, Istanbul / TURKEY\n\n");

        message = message + wxT("   M.Sc. Control Sysytem Engineering\n\n");

        message = message + wxT("   ORCID ID: 0000-0003-3690-2770\n\n");

        message = message + wxT("   http://www.pcynlitx.com/developer/\n\n");

        message = message + wxT("   pcynlitx.help@gmail.com\n\n");


        wxRichMessageDialog * dial = new wxRichMessageDialog(this,

                     message, wxT("    THE DEVELOPER OF THE PLATFORM"), wxOK|wxCENTRE);

        if(dial->ShowModal() == ID_SHOW_AUTOR_INFO){

           delete dial;
        };
     }
}



void MainFrame::Close_Directory_Pane(wxAuiManagerEvent & event)
{
     event.Veto(true);

     event.StopPropagation();

     this->Dir_List_Manager->RemoveProjectDirectory();

     this->Dir_List_Manager->Close_Directory_Pane();

     this->Interface_Manager.Update();
}

void MainFrame::DirectoryOpen(wxCommandEvent & event)
{
     if(event.GetId() == ID_OPEN_TREE_WIEW){

        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);


        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           if(!this->Dir_List_Manager->Get_Panel_Open_Status()){

              this->Dir_List_Manager->Load_Project_Directory(DirectoryPath);
           }

           this->Interface_Manager.Update();
        }


        this->Centre();

        this->tree_control->Update();

        this->PaintNow(this);

        this->Update();
     }
}




void MainFrame::Start_Build_System_Construction(wxCommandEvent & event){

  if(event.GetId() == ID_RUN_BUILD_SYSTEM_CONSTRUCTOR)
  {
    event.Skip(true);

    if(this->is_descriptor_file_open){

       char executable [] = "D:\\Pcynlitx_Build_Platform\\CBuild.exe ";

       char option [] = " -ip_for_gui";

       size_t exe_cmd_size  = strlen(executable);

       size_t des_path_size = strlen(this->Descriptor_File_Path.c_str()); 

       size_t option_size   = strlen(option);

       size_t cmd_str_size = exe_cmd_size + des_path_size + option_size;

       size_t cmd_size = 2*cmd_str_size;

       char * cmd = new char[cmd_size];

       for(size_t i=0;i<cmd_size;i++){

           cmd[i] = '\0';
       }

       size_t index = 0;

       for(size_t i=0;i<exe_cmd_size;i++){

           cmd[index] = executable[i];

           index++;
       }

       for(size_t i=0;i<des_path_size;i++){

           cmd[index] = this->Descriptor_File_Path.c_str()[i];

           index++;

       }

       for(size_t i=0;i<option_size;i++){

           cmd[index] = option[i];

           index++;
       }

       cmd[index] = '\0';




       this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());

       this->Des_Reader->Read_Descriptor_File();


       std::string warehose_word = "\\WAREHOUSE";

       this->Warehouse_Location = this->Des_Reader->Get_Warehouse_Location() + warehose_word;


       this->Progress_Bar_Start_status = false;

       this->Child_Process_End_Status  = false;

       this->Child_Process_Started_to_Execution = false;

       this->is_pipe_ready = false;



       this->fork_process = new std::thread(MainFrame::ForkProcess,this,cmd);

       this->fork_process->detach();

       this->progress_point = 0;


       this->read_process_output = new std::thread(MainFrame::ReadProcessOutput,this,&this->progress_point);

       this->read_process_output->detach();


       wxString label = wxT("Build System Construction");

       this->Show_Progress(label);
    }
    else{

         this->Descriptor_File_Selection_Check();
    }
  }
}


void MainFrame::ForkProcess(char * cmd){

     std::unique_lock<std::mutex> lck(this->mtx);

     lck.unlock();

     

     this->SysInt.CreateProcessWith_NamedPipe_From_Parent(cmd);

     delete [] cmd;


     lck.lock();

     this->Child_Process_Started_to_Execution = true;

     lck.unlock();



     lck.lock();

     if(!this->Progress_Bar_Start_status){

         this->cv.wait(lck);

         lck.unlock();
     }
     else{

         lck.unlock();
     }       


     lck.lock();

     if(!this->Child_Process_End_Status){

         this->cv.wait(lck);

         lck.unlock();
     }
     else{

         lck.unlock();
     }


     this->SysInt.Close_Parent_Handles_For_Named_Pipe_Connection();

}




void MainFrame::Show_Progress(wxString Process_Label){

     std::unique_lock<std::mutex> lck(this->mtx);

     lck.unlock();


     this->Process_Output = new Custom_ProcessOutput(this);

     this->Process_Output->Receive_System_Interface(&this->SysInt);
 
     this->Process_Output->Receive_Process_End_Status(&this->Child_Process_End_Status);

     this->Process_Output->Receive_Warehouse_Location(this->Warehouse_Location);

     this->Process_Output->Receive_Tree_View_Panel(this->Dir_List_Manager);

     int max=20;
     
     this->Process_Output->Construct_Output(max);


     for(;;){

         if(this->is_pipe_ready){

            if(this->Process_Output->GetWindowsOpenStatus()){

               this->Process_Output->GetDialogAddress()->SetValue(this->progress_point);
            }
            else{

                if(this->Process_Output->GetWindowsOpenStatus()){

                   this->Process_Output->GetDialogAddress()->SetValue(1);
                }

            }
         }
                       
         wxMilliSleep(1);
         wxYield();


         if(!this->Child_Process_Started_to_Execution){

            do{

                wxYield();
                wxMilliSleep(1);

            }while(!this->Child_Process_Started_to_Execution);
         }


         
         lck.lock();

         if(!this->Progress_Bar_Start_status){

            this->Progress_Bar_Start_status = true;
   
            this->cv.notify_all();

            lck.unlock();
         }
         else{

            lck.unlock();
         }

         

        if(!this->SysInt.IsChildProcessStillAlive()){

            if(this->Process_Output->GetWindowsOpenStatus()){

               this->Process_Output->GetDialogAddress()->SetValue(max);
            }

            break;   
        }

     }
}


void MainFrame::ReadProcessOutput(int * prg){

     std::unique_lock<std::mutex> lck(this->mtx);

     lck.unlock();



     lck.lock();

     if(!this->Progress_Bar_Start_status){

         this->cv.wait(lck);

         lck.unlock();
     }
     else{

         lck.unlock();
     }       



     do{

        if(this->SysInt.IsPipeReadytoRead()){

            break;
        }
        else{

            sleep(0.1);
        }

     }while(!this->SysInt.IsPipeReadytoRead());

     this->is_pipe_ready = true;

     std::string total_text;

     size_t text_size = 0;

     for(;;)
     {
        std::string pipeStr = this->SysInt.ReadNamedPipe_From_Parent();

        total_text = total_text + pipeStr;

        total_text.shrink_to_fit();

        size_t next_size = total_text.size();

        if(next_size > text_size){

           *prg += 2;
        }

        text_size = next_size;

        wxString text(pipeStr);

        this->Process_Output->PrintProcessOutput(text);

        if(!this->SysInt.IsChildProcessStillAlive()){

            break;
        }
     } 


     lck.lock();

     this->Child_Process_End_Status = true;

     this->cv.notify_all();

     lck.unlock();

}



void MainFrame::Open_Empty_Project_File(wxCommandEvent & event)
{
  if(event.GetId() == ID_OPEN_EMPTY_PROJECT_FILE)
  {
     wxDirDialog dlg(NULL, "Select Descriptor File Location", "",

           wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

     if(dlg.ShowModal() == wxID_OK){

        wxString construction_dir =dlg.GetPath();

        this->Descriptor_File_Path = construction_dir + wxT("\\Pcb_Descriptor.txt");

        this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());

        this->Process_Ptr = new Process_Manager(this,wxID_ANY);

        wxString shell_command = "D:\\Pcynlitx_Build_Platform\\CBuild.exe " 
        
        + construction_dir + " -ed";

        this->Process_Ptr->Fork_Process(shell_command);

        this->is_descriptor_file_open = true;
     }
   }
}

void MainFrame::Select_Project_File(wxCommandEvent & event)
{
     if(event.GetId() == ID_SELECT_PROJECT_FILE ){

       event.Skip(true);

        wxFileDialog * openFileDialog

              = new wxFileDialog(this,wxT("Select Project File"));

        if (openFileDialog->ShowModal() == wxID_OK){

            this->Descriptor_File_Path = openFileDialog->GetPath();

            wxDir Dir_Ctrl;

            if(Dir_Ctrl.Exists(this->Descriptor_File_Path)){

               Dir_Ctrl.Open(this->Descriptor_File_Path);

               if(Dir_Ctrl.IsOpened()){

                  wxMessageDialog * dial = new wxMessageDialog(NULL,

                    wxT(" This is a directory!\n A file must be selected ."),

                         wxT("Error Message"), wxOK);

                         dial->ShowModal();

                    return;
                }
            }

            delete openFileDialog;

            this->is_descriptor_file_open = true;

            this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());
     }
   }
}



void MainFrame::FileSelect(wxTreeEvent& event)
{
     event.Skip(true);

     event.StopPropagation();

     wxTreeItemId Item = this->tree_control->GetSelection();

     wxString Path = this->Dir_List_Manager->GetItemPath(Item);

     if(this->dir_control->Exists(Path)){

        if(this->Dir_List_Manager->GetTreeCtrl()->IsExpanded(Item)){

           this->Dir_List_Manager->GetTreeCtrl()->Collapse(Item);

           this->Dir_List_Manager->GetTreeCtrl()->PaintNow();
        }
        else{

             this->Dir_List_Manager->GetTreeCtrl()->Expand(Item);

             this->Dir_List_Manager->GetTreeCtrl()->PaintNow();
        }
     }
     else{

            this->Book_Manager->Open_File(Path);
     }
}

void MainFrame::FileNameEdit(wxTreeEvent& event)
{
     event.Veto();

}




void MainFrame::Open_Intro_Page(wxCommandEvent & event)
{
     if(event.GetId() == ID_OPEN_INTROPAGE)
     {
        this->Book_Manager->OpenIntroPage();
     }
}

void MainFrame::Enter_Git_Repo_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_GIT_REPO_LOCATION){

       if(!this->is_descriptor_file_open){

          this->Descriptor_File_Selection_Check();
       }
       else{

            this->DataType = "PROJECT-ROOT-DIR";

            this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

            this->data_panel_ptr->File_Slection_Status(false);

            this->data_panel_ptr->Receive_Text_Enter_Status(false);

            this->data_panel_ptr->Receive_Data_Type(this->DataType);

            this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

            this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

            this->data_panel_ptr->AppendTextColumn(wxT("Git repository location"));

            this->data_panel_ptr->Show();

            this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}


void MainFrame::Enter_Header_File_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_HEADER_FILE_LOCATION){

        if(!this->is_descriptor_file_open){

            this->Descriptor_File_Selection_Check();
        }
        else{
              this->DataType = "INCLUDE-DIRECTORIES";

              this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

              this->data_panel_ptr->File_Slection_Status(false);

              this->data_panel_ptr->Receive_Text_Enter_Status(false);

              this->data_panel_ptr->Receive_Data_Type(this->DataType);

              this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

              this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

              this->data_panel_ptr->AppendTextColumn(wxT("HEADER FILE LOCATIONS"));

              this->data_panel_ptr->Show();

              this->data_panel_ptr->GetDataViewListCtrl()->Show();
        }
     }
}

void MainFrame::Enter_Source_File_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_SOURCE_FILE_LOCATION){

        if(!this->is_descriptor_file_open){

            this->Descriptor_File_Selection_Check();
        }
        else{

           this->DataType = "SOURCE-FILE-DIRECTORIES";

           this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

           this->data_panel_ptr->File_Slection_Status(false);

           this->data_panel_ptr->Receive_Text_Enter_Status(false);

           this->data_panel_ptr->Receive_Data_Type(this->DataType);

           this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

           this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

           this->data_panel_ptr->AppendTextColumn(wxT("SOURCE FILE LOCATIONS"));

           this->data_panel_ptr->Show();

           this->data_panel_ptr->GetDataViewListCtrl()->Show();
        }
     }
}

void MainFrame::Enter_Library_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_LIBRARY_LOCATION){

       if(!this->is_descriptor_file_open){

           this->Descriptor_File_Selection_Check();
       }
       else{

             this->DataType = "LIBRARY-DIRECTORIES";

             this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

             this->data_panel_ptr->File_Slection_Status(false);

             this->data_panel_ptr->Receive_Text_Enter_Status(false);

             this->data_panel_ptr->Receive_Data_Type(this->DataType);

             this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

             this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

             this->data_panel_ptr->AppendTextColumn(wxT("LIBRARY PATHS"));

             this->data_panel_ptr->Show();

             this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::OpenTerminal(wxCommandEvent & event)
{
     if(event.GetId() == ID_OPEN_TERMINAL){

        wxExecute(wxT("powershell.exe"),wxEXEC_SYNC | wxEXEC_SHOW_CONSOLE);
     }
}


void MainFrame::Enter_Library_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_LIBRARY_NAME){

       if(!this->is_descriptor_file_open){

          this->Descriptor_File_Selection_Check();
       }
       else{

            this->DataType = "LIBRARY-FILES";

            this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

            this->data_panel_ptr->File_Slection_Status(true);

            this->data_panel_ptr->Receive_Text_Enter_Status(false);

            this->data_panel_ptr->Receive_Data_Type(this->DataType);

            this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

            this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

            this->data_panel_ptr->AppendTextColumn(wxT("LIBRARY-FILES"));

            this->data_panel_ptr->Show();

            this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::Enter_Warehouse_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_CONSTRUCTION_POINT){

       if(!this->is_descriptor_file_open){

         this->Descriptor_File_Selection_Check();
       }
       else{

           this->DataType = "PROJECT-WAREHOUSE-LOCATION";

           this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

           this->data_panel_ptr->File_Slection_Status(false);

           this->data_panel_ptr->Receive_Text_Enter_Status(false);

           this->data_panel_ptr->Receive_Data_Type(this->DataType);

           this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

           this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

           this->data_panel_ptr->AppendTextColumn(wxT("Repo Warehouse Location"));

           this->data_panel_ptr->Show();

           this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::Enter_Exe_File_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_EXE_FILE_NAME){

        if(!this->is_descriptor_file_open){

           this->Descriptor_File_Selection_Check();
        }
        else{

           this->DataType = "EXECUTABLE-FILE-NAMES";

           this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

           this->data_panel_ptr->Receive_Data_Type(this->DataType);

           this->data_panel_ptr->File_Slection_Status(false);

           this->data_panel_ptr->Receive_Text_Enter_Status(true);

           this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

           this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

           this->data_panel_ptr->AppendTextColumn(wxT("Executable File Name"));

           this->data_panel_ptr->Show();

           this->data_panel_ptr->GetDataViewListCtrl()->Show();
        }
     }
}

void MainFrame::Enter_Main_File_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_MAIN_FILE_NAME){

       if(!this->is_descriptor_file_open){

           this->Descriptor_File_Selection_Check();
       }
       else{

         this->DataType = "MAIN-FILE-NAMES";

         this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

         this->data_panel_ptr->Receive_Data_Type(this->DataType);

         this->data_panel_ptr->File_Slection_Status(false);

         this->data_panel_ptr->Receive_Text_Enter_Status(true);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

         this->data_panel_ptr->AppendTextColumn(wxT("Main file name"));

         this->data_panel_ptr->Show();

         this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::Enter_Standard(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_C_STANDART){

       if(!this->is_descriptor_file_open){

           this->Descriptor_File_Selection_Check();
       }
       else{

         this->DataType = "C++-STANDARD";

         this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

         this->data_panel_ptr->Receive_Data_Type(this->DataType);

         this->data_panel_ptr->File_Slection_Status(false);

         this->data_panel_ptr->Receive_Text_Enter_Status(true);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

         this->data_panel_ptr->AppendTextColumn(wxT("Main file name"));

         this->data_panel_ptr->Show();

         this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::Enter_Options(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_OPTIONS){

       if(!this->is_descriptor_file_open){

           this->Descriptor_File_Selection_Check();
       }
       else{

         this->DataType = "OPTIONS";

         this->data_panel_ptr = new Custom_DataPanel(this,wxSize(700,400));

         this->data_panel_ptr->Receive_Data_Type(this->DataType);

         this->data_panel_ptr->File_Slection_Status(false);

         this->data_panel_ptr->Receive_Text_Enter_Status(true);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

         this->data_panel_ptr->SetTitle(wxT("INSERT YOUR CHOICE"));

         this->data_panel_ptr->AppendTextColumn(wxT("Main file name"));

         this->data_panel_ptr->Show();

         this->data_panel_ptr->GetDataViewListCtrl()->Show();
       }
     }
}

void MainFrame::Descriptor_File_Selection_Check(){

     wxString Error_Message = "Descriptor file was not selected";

     Error_Message = Error_Message + "\nPlease select a descriptor file";

     Error_Message = Error_Message + "\nor construct an empty descriptor file";

     wxMessageDialog * dial = new wxMessageDialog(NULL,

      Error_Message, wxT("Info"), wxOK);

     if(dial->ShowModal()== wxOK){

        delete dial;
      }
}



void MainFrame::Increase_Font_Size(wxCommandEvent & event)
{
     if(event.GetId() == ID_INCREASE_FONT_SIZE){

        event.StopPropagation();

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           wxFont Font = this->Book_Manager->Get_Selected_Text_Ctrl()->StyleGetFont(wxSTC_C_REGEX);

           Font.SetPointSize(Font.GetPointSize()+1);

           this->Book_Manager->Set_Font(Font);

           if(this->is_bold_style_selected){

              this->Book_Manager->Use_Bold_Styling();
           }
        }
     }
}

void MainFrame::Decrease_Font_Size(wxCommandEvent & event)
{
     if(event.GetId() == ID_DECREASE_FONT_SIZE){

        event.StopPropagation();

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           wxFont Font = this->Book_Manager->Get_Selected_Text_Ctrl()->StyleGetFont(wxSTC_C_REGEX);

           Font.SetPointSize(Font.GetPointSize()-1);

           this->Book_Manager->Set_Font(Font);

           if(this->is_bold_style_selected){

              this->Book_Manager->Use_Bold_Styling();
            }
        }
     }
}





void MainFrame::Undo_Changes(wxCommandEvent & event)
{
     if(event.GetId() == ID_UNDO_CHANGES){

        event.StopPropagation();

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           this->Book_Manager->Get_Selected_Text_Ctrl()->Undo();
        }
     }
}

void MainFrame::Redo_Changes(wxCommandEvent & event)
{
     if(event.GetId() == ID_REDO_CHANGES){

        event.StopPropagation();

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           this->Book_Manager->Get_Selected_Text_Ctrl()->Redo();
        }
     }
}

void MainFrame::Clear_Style(wxCommandEvent & event)
{
     if(event.GetId() ==  ID_CLEAR_STYLE){

        event.StopPropagation();

        this->is_bold_style_selected = false;

        this->Book_Manager->Clear_Style();
     }
}

void MainFrame::Reload_Default_Style(wxCommandEvent & event)
{
     if(event.GetId() == ID_RELOAD_STYLE){

        event.StopPropagation();

        this->is_bold_style_selected = false;

        this->Book_Manager->Reload_Style();
     }
}

void MainFrame::Clear_Text(wxCommandEvent & event)
{
     if(event.GetId() == ID_CLEAR_TEXT){

        event.StopPropagation();

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           this->Book_Manager->Get_Selected_Text_Ctrl()->ClearAll();
        }
     }
}

void MainFrame::Change_Cursor_Type(wxCommandEvent & event)
{
     if(event.GetId() == ID_CHANGE_CURSOR_TYPE){

       event.StopPropagation();

       this->Book_Manager->Change_Cursor_Type();
     }
}

void MainFrame::Load_Default_Cursor(wxCommandEvent & event)
{
     if(event.GetId() == ID_SET_CURSOR_TYPE_DEFAULT){

        event.StopPropagation();

        this->Book_Manager->Load_Default_Cursor();
     }
}

void MainFrame::Set_Caret_Line_Visible(wxCommandEvent & event)
{
     if(event.GetId() == ID_SET_CARET_LINE_VISIBLE){

       event.StopPropagation();

       this->Book_Manager->Set_Caret_Line_Visible();
     }
}

void MainFrame::Set_Caret_Line_InVisible(wxCommandEvent & event)
{
     if(event.GetId() == ID_SET_CARET_LINE_INVISIBLE){

        event.StopPropagation();

        this->Book_Manager->Set_Caret_Line_InVisible();
     }
}

void MainFrame::Use_Block_Caret(wxCommandEvent & event)
{
     if(event.GetId() == ID_USE_BLOCK_CARET){

       event.StopPropagation();

       this->Book_Manager->Use_Block_Caret();
     }
}

void MainFrame::Use_Default_Caret(wxCommandEvent & event)
{
     if(event.GetId() == ID_USE_DEFAULT_CARET){

        this->Book_Manager->Use_Default_Caret();
     }
}

void MainFrame::Use_Bold_Styling(wxCommandEvent & event)
{
     if(event.GetId() == ID_BOLD_STYLE){

       event.StopPropagation();

       this->is_bold_style_selected = true;

       this->Book_Manager->Use_Bold_Styling();
     }
}

void MainFrame::Save_File_As(wxCommandEvent & event)
{
     if(event.GetId() == ID_SAVE_AS){

        bool is_this_text_file = this->Book_Manager->Is_Current_Page_Text_File();

        if(is_this_text_file){

           wxString File_Path;

           wxString message = wxT("Text files (*.txt)|*.txt|C++ Source Files (*.cpp)|");

           message = message + wxT("*.cpp|C Source files (*.c)|*.c|C header files (*.h)|*.h");

           wxFileDialog * SaveDialog = new wxFileDialog(this,wxT("Save File As ?"), wxEmptyString,

           wxEmptyString, message, wxFD_OVERWRITE_PROMPT | wxFD_SAVE, wxDefaultPosition);

           if(SaveDialog->ShowModal() == wxID_OK) // If the user clicked "OK"
           {
              File_Path = SaveDialog->GetPath();

              this->Book_Manager->Get_Selected_Text_Ctrl()->SaveFile(File_Path);
           }

           SaveDialog->Destroy();
        }
     }
}


void MainFrame::New_File(wxCommandEvent & event)
{
     if(event.GetId() == ID_NEW_FILE){

        wxString File_Path;

        wxFileDialog * File_Dialog = new wxFileDialog(this,wxT("New File"),

               wxEmptyString, wxEmptyString,wxT(""),

               wxFD_OVERWRITE_PROMPT | wxFD_SAVE, wxDefaultPosition);

        if(File_Dialog->ShowModal() == wxID_OK) // If the user clicked "OK"
        {
           File_Path = File_Dialog->GetPath();

           wxTextFile File_Manager(File_Path);

           if(!File_Manager.Exists()){

              File_Manager.Create();
           }

           this->Book_Manager->Add_New_File(File_Path);
        }

        File_Dialog->Destroy();
     }
}

