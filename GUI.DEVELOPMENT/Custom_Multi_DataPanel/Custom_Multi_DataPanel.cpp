

#include "Custom_Multi_DataPanel.hpp"


BEGIN_EVENT_TABLE(Custom_Multi_DataPanel,wxDialog )
    EVT_BUTTON(ID_INSERT_ITEM_FOR_PATH,Custom_Multi_DataPanel::Insert_Data_For_Path)
    EVT_BUTTON(ID_INSERT_ITEM_FOR_NAME,Custom_Multi_DataPanel::Insert_Data_For_Name)
    EVT_BUTTON(ID_SAVE_MAKE_FILE_DATA,Custom_Multi_DataPanel::Save_MakeFile_Data)
    EVT_PAINT(Custom_Multi_DataPanel::OnPaint)
END_EVENT_TABLE()

Custom_Multi_DataPanel::Custom_Multi_DataPanel(wxFrame * parent, wxWindowID id, const wxString & title, 

   const wxPoint &pos, const wxSize &size, 
   
   long style) : wxDialog(parent,id,title,pos,size,
   
   wxDEFAULT_DIALOG_STYLE |wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxSTAY_ON_TOP)
{

     this->Parent_Frame = parent;

     wxIcon Frame_Icon(wxT("D:\\Pcynlitx_Build_Platform\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

     this->SetIcon(Frame_Icon);

     this->SetTitle(wxT("INSERT RELATED DATA"));

     this->Data_Save_Status = false;
}


Custom_Multi_DataPanel::~Custom_Multi_DataPanel(){

}

void Custom_Multi_DataPanel::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(245,245,245));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_Multi_DataPanel::OnPaint(wxPaintEvent & event)
{
     event.Skip(false);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
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

     this->InsertButton_for_path   = new wxButton(this,ID_INSERT_ITEM_FOR_PATH,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));


     this->Start_Button     = new wxButton(this,ID_SAVE_MAKE_FILE_DATA,wxT("START"),wxDefaultPosition, wxSize(150, 40));


     this->vbox_path = new wxBoxSizer(wxVERTICAL);

     this->hbox_path = new wxBoxSizer(wxHORIZONTAL);

     this->hbox_path->Add(this->InsertButton_for_path,0, wxALL,10);

     this->hbox_path->Layout();


     this->vbox_path->Add(this->listctrl_for_path,1, wxEXPAND | wxALL,10);

     this->vbox_path->Add(this->hbox_path,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,0);

     this->vbox_path->Layout();




     this->listctrl_for_name       = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,wxSize(700,200));

     this->listctrl_for_name->AppendTextColumn(wxT("THE NAME OF THE EXECUTABLE FILE TO BE COMPILED"));


     this->InsertButton_for_name   = new wxButton(this,ID_INSERT_ITEM_FOR_NAME,wxT("INSERT"),wxDefaultPosition, wxSize(75, 40));


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


bool Custom_Multi_DataPanel::Get_Data_Save_Status(){

     return this->Data_Save_Status;
}



