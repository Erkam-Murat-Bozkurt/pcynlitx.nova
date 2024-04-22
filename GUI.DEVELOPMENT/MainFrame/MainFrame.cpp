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

MainFrame::MainFrame(wxColour theme_clr) : wxFrame((wxFrame * )NULL,-1,"NWINIX",

        wxDefaultPosition, wxSize(1350,1000),wxDEFAULT_FRAME_STYLE )
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

  this->exclamation_mark_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\exclamation_icon.png"),wxBITMAP_TYPE_ANY);

  this->logo_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\logo.png"),wxBITMAP_TYPE_ANY);


  this->Des_Reader = new Descriptor_File_Reader('w');

  this->Des_Reader->Set_Gui_Read_Status(true);


  this->Process_Ptr = new Process_Manager(this,wxID_ANY);

  wxString Builder_Path(wxT("D:\\Pcynlitx_Build_Platform\\CBuild.exe"));

  this->Process_Ptr->Receive_Builder_Path(Builder_Path);


  std::string tabart_font = "Segoe UI";

  std::string face_name = "Segoe UI"; 




  this->Default_Font = new wxFont(9,wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,

                     wxFONTWEIGHT_NORMAL,false,wxString(face_name));

  this->SetFont(*(this->Default_Font));


  this->is_bold_style_selected = false;


  this->SetBackgroundColour(wxColour(240,240,240));

  this->Interface_Manager.SetFlags(wxAUI_MGR_LIVE_RESIZE);


  this->SetSize(wxSize(1350,1000));

  this->SetMinSize(wxSize(1350,1000));

  this->Refresh();

  this->SetDoubleBuffered(true);

  this->SetAutoLayout(true);


  // THE CONSTRUCTION OF THE MENU BAR

  //this->MB_Options = new Menu_Bar_Options();

  //this->SetMenuBar(this->MB_Options->Get_MenuBar());

  //this->MB_Options->Get_MenuBar()->Refresh();
   
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

  this->Central_Pane_Info.MinSize(800,900);



  this->Custom_Main_Panel = new Custom_wxPanel(this,wxID_ANY,wxDefaultPosition,

                            wxDefaultSize,wxColour(200,200,200),&this->Central_Pane_Info);
  

  this->Custom_Main_Panel->SetSize(this->GetClientSize());

  this->Custom_Main_Panel->SetMinSize(wxSize(750,850));

  this->Custom_Main_Panel->Fit();

  this->Custom_Main_Panel->SetAutoLayout(true);


  // THE CONSTRUCTION OF THE NOTEBOOK

  this->Book_Manager = new Custom_Notebook(this,this->Custom_Main_Panel,&this->Interface_Manager,

                       *(this->Default_Font),this->GetClientSize(),theme_clr);

  this->Book_Manager->SetMinSize(wxSize(740,840));


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

                            wxSize(400,this->GetClientSize().y),&this->Interface_Manager,

                            *(this->Default_Font),this->Book_Manager->GetTabCtrlHeight(),theme_clr);

  this->tree_control = this->Dir_List_Manager->GetTreeCtrl();

  this->dir_control = new wxDir;


  this->Dir_List_Manager->Notebook_Ptr = this->Book_Manager;

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


  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_BUTTON,&MainFrame::Open_PopUp_Menu,this,wxID_ANY);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Select_Project_File,this,ID_SELECT_PROJECT_FILE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Show_Project_File,this,ID_SHOW_PROJECT_FILE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::PrintDescriptions,this,ID_PRINT_DESCRIPTIONS);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Open_Empty_Project_File,this,ID_OPEN_EMPTY_PROJECT_FILE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Start_Build_System_Construction,this,ID_RUN_BUILD_SYSTEM_CONSTRUCTOR);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Run_Project_Script_On_Terminal,this,ID_RUN_PROJECT_SCRIPT);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Determine_Source_File_Dependencies,this,ID_DETERMINE_SOURCE_FILE_DEPENDENCIES);


  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Single_File_Script_Construction,this,ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Advance_Single_File_Script_Construction,this,ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR);




  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Increase_Font_Size,this,ID_INCREASE_FONT_SIZE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Decrease_Font_Size,this,ID_DECREASE_FONT_SIZE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Undo_Changes,this,ID_UNDO_CHANGES);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Redo_Changes,this,ID_REDO_CHANGES);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Clear_Text,this,ID_CLEAR_TEXT);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Load_Default_Cursor,this,ID_SET_CURSOR_TYPE_DEFAULT);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Change_Cursor_Type,this,ID_CHANGE_CURSOR_TYPE);


  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Set_Caret_Line_Visible,this,ID_SET_CARET_LINE_VISIBLE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Set_Caret_Line_InVisible,this,ID_SET_CARET_LINE_INVISIBLE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Use_Block_Caret,this,ID_USE_BLOCK_CARET);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Use_Default_Caret,this,ID_USE_DEFAULT_CARET);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Clear_Style,this,ID_CLEAR_STYLE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Reload_Default_Style,this,ID_RELOAD_STYLE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Use_Bold_Styling,this,ID_BOLD_STYLE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Change_Font,this,ID_FONT_CHANGE);




  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Show_Help_Menu,this,ID_SHOW_HELP_MENU);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Use_Default_Caret,this,wxID_ABOUT);



  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::File_Save,this,ID_FILE_SAVE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Save_File_As,this,ID_SAVE_AS);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Open_File,this,ID_OPEN_FILE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::New_File,this,ID_NEW_FILE);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::DirectoryOpen,this,ID_OPEN_TREE_WIEW);

  this->Custom_Main_Panel->GetEventHandler()->Bind(wxEVT_MENU,&MainFrame::Exit,this,ID_EXIT);












  wxRect Book_Manager_Rect(this->Custom_Main_Panel->GetSize());

  this->Book_Manager->Refresh(true,&Book_Manager_Rect);

  

  this->Book_Manager->Update();



  this->intro_page_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\Intro_File_Back.png"),wxBITMAP_TYPE_ANY);


  this->background_figure = new wxStaticBitmap(this->Book_Manager,wxID_ANY,*this->intro_page_bmp);

  this->background_figure->SetBackgroundColour(wxColour(240,240,240));

  wxSize figure_size = this->background_figure->GetSize();

  wxSize main_frame_size = this->GetSize();

  int x_pos = (main_frame_size.GetX() - figure_size.GetX())/2 - 70;

  int y_pos = (main_frame_size.GetY() - figure_size.GetY())/2;

  this->background_figure->SetPosition(wxPoint(x_pos,y_pos));


  this->background_figure->Show(false);

  this->Book_Manager->Receive_Intro_Image(this->background_figure);

  this->Book_Manager->OpenIntroPage();

  wxString Help_Page_Path = wxT("D:\\Pcynlitx_Build_Platform\\Introduction.txt");

  this->Book_Manager->Open_File(Help_Page_Path);

  size_t notebook_index = this->Book_Manager->GetIndex_FromPath(Help_Page_Path);

  this->Book_Manager->Get_NoteBook_Pointer()->SetPageText(notebook_index,wxT("Introduction"));

  this->Book_Manager->SelectIntroPage();

  this->Update();



  this->Raise();

  this->PostSizeEvent();

  this->Interface_Manager.Update();

  this->opr_sis = 'w';
}

MainFrame::~MainFrame()
{
   this->Interface_Manager.UnInit();

   this->Close(true);
}



void MainFrame::Open_PopUp_Menu(wxCommandEvent & event){

     if(event.GetId() == ID_OPEN_POPUP_MENU ){

        event.Skip(true);

        int x,y;

        this->Custom_Main_Panel->Start_Button->GetPosition(&x,&y);

        this->Custom_Main_Panel->bottom_window->PopupMenu(this->Custom_Main_Panel->Main_Menu,x,y);
     }
}


void MainFrame::OpenSettings(wxCommandEvent & event){

     if(event.GetId() == ID_OPEN_SETTINGS){

       if(this->is_project_file_selected){

          this->Multi_DataPanel = new Custom_Multi_DataPanel(this,wxID_ANY);

          this->Multi_DataPanel->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

          this->Multi_DataPanel->Construct_Description_Panel();

          this->Multi_DataPanel->Load_Data_From_Descriptor_File_To_Panel();
       }
       else{

            this->Descriptor_File_Selection_Check();
       }
     }
}


void MainFrame::File_Save(wxCommandEvent & event){

     if(event.GetId() == ID_FILE_SAVE){

        if(this->Book_Manager->Get_Open_File_Number() > 0){

           this->Book_Manager->File_Save();
        }
        else{

            wxString message =  wxT(" This is no any file currently open!");
            
            message += "\n A file must be openned.";
            
            Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,message,
            
            wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
            *this->exclamation_mark_bmp, wxDefaultPosition);

            dial->ShowModal();

            delete dial;            
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
     dc.SetBrush(wxColour(240,240,240));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+10,rect.GetHeight()+10);
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



void MainFrame::Exit(wxCommandEvent & event){

     if(event.GetId() == ID_EXIT){

        this->Destroy();
     }
}

void MainFrame::Show_Project_File(wxCommandEvent & event){

     if(event.GetId() == ID_SHOW_PROJECT_FILE){

        event.Skip(true);

        if(this->is_project_file_selected){

           bool is_project_file_currently_open = false;

           for(int i=0;i<20;i++){

               wxString Path_Data =  this->Book_Manager->Get_Notebook_Page_File_Path(i);

               if(Path_Data == this->Descriptor_File_Path){

                  is_project_file_currently_open = true;

                  break;
               }
            }

            if(is_project_file_currently_open){

                this->Book_Manager->Select_File(this->Descriptor_File_Path);

                this->Book_Manager->Clear_Text_Control_Style(this->Book_Manager->Get_Selected_Text_Ctrl());
            }
            else{

                  this->Book_Manager->Open_File(this->Descriptor_File_Path);

                  this->Book_Manager->Clear_Text_Control_Style(this->Book_Manager->Get_Selected_Text_Ctrl());
            }
        }
        else{

             this->Descriptor_File_Selection_Check();
        }
     }
}

void MainFrame::Run_Project_Script_On_Terminal(wxCommandEvent & event){

     if(event.GetId() == ID_RUN_PROJECT_SCRIPT){

        if(this->is_project_file_selected){

           if(this->Control_Build_Script_Existance()){

              std::string project_construction_dir = this->Des_Reader->Get_Warehouse_Location();

              std::string project_script_path = project_construction_dir + "\\Project_Build_Script.ps1";

              wxString run_cmd = wxT("powershell.exe ") + wxString(project_script_path);

              wxExecute(run_cmd,wxEXEC_SYNC | wxEXEC_SHOW_CONSOLE);

              wxString Warehouse_Dir_Path = project_construction_dir + wxT("\\WAREHOUSE");

              wxString Library_Directory_Path = project_construction_dir + wxT("\\WAREHOUSE\\LIBRARY.FILES");

              wxString Object_Directory_Path = project_construction_dir + wxT("\\WAREHOUSE\\OBJECT.FILES");

              if(this->Dir_List_Manager->Get_Panel_Open_Status()){

                 this->Dir_List_Manager->Close_Directory_Pane();

                 this->Dir_List_Manager->Load_Project_Directory(wxString(project_construction_dir));

                 this->Dir_List_Manager->Expand_Path(Warehouse_Dir_Path);

                 this->Dir_List_Manager->Expand_Path(Library_Directory_Path);
              }
              else{

                 this->Dir_List_Manager->Load_Project_Directory(wxString(project_construction_dir));

                 this->Dir_List_Manager->Expand_Path(Warehouse_Dir_Path);

                 this->Dir_List_Manager->Expand_Path(Library_Directory_Path);
              }

              this->Interface_Manager.Update();
           }
           else{

                  wxString Message = "Build system script is not exist!";

                  Message = Message + "\nThe build system construction";

                  Message = Message + "\nmust be performed before this";

                  Message = Message + "\noperation";

            
                  Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
                  wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
                  *this->exclamation_mark_bmp, wxDefaultPosition);

                  dial->ShowModal();

                  delete dial;
           }
        }
        else{

              this->Descriptor_File_Selection_Check();
        }
     }
}


void MainFrame::Show_Help_Menu(wxCommandEvent & event)
{
     if(event.GetId() == ID_SHOW_HELP_MENU){

        event.Skip(false);

        wxString message = wxT("ERKAM MURAT BOZKURT\n\n");

        message = message + wxT("PCYNLITX Software, Istanbul / TURKEY\n\n");

        message = message + wxT("M.Sc. Control Sysytem Engineering\n\n");

        message = message + wxT("http://www.nwinix.com\n\n");

        message = message + wxT("help@nwinix.com\n\n");


        Help_Page_Constructor * dial = new Help_Page_Constructor(this,message,
            
            wxT("DEVELOPER:\n"),wxID_ANY,
               
            wxT("THE HELP FOR PLATFORM"),
               
            *this->logo_bmp, wxDefaultPosition,wxSize(600,750));
          
        dial->NoteBook_Ptr = this->Book_Manager;

        if(dial->ShowModal() == ID_SHOW_HELP_MENU){

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

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           if(!this->Dir_List_Manager->Get_Panel_Open_Status()){

              this->Dir_List_Manager->Load_Project_Directory(DirectoryPath);
           }

           this->Interface_Manager.Update();
        }

        this->tree_control->Update();

        this->PaintNow(this);

        this->Update();
     }
}



void MainFrame::Single_File_Script_Construction(wxCommandEvent & event){
    
     if(event.GetId() == ID_RUN_SINGLE_FILE_SCRIPT_CONSTRUCTOR){

        event.Skip(false);

        if(this->is_project_file_selected){

           if(!this->Control_Project_File_Syntax()){

               this->Multi_DataPanel = new Custom_Multi_DataPanel(this,wxID_ANY);

               this->Multi_DataPanel->Create_Exe_Script_Panel();

               //if(this->Multi_DataPanel->ShowModal() == wxID_OK ){
               
               //}

               char strategy = 's';

               this->Single_File_Script_Construction_Executer(this->Multi_DataPanel->FilePath,
           
               this->Multi_DataPanel->ExeFileName,strategy);
           }
           else{

               this->Print_Project_File_Syntax_Error();
           }
        }
        else{

           this->Descriptor_File_Selection_Check();
        }        
     }
}


void MainFrame::Determine_Source_File_Dependencies(wxCommandEvent & event){

     if(event.GetId() == ID_DETERMINE_SOURCE_FILE_DEPENDENCIES){
     
        if(this->is_project_file_selected){

           if(!this->Control_Project_File_Syntax()){

               wxString FilePATH;

               this->Select_File(FilePATH,wxT("Select source file path"));

               if(!FilePATH.empty()){

                  this->fork_process 
          
                   = new std::thread(MainFrame::Run_Source_File_Dependency_Determination_Process,this,FilePATH);


                  this->Progress_Dialog = new Custom_Progress_Dialog(this,wxID_ANY,wxT("PROCESS REPORT"),wxDefaultPosition);

                  this->Progress_Dialog->Construct_Text_Panel(wxT("Process Output"),20);

                  this->Progress_Dialog->SetBoldFont();

                  this->Progress_Dialog->AppendText_To_TextCtrl(wxT("\n\n    SOURCE FILE DEPENDENCY DETERMINATION STARTED:"));

                  this->Progress_Dialog->SetLightFont();

                  this->Progress_Dialog->ShowModal();
           
                  this->depPrinter = new Dependency_Tree_Printer(this);

                  this->depPrinter->Construct_Tree_Panel(wxT("DEPENDENCY TREE"));

                  this->print_to_tree_ctrl = new std::thread(MainFrame::Print_File_Dependency_to_tree_control,this);

                  this->print_to_tree_ctrl->detach();

                  this->depPrinter->PrintDependencyTree();

                  this->fork_process->join();
               }
           }
           else{

               this->Print_Project_File_Syntax_Error();
           }
        }
        else{

            this->Descriptor_File_Selection_Check();
        }
     }

}


void MainFrame::Run_Source_File_Dependency_Determination_Process(wxString FilePATH){
     
     this->Process_Ptr->Find_Source_File_Dependency_Determination_Command(FilePATH);

     this->Process_Ptr->Fork_Process_With_Named_Pipe_Connection(this->Process_Ptr->Get_Process_Command());
     
     this->print_file_dependency = new std::thread(MainFrame::Print_File_Dependency_Output,this);

     this->print_file_dependency->join();

}

void MainFrame::Print_File_Dependency_Output(){

     std::string pipe_string = this->Process_Ptr->GetNamedPipeString();

     int new_line_number = 0, start_point = 0, progress = 0;

     for(size_t i=0;i<pipe_string.size();i++){

         if(pipe_string[i] == '\n'){

             new_line_number++;

             std::string str_line;

             for(size_t k=start_point;k<i;k++){

                 str_line.push_back(pipe_string[k]);
             }

             this->Progress_Dialog->AppendText_To_TextCtrl(wxString(str_line));


             progress +=4;

             this->Progress_Dialog->GetDialogAddress()->SetValue(progress);

             start_point = i;
         }
         else{

             if(new_line_number>0){

                new_line_number--;
             }
         }

         if(new_line_number==3){

            this->Progress_Dialog->GetDialogAddress()->SetValue(20);

            break;
         }
     }
}



void MainFrame::Print_File_Dependency_to_tree_control(){

      std::string pipe_string = this->Process_Ptr->GetNamedPipeString();

      size_t data_start_point = 0;

      int new_line_number = 0;

      for(size_t i=0;i<pipe_string.size();i++){

         if(pipe_string[i] == '\n'){

             new_line_number++;
         }
         else{

             if(new_line_number>0){

                new_line_number--;
             }
         }

         if(new_line_number==3){

           data_start_point = i;

           break;
         }
      }

         

      while(((pipe_string[data_start_point] == '\n') 
      
            || (pipe_string[data_start_point] == ' '))){

            data_start_point++;
      }


      int item_number = 0;

      wxDataViewItem rootId;

      for(size_t i=data_start_point;i<pipe_string.size();i++){

          std::string src_name;

          do {

               src_name.push_back(pipe_string[i]);

               i++;

          }while(pipe_string[i]!= '\n');

          if(item_number == 0){

             this->depPrinter->GetTreeCtrl()->AppendContainer(rootId,src_name,-1,-1,NULL);

             item_number++;
          }
          else{

              this->depPrinter->GetTreeCtrl()->AppendItem(rootId,src_name,-1,NULL);

              item_number++;
          }
      }

      this->depPrinter->GetTreeCtrl()->Expand(rootId);
}

void MainFrame::Advance_Single_File_Script_Construction(wxCommandEvent & event){

     if(event.GetId() == ID_RUN_ADVANCE_SINGLE_FILE_SCRIPT_CONSTRUCTOR){

        event.Skip(false);

        if(this->is_project_file_selected){

           if(!this->Control_Project_File_Syntax()){

              this->Multi_DataPanel = new Custom_Multi_DataPanel(this,wxID_ANY);

              this->Multi_DataPanel->Create_Exe_Script_Panel();

              
              char strategy = 'a';

              this->Single_File_Script_Construction_Executer(this->Multi_DataPanel->FilePath,
           
              this->Multi_DataPanel->ExeFileName,strategy);
           }
           else{

               this->Print_Project_File_Syntax_Error();
           }
        }
        else{

           this->Descriptor_File_Selection_Check();
        }        
     }
}


void MainFrame::Single_File_Script_Construction_Executer(wxString FilePath, 

     wxString FileName, char strategy){

     if(!FilePath.empty() && !FileName.empty()){
        
         this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());

         this->Des_Reader->Read_Descriptor_File();

         if(this->Des_Reader->Get_Gui_Read_Success_Status()){

            this->Determine_Executable_File_Script_Construction_Point(FileName);

            wxString Construction_Point(this->Executable_File_Script_Construction_Point);
 
            std::string src_path = FilePath.ToStdString();

            std::string exe_name = FileName.ToStdString();

            this->Process_Ptr->Exec_Cmd_For_Single_Src_File(src_path,exe_name,strategy);

            wxString label = wxT("BUILD SYSTEM CONSTRUCTION FOR A SOURCE FILE");

            wxString start_text = wxT("\n\n   EXECUTABLE MAKEFILE CONSTRUCTION STARTED");

            this->Start_Construction_Process(label,this->Executable_File_Script_Construction_Point,start_text);
         }
         else{


            std::string error_message = this->Des_Reader->Get_Error_Message();

            wxString message(error_message);
            
            Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,message,
            
            wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX BUILD SYSTEM COSTRUCTION REPORT"),
               
            *this->exclamation_mark_bmp, wxDefaultPosition);

            dial->ShowModal();

            delete dial;
         }
      }
}


void MainFrame::Start_Build_System_Construction(wxCommandEvent & event){

  if(event.GetId() == ID_RUN_BUILD_SYSTEM_CONSTRUCTOR)
  {
    event.Skip(false);

    if(this->is_project_file_selected){

       if(!this->Control_Project_File_Syntax()){

           this->Process_Ptr->Determine_Build_System_Initialization_Command();

           this->Des_Reader->Read_Descriptor_File();

           if(this->Des_Reader->Get_Gui_Read_Success_Status()){

              std::string warehose_word = "\\WAREHOUSE";

              this->Warehouse_Location = this->Des_Reader->Get_Warehouse_Location() + warehose_word;


              wxString label = wxT("BUILD SYSTEM CONSTRUCTION PROCESS");

              wxString start_text = wxT("\n\n   BUILD SYSTEM CONSTRUCTION STARTED");

              this->Start_Construction_Process(label,this->Warehouse_Location,start_text);
            }
            else{

              std::string error_message = this->Des_Reader->Get_Error_Message();

              wxString message(error_message);
            

              Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,message,
            
              wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX BUILD SYSTEM COSTRUCTION REPORT"),
               
              *this->exclamation_mark_bmp, wxDefaultPosition);

              dial->ShowModal();

              delete dial;
            }
       }
       else{

           this->Print_Project_File_Syntax_Error();
       }
    }
    else{

         this->Descriptor_File_Selection_Check();
    }
  }
}


void MainFrame::Start_Construction_Process(wxString label, 

     wxString dir_open, wxString start_text){
      
     this->Progress_Bar_Start_status = false;

     this->Child_Process_End_Status  = false;

     this->Child_Process_Started_to_Execution = false;

     this->is_pipe_ready = false;

     this->progres_wait = false;

     this->fork_wait = false;

     this->read_wait = false;

     this->Process_Output = new Custom_ProcessOutput(this,wxID_ANY,label);

     this->Process_Output->Receive_System_Interface(&this->SysInt);

     this->Process_Output->Directory_List_Show_Cond(true);

     this->Process_Output->Receive_Process_End_Status(&this->Child_Process_End_Status);

     this->Process_Output->Receive_Directory_Open_Location(dir_open);

     this->Process_Output->Receive_Tree_View_Panel(this->Dir_List_Manager);

     int max=20;
     
     this->Process_Output->Construct_Output(max);


     char * cmd = this->Process_Ptr->Get_Process_Command();

     this->fork_process = new std::thread(MainFrame::ForkProcess,this,cmd,start_text);

     this->fork_process->detach();

}



void MainFrame::ForkProcess(char * cmd, wxString start_text){

     std::unique_lock<std::mutex> lck(this->mtx);

     lck.unlock();


     this->SysInt.CreateProcessWith_NamedPipe_From_Parent(cmd);


     this->progress_point = 0;

     this->read_process_output = new std::thread(MainFrame::ReadProcessOutput,this,start_text);

     this->read_process_output->detach();


     lck.lock();

     if(!this->Child_Process_End_Status){

         this->fork_wait = true;

         this->cv_fork.wait(lck);

         this->fork_wait = false;

         lck.unlock();
     }
     else{

         lck.unlock();
     }


     this->SysInt.Close_Parent_Handles_For_Named_Pipe_Connection();

}




void MainFrame::PrintDescriptions(wxCommandEvent & event){

     if(event.GetId() == ID_PRINT_DESCRIPTIONS)
     {
        event.Skip(false);

        if(this->is_project_file_selected){
      
           if(!this->Control_Project_File_Syntax())
           {

               this->Descriptions_Printer = new Project_Descriptions_Printer(this,wxID_ANY,
           
                                         wxT("THE PROJECT DESCRIPTION LIST"));

               this->Descriptions_Printer->Receive_Descriptor_File_Path(this->Descriptor_File_Path);
               
               this->Descriptions_Printer->Receive_Descriptor_File_Reader(this->Des_Reader);

               this->Descriptions_Printer->Read_Descriptions();

               this->Descriptions_Printer->Print_Descriptions();
           }
           else{

                this->Print_Project_File_Syntax_Error();
           }
        }
        else{

            wxString Message = "Descriptor file was not selected";

            Message = Message + "\nPlease select a descriptor file or";

            Message = Message + "\nconstruct an empty descriptor file";
            
            Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
               wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
               *this->exclamation_mark_bmp, wxDefaultPosition);

            dial->ShowModal();
        }
     }      
}


void MainFrame::ReadProcessOutput(wxString start_text){

     std::unique_lock<std::mutex> lck(this->mtx);

     lck.unlock();


     int max=20;

     do{

        if(this->SysInt.IsPipeReadytoRead()){

            break;
        }
        else{

            sleep(0.05);
        }

     }while(!this->SysInt.IsPipeReadytoRead());



     this->Process_Output->SetBoldFont();

     this->Process_Output->GetTextControl()->AppendText(start_text);

     this->Process_Output->SetLightFont();


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

        this->Process_Output->PrintProcessOutput(text);

        if(this->Process_Output->GetWindowsOpenStatus()){

           this->Process_Output->GetDialogAddress()->SetValue(this->progress_point);
        }
 

        if(!this->SysInt.IsChildProcessStillAlive()){

            if(this->Process_Output->GetWindowsOpenStatus()){

               this->Process_Output->GetDialogAddress()->SetValue(max);
            }

            break;
        }
     } 


     lck.lock();

     this->Child_Process_End_Status = true;

     lck.unlock();


     do{

         this->cv_fork.notify_all();

         sleep(0.05);

     }while(this->fork_wait);
}



void MainFrame::Open_Empty_Project_File(wxCommandEvent & event)
{
  if(event.GetId() == ID_OPEN_EMPTY_PROJECT_FILE)
  {

     event.Skip(false);

     wxDirDialog dlg(NULL, "Select Descriptor File Location", "",

           wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

     dlg.CenterOnScreen(wxBOTH);


     if(dlg.ShowModal() == wxID_OK){

        wxString construction_dir =dlg.GetPath();

        this->Descriptor_File_Path = construction_dir + wxT("\\Pcb_Descriptor.txt");

        this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());

        wxString shell_command = "D:\\Pcynlitx_Build_Platform\\CBuild.exe " 
        
        + construction_dir + " -ed";

        this->Process_Ptr->Fork_Process(shell_command);

        this->Process_Ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

       if(!this->Descriptor_File_Path.empty()){

           this->is_project_file_selected = true;
        }
     }
   }
}

void MainFrame::Select_Project_File(wxCommandEvent & event)
{
     if(event.GetId() == ID_SELECT_PROJECT_FILE ){

       event.Skip(false);

       this->Freeze();

       Project_File_Selection_Window * window = new Project_File_Selection_Window(this,wxID_ANY);

       window->Receive_Descriptor_File_Path(&this->Descriptor_File_Path);

       window->Receive_Process_Manager(this->Process_Ptr);

       window->Receive_Project_File_Selection_Status(&this->is_project_file_selected);

       window->ShowModal();

       this->Thaw();

       this->Des_Reader->Receive_Descriptor_File_Path(this->Descriptor_File_Path.ToStdString());

       this->Process_Ptr->Receive_Descriptor_File_Path(this->Descriptor_File_Path);
   }
}


void MainFrame::Select_File(wxString & FilePATH, wxString Title){

     wxFileDialog * openFileDialog

              = new wxFileDialog(this,Title);

     openFileDialog->CenterOnScreen(wxBOTH);

     if (openFileDialog->ShowModal() == wxID_OK){

         FilePATH = openFileDialog->GetPath();

         wxDir Dir_Ctrl;

         if(Dir_Ctrl.Exists(FilePATH)){

            Dir_Ctrl.Open(FilePATH);

            if(Dir_Ctrl.IsOpened()){

               wxString Message = "This is a directory!";

               Message = Message + "\nA file must be selected .";
            
               Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
               wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
               *this->exclamation_mark_bmp, wxDefaultPosition);

               dial->ShowModal();
            }
         }
     }
     else{

          FilePATH.clear();

          FilePATH.shrink_to_fit();
     }

     delete openFileDialog;
}



void MainFrame::Open_File(wxCommandEvent & event){

     if(event.GetId() == ID_OPEN_FILE){

        wxString FilePATH;

        FilePATH.clear();

        wxString title(wxT("Select the file"));

        this->Select_File(FilePATH,title);

        if(!FilePATH.empty()){

           this->Book_Manager->Open_File(FilePATH);
        }
     }
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

       if(!this->is_project_file_selected){

          this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("PROJECT-ROOT-DIR"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("Git repository location"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,false);
       }
     }
}


void MainFrame::Enter_Header_File_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_HEADER_FILE_LOCATION){

        if(!this->is_project_file_selected){

            this->Descriptor_File_Selection_Check();
        }
        else{


            wxString DataType(wxT("INCLUDE-DIRECTORIES"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("HEADER FILE LOCATIONS"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,false);

        }
     }
}

void MainFrame::Enter_Source_File_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_SOURCE_FILE_LOCATION){

        if(!this->is_project_file_selected){

            this->Descriptor_File_Selection_Check();
        }
        else{

            wxString DataType(wxT("SOURCE-FILE-DIRECTORIES"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("SOURCE FILE LOCATIONS"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,false);
        }
     }
}

void MainFrame::Enter_Library_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_LIBRARY_LOCATION){

       if(!this->is_project_file_selected){

           this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("LIBRARY-DIRECTORIES"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("LIBRARY PATHS"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,false);
       }
     }
}

void MainFrame::OpenTerminal(wxCommandEvent & event)
{
     if(event.GetId() == ID_OPEN_TERMINAL){

        wxProcess * proc = new wxProcess(this,wxID_ANY);

        wxExecute(wxT("powershell.exe"),wxEXEC_SYNC | wxEXEC_SHOW_CONSOLE,proc);


        proc->Redirect();

        long int pid = proc->GetPid();

        int process_exit_status = 0;

        proc->OnTerminate(pid,process_exit_status);

     }
}


void MainFrame::Enter_Library_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_LIBRARY_NAME){

       if(!this->is_project_file_selected){

          this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("LIBRARY-FILES"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("LIBRARY PATHS"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,true,false);
       }
     }
}

void MainFrame::Enter_Warehouse_Location(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_CONSTRUCTION_POINT){

       if(!this->is_project_file_selected){

         this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("PROJECT-WAREHOUSE-LOCATION"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("Repo Warehouse Location"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,false);
       }
     }
}

void MainFrame::Enter_Exe_File_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_EXE_FILE_NAME){

        if(!this->is_project_file_selected){

           this->Descriptor_File_Selection_Check();
        }
        else{

           wxString DataType(wxT("EXECUTABLE-FILE-NAMES"));

           wxString Title(wxT("INSERT YOUR CHOICE"));

           wxString Text(wxT("Executable File Name"));

           this->Custom_DataPanel_Constructor(DataType,Title,Text,false,true);
        }
     }
}

void MainFrame::Enter_Main_File_Name(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_MAIN_FILE_NAME){

       if(!this->is_project_file_selected){

           this->Descriptor_File_Selection_Check();
       }
       else{

           wxString DataType(wxT("MAIN-FILE-NAMES"));

           wxString Title(wxT("INSERT YOUR CHOICE"));

           wxString Text(wxT("Main file name"));

           this->Custom_DataPanel_Constructor(DataType,Title,Text,false,true);
       }
     }
}

void MainFrame::Enter_Standard(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_C_STANDART){

       if(!this->is_project_file_selected){

           this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("C++-STANDARD"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("C++ Standard"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,true);
       }
     }
}

void MainFrame::Enter_Options(wxCommandEvent & event)
{
     if(event.GetId() == ID_INPUT_OPTIONS){

       if(!this->is_project_file_selected){

           this->Descriptor_File_Selection_Check();
       }
       else{

            wxString DataType(wxT("OPTIONS"));

            wxString Title(wxT("INSERT YOUR CHOICE"));

            wxString Text(wxT("Compiler Options"));

            this->Custom_DataPanel_Constructor(DataType,Title,Text,false,true);
       }
     }
}

void MainFrame::Descriptor_File_Selection_Check(){
      
     wxString Message = "Descriptor file was not selected";

     Message = Message + "\nPlease select a descriptor file or";

     Message = Message + "\nconstruct an empty descriptor file";
            
     Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
         wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
         *this->exclamation_mark_bmp, wxDefaultPosition);

         dial->ShowModal();

     delete dial;
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

           this->Book_Manager->Get_Selected_Text_Ctrl()->EndUndoAction();

           this->Book_Manager->Get_Selected_Text_Ctrl()->Undo();

           this->Book_Manager->Get_Selected_Text_Ctrl()->BeginUndoAction();
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

        File_Dialog->CenterOnScreen(wxBOTH);


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


void MainFrame::OpenFile(wxCommandEvent & event)
{
     if(event.GetId() == ID_OPEN_FILE){

        wxString File_Path;

        wxFileDialog * File_Dialog = new wxFileDialog(this,wxT("New File"),

               wxEmptyString, wxEmptyString,wxT(""),

               wxFD_OVERWRITE_PROMPT | wxFD_SAVE, wxDefaultPosition);

        File_Dialog->CenterOnScreen(wxBOTH);

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




void MainFrame::Change_Font(wxCommandEvent & event){

     if(event.GetId() == ID_FONT_CHANGE){

        wxFontData data;

        data.SetInitialFont(*this->Default_Font);

        wxFontDialog dialog(this,data);

        dialog.Centre(wxBOTH);

        if(dialog.ShowModal() == wxID_OK)
        {     
           wxFontData FData = dialog.GetFontData();
           
           wxFont SelectedFont = FData.GetChosenFont();

           this->Book_Manager->Set_Font(SelectedFont);
        }
     }
}






void MainFrame::Determine_Executable_File_Script_Construction_Point(wxString FileName){

     this->Warehouse_Location = this->Des_Reader->Get_Warehouse_Location();


     std::string warehouse_word  ="WAREHOUSE";

     this->Executable_File_Script_Construction_Point = this->Warehouse_Location;

     if(this->opr_sis == 'w'){

        if(this->Executable_File_Script_Construction_Point.back()!='\\'){

            this->Executable_File_Script_Construction_Point.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->Executable_File_Script_Construction_Point.back()!='/'){

            this->Executable_File_Script_Construction_Point.push_back('/');
        }
     }


     for(size_t i=0;i<warehouse_word.length();i++){

         this->Executable_File_Script_Construction_Point.push_back(warehouse_word[i]);
     }

     if(this->opr_sis == 'w'){

        if(this->Executable_File_Script_Construction_Point.back()!='\\'){

            this->Executable_File_Script_Construction_Point.push_back('\\');
        }
     }

     if(this->opr_sis == 'l'){

        if(this->Executable_File_Script_Construction_Point.back()!='/'){

            this->Executable_File_Script_Construction_Point.push_back('/');
        }
     }

     size_t name_size = FileName.length();

     for(size_t i=0;i<name_size;i++){
 
         char upper_case = toupper(FileName[i]);

         if(upper_case == '.'){

            upper_case = '_';
         }

         this->Executable_File_Script_Construction_Point.push_back(upper_case);
     }

     std::string dir_add_word = "_BUILDER";

     for(size_t i=0;i<dir_add_word.length();i++){

         this->Executable_File_Script_Construction_Point.push_back(dir_add_word[i]);
     }
}


bool MainFrame::Control_Build_Script_Existance(){

     bool is_exist = false;

     this->Des_Reader->Read_Descriptor_File();

     std::string warehouse_Location = this->Des_Reader->Get_Warehouse_Location();

     std::string script_path = warehouse_Location + "\\Project_Build_Script.ps1";

     Cpp_FileOperations FileManager;

     if(FileManager.Is_Path_Exist(script_path)){

        is_exist = true;

        return is_exist;          
     }

     return is_exist;
}


void MainFrame::Custom_DataPanel_Constructor(wxString DataType, wxString Title, wxString Text,

     bool file_selection, bool text_enter_status){
      
     this->DataPanel_Pointer = new Custom_DataPanel(this,wxSize(700,400));

     this->DataPanel_Pointer->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

     this->DataPanel_Pointer->File_Slection_Status(file_selection);

     this->DataPanel_Pointer->Receive_Descriptor_File_Path(this->Descriptor_File_Path);

     this->DataPanel_Pointer->Receive_Text_Enter_Status(text_enter_status);

     this->DataPanel_Pointer->Receive_Data_Type(DataType);

     this->DataPanel_Pointer->SetTitle(Title);

     this->DataPanel_Pointer->AppendTextColumn(Text);

     this->DataPanel_Pointer->Show();

     this->DataPanel_Pointer->GetDataViewListCtrl()->Show();
}


bool MainFrame::Control_Project_File_Syntax(){

     bool syntax_error_status = false;

     this->Des_Reader->Clear_Dynamic_Memory();

     this->Des_Reader->Set_Gui_Read_Status(true);

     std::string des_path = this->Descriptor_File_Path.ToStdString();

     this->Des_Reader->Receive_Descriptor_File_Path(des_path.c_str());

     this->Des_Reader->Read_Descriptor_File();

     if(this->Des_Reader->Get_Syntax_Error_Status()){

         syntax_error_status = true;
     }

     return syntax_error_status;
}

void MainFrame::Print_Project_File_Syntax_Error(){

     wxString Message = "The project file is invalid or ";

     Message = Message + "\nthere is an error on declerations!";

     Message = Message + "\nPlease check your project file and ";

     Message = Message + "\ndeclerations ";
            
     Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
     wxT("ERROR MESSAGE:\n"),wxID_ANY,wxT("NWINIX OPERATION REPORT"),
               
         *this->exclamation_mark_bmp, wxDefaultPosition);

         dial->ShowModal();
}
