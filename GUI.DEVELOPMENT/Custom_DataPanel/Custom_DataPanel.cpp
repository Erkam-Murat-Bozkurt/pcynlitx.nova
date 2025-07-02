
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



#include "Custom_DataPanel.hpp"

BEGIN_EVENT_TABLE(Custom_DataPanel,wxFrame)
    EVT_BUTTON(ID_INSERT_ITEM,Custom_DataPanel::Insert_Data)
    EVT_BUTTON(ID_REMOVE_ITEM,Custom_DataPanel::Remove_Data)
    EVT_BUTTON(ID_SAVE_RECORDS,Custom_DataPanel::Save_Data)
    EVT_PAINT(Custom_DataPanel::OnPaint)
END_EVENT_TABLE()


Custom_DataPanel::Custom_DataPanel(wxFrame * frm, wxSize frame_size)

                : wxFrame(frm, wxID_ANY,wxT(""),wxDefaultPosition,frame_size)
{
    this->frame_ptr = frm;

    wxIcon Frame_Icon(wxT("C:\\Program Files\\Pcynlitx\\icons\\frame_icon.png"),wxBITMAP_TYPE_PNG,-1,-1);

    this->SetIcon(Frame_Icon);

    this->listctrl = new wxDataViewListCtrl(this, wxID_ANY,wxDefaultPosition,frame_size);

    this->InsertButton  = new wxButton(this,ID_INSERT_ITEM,wxT("INSERT"),wxDefaultPosition, wxSize(80, 50));

    this->RemoveButton  = new wxButton(this,ID_REMOVE_ITEM,wxT("REMOVE"),wxDefaultPosition,wxSize(80, 50));

    this->SaveButton    = new wxButton(this,ID_SAVE_RECORDS,wxT("SAVE"),wxDefaultPosition, wxSize(80, 50));


    this->vbox = new wxBoxSizer(wxVERTICAL);

    this->hbox = new wxBoxSizer(wxHORIZONTAL);

    this->hbox->Add(this->InsertButton,0, wxALL,10);

    this->hbox->Add(this->RemoveButton,0, wxALL,10);

    this->hbox->Add(this->SaveButton,0, wxALL,10);

    this->hbox->Layout();


    this->vbox->Add(this->listctrl,1, wxEXPAND | wxALL,10);

    this->vbox->Add(this->hbox,0,wxALIGN_RIGHT | wxFIXED_MINSIZE | wxALL,0);

    this->vbox->Layout();


    this->SetSizer(this->vbox);

    this->vbox->SetSizeHints(this);


    this->Centre();

    this->SetAutoLayout(true);

    this->DataType = wxT("");

    this->Data = wxT("");

    this->Descriptor_File_Path = wxT("");

    this->File_Slection = false;

    this->Text_Enter_Status = false;

    this->Raise();
}

void Custom_DataPanel::DrawBackground(wxDC & dc, wxWindow *  wnd, const wxRect& rect)
{
     dc.SetBrush(wxColour(245,245,245));

     dc.DrawRectangle(rect.GetX()-5, rect.GetY()-5, rect.GetWidth()+5,rect.GetHeight()+5);
}

void Custom_DataPanel::OnPaint(wxPaintEvent & event)
{
     event.Skip(false);

     wxPaintDC dc(this);

     wxRect rect(this->GetSize());

     this->DrawBackground(dc,this,rect);
}

void Custom_DataPanel::Receive_Descriptor_File_Path(wxString path){

     this->Descriptor_File_Path = path;
}

void Custom_DataPanel::Receive_Data_Type(wxString DataType){

     this->DataType = DataType;
}


void Custom_DataPanel::Receive_Data(wxString Data){

     this->Data = Data;
}

void Custom_DataPanel::File_Slection_Status(bool status){

     this->File_Slection = status;
}

void Custom_DataPanel::Receive_Text_Enter_Status(bool status){

     this->Text_Enter_Status = status;
}

void Custom_DataPanel::AppendDataItem(wxString str){

     wxVector<wxVariant> data;

     data.push_back(wxVariant(str));

     this->listctrl->AppendItem(data);

     data.clear();
}

void Custom_DataPanel::AppendTextColumn(wxString str){

     this->listctrl->AppendTextColumn(str);
}


Custom_DataPanel::~Custom_DataPanel()
{

}


void Custom_DataPanel::Insert_Data(wxCommandEvent & event){

     if(event.GetId() == ID_INSERT_ITEM ){

        event.Skip(true);

        this->DataInput = "";

        if(this->File_Slection){

           wxFileDialog * openFileDialog = new wxFileDialog(this);

           openFileDialog->CentreOnParent(wxBOTH);

           if (openFileDialog->ShowModal() == wxID_OK){

               this->DataInput = openFileDialog->GetPath();
           }

           delete openFileDialog;
        }
        else{

              if(this->Text_Enter_Status){

                 this->DataInput  = wxGetTextFromUser(wxT(""),

                  wxT("   ENTER YOUR SELECTION   "));
              }
              else{
                      wxDirDialog dlg(NULL, "Choose input directory", "",

                                   wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);

                      if(dlg.ShowModal() == wxID_OK){

                         this->DataInput =dlg.GetPath();
                     }
              }
        }

        this->AppendDataItem(this->DataInput);
    }
}

void Custom_DataPanel::Remove_Data(wxCommandEvent & event){

     if(event.GetId() == ID_REMOVE_ITEM ){

        event.Skip(true);

        int row = this->listctrl->GetSelectedRow();

        this->listctrl->DeleteItem(row);
    }
}

void Custom_DataPanel::Save_Data(wxCommandEvent & event){

     if(event.GetId() == ID_SAVE_RECORDS ){

        event.Skip(true);

        this->Show(false);

        int item_count = this->listctrl->GetItemCount();

        wxString item_data = "";

        for(int i=0;i<item_count;i++){

            item_data = item_data +

            this->listctrl->GetTextValue(i,0) + "\n";
        }


        wxString shell_command = "";
         
        this->Process_Ptr = new Process_Manager(this->frame_ptr);

        shell_command = "C:\\Program Files\\Pcynlitx\\Pcynlitx_Kernel.exe " +

        this->Descriptor_File_Path + wxT(" -ar ") + this->DataType;

        shell_command = shell_command + " ";

        shell_command = shell_command + item_data;


        this->Process_Ptr->Fork_Process(shell_command);

        int status  = this->Process_Ptr->Get_Process_Exit_Status();

        delete this->Process_Ptr;

    }
}

wxDataViewListCtrl * Custom_DataPanel::GetDataViewListCtrl(){

     return this->listctrl;
}
