

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



#include "Custom_Multi_DataPanel.hpp"


BEGIN_EVENT_TABLE(Custom_Multi_DataPanel,wxDialog )

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

    EVT_BUTTON(ID_INSERT_COMPILER_OPTIONS,Custom_Multi_DataPanel::Insert_Compiler_Options)

    EVT_BUTTON(ID_INSERT_LINKER_OPTIONS,Custom_Multi_DataPanel::Insert_Linker_Options)

    EVT_BUTTON(ID_INSERT_BUILD_SYSTEM_TYPE,Custom_Multi_DataPanel::Select_Build_System_Type)

    EVT_BUTTON(ID_INSERT_PROJECT_NAME,Custom_Multi_DataPanel::Insert_Project_Name)

    EVT_BUTTON(ID_INSERT_VERSION_NUMBER,Custom_Multi_DataPanel::Insert_Version_Number)



    EVT_BUTTON(ID_SAVE_GIT_REPO_DIR,Custom_Multi_DataPanel::Save_Git_Repo_Dir)

    EVT_BUTTON(ID_SAVE_CONSTRUCTION_POINT,Custom_Multi_DataPanel::Save_Construction_Point)

    EVT_BUTTON(ID_SAVE_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Save_Header_File_Location)

    EVT_BUTTON(ID_SAVE_SRC_LOCATION,Custom_Multi_DataPanel::Save_Source_File_Location)

    EVT_BUTTON(ID_SAVE_LIB_DIRECTORY,Custom_Multi_DataPanel::Save_Library_Directory)

    EVT_BUTTON(ID_SAVE_LIBRARY_NAME,Custom_Multi_DataPanel::Save_Library_Name)

    EVT_BUTTON(ID_SAVE_STANDART,Custom_Multi_DataPanel::Save_Standart)

    EVT_BUTTON(ID_SAVE_COMPILER_OPTIONS,Custom_Multi_DataPanel::Save_Compiler_Options)

    EVT_BUTTON(ID_SAVE_LINKER_OPTIONS,Custom_Multi_DataPanel::Save_Linker_Options)




    EVT_BUTTON(ID_REMOVE_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Remove_Header_File_Location)

    EVT_BUTTON(ID_REMOVE_SRC_LOCATION,Custom_Multi_DataPanel::Remove_Source_File_Location)
  
    EVT_BUTTON(ID_REMOVE_LIB_DIRECTORY,Custom_Multi_DataPanel::Remove_Library_Directory)
  
    EVT_BUTTON(ID_REMOVE_LIBRARY_NAME,Custom_Multi_DataPanel::Remove_Library_Name)
  
    EVT_BUTTON(ID_REMOVE_COMPILER_OPTION,Custom_Multi_DataPanel::Remove_Compiler_Option)

    EVT_BUTTON(ID_REMOVE_LINKER_OPTION,Custom_Multi_DataPanel::Remove_Linker_Option)

    EVT_BUTTON(ID_REMOVE_COMPILER_PATH,Custom_Multi_DataPanel::Remove_Compiler_Path)



    EVT_BUTTON(ID_CLEAR_HEADER_FILE_LOCATION,Custom_Multi_DataPanel::Clear_Header_File_Locations)

    EVT_BUTTON(ID_CLEAR_SRC_LOCATIONS,Custom_Multi_DataPanel::Clear_Source_File_Locations)
  
    EVT_BUTTON(ID_CLEAR_LIB_DIRECTORIES,Custom_Multi_DataPanel::Clear_Library_Directories)
  
    EVT_BUTTON(ID_CLEAR_LIBRARY_NAMES,Custom_Multi_DataPanel::Clear_Library_Names)

    EVT_BUTTON(ID_CLEAR_COMPILER_OPTIONS,Custom_Multi_DataPanel::Clear_Compiler_Options)

    EVT_BUTTON(ID_CLEAR_LINKER_OPTIONS,Custom_Multi_DataPanel::Clear_Linker_Options)



    EVT_BUTTON(ID_CLOSE_DESCRIPTION_PANEL,Custom_Multi_DataPanel::Close_Description_Panel)

    EVT_BUTTON(ID_SAVE_PANEL_DESCRIPTIONS,Custom_Multi_DataPanel::Save_Panel_Descriptions)

    EVT_BUTTON(ID_CLEAR_PANEL_DESCRIPTIONS,Custom_Multi_DataPanel::Clear_Panel_Descriptions)


    EVT_BUTTON(ID_SELECT_COMPILER_PATH,Custom_Multi_DataPanel::Insert_Compiler_Path)

    EVT_BUTTON(ID_CLEAR_COMPILER_SELECTIONS,Custom_Multi_DataPanel::Clear_Compiler_Paths)



    EVT_PAINT(Custom_Multi_DataPanel::OnPaint)

END_EVENT_TABLE()



Custom_Multi_DataPanel::Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint & pos, const wxSize & size, long style, char opr_sis) : 
   
   wxDialog(parent,id,title,pos,size, style), Data_Recorder(opr_sis), Des_Reader(opr_sis)
{
     this->Parent_Frame = parent;

     this->Frame_Bitmap = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("FRAME_ICON"));

     wxIcon Frame_Icon;

     Frame_Icon.CopyFromBitmap(*this->Frame_Bitmap);

     this->SetIcon(Frame_Icon);

     this->SetTitle(wxT("PCYNLITX BUILD SYSTEM DESCRIPTION PANEL"));


     this->save_bmp 
  
      = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("SAVE_SUCCESS_ICON"));

     this->exclamation_mark_bmp 
  
      = this->Rsc_Loader.CreateBitmapFromPngResource(wxString("EXCLAMATION_ICON"));

     this->SetBackgroundColour(wxColour(250,250,250));

     this->Data_Recorder.parent = this;

     this->Data_Save_Status = false;
}


Custom_Multi_DataPanel::~Custom_Multi_DataPanel(){

}

void Custom_Multi_DataPanel::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(240,240,240));

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

     this->DataPanel_Sizers = new wxBoxSizer  * [18];

     for(int i=0;i<18;i++){

         this->DataPanel_Sizers[i] = nullptr;
     }

     this->List_Ctrl_Sizers = new wxBoxSizer  * [18];

     for(int i=0;i<18;i++){

         this->List_Ctrl_Sizers[i] = nullptr;
     }

     this->Buton_Sizers = new wxBoxSizer  * [18];

     for(int i=0;i<18;i++){

         this->Buton_Sizers[i] = nullptr;
     }



     this->scroll_win = new wxScrolledWindow(this,wxID_ANY,wxDefaultPosition,wxSize(1000,-1));

     this->scroll_win->SetBackgroundColour(wxColour(240, 240, 240));


     wxString title = wxT("PCYNLITX DEPENDENCY MANAGEMENT PANEL");
     
     wxStaticText * text   = new wxStaticText(this->scroll_win ,wxID_ANY,title);

     wxFont Title_Font = text->GetFont();

     Title_Font.SetPointSize(14);

     Title_Font.SetFaceName(wxT("Oswald"));

     text->SetFont(Title_Font);

     text->SetForegroundColour(wxColour(65, 65, 75,0xff));
     



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







     // SETTINGS FOR BUILD SYSTEM SELECTION PANEL


     this->listctrl_build_system_type = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,75));

     this->InsertButton_for_build_system_type = new wxButton(this->scroll_win,ID_INSERT_BUILD_SYSTEM_TYPE,wxT("SELECT"),wxDefaultPosition, wxSize(75, 40));

     this->Buton_Sizers[3] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[3]->Add(this->InsertButton_for_build_system_type,0, wxEXPAND | wxALL,10);



     this->List_Ctrl_Sizers[3] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[3]->Add(this->listctrl_build_system_type,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[3] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[3]->Add(this->List_Ctrl_Sizers[3],0, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[3]->Add(this->Buton_Sizers[3],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_build_system_type->AppendTextColumn(wxT("BUILD SYSTEM TYPE"));






     // SETTINGS FOR HEADER FILE LOCATIONS DATA PANEL

     this->listctrl_for_header_dir = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_header_file_location    = new wxButton(this->scroll_win,ID_INSERT_HEADER_FILE_LOCATION,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_header_file_locations  = new wxButton(this->scroll_win,ID_REMOVE_HEADER_FILE_LOCATION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_header_file_locations   = new wxButton(this->scroll_win,ID_CLEAR_HEADER_FILE_LOCATION,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[4] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[4]->Add(this->InsertButton_for_header_file_location,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[4]->Add(this->Remove_Button_for_header_file_locations, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[4]->Add(this->Clear_Button_for_header_file_locations, 0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[4] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[4]->Add(this->listctrl_for_header_dir,1,wxEXPAND | wxALL,10);

     this->DataPanel_Sizers[4] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[4]->Add(this->List_Ctrl_Sizers[4],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[4]->Add(this->Buton_Sizers[4],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_for_header_dir->AppendTextColumn(wxT("TARGET HEADER FILE DIRECTORIES "));







     // SETTINGS FOR SOURCE FILE LOCATIONS DATA PANEL

     this->listctrl_src_file_location           = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_src_file_locations  = new wxButton(this->scroll_win,ID_INSERT_SRC_LOCATION,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_src_file_locations = new wxButton(this->scroll_win,ID_REMOVE_SRC_LOCATION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_src_file_locations  = new wxButton(this->scroll_win,ID_CLEAR_SRC_LOCATIONS,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[5] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[5]->Add(this->InsertButton_for_src_file_locations,  0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[5]->Add(this->Remove_Button_for_src_file_locations, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[5]->Add(this->Clear_Button_for_src_file_locations,  0, wxEXPAND | wxALL,10);


     this->List_Ctrl_Sizers[5] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[5]->Add(this->listctrl_src_file_location,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[5] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[5]->Add(this->List_Ctrl_Sizers[5],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[5]->Add(this->Buton_Sizers[5],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_src_file_location->AppendTextColumn(wxT("TARGET SOURCE FILE DIRECTORIES "));




     // SETTINGS FOR LIBRARY DIRECTORY DATA PANEL

     this->listctrl_library_dir          = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_library_dir  = new wxButton(this->scroll_win,ID_INSERT_LIB_DIRECTORIES,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_library_dir = new wxButton(this->scroll_win,ID_REMOVE_LIB_DIRECTORY,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_library_dir  = new wxButton(this->scroll_win,ID_CLEAR_LIB_DIRECTORIES,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[6] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[6]->Add(this->InsertButton_for_library_dir,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[6]->Add(this->Remove_Button_for_library_dir, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[6]->Add(this->Clear_Button_for_library_dir, 0, wxEXPAND | wxALL,10);



     this->List_Ctrl_Sizers[6] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[6]->Add(this->listctrl_library_dir,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[6] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[6]->Add(this->List_Ctrl_Sizers[6],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[6]->Add(this->Buton_Sizers[6],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_library_dir->AppendTextColumn(wxT("TARGET LIBRARY DIRECTORIES "));





     // SETTINGS FOR LIBRARY NAMES DATA PANEL

     this->listctrl_library_name          = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,300));

     this->InsertButton_for_library_name  = new wxButton(this->scroll_win,ID_INSERT_LIBRARIES,  wxT("INSERT"),   wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_library_name = new wxButton(this->scroll_win,ID_REMOVE_LIBRARY_NAME,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_library_name  = new wxButton(this->scroll_win,ID_CLEAR_LIBRARY_NAMES,wxT("CLEAR"), wxDefaultPosition, wxSize(75, 40)); 


     this->Buton_Sizers[7] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[7]->Add(this->InsertButton_for_library_name,  0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[7]->Add(this->Remove_Button_for_library_name, 0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[7]->Add(this->Clear_Button_for_library_name,  0, wxEXPAND | wxALL,10);




     this->List_Ctrl_Sizers[7] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[7]->Add(this->listctrl_library_name,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[7] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[7]->Add(this->List_Ctrl_Sizers[7],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[7]->Add(this->Buton_Sizers[7],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_library_name->AppendTextColumn(wxT("TARGET LIBRARIES FOR LINKING"));








     // SETTINGS FOR COMPILER OPTIONS DATA PANEL


     this->listctrl_compiler_options = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_compiler_options = new wxButton(this->scroll_win,ID_INSERT_COMPILER_OPTIONS,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_compiler_options  = new wxButton(this->scroll_win,ID_REMOVE_COMPILER_OPTION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_compiler_options   = new wxButton(this->scroll_win,ID_CLEAR_COMPILER_OPTIONS,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 



     this->Buton_Sizers[8] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[8]->Add(this->InsertButton_for_compiler_options,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[8]->Add(this->Remove_Button_for_compiler_options,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[8]->Add(this->Clear_Button_for_compiler_options,0, wxEXPAND | wxALL,10);



     this->List_Ctrl_Sizers[8] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[8]->Add(this->listctrl_compiler_options,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[8] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[8]->Add(this->List_Ctrl_Sizers[8],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[8]->Add(this->Buton_Sizers[8],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_compiler_options->AppendTextColumn(wxT("TARGET COMPILER OPTIONS"));





     // SETTINGS FOR LIBKER OPTIONS DATA PANEL


     this->listctrl_linker_options = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_linker_options = new wxButton(this->scroll_win,ID_INSERT_LINKER_OPTIONS,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_linker_options  = new wxButton(this->scroll_win,ID_REMOVE_LINKER_OPTION,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));

     this->Clear_Button_for_linker_options   = new wxButton(this->scroll_win,ID_CLEAR_LINKER_OPTIONS,wxT("CLEAR"),wxDefaultPosition, wxSize(75, 40)); 



     this->Buton_Sizers[9] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[9]->Add(this->InsertButton_for_linker_options,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[9]->Add(this->Remove_Button_for_linker_options,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[9]->Add(this->Clear_Button_for_linker_options,0, wxEXPAND | wxALL,10);


     this->List_Ctrl_Sizers[9] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[9]->Add(this->listctrl_linker_options,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[9] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[9]->Add(this->List_Ctrl_Sizers[9],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[9]->Add(this->Buton_Sizers[9],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_linker_options->AppendTextColumn(wxT("TARGET LINKER OPTIONS"));



     // SETTINGS FOR PROJECT NAME DATA PANEL


     this->listctrl_project_name = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_project_name = new wxButton(this->scroll_win,ID_INSERT_PROJECT_NAME,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));



     this->Buton_Sizers[10] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[10]->Add(this->InsertButton_for_project_name,0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[10] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[10]->Add(this->listctrl_project_name,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[10] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[10]->Add(this->List_Ctrl_Sizers[10],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[10]->Add(this->Buton_Sizers[10],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_project_name->AppendTextColumn(wxT("PROJECT NAME"));



     // SETTINGS FOR VERSION NUMBER PANEL


     this->listctrl_version_number = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_version_number = new wxButton(this->scroll_win,ID_INSERT_VERSION_NUMBER,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));




     this->Buton_Sizers[11] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[11]->Add(this->InsertButton_for_version_number,0, wxEXPAND | wxALL,10);

     this->List_Ctrl_Sizers[11] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[11]->Add(this->listctrl_version_number,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[11] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[11]->Add(this->List_Ctrl_Sizers[11],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[11]->Add(this->Buton_Sizers[11],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_version_number->AppendTextColumn(wxT("VERSION MUNBER"));





     // SETTINGS FOR COMPILER PATHS


     this->listctrl_compiler_path = new wxDataViewListCtrl(this->scroll_win, wxID_ANY,wxDefaultPosition,wxSize(-1,150));

     this->InsertButton_for_compiler_paths   = new wxButton(this->scroll_win,ID_SELECT_COMPILER_PATH,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));

     this->Remove_Button_for_compiler_paths  = new wxButton(this->scroll_win,ID_REMOVE_COMPILER_PATH,wxT("REMOVE"),wxDefaultPosition, wxSize(75, 40));



     this->Buton_Sizers[12] = new wxBoxSizer(wxHORIZONTAL);

     this->Buton_Sizers[12]->Add(this->InsertButton_for_compiler_paths,0, wxEXPAND | wxALL,10);

     this->Buton_Sizers[12]->Add(this->Remove_Button_for_compiler_paths,0, wxEXPAND | wxALL,10);


     this->List_Ctrl_Sizers[12] = new wxBoxSizer(wxHORIZONTAL);

     this->List_Ctrl_Sizers[12]->Add(this->listctrl_compiler_path,1,wxEXPAND | wxALL,10);


     this->DataPanel_Sizers[12] = new wxBoxSizer(wxVERTICAL);

     this->DataPanel_Sizers[12]->Add(this->List_Ctrl_Sizers[12],1, wxEXPAND | wxTOP | wxALL,10);

     this->DataPanel_Sizers[12]->Add(this->Buton_Sizers[12],0, wxALIGN_RIGHT | wxFIXED_MINSIZE | wxBOTTOM | wxALL,10);

     this->listctrl_compiler_path->AppendTextColumn(wxT("COMPILER PATHS"));




     // CLOSE PANEL ETTINGS

     this->close_panel  = new wxPanel(this,wxID_ANY,wxDefaultPosition,wxSize(220,1000));

     this->close_panel->SetBackgroundColour(wxColour(200,200,200,0xff));

     this->close_panel->SetMinSize(wxSize(220,1000));

     this->close_panel->SetSize(wxSize(220,1000));



     this->panel_close_button  = new wxButton(close_panel,ID_CLOSE_DESCRIPTION_PANEL,
     
                               wxT("CLOSE PANEL"),wxDefaultPosition, wxSize(150, 60));

     this->panel_save_button   = new wxButton(close_panel,ID_SAVE_PANEL_DESCRIPTIONS,
     
                               wxT("SAVE PANEL"),wxDefaultPosition, wxSize(150, 60));

     this->panel_clear_button  = new wxButton(close_panel,ID_CLEAR_PANEL_DESCRIPTIONS,
     
                               wxT("CLEAR PANEL"),wxDefaultPosition, wxSize(150, 60));


     wxFont buton_font = this->panel_close_button->GetFont();
     
     buton_font.SetFaceName(wxT("Oswald"));
                          
     buton_font.SetPointSize(10);


     this->panel_save_button->SetFont(buton_font);
                                                    
     this->panel_clear_button->SetFont(buton_font);

     this->panel_close_button->SetFont(buton_font);


     this->panel_close_button->SetForegroundColour(wxColour(50,50,50));

     this->panel_save_button->SetForegroundColour(wxColour(50,50,50));

     this->panel_clear_button->SetForegroundColour(wxColour(50,50,50));


     this->Buton_Sizers[13] = new wxBoxSizer(wxVERTICAL);

     this->Buton_Sizers[13]->Add(panel_close_button,0, wxFIXED_MINSIZE | wxALL,20);

     this->Buton_Sizers[13]->Add(panel_save_button, 0, wxFIXED_MINSIZE | wxALL,20);

     this->Buton_Sizers[13]->Add(panel_clear_button,0, wxFIXED_MINSIZE | wxALL,20);

     this->close_panel->SetSizer(this->Buton_Sizers[13]);

     this->close_panel->Fit();

     this->Buton_Sizers[13]->SetSizeHints(this->close_panel);




     this->Frame_Sizer = new wxBoxSizer(wxVERTICAL);

     this->Frame_Sizer->Add(text_sizer,0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[0],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[1],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[2],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[3],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[4],1,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[5],1,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[6],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[7],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[8],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[9],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[10],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[11],0,wxEXPAND | wxALL, 20);

     this->Frame_Sizer->Add(this->DataPanel_Sizers[12],0,wxEXPAND | wxALL, 20);



     this->scroll_win->SetSizer(this->Frame_Sizer);

     this->scroll_win->SetVirtualSize(wxSize(-1,3500));

     this->scroll_win->FitInside();

     this->scroll_win->SetScrollRate(1,1);

     this->Frame_Sizer->SetSizeHints(this->scroll_win);



     this->topSizer = new wxBoxSizer(wxHORIZONTAL);

     this->topSizer->Add(this->close_panel,0, wxEXPAND  | wxALL, 0);

     this->topSizer->Add(this->scroll_win,1, wxEXPAND  | wxALL,0);


     this->SetSizer(this->topSizer);

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

     this->listctrl_build_system_type->Show();

     this->listctrl_project_name->Show();

     this->listctrl_version_number->Show();

     this->listctrl_compiler_options->Show();

     this->listctrl_linker_options->Show();

     this->listctrl_compiler_path->Show();

     this->close_panel->Show();

     this->Centre(wxBOTH);

     this->Show();

     this->Update();
}

void Custom_Multi_DataPanel::Save_Report(){

     wxString Message = "Descriptions are recorded";
            
     Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
     wxT("STATUS:\n"),wxID_ANY,wxT("PCYNLITX DATA RECORD OPERATION REPORT"),*this->save_bmp);

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
        
        this->Collect_List_Ctrl_Data(this->listctrl_git_repo_path,this->Record_Data.root_dir);
     
        this->Collect_List_Ctrl_Data(this->listctrl_warehouse_location,this->Record_Data.warehouse_location);

        this->Collect_List_Ctrl_Data(this->listctrl_compiler_options,this->Record_Data.compiler_options);

        this->Collect_List_Ctrl_Data(this->listctrl_linker_options,this->Record_Data.linker_options);

        this->Collect_List_Ctrl_Data(this->listctrl_project_name,this->Record_Data.project_name);

        this->Collect_List_Ctrl_Data(this->listctrl_version_number,this->Record_Data.version_number);

        this->Collect_List_Ctrl_Data(this->listctrl_standard,this->Record_Data.standard);

        this->Collect_List_Ctrl_Data(this->listctrl_build_system_type,this->Record_Data.build_system_type);

        this->Collect_List_Ctrl_Data(this->listctrl_for_header_dir,this->Record_Data.Include_Directories);

        this->Collect_List_Ctrl_Data(this->listctrl_library_dir,this->Record_Data.Library_Directories);

        this->Collect_List_Ctrl_Data(this->listctrl_library_name,this->Record_Data.Library_Files);

        this->Collect_List_Ctrl_Data(this->listctrl_src_file_location,this->Record_Data.Source_File_Directories);

        this->Collect_List_Ctrl_Data(this->listctrl_compiler_path,this->Record_Data.compiler_paths);


        this->Data_Recorder.Receive_Descriptions_Record_Data(&this->Record_Data);

        this->Data_Recorder.Update_Descriptor_File();

        this->Save_Report();
     }
}


void Custom_Multi_DataPanel::Clear_Record_Data(){

     this->Clear_String_Memory(this->Record_Data.root_dir);

     this->Clear_String_Memory(this->Record_Data.warehouse_location);

     this->Clear_String_Memory(this->Record_Data.standard);

     this->Clear_String_Memory(this->Record_Data.project_name);

     this->Clear_String_Memory(this->Record_Data.version_number);

     this->Clear_Vector_Memory(this->Record_Data.Include_Directories);

     this->Clear_Vector_Memory(this->Record_Data.Library_Files);

     this->Clear_Vector_Memory(this->Record_Data.Library_Directories);

     this->Clear_Vector_Memory(this->Record_Data.Source_File_Directories);

     this->Clear_Vector_Memory(this->Record_Data.compiler_options);

     this->Clear_Vector_Memory(this->Record_Data.linker_options);

     this->Clear_Vector_Memory(this->Record_Data.compiler_paths);
}



void Custom_Multi_DataPanel::Clear_Vector_Memory(std::vector<std::string> & vec){

     vec.shrink_to_fit();

     size_t vector_size = vec.size();

     for(size_t i=0;i<vector_size;i++){

        this->Clear_String_Memory(vec.at(i));
     }

     vec.clear();

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

     this->listctrl_compiler_options->DeleteAllItems();

     this->listctrl_linker_options->DeleteAllItems();

     this->listctrl_build_system_type->DeleteAllItems();

     this->listctrl_project_name->DeleteAllItems();

     this->listctrl_version_number->DeleteAllItems();

     this->listctrl_compiler_path->DeleteAllItems();
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
          
     this->listctrl_for_path  = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,200));

     this->listctrl_for_path->AppendTextColumn(wxT("THE SOURCE FILE PATH"));

     this->InsertButton_for_path = new wxButton(this,ID_INSERT_ITEM_FOR_PATH,wxT("INSERT"),wxDefaultPosition, wxSize(80, 50));


     this->Start_Button = new wxButton(this,ID_SAVE_MAKE_FILE_DATA,wxT("START"),wxDefaultPosition, wxSize(150, 60));


     this->vbox_path = new wxBoxSizer(wxVERTICAL);

     this->hbox_path = new wxBoxSizer(wxHORIZONTAL);

     this->hbox_path->Add(this->InsertButton_for_path,0, wxALL,10);

     this->hbox_path->Layout();


     this->vbox_path->Add(this->listctrl_for_path,1, wxEXPAND | wxALL,10);

     this->vbox_path->Add(this->hbox_path,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,0);

     this->vbox_path->Layout();




     this->listctrl_for_name = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,200));

     this->listctrl_for_name->AppendTextColumn(wxT("THE NAME OF THE EXECUTABLE FILE TO BE COMPILED"));


     this->InsertButton_for_name = new wxButton(this,ID_INSERT_ITEM_FOR_NAME,wxT("INSERT"),wxDefaultPosition, wxSize(80, 50));


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

     bool syntax_error_status     = this->Des_Reader.Get_Syntax_Error_Status();

     bool leack_of_description    = this->Des_Reader.Get_Lack_of_Decleration_Error_Status();

     bool description_error = syntax_error_status && !leack_of_description;

     bool invalid_des_file_status = this->Des_Reader.Get_Invalid_Descriptor_File_Status();


     bool error_status = false;

     if(description_error || invalid_des_file_status){

         error_status = true;
     }


     if(!error_status){

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



         const std::vector<std::string> & compiler_options = this->Des_Reader.Get_Compiler_Options();
                                    
         if(compiler_options.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_compiler_options,compiler_options);
         }


         const std::vector<std::string> & linker_options = this->Des_Reader.Get_Linker_Options();

         if(linker_options.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_linker_options,linker_options);
         }



         const std::vector<std::string> & compiler_paths = this->Des_Reader.Get_Compiler_Paths();

         if(compiler_paths.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_compiler_path,compiler_paths);
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



         std::string build_system_type = this->Des_Reader.Get_Build_System_Type();

         if(build_system_type.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_build_system_type,build_system_type);      
         }

         std::string project_name = this->Des_Reader.Get_Project_Name();

         if(project_name.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_project_name,project_name);      
         }

         std::string version_number = this->Des_Reader.Get_Version_Number();

         if(version_number.size()>0){

            this->Load_Data_List_Ctrl(this->listctrl_version_number,version_number);      
         }


         bool gui_read_error_status  = !this->Des_Reader.Get_Gui_Read_Success_Status(); 

         bool leack_of_description    = this->Des_Reader.Get_Lack_of_Decleration_Error_Status();

         // IN THE CASE OF NEW EMPTY FILE, LACK OF DESCRIPTION ERROR MUST NOT BE STOP THE DATA PANEL
         // BECAUSE, THE DESCRIPTOR FILE CONSTRUCTION JUST STARTED AND IT DID NOT CONSTRUCTED YET, 
         // The lack of description errors must be control on the build system construction process
         // This is the reason why the condition (gui_read_error_status && !leack_of_description) is ued in here

         if(gui_read_error_status && !leack_of_description){

            wxString Message = "\nSome information may be missed on the project file";

            Message += "\nPlease control descriptor file";

            Message += "\n\nMessage:";

            Message += Des_Reader.Get_Error_Message();

            Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
                         wxT("ERROR REPORT:"),wxID_ANY,
                         
                         wxT("PCYNLITX PLATFORM OPERATION REPORT"),*this->exclamation_mark_bmp);

            dial->SetSize(wxSize(600,420));

            dial->Centre(wxBOTH);

            dial->ShowModal();
         }
     }
     else{
           
           wxString Message = "There is an error in descriptor file";

           Message += "\nor descriptor file is invalid";

           Message += "\nPlease control descriptor file";

            
           Custom_Message_Dialog * dial = new Custom_Message_Dialog(this,Message,
            
               wxT("STATUS:\n"),wxID_ANY,wxT("PCYNLITX DATA RECORD OPERATION REPORT"),*this->exclamation_mark_bmp);

           dial->ShowModal();
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



void Custom_Multi_DataPanel::Insert_Project_Name(wxCommandEvent & event){
     
     if(event.GetId() == ID_INSERT_PROJECT_NAME ){

        event.Skip(true);

        wxString Project_Name  = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER PROJECT NAME   "));

        int row_num = this->listctrl_project_name->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_project_name->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_project_name,Project_Name);
     }
}

void Custom_Multi_DataPanel::Insert_Compiler_Path(wxCommandEvent & event){
     
     if(event.GetId() == ID_SELECT_COMPILER_PATH ){

        event.Skip(true);

        wxString Compiler_Path;
        
        wxFileDialog * openFileDialog = new wxFileDialog(this);

        openFileDialog->CentreOnParent(wxBOTH);

        if(openFileDialog->ShowModal() == wxID_OK){

           Compiler_Path = openFileDialog->GetPath();
        }

        delete openFileDialog;

        this->AppendDataItem(this->listctrl_compiler_path,Compiler_Path);
     }
}


void Custom_Multi_DataPanel::Clear_Compiler_Paths(wxCommandEvent & event){
     
     if(event.GetId() == ID_CLEAR_COMPILER_SELECTIONS){

        event.Skip(true);

        this->listctrl_compiler_path->DeleteAllItems();
     }
}

void Custom_Multi_DataPanel::Insert_Version_Number(wxCommandEvent & event){
     
     if(event.GetId() == ID_INSERT_VERSION_NUMBER ){

        event.Skip(true);

        wxString Version_Number  = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER EXECUTABLE FILE NAME   "));

        int row_num = this->listctrl_version_number->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_version_number->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_version_number,Version_Number);
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

           this->listctrl_git_repo_path->DeleteAllItems();

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

           this->listctrl_warehouse_location->DeleteAllItems();

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



void Custom_Multi_DataPanel::Insert_Compiler_Options(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_COMPILER_OPTIONS ){

        event.Skip(true);

        wxString Compiler_Options = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER A COMPILER OPTION  "));

        this->AppendDataItem(this->listctrl_compiler_options,Compiler_Options);
     }
}

void Custom_Multi_DataPanel::Insert_Linker_Options(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_LINKER_OPTIONS ){

        event.Skip(true);

        wxString Linker_Options = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER A LINKER OPTION  "));

        this->AppendDataItem(this->listctrl_linker_options,Linker_Options);
     }
}


void Custom_Multi_DataPanel::Select_Build_System_Type(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_BUILD_SYSTEM_TYPE){

        event.Skip(true);

        wxString Choices[3];

        std::string cmake_ = "CMAKE";

        std::string shell_scripting_ = "Shell-Scripting";

        std::string empty_choice = "";


        wxString build_system_type;

        Choices[0] = wxString(cmake_);

        Choices[1] = wxString(shell_scripting_);

        Choices[2] = wxString(empty_choice);

        wxSingleChoiceDialog Choice(this,wxT("Please select build system"),wxT("BUILD SYSTEM SELECTION PANEL"),2,Choices,
        
            nullptr,wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER | wxOK | wxCANCEL | wxCENTRE,wxDefaultPosition);

        Choice.SetSize(wxSize(450,320));

        Choice.Centre(wxBOTH);

        if(Choice.ShowModal() == wxID_OK){

           int selection = Choice.GetSelection();

           if(selection == 0){

               build_system_type = Choices[0];
           }
           
           if(selection == 1){

               build_system_type = Choices[1];
           }
        };

        int row_num = this->listctrl_build_system_type->GetItemCount();

        for(int i=0;i<row_num;i++){

            this->listctrl_build_system_type->DeleteItem(i);
        }

        this->AppendDataItem(this->listctrl_build_system_type,build_system_type);
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


void Custom_Multi_DataPanel::Save_Compiler_Options(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_COMPILER_OPTIONS ){

        event.Skip(true);

        wxString DataType(wxT("COMPILER-OPTIONS"));

        this->Save_Data(this->listctrl_compiler_options,DataType);
     }
}

void Custom_Multi_DataPanel::Save_Linker_Options(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_LINKER_OPTIONS ){

        event.Skip(true);

        wxString DataType(wxT("LINKER-OPTIONS"));

        this->Save_Data(this->listctrl_linker_options,DataType);
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

     std::string data_type = DataType.ToStdString();

     if(data_type == "PROJECT-ROOT-DIR")
     {
        std::string root_dir;

        this->Collect_List_Ctrl_Data(listctrl,root_dir);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),root_dir);
     }


     if(data_type == "PROJECT-WAREHOUSE-LOCATION"){

        std::string warehouse_location;

        this->Collect_List_Ctrl_Data(listctrl,warehouse_location);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),warehouse_location);
     }


     if(data_type == "C++-STANDARD"){

        std::string standard;

       this->Collect_List_Ctrl_Data(listctrl,standard);

       this->Data_Recorder.Record_Data(DataType.ToStdString(),standard);
     }  


     if(data_type == "BUILD-SYSTEM"){

        std::string build_type;

        this->Collect_List_Ctrl_Data(listctrl,build_type);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),build_type);
     }  



     if(data_type == "PROJECT-NAME"){

        std::string project_name;

        this->Collect_List_Ctrl_Data(listctrl,project_name);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),project_name);
     }  


     if(data_type == "VERSION-NUMBER"){

        std::string version_number;

        this->Collect_List_Ctrl_Data(listctrl,version_number);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),version_number);
     }  



     if(data_type == "INCLUDE-DIRECTORIES"){

        std::vector<std::string> inc_dirs;

        this->Collect_List_Ctrl_Data(listctrl,inc_dirs);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),inc_dirs);
     }



     if(data_type == "SOURCE-FILE-DIRECTORIES"){

        std::vector<std::string> src_dirs;

        this->Collect_List_Ctrl_Data(listctrl,src_dirs);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),src_dirs);
     }



     if(data_type == "LIBRARY-DIRECTORIES"){

        std::vector<std::string> lib_dirs;

        this->Collect_List_Ctrl_Data(listctrl,lib_dirs);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),lib_dirs);
     }


     if(data_type == "LIBRARY-FILES"){

        std::vector<std::string> lib_files;

        this->Collect_List_Ctrl_Data(listctrl,lib_files);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),lib_files);
     }


     if(data_type == "COMPILER-OPTIONS"){
    
        std::vector<std::string> comp_options;

        this->Collect_List_Ctrl_Data(listctrl,comp_options);

        this->Data_Recorder.Record_Data(DataType.ToStdString(),comp_options);
     }  


     if(data_type == "LINKER-OPTIONS"){

        std::vector<std::string> linker_options;

        this->Collect_List_Ctrl_Data(listctrl,linker_options); 

        this->Data_Recorder.Record_Data(DataType.ToStdString(),linker_options);
     }    


     if(data_type == "COMPILER-PATHS"){

        std::vector<std::string> compiler_paths;

        this->Collect_List_Ctrl_Data(listctrl,compiler_paths); 

        this->Data_Recorder.Record_Data(DataType.ToStdString(),compiler_paths);
     }  
}


void Custom_Multi_DataPanel::Collect_List_Ctrl_Data(wxDataViewListCtrl * listctrl, 

     std::vector<std::string> & data){

     int item_count = listctrl->GetItemCount();

     for(int i=0;i<item_count;i++){

         wxString item_data = wxT("");

         item_data = listctrl->GetTextValue(i,0);

         data.push_back(item_data.ToStdString());
     }
}


void Custom_Multi_DataPanel::Collect_List_Ctrl_Data(wxDataViewListCtrl * listctrl, 

     std::string & str){

     int item_count = listctrl->GetItemCount();

     for(int i=0;i<item_count;i++){

         wxString item_data = listctrl->GetTextValue(i,0);

         str = item_data.ToStdString();
     }
}


void Custom_Multi_DataPanel::Remove_Header_File_Location(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_HEADER_FILE_LOCATION ){

        event.Skip(true);

        int row = this->listctrl_for_header_dir->GetSelectedRow();

        this->listctrl_for_header_dir->DeleteItem(row);
     }
}


void Custom_Multi_DataPanel::Remove_Compiler_Path(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_COMPILER_PATH ){

        event.Skip(true);

        int row = this->listctrl_compiler_path->GetSelectedRow();

        this->listctrl_compiler_path->DeleteItem(row);
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


void Custom_Multi_DataPanel::Remove_Linker_Option(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_LINKER_OPTION){

        event.Skip(true);

        int row = this->listctrl_linker_options->GetSelectedRow();

        this->listctrl_linker_options->DeleteItem(row);
     }
}

void Custom_Multi_DataPanel::Remove_Compiler_Option(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_COMPILER_OPTION){

        event.Skip(true);

        int row = this->listctrl_compiler_options->GetSelectedRow();

        this->listctrl_compiler_options->DeleteItem(row);
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

void Custom_Multi_DataPanel::Clear_Compiler_Options(wxCommandEvent & event){

     if(event.GetId() == ID_CLEAR_COMPILER_OPTIONS){

        event.Skip(true);

        this->listctrl_compiler_options->DeleteAllItems();
     }
}


void Custom_Multi_DataPanel::Clear_Linker_Options(wxCommandEvent & event){

     if(event.GetId() == ID_CLEAR_LINKER_OPTIONS){

        event.Skip(true);

        this->listctrl_linker_options->DeleteAllItems();
     }
}


bool Custom_Multi_DataPanel::Get_Data_Save_Status(){

     return this->Data_Save_Status;
}



