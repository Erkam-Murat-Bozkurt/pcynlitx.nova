

/*

 * Copyright (C) { Erkam Murat Bozkurt } - All Rights Reserved
 * 
 * This source code is protected under international copyright law.  All rights
 * reserved and protected by the copyright holders.
 * 
 * This file is confidential and only available to authorized individuals with the
 * permission of the copyright holders.  If you encounter this file and do not have
 * permission, please contact the copyright holders and delete this file.

*/

#include "Project_File_Selection_Dialog.h"

Project_File_Selection_Dialog::Project_File_Selection_Dialog(wxFrame * Frame){

    this->File_Selection_Dialog = new wxDialog(Frame,-1,"MAKE SELECTION",wxDefaultPosition,

            wxSize(650,500),wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);


    this->File_Selection_Panel = new wxPanel(this->File_Selection_Dialog,-1,

           wxDefaultPosition,wxSize(650,500));


    this->vbox = new wxBoxSizer(wxVERTICAL);

    this->hbox = new wxBoxSizer(wxHORIZONTAL);

    this->file_selection_sizer = new wxBoxSizer(wxVERTICAL);

    this->File_Selection_Control = new wxFileCtrl(this->File_Selection_Panel,

                        wxID_ANY,wxEmptyString,wxEmptyString,wxFileSelectorDefaultWildcardStr,

                        wxFC_DEFAULT_STYLE | wxFC_NOSHOWHIDDEN ,wxDefaultPosition,wxSize(650,500));


    this->File_Selection_Control->Centre();


    this->SelectButton = new wxButton(this->File_Selection_Dialog,wxID_OK,wxT(" Select "),

                        wxDefaultPosition, wxSize(90, 45));

    this->closeButton = new wxButton(this->File_Selection_Dialog,wxID_CANCEL,wxT(" Close "),

                        wxDefaultPosition, wxSize(90, 45));



    this->hbox->Add(this->SelectButton,0,wxALL,5);

    this->hbox->Add(this->closeButton,0,wxALL,5);

    this->hbox->Layout();



    this->file_selection_sizer->Add(this->File_Selection_Control,0, wxALL);

    this->File_Selection_Panel->SetSizer(this->file_selection_sizer);

    this->file_selection_sizer->SetSizeHints(this->File_Selection_Panel);


    this->vbox->Add(this->File_Selection_Panel,0, wxEXPAND | wxALL,20);

    this->vbox->Add(this->hbox,0, wxFIXED_MINSIZE | wxALL,10);

    this->File_Selection_Dialog->SetSizer(this->vbox);

    this->vbox->SetSizeHints(this->File_Selection_Dialog);


    this->File_Selection_Dialog->Centre();

    this->File_Selection_Dialog->SetAutoLayout(true);

    this->File_Selection_Dialog->Show(true);
}

Project_File_Selection_Dialog::~Project_File_Selection_Dialog(){

    if(this->File_Selection_Control != nullptr){

       delete this->File_Selection_Control;

       this->File_Selection_Control = nullptr;
    }

    if(this->SelectButton != nullptr){

       delete this->SelectButton;

       this->SelectButton = nullptr;
    }

    if(this->closeButton != nullptr){

        delete this->closeButton;

        this->closeButton = nullptr;
    }

    if(this->hbox != nullptr){

       delete this->hbox;

       this->hbox = nullptr;
    }

    if(this->vbox != nullptr){

       delete this->vbox;

       this->vbox = nullptr;
    }

    if(this->File_Selection_Panel != nullptr){

        delete this->File_Selection_Panel;

        this->File_Selection_Panel = nullptr;
    }

    if(this->file_selection_sizer != nullptr){

       delete this->file_selection_sizer;

       this->file_selection_sizer = nullptr;
    }

    if(this->File_Selection_Dialog != nullptr){

       delete this->File_Selection_Dialog;

       this->File_Selection_Dialog = nullptr;
    }
}

wxDialog * Project_File_Selection_Dialog::Get_Project_File_Selection_Dialog(){

    return this->File_Selection_Dialog;
}

wxFileCtrl * Project_File_Selection_Dialog::Get_File_Selection_Control(){

    return this->File_Selection_Control;
}
