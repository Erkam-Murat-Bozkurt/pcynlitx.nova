

#include "Custom_Multi_DataPanel.hpp"


BEGIN_EVENT_TABLE(Custom_Multi_DataPanel,wxFrame )

    EVT_BUTTON(ID_INSERT_ITEM_FOR_PATH,Custom_Multi_DataPanel::Insert_Data_For_Path)

    EVT_BUTTON(ID_INSERT_ITEM_FOR_NAME,Custom_Multi_DataPanel::Insert_Data_For_Name)

    EVT_BUTTON(ID_SAVE_MAKE_FILE_DATA,Custom_Multi_DataPanel::Save_MakeFile_Data)


    EVT_BUTTON(ID_INSERT_GIT_REPO_DIR,Custom_Multi_DataPanel::Inser_Git_Repo_Dir)

    EVT_BUTTON(ID_INSERT_CONSTRUCTION_POINT,Custom_Multi_DataPanel::Insert_Construction_Point)

    EVT_BUTTON(ID_INSERT_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Insert_Header_File_Location)

    EVT_BUTTON(ID_INSERT_SRC_LOCATION,Custom_Multi_DataPanel::Insert_Source_File_Location)

    EVT_BUTTON(ID_INSERT_LIB_DIRECTORIES,Custom_Multi_DataPanel::Insert_Library_Location)

    EVT_BUTTON(ID_INSERT_LIBRARIES,Custom_Multi_DataPanel::Insert_Library)

    EVT_BUTTON(ID_INSERT_STANDART,Custom_Multi_DataPanel::Insert_Standart)

    EVT_BUTTON(ID_INSERT_OPTIONS,Custom_Multi_DataPanel::Insert_Option)




    EVT_BUTTON(ID_SAVE_GIT_REPO_DIR,Custom_Multi_DataPanel::Save_Git_Repo_Dir)

    EVT_BUTTON(ID_SAVE_CONSTRUCTION_POINT,Custom_Multi_DataPanel::Save_Construction_Point)

    EVT_BUTTON(ID_SAVE_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Save_Header_File_Location)

    EVT_BUTTON(ID_SAVE_SRC_LOCATION,Custom_Multi_DataPanel::Save_Source_File_Location)

    EVT_BUTTON(ID_SAVE_LIB_DIRECTORY,Custom_Multi_DataPanel::Save_Library_Directory)

    EVT_BUTTON(ID_SAVE_LIBRARY_NAME,Custom_Multi_DataPanel::Save_Library_Name)

    EVT_BUTTON(ID_SAVE_STANDART,Custom_Multi_DataPanel::Save_Standart)

    EVT_BUTTON(ID_SAVE_OPTIONS,Custom_Multi_DataPanel::Save_Option)




    EVT_BUTTON(ID_REMOVE_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Remove_Header_File_Location)

    EVT_BUTTON(ID_REMOVE_SRC_LOCATION,Custom_Multi_DataPanel::Remove_Source_File_Location)
  
    EVT_BUTTON(ID_REMOVE_LIB_DIRECTORY,Custom_Multi_DataPanel::Remove_Library_Directory)
  
    EVT_BUTTON(ID_REMOVE_LIBRARY_NAME,Custom_Multi_DataPanel::Remove_Library_Name)
  


    EVT_BUTTON(ID_CLEAR_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Clear_Header_File_Locations)

    EVT_BUTTON(ID_CLEAR_SRC_LOCATIONS,Custom_Multi_DataPanel::Clear_Source_File_Locations)
  
    EVT_BUTTON(ID_CLEAR_LIB_DIRECTORIES,Custom_Multi_DataPanel::Clear_Library_Directories)
  
    EVT_BUTTON(ID_CLEAR_LIBRARY_NAMES,Custom_Multi_DataPanel::Clear_Library_Names)


    EVT_BUTTON(ID_CLOSE_DESCRIPTION_PANEL,Custom_Multi_DataPanel::Close_Description_Panel)

    EVT_BUTTON(ID_SAVE_PANEL_DESCRIPTIONS,Custom_Multi_DataPanel::Save_Panel_Descriptions)

    EVT_BUTTON(ID_CLEAR_PANEL_DESCRIPTIONS,Custom_Multi_DataPanel::Clear_Panel_Descriptions)


    EVT_PAINT(Custom_Multi_DataPanel::OnPaint)

END_EVENT_TABLE()



Custom_Multi_DataPanel::Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint & pos, const wxSize & size, long style, char opr_sis) : 
   
   wxFrame(parent,id,title,pos,size, style), Data_Recorder(opr_sis), Des_Reader(opr_sis)
{
     this->Parent_Frame = parent;

     this->Des_Reader.Set_Gui_Read_Status(true);

     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetTitle(wxT("NWINIX BUILD SYSTEM DESCRIPTION PANEL"));


     this->save_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\save_success_icon.png"),wxBITMAP_TYPE_ANY);

     this->exclamation_mark_bmp 
  
      = new wxBitmap(wxT("D:\\Pcynlitx_Build_Platform\\icons\\exclamation_icon.png"),wxBITMAP_TYPE_ANY);

     this->SetBackgroundColour(wxColour(250,250,250));

     this->Data_Recorder.parent = this;

     this->Data_Save_Status = false;
}


Custom_Multi_DataPanel::~Custom_Multi_DataPanel(){

}

void Custom_Multi_DataPanel::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(220,220,220));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_Multi_DataPanel::OnPaint(wxPaintEvent & event)
{
     event.Skip(false);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}


void Custom_Multi_DataPanel::Receive_Descriptor_File_Path(wxString path){

     this->Descriptor_File_Path = path;

     this->Data_Recorder.Receive_Descriptor_File_Path(path.ToStdString());

     this->Des_Reader.Receive_Descriptor_File_Path(path.ToStdString());
}


void Custom_Multi_DataPanel::Construct_MultiData_Panel(int num){

     this->Panel_Number = num;

     this->listctrls = new wxDataViewListCtrl * [2*this->Panel_Number];

     this->Insert_Buttons   = new wxButton    * [2*this->Panel_Number];

     this->DataPanel_Sizers = new wxBoxSizer  * [2*this->Panel_Number];


     for(int i=0;i<this->Panel_Number;i++){

          this->listctrls[i] = nullptr;

          this->DataPanel_Sizers[i] = nullptr;
     }


     for(int i=0;i<this->Panel_Number;i++){

         this->listctrls[i] = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,120));

         this->Insert_Buttons[i] = new wxButton(this,wxID_ANY,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

         this->DataPanel_Sizers[i] = new wxBoxSizer(wxVERTICAL);

         this->DataPanel_Sizers[i]->Add(this->listctrls[i],1, wxEXPAND | wxTOP | wxALL,10);

         this->DataPanel_Sizers[i]->Add(this->Insert_Buttons[i],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);
     }



     this->Frame_Sizer = new wxBoxSizer(wxVERTICAL);

     for(int i=0;i<this->Panel_Number;i++){

          this->Frame_Sizer->Add(this->DataPanel_Sizers[i],1,wxEXPAND | wxALL,10);
     }


     this->SetSizer(this->Frame_Sizer);

     this->Frame_Sizer->SetSizeHints(this);


     this->Centre(wxBOTH);

     for(int i=0;i<this->Panel_Number;i++){

         this->listctrls[i]->Show();
     }

     this->Show();
}


void Custom_Multi_DataPanel::Construct_Description_Panel(){

     this->DataPanel_Sizers = new wxBoxSizer  * [16];

     for(int i=0;i<16;i++){

         this->DataPanel_Sizers[i] = nullptr;
     }

     this->List_Ctrl_Sizers = new wxBoxSizer  * [16];

     for(int i=0;i<16;i++){

         this->List_Ctrl_Sizers[i] = nullptr;
     }

     this->Buton_Sizers = new wxBoxSizer  * [16];

     for(int i=0;i<16;i++){

         this->Buton_Sizers[i] = nullptr;
     }



     this->scroll_win = new wxScrolledWindow(this,wxID_ANY,wxDefaultPosition,wxSize(1000,-1));

     this->scroll_win->SetBackgroundColour(wxColour(245, 245, 245));


     wxString title = wxT("NWINIX DEPENDENCY MANAGEMENT PANEL");
     
     wxStaticText * text   = new wxStaticText(this->scroll_win ,wxID_ANY,title);

     wxFont Title_Font = text->GetFont();

     Title_Font.SetPointSize(10);

     Title_Font.SetFaceName(wxT("Segoe UI Semibold"));

     text->SetFont(Title_Font);

     text->SetForegroundColour(wxColour(80,80,80));
     



     wxBoxSizer * text_sizer = new wxBoxSizer(wxVERTICAL);

     text_sizer->Add(text,0,wxEXPAND |  wxALIGN_LEFT | wxFIXED_MINSIZE | wxLEFT,20);




     // SETTINGS FOR GIT REPO DATA PANEL

     this->listctrl_git_repo_path = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,75));

     this->InsertButton_for_git_repo_path = new wxButton(this->scroll_win,ID_INSERT_GIT_REPO_DIR,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Buton_Sizers[0] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[0]->Add(this->InsertButton_for_git_repo_path,0, wxEXPAND | wxBOTTOM| wxLEFT | wxRIGHT,10);

     this->List_Ctrl_Sizers[0] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[0]->Add(this->listctrl_git_repo_path,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[0] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[0]->Add(this->List_Ctrl_Sizers[0],1, wxEXPAND | wxBOTTOM| wxLEFT | wxRIGHT,10);

     this->DataPanel_Sizers[0]->Add(this->Buton_Sizers[0],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_git_repo_path->AppendTextColumn(wxT("GIT REPO DIRECTORY"));




     // SETTINGS FOR WAREHOUSE LOCATION DATA PANEL

     this->listctrl_warehouse_location = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,75));

     this->InsertButton_for_warehouse_location = new wxButton(this->scroll_win,ID_INSERT_CONSTRUCTION_POINT,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Buton_Sizers[1] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[1]->Add(this->InsertButton_for_warehouse_location,0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[1] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[1]->Add(this->listctrl_warehouse_location,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[1] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[1]->Add(this->List_Ctrl_Sizers[1],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[1]->Add(this->Buton_Sizers[1],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_warehouse_location->AppendTextColumn(wxT("TARGET DIRECTORY FOR BUILD SYSTEM "));





     // SETTINGS FOR STANDARD DATA PANEL


     this->listctrl_standard = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,75));

     this->InsertButton_for_standard = new wxButton(this->scroll_win,ID_INSERT_STANDART,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Buton_Sizers[2] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[2]->Add(this->InsertButton_for_standard,0, wxEXPAND | wxALL,10);



     this->List_Ctrl_Sizers[2] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[2]->Add(this->listctrl_standard,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[2] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[2]->Add(this->List_Ctrl_Sizers[2],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[2]->Add(this->Buton_Sizers[2],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_standard->AppendTextColumn(wxT("TARGET C++ STANDARD"));









     // SETTINGS FOR HEADER FILE LOCATIONS DATA PANEL

     this->listctrl_for_header_dir = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_header_file_location    = new wxButton(this->scroll_win,ID_INSERT_HEADER_FILE_LOCATION,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_header_file_locations  = new wxButton(this->scroll_win,ID_REMOVE_HEADER_FILE_LOCATION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_header_file_locations   = new wxButton(this->scroll_win,ID_CLEAR_HEADER_FILE_LOCATION,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[3] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[3]->Add(this->InsertButton_for_header_file_location,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[3]->Add(this->Remove_Button_for_header_file_locations, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[3]->Add(this->Clear_Button_for_header_file_locations, 0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[3] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[3]->Add(this->listctrl_for_header_dir,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[3] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[3]->Add(this->List_Ctrl_Sizers[3],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[3]->Add(this->Buton_Sizers[3],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_for_header_dir->AppendTextColumn(wxT("TARGET HEADER FILE DIRECTORIES "));







     // SETTINGS FOR SOURCE FILE LOCATIONS DATA PANEL

     this->listctrl_src_file_location           = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_src_file_locations  = new wxButton(this->scroll_win,ID_INSERT_SRC_LOCATION,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_src_file_locations = new wxButton(this->scroll_win,ID_REMOVE_SRC_LOCATION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_src_file_locations  = new wxButton(this->scroll_win,ID_CLEAR_SRC_LOCATIONS,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[4] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[4]->Add(this->InsertButton_for_src_file_locations,  0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[4]->Add(this->Remove_Button_for_src_file_locations, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[4]->Add(this->Clear_Button_for_src_file_locations,  0, wxEXPAND | wxALL,10);


     this->List_Ctrl_Sizers[4] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[4]->Add(this->listctrl_src_file_location,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[4] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[4]->Add(this->List_Ctrl_Sizers[4],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[4]->Add(this->Buton_Sizers[4],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_src_file_location->AppendTextColumn(wxT("TARGET SOURCE FILE DIRECTORIES "));




     // SETTINGS FOR LIBRARY DIRECTORY DATA PANEL

     this->listctrl_library_dir          = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_library_dir  = new wxButton(this->scroll_win,ID_INSERT_LIB_DIRECTORIES,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_library_dir = new wxButton(this->scroll_win,ID_REMOVE_LIB_DIRECTORY,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_library_dir  = new wxButton(this->scroll_win,ID_CLEAR_LIB_DIRECTORIES,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[5] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[5]->Add(this->InsertButton_for_library_dir,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[5]->Add(this->Remove_Button_for_library_dir, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[5]->Add(this->Clear_Button_for_library_dir, 0, wxEXPAND | wxALL,10);



     this->List_Ctrl_Sizers[5] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[5]->Add(this->listctrl_library_dir,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[5] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[5]->Add(this->List_Ctrl_Sizers[5],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[5]->Add(this->Buton_Sizers[5],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_library_dir->AppendTextColumn(wxT("TARGET LIBRARY DIRECTORIES "));





     // SETTINGS FOR LIBRARY NAMES DATA PANEL

     this->listctrl_library_name          = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_library_name  = new wxButton(this->scroll_win,ID_INSERT_LIBRARIES,wxT("INSERT"),   wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_library_name = new wxButton(this->scroll_win,ID_REMOVE_LIBRARY_NAME,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_library_name  = new wxButton(this->scroll_win,ID_CLEAR_LIBRARY_NAMES,wxT("CLEAR"), wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[6] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[6]->Add(this->InsertButton_for_library_name,  0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[6]->Add(this->Remove_Button_for_library_name, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[6]->Add(this->Clear_Button_for_library_name,  0, wxEXPAND | wxALL,10);




     this->List_Ctrl_Sizers[6] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[6]->Add(this->listctrl_library_name,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[6] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[6]->Add(this->List_Ctrl_Sizers[6],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[6]->Add(this->Buton_Sizers[6],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_library_name->AppendTextColumn(wxT("TARGET LIBRARIES FOR LINKING"));








     // SETTINGS FOR OPTIONS DATA PANEL


     this->listctrl_options = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_options = new wxButton(this->scroll_win,ID_INSERT_OPTIONS,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));



     this->Buton_Sizers[7] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[7]->Add(this->InsertButton_for_options,0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[7] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[7]->Add(this->listctrl_options,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[7] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[7]->Add(this->List_Ctrl_Sizers[7],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[7]->Add(this->Buton_Sizers[7],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_options->AppendTextColumn(wxT("TARGET COMPILER OPTIONS"));





     this->close_panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(1000,220));

     this->close_panel->SetMinSize(wxSize(1000,220));

     this->close_panel->SetBackgroundColour(wxColour(220,220,220));



     this->panel_close_button  = new wxButton(close_panel,ID_CLOSE_DESCRIPTION_PANEL,wxT("CLOSE PANEL"),wxDefaultPosition, wxSize(180, 60));

     this->panel_save_button   = new wxButton(close_panel,ID_SAVE_PANEL_DESCRIPTIONS,wxT("SAVE DESCRIPTIONS"),wxDefaultPosition, wxSize(180, 60));

     this->panel_clear_button  = new wxButton(close_panel,ID_CLEAR_PANEL_DESCRIPTIONS,wxT("CLEAR DESCRIPTIONS"),wxDefaultPosition, wxSize(180, 60));




     this->panel_close_button->SetForegroundColour(wxColour(50,50,50));

     this->panel_save_button->SetForegroundColour(wxColour(50,50,50));

     this->panel_clear_button->SetForegroundColour(wxColour(50,50,50));


     this->Buton_Sizers[8] = new wxBoxSizer(wxVERTICAL);

     this->Buton_Sizers[8]->Add(panel_close_button,1, wxEXPAND | wxALL,10);

     this->Buton_Sizers[8]->Add(panel_save_button, 1, wxEXPAND | wxALL,10);

     this->Buton_Sizers[8]->Add(panel_clear_button,1, wxEXPAND | wxALL,10);

     this->close_panel->SetSizer(this->Buton_Sizers[8]);

     this->close_panel->Fit();

     this->Buton_Sizers[8]->SetSizeHints(close_panel);




     this->Frame_Sizer = new wxBoxSizer(wxVERTICAL);

     this->Frame_Sizer->Add(text_sizer,0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[0],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[1],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[2],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[3],1,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[4],1,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[5],1,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[6],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[7],0,wxEXPAND | wxALL, 20);




     this->scroll_win->SetSizer(this->Frame_Sizer);

     this->scroll_win->SetVirtualSize(wxSize(-1,3500));

     this->scroll_win->FitInside();

     this->scroll_win->SetScrollRate(1,1);

     this->Frame_Sizer->SetSizeHints(this->scroll_win);



     this->topSizer = new wxBoxSizer(wxHORIZONTAL);

     this->topSizer->Add(this->close_panel,0, wxFIXED_MINSIZE  | wxALL, 10);

     this->topSizer->Add(this->scroll_win,1, wxEXPAND  | wxALL,0);


     this->SetSizer(topSizer);

     this->Fit();

     this->topSizer->SetSizeHints(this);


     this->SetMinSize(wxSize(1000,820));

     this->scroll_win->SetMinSize(wxSize(1000,600));


     this->SetSize(wxSize(1000,820));

     this->scroll_win->SetSize(wxSize(1000,600));

     this->close_panel->SetSize(1000,220);

     this->close_panel->Refresh();

     text->Show(true);

     this->listctrl_git_repo_path->Show();

     this->listctrl_warehouse_location->Show();

     this->listctrl_for_header_dir->Show();

     this->listctrl_src_file_location->Show();

     this->listctrl_library_dir->Show();

     this->listctrl_library_name->Show();

     this->listctrl_standard->Show();

     this->listctrl_options->Show();

     this->close_panel->Show();

     this->Centre(wxBOTH);

     this->Show();

     this->Update();
}

void Custom_Multi_DataPanel::Save_Report(){

     wxString Message = "Descriptions are recorded";
            
     Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
     wxT("STATUS:\n"),wxID_ANY,wxT("NWINIX DATA RECORD OPERATION REPORT"),*this->save_bmp);

     dial->ShowModal();
}




void Custom_Multi_DataPanel::Close_Description_Panel(wxCommandEvent & event){

     if(event.GetId() == ID_CLOSE_DESCRIPTION_PANEL ){

        event.Skip(true);

        this->Destroy();
     }
}

void Custom_Multi_DataPanel::Save_Panel_Descriptions(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_PANEL_DESCRIPTIONS ){

        event.Skip(true);

        this->Clear_Record_Data();
     
        this->Record_Data.root_dir = this->Collect_List_Ctrl_Data(this->listctrl_git_repo_path);

        this->Record_Data.warehouse_location = this->Collect_List_Ctrl_Data(this->listctrl_warehouse_location);

        this->Record_Data.options   = this->Collect_List_Ctrl_Data(this->listctrl_options);

        this->Record_Data.standard = this->Collect_List_Ctrl_Data(this->listctrl_standard);


        std::string header_locations = this->Collect_List_Ctrl_Data(this->listctrl_for_header_dir);

        this->Data_Recorder.Extract_Data_List(this->Record_Data.Include_Directories,header_locations);


        std::string source_file_locations = this->Collect_List_Ctrl_Data(this->listctrl_src_file_location);

        this->Data_Recorder.Extract_Data_List(this->Record_Data.Source_File_Directories,source_file_locations);


        std::string library_file_locations = this->Collect_List_Ctrl_Data(this->listctrl_library_dir);

        this->Data_Recorder.Extract_Data_List(this->Record_Data.Library_Directories,library_file_locations);

        
        std::string library_file_names = this->Collect_List_Ctrl_Data(this->listctrl_library_name);

        this->Data_Recorder.Extract_Data_List(this->Record_Data.Library_Files,library_file_names);



        this->Data_Recorder.Receive_Descriptions_Record_Data(&this->Record_Data);

        this->Data_Recorder.Update_Descriptor_File();

        this->Save_Report();
     }
}


void Custom_Multi_DataPanel::Clear_Record_Data(){

     this->Clear_String_Memory(this->Record_Data.root_dir);

     this->Clear_String_Memory(this->Record_Data.warehouse_location);

     this->Clear_String_Memory(this->Record_Data.options);

     this->Clear_String_Memory(this->Record_Data.standard);

     this->Clear_Vector_Memory(this->Record_Data.Include_Directories);

     this->Clear_Vector_Memory(this->Record_Data.Library_Files);

     this->Clear_Vector_Memory(this->Record_Data.Library_Directories);

     this->Clear_Vector_Memory(this->Record_Data.Source_File_Directories);
}



void Custom_Multi_DataPanel::Clear_Vector_Memory(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     size_t vector_size = vec.size();

     for(size_t i=0;i<vector_size;i++){

        this->Clear_String_Memory(vec.at(i));
     }

     vec.shrink_to_fit();
}

void Custom_Multi_DataPanel::Clear_String_Memory(std::string & str){

     str.clear();

     str.shrink_to_fit();
}

void Custom_Multi_DataPanel::Clear_Panel_Descriptions(wxCommandEvent & event){

     if(event.GetId() == ID_CLEAR_PANEL_DESCRIPTIONS ){

        event.Skip(true);

        this->Clear_List_All_Ctrl_Contents();
     }
}


void Custom_Multi_DataPanel::Clear_List_All_Ctrl_Contents(){

     this->listctrl_git_repo_path->DeleteAllItems();

     this->listctrl_warehouse_location->DeleteAllItems();
     
     this->listctrl_for_header_dir->DeleteAllItems();

     this->listctrl_src_file_location->DeleteAllItems();

     this->listctrl_library_dir->DeleteAllItems();
        
     this->listctrl_library_name->DeleteAllItems();

     this->listctrl_standard->DeleteAllItems();

     this->listctrl_options->DeleteAllItems();
}



void Custom_Multi_DataPanel::Create_Exe_Script_Panel(){

     this->Data_Save_Status = false;

     this->Construct_NewData_Panels();


     this->Frame_Sizer = new wxBoxSizer(wxVERTICAL);

     this->Frame_Sizer->Add(this->vbox_path,1, wxEXPAND | wxALL | wxTOP,10);

     this->Frame_Sizer->Add(this->vbox_name,1, wxEXPAND | wxALL | wxBOTTOM,10);

     this->Frame_Sizer->Add(this->Start_Button,0, wxEXPAND | wxALL | wxBOTTOM,10);

     this->Frame_Sizer->Layout();


     this->SetSizer(this->Frame_Sizer);

     this->Frame_Sizer->SetSizeHints(this);

      
     this->listctrl_for_path->Show();

     this->listctrl_for_name->Show();

     this->Show();

     this->Centre(wxBOTH);

}


void Custom_Multi_DataPanel::Construct_NewData_Panels(){
          
     this->listctrl_for_path       = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,200));

     this->listctrl_for_path->AppendTextColumn(wxT("THE SOURCE FILE PATH"));

     this->InsertButton_for_path   = new wxButton(this,ID_INSERT_ITEM_FOR_PATH,wxT("INSERT"),wxDefaultPosition, wxSize(80, 50));


     this->Start_Button     = new wxButton(this,ID_SAVE_MAKE_FILE_DATA,wxT("START"),wxDefaultPosition, wxSize(150, 60));


     this->vbox_path = new wxBoxSizer(wxVERTICAL);

     this->hbox_path = new wxBoxSizer(wxHORIZONTAL);

     this->hbox_path->Add(this->InsertButton_for_path,0, wxALL,10);

     this->hbox_path->Layout();


     this->vbox_path->Add(this->listctrl_for_path,1, wxEXPAND | wxALL,10);

     this->vbox_path->Add(this->hbox_path,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,0);

     this->vbox_path->Layout();




     this->listctrl_for_name = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,200));

     this->listctrl_for_name->AppendTextColumn(wxT("THE NAME OF THE EXECUTABLE FILE TO BE COMPILED"));


     this->InsertButton_for_name   = new wxButton(this,ID_INSERT_ITEM_FOR_NAME,wxT("INSERT"),wxDefaultPosition, wxSize(80, 50));


     this->vbox_name  = new wxBoxSizer(wxVERTICAL);

     this->hbox_name  = new wxBoxSizer(wxHORIZONTAL);

     this->hbox_name->Add(this->InsertButton_for_name,0, wxALL,10);



     this->hbox_name->Layout();


     this->vbox_name->Add(this->listctrl_for_name,1, wxEXPAND | wxALL,10);

     this->vbox_name->Add(this->hbox_name,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,0);

     this->vbox_name->Layout();
}


void Custom_Multi_DataPanel::AppendDataItem(wxDataViewListCtrl * listctrl, wxString str){

     wxVector<wxVariant> data;

     data.push_back(wxVariant(str));

     listctrl->AppendItem(data);

     data.clear();
}



void Custom_Multi_DataPanel::Load_Data_From_Descriptor_File_To_Panel(){

     this->Clear_List_All_Ctrl_Contents();

     this->Des_Reader.Read_Descriptor_File();

     const std::vector<std::string> & include_dir = this->Des_Reader.Get_Include_Directories();

     const std::vector<std::string> & lib_dir     = this->Des_Reader.Get_Library_Directories();

     const std::vector<std::string> & src_dir     = this->Des_Reader.Get_Source_File_Directories();

     const std::vector<std::string> & lib_files   = this->Des_Reader.Get_Library_Files();



     if(include_dir.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_for_header_dir,include_dir);
     }

     if(lib_dir.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_library_dir,lib_dir);
     }


     if(src_dir.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_src_file_location,src_dir);
     }


     if(lib_files.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_library_name,lib_files);
     }



     std::string c_standard = this->Des_Reader.Get_Standard();

     c_standard.shrink_to_fit();

     if(c_standard.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_standard,c_standard);
     }


     std::string options = this->Des_Reader.Get_Options();

     options.shrink_to_fit();

     if(options.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_options,options);
     }


     std::string warehouse_loc = this->Des_Reader.Get_Warehouse_Location();

     warehouse_loc.shrink_to_fit();

     if(warehouse_loc.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_warehouse_location,warehouse_loc);
     }


     std::string repo_dir = this->Des_Reader.Get_Repo_Directory_Location();

     repo_dir.shrink_to_fit();

     if(repo_dir.size()>0){

        this->Load_Data_List_Ctrl(this->listctrl_git_repo_path,repo_dir);      
     }

}




void Custom_Multi_DataPanel::Load_Data_List_Ctrl(wxDataViewListCtrl * listctrl, 

     const std::vector<std::string> & vec){

     size_t vec_size = vec.size();

     for(size_t i=0;i<vec_size;i++){

         this->AppendDataItem(listctrl,vec.at(i));
     }
}


void Custom_Multi_DataPanel::Load_Data_List_Ctrl(wxDataViewListCtrl * listctrl, 

     std::string data){

     this->AppendDataItem(listctrl,data);
}


void Custom_Multi_DataPanel::Insert_Data_For_Path(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_ITEM_FOR_PATH ){

        event.Skip(true);

        wxFileDialog * openFileDialog = new wxFileDialog(this);

        openFileDialog->CentreOnParent(wxBOTH);

        if(openFileDialog->ShowModal() == wxID_OK){

           this->FilePath = openFileDialog->GetPath();
        }

        delete openFileDialog;

        int row_num = this->listctrl_for_path->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_for_path->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_for_path,this->FilePath);
     }
}

void Custom_Multi_DataPanel::Insert_Data_For_Name(wxCommandEvent & event){
     
     if(event.GetId() == ID_INSERT_ITEM_FOR_NAME ){

        event.Skip(true);

        this->ExeFileName  = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER EXECUTABLE FILE NAME   "));

        int row_num = this->listctrl_for_name->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_for_name->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_for_name,this->ExeFileName);
     }
}


void Custom_Multi_DataPanel::Save_MakeFile_Data(wxCommandEvent & event){
     
     if(event.GetId() == ID_SAVE_MAKE_FILE_DATA){

        event.Skip(true);

        this->Data_Save_Status = true;

        this->Show(false);
     }
}






void Custom_Multi_DataPanel::Inser_Git_Repo_Dir(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_GIT_REPO_DIR ){

        event.Skip(true);

        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           this->AppendDataItem(this->listctrl_git_repo_path,DirectoryPath);
        }
     }
}

void Custom_Multi_DataPanel::Insert_Construction_Point(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_CONSTRUCTION_POINT){

        event.Skip(true);
     
        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           this->AppendDataItem(this->listctrl_warehouse_location,DirectoryPath);
        }
     }
}


void Custom_Multi_DataPanel::Insert_Header_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_HEADER_FILE_LOCATION ){

        event.Skip(true);

        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           this->AppendDataItem(this->listctrl_for_header_dir,DirectoryPath);
        }
     }
}




void Custom_Multi_DataPanel::Insert_Source_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_SRC_LOCATION){

        event.Skip(true);

        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           this->AppendDataItem(this->listctrl_src_file_location,DirectoryPath);
        }
     }
}


void Custom_Multi_DataPanel::Insert_Library_Location(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_LIB_DIRECTORIES){

        event.Skip(true);

        wxDirDialog dir_dialog(this, "Select a directory","",

                    wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

        dir_dialog.CenterOnScreen(wxBOTH);

        if(dir_dialog.ShowModal() == wxID_OK){

           wxString DirectoryPath = dir_dialog.GetPath();

           this->AppendDataItem(this->listctrl_library_dir,DirectoryPath);
        }
     }
}


void Custom_Multi_DataPanel::Insert_Library(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_LIBRARIES){

        event.Skip(true);

        wxString FilePATH = wxFileSelector(wxT("Select a library file"));

        this->AppendDataItem(this->listctrl_library_name,FilePATH);
     }
}

void Custom_Multi_DataPanel::Insert_Standart(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_STANDART ){

        event.Skip(true);

        wxString Standard = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER C++ STANDARD  "));

        int row_num = this->listctrl_standard->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_standard->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_standard,Standard);
     }
}



void Custom_Multi_DataPanel::Insert_Option(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_OPTIONS ){

        event.Skip(true);

        wxString Options = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER COMPILER OPTIONS  "));

        int row_num = this->listctrl_options->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_options->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_options,Options);
     }
}








void Custom_Multi_DataPanel::Save_Git_Repo_Dir(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_GIT_REPO_DIR ){

        event.Skip(true);

        wxString DataType(wxT("PROJECT-ROOT-DIR"));

        this->Save_Data(this->listctrl_git_repo_path,DataType);

     }

}


void Custom_Multi_DataPanel::Save_Construction_Point(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_CONSTRUCTION_POINT ){

        event.Skip(true);

        wxString DataType(wxT("PROJECT-WAREHOUSE-LOCATION"));

        this->Save_Data(this->listctrl_warehouse_location,DataType);
     }

}



void Custom_Multi_DataPanel::Save_Header_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_HEADER_FILE_LOCATION ){

        event.Skip(true);

        wxString DataType(wxT("INCLUDE-DIRECTORIES"));

        this->Save_Data(this->listctrl_for_header_dir,DataType);
     }
}


    
void Custom_Multi_DataPanel::Save_Standart(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_STANDART ){

        event.Skip(true);

        wxString DataType(wxT("C++-STANDARD"));

        this->Save_Data(this->listctrl_standard,DataType);
     }
}


void Custom_Multi_DataPanel::Save_Option(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_OPTIONS ){

        event.Skip(true);

        wxString DataType(wxT("OPTIONS"));

        this->Save_Data(this->listctrl_options,DataType);
     }
}



void Custom_Multi_DataPanel::Save_Source_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_SRC_LOCATION){

        event.Skip(true);

        wxString DataType(wxT("SOURCE-FILE-DIRECTORIES"));

        this->Save_Data(this->listctrl_src_file_location,DataType);
     }
}


void Custom_Multi_DataPanel::Save_Library_Directory(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_LIB_DIRECTORY ){

        event.Skip(true);

        wxString DataType(wxT("LIBRARY-DIRECTORIES"));

        this->Save_Data(this->listctrl_library_dir,DataType);
     }
}


    
void Custom_Multi_DataPanel::Save_Library_Name(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_LIBRARY_NAME ){

        event.Skip(true);

        wxString DataType(wxT("LIBRARY-FILES"));

        this->Save_Data(this->listctrl_library_name,DataType);
     }
}

void Custom_Multi_DataPanel::Save_Data(wxDataViewListCtrl * listctrl, wxString DataType){

     std::string  list_ctrl_data = this->Collect_List_Ctrl_Data(listctrl);

     this->Data_Recorder.Record_Data(DataType.ToStdString(),list_ctrl_data);
}


std::string Custom_Multi_DataPanel::Collect_List_Ctrl_Data(wxDataViewListCtrl * listctrl){

       std::string  list_ctrl_data;

       wxString item_data = wxT("");

       int item_count = listctrl->GetItemCount();

       for(int i=0;i<item_count;i++){

           item_data = item_data +

           listctrl->GetTextValue(i,0) + wxT('\n');
       }

       list_ctrl_data = item_data.ToStdString();

       return list_ctrl_data;
}


void Custom_Multi_DataPanel::Remove_Header_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_HEADER_FILE_LOCATION ){

        event.Skip(true);

        int row = this->listctrl_for_header_dir->GetSelectedRow();

        this->listctrl_for_header_dir->DeleteItem(row);
     }
}


void Custom_Multi_DataPanel::Remove_Source_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_SRC_LOCATION ){

        event.Skip(true);

        int row = this->listctrl_src_file_location->GetSelectedRow();

        this->listctrl_src_file_location->DeleteItem(row);
     }
}



void Custom_Multi_DataPanel::Remove_Library_Directory(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_LIB_DIRECTORY ){

        event.Skip(true);

        int row = this->listctrl_library_dir->GetSelectedRow();

        this->listctrl_library_dir->DeleteItem(row);
     }
}

    
void Custom_Multi_DataPanel::Remove_Library_Name(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_LIBRARY_NAME ){

        event.Skip(true);

        int row = this->listctrl_library_name->GetSelectedRow();

        this->listctrl_library_name->DeleteItem(row);
     }
}


void Custom_Multi_DataPanel::Clear_Header_File_Locations(wxCommandEvent & event){
     
     if(event.GetId() == ID_CLEAR_HEADER_FILE_LOCATION ){

        event.Skip(true);

        this->listctrl_for_header_dir->DeleteAllItems();
     }
}



void Custom_Multi_DataPanel::Clear_Source_File_Locations(wxCommandEvent & event){
     
     if(event.GetId() == ID_CLEAR_SRC_LOCATIONS ){

        event.Skip(true);

        this->listctrl_src_file_location->DeleteAllItems();        
     }
}



void Custom_Multi_DataPanel::Clear_Library_Directories(wxCommandEvent & event){

     if(event.GetId() == ID_CLEAR_LIB_DIRECTORIES ){

        event.Skip(true);

        this->listctrl_library_dir->DeleteAllItems(); 
     }
}



void Custom_Multi_DataPanel::Clear_Library_Names(wxCommandEvent & event){

     if(event.GetId() == ID_CLEAR_LIBRARY_NAMES){

        event.Skip(true);

        this->listctrl_library_name->DeleteAllItems();
     }
}

bool Custom_Multi_DataPanel::Get_Data_Save_Status(){

     return this->Data_Save_Status;
}



